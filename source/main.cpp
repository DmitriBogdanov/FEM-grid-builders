#include "FEMGrid.h"

#include <fstream>


// #####################
// ### Input parsing ###
// #####################
T func(Vec3 point)
{
	return(10 + 5 * point.y * sin(2 * PI * point.x));
}

bool if_output(std::string answer){
	if (answer == "Yes" || answer == "yes")
		return(true);
	else
		return(false);
}

int main() {
	const int MAX_THREADS = omp_get_max_threads();
	omp_set_num_threads(MAX_THREADS);
	std::cout << "Number of threads = " << MAX_THREADS << "\n";

	std::string filename = "lab4_input", answer; //For lab4 we need only one file 

	std::cout << "Do you wanna output the data? (Yes/No) -> ";
	std::cin >> answer;

	//std::cout << "Take input from -> ";
	//std::cin >> filename;

	std::ifstream inFile(filename + ".txt");
	if (!inFile.is_open()) exit_with_error("Could not open input file");

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

		FEMGrid obj;

		obj.construct_grid_2(pointA, pointB, NE, type);
		obj.export_grid("output.txt");

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

		FEMGrid obj;

		obj.construct_grid_4(pointA, pointB, pointC, pointD, NE1, NE2, type);
		obj.calculation(func);

		obj.export_all("output");

		std::cout << ">>> Done\n";
		if (if_output(answer))
		{
			/// TESTING
			auto neighboors = obj.get_elements_adjacent_to_vertex(0);
			for (auto &el : neighboors) std::cout << "   " << el;

			std::cout << "\n\n";

			/// TESTING
			auto neighboorsPoints = obj.get_vertices_adjacent_to_vertex(0);
			for (auto &point : neighboorsPoints) std::cout << "   " << point;

			std::cout << "\n\n";

			/// TESTING
			for (auto &centroid : obj._centroids) std::cout << centroid.toString() << "\n";
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