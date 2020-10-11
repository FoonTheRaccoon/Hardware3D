#pragma once
#include <vector>
#include <d3dcommon.h>

struct Verts
{
	float x, y, z;
};

struct TexCor
{
	float u, v;
};

struct VertNorm
{
	float x, y, z;
};


struct Model
{
	Model(std::vector<Verts>& verts, 
		std::vector<TexCor>& texCor, 
		std::vector<VertNorm>& vertNorm, 
		std::vector<size_t>& vertIndices, 
		std::vector<size_t>& texIndices, 
		std::vector<size_t>& normIndices, 
		D3D_PRIMITIVE_TOPOLOGY topologyType)
		:
		verts(std::move(verts)),
		texCor(std::move(texCor)),
		vertNorm(std::move(vertNorm)),
		vertIndices(std::move(vertIndices)),
		texIndices(std::move(texIndices)),
		normIndices(std::move(normIndices)),
		topologyType(topologyType)
	{}
	const std::vector<Verts> verts;
	const std::vector<TexCor> texCor;
	const std::vector<VertNorm> vertNorm;
	const std::vector<size_t> vertIndices;
	const std::vector<size_t> texIndices;
	const std::vector<size_t> normIndices;
	D3D_PRIMITIVE_TOPOLOGY topologyType;
};