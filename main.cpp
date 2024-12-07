#include "include/Assento.h"
#include "include/Passageiro.h"
#include "include/Tripulacao.h"
#include "include/Voo.h"
#include <iostream>



#include <iostream>

using namespace std;

// Fun��es auxiliares para o sub-menu de passageiros
void menuPassageiros() {
    int opcao;
    do {
        cout << "\n--- Gerenciamento de Passageiros ---\n";
        cout << "1. Adicionar Passageiro\n";
        cout << "2. Listar Passageiros\n";
        cout << "3. Atualizar Passageiro\n";
        cout << "4. Deletar Passageiro\n";
        cout << "5. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {
            int codigo;
            char nome[TAM_NOME], endereco[TAM_ENDERECO], telefone[TAM_TELEFONE];
            bool fidelidade;
            cout << "\nDigite os dados do passageiro:\n";
            cout << "C�digo: ";
            cin >> codigo;
            cin.ignore(); // Limpar o buffer
            cout << "Nome: ";
            cin.getline(nome, TAM_NOME);
            cout << "Endere�o: ";
            cin.getline(endereco, TAM_ENDERECO);
            cout << "Telefone: ";
            cin.getline(telefone, TAM_TELEFONE);
            cout << "Fidelidade (1 para Sim, 0 para N�o): ";
            cin >> fidelidade;

            Passageiro p(codigo, nome, endereco, telefone, fidelidade);
            if (Passageiro::adicionarPassageiro(p)) {
                cout << "Passageiro adicionado com sucesso!\n";
            } else {
                cout << "Erro ao adicionar passageiro. Lista cheia!\n";
            }
            break;
        }
        case 2:
            cout << "\nLista de Passageiros:\n";
            Passageiro::listarPassageiros();
            break;

        case 3: {
            int codigo;
            cout << "\nDigite o codigo do passageiro que deseja atualizar: ";
            cin >> codigo;

            Passageiro* passageiro = Passageiro::buscarPorCodigo(codigo);
            if (passageiro) {
                char nome[TAM_NOME], endereco[TAM_ENDERECO], telefone[TAM_TELEFONE];
                bool fidelidade;
                cout << "Digite os novos dados do passageiro:\n";
                cin.ignore(); // Limpar o buffer
                cout << "Nome: ";
                cin.getline(nome, TAM_NOME);
                cout << "Endere�o: ";
                cin.getline(endereco, TAM_ENDERECO);
                cout << "Telefone: ";
                cin.getline(telefone, TAM_TELEFONE);
                cout << "Fidelidade (1 para Sim, 0 para N�o): ";
                cin >> fidelidade;


                passageiro->setNome(nome);
                passageiro->setEndereco(endereco);
                passageiro->setTelefone(telefone);
                passageiro->setFidelidade(fidelidade);
                cout << "Passageiro atualizado com sucesso!\n";
            } else {
                cout << "Passageiro com o codigo " << codigo << " nao encontrado.\n";
            }
            break;
        }

        case 4: {
            int codigo;
            cout << "\nDigite o codigo do passageiro que deseja deletar: ";
            cin >> codigo;
            if (Passageiro::deletarPassageiro(codigo)) {
                cout << "Passageiro deletado com sucesso!\n";
            } else {
                cout << "Passageiro com o codigo " << codigo << " nao encontrado.\n";
            }
            break;
        }

        case 5:
            cout << "Voltando ao menu principal...\n";
            break;

        default:
            cout << "Op��o invalida. Tente novamente.\n";
        }
    } while (opcao != 5);
}

