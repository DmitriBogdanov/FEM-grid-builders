#include "FEMGrid.h"


// Sizes
uint build_NE(uint type, uint inp_NE1, uint inp_NE2) {
	switch (type) {
	case 1: return 1 * inp_NE1 * inp_NE2;
	case 2: return 2 * inp_NE1 * inp_NE2;
	case 3: return 2 * inp_NE1 * inp_NE2;
	case 4: return 4 * inp_NE1 * inp_NE2;
	default: exit_with_error("Unknown element type"); return -1;
	}
}

uint build_NP(uint type, uint inp_NE1, uint inp_NE2) {
	return
		type == 4
		? (inp_NE1 + 1) * (inp_NE2 + 1) + inp_NE1 * inp_NE2
		: (inp_NE1 + 1) * (inp_NE2 + 1);
}


// Elements
void build_elements_type_1(Array<Element> &elements, uint NP1, uint NP2, uint NE1, uint NE2) {
	for (uint i = 0; i < NE2; ++i)
		for (uint j = 0; j < NE1; ++j)
			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1,
				i * NP1 + j + 1 + NP1,
				i * NP1 + j + 1 + NP1 - 1
			});
}

void build_elements_type_2(Array<Element> &elements, uint NP1, uint NP2, uint NE1, uint NE2) {
	for (uint i = 0; i < NE2; ++i)
		for (uint j = 0; j < NE1; ++j) {
			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1 + NP1,
				i * NP1 + j + 1 + NP1 - 1
			});

			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1,
				i * NP1 + j + 1 + NP1
			});
		}
}

void build_elements_type_3(Array<Element> &elements, uint NP1, uint NP2, uint NE1, uint NE2) {
	for (uint i = 0; i < NE2; ++i)
		for (uint j = 0; j < NE1; ++j) {
			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1,
				i * NP1 + j + 1 + NP1 - 1
			});

			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1 + NP1,
				i * NP1 + j + 1 + NP1 - 1
			});
		}
}

void build_elements_type_4(Array<Element> &elements, uint NP1, uint NP2, uint NE1, uint NE2) {
	uint centerCounter = 0;

	for (uint i = 0; i < NE2; ++i)
		for (uint j = 0; j < NE1; ++j) {
			// bottom element
			elements.push_back({
				i * NP1 + j,
				i * NP1 + j + 1,
				NP1 * NP2 + centerCounter
			});
			// right element
			elements.push_back({
				i * NP1 + j + 1,
				i * NP1 + j + 1 + NP1,
				NP1 * NP2 + centerCounter
			});
			// top element
			elements.push_back({
				i * NP1 + j + 1 + NP1 - 1,
				i * NP1 + j + 1 + NP1,
				NP1 * NP2 + centerCounter
			});
			// left element
			elements.push_back({
				i * NP1 + j + 1 + NP1 - 1,
				i * NP1 + j,
				NP1 * NP2 + centerCounter
			});

			++centerCounter;
		}
}


// Constructor (4 points)
void FEMGrid::construct_grid_4(
	const Vec3& inp_pointA, const Vec3& inp_pointB, const Vec3& inp_pointC, const Vec3& inp_pointD,
	uint inp_NE1, uint inp_NE2, uint type
) {
	// NE, NP, NC
	const uint NE = build_NE(type, inp_NE1, inp_NE2); // Number of elements
	const uint NP = build_NP(type, inp_NE1, inp_NE2); // Number of vertices
	const uint NC = 1;                               // Number of contours

	_elements.reserve(NE);
	_vertices.reserve(NP);
	_contours.reserve(NC);

	// Elements
	const uint NE1 = inp_NE1;
	const uint NE2 = inp_NE2;
	const uint NP1 = inp_NE1 + 1;
	const uint NP2 = inp_NE2 + 1;

	switch (type) {
	case 1: build_elements_type_1(_elements, NP1, NP2, NE1, NE2); break;
	case 2: build_elements_type_2(_elements, NP1, NP2, NE1, NE2); break;
	case 3: build_elements_type_3(_elements, NP1, NP2, NE1, NE2); break;
	case 4: build_elements_type_4(_elements, NP1, NP2, NE1, NE2); break;
	default: exit_with_error("Unknown element type");
	}

	// Vertices
	// Compute and write coords of grid points
	for (uint j = 0; j < NP2; ++j)
		for (uint i = 0; i < NP1; ++i) {
			// Point in local coords
			const double xi = static_cast<T>(i) / (NP1 - 1);
			const double nu = static_cast<T>(j) / (NP2 - 1);

			// Point in global coords
			const double weightA = (1. - xi) * (1. - nu);
			const double weightB = xi * (1. - nu);
			const double weightC = xi * nu;
			const double weightD = (1. - xi) * nu;

			_vertices.push_back(
				inp_pointA * weightA +
				inp_pointB * weightB +
				inp_pointC * weightC +
				inp_pointD * weightD
			);
		}

	if (type == 4) {
		for (uint j = 0; j < NP2 - 1; ++j)
			for (uint i = 0; i < NP1 - 1; ++i) {
				// Point in local coords
				const double xi = static_cast<T>(i + 0.5) / NE1;
				const double nu = static_cast<T>(j + 0.5) / NE2;

				// Point in global coords
				const double weightA = (1. - xi) * (1. - nu);
				const double weightB = xi * (1. - nu);
				const double weightC = xi * nu;
				const double weightD = (1. - xi) * nu;

				_vertices.push_back(
					inp_pointA * weightA +
					inp_pointB * weightB +
					inp_pointC * weightC +
					inp_pointD * weightD
				);
			}
	}

	// Contours (1 in current case)
	Contour contour;

	contour.reserve(2 * NP1 + 2 * (NP2 - 2));

	// Bottom
	for (uint i = 0; i < NP1; ++i) contour.push_back(NP1 * 0 + i);
	// Right
	for (uint j = 1; j < NP2 - 1; ++j) contour.push_back(NP1 * j + NP1 - 1);
	// Top
	for (uint i = 0; i < NP1; ++i) contour.push_back(NP1 * NP2 - i - 1);
	// Left
	for (uint j = 1; j < NP2 - 1; ++j) contour.push_back(NP1 * (NP2 - j - 1));

	_contours.push_back(std::move(contour));

	// Metadata
	this->_setup_centroids();
}