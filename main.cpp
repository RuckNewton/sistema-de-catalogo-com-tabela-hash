#include <iostream>
#include <string>
using namespace std;

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

const int TAM = 101;

struct tabelaHash
{
    No *tabela[TAM];
    int idContador;

    tabelaHash() : idContador(1)
    {
        for (int i = 0; i < TAM; i++)
        {
            tabela[i] = nullptr;
        }
    }
    // destrutor
    ~tabelaHash()
    {
        for (int i = 0; i < TAM; i++)
        {
            No *atual = tabela[i];
            while (atual != nullptr)
            {
                No *proximo = atual->prox;
                delete atual;
                atual = proximo;
            }
        }
    }

    int gerarHash(int id)
    {
        return id % TAM;
    }

    void addLivro()
    {
        Livro novoLivro;
        novoLivro.id = idContador++;

        cout << "--- Adicionar novo livro ---" << endl;
        cout << "ID: " << novoLivro.id << endl;

        cout << "Título do livro: ";
        getline(cin >> ws, novoLivro.nome);

        cout << "Categoria do livro (gênero): ";
        getline(cin >> ws, novoLivro.categoria);

        cout << "Autor: ";
        getline(cin >> ws, novoLivro.autor);

        inserirLivro(novoLivro);
    }

    void inserirLivro(const Livro &novoLivro)
    {
        int indice = gerarHash(novoLivro.id);
        No *novoNo = new No{novoLivro, nullptr};
        novoNo->prox = tabela[indice];
        tabela[indice] = novoNo;

        cout << "Livro '" << novoLivro.nome << "' (ID: " << novoLivro.id << ") inserido com sucesso!" << endl;
    }
};