#include <fstream>

#include "grid_builders.h"


// #####################
// ### Input parsing ###
// #####################
int main() {
	std::string filename;

	std::cout << "Take input from -> ";
	std::cin >> filename;

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

		build_point_2(type, pointA, pointB, NE);

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

		build_point_4(type, pointA, pointB, pointC, pointD, NE1, NE2);

		std::cout << ">>> Done\n";
	}
	else exit_with_error("NP not 2 or 4");

	// Log a copy of input
	inFile.clear();
	inFile.seekg(0);
	std::ofstream copyOfInFile("input.txt");
	copyOfInFile << inFile.rdbuf();

	return 0;
}