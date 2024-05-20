#include "Classes/Map.hpp"
#include "Classes/Unit.hpp"

using namespace Game;

int main(int argc, char const *argv[])
{
   Map mapa = Map(Vec2(512, 512));

   std::ofstream file_out("assets/mapa.bin", std::ios::binary);
   if(!file_out.is_open())
      return 1;
      //throw std::invalid_argument("The filepath \"" + filepath + "\" does not exists! ");
   
   ISerialize<Map>::SaveToFile(mapa, file_out);
   file_out.close();

   std::ifstream file_in("assets/mapa.bin", std::ios::binary);
   if(!file_in.is_open())
      return 1;
      //throw std::invalid_argument("The filepath \"" + filepath + "\" does not exists! ");
   
   Map carregado = ISerialize<Map>::LoadFromFile(file_in);
   file_in.close();

   return 0;
}
