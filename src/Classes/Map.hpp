#pragma once

#include "ISerialize.hpp"
#include "Commons.hpp"
#include "Unit.hpp"

#include <vector>
#include <array>
#include <fstream>

namespace Game
{
   class Tile : ISerialize<Tile>
   {
   private:
      const Vec2 position;

      // Serialized (Go to file) vars
      // TODO: Tile propreties (vegetation, terrain, etc)
      uint8_t fortification;

   public:
      // Constructors
      Tile(Vec2 _position, char* data);
      Tile(Vec2 _position);
      ~Tile();
      Tile() = delete;

      friend Tile ISerialize<Tile>::LoadFromFile(std::ifstream &file, const Vec2 position);
      friend void ISerialize<Tile>::SaveToFile(Tile &object, std::ofstream &file);
   };
   
   class Map : ISerialize<Map>
   {
   private:
      std::string name;
      const Vec2 size;
      std::vector<Tile> tiles{};

   public:
      // Constructors
      Map(Vec2 _size, std::string _name);
      Map(Vec2 _size);
      ~Map();
      Map() = delete;

      // Overloads
      Tile &operator() (uint32_t X, uint32_t Y);
      Tile &operator() (Vec2 position);

      // Static
      friend Map ISerialize<Map>::LoadFromFile(std::ifstream &file);
      friend void ISerialize<Map>::SaveToFile(Map &object, std::ofstream &file);
   };

}