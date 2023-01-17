#include <string>
#include <iostream>
#include <stack>
#include "SudokuExactCovering.h"
#include "definitions.h"

int **getBasicSudokuGrid()
{
  int **sudokuToColor = new int *[SUDOKU_GAME_SIZE];
  for (int i = 0; i < SUDOKU_GAME_SIZE; i++)
  {
    sudokuToColor[i] = new int[SUDOKU_GAME_SIZE];
  }
  for (int i = 0; i < SUDOKU_GAME_SIZE; i++)
  {
    for (int j = 0; j < SUDOKU_GAME_SIZE; j++)
    {
      sudokuToColor[i][j] = 0;
    }
  }
  return sudokuToColor;
}

void printSolutions(std::stack<DancingLinkNode> *solutionStack, int **sudokuToColor)
{
  if (solutionStack == NULL)
  {
    std::cout << "Sem solução" << std::endl;
    exit(1);
  }

  while (!solutionStack->empty())
  {
    DancingLinkNode solution = solutionStack->top();
    sudokuToColor[solution.row][solution.column] = solution.color + 1;
    solutionStack->pop();
  }

  std::cout << "Encontrada coloração para sudoku: " << std::endl;
  for (int i = 0; i < SUDOKU_GAME_SIZE; i++)
  {
    if (i % SUBGRID_SIZE == 0)
      std::cout << "-------------------------" << std::endl;

    for (int j = 0; j < SUDOKU_GAME_SIZE; j++)
    {
      if (j % SUBGRID_SIZE == 0)
        std::cout << "| ";
      std::cout << sudokuToColor[i][j] << " ";
    }

    std::cout << "|" << std::endl;
  }
  std::cout << "-------------------------" << std::endl;

  delete solutionStack;
  solutionStack = NULL;
}

int main()
{
  SudokuExactCovering *sudokuExactCoveringTableau = new SudokuExactCovering();

  if (!(sudokuExactCoveringTableau->createBasicSudokuDancingLinksTableau()))
  {
    delete sudokuExactCoveringTableau;
    return 1;
  }

  int **sudokuToColor = getBasicSudokuGrid();

  std::string sudokuToColorFilename("sudokus/1.txt");

  printSolutions(sudokuExactCoveringTableau->findSolutionsFromFilename(sudokuToColorFilename.c_str()),
                 sudokuToColor);

  if (sudokuExactCoveringTableau != NULL)
    delete sudokuExactCoveringTableau;

  return 0;
}
