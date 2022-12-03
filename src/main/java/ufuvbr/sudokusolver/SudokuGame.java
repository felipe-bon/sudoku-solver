package ufuvbr.sudokusolver;

import lombok.*;
import ufuvbr.sudokusolver.strategies.SolverStrategy;

import java.util.ArrayList;

@Setter
@Getter
@AllArgsConstructor
@Builder
public class SudokuGame implements SolverStrategy {
    private ArrayList<Integer> colorings;
    private SolverStrategy solverStrategy;

    @Override
    public ArrayList<Integer> solve(SudokuGame sudokuGame) {
        return solverStrategy.solve(this);
    }

    @Override
    public String toString() {
        StringBuilder sudokuGrids = new StringBuilder();
        for (int line = 0; line < 9; line++) {
            for (int subgrid = 0; subgrid < 3; subgrid++) {
                for (int subgridElement = 0; subgridElement < 3; subgridElement++) {
                    Integer colorOfPosition = colorings.get(line * 9 + subgrid * 3 + subgridElement);
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
