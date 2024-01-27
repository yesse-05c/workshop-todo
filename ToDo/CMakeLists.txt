# CMakeList.txt : CMake project for BigToDo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (todo_lib "console.cpp" "include/console.hpp" "db.cpp" "include/db.hpp" "include/todo.hpp" "todo.cpp" "include/types.hpp")
target_include_directories (todo_lib PUBLIC "include")

add_executable (todo "main.cpp")
target_link_libraries (todo todo_lib)

# TODO: Add tests and install targets if needed.
