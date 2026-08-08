cmake_minimum_required(VERSION 3.14)
project(LogicSimulator)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)
add_executable(MySimulator src/main.cpp)
# Notice we link against both ftxui AND our logic_core engine!
target_link_libraries(MySimulator PRIVATE logic_core ftxui::screen ftxui::dom ftxui::component)