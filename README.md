# Projeto-DA-2

This project aims to analyse the Travelling Salesperson Problem (TSP) and design heuristics to solve it, using several datasets from the context of ocean shipping and urban deliveries. 

---------------

## Note
Due to their large size, and potentially storage issues, the real-world graphs are not fully connected.
As such, and only whenever you need to determine the distance between two nodes whose edge is not
provided, you may use the geographic latitude and longitude distance to determine “on demand” the distance between two nodes and assume they are therefore connected. You will get a tour that is not “real”
in the sense that the edges it is based on do not necessarily exist, but at least you guarantee the 2-
approximation bound. In order to compute the distances between nodes, you need to use the Haversine
distance computation described in appendix A.

-----------------------

## T1.1 (1 point)
- [ ] Create a simple interface menu exposing all the implemented functionalities in a user-friendly interface 

## T1.2 (1 point)
- [x] Develop basic functionality to load and parse the provided dataset files.
- [ ] Accessible through the menu, enables the selection of the dataset to be used in the analysis 
of the algorithms developed.
- [ ] Create one (or more) appropriate graphs upon which you will carry out the requested tasks.

## T1.3 (2 points)
- [ ] Include documentation for all code implemented in this project, using Doxygen, indicating the corresponding time complexity for each algorithm implemented.

## Backtracking Algorithm - T2.1 (4 points)
- [x] Develop a backtracking algorithmic approach to the TSP for a graph starting and ending the node tour on node labelled with the zero-identifier label
- [x] You are expected to use the small graphs to validate this approach and to observe that for the larger graphs this approach is not really feasible.
- [ ] To this extent, you are suggested to plot the execution time (or other performance metrics you find significant) to illustrate the feasibility or not of this approach for larger graphs.

## Triangular Approximation Heuristic - T2.2 (4 points)
- [ ] Use the geographic node data, and implement the approximation algorithm for TSP that relies on the triangular inequality to ensure a 2-approximation algorithm for this problem again starting and ending the node tour on node with the zero-identifier label
- [ ] Compare with the backtracking algorithm for the same small graphs.

## Other Heuristics - T2.3 (6 points)
- [ ] Develop your own “efficient” heuristic for TSP that can leverage, or not, the geographic node data.  The emphasis in this approach should be on efficiency as this algorithm should be feasible even for the large graphs.
- [ ] Make use of several algorithmic techniques:
- [ ] Divide-and-conquer to split the graph into multiple geographic sections
- [ ] Use of clustering
- [ ] Or both, possibly even in combination with the 2-approximation algorithm.
- [ ] Note though, that in this algorithm the tour has to rely exclusively on “real” or existing edges and cannot be “approximated” as you possibly have done in the 2-approximation algorithm. Nevertheless, you may use the “non-real” approximation solution as a basis for your heuristic.
- [ ] Compare the quality and run-time performance of your heuristic solution against the 2-approximation algorithm (if you do not rely on it).
- [ ] Although possible, you are not expected to present multiple heuristics, but rather a heuristic that works well over the basic 2- approximation or one that offers comparable tour length results but with noticeably faster execution time (i.e., time complexity).

## Demonstration & Presentation - T4.1 (2 points)
- [ ] Prepare a presentation of your work with the main conclusions about your implementation of the TSP applied to the scenario of urban deliveries.
- [ ] Your presentation should focus on the explanation and analysis of the heuristics developed for the graphs represented in the dataset, using illustrative examples
- [ ] In addition to the rationale of your heuristics, you should discuss which heuristics are more adequate to a given graph in the dataset. In this discussion, you should also analyse the trade-offs between the efficiency and the optimality of your solution for all graphs provided in the datasets. The optimality of your heuristics can be analysed by comparing their results with the results produced by the backtracking algorithm
- [ ] In addition to the heuristics, your presentation should also explain the implemented backtracking algorithm for the toy example graphs.

------

### Class Notes
- Calcular desvio padrão para provar distâncias equivalentes e utilizar triangular approach no 3 exercicio
- Adicionar opção de escolher o ficheiro para abrir.
- Explicar o que o n significa no doxygen

### Developed by 🧑🏻‍💻

- **Tiago Cruz** - [@Tiago27Cruz](https://www.github.com/Tiago27Cruz)
- **João Lourenço** - [@Tonevanda](https://www.github.com/Tonevanda)
- **Tomás Xavier** - [@dratomitoma](https://www.github.com/dratomitoma)
