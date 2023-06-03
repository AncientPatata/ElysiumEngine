#include "Utils.h"


// Helper function to read shader source code from a file
std::string Core::ReadFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}
