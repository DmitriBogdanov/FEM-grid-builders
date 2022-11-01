#include "FEMGrid.h"


void FEMGrid::_setup_centroids() {
	_centroids.reserve(_elements.size());

	for (const auto &element : _elements) {
		Vec3 centroid = { 0, 0, 0 };

		const T inverseN = T(1) / element.size();
		for (const auto &vertex_id : element) centroid += _vertices[vertex_id] * inverseN;

		_centroids.push_back(std::move(centroid));
	}
}

// Elements
void build_elements_type_1(Array<Element> &elements, uint NE) {
	for (uint i = 0; i < NE; ++i)
		elements.push_back({
			i,
			i + 1
		});		
}

void build_elements_type_2(Array<Element> &elements, uint NE) {
	for (uint i = 0; i < NE; ++i)
		elements.push_back({
			2 * i,
			2 * i + 1,
			2 * i + 2
		});
}


// Constructor (2 points)
void FEMGrid::construct_grid_2(
	const Vec3 &inp_pointA, const Vec3 &inp_pointB,
	uint inp_NE, uint type
) {
	// E, NP, NC
	const uint NE = inp_NE;
	const uint NP = type * inp_NE + 1;
	const uint NC = 2;

	_elements.reserve(NE);
	_vertices.reserve(NP);
	_contours.reserve(NC);

	// Elements
	switch (type) {
	case 1: build_elements_type_1(_elements, NE); break;
	case 2: build_elements_type_2(_elements, NE); break;
	default: exit_with_error("Unknown element type");
	}

	// Vertices
	const Vec3 increment = (inp_pointB - inp_pointA) / (NP - 1);

	for (uint i = 0; i < NP; ++i) {
		// Point in local coords
		const double xi = static_cast<T>(i) / (NP - 1);

		// Point in global coords
		const double weightA = (1. - xi);
		const double weightB = xi;

		_vertices.push_back(
			inp_pointA * weightA +
			inp_pointB * weightB
		);
	}

	// Contours (2 in current case)
	_contours.push_back({ 0 });
	_contours.push_back({ NP - 1 });

	// Metadata
	this->_setup_centroids();
}