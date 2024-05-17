#include "Map.hpp"

#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace Game
{
Tile::Tile(Vec2 _position, char* data) : position(_position)
{
   
}
Tile::Tile(Vec2 _position) : position(_position)
{

}
Tile::~Tile()
{

}
template<>
void Tile::ISerialize<Tile>::SaveToFile(Tile &object, std::ofstream &file)
{
   file.write((char*) &object.position.X, sizeof(uint32_t));
   file.write((char*) &object.position.Y, sizeof(uint32_t));
   return;
}

Map::Map(Vec2 _size, char *data) : size(_size)
{
   
}
Map::Map(Vec2 _size) : size(_size)
{
   name = "NONE";
   uint32_t tileCount = GetSize(size);
   for (size_t i = 0; i < tileCount; i++)
   {
      tiles.push_back(Tile(GetPosition(i, size)));
   }
   
}
Map::~Map()
{

}

// Tile &Map::operator()(uint32_t X, uint32_t Y)
// {

// }
// Tile &Map::operator()(Position position)
// {

// }

// Map Map::LoadFromFile(std::string filepath)
// {

// }
template<>
void Map::ISerialize<Map>::SaveToFile(Map &object, std::ofstream &file)
{
   // Map Header
   uint32_t mapSize = GetSize(object.size);
   file.write((char *) &mapSize, sizeof(uint32_t));
   
   uint16_t mapNameSize = static_cast<uint16_t>(object.name.size());
   file.write((char *) &mapNameSize, sizeof(uint16_t));
   file.write(object.name.c_str(), object.name.size() * sizeof(char));

   // Tiles
   for (Tile &tile : object.tiles)
   {
      ISerialize<Tile>::SaveToFile(tile, file);
   }

   return;
}

}