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

      this->GetWindowSize();
      uint32_t maxWindowSize = GetSize(Vec2(
         csbi.dwMaximumWindowSize.X + 1 - 1,
         csbi.dwMaximumWindowSize.Y));

      this->buffer = std::string(maxWindowSize, 'x');
      this->Update();
   }
   void Display::Update()
   {
      GetConsoleScreenBufferInfo(handle, &csbi);

      this->GetWindowSize();
      this->GetCursorPosition();

      this->ClearScreen();
      std::cout << buffer << std::endl;
   }

   void Display::ClearScreen()
   {
      system("cls");
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
   void SetCursorPosition(Vec2 position)
   {
      SetConsoleCursorPosition(
         handle,
         (COORD) {
         static_cast<short>(position.X),
         static_cast<short>(position.Y)
         });
   }

   void DrawBox();
   void DrawMap(Map &map);
   void DrawStatus();
   void DrawMenu();
}

#elif __linux__
// Linux

#endif