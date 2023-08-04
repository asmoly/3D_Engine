#include "Mesh.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(const char* pathToFile)
{
    this->load_from_obj(pathToFile);
}

// void Mesh::load_from_obj(const char* pathToFile)
// {
//     this->drawType = GL_TRIANGLES;

//     struct TextureCoord
//     {
//         float x = 0.0, y = 0.0;
//     };

//     struct Vertex
//     {
//         float x, y, z;
//         TextureCoord textureCoord;
//         bool assigned = true;
//         int nextCopy = -1;
//     };

//     std::vector<Vertex> fileVertices;
//     std::vector<TextureCoord> fileTextureCoords;
//     std::vector<int> fileIndices;

//     std::ifstream file(pathToFile);

//     std::string line;
//     while (std::getline(file, line))
//     {
//         std::stringstream ss(line);
//         std::string type;
//         ss >> type;

//         if (type == "v")
//         {
//             Vertex vertex;
//             ss >> vertex.x >> vertex.y >> vertex.z;
//             vertex.assigned = false;
//             fileVertices.push_back(vertex);
//         }
//         else if (type == "vt")
//         {
//             TextureCoord textureCoord;
//             ss >> textureCoord.x >> textureCoord.y;
//             fileTextureCoords.push_back(textureCoord);
//         }
//         else if (type == "f")
//         {
//             for (int i = 0; i < 3; i++)
//             {
//                 std::string element;
//                 ss >> element;
//                 std::replace(element.begin(), element.end(), '/', ' ');
//                 std::stringstream elementStream(element);

//                 std::string indexAsStr;
//                 std::string textureCoordIndexAsStr;
//                 std::string normalIndexAsStr;

//                 elementStream >> indexAsStr >> textureCoordIndexAsStr >> normalIndexAsStr;

//                 int index = std::stoi(indexAsStr) - 1;
//                 int textureCoordIndex = std::stoi(textureCoordIndexAsStr) - 1;
//                 int normalIndex = std::stoi(normalIndexAsStr) - 1;

//                 bool foundCoord = false;
//                 int newIndex = index;
//                 while (foundCoord == false)
//                 {
//                     TextureCoord textureCoord = fileTextureCoords[textureCoordIndex];

//                     if (fileVertices[newIndex].assigned == false)
//                     {
//                         // set default vertex
//                         fileVertices[newIndex].textureCoord = textureCoord;
//                         fileVertices[newIndex].assigned = true;

//                         // Found
//                         foundCoord = true;
//                         fileIndices.push_back(newIndex);
//                     }
//                     else if (fileVertices[newIndex].textureCoord.x == textureCoord.x && fileVertices[newIndex].textureCoord.y == textureCoord.y)
//                     {
//                         // Found
//                         foundCoord = true;
//                         fileIndices.push_back(newIndex);
//                     }
//                     else if (fileVertices[newIndex].nextCopy == -1)
//                     {
//                         // Create new copy
//                         Vertex newVertex;
//                         newVertex.textureCoord = textureCoord;

//                         newVertex.x = fileVertices[newIndex].x;
//                         newVertex.y = fileVertices[newIndex].y;
//                         newVertex.z = fileVertices[newIndex].z;
//                         fileVertices[newIndex].nextCopy = fileVertices.size();

//                         fileVertices.push_back(newVertex);
//                         fileIndices.push_back(fileVertices[newIndex].nextCopy);
//                         foundCoord = true;
//                         // Found
//                     }
//                     else
//                     {
//                         // Skip
//                         newIndex = fileVertices[newIndex].nextCopy;
//                         foundCoord = false;
//                     }
//                 }
//             }
//         }
//     }

//     file.close();

//     this->vertexCount = (4 + 2)*std::size(fileVertices);
//     this->indexCount = std::size(fileIndices);
    
//     this->vertices = new float[this->vertexCount];
//     this->indices = new unsigned int[this->indexCount];

//     int counter = 0;
//     for (Vertex i : fileVertices)
//     {
//         this->vertices[counter] = i.x;
//         this->vertices[counter + 1] = i.y;
//         this->vertices[counter + 2] = i.z;
//         this->vertices[counter + 3] = 1.0;
//         this->vertices[counter + 4] = i.textureCoord.x;
//         this->vertices[counter + 5] = i.textureCoord.y;

//         counter += (4 + 2);
//     }

//     counter = 0;
//     for (int i : fileIndices)
//     {
//         this->indices[counter] = i;
//         counter += 1;
//     }
// }

