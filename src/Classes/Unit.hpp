#pragma once

#include "Commons.hpp"
#include "Entity.hpp"

#include "ISerialize.hpp"

namespace Game
{
   class Unit : Entity, ISerialize<Unit>
   {
   private:
      const uint8_t side_ID;
   public:
      Unit();
      ~Unit();
   };
}