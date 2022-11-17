#include "FEMGrid.h"

#include <fstream>


// #####################
// ### Input parsing ###
// #####################
T func(Vec3 point) {
	return 10 + 5 * point.y * sin(2 * PI * point.x);
}

bool query_is_yes(const std::string &query){
	return
		query == "Yes"        || query == "yes"        ||
		query == "Indeed"     || query == "indeed"     ||
		query == "Absolutely" || query == "absolutely" ||
		query == "Definitely" || query == "definitely" ||
		query == "Ofc"        || query == "ofc"        ||
		query == "Of course"  || query == "of course"  ||
		query == "Si"         || query == "si"         ||
		query == "Da"         || query == "da"         ||
		query == "Jawohl"     || query == "jawohl";
}

int main() {
	// Set up OpenMP
	const int MAX_THREADS = omp_get_max_threads();
	omp_set_num_threads(MAX_THREADS);
	std::cout << ">>> OpenMP: " << MAX_THREADS << " threads detected and set\n\n";

	// Set up input file
	std::string inputFilename;
	std::cout << "Take input from -> ";
	std::cin >> inputFilename;

	std::cout << "\n";

	std::ifstream inFile(inputFilename + ".txt");
	if (!inFile.is_open()) exit_with_error("Could not open input file");

	// Config
	std::string	query;
	std::cout << "Output additional info? (Yes/No) -> ";
	std::cin >> query;

	std::cout << "\n>>> Input read:\n";

	// Read number of points (2 or 4)
	uint NP;
	inFile >> NP;

	if (NP == 2) {
		// Read 2 points forming a line
		Vec3 pointA, pointB;

		inFile >> pointA.x >> pointA.y >> pointA.z;
		inFile >> pointB.x >> pointB.y >> pointB.z;

		// Read number of elements
		uint NE;
		inFile >> NE;

		// Read type of the elements
		uint type;
		inFile >> type;

		std::cout
			<< "NP = " << NP << "\n"
			<< "pointA = " << pointA.toString() << "\n"
			<< "pointB = " << pointB.toString() << "\n"
			<< "NE = " << NE << "\n"
			<< "type = " << type << "\n\n"
			<< ">>> Building the grid..." << "\n";

		FEMGrid grid;

		grid.construct_grid_2(pointA, pointB, NE, type);
		grid.export_grid("output[grid].txt");

		std::cout << ">>> Done\n";
	}
	else if (NP == 4) {
		// Read 4 points forming a polygon
		Vec3 pointA, pointB, pointC, pointD;

		inFile >> pointA.x >> pointA.y >> pointA.z;
		inFile >> pointB.x >> pointB.y >> pointB.z;
		inFile >> pointC.x >> pointC.y >> pointC.z;
		inFile >> pointD.x >> pointD.y >> pointD.z;

		// Read number of elements
		uint NE1, NE2;
		inFile >> NE1 >> NE2;

		// Read type of the elements
		uint type;
		inFile >> type;

		std::cout
			<< "NP = " << NP << "\n"
			<< "pointA = " << pointA.toString() << "\n"
			<< "pointB = " << pointB.toString() << "\n"
			<< "pointC = " << pointC.toString() << "\n"
			<< "pointD = " << pointD.toString() << "\n"
			<< "NE1 = " << NE1 << "\n"
			<< "NE2 = " << NE2 << "\n"
			<< "type = " << type << "\n\n"
			<< ">>> Building the grid..." << "\n";

		FEMGrid grid;

		grid.construct_grid_4(pointA, pointB, pointC, pointD, NE1, NE2, type);

		// Grid function is only computed for triangular elements
		if (type == 1) {
			grid.export_grid("output[grid].txt");
			std::cout << "NOTE: Grid function is not computed for quadrilateral elements\n";
		}
		else {
			grid.compute_all(func);
			grid.export_all("output");

			const Vec3 test_point = { 5, 5, 0 };
			std::cout << "Test_point found in element: " << grid.get_element_containing_point(test_point);
			grid.export_function_at_point("output[point].txt", test_point);
		}
		

		std::cout << "\n>>> Done\n\n";

		if (query_is_yes(query)) {
			std::cout << ">>> Additional info:\n";

			if (!grid._centroids.empty())
				std::cout << "- Centroids were computed\n";

			if (!grid._grid_function._values.empty())
				std::cout << "- Function values were computed\n";

			if (!grid._grid_function._element_grads.empty())
				std::cout << "- Function element grads were computed\n";

			if (!grid._grid_function._element_integrals.empty())
				std::cout << "- Function element integrals were computed\n";

			if (!grid._grid_function._vertex_grads.empty())
				std::cout << "- Function vertex grads were computed\n";

			if (!grid._grid_function._vertex_integrals.empty())
				std::cout << "- Function vertex integrals were computed\n";
		}
	}
	else exit_with_error("NP not 2 or 4");
	

	// Log a copy of input
	inFile.clear();
	inFile.seekg(0);
	std::ofstream copyOfInFile("input.txt");
	copyOfInFile << inFile.rdbuf();

	return 0;
}