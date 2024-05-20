#pragma once

#include <cstdint>
#include <string>

namespace Game
{
   struct Vec2
   {
      uint32_t X;
      uint32_t Y;

      Vec2(uint32_t _X, uint32_t _Y);
   };
   
   uint32_t GetPosition(Vec2 position, Vec2 size);
   Vec2 GetPosition(uint32_t position, Vec2 size);
   uint32_t GetSize(Vec2 size);

}