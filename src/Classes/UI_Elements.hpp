#pragma once

#include <vector>
#include "Commons.hpp"

namespace Game
{
   class IElement
   {
   protected:
      Vec2 screen_pos;
      Vec2 screen_size;

   public:
      virtual void Draw(std::string& buffer, Vec2 screen_limit) = 0;

      IElement(Vec2 _screen_pos, Vec2 _screen_size);
      IElement() = delete;
   };

   class UI_Box : public IElement
   {
   private:
      bool is_hollow;

   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_Box(Vec2 _screen_pos, Vec2 _screen_size, bool _is_holow = false);
      UI_Box() = delete;
   };

   class UI_Text : public UI_Box
   {
   public:
      enum class Alignment
      {
         Right = 0,
         Center = 1,
         Left = 2
      };

   private:
      std::vector<std::string> lines;
      Alignment align;

   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_Text(Vec2 _screen_pos, Vec2 _screen_size, Alignment _align = Alignment::Left);
      UI_Text(Vec2 _screen_pos, Vec2 _screen_size, const std::vector<std::string>, Alignment _align = Alignment::Left);
      UI_Text() = delete;

   };

   enum class Symbol : uint8_t
   {
      Line_EW     = 205,// '═',
      Line_NS     = 186,// '║',
      Corner_NW   = 201,// '╔',
      Corner_SW   = 200,// '╚',
      Corner_SE   = 188,// '╝',
      Corner_NE   = 187,// '╗',
      Cross       = 206 // '╬'
   };
}