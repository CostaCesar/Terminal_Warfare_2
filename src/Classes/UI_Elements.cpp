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

   UI_Box::UI_Box() : IElement({0, 0}, {0 , 0})
   {
     this->is_hollow = false;
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

   UI_Text::UI_Text() : IElement({0, 0}, {0 , 0})
   {
      this->align = Alignment::Center;
      this->lines = std::vector<std::string>(0);
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
   void UI_Text::UpdateLine(uint16_t line_number, const std::string new_string)
   {
      if(line_number < 0 || line_number > this->lines.size())
         throw std::invalid_argument("Line index outside of bounds!");

      this->lines[line_number] = new_string;
   }
   const std::string& UI_Text::GetLine(uint16_t line_number)
   {
      if(line_number < 0 || line_number > this->lines.size())
         throw std::invalid_argument("Line index outside of bounds!");

      return this->lines[line_number];
   }
   uint16_t UI_Text::GetLineCount()
   { return this->lines.size(); }

   UI_BoxText::UI_BoxText(Vec2 _screen_pos, Vec2 _screen_size,
      const std::vector<std::string> _text,
      Vec2 _screen_padding, UI_Text::Alignment _align)
   : IElement(_screen_pos, _screen_size)
   {
      this->box = UI_Box(_screen_pos, _screen_size);
      this->text = UI_Text(_screen_pos + (Vec2) {1,1} + _screen_padding, _screen_size - _screen_padding,_text, _align);
   }
   void UI_BoxText::Draw(std::string& buffer, Vec2 screen_limit)
   {
      this->box.Draw(buffer, screen_limit);
      this->text.Draw(buffer, screen_limit);
   }

   UI_Menu::UI_Menu(Vec2 _screen_pos, Vec2 _screen_size,
      const std::vector<std::string> _options,
      const std::vector<std::string> _text,
      bool _textFirst, Vec2 _padding , UI_Text::Alignment _align)
   : IElement(_screen_pos, _screen_size)
   {
      if(_options.size() < 1)
         throw std::invalid_argument("No options given to menu!");
      
      this->box = UI_Box(_screen_pos, _screen_size, false);
      
      Vec2 promp_pos = _screen_pos + Vec2{1, 1};
      Vec2 options_pos = _screen_pos + Vec2{1, 1};
      if(_textFirst)
         options_pos += Vec2{0, static_cast<uint32_t>(_options.size()) + 1};
      else promp_pos += Vec2{0, static_cast<uint32_t>(_options.size()) + 1};
      
      // To open space for the selector
      options_pos.X += 2;

      this->options = UI_Text(options_pos, _screen_size, _options, _align);
      this->prompt = UI_Text(promp_pos, _screen_size, _text, _align);

      this->selector = UI_Text(options_pos - Vec2{2, 0}, Vec2(2, _options.size()), std::vector<std::string>(_options.size(), "  "));
      this->selected_option = 0;
      this->ChangeSelection(this->selected_option);
   }
   void UI_Menu::ChangeSelection(uint16_t new_selection)
   {
      if(new_selection >= this->options.GetLineCount())
         throw std::invalid_argument("Selection outside bounds!");

      this->selector.UpdateLine(this->selected_option, "  ");
      this->selected_option = new_selection;
      this->selector.UpdateLine(this->selected_option, std::string(1, (char)Symbol::Selected) + " ");
   }
   void UI_Menu::ChangeSelection(bool goUp)
   {
      this->selector.UpdateLine(this->selected_option, "  ");
      
      if(goUp && this->selected_option == this->options.GetLineCount() - 1)
         this->selected_option = 0;
      else if (!goUp && this->selected_option == 0)
         this->selected_option = this->options.GetLineCount() - 1;
      else this->selected_option = (uint16_t) ((int) this->selected_option + (goUp ? 1 : -1));

      this->selector.UpdateLine(this->selected_option, std::string(1, (char)Symbol::Selected) + " ");
   }
   void UI_Menu::Draw(std::string& buffer, Vec2 screen_limit)
   {
      this->box.Draw(buffer, screen_limit);
      this->prompt.Draw(buffer, screen_limit);
      this->options.Draw(buffer, screen_limit);
      this->selector.Draw(buffer, screen_limit);
   };
}