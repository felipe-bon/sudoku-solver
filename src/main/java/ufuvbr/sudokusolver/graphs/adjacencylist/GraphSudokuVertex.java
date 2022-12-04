package ufuvbr.sudokusolver.graphs.adjacencylist;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Setter
@Getter
@Builder
@AllArgsConstructor
public class GraphSudokuVertex {
    private Integer position;
    private Integer color;
    private List<GraphSudokuVertex> adjacentVertices;
}
