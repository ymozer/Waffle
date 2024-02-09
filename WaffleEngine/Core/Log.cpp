#include "Log.hpp"
#include <iostream>

void Log::Init() {
    // Initialize logging mechanisms, if any
}

void Log::Print(const char* message) {
    std::cout << message << std::endl;
}
