#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

using namespace std;

const int TAM = 101;

struct Livro
{
    int id;
    string nome;
    string categoria;
    string autor;
};

struct No
{
    Livro dadosLivro;
    No *prox;
};

struct tabelaHash
{
    No *tabela[TAM];
    int idContador;

    // Construtor e Destrutor
    tabelaHash();
    ~tabelaHash();

    // Protótipos das Funções
    int gerarHash(int id);
    void inserirLivro(const Livro &novoLivro);
    void addLivro();
    void buscarLivroPorID();
    void removerLivroPorID(); 
    void editarLivroPorID();  
    void listarTodos();      
    void exibirMenu();
};

#endif