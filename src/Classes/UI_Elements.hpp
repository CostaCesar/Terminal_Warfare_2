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
      UI_Box();
   };

   class UI_Text : public IElement
   {
   public:
      enum class Alignment
      {
         Right = 0,
         Center = 1,
         Left = 2
      };

   private:
      Alignment align;
      std::vector<std::string> lines;


   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_Text(Vec2 _screen_pos, Vec2 _screen_size, Alignment _align);
      UI_Text(Vec2 _screen_pos, Vec2 _screen_size, const std::vector<std::string> _text, Alignment _align = Alignment::Left);
      UI_Text();

   };

   class UI_BoxText : public IElement
   {
   private:
      UI_Box box;
      UI_Text text;

   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_BoxText(Vec2 _screen_pos, Vec2 _screen_size,
         const std::vector<std::string> _text,
          Vec2 _screen_padding = Vec2{0,0},
         UI_Text::Alignment _align = UI_Text::Alignment::Left);
      UI_BoxText() = delete;
   };
   enum class Symbol : uint8_t
   {
      Line_EW     = 205,// '═',
      Line_NS     = 186,// '║',
      Corner_NW   = 201,// '╔',
      Corner_SW   = 200,// '╚',
      Corner_SE   = 188,// '╝',
      Corner_NE   = 187,// '╗',
      Cross       = 206,// '╬',
      Selected    = '>'
   };
}