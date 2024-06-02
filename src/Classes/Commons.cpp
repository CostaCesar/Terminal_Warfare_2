#include "Commons.hpp"

namespace Game
{
   Vec2::Vec2(uint32_t _X, uint32_t _Y)
   {
      this->X = _X;
      this->Y = _Y;
   }
   Vec2::Vec2()
   {
      this->X = 0;
      this->Y = 0;
   }

   uint32_t Vec2::operator()(Vec2 position)
   { return GetPosition(position, *this); }
   uint32_t Vec2::operator()(uint32_t X, uint32_t Y)
   { return GetPosition(Vec2(X, Y), *this);}
   Vec2 Vec2::operator+(Vec2 other)
   { return Vec2(this->X + other.X, this->Y + other.Y); }
   bool Vec2::IsInside(Vec2 end, Vec2 start)
   {
      if(this->X < start.X || this->X >= end.X)
         return false;
      if(this->Y < start.Y || this->Y >= end.Y)
         return false;
      return true;
   }
   
   uint32_t GetPosition(Vec2 position, Vec2 size)
   {
      return ((position.Y * size.X) + position.X);
   }
   Vec2 GetPosition(uint32_t position, Vec2 size)
   {
      return Vec2(
         static_cast<uint32_t>(position % size.X),
         static_cast<uint32_t>(position / size.X));
   }
   uint32_t GetSize(Vec2 size)
   {
      return (size.X * size.Y);
   }
}