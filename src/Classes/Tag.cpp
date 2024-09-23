#include "Tag.hpp"
#include <sstream>

namespace Game
{
   Tag::Tag() : tag_id(INT32_MAX), name("NULL")
   {
      this->value = 0;
   }

   Tag::Tag(std::string _name, uint32_t _tag_id, uint32_t _value)
   : tag_id(_tag_id), name(_name)
   {
      this->value = _value;
   }

   uint32_t Tag::GetValue()
   { return this->value; }

   void Tag::SetValue(uint32_t new_value)
   { this->value = new_value; }

   std::string Tag::ToString()
   {
      std::ostringstream output;
      output << "[" << std::to_string(this->tag_id) << "] ";
      output << this->name << ": ";
      output << std::to_string(this->value);
      return output.str();
   }

   bool Tag::operator ==(const Tag& target)
   { return target.tag_id == this->tag_id; }
   bool Tag::operator !=(const Tag& target)
   { return !((*this) == target); }
   
   Tag& Tag::operator =(const Tag& source)
   {
      if(this == &source) return *this;

      this->~Tag();
      return *new (this) Tag(source);
   }


   Tag_Container::Tag_Container()
   { 
      this->data = std::unordered_map<uint32_t, Tag>();
   }

   uint32_t Tag_Container::GetSize()
   { return this->data.size(); }
   bool Tag_Container::Contains(const Tag& target) const
   { return (this->data.find(target.tag_id) == this->data.end()); }

   void Tag_Container::Remove(const Tag& target)
   {
      if(!this->Contains(target)) return;
      this->data.erase(target.tag_id);
   }

   bool Tag_Container::operator ==(const Tag& target) const
   { return this->Contains(target); }

   bool Tag_Container::operator ==(const Tag_Container& target) const
   {
      if(this->data.size() != target.data.size()) return false;

      for (auto &&i : this->data)
      {
         if(!target.Contains(i.second)) return false;
      }
      return true;
   }

   Tag Tag_Container::operator [](Tag key) const
   {
      if(!this->Contains(key)) return Tag();

      return data.at(key.tag_id);
   }

   Tag &Tag_Container::operator [](Tag key)
   {
      return this->data[key.tag_id];
   }

   std::unordered_map<uint32_t, Game::Tag>::iterator Tag_Container::begin()
   { return this->data.begin(); }
   std::unordered_map<uint32_t, Game::Tag>::iterator Tag_Container::end()
   { return this->data.end(); }
}