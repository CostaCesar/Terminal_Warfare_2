#include "Map.hpp"

using Game::Map;
using Game::Vec2;
using Game::ISerialize;

int main(int argc, char const *argv[])
{
   Map mapa = Map(Vec2(10, 10));

   std::ofstream file("assets/mapa.bin", std::ios::binary);
   if(!file.is_open())
      return 1;
      //throw std::invalid_argument("The filepath \"" + filepath + "\" does not exists! ");
   
   ISerialize<Map>::SaveToFile(mapa, file);
   file.close();
   return 0;
}
