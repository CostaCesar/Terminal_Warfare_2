#pragma once

#include "Map.hpp"
#include "UI_Elements.hpp"
#include <unordered_map>
#include <vector>

template<typename K, typename T> using uMap = std::unordered_map<K, T>;
namespace Game
{
   class Display
   {
   private:
      Vec2 window_size;
      Vec2 cursor_pos;

      std::vector<IElement*> elements;

      std::string buffer;

      void GetWindowSize();
      void ClearScreen();
      void SetCursorPosition(Vec2 position);
      void GetCursorPosition();
      
      void DrawMap(Map& map);
      void DrawStatus();
      void DrawMenu();

      bool HasChangedSize()
      { return false; }
      void CreateBuffer();
      void ToggleCursor(bool show);

   public:
      Display();
      ~Display();

      void Initialise();
      void Update();

      void AddElement(IElement *element);
   };
}
