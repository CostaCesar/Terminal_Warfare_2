#pragma once

#include "Commons.hpp"
#include "ISerialize.hpp"

namespace Game
{
   class Unit : ISerialize<Unit>
   {
   private:
      const uint32_t unit_ID;
   public:
      Unit();
      ~Unit();
   };
}