package ufuvbr.sudokusolver;

import ufuvbr.sudokusolver.strategies.SolverChuveirinhoStrategy;

public class Main {
    public static void main(String[] args) {
        SudokuGame sudokuGame =  SudokuGameSimpleFactory.createSudoku(SolverChuveirinhoStrategy.class);
        System.out.println(sudokuGame);
        System.out.println(sudokuGame.solve().toString());
    }
}