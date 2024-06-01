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
      void DrawBox(Vec2 position, Vec2 size);

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
