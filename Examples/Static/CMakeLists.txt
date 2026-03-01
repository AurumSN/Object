add_executable(Static_ "Include/Terminal.h" "Source/Main.cpp" "Source/Terminal.cpp")

set_property(TARGET Static_ PROPERTY CXX_STANDARD 23)

target_include_directories(Static_ PUBLIC "Include")
target_link_libraries(Static_ PUBLIC Object)