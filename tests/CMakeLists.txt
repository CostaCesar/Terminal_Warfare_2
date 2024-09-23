include_directories(../src)

add_executable(Tag_Test Tag_Test.cpp)

target_link_libraries(Tag_Test PRIVATE Tag_Lib)

# target_link_libraries(Tag_Test PRIVATE Tag_Lib)
# target_include_directories(Tag_Test PRIVATE src)

add_test(UnitTests
   Tag_Test)