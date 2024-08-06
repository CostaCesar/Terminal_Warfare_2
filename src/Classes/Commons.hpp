#pragma once

#include <cstdint>
#include <string>
#include <exception>

#define MAX_UNITS_IN_TILE 1

namespace Game
{
   struct Vec2
   {
      uint32_t X;
      uint32_t Y;

      Vec2(uint32_t _X, uint32_t _Y);
      Vec2();

      uint32_t operator()(Vec2 position);
      uint32_t operator()(uint32_t X, uint32_t Y);
      Vec2 operator+(Vec2 other);
      Vec2 operator-(Vec2 other);
     
      bool IsInside(Vec2 end, Vec2 start = Vec2(0, 0));
   };
   typedef uint16_t ExitCode;
   
   uint32_t GetPosition(Vec2 position, Vec2 size);
   Vec2 GetPosition(uint32_t position, Vec2 size);
   uint32_t GetSize(Vec2 size);

}