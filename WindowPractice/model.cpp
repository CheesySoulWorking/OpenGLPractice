#include "model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Model loadOBJ(const std::string& path) {
    Model model;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return model;
    }

    std::vector<Vector3> tempPositions;
    std::vector<Vector3> tempNormals;
    std::vector<Vector2> tempTexCoords;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        // vertex
        if (type == "v") {
            Vector3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            tempPositions.push_back(pos);
        }
        
        // texture coordinate
        else if (type == "vt") {
            Vector2 tex;
            iss >> tex.x >> tex.y;
            tempTexCoords.push_back(tex);
        }

        // normal
        else if (type == "vn") {
            Vector3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }

        // face
        else if (type == "f") {
            // Faces can have format like:
            // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
            std::string vertexStr;
            for (int i = 0; i < 3; ++i) {
                iss >> vertexStr;
                std::replace(vertexStr.begin(), vertexStr.end(), '/', ' ');
                std::istringstream viss(vertexStr);
                int vIdx, tIdx, nIdx;
                viss >> vIdx >> tIdx >> nIdx;

                model.positions.push_back(tempPositions[vIdx - 1]);
                if (!tempTexCoords.empty())
                    model.texCoords.push_back(tempTexCoords[tIdx - 1]);
                if (!tempNormals.empty())
                    model.normals.push_back(tempNormals[nIdx - 1]);
            }
        }
    }

    return model;
}