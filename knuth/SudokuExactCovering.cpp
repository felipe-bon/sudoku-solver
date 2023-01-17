#include "SudokuExactCovering.h"

SudokuExactCovering::SudokuExactCovering()
{
  headerNode = new DancingLinkNode();
  headerNode->isHeader = true;
  headerNode->right = headerNode->left = headerNode->up = headerNode->down = headerNode;
  temporarySolution = new std::stack<DancingLinkNode>();
  isSolved = false;
}
SudokuExactCovering::~SudokuExactCovering()
{
  deleteDancingLinksStructure();
  delete headerNode;
  delete temporarySolution;
}

bool SudokuExactCovering::addNewColumn(DancingLinkNode *insertingNode)
{
  if (!insertingNode->isHeader || headerNode == insertingNode)
    return false;

  insertingNode->left = headerNode->left;
  insertingNode->right = headerNode;
  headerNode->left->right = insertingNode;
  headerNode->left = insertingNode;

  return true;
}

void SudokuExactCovering::deleteDancingLinksStructure()
{
  DancingLinkNode *deleteNextCol = headerNode->right;
  DancingLinkNode *temp;
  while (deleteNextCol != headerNode)
  {
    DancingLinkNode *deleteNextRow = deleteNextCol->down;
    while (!deleteNextRow->isHeader)
    {
      temp = deleteNextRow->down;
      delete deleteNextRow;
      deleteNextRow = temp;
    }
    temp = deleteNextCol->right;
    delete deleteNextCol;
    deleteNextCol = temp;
  }
}

DancingLinkNode *SudokuExactCovering::setDancingLinkPositionColored(int i, int j, int sudokuPositionColor)
{
  DancingLinkNode *toFind = new DancingLinkNode(i, j, sudokuPositionColor - 1);
  DancingLinkNode *keepNode = findNode(toFind);
  delete toFind;

  if (keepNode != NULL)
  {
    DancingLinkNode *columnNode = keepNode->colHeader;
    cover(columnNode);

    coverRowsFromNode(keepNode);
  }

  return keepNode;
}

std::stack<DancingLinkNode> *SudokuExactCovering::findSolutionsFromFilename(const char *filename)
{
  isSolved = false;
  while (!temporarySolution->empty())
    temporarySolution->pop();

  std::ifstream fileStream(filename);
  if (fileStream.fail())
  {
    std::cout << "Erro ao abrir" << filename << std::endl;
    fileStream.close();
    return NULL;
  }

  std::stack<DancingLinkNode *> coveredPuzzleNodes;

  for (int i = 0; i < SUDOKU_GAME_SIZE; i++)
  {
    for (int j = 0; j < SUDOKU_GAME_SIZE; j++)
    {
      int sudokuPositionColor;
      fileStream >> sudokuPositionColor;
      if (fileStream.fail() || sudokuPositionColor < 0 || sudokuPositionColor > SUDOKU_GAME_SIZE)
      {
        std::cout << "Sudoku inválido" << std::endl;
        fileStream.close();
        return NULL;
      }

      if (sudokuPositionColor != 0)
      {
        DancingLinkNode *keepNode = setDancingLinkPositionColored(i, j, sudokuPositionColor);
        if (keepNode == NULL)
        {
          std::cout << "Não foi possível setar posição " << i << "," << j << " na cor " << sudokuPositionColor << std::endl;
          fileStream.close();
          return NULL;
        }

        coveredPuzzleNodes.push(keepNode);
        temporarySolution->push(*keepNode);
      }
    }
  }
  fileStream.close();

  if (!performAlgorithmX())
    std::cout << "Não foi possível resolver" << std::endl;

  std::stack<DancingLinkNode> cleaningStack, *solutionStack;

  while (!temporarySolution->empty())
  {
    cleaningStack.push(temporarySolution->top());
    temporarySolution->pop();
  }

  solutionStack = new std::stack<DancingLinkNode>();
  while (!cleaningStack.empty())
  {
    solutionStack->push(cleaningStack.top());
    cleaningStack.pop();
  }

  return solutionStack;
}

void SudokuExactCovering::unlinkLaterallyNode(DancingLinkNode *n)
{
  n->right->left = n->left;
  n->left->right = n->right;
}

void SudokuExactCovering::unlinkVerticallyNode(DancingLinkNode *n)
{
  n->up->down = n->down;
  n->down->up = n->up;
}

