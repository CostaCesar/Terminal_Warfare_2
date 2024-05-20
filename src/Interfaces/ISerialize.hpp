#pragma once

#include "Commons.hpp"

#include <fstream>

namespace Game
{
   template <typename T>
   class ISerialize
   {
   private:

   public:
      static void SaveToFile(T &object, std::ofstream &file);
      static T& LoadFromFile(std::ifstream &file);
   };
}
