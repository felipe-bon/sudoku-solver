package ufuvbr.sudokusolver;

import lombok.*;
import ufuvbr.sudokusolver.graphs.adjacencylist.Graph;
import ufuvbr.sudokusolver.strategies.SolverStrategy;

import java.util.ArrayList;

@Setter
@Getter
@AllArgsConstructor
@Builder
public class SudokuGame {
    private ArrayList<Integer> colorings;
    private SolverStrategy solverStrategy;
    @Builder.Default
    private int lines = 9;
    @Builder.Default
    private int subgridsPerLine = 3;
    @Builder.Default
    private int subgridsPerColumn = 3;
    @Builder.Default
    private int elementsPerLineOfSubgrid = 3;

    public int getLineSize() { return this.subgridsPerLine * this.elementsPerLineOfSubgrid; }
    public int maxI() {
        return this.lines * (this.subgridsPerLine * this.elementsPerLineOfSubgrid);
    }

    public SudokuGame solve() {
        Graph solvedSudokuGraphColoring = solverStrategy.solve();
        return SudokuGameSimpleFactory.createSudoku(solvedSudokuGraphColoring);
    }

    @Override
    public String toString() {
        StringBuilder sudokuGrids = new StringBuilder();
        for (int line = 0; line < lines; line++) {
            for (int subgrid = 0; subgrid < subgridsPerLine; subgrid++) {
                for (int subgridElement = 0; subgridElement < elementsPerLineOfSubgrid; subgridElement++) {
                    Integer colorOfPosition = colorings.get(line * this.lines + subgrid * this.subgridsPerLine + subgridElement);
                    sudokuGrids.append(" ");
                    sudokuGrids.append(colorOfPosition != null ? colorOfPosition : " ");
                    sudokuGrids.append(" ");
                }
                if (subgrid != 2) sudokuGrids.append("|");
            }
            sudokuGrids.append("\n");
            if ((line + 1) % 3 == 0 && line != 8) sudokuGrids.append("------------------------------\n");
        }
        return sudokuGrids.toString();
    }
}
