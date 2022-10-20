#include "grid_builders.h"

#include <fstream>

uint func_NE(uint type, uint inp_NE1, uint inp_NE2) {
	switch (type) {
	case 1: return 1 * inp_NE1 * inp_NE2;
	case 2: return 2 * inp_NE1 * inp_NE2;
	case 3: return 2 * inp_NE1 * inp_NE2;
	case 4: return 4 * inp_NE1 * inp_NE2;
	default: exit_with_error("Unknown type");
	}
}

uint func_NP(uint type, uint inp_NE1, uint inp_NE2) {
	return
		type == 4
		? (inp_NE1 + 1) * (inp_NE2 + 1) + inp_NE1 * inp_NE2
		: (inp_NE1 + 1) * (inp_NE2 + 1);
}

void type1_write(std::ofstream& outFile, uint NP1, uint NP2, uint NE1, uint NE2) {
	uint counter = 1;
	for (uint i = 0; i < NE1; ++i)
		for (uint j = 0; j < NE2; ++j)
			outFile
			<< ' ' << counter++
			<< ' ' << 4
			<< ' ' << i * NP1 + j + 1
			<< ' ' << i * NP1 + j + 2
			<< ' ' << i * NP1 + j + 2 + NP2
			<< ' ' << i * NP1 + j + 2 + NP2 - 1
			<< '\n';
}

void type2_write(std::ofstream& outFile, uint NP1, uint NP2, uint NE1, uint NE2) {
	uint counter = 1;
	for (uint i = 0; i < NE1; ++i)
		for (uint j = 0; j < NE2; ++j)
			outFile
			// top-left element
			<< ' ' << counter++
			<< ' ' << 3
			<< ' ' << i * NP1 + j + 1
			<< ' ' << i * NP1 + j + 2 + NP2
			<< ' ' << i * NP1 + j + 2 + NP2 - 1
			<< '\n'
			// bottom-right element
			<< ' ' << counter++
			<< ' ' << 3
			<< ' ' << i * NP1 + j + 1
			<< ' ' << i * NP1 + j + 2
			<< ' ' << i * NP1 + j + 2 + NP2
			<< '\n';
}

void type3_write(std::ofstream& outFile, uint NP1, uint NP2, uint NE1, uint NE2) {
	uint counter = 1;
	for (uint i = 0; i < NE1; ++i)
		for (uint j = 0; j < NE2; ++j)
			outFile
			// bottom-left element
			<< ' ' << counter++
			<< ' ' << 3
			<< ' ' << i * NP1 + j + 1
			<< ' ' << i * NP1 + j + 2
			<< ' ' << i * NP1 + j + 2 + NP2 - 1
			<< '\n'
			// top-right element
			<< ' ' << counter++
			<< ' ' << 3
			<< ' ' << i * NP1 + j + 2
			<< ' ' << i * NP1 + j + 2 + NP2
			<< ' ' << i * NP1 + j + 2 + NP2 - 1
			<< '\n';
}

void type4_write(std::ofstream& outFile, uint NP1, uint NP2, uint NE1, uint NE2) {
	uint counter = 1;
	uint centerCounter = 1;
	for (uint i = 0; i < NE1; ++i)
		for (uint j = 0; j < NE2; ++j)
		{
			outFile
				// bottom element
				<< ' ' << counter++
				<< ' ' << 3
				<< ' ' << i * NP1 + j + 1
				<< ' ' << i * NP1 + j + 2
				<< ' ' << NP1 * NP2 + centerCounter
				<< '\n'
				// right element
				<< ' ' << counter++
				<< ' ' << 3
				<< ' ' << i * NP1 + j + 2
				<< ' ' << i * NP1 + j + 2 + NP2
				<< ' ' << NP1 * NP2 + centerCounter
				<< '\n'
				// top element
				<< ' ' << counter++
				<< ' ' << 3
				<< ' ' << i * NP1 + j + 2 + NP2 - 1
				<< ' ' << i * NP1 + j + 2 + NP2
				<< ' ' << NP1 * NP2 + centerCounter
				<< '\n'
				// left element
				<< ' ' << counter++
				<< ' ' << 3
				<< ' ' << i * NP1 + j + 2 + NP2 - 1
				<< ' ' << i * NP1 + j + 1
				<< ' ' << NP1 * NP2 + centerCounter
				<< '\n';

			++centerCounter;
		}
}