void SudokuExactCovering::cover(DancingLinkNode *node)
{
  DancingLinkNode *columnNode = node->colHeader;

  unlinkLaterallyNode(columnNode);

  for (DancingLinkNode *nodesFromColumn = columnNode->down; nodesFromColumn != columnNode; nodesFromColumn = nodesFromColumn->down)
  {
    for (DancingLinkNode *nodesFromColumnRow = nodesFromColumn->right; nodesFromColumnRow != nodesFromColumn; nodesFromColumnRow = nodesFromColumnRow->right)
    {
      unlinkVerticallyNode(nodesFromColumnRow);
    }
  }
}

void SudokuExactCovering::relinkLaterallyNode(DancingLinkNode *n)
{
  n->right->left = n;
  n->left->right = n;
}

void SudokuExactCovering::relinkVerticallyNode(DancingLinkNode *n)
{
  n->up->down = n;
  n->down->up = n;
}

void SudokuExactCovering::uncover(DancingLinkNode *node)
{
  DancingLinkNode *colNode = node->colHeader;
  for (DancingLinkNode *nodeFromColumn = colNode->up; nodeFromColumn != colNode; nodeFromColumn = nodeFromColumn->up)
  {
    for (DancingLinkNode *nodeFromColumnRow = nodeFromColumn->left; nodeFromColumnRow != nodeFromColumn; nodeFromColumnRow = nodeFromColumnRow->left)
    {
      relinkVerticallyNode(node);
    }
  }
  relinkLaterallyNode(node);
}

bool SudokuExactCovering::isEmpty() { return headerNode == headerNode->right; }

void SudokuExactCovering::coverRowsFromNode(DancingLinkNode *node)
{
  for (DancingLinkNode *columnsFromRow = node->right;
       columnsFromRow != node;
       columnsFromRow = columnsFromRow->right)
  {
    cover(columnsFromRow->colHeader);
  }
}

void SudokuExactCovering::uncoverRowsFromNode(DancingLinkNode *node)
{
  for (DancingLinkNode *columnsFromRow = node->right;
       columnsFromRow != node;
       columnsFromRow = columnsFromRow->right)
  {
    uncover(columnsFromRow->colHeader);
  }
}

bool SudokuExactCovering::performAlgorithmX()
{
  if (isEmpty())
    return true;

  DancingLinkNode *columnWithLessOnes = chooseLesserNumberOfOnesColumn();

  if (columnWithLessOnes == NULL)
    return false;

  cover(columnWithLessOnes);

  for (DancingLinkNode *rowFromLesserZeroesCol = columnWithLessOnes->down;
       rowFromLesserZeroesCol != columnWithLessOnes;
       rowFromLesserZeroesCol = rowFromLesserZeroesCol->down)
  {
    temporarySolution->push(*rowFromLesserZeroesCol);

    coverRowsFromNode(rowFromLesserZeroesCol);

    if (!(isSolved = performAlgorithmX()))
    {
      temporarySolution->pop();
    }

    uncoverRowsFromNode(rowFromLesserZeroesCol);
  }

  uncover(columnWithLessOnes);

  return isSolved;
}

int SudokuExactCovering::countNonZeroesOnColumn(DancingLinkNode *column)
{
  int tempCount = 0;
  for (DancingLinkNode *elementsFromColumnCovered = column->down;
       elementsFromColumnCovered != column;
       elementsFromColumnCovered = elementsFromColumnCovered->down)
  {
    tempCount++;
  }
  return tempCount;
}

DancingLinkNode *SudokuExactCovering::chooseLesserNumberOfOnesColumn()
{
  DancingLinkNode *currentLesserOnes = headerNode->right;
  int best = -1;

  for (DancingLinkNode *col = currentLesserOnes;
       col != headerNode;
       col = col->right)
  {
    int columnOnesCount = countNonZeroesOnColumn(col);
    if (columnOnesCount < best || best == -1)
    {
      currentLesserOnes = col;
      best = columnOnesCount;
    }
  }

  if (currentLesserOnes == headerNode || best <= 0)
  {
    return NULL;
  }

  return currentLesserOnes;
}

DancingLinkNode *SudokuExactCovering::findNode(DancingLinkNode *toFind)
{
  for (DancingLinkNode *rowNode = headerNode->right;
       rowNode != headerNode;
       rowNode = rowNode->right)
  {
    for (DancingLinkNode *colNode = rowNode->down;
         colNode != rowNode;
         colNode = colNode->down)
    {
      if (colNode->row == toFind->row &&
          colNode->column == toFind->column &&
          colNode->color == toFind->color)
      {
        return colNode;
      }
    }
  }
  return NULL;
}

