#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <functional>
#include <omp.h>

using T = double;
using uint = unsigned int;
static const double PI = 3.141592653589793;

struct Vec3 {
	T x;
	T y;
	T z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	inline Vec3 operator=(const Vec3 &other) {
		this->x = other.x; this->y = other.y; this->z = other.z;
		return *this;
	}

	// Arithmetic
	inline Vec3 operator+(const Vec3 &other) const {
		return Vec3{ this->x + other.x, this->y + other.y , this->z + other.z };
	}
	inline Vec3 operator-(const Vec3 &other) const {
		return Vec3{ this->x - other.x, this->y - other.y , this->z - other.z };
	}
	inline Vec3 operator*(T val) const {
		return Vec3{ this->x * val, this->y * val, this->z * val };
	}
	inline Vec3 operator/(T val) const {
		return Vec3{ this->x / val, this->y / val, this->z / val };
	}

	// Increments
	inline Vec3& operator+=(const Vec3 &other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}
	inline Vec3& operator-=(const Vec3 &other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}
	inline Vec3& operator*=(const Vec3 &other) {
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}
	inline Vec3& operator/=(const Vec3 &other) {
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}

	// Conversion
	inline std::string toString(const std::string &begin = "", const std::string &delimer = " ", const std::string &end = "") const {
		return begin +
			std::to_string(this->x) + delimer +
			std::to_string(this->y) + delimer +
			std::to_string(this->z) +
			end;
	}

	inline T norm() {
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
};

inline T triangle_area(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
	Vec3 AB = a - b, AC = a - c;
	Vec3 res(AB.y * AC.z - AC.y * AB.z, AB.z * AC.x - AC.z * AB.x, AB.x * AC.y - AC.x * AB.y);
	return res.norm() / T(2);
}


inline T sqr(T val) { return val * val; }

inline void exit_with_error(const std::string &msg) {
	std::cout << "ERROR: " << msg << "\n";
	exit(1);
}

// Looks for element inside the array
//   > found     => return index of element inside the element
//   > not found => return std::nullopt
//
// NOTE: Essentialy .find() but less ugly
//
template<typename Val>
std::optional<size_t> find_value_in_array(const std::vector<Val> &array, Val value) {
	for (size_t k = 0; k < array.size(); ++k) if (array[k] == value) return k;
	return std::nullopt;
}

template<typename _Ty>
T sum_of_array(const _Ty &array) {
	T sum = 0;
	for (const auto &el : array) sum += el;
	return sum;
}

inline Vec3 project_onto_plane(const Vec3 &point) {
	return Vec3(point.x, point.y, 0);
}