void write_elements(std::ofstream& outFile, uint type, uint NP1, uint NP2, uint NE1, uint NE2) {
	switch (type) {
	case 1:
		type1_write(outFile, NP1, NP2, NE1, NE2);
		break;
	case 2:
		type2_write(outFile, NP1, NP2, NE1, NE2);
		break;
	case 3:
		type3_write(outFile, NP1, NP2, NE1, NE2);
		break;
	case 4:
		type4_write(outFile, NP1, NP2, NE1, NE2);
		break;
	default:
		exit_with_error("Unknown element type");
	}
}

void build_point_4(uint type, const Vec3& inp_pointA, const Vec3& inp_pointB, const Vec3& inp_pointC, const Vec3& inp_pointD,
	uint inp_NE1, uint inp_NE2) {

	std::ofstream outFile("output.txt");

	// Write NE, NP, NC
	const uint NE = func_NE(type, inp_NE1, inp_NE2);
	const uint NP = func_NP(type, inp_NE1, inp_NE2);
	const uint NC = 1;
	outFile
		<< ' ' << NE
		<< ' ' << NP
		<< ' ' << NC
		<< '\n';

	// Write info about elements
	const uint NE1 = inp_NE1;
	const uint NE2 = inp_NE2;
	const uint NP1 = inp_NE1 + 1;
	const uint NP2 = inp_NE2 + 1;

	write_elements(outFile, type, NP1, NP2, NE1, NE2);

	// Compute and write coords of grid points
	const Vec3 increment1 = (inp_pointB - inp_pointA) / NE1;
	const Vec3 increment2 = (inp_pointD - inp_pointA) / NE2;

	uint counter = 1;
	for (uint j = 0; j < NP2; ++j)
		for (uint i = 0; i < NP1; ++i) {
			// Point in local coords
			const double xi = static_cast<double>(i) / NE1;
			const double nu = static_cast<double>(j) / NE2;

			// Point in global coords
			const double weightA = (1. - xi) * (1. - nu);
			const double weightB = xi * (1. - nu);
			const double weightC = xi * nu;
			const double weightD = (1. - xi) * nu;

			const Vec3 point =
				 inp_pointA * weightA +
				 inp_pointB * weightB +
				 inp_pointC * weightC +
				 inp_pointD * weightD;

			outFile
				<< ' ' << counter++
				<< ' ' << point.x
				<< ' ' << point.y
				<< ' ' << point.z
				<< '\n';
		}

	if (type == 4) {
		for (uint j = 0; j < NP2 - 1; ++j)
			for (uint i = 0; i < NP1 - 1; ++i) {
				// Point in local coords
				const double xi = static_cast<double>(i + 0.5) / NE1;
				const double nu = static_cast<double>(j + 0.5) / NE2;

				// Point in global coords
				const double weightA = (1. - xi) * (1. - nu);
				const double weightB = xi * (1. - nu);
				const double weightC = xi * nu;
				const double weightD = (1. - xi) * nu;

				const Vec3 point =
					inp_pointA * weightA +
					inp_pointB * weightB +
					inp_pointC * weightC +
					inp_pointD * weightD;

				outFile
					<< ' ' << counter++
					<< ' ' << point.x
					<< ' ' << point.y
					<< ' ' << point.z
					<< '\n';
			}
	}

	// Write contours (1 in current case)
	outFile
		<< ' ' << 2 * NP1 + 2 * (NP2 - 2)
		<< '\n';

	for (uint i = 0; i < NP1; ++i) outFile << ' ' << NP1 * 0 + i + 1 << '\n';

	for (uint j = 1; j < NP2 - 1; ++j) outFile << ' ' << NP1 * j + NP1 << '\n';

	for (uint i = 0; i < NP1; ++i) outFile << ' ' << NP1 * NP2 - i << '\n';

	for (uint j = 1; j < NP2 - 1; ++j) outFile << ' ' << NP1 * (NP2 - j - 1) + 1 << '\n';
}