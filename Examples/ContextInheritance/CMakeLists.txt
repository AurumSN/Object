add_executable(ContextInheritance "Source/Main.cpp" "Include/CommandQueue.h" "Source/CommandQueue.cpp" "Source/CommandQueueImpl.h")

set_property(TARGET ContextInheritance PROPERTY CXX_STANDARD 23)

target_include_directories(ContextInheritance PUBLIC "Include")
target_link_libraries(ContextInheritance PUBLIC Object)