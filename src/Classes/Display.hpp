#pragma once

#include "Map.hpp"

namespace Game
{
   class Display
   {
   private:
      Vec2 window_size;
      Vec2 cursor_pos;

      std::string buffer;

      void GetWindowSize();
      void ClearScreen();
      void SetCursorPosition(Vec2 position);
      void GetCursorPosition();
      
      void DrawBox();
      void DrawMap(Map& map);
      void DrawStatus();
      void DrawMenu();

   public:
      Display();
      ~Display();

      void Initialise();
      void Update();

   private:
      enum class Symbol : uint8_t
      {
         Line_EW     = 205,// '═',
         Line_NS     = 186,// '║',
         Corner_NW   = 201,// '╔',
         Corner_SW   = 200,// '╚',
         Corner_SE   = 188,// '╝',
         Corner_WE   = 187,// '╗',
         Cross       = 206 // '╬'
      };
   };
}
