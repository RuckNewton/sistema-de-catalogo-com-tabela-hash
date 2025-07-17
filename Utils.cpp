#include "Utils.h"

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