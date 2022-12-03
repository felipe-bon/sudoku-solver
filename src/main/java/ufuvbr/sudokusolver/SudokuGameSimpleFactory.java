package ufuvbr.sudokusolver;

import ufuvbr.sudokusolver.strategies.SolverChuverinhoStrategy;
import ufuvbr.sudokusolver.strategies.SolverStrategy;

import java.util.ArrayList;

public class SudokuGameSimpleFactory {
    public static ArrayList<Integer> makeRandomColoring() {
        ArrayList<Integer> coloring = new ArrayList<>();
        for (int i = 0; i < 81; i++) {
            coloring.add(null);
        }
        return coloring;
    }
    public static SudokuGame createSudoku(Class<? extends SolverStrategy> solverStrategyClass) {
        if (SolverChuverinhoStrategy.class.equals(solverStrategyClass)) {
            return SudokuGame
                    .builder()
                    .colorings(makeRandomColoring())
                    .solverStrategy(new SolverChuverinhoStrategy())
                    .build();
        }

        throw new IllegalArgumentException("Missing Solver Strategy Class");
    }
}