void Mesh::load_from_obj(const char* pathToFile)
{
    this->drawType = GL_TRIANGLES;

    struct TextureCoord
    {
        float x = 0.0, y = 0.0;
    };

    struct Normal
    {
        float x, y, z;
    };

    struct Vertex
    {
        float x, y, z;
        
        TextureCoord textureCoord;
        bool assigned = true;
        int nextCopy = -1;

        Normal normal;
        std::vector<int> normalIndices;
    };

    struct Index
    {
        int vertexIndex, textureCoordIndex, normalIndex;
    };

    std::vector<Vertex> fileVertices;
    std::vector<Normal> fileNormals;
    std::vector<TextureCoord> fileTextureCoords;
    std::vector<Index> fileIndices;

    std::ifstream file(pathToFile);

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            Vertex vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertex.assigned = false;
            fileVertices.push_back(vertex);
        }
        else if (type == "vn")
        {
            Normal normal;
            ss >> normal.x >> normal.y >> normal.z;
            fileNormals.push_back(normal);
        }
        else if (type == "vt")
        {
            TextureCoord textureCoord;
            ss >> textureCoord.x >> textureCoord.y;
            fileTextureCoords.push_back(textureCoord);
        }
        else if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                std::string element;
                ss >> element;
                std::replace(element.begin(), element.end(), '/', ' ');
                std::stringstream elementStream(element);

                Index index;
                elementStream >> index.vertexIndex >> index.textureCoordIndex >> index.normalIndex;
                index.vertexIndex -= 1;
                index.textureCoordIndex -= 1;
                index.normalIndex -= 1;
                fileIndices.push_back(index);
            }
        }
    }

    file.close();

    for (Index i : fileIndices)
    {
        if (std::find(fileVertices[i.vertexIndex].normalIndices.begin(), fileVertices[i.vertexIndex].normalIndices.end(), i.normalIndex) == fileVertices[i.vertexIndex].normalIndices.end())
        {
            fileVertices[i.vertexIndex].normalIndices.push_back(i.normalIndex);
        }
    }

    int counter = 0;
    for (Vertex i : fileVertices)
    {
        i.normal.x = 0.0;
        i.normal.y = 0.0;
        i.normal.z = 0.0;

        for (int j : i.normalIndices)
        {
            i.normal.x += fileNormals[j].x;
            i.normal.y += fileNormals[j].y;
            i.normal.z += fileNormals[j].z;
        }

        fileVertices[counter].normal.x = i.normal.x/(float)i.normalIndices.size();
        fileVertices[counter].normal.y = i.normal.y/(float)i.normalIndices.size();
        fileVertices[counter].normal.z = i.normal.z/(float)i.normalIndices.size();
        counter ++;
    }

    counter = 0;
    for (Index i : fileIndices)
    {
        TextureCoord textureCoord = fileTextureCoords[i.textureCoordIndex];

        int newIndex = i.vertexIndex;
        bool foundVertex = false;
        while (foundVertex == false)
        {
            if (fileVertices[newIndex].assigned == false)
            {
                fileVertices[newIndex].textureCoord = textureCoord;
                fileVertices[newIndex].assigned = true;
                foundVertex = true;
            }
            else if (fileVertices[newIndex].textureCoord.x == textureCoord.x && fileVertices[newIndex].textureCoord.y == textureCoord.y)
            {
                foundVertex = true;
            }
            else if (fileVertices[newIndex].nextCopy == -1)
            {
                Vertex newVertex;
                newVertex.x = fileVertices[newIndex].x;
                newVertex.y = fileVertices[newIndex].y;
                newVertex.z = fileVertices[newIndex].z;
                newVertex.normal.x = fileVertices[newIndex].normal.x;
                newVertex.normal.y = fileVertices[newIndex].normal.y;
                newVertex.normal.z = fileVertices[newIndex].normal.z;
                newVertex.textureCoord = textureCoord;

                newIndex = fileVertices.size();
                fileIndices[counter].vertexIndex = newIndex;
                fileVertices.push_back(newVertex);
                foundVertex = true;
            }
            else
            {
                newIndex = fileVertices[newIndex].nextCopy;
                foundVertex = false;
            }
        }

        counter ++;
    }

    this->vertexCount = (4 + 2 + 3)*std::size(fileVertices);
    this->vertices = new float[this->vertexCount];

    this->indexCount = std::size(fileIndices);
    this->indices = new unsigned int[this->indexCount];

    counter = 0;
    for (Vertex i : fileVertices)
    {
        this->vertices[counter] = i.x;
        this->vertices[counter + 1] = i.y;
        this->vertices[counter + 2] = i.z;
        this->vertices[counter + 3] = 1.0;
        this->vertices[counter + 4] = i.textureCoord.x;
        this->vertices[counter + 5] = i.textureCoord.y;
        this->vertices[counter + 6] = i.normal.x;
        this->vertices[counter + 7] = i.normal.y;
        this->vertices[counter + 8] = i.normal.z;

        counter += (4 + 2 + 3);
    }

    counter = 0;
    for (Index i : fileIndices)
    {
        this->indices[counter] = i.vertexIndex;
        counter ++;
    }
}

void Mesh::print()
{
    std::cout << "Vertices: " << int(this->vertexCount/9.0) << std::endl;
    for (int i = 0; i < this->vertexCount; i += 9)
    {
        std::cout << "[" << this->vertices[i] << ", " << this->vertices[i + 1] << ", " << this->vertices[i + 2] << ", " << this->vertices[i + 3] << ", " << this->vertices[i + 4] << ", " << this->vertices[i + 5] << ", " << this->vertices[i + 6] << ", " << this->vertices[i + 7] << ", " << this->vertices[i + 8] << "]" << std::endl;
    }

    std::cout << "\nIndices: " << int(this->indexCount/3.0) << std::endl;
    for (int i = 0; i < this->indexCount; i += 3)
    {
        std::cout << "[" << this->indices[i] << ", " << this->indices[i + 1] << ", " << this->indices[i + 2] <<  "]" << std::endl;
    }
}