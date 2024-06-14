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
   UI_Box box1 = UI_Box(Vec2(0, 0), Vec2(10, 10));
   UI_Box box2 = UI_Box(Vec2(5, 5), Vec2(15, 10), true);
   tela.AddElement(&box1);
   tela.AddElement(&box2);

   for(int i = 0; i < 200; i++)
   {
      tela.Update();
      Sleep(100);
   }

   return 0;
}
