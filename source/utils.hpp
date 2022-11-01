#pragma once

#include <iostream>
#include <vector>
#include <string>

using T = double;
using uint = unsigned int;

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
	inline std::string toString() const {
		return "{" +
			std::to_string(this->x) + ", " +
			std::to_string(this->y) + ", " +
			std::to_string(this->z) +
			+"}";
	}
};

inline void exit_with_error(const std::string &msg) {
	std::cout << "ERROR: " << msg << "\n";
	exit(1);
}


// Looks for element inside the array
//   > found     => return index of element inside the element
//   > not found => return std::nullopt
// NOTE: Essentialy .find() but less ugly
//
template<typename Val>
std::optional<int> find_value_in_array(const std::vector<Val> &array, Val value) {
	for (uint k = 0; k < array.size(); ++k) if (array[k] == value) return k;
	return std::nullopt;
}