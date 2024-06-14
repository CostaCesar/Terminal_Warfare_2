#include "UI_Elements.hpp"
#include <stdexcept>

namespace Game
{
   IElement::IElement(Vec2 _screen_pos, Vec2 _screen_size)
   {
      this->screen_pos = _screen_pos;
      this->screen_size = _screen_size;
   }

   UI_Box::UI_Box(Vec2 _screen_pos, Vec2 _screen_size, bool _is_holow) : IElement( _screen_pos, _screen_size)
   {
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

   UI_Text::UI_Text(Vec2 _screen_pos, Vec2 _screen_size) : UI_Box(_screen_pos, _screen_size, false)
   {
      this->lines.reserve(std::max<uint32_t>(_screen_size.Y - 2, 2));
   }
   void UI_Text::Draw(std::string& buffer, Vec2 screen_limit)
   {

   }
}