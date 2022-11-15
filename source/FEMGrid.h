#pragma once

#include "utils.hpp"


// Typedefs
using ID = uint;

template<typename T> using Array = std::vector<T>;
template<typename T> using Matrix = std::vector<std::vector<T>>;

using Element = Array<ID>;
using Contour = Array<ID>;
using Function3D = std::function<T(Vec3)>;

//Container for necessary calculations and further data export in txt file
struct GridFunction {
	Array<T> _values;
	Array<Vec3> _element_grads;
	Array<T> _element_integrals;
	Array<Vec3> _vertex_grads;
	Array<T> _vertex_integrals;

	uint _number_of_elements, _number_of_vertices;

	GridFunction(uint elems = 0, uint vertices = 0):_number_of_elements(elems), _number_of_vertices(vertices){
		_values.reserve(_number_of_vertices);
		_element_grads.reserve(_number_of_elements);
		_element_integrals.reserve(_number_of_elements);
		_vertex_grads.reserve(_number_of_vertices);
		//_vertices_uintegrals.reserve(_number_of_vertices);
	};

	GridFunction(GridFunction& other) :_number_of_elements(other._number_of_elements),
									   _number_of_vertices(other._number_of_vertices) {
		_values.reserve(_number_of_vertices);
		_element_grads.reserve(_number_of_elements);
		_element_integrals.reserve(_number_of_elements);
		_vertex_grads.reserve(_number_of_vertices);
		//_vertices_uintegrals.reserve(_number_of_vertices);
	};

	void info() {
		std::cout
			<< "\n"
			<< "--------< GridFunction >--------" << "\n"
			<< "_values size: "			  << _values.size() << "\n"
			<< "_element_grads size: "      << _element_grads.size() << "\n"
			<< "_elements_uintegrals size: " << _element_integrals.size() << "\n"
			<< "_vertex_grads size: "      << _vertex_grads.size() << "\n"
			<< "_vertices_uintegrals size: " << _vertex_integrals.size() << "\n"
			<< "--------------------------------" << "\n";
	}
};


class FEMGrid {
public:
	// Necessary data
	Array<Vec3>    _vertices;
	Array<Element> _elements;
	Array<Contour> _contours;
	GridFunction  _grid_function;

	// Metadata
	Array<Vec3>    _centroids; // centroids of elements, ASSERT(_centroids.size() == _elements.size())

private:
	
	void _setup_centroids();

public:

	// # 2-pouint region contructor #
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
		const Vec3 &inp_pouintA, const Vec3 &inp_pouintB,
		uint inp_NE, uint type
	);

	// # 4-pouint region contructor #
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
		const Vec3& inp_pouintA, const Vec3& inp_pouintB, const Vec3& inp_pouintC, const Vec3& inp_pouintD,
		uint inp_NE1, uint inp_NE2, uint type
	);

	void setup_grid_function(Function3D f);

	// Export
	void export_all(const std::string &filename) const;

	void export_grid(const std::string &filename) const;
	void export_grid_function_values(const std::string &filename) const;
	void export_grid_function_vertex_grads(const std::string &filename) const;
	void export_grid_function_element_grads(const std::string &filename) const;
	void export_grid_function_vertex_integrals(const std::string &filename) const;
	void export_grid_function_element_integrals(const std::string &filename) const;

	// Getters (geometry)
	Array<ID> get_elements_adjacent_to_vertex(ID vertex_id) const;
	Array<ID> get_vertices_adjacent_to_vertex(ID vertex_id) const;

	// Getters (calculations)
	void setup_grad_at_vertices();
	void setup_grad_at_elements();

	void setup_integral_at_vertices();
	void setup_integral_at_elements();

	void compute_all(Function3D f);
};

template<typename Val>
inline Array<Val> operator/(Array<Val> arr, Val val) {
	Array<Val> res = arr;
	for (uint i = 0; i < arr.size(); ++i) res[i] /= val;
	return res;
}