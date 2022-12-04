package ufuvbr.sudokusolver.strategies;

import ufuvbr.sudokusolver.SudokuGame;
import ufuvbr.sudokusolver.graphs.adjacencylist.Graph;

import java.util.ArrayList;

public interface SolverStrategy {
    Graph solve();
}