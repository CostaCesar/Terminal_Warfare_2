#pragma once

#include "Commons.hpp"

namespace Game
{
   enum class EntityType
   {
      Entity = 0,
      Unit = 1,
      Building = 2
   };
   
   class Entity
   {
   private:
      const uint32_t game_ID;
      const EntityType type;
      
      Vec2 position;
      
   public:
      Entity() : game_ID(0), type(EntityType::Entity)
      {}
      ~Entity()
      {}

      ExitCode Interact(Entity* initiator);
   };
}