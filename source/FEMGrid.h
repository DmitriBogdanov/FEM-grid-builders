#pragma once

#include "utils.hpp"


// Typedefs
using ID = uint;

template<typename T> using Array = std::vector<T>;

using Element = Array<ID>;
using Contour = Array<ID>;

class FEMGrid {
public:
	// Necessary data
	Array<Vec3>    _vertices;
	Array<Element> _elements;
	Array<Contour> _contours;

	// Metadata
	Array<Vec3>    _centroids; // centroids of elements, ASSERT(_centroids.size() == _elements.size())

private:
	
	void _setup_centroids();

public:

	// # 2-point region contructor #
	//  Region - Line in 3D space:
	//    A-------------------------------B
	//
	//  Type (1) elements:
	//    Linear elements
	//    A-------0-------0-------0-------B
	//
	//  Type (2) elements:
	//    Quadratic elements
	//    A---*---0---*---0---*---0---*---B
	//
	void construct_grid_2(
		const Vec3 &inp_pointA, const Vec3 &inp_pointB,
		uint inp_NE, uint type
	);

	// # 4-point region contructor #
	//  Region - 2nd order surface in 3D space:
	//    D-----0-----0-----0-----C
	//    |                       |
	//    |                       |
	//    |                       |
	//    |                       |
	//    |                       |
	//    |                       |
	//    |                       |
	//    A-----0-----0-----0-----B
	//
	//  Type (1) elements:
	//    Triangular elements ver 1.
	//    D-----0-----0-----0-----C
	//    |     |     |     |     |
	//    |     |     |     |     |
	//    |     |     |     |     |
	//    0-----0-----0-----0-----0
	//    |     |     |     |     |
	//    |     |     |     |     |
	//    |     |     |     |     |
	//    A-----0-----0-----0-----B
	//
	//  Type (2) elements:
	//    Triangular elements ver 1.
	//    D-----0-----0-----0-----C
	//    |   / |   / |   / |   / |
	//    |  /  |  /  |  /  |  /  |
	//    | /   | /   | /   | /   |
	//    0-----0-----0-----0-----0
	//    |   / |   / |   / |   / |
	//    |  /  |  /  |  /  |  /  |
	//    | /   | /   | /   | /   |
	//    A-----0-----0-----0-----B
	//
	//  Type (3) elements:
	//    Triangular elements ver 2.
	//    D-----0-----0-----0-----C
	//    | \   | \   | \   | \   |
	//    |  \  |  \  |  \  |  \  |
	//    |   \ |   \ |   \ |   \ |
	//    0-----0-----0-----0-----0
	//    | \   | \   | \   | \   |
	//    |  \  |  \  |  \  |  \  |
	//    |   \ |   \ |   \ |   \ |
	//    A-----0-----0-----0-----B
	//
	//  Type (4) elements:
	//    Triangular elements ver 3.
	//    D-----0-----0-----0-----C
	//    | \ / | \ / | \ / | \ / |
	//    |  0  |  0  |  0  |  0  |
	//    | / \ | / \ | / \ | / \ |
	//    0-----0-----0-----0-----0
	//    | \ / | \ / | \ / | \ / |
	//    |  0  |  0  |  0  |  0  |
	//    | / \ | / \ | / \ | / \ |
	//    A-----0-----0-----0-----B
	//
	void construct_grid_4(
		const Vec3& inp_pointA, const Vec3& inp_pointB, const Vec3& inp_pointC, const Vec3& inp_pointD,
		uint inp_NE1, uint inp_NE2, uint type
	);

	void save_to_file(const std::string &filename);

	// Getters (geometry)
	Array<ID> get_elements_adjacent_to_vertex(ID vertex_id) const;
	Array<ID> get_vertices_adjacent_to_vertex(ID vertex_id) const;

	// Getters (computation)
	Vec3 get_grad_at_vertex(ID vertex_id) const;
	Vec3 get_grad_at_element(ID element_id) const;

	T get_integral_at_vertex(ID vertex_id) const;
	T get_integral_at_element(ID element_id) const;
};