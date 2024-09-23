#pragma once

#include "Commons.hpp"
#include <unordered_map>

namespace Game
{
   class Tag
   {
   private:
      uint32_t value;
   public:
      const std::string name;
      const uint32_t tag_id;

      Tag(std::string _name, uint32_t _tag_id, uint32_t _value = 0);
      Tag();
      
      uint32_t GetValue();
      void SetValue(uint32_t new_value);

      std::string ToString();

      Tag& operator =(const Game::Tag &);
      bool operator ==(const Tag& target);
      bool operator !=(const Tag& target);
   };

   class Tag_Container
   {
   private:
      std::unordered_map<uint32_t, Tag> data;

   
   public:
      Tag_Container();

      uint32_t GetSize();
      void Remove(const Tag& target);
      bool Contains(const Tag& target) const;

      bool operator ==(const Tag& target) const;
      bool operator ==(const Tag_Container& target) const;
      
      Tag operator [](Tag key) const;
      Tag &operator [](Tag key);

      std::unordered_map<uint32_t, Game::Tag>::iterator begin();
      std::unordered_map<uint32_t, Game::Tag>::iterator end();
   };
}
