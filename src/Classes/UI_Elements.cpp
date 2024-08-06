#include "UI_Elements.hpp"
#include <stdexcept>
#
namespace Game
{
   IElement::IElement(Vec2 _screen_pos, Vec2 _screen_size)
   {
      this->screen_pos = _screen_pos;
      this->screen_size = _screen_size;
   }

   UI_Box::UI_Box(Vec2 _screen_pos, Vec2 _screen_size,bool _is_holow)
   : IElement( _screen_pos, _screen_size)
   {
      if(_screen_size.X < 2 || _screen_size.Y < 2)
         throw std::invalid_argument("Box container has insuficient size!");

      this->is_hollow = _is_holow;
   }
   void UI_Box::Draw(std::string& buffer, Vec2 screen_limit)
   {
      screen_size.X--, screen_size.Y--;
      if(!screen_pos.IsInside(screen_limit))
         throw std::out_of_range("Box's start screen_pos out of screen!");
      Vec2 end = Vec2(screen_pos + screen_size);
      if(!end.IsInside(screen_limit))
         throw std::out_of_range("Box's start screen_pos out of screen!");

      buffer[screen_limit(screen_pos)] = (char) Symbol::Corner_NW;
      for(int i = screen_limit(screen_pos) + 1; i < screen_limit(end.X, screen_pos.Y); i++)
         buffer[i] = (char) Symbol::Line_EW;
      buffer[screen_limit(end.X, screen_pos.Y)] = (char) Symbol::Corner_NE;

      for(int col = 1; col < screen_size.Y; col++)
      {
         buffer[screen_limit(screen_pos.X, screen_pos.Y + col)] = (char) Symbol::Line_NS;
         if(!is_hollow)
         {
            for(int i = screen_limit(screen_pos.X, screen_pos.Y + col) + 1; i < screen_limit(end.X, screen_pos.Y + col); i++)
               buffer[i] = ' ';
         }
         buffer[screen_limit(end.X, screen_pos.Y + col)] = (char) Symbol::Line_NS;
      }

      buffer[screen_limit(screen_pos.X, end.Y)] = (char) Symbol::Corner_SW;
      for(int i = screen_limit(screen_pos.X, end.Y) + 1; i < screen_limit(end); i++)
         buffer[i] = (char) Symbol::Line_EW;
      buffer[screen_limit(end)] = (char) Symbol::Corner_SE;

      screen_size.X++, screen_size.Y++;
      return;
   }

   UI_Text::UI_Text(Vec2 _screen_pos, Vec2 _screen_size, Alignment _align)
   : IElement(_screen_pos, _screen_size)
   {
      if(_screen_size.Y < 3)
         throw std::invalid_argument("Text container has insuficient lines inside it!");

      this->lines.reserve(_screen_size.Y-2);
      this->align = _align;
   }
   UI_Text::UI_Text(Vec2 _screen_pos, Vec2 _screen_size,
   const std::vector<std::string> text, Alignment _align)
   : IElement(_screen_pos, _screen_size)
   {
      if(_screen_size.Y < 3)
         throw std::invalid_argument("Text container has insuficient lines inside it!");

      this->align = _align;
      this->lines = text;
   }
   void UI_Text::Draw(std::string& buffer, Vec2 screen_limit)
   {
      Vec2 textPos = {screen_pos.X, screen_pos.Y};

      for (auto const &line : lines)
      {
         uint32_t linePos = 0;
         switch (align)
         {
         case Alignment::Left:
            linePos = screen_limit(textPos);
            break;
         case Alignment::Center:
            linePos = (screen_limit((textPos.X + (screen_size.X / 2)), textPos.Y))
               - (line.length() / 2);
            break;
         case Alignment::Right:
            linePos = screen_limit(textPos.X + screen_size.X, textPos.Y)
               - line.length();
            break;
         }
         buffer.replace(linePos, line.length(), line);
         textPos.Y++;
      }

   }

   UI_BoxText::UI_BoxText(Vec2 _screen_pos, Vec2 _screen_size,
      const std::vector<std::string> _text,
      Vec2 _screen_padding, UI_Text::Alignment _align)
   : IElement(_screen_pos, _screen_size),
      box(_screen_pos, _screen_size),
      text(_screen_pos + (Vec2) {1,1} + _screen_padding, _screen_size - _screen_padding,_text, _align)
   { }
   void UI_BoxText::Draw(std::string& buffer, Vec2 screen_limit)
   {
      this->box.Draw(buffer, screen_limit);
      this->text.Draw(buffer, screen_limit);
   }

}