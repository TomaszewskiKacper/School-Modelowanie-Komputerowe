#include "CubePalette.h"
#include <iostream>

CubePalette::CubePalette()
{
	m_palette.insert(std::make_pair(Cube::Type::None, Cube("Textures/test.png")));
	m_palette.insert(std::make_pair(Cube::Type::Grass, Cube("Textures/grass.jpg")));
	m_palette.insert(std::make_pair(Cube::Type::Stone, Cube("Textures/stone.jpg")));
	m_palette.insert(std::make_pair(Cube::Type::Dirt, Cube("Textures/dirt.jpg")));
	m_palette.insert(std::make_pair(Cube::Type::Alive, Cube("Textures/alive.jpg")));

}

const Cube& CubePalette::LookUp(Cube::Type type) const
{
	auto it = m_palette.find(type);
	if (it != m_palette.end()) {
		return it->second;
	}
	else {
		return m_palette.find(Cube::Type::None)->second;
	}
}
