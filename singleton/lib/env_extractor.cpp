#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "env_extractor.hpp"

void load_env(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key   = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        setenv(key.c_str(), value.c_str(), 1); // 1 = overwrite
    }
}