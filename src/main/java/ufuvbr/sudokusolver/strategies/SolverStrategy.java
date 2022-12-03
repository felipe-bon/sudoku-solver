package ufuvbr.sudokusolver.strategies;

import ufuvbr.sudokusolver.SudokuGame;

import java.util.ArrayList;

public interface SolverStrategy {
    ArrayList<Integer> solve(SudokuGame sudokuGame);
}
