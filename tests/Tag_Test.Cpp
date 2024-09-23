#include "Classes/Tag.hpp"
#include <iostream>
#include <cstring>

#ifdef _WIN32
   #define __FILENAME__ (strrchr("\\" __FILE__, '\\') + 1)
#else
   #define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#endif

static uint64_t test_count = 0;

void _Assert(bool condition, std::string line = "Unspecified Line")
{
   if(!condition)
   {
      std::cout << "[" << std::to_string(test_count) << "] Assertion failed at " << line << std::endl;
      std::cout << "> Failed after " << std::to_string(test_count) << " tests" << std::endl;
      exit(1);
   }
   else test_count++;
}
#define ASSERT(x) _Assert(x, std::to_string(__LINE__))

using namespace Game;

int main(int argc, char const *argv[])
{
   std::cout << "> Testing with: " << std::string(__FILENAME__) << std::endl;
   const int count = 10;
   
   Tag myTag = Tag();
   ASSERT(myTag.tag_id == INT32_MAX);

   Tag_Container tags;
   ASSERT(tags.GetSize() == 0);

   for (int i = 1; i < count; i++)
   {
      Tag a = Tag("Test tag", i, static_cast<uint32_t>(2 << i));
      tags[a] = a;
      ASSERT(tags[a] == a);
      ASSERT(tags.GetSize() == i);

      std::cout << tags[a].ToString() << std::endl;
   }

   Tag_Container buffer = tags;
   for(auto &&x : buffer)
   {
      x.second.SetValue(5 << x.first);
      ASSERT(tags[x.second].GetValue() != buffer[x.second].GetValue());
   }
   tags = buffer;
   for(auto &&x : buffer)
   {
      ASSERT(tags[x.second].GetValue() == (5 << x.first));
   }

   Tag toAdd("Added tag", 2, 10101010);
   tags[toAdd] = toAdd;
   ASSERT(tags[toAdd].GetValue() == toAdd.GetValue());
   
   std::cout << "> " << std::to_string(test_count) << " tests have passed" << std::endl;
   return 0;
}
