![C++](https://img.shields.io/badge/C++-std=17-blue.svg?style=flat&logo=cplusplus) <br>
# FEM (Finite Element Method) grid builder

Contains various grid builders for finite element method. Grid builders implemented in C++, visualization done through "Wolfram Mathematica" package.

2D triangular elements also support computation of grid function $f(x, y, z)$, its' integrals and gradients on each element. Same values can be obtained for vertices through averaging out adjacent elements, using areas as weights. For a "free" point outside of grid vertices such values are computed through barycentric coordinates inside the enclosing element.

## 1D grids

1D area - line defined by 2 points in space.

* Linear elements
<img src="images/example_points_2_type_1.png" width=40% height=40%>

* Quadratic elements

<img src="images/example_points_2_type_2.png" width=40% height=40%>

## 2D grids

2D area - 2nd order surface defined by 4 points in space. Following examples use flat rectangular regions to better demonstrate element geometry.

* Elements with quadrilateral base

<img src="images/example_points_4_type_1.png" width=40% height=40%>

* Elements with triangular base ver. 1

<img src="images/example_points_4_type_2.png" width=40% height=40%>

* Elements with triangular base ver. 2

<img src="images/example_points_4_type_3.png" width=40% height=40%>

* Elements with triangular base ver. 3

<img src="images/example_points_4_type_4.png" width=40% height=40%>

## Grid Function

Following example demonstrates visualization of function values and grads at grid vertices.

<img src="images/example_grid_function.png" width=40% height=40%>

## Usage

| Input file format                          |                                                                            |
|--------------------------------------------|----------------------------------------------------------------------------|
| NP                                         | Number of points defining the area (2 or 4) clockwise                      |
| x_1 y_1 z_1<br /> ...<br /> x_NP y_NP z_NP | Point coords                                                               |
| NE1 NE2                                    | Number of elements on a line (1 value for 2 points, 2 values for 4 points) |
| type                                       | Type of the element (for 2 point - 1 or 2, for 4 point - 1, 2, 3 or 4)     |

NOTE: By default both "main.cpp" and "Visualization.wl" look for files in the current folder.

| Output file format                                                                              |                                                                                               |
|-------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| NE NP NC                                                                                        | NE - number of elements,<br /> NP - number of point,<br /> NC - number of contours            |
| EN_1 ENP_1 EP_1 ... EP_ENP_1<br /> ...<br />EN_NE ENP_NE EP_1 ... EP_ENP_NE                     | EN - element id,<br /> ENP - number of vertices in the element,<br /> {EP} - element vertices |
| PN_1 x_1 y_1 z_1<br /> ...<br /> PN_NP x_NP y_NP z_NP                                           | PN - vertex id, {x, y, z} - vertex coords                                                     |
| CPN_1 CPN_NC<br /> CP_1<br /> ...<br /> CP_CPN_1<br /> ...<br /> CP_1<br /> ...<br /> CP_CPN_NC | CPN - number of vertices forming a contour,<br /> {CP} - contour vertices                     |

## Requirements

To launch "Visualization.wl" one may need an access to a valid Wolfram Mathematica license.

## Version History

* 01.06
    * Removed OpenMP parallelism due to bugs in order of operation that it caused

* 01.05
    * Added method for computing barycentric coordinates of a point
    * Added method that finds element containing given point
    * Added method that exports function value, integral and grad based on point coords

* 01.04
    * Added more safety checks

* 01.03
    * Implemented visualization of function function values, gradients and integrals on a grid
    * Cosmetic changes to output format

* 01.02
    * Implemented computation of function values, gradients and integrals at triangular elements
    * Implemented computation of function values, gradients and integrals at grid vertices through averaging out adjacent elements

* 01.01
    * Vastly changed code structure, instead of methods writing grids straight to files was implemented a general class that can build grids, hold their metadata, operate on them and save results to a file in the same format as before
    * Changed indexation to start from 0 instead of 1, so internal indixation is the same as displayed
    * Bug fixes related to new indexation
    * Added element centroids to stored metadata
    * Implemented methods for finding adjacent elements and vertices

* 00.05
    * Fixed an issue that caused incorrect enumeration of elements for different NE1 and NE2
    * Replaced Mathematica notebook with a package

* 00.04
    * Fixed an oversight that caused incorrect behaviour when 3rd point didn't belong to the same plane as others

* 00.03
    * Generalized method interface

* 00.02
    * Implemented 6 separate grid builders

* 00.01
    * Initial release

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
