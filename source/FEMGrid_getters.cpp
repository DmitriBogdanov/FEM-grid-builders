#include "FEMGrid.h"

#include <fstream>


void FEMGrid::export_all(const std::string &filename) const {
	const std::string file_extension = ".txt";

	this->export_grid(                           filename + "[grid]"                       + file_extension);
	this->export_grid_function_values(           filename + "[function_values]"            + file_extension);
	this->export_grid_function_vertex_grads(     filename + "[function_vertex_grads]"      + file_extension);
	this->export_grid_function_vertex_integrals( filename + "[function_vertex_integrals]"  + file_extension);
	this->export_grid_function_element_grads(    filename + "[function_element_grads]"     + file_extension);
	this->export_grid_function_element_integrals(filename + "[function_element_integrals]" + file_extension);
}

void FEMGrid::export_grid(const std::string &filename) const {

	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	// Write "NE, NP, NC"
	const uint NE = _elements.size();
	const uint NP = _vertices.size();
	const uint NC = _contours.size();

	outFile
		<< ' ' << NE
		<< ' ' << NP
		<< ' ' << NC
		<< '\n';

	// Write elements "NE_j ENP_j <vertex ids>
	for (ID element_id = 0; element_id < NE; ++element_id) {
		const auto &element = _elements[element_id];

		outFile
			<< ' ' << element_id
			<< ' ' << element.size();

		for (const auto &vertex_id : element) outFile << ' ' << vertex_id;

		outFile
			<< '\n';
	}

	// Write vertices "PN_j, x, y, z"
	for (ID vertex_id = 0; vertex_id < NP; ++vertex_id) {
		const auto &vertex = _vertices[vertex_id];

		outFile
			<< ' ' << vertex_id
			<< ' ' << vertex.x
			<< ' ' << vertex.y
			<< ' ' << vertex.z
			<< '\n';
	}
	
	/// Horrible style IMO, contours can be written in the same format as elements
	// Write contour sizes "CPN_1, ... , CPN_NC"
	for (ID contour_id = 0; contour_id < NC; ++contour_id) {
		outFile
			<< ' ' << _contours[contour_id].size();
	}

	// Write contour points "CP_1, ... , CP_CPN_j" for all contours
	for (ID contour_id = 0; contour_id < NC; ++contour_id) {
		const auto &contour = _contours[contour_id];

		for (const auto &vertex_id : contour) outFile << '\n' << ' ' << vertex_id;
	}
}

void FEMGrid::export_grid_function_values(const std::string &filename) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	for (const auto &value : _grid_function._values) outFile << value << '\n';
}

void FEMGrid::export_grid_function_vertex_grads(const std::string &filename) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	for (const auto &value : _grid_function._vertex_grads) outFile << value.toString() << '\n';
}

void FEMGrid::export_grid_function_element_grads(const std::string &filename) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	for (const auto &value : _grid_function._element_grads) outFile << value.toString() << '\n';
}

void FEMGrid::export_grid_function_vertex_integrals(const std::string &filename) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	for (const auto &value : _grid_function._vertex_integrals) outFile << value << '\n';
}

void FEMGrid::export_grid_function_element_integrals(const std::string &filename) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) exit_with_error("File creation failed");

	for (const auto &value : _grid_function._element_integrals) outFile << value << '\n';
}



Array<ID> FEMGrid::get_elements_adjacent_to_vertex(ID vertex_id) const {
	Array<ID> adjacent_elements;

	for (ID element_id = 0; element_id < _elements.size(); ++element_id) {
		const auto &element = _elements[element_id];

		if (find_value_in_array(element, vertex_id)) adjacent_elements.push_back(element_id);
	}

	return adjacent_elements;
}

Array<ID> FEMGrid::get_vertices_adjacent_to_vertex(ID vertex_id) const {
	Array<ID> adjacent_vertices;

	for (ID element_id = 0; element_id < _elements.size(); ++element_id) {
		const auto &element = _elements[element_id];
		
		// Element contains vertex => add 2 vertices to left/right to 'adjacent_vertices'
		if (const auto optional = find_value_in_array(element, vertex_id)) {
			const ID index_in_element = static_cast<ID>(optional.value());

			const ID vertex_to_left =
				index_in_element > 0
				? element[index_in_element - 1]
				: element.back(); // 'wrap around' logic for vector bounds

			const ID vertex_to_right =
				index_in_element < element.size() - 1
				? element[index_in_element + 1]
				: element.front(); // 'wrap around' logic for vector bounds

			// Since multiple elements can have the same edge, we have to check
			// that new vertices aren't already accounted for
			if (!find_value_in_array(adjacent_vertices, vertex_to_left))
				adjacent_vertices.push_back(vertex_to_left);

			if (!find_value_in_array(adjacent_vertices, vertex_to_right))
				adjacent_vertices.push_back(vertex_to_right);
		}
	}

	return adjacent_vertices;
}