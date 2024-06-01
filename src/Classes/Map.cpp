#include "Map.hpp"

#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace Game
{
Tile::Tile(Vec2 _position, char* data) : position(_position)
{
   fortification = 0;
}
Tile::Tile(Vec2 _position) : position(_position)
{
   fortification = 0;
}
Tile::~Tile()
{

}
template<>
void ISerialize<Tile>::SaveToFile(Tile &object, std::ofstream &file)
{
   file.write((char*) &object.fortification, sizeof(object.fortification));
   return;
}
template<>
Tile ISerialize<Tile>::LoadFromFile(std::ifstream &file, const Vec2 position)
{
   Tile object = Tile(position);

   file.read((char*) &object.fortification, sizeof(object.fortification));
   
   return object;
}

Map::Map(Vec2 _size, std::string _name) : size(_size)
{
   name = _name;
   tiles.reserve(GetSize(size));
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


template<>
void ISerialize<Map>::SaveToFile(Map &object, std::ofstream &file)
{
   // Map Header
   file.write((char *) &object.size, sizeof(Vec2));
   
   uint16_t mapNameSize = static_cast<uint16_t>(object.name.size());
   file.write((char *) &mapNameSize, sizeof(uint16_t));
   file.write(object.name.c_str(), mapNameSize * sizeof(char));

   // Tiles
   for (Tile &tile : object.tiles)
   {
      ISerialize<Tile>::SaveToFile(tile, file);
   }

   return;
}
template<>
Map ISerialize<Map>::LoadFromFile(std::ifstream &file)
{
   Vec2 mapSize = {0, 0};
   file.read((char*) &mapSize, sizeof(Vec2));

   uint16_t mapNameSize = 0;
   file.read((char*) &mapNameSize, sizeof(uint16_t));
   std::string mapName(mapNameSize, 'x');
   file.read(mapName.data(), mapNameSize * sizeof(char));

   Map object = Map(mapSize, mapName);
   for (uint64_t i = 0; i < GetSize(mapSize); i++)
   {
      object.tiles.push_back( ISerialize<Tile>::LoadFromFile(
         file,
         Vec2(i % mapSize.X, i / mapSize.X)));
   }

   return object;
}

}