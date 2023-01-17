#include "definitions.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <functional>

struct DancingLinkNode
{
  DancingLinkNode *left;
  DancingLinkNode *down;
  DancingLinkNode *up;
  DancingLinkNode *right;
  DancingLinkNode *colHeader;

  int row;
  int column;
  int color;

  bool isHeader;

  DancingLinkNode()
  {
    isHeader = false;
    row = column = color = -1;
    up = down = left = right = colHeader = NULL;
  }
  DancingLinkNode(int r, int col, int nodeColor)
  {
    isHeader = false;
    row = r;
    column = col;
    color = nodeColor;
    up = down = left = right = colHeader = NULL;
  }
};

class SudokuExactCovering
{
public:
  SudokuExactCovering();
  ~SudokuExactCovering();

  bool createBasicSudokuDancingLinksTableau(); // retorna se foi possível iniciar os nós do dancing links

  bool addNewColumn(DancingLinkNode *columnNode); // adicionar às colunas existentes

  std::stack<DancingLinkNode> *findSolutionsFromFilename(const char *filename);

private:
  void deleteDancingLinksStructure();

  DancingLinkNode *headerNode; // header dos headers

  std::stack<DancingLinkNode> *temporarySolution;
  bool isSolved;

  bool isEmpty();

  void unlinkLaterallyNode(DancingLinkNode *node);
  void unlinkVerticallyNode(DancingLinkNode *node);
  void coverRowsFromNode(DancingLinkNode *node);
  void cover(DancingLinkNode *node); // considera coberto todas colunas do nó e desconecta lateralmente

  void relinkLaterallyNode(DancingLinkNode *node);
  void relinkVerticallyNode(DancingLinkNode *node);
  void uncoverRowsFromNode(DancingLinkNode *node);
  void uncover(DancingLinkNode *node); // desconsidera e relinka

  DancingLinkNode *findNode(DancingLinkNode *find);

  bool performAlgorithmX();
  /* Algoritmo X:
          vazio -> termina
          escolhe coluna col com menos 1's
          se numZeros(col) == 0 retorna falha
          pra cada linha na col:
            tmp += linha
            matrizReduzida := cobre linha
            se algoritmoX(matrizReduzida) == falha:
              retorna falha
              descobre linha, tmp -= linha
            senão retorna ok e a tmp

  */

  int countNonZeroesOnColumn(DancingLinkNode *column);
  DancingLinkNode *chooseLesserNumberOfOnesColumn();

  DancingLinkNode *setDancingLinkPositionColored(int i, int j, int sudokuPositionColor);
  void create4ConstraintsTableau(DancingLinkNode *exactCoverTableauBase[MAX_ROWS][MAX_COLS]);
  bool linkConstraints(DancingLinkNode *exactCoveringTableau[MAX_ROWS][MAX_COLS]);
};