void SudokuExactCovering::create4ConstraintsTableau(DancingLinkNode *exactCoveringTableau[MAX_ROWS][MAX_COLS])
{
  for (int i = 0; i < MAX_ROWS; i++)
  {
    for (int j = 0; j < MAX_COLS; j++)
    {
      exactCoveringTableau[i][j] = NULL;
    }
  }

  for (int possibleRows = 0; possibleRows < SUDOKU_GAME_SIZE; possibleRows++)
  {
    for (int possibleColumns = 0; possibleColumns < SUDOKU_GAME_SIZE; possibleColumns++)
    {
      for (int possibleColors = 0; possibleColors < SUDOKU_GAME_SIZE; possibleColors++)
      {
        int row = (possibleRows * COL_EXACT_MATCHING + possibleColumns * SUDOKU_GAME_SIZE + possibleColors);
        DancingLinkNode *rowCostraintNode = exactCoveringTableau[row][ROW_EXACT_MATCHING + (possibleRows * SUDOKU_GAME_SIZE + possibleColors)] =
            new DancingLinkNode(possibleRows, possibleColumns, possibleColors);
        DancingLinkNode *colConstraintNode = exactCoveringTableau[row][COL_EXACT_MATCHING + (possibleColumns * SUDOKU_GAME_SIZE + possibleColors)] =
            new DancingLinkNode(possibleRows, possibleColumns, possibleColors);
        DancingLinkNode *colorConstraintNode = exactCoveringTableau[row][COLOR_EXACT_COVER + (possibleRows * SUDOKU_GAME_SIZE + possibleColumns)] =
            new DancingLinkNode(possibleRows, possibleColumns, possibleColors);
        DancingLinkNode *subgridConstraintNode =
            exactCoveringTableau[row][SUBGRID_EXACT_COVER + ((possibleRows / SUBGRID_SIZE +
                                                              possibleColumns / SUBGRID_SIZE * SUBGRID_SIZE) *
                                                                 SUDOKU_GAME_SIZE +
                                                             possibleColors)] = new DancingLinkNode(possibleRows, possibleColumns, possibleColors);

        rowCostraintNode->right = colConstraintNode;
        rowCostraintNode->left = subgridConstraintNode;
        colConstraintNode->left = rowCostraintNode;
        colConstraintNode->right = colorConstraintNode;
        colorConstraintNode->left = colConstraintNode;
        colorConstraintNode->right = subgridConstraintNode;
        subgridConstraintNode->left = colorConstraintNode;
        subgridConstraintNode->right = rowCostraintNode;
      }
    }
  }
}

bool SudokuExactCovering::linkConstraints(DancingLinkNode *exactCoveringTableau[MAX_ROWS][MAX_COLS])
{
  for (int j = 0; j < MAX_COLS; j++)
  {
    DancingLinkNode *newColumnHeader = new DancingLinkNode();
    newColumnHeader->isHeader = true;
    newColumnHeader->up = newColumnHeader->down =
        newColumnHeader->left = newColumnHeader->right =
            newColumnHeader->colHeader = newColumnHeader;
    DancingLinkNode *newColumnRow = newColumnHeader;

    for (int i = 0; i < MAX_ROWS; i++)
    {
      if (exactCoveringTableau[i][j] != NULL)
      {
        exactCoveringTableau[i][j]->up = newColumnRow;
        newColumnRow->down = exactCoveringTableau[i][j];
        exactCoveringTableau[i][j]->down = newColumnHeader;
        newColumnHeader->up = exactCoveringTableau[i][j];
        exactCoveringTableau[i][j]->colHeader = newColumnHeader;
        newColumnRow = exactCoveringTableau[i][j];
      }
    }

    if (newColumnHeader->down == newColumnHeader || !addNewColumn(newColumnHeader))
    {
      for (int i = 0; i < MAX_ROWS; i++)
      {
        for (int j = 0; j < MAX_COLS; j++)
        {
          if (exactCoveringTableau[i][j] != NULL)
            delete exactCoveringTableau[i][j];
        }
      }
      return false;
    }
  }

  return true;
}

bool SudokuExactCovering::createBasicSudokuDancingLinksTableau()
{
  DancingLinkNode *exactCoveringTableau[MAX_ROWS][MAX_COLS];

  create4ConstraintsTableau(exactCoveringTableau);

  return linkConstraints(exactCoveringTableau);
}
