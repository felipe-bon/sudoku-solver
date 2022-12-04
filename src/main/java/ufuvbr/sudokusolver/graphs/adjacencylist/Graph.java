package ufuvbr.sudokusolver.graphs.adjacencylist;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Builder
@Getter
@Setter
@AllArgsConstructor
public class Graph {
    private List<GraphSudokuVertex> adjacencyList;
}
