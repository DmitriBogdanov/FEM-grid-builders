#pragma once

#include "utils.hpp"

void build_point_2(
	uint type, const Vec3 &inp_pointA, const Vec3 &inp_pointB,
	uint inp_NE);

void build_point_4(
	uint type, const Vec3& inp_pointA, const Vec3& inp_pointB, const Vec3& inp_pointC, const Vec3& inp_pointD,
	uint inp_NE1, uint inp_NE2);

void build_point_4_type_1(
	const Vec3 &inp_pointA, const Vec3 &inp_pointB, const Vec3 &inp_pointC, const Vec3 &inp_pointD,
	uint inp_NE1, uint inp_NE2);

void build_point_4_type_2(
	const Vec3 &inp_pointA, const Vec3 &inp_pointB, const Vec3 &inp_pointC, const Vec3 &inp_pointD,
	uint inp_NE1, uint inp_NE2);

void build_point_4_type_3(
	const Vec3 &inp_pointA, const Vec3 &inp_pointB, const Vec3 &inp_pointC, const Vec3 &inp_pointD,
	uint inp_NE1, uint inp_NE2);

void build_point_4_type_4(
	const Vec3 &inp_pointA, const Vec3 &inp_pointB, const Vec3 &inp_pointC, const Vec3 &inp_pointD,
	uint inp_NE1, uint inp_NE2);