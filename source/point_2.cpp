#include "grid_builders.h"

#include <fstream>

void build_point_2(uint type, const Vec3 &inp_pointA, const Vec3 &inp_pointB, uint inp_NE) {
	std::ofstream outFile("output.txt");

	// Write NE, NP, NC
	const uint NE = inp_NE;
	const uint NP = type * inp_NE + 1;
	const uint NC = 2;

	outFile
		<< ' ' << NE
		<< ' ' << NP
		<< ' ' << NC
		<< '\n';

	// Write info about elements
	for (uint i = 0; i < NE; ++i) {
		outFile
			<< ' ' << i + 1
			<< ' ' << type + 1;

		for (uint j = 1; j <= type + 1; ++j) outFile << ' ' << type * i + j;

		outFile << '\n';
	}

	// Compute and write coords of grid points
	const Vec3 increment = (inp_pointB - inp_pointA) / (NP - 1);

	for (uint i = 0; i < NP; ++i) {
		const Vec3 point = inp_pointA + increment * i;

		outFile
			<< ' ' << i + 1
			<< ' ' << point.x
			<< ' ' << point.y
			<< ' ' << point.z
			<< '\n';
	}

	// Write contours (2 in current case)
	outFile
		<< ' ' << 1
		<< ' ' << 1
		<< '\n';

	outFile
		<< ' ' << 1
		<< '\n'
		<< ' ' << NP;
}