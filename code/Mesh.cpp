#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "GL/glew.h"

Mesh::Mesh()
{
    this->drawType = GL_TRIANGLES;
}

void Mesh::load_from_obj(const char* pathToFile)
{
    struct Vector3
    {
        float x, y, z, w;
    };

    std::vector<Vector3> fileVertices;
    std::vector<Vector3> fileIndices;

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
            fileVertices.push_back(vertex);
        }
        else if (type == "f")
        {
            Vector3 index;

            std::string index1;
            std::string index2;
            std::string index3;

            ss >> index1 >> index2 >> index3;

            index1 = index1.substr(0, index1.find('/'));
            index2 = index2.substr(0, index2.find('/'));
            index3 = index3.substr(0, index3.find('/'));

            index.x = std::stoi(index1);
            index.y = std::stoi(index2);
            index.z = std::stoi(index3);

            fileIndices.push_back(index);
        }


        this->vertexCount = 4*std::size(fileVertices);
        this->indexCount = 3*std::size(fileIndices);
        
        this->vertices = new float[this->vertexCount];
        this->indices = new unsigned int[this->indexCount];

        int counter = 0;
        for (Vector3 i : fileVertices)
        {
            this->vertices[counter] = i.x;
            this->vertices[counter + 1] = i.y;
            this->vertices[counter + 2] = i.z;
            this->vertices[counter + 3] = 1.0;
            counter += 4;
        }

        counter = 0;
        for (Vector3 i : fileIndices)
        {
            this->indices[counter] = i.x - 1;
            this->indices[counter + 1] = i.y - 1;
            this->indices[counter + 2] = i.z - 1;

            counter += 3;
        }
    }

    file.close();
}

void Mesh::print()
{
    std::cout << "Vertices: " << int(this->vertexCount/4.0) << std::endl;
    for (int i = 0; i < this->vertexCount; i += 4)
    {
        std::cout << "[" << this->vertices[i] << ", " << this->vertices[i + 1] << ", " << this->vertices[i + 2] << ", " << this->vertices[i + 3] << "]" << std::endl;
    }

    std::cout << "\nIndices: " << int(this->indexCount) << std::endl;
    for (int i = 0; i < this->indexCount; i += 3)
    {
        std::cout << "[" << this->indices[i] << ", " << this->indices[i + 1] << ", " << this->indices[i + 2] <<  "]" << std::endl;
    }
}