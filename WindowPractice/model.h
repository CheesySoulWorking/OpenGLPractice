#pragma once
#include <vector>
#include <string>
#include "vector3.h"
#include "vector2.h"

struct Model {
	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> texCoords;
};

Model loadOBJ(const std::string& path);