#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Model.h"
#include <d3dcommon.h>

struct ObjLoader
{
	//Main Loading function
	static Model MakeModelFromObjFile(const std::wstring& file_in)
	{
		std::ifstream file(file_in);

		if (file)
		{
			//File reading variables
			char line[512];

			std::string lineBuffer;
			std::string firstWord;

			//Model making variables
			std::vector<Verts> verticies;
			std::vector<TexCor> texCor;
			std::vector<VertNorm> verticiesNorm;
			std::vector<size_t> vertIndices;
			std::vector<size_t> texIndices;
			std::vector<size_t> normIndices;

			D3D_PRIMITIVE_TOPOLOGY topoType;

			while (file.getline(line, 512))
			{
				lineBuffer = line;

				firstWord = GetFirstWordInLine(lineBuffer);

				if (firstWord == "v") //Vertice line
				{
					PullVerticeFromLine(lineBuffer, verticies);
				}
				else if (firstWord == "vt") //Texture coordinate line
				{
					PullTextureCoordFromLine(lineBuffer, texCor);
				}
				else if (firstWord == "vn") //Vert normal line
				{
					PullVerticeNormFromLine(lineBuffer, verticiesNorm);
				}
				else if (firstWord == "f") //Load all three indicies
				{
					topoType = PullIndiciesFromLine(lineBuffer, vertIndices, texIndices, normIndices);
				}
			}

			return { verticies, texCor, verticiesNorm, vertIndices, texIndices, normIndices, topoType};
		}
		return MakeModelFromObjFile(L"Models\\sphere.obj");
	}
private:

	//Helper functions
	static std::string GetFirstWordInLine(const std::string& line)
	{
		std::string resultBuffer;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				resultBuffer += line[i];
			}
			else
			{
				return resultBuffer;
			}
		}

		return resultBuffer;
	}
	//Extract verticies from a line
	static void PullVerticeFromLine(const std::string& line, std::vector<Verts>& verticies)
	{
		std::string numBuf;

		float vec[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		int index = 0;

		for (int i = 2; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		//For last element
		vec[index] = std::stof(numBuf);

		verticies.emplace_back(Verts{ vec[0], vec[1], vec[2]});
	}
	//Extract texture coordinates from a line
	static void PullTextureCoordFromLine(const std::string& line, std::vector<TexCor>& texCor)
	{
		std::string numBuf;

		float vec[3] = { 0.0f, 0.0f, 0.0f};

		int index = 0;

		for (int i = 3; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		
		//For last element
		vec[index] = std::stof(numBuf);

		texCor.emplace_back(TexCor{ vec[0], vec[1]});
	}
	//Extract the vertice normal from a line
	static void PullVerticeNormFromLine(const std::string& line, std::vector<VertNorm>& verticiesNorm)
	{
		std::string numBuf;

		float vec[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		int index = 0;

		for (int i = 3; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		
		//For last element
		vec[index] = std::stof(numBuf);

		verticiesNorm.emplace_back(VertNorm{ vec[0], vec[1], vec[2] });
	}

	//Extract extract each type of idicies from a line and return a topology type based on spacing
	static D3D_PRIMITIVE_TOPOLOGY PullIndiciesFromLine(
		const std::string&		line,
		std::vector<size_t>&	vertIndices, 
		std::vector<size_t>&	texIndices, 
		std::vector<size_t>&	normIndices)
	{
		std::string numBuf;

		int slashIndex = 0;
		int spaceIndex = 0;

		for (int i = 2; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				if (line[i] == '/')
				{
					size_t index = size_t(std::stoi(numBuf) - 1);
					if (slashIndex == 0)
					{
						vertIndices.emplace_back(index);
					}
					else if (slashIndex == 1)
					{
						texIndices.emplace_back(index);
					}
					++slashIndex;
					numBuf.clear();
				}
				else
				{
					numBuf += line[i];
				}
			}
			else
			{
				size_t index = size_t(std::stoi(numBuf) - 1);
				normIndices.emplace_back(index);
				numBuf.clear();
				++spaceIndex;
				slashIndex = 0;
			}
		}
		size_t index = size_t(std::stoi(numBuf) - 1);
		normIndices.emplace_back(index);

		if (spaceIndex == 2)
		{
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		}
		else if (spaceIndex == 3)
		{
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		}
		else
		{
			std::exception("ObjLoader unable to get proper indicies space count from 'PullIndiciesFromLine' function!");
		}
	}
};