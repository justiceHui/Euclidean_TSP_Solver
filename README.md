# Euclidean-TSP-Solver

* O(N log N) 2-Approximation Euclidean TSP Solver
* This code using Delaunay Triangulation and Euclidean MST. Worst time complexity is O(N log N)

### Content
* [Constraint](https://github.com/justiceHui/Euclidean_TSP_Solver#constraint)
* **[FunctionFormat](https://github.com/justiceHui/Euclidean_TSP_Solver#function-format)**
* **[Known Issues](https://github.com/justiceHui/Euclidean_TSP_Solver#known-issues)**
* [Special thanks to](https://github.com/justiceHui/Euclidean_TSP_Solver#special-thanks-to)

### Constraint
See `Triangulation::triangulate` Function Format

### Function Format
> Reading `main.cpp` can be helpful to know about function format.
>
> `using T = long double;`

* `std::pair<T, std::vector<int>> EuclideanTSP::euclideanTSP(std::vector<std::pair<T, T>> v, int root)`
    * get 2-Approximation Euclidean TSP Order
    * Time : O(N log N)
    * Input : EuclideanTSP::euclideanTSP({{X0, Y0}, {X1, Y1}, ...}, StartPoint)
    * Output : {TotalDistance, {P0, P1, ..., P0}}
* `std::vector<Edge> EuclideanMST::euclideanMST(std::vector<std::pair<T, T>> v)`
    * get Euclidean MST using Delaunay Triangulation
    * Time : O(N log N)
    * Input : EuclideanMST::euclideanMST({{X0, Y0}, {X1, Y1}, ...})
    * Output : MST Edge List
* `std::vector<std::array<std::pair<T, T>, 3>> Triangulation::triangulate(std::vector<std::pair<T, T>> pts)`
    * get Delaunay Triangulation
    * Time : O(N log N)
    * There must be no duplicate points.
    * If all points are on a line, no triangles will be returned.
    * Input : Triangulation::triangulate({{X0, Y0}, {X1, Y1}, ...})
    * Output : Returns triangles, all points in triangle are counter-clockwise.

### Known Issues
* floating point precision issue
* memory leak issue

### Special thanks to
* [kactl/FastDelaunay.h](https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/FastDelaunay.h)
* [bqi343/DelaunayFast.h](https://github.com/bqi343/USACO/blob/master/Implementations/content/geometry%20(13)/Misc/DelaunayFast.h)
* [zigui-ps/VoronoiDiagram](https://github.com/zigui-ps/VoronoiDiagram)