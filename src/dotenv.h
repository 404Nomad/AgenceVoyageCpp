#ifndef DOTENV_H
#define DOTENV_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <iostream>

class Dotenv {
public:
    static void load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier .env : " + filepath);
        }

        std::string line;
        while (std::getline(file, line)) {
            auto pos = line.find('=');
            if (pos == std::string::npos || line[0] == '#') {
                continue;
            }

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Supprime les espaces autour de la clé et de la valeur
            trim(key);
            trim(value);

            // Définit la variable d'environnement
            setenv(key.c_str(), value.c_str(), 1);
        }
        file.close();
    }

private:
    static void trim(std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        str = str.substr(first, (last - first + 1));
    }
};

#endif // DOTENV_H
