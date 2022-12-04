package ufuvbr.sudokusolver;

import ufuvbr.sudokusolver.graphs.adjacencylist.Graph;
import ufuvbr.sudokusolver.graphs.adjacencylist.GraphSudokuVertex;
import ufuvbr.sudokusolver.strategies.SolverChuveirinhoStrategy;
import ufuvbr.sudokusolver.strategies.SolverStrategy;

import java.util.ArrayList;

public class SudokuGameSimpleFactory {
    public static ArrayList<Integer> makeRandomColoring() {
        ArrayList<Integer> coloring = new ArrayList<>();
        for (int i = 0; i < 81; i++) {
            coloring.add(null);
        }
        coloring.set(0, 5);
        coloring.set(1, 5);
        coloring.set(4, 7);
        coloring.set(9, 6);
        coloring.set(12, 1);
        coloring.set(13, 9);
        coloring.set(14, 5);
        coloring.set(19, 9);
        coloring.set(20, 8);
        coloring.set(25, 6);
        coloring.set(27, 8);
        coloring.set(31, 6);
        coloring.set(35, 3);
        coloring.set(36, 4);
        coloring.set(39, 8);
        coloring.set(41, 3);
        coloring.set(44, 1);
        coloring.set(45, 7);
        coloring.set(49, 2);
        coloring.set(53, 6);
        coloring.set(55, 6);
        coloring.set(60, 2);
        coloring.set(61, 8);
        coloring.set(66, 4);
        coloring.set(67, 1);
        coloring.set(68, 9);
        coloring.set(71, 5);
        coloring.set(76, 8);
        coloring.set(79, 7);
        coloring.set(80, 9);

        return coloring;
    }

    public static SudokuGame createSudoku(Graph graph) {
        return SudokuGame.builder()
                .colorings(new ArrayList<>(graph.getAdjacencyList().stream().map(GraphSudokuVertex::getColor).toList()))
                .build();
    }

    public static SudokuGame createSudoku(Class<? extends SolverStrategy> solverStrategyClass) {
        if (SolverChuveirinhoStrategy.class.equals(solverStrategyClass)) {
            SudokuGame sudokuGame = SudokuGame
                    .builder()
                    .colorings(makeRandomColoring())
                    .build();
            sudokuGame.setSolverStrategy(new SolverChuveirinhoStrategy(sudokuGame));
            return sudokuGame;
        }

        throw new IllegalArgumentException("Missing Solver Strategy Class");
    }
}
