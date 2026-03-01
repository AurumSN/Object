add_executable(ThreadSafe "Source/Main.cpp" "Include/Counter.h" "Source/Counter.cpp" "Source/CounterImpl.h")

target_include_directories(ThreadSafe PUBLIC "Include")
target_link_libraries(ThreadSafe PUBLIC Object)