// Fun��es auxiliares para o sub-menu de tripulantes
void menuTripulantes() {
    int opcao;
    do {
        cout << "\n--- Gerenciamento de Tripulantes ---\n";
        cout << "1. Adicionar Tripulante\n";
        cout << "2. Listar Tripulantes\n";
        cout << "3. Atualizar Tripulante\n";
        cout << "4. Deletar Tripulante\n";
        cout << "5. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {
            int codigo,cargo;
            char nome[TAM_NOME], endereco[TAM_ENDERECO], telefone[TAM_TELEFONE];

            cout << "\nDigite os dados do tripulante:\n";
            cout << "C�digo: ";
            cin >> codigo;
            cin.ignore(); // Limpar o buffer
            cout << "Nome: ";
            cin.getline(nome, TAM_NOME);
            cout << "Endere�o: ";
            cin.getline(endereco, TAM_ENDERECO);
            cout << "Telefone: ";
            cin.getline(telefone, TAM_TELEFONE);
            cout << "Cargo (1-Piloto) (2-Copiloto) (3-Comissario): ";
            cin>>cargo;

            Tripulacao t(codigo, nome, endereco, telefone, cargo);
            if (Tripulacao::adicionarTripulante(t)) {
                cout << "Tripulante adicionado com sucesso!\n";
            } else {
                cout << "Erro ao adicionar tripulante\n";
            }
            break;
        }
        case 2:
            cout << "\nLista de Tripulantes:\n";
            Tripulacao::listarTripulantes();
            break;

        case 3: {
            int codigo;
            cout << "\nDigite o codigo do tripulante que deseja atualizar: ";
            cin >> codigo;

            Tripulacao* tripulante = Tripulacao::buscarPorCodigo(codigo);
            if (tripulante) {
                int cargo;
                char nome[TAM_NOME], endereco[TAM_ENDERECO], telefone[TAM_TELEFONE];

                cout << "Digite os novos dados do tripulante:\n";
                cin.ignore(); // Limpar o buffer
                cout << "Nome: ";
                cin.getline(nome, TAM_NOME);
                cout << "Endere�o: ";
                cin.getline(endereco, TAM_ENDERECO);
                cout << "Telefone: ";
                cin.getline(telefone, TAM_TELEFONE);
                cout << "Cargo (1-Piloto) (2-Copiloto) (3-Comissario): ";
                cin>>cargo;


                tripulante->setNome(nome);
                tripulante->setEndereco(endereco);
                tripulante->setTelefone(telefone);
                tripulante->setCargo(cargo);
                cout << "Tripulante atualizado com sucesso!\n";
            } else {
                cout << "Tripulante com o codigo " << codigo << " nao encontrado.\n";
            }
            break;
        }

        case 4: {
            int codigo;
            cout << "\nDigite o codigo do tripulante que deseja deletar: ";
            cin >> codigo;
            if (Tripulacao::deletarTripulante(codigo)) {
                cout << "Tripulante deletado com sucesso!\n";
            } else {
                cout << "Tripulante com o codigo " << codigo << " nao encontrado.\n";
            }
            break;
        }

        case 5:
            cout << "Voltando ao menu principal...\n";
            break;

        default:
            cout << "Op��o invalida. Tente novamente.\n";
        }
    } while (opcao != 5);
}





void menuVoo() {
    int opcao;
    do {
        cout << "\n--- Gerenciamento de Voos ---\n";
        cout << "1. Adicionar Voo\n";
        cout << "2. Listar Voos\n";
        cout << "3. Atualizar Voo\n";
        cout << "4. Deletar Voo\n";
        cout << "5. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {
               Voo::cadastrarVoo();

        }
        case 2:
            {
            cout << "Listando voos cadastrados:" << endl;
            Voo::listarVoos();
            break;
        }
        case 3: {
            // Atualizando um voo
            int codigoAtualizar;
            cout << "Digite o c�digo do voo a ser atualizado: ";
            cin >> codigoAtualizar;
            Voo::atualizarVoo(codigoAtualizar);  // Atualiza o voo com o c�digo fornecido
            break;
        }

        case 4: {

            // Deletando um voo
            int codigoDeletar;
            cout << "Digite o c�digo do voo a ser deletado: ";
            cin >> codigoDeletar;
            Voo::deletarVoo(codigoDeletar);  // Deleta o voo com o c�digo fornecido
            break;
        }

        case 5:
            cout << "Voltando ao menu principal...\n";
            break;

        default:
            cout << "Op��o invalida. Tente novamente.\n";
        }
    } while (opcao != 5);
}



void menuAssentos() {
    int opcao;
    do {
        cout << "\n--- Gerenciamento de Voos ---\n";
        cout << "1. Adicionar assento\n";
        cout << "2. Atualizar assento\n";
        cout << "3. Deletar assento\n";
        cout << "4. Listar Assentos\n";
        cout << "5. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {

                Assento::CadastrarAssento();
                break;
        }
        case 2:
            {
                int a;
                cout<<"Qual o assento a ser atualizado"<<endl;
                cin>>a;

                Assento* AttAss = Assento::buscarporId(a);
                if(AttAss== nullptr){
                    cout<<"Assento nao encontrado"<<endl;
                    break;
                }
                AttAss->AtualizarAssento();
                break;

        }
        case 3: {

                int num;
                cout << "Digite o numero do assento: ";
                cin>>num;
                Assento::Deletar(num);
             break;
        }

        case 4: {
                Assento::ListarAssentos();
            break;
        }
        case 5:{
             cout << "Voltando ao menu principal...\n";
            break;
        }


        default:
            cout << "Op��o invalida. Tente novamente.\n";
        }
    } while (opcao != 5);
}








int main() {
    int opcao;

    do {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Gerenciar Passageiros\n";
        cout << "2. Gerenciar Tripulantes\n";
        cout << "3. Gerenciar Voos\n";  // Nova op��o de submenu para voos
        cout << "4. Gerenciar Assentos\n";
        cout << "5. Sair\n";
        cout << "Escolha uma op��o: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            menuPassageiros();
            break;
        case 2:
            menuTripulantes();
            break;
        case 3:{
            menuVoo();
            break;
        case 4:
            menuAssentos();
            break;
        case 5:

            break;
        default:
            cout << "Op��o inv�lida. Tente novamente.\n";
        }
        }
    } while (opcao != 5);

    return 0;
}

