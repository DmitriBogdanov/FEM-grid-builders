#pragma once

#include <iostream>
#include <string>

using uint = unsigned int;

struct Vec3 {

	Vec3() : x(0), y(0), z(0) {}
	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	inline Vec3 operator=(const Vec3 &other) {
		this->x = other.x; this->y = other.y; this->z = other.z;
		return *this;
	}

	inline Vec3 operator+(const Vec3 &other) const {
		return Vec3{ this->x + other.x, this->y + other.y , this->z + other.z };
	}

	inline Vec3 operator-(const Vec3 &other) const {
		return Vec3{ this->x - other.x, this->y - other.y , this->z - other.z };
	}

	inline Vec3 operator*(double val) const {
		return Vec3{ this->x * val, this->y * val, this->z * val };
	}

	inline Vec3 operator/(double val) const {
		return Vec3{ this->x / val, this->y / val, this->z / val };
	}

	inline std::string toString() const {
		return "{" +
			std::to_string(this->x) + ", " +
			std::to_string(this->y) + ", " +
			std::to_string(this->z) +
			+"}";
	}

	double x;
	double y;
	double z;
};

inline void exit_with_error(const std::string &msg) {
	std::cout << "ERROR: " << msg << "\n";
	exit(1);
}