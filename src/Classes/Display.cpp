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
      for (auto &&ui_element : elements)
      {
         ui_element->Draw(buffer, window_size);
      }
      

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

   void Display::AddElement(IElement *element)
   {
      elements.push_back(element);
   }
   void DrawMap(Map &map);
   void DrawStatus();
   void DrawMenu();
}

#elif __linux__
// Linux

#endif