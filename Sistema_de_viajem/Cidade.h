#ifndef CIDADE_H
#define CIDADE_H

#include <string>

// Representa uma cidade no sistema
class Cidade {
private:
    std::string nome; // Nome da cidade

public:
    Cidade(std::string nome);
    std::string getNome() const;
};

#endif