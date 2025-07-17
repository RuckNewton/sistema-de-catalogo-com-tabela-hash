#include "Utils.h"
#include <iostream>
#include <limits>

// construtor
tabelaHash::tabelaHash() : idContador(1)
{
    for (int i = 0; i < TAM; i++)
    {
        tabela[i] = nullptr;
    }
}

// destrutor
tabelaHash::~tabelaHash()
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

int tabelaHash::gerarHash(int id)
{
    return id % TAM;
}

void tabelaHash::addLivro()
{
    Livro novoLivro;
    novoLivro.id = idContador++;

    cout << "--- Adicionar novo livro ---" << endl;
    cout << "ID: " << novoLivro.id << endl;

    cout << "Título do livro: ";
    cin.ignore();
    getline(cin, novoLivro.nome);

    cout << "Categoria do livro (gênero): ";
    getline(cin, novoLivro.categoria);

    cout << "Autor: ";
    getline(cin, novoLivro.autor);

    inserirLivro(novoLivro);
}

void tabelaHash::inserirLivro(const Livro &novoLivro)
{
    int indice = gerarHash(novoLivro.id);
    No *novoNo = new No{novoLivro, nullptr};
    novoNo->prox = tabela[indice];
    tabela[indice] = novoNo;

    cout << "Livro '" << novoLivro.nome << "' (ID: " << novoLivro.id << ") inserido com sucesso!" << endl;
}

// ... Implementar aqui as outras funções: buscar, remover, editar, listar ...

void tabelaHash::buscarLivroPorID()
{
    int idBusca;
    cout << "\n--- Buscar Livro por ID ---" << endl;
    cout << "Digite o ID do livro que deseja buscar: ";
    cin >> idBusca;

    int indice = gerarHash(idBusca);
    No *atual = tabela[indice];
    bool encontrado = false;

    // Percorre a lista encadeada no índice calculado
    while (atual != nullptr)
    {
        if (atual->dadosLivro.id == idBusca)
        {
            cout << "\n--- Livro Encontrado ---" << endl;
            cout << "ID: " << atual->dadosLivro.id << endl;
            cout << "Título: " << atual->dadosLivro.nome << endl;
            cout << "Categoria: " << atual->dadosLivro.categoria << endl;
            cout << "Autor: " << atual->dadosLivro.autor << endl;
            cout << "------------------------" << endl;
            encontrado = true;
            break; // Achou o livro!
        }
        atual = atual->prox;
    }

    if (!encontrado)
    {
        cout << "\nLivro com ID " << idBusca << " não encontrado no catálogo." << endl;
    }
}

void tabelaHash::removerLivroPorID()
{
    int idBusca;
    cout << "\n--- Remover Livro por ID ---" << endl;
    cout << "Digite o ID do livro que deseja remover: ";
    cin >> idBusca;

    int indice = gerarHash(idBusca);
    No *atual = tabela[indice];
    No *anterior = nullptr;
    bool encontrado = false;

    // Percorre a lista para encontrar o nó a ser removido
    while (atual != nullptr)
    {
        if (atual->dadosLivro.id == idBusca)
        {
            // O nó a ser removido é o primeiro da lista
            if (anterior == nullptr)
            {
                tabela[indice] = atual->prox;
            }
            // O nó a ser removido no meio ou no fim
            else
            {
                anterior->prox = atual->prox;
            }

            cout << "\nLivro '" << atual->dadosLivro.nome << "' (ID: " << idBusca << ") removido com sucesso!" << endl;
            delete atual;
            encontrado = true;
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    if (!encontrado)
    {
        cout << "\nLivro com ID " << idBusca << " não encontrado. Nenhum livro foi removido." << endl;
    }
}

void tabelaHash::editarLivroPorID()
{
    int idBusca;
    cout << "\n--- Editar Livro por ID ---" << endl;
    cout << "Digite o ID do livro que deseja editar: ";
    cin >> idBusca;

    int indice = gerarHash(idBusca);
    No *atual = tabela[indice];
    bool encontrado = false;

    // Percorre a lista para encontrar o nó a ser editado
    while (atual != nullptr)
    {
        if (atual->dadosLivro.id == idBusca)
        {
            encontrado = true;
            cout << "\n--- Livro Encontrado ---" << endl;
            cout << "ID: " << atual->dadosLivro.id << " (não pode ser alterado)" << endl;
            cout << "1. Título Atual: " << atual->dadosLivro.nome << endl;
            cout << "2. Categoria Atual: " << atual->dadosLivro.categoria << endl;
            cout << "3. Autor Atual: " << atual->dadosLivro.autor << endl;
            cout << "------------------------" << endl;

            int opcao;
            cout << "Qual campo deseja editar? (1-3, ou 0 para cancelar): ";
            cin >> opcao;

            // Limpa o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcao)
            {
            case 1:
                cout << "Digite o novo título: ";
                getline(cin, atual->dadosLivro.nome);
                cout << "Título atualizado com sucesso!" << endl;
                break;
            case 2:
                cout << "Digite a nova categoria: ";
                getline(cin, atual->dadosLivro.categoria);
                cout << "Categoria atualizada com sucesso!" << endl;
                break;
            case 3:
                cout << "Digite o novo autor: ";
                getline(cin, atual->dadosLivro.autor);
                cout << "Autor atualizado com sucesso!" << endl;
                break;
            case 0:
                cout << "Edição cancelada." << endl;
                break;
            default:
                cout << "Opção inválida. Nenhuma alteração foi feita." << endl;
                break;
            }
            break;
        }
        atual = atual->prox;
    }

    if (!encontrado)
    {
        cout << "\nLivro com ID " << idBusca << " não encontrado no catálogo." << endl;
    }
}

void tabelaHash::listarTodos()
{
    cout << "\n--- Listando todos os livros do Catálogo ---" << endl;
    bool catalogoVazio = true;

    // Percorre todo o vetor principal da tabela hash
    for (int i = 0; i < TAM; i++)
    {

        if (tabela[i] != nullptr)
        {
            catalogoVazio = false;
            No *atual = tabela[i];

            // Percorre a lista encadeada daquela posição
            while (atual != nullptr)
            {
                cout << "------------------------" << endl;
                cout << "Índice na Tabela: " << i << endl;
                cout << "ID: " << atual->dadosLivro.id << endl;
                cout << "Título: " << atual->dadosLivro.nome << endl;
                cout << "Categoria: " << atual->dadosLivro.categoria << endl;
                cout << "Autor: " << atual->dadosLivro.autor << endl;

                atual = atual->prox;
            }
        }
    }

    if (catalogoVazio)
    {
        cout << "\nO catálogo está vazio. Não há nenhum livro para listar." << endl;
    } else {
        cout << "------------------------" << endl;
        cout << "--- Fim da Lista ---" << endl;
    }
}

void tabelaHash::exibirMenu()
{
    cout << "\n--- Sistema de Catálogo de Livros ---" << endl;
    cout << "1. Inserir um novo livro" << endl;
    cout << "2. Buscar um livro pelo ID" << endl;
    cout << "3. Remover um livro pelo ID" << endl;
    cout << "4. Editar os dados de um livro" << endl;
    cout << "5. Listar todos os livros" << endl;
    cout << "0. Sair do sistema" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Escolha uma opção: ";
}