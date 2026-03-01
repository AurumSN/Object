add_executable(Context "Include/Directory.h" "Include/File.h" "Source/Main.cpp" "Source/DirectoryImpl.h" "Source/Directory.cpp" "Source/FileImpl.h" "Source/File.cpp")

set_property(TARGET Context PROPERTY CXX_STANDARD 23)

target_include_directories(Context PUBLIC "Include")
target_link_libraries(Context PUBLIC Object)