#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Mesh.h"

void Mesh::load_from_obj(const char* pathToFile)
{
    struct Vector3
    {
        float x, y, z;
    };

    std::vector<Vector3> vertices;
    std::vector<Vector3> indices;

    std::ifstream file(pathToFile);

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            Vector3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (type == "f")
        {
            std::string index1;
            std::string index2;
            std::string index3;

            ss >> index1 >> index2 >> index3;

            int index = index1.find('/');
            //std::cout << index << std::endl;
        }
    }

    //std::cout << std::size(vertices);

    file.close();
}