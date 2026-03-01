add_executable(Inheritance "Source/Main.cpp" "Include/Transport.h" "Source/Transport.cpp" "Source/TransportImpl.h")

target_include_directories(Inheritance PUBLIC "Include")
target_link_libraries(Inheritance PUBLIC Object)