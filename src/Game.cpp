#include "Classes/Map.hpp"
#include "Classes/Unit.hpp"
#include "Classes/Display.hpp"
#include "Windows.h"

#include <iostream>

using namespace Game;

int main(int argc, char const *argv[])
{
   Map test_map = Map(Vec2(512, 512));

   std::string input_map = "assets/test_map.bin", output_map = "assets/test_map.bin";

   std::ofstream file_out(input_map, std::ios::binary);
   if(!file_out.is_open())
      throw std::invalid_argument("The filepath \"" + input_map + "\" does not exists! ");
   
   ISerialize<Map>::SaveToFile(test_map, file_out);
   file_out.close();

   std::ifstream file_in("assets/test_map.bin", std::ios::binary);
   if(!file_in.is_open())
      throw std::invalid_argument("The filepath \"" + output_map + "\" does not exists! ");
   
   Map loaded_map = ISerialize<Map>::LoadFromFile(file_in);
   file_in.close();

   Display window;
   
   UI_Box box1 = UI_Box(Vec2(0, 0), Vec2(10, 10));
   UI_Box box2 = UI_Box(Vec2(5, 5), Vec2(15, 10), true);
   
   UI_Text text1 = UI_Text(Vec2(10, 10), Vec2(32, 5),
      {"Example", "Test", ".123com"}, UI_Text::Alignment::Right);
   UI_Text text2 = UI_Text(Vec2(60, 10), Vec2(16, 5),
      {"Example", "Test", ".123com"}, UI_Text::Alignment::Left);
   UI_BoxText box_text1 = UI_BoxText(Vec2(24,10), Vec2(24,10),
      {"Example", "Test", ".123com"}, Vec2(0,0), UI_Text::Alignment::Left);
   
   window.AddElement(&box1);
   window.AddElement(&box2);
   window.AddElement(&text1);
   window.AddElement(&text2);
   window.AddElement(&box_text1);

   for(int i = 0; i < 200; i++)
   {
      window.Update();
      Sleep(100);
   }

   return 0;
}
