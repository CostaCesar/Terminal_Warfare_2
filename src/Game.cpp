#include "Classes/Map.hpp"
#include "Classes/Unit.hpp"
#include "Classes/Display.hpp"
#include "Windows.h"

#include <iostream>

using namespace Game;

int main(int argc, char const *argv[])
{
   Map mapa = Map(Vec2(512, 512));

   std::string inp = "assets/mapa.bin", oup = "assets/mapa.bin";

   std::ofstream file_out(inp, std::ios::binary);
   if(!file_out.is_open())
      throw std::invalid_argument("The filepath \"" + inp + "\" does not exists! ");
   
   ISerialize<Map>::SaveToFile(mapa, file_out);
   file_out.close();

   std::ifstream file_in("assets/mapa.bin", std::ios::binary);
   if(!file_in.is_open())
      throw std::invalid_argument("The filepath \"" + oup + "\" does not exists! ");
   
   Map carregado = ISerialize<Map>::LoadFromFile(file_in);
   file_in.close();

   Display tela;

   for(int i = 0; i < 200; i++)
   {
      tela.DrawBox(Vec2(i, i), Vec2(i+2, i+2), true);
      tela.Update();
      Sleep(100);
   }

   return 0;
}
