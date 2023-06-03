#pragma once
#include <string>
#include <fstream>
#include <sstream>

namespace Core {

    // Helper function to read shader source code from a file
    std::string ReadFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }

}