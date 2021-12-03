#pragma once
#include "pch.h"

template<typename T>
struct Vector3 {
	T x, y, z;

	Vector3();

	Vector3(T x, T y, T z);

	Vector3<T> operator+(const Vector3<T>& other);
};

typedef Vector3<float> Vector3F;
typedef Vector3<int> Vector3I;

struct Voxel {
	Vector3F position;
	float value;
};

int edgeTable[256];
int indexTable[256][16];

extern "C" {
	__declspec(dllexport) void mcMarchingCubes(float isoLevel, const Vector3I& resolution, const Voxel*& voxels, Vector3F*& vertices, int*& triangles, int* length, std::vector<Vector3F>*& verticesList, std::vector<int>*& trianglesList);

	__declspec(dllexport) void mcDeleteVector(unsigned char* array);
}

void triangulateCell(float isoLevel, const Voxel& voxel0, const Voxel& voxel1, const Voxel& voxel2, const Voxel& voxel3, const Voxel& voxel4, const Voxel& voxel5, const Voxel& voxel6, const Voxel& voxel7, std::vector<Vector3F>& vertices,
	std::vector<int>& triangles);

Vector3F interpolateVertexPosition(const Voxel& voxel1, const Voxel& voxel2, float isoLevel);

const Voxel& getVoxel(const Vector3I& position, const Vector3I& resolution, const Voxel*& voxels);

template<typename T>
inline Vector3<T>::Vector3() : x(), y(), z()
{
}

template<typename T>
inline Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& other)
{
	return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
}
