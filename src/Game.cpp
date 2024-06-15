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
   
   UI_Text text1 = UI_Text(Vec2(10, 10), Vec2(32, 5),
      {"Example", "Test", ".123com"}, UI_Text::Alignment::Right);
   UI_Text text2 = UI_Text(Vec2(60, 10), Vec2(16, 5),
      {"Example", "Test", ".123com"}, UI_Text::Alignment::Left);
   UI_Text text3 = UI_Text(Vec2(20, 15), Vec2(24, 10),
      {"Example", "Test", ".123com"}, UI_Text::Alignment::Center);
   
   tela.AddElement(&box1);
   tela.AddElement(&box2);
   tela.AddElement(&text1);
   tela.AddElement(&text2);
   tela.AddElement(&text3);

   for(int i = 0; i < 200; i++)
   {
      tela.Update();
      Sleep(100);
   }

   return 0;
}
