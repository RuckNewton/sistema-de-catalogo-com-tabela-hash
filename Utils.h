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
    void removerLivroPorID(); // Função a ser criada
    void editarLivroPorID();  // Função a ser criada
    void listarTodos();       // Função a ser criada
    void exibirMenu();        // Função a ser criada
};

#endif