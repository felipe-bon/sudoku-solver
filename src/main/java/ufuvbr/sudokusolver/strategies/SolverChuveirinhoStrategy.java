package ufuvbr.sudokusolver.strategies;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import ufuvbr.sudokusolver.SudokuGame;
import ufuvbr.sudokusolver.graphs.adjacencylist.Graph;
import ufuvbr.sudokusolver.graphs.adjacencylist.GraphSudokuVertex;

import java.util.ArrayList;

@Getter
@Setter
@AllArgsConstructor
public class SolverChuveirinhoStrategy implements SolverStrategy {
    private SudokuGame sudokuGame;

    private int getVerticalSubgrid(int v) {
        return v / this.getSudokuGame().getLineSize() * this.getSudokuGame().getSubgridsPerColumn();
    }

    private int getHorizontalSubgrid(int v) {
        return (v % this.getSudokuGame().getLineSize()) % this.getSudokuGame().getSubgridsPerLine();
    }

    private boolean sameVerticalSubgrid(int v1, int v2) {
        return getVerticalSubgrid(v1) == getVerticalSubgrid(v2);
    }

    private boolean sameHorizontalSubgrid(int v1, int v2) {
        return getHorizontalSubgrid(v1) == getHorizontalSubgrid(v2);
    }

    private boolean sameSubgrid(int v1, int v2) {
        return sameVerticalSubgrid(v1, v2) && sameHorizontalSubgrid(v1, v2);
    }

    private boolean sameLine(int v1, int v2) {
        return v1 / sudokuGame.getLineSize() == v2 / sudokuGame.getLineSize();
    }

    private boolean sameColumn(int v1, int v2) {
        return v1 % sudokuGame.getLineSize() == v2 % sudokuGame.getLineSize();
    }

    private boolean isAdjacentToV1(int v1, int v2) {
        return sameLine(v1, v2) || sameColumn(v1, v2) || sameSubgrid(v1, v2);
    }

    private Graph makeChuveirinho() {
        ArrayList<GraphSudokuVertex> allVertices = new ArrayList<>();

        // creating all vertices
        for (int i = 0; i < sudokuGame.maxI(); i++) {
            allVertices.add(GraphSudokuVertex.builder()
                    .position(i)
                    .color(sudokuGame.getColorings().get(i))
                    .build());
        }

        allVertices.forEach(graphSudokuVertex ->
                graphSudokuVertex.setAdjacentVertices(
                        allVertices.stream()
                                .filter(possibleAdjacentVertex -> isAdjacentToV1(
                                        graphSudokuVertex.getPosition(),
                                        possibleAdjacentVertex.getPosition())).toList()));

        return Graph.builder()
                .adjacencyList(allVertices)
                .build();
    }

    @Override
    public Graph solve() {
        Graph chuveirinho = makeChuveirinho();

        chuveirinho.getAdjacencyList().forEach(graphSudokuVertex -> graphSudokuVertex.setColor(graphSudokuVertex.getColor() != null ? graphSudokuVertex.getColor() : 0));

        return chuveirinho;
    }
}
