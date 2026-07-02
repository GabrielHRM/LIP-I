#include "Cidade.h"

// Cria uma cidade com o nome informado
Cidade::Cidade(std::string nome) : nome(nome)
{
}

// Retorna o nome da cidade
std::string Cidade::getNome() const
{ 
    return nome;
}