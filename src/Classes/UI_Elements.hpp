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

      void UpdateLine(uint16_t line_number, const std::string new_string);
      const std::string& GetLine(uint16_t line_number);
      uint16_t GetLineCount();
   };

   class UI_BoxText : public IElement
   {
   private:
      UI_Box box;
      
   protected:
      UI_Text text;

   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_BoxText(Vec2 _screen_pos, Vec2 _screen_size,
         const std::vector<std::string> _text,
          Vec2 _screen_padding = Vec2{0,0},
         UI_Text::Alignment _align = UI_Text::Alignment::Left);
      UI_BoxText() = delete;
   };

   class UI_Menu : public IElement
   {
   private:
      UI_Box box;
      UI_Text prompt;
      UI_Text options;
      UI_Text selector;

      uint16_t selected_option;
   public:

      void ChangeSelection(uint16_t new_value);
      void ChangeSelection(bool goUp);
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_Menu(Vec2 _screen_pos, Vec2 _screen_size,
         const std::vector<std::string> _options,
         const std::vector<std::string> _text = {""},
         bool _textFirst = true, Vec2 _padding = {1, 1},
         UI_Text::Alignment align = UI_Text::Alignment::Left);
      UI_Menu() = delete;
   };

   class UI_LoadBar : public UI_BoxText
   {
   private:
      uint16_t progress;
      uint16_t progress_goal;
      uint16_t progress_rate;
   public:
      void Draw(std::string& buffer, Vec2 screen_limit) override;

      UI_LoadBar(Vec2 _screen_pos, Vec2 _screen_size, uint16_t _goal, uint16_t _rate = 0);
      UI_LoadBar() = delete;

      bool IsCompleted();
      void ResetBar();
      void ChangeRate(uint16_t new_rate);
      uint8_t GetProgress();
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
      Selected    = '>',
      BarFill     = '#'
   };
}