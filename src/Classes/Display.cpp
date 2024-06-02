#include "Display.hpp"

#include <iostream>

#ifdef _WIN32
// Windows
#include "Windows.h"

namespace Game
{
   HANDLE handle;
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   Display::Display()
   {
      Initialise();
   }
   Display::~Display()
   {
      handle = nullptr;
      csbi = {0};
   }

   void Display::Initialise()
   {
      handle = GetStdHandle(STD_OUTPUT_HANDLE);
      GetConsoleScreenBufferInfo(handle, &csbi);

      ShowScrollBar(GetConsoleWindow(), SB_VERT, false);
      this->ToggleCursor(false);
      
      this->GetWindowSize();
      this->CreateBuffer();
   
      this->Update();
   }
   void Display::Update()
   {
      GetConsoleScreenBufferInfo(handle, &csbi);

      this->GetWindowSize();
      this->GetCursorPosition();

      if(this->HasChangedSize())
      {
         this->ClearScreen();
         this->CreateBuffer();
      }

      this->ToggleCursor(false);
      std::cout << buffer;
      
      this->SetCursorPosition((Vec2) {0, 0});
   }

   void Display::CreateBuffer()
   {
      uint32_t buffer_size = GetSize(window_size) - 1;
      this->buffer = std::string(buffer_size, 'x');
      
      for(int i = 1; i < window_size.Y; i++)
         buffer[(i * window_size.X) - 1] = '\n';

      return;
   }
   void Display::ClearScreen()
   {
      system("cls");
      this->SetCursorPosition((Vec2) {0, 0});
   }
   void Display::GetWindowSize()
   {
      this->window_size = Vec2{
         static_cast<uint32_t>(csbi.dwSize.X),
         static_cast<uint32_t>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
         };
   }
   void Display::GetCursorPosition()
   {
      this->cursor_pos = Vec2{
         static_cast<uint32_t>(csbi.dwCursorPosition.X),
         static_cast<uint32_t>(csbi.dwCursorPosition.Y)
         };
   }
   void Display::SetCursorPosition(Vec2 position)
   {
      SetConsoleCursorPosition(
         handle,
         (COORD) {
         static_cast<short>(position.X),
         static_cast<short>(position.Y)
         });
   }
   void Display::ToggleCursor(bool show)
   {
      CONSOLE_CURSOR_INFO info;
      info.dwSize = 100;
      info.bVisible = show;
      SetConsoleCursorInfo(handle, &info);
   }

   void Display::DrawBox(Vec2 position, Vec2 size, bool hollow)
   {
      size.X--, size.Y--;
      if(!position.IsInside(window_size))
         throw std::out_of_range("Box's start position out of screen!");
      Vec2 end = Vec2(position + size);
      if(!end.IsInside(window_size))
         throw std::out_of_range("Box's start position out of screen!");
      
      buffer[window_size(position)] = (char) Symbol::Corner_NW;
      for(int i = window_size(position) + 1; i < window_size(end.X, position.Y); i++)  
         buffer[i] = (char) Symbol::Line_EW;
      buffer[window_size(end.X, position.Y)] = (char) Symbol::Corner_NE;

      for(int col = 1; col < size.Y; col++)
      {
         buffer[window_size(position.X, position.Y + col)] = (char) Symbol::Line_NS;
         if(!hollow)
         {
            for(int i = window_size(position.X, position.Y + col) + 1; i < window_size(end.X, position.Y + col) - 1; i++)
               buffer[i] = ' ';
         }
         buffer[window_size(end.X, position.Y + col)] = (char) Symbol::Line_NS;
      }

      buffer[window_size(position.X, end.Y)] = (char) Symbol::Corner_SW;
      for(int i = window_size(position.X, end.Y) + 1; i < window_size(end); i++)  
         buffer[i] = (char) Symbol::Line_EW;
      buffer[window_size(end)] = (char) Symbol::Corner_SE;

      return;
   }

   void DrawMap(Map &map);
   void DrawStatus();
   void DrawMenu();
}

#elif __linux__
// Linux

#endif