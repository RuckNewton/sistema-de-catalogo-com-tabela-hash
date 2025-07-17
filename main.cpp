#include "Utils.h"

int main() {
    tabelaHash catalogo;
    int opcao;

    do {
        catalogo.exibirMenu(); // Função que mostra as opções
        cin >> opcao;

        switch (opcao) {
            case 1:
                catalogo.addLivro();
                break;
            case 2:
                catalogo.buscarLivroPorID();
                break;
            case 3:
                catalogo.removerLivroPorID();
                break;
            case 4:
                catalogo.editarLivroPorID();
                break;
            case 5:
                catalogo.listarTodos();
                break;
            case 0:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}