package ufuvbr.sudokusolver;

import ufuvbr.sudokusolver.strategies.SolverChuverinhoStrategy;

public class Main {
    public static void main(String[] args) {
        System.out.println(SudokuGameSimpleFactory.createSudoku(SolverChuverinhoStrategy.class).toString());
    }
}