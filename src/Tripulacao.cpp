#include <iostream>
#include <cstring>  // Para funções de string como strcpy, strcmp
#include "include/Tripulacao.h"

using namespace std;

const int PILOTO = 1;
const int COPILOTO = 2;
const int COMISSARIO = 3;

// Inicialização do vetor estático e da quantidade
Tripulacao Tripulacao::listaTripulantes[MAX_TRIPULANTES];

int Tripulacao::quantidade = 0;

// Construtor padrão
Tripulacao::Tripulacao() : codigo(0), cargo(0) {
    strcpy(nome, "");
    strcpy(endereco, "");
    strcpy(telefone, "");
}

// Construtor com parâmetros
Tripulacao::Tripulacao(int cod, const char* n, const char* end, const char* tel, int c) {
    setCodigo(cod);
    setNome(n);
    setEndereco(end);
    setTelefone(tel);
    setCargo(c);  // Agora espera um int (1 - Piloto, 2 - Copiloto, 3 - Comissário)
}

// Adicionar tripulante
bool Tripulacao::adicionarTripulante(const Tripulacao& t) {
    // Verifica se o código já está em uso
    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == t.getCodigo()) {
            cout << "Erro: Codigo de tripulante duplicado! Nao foi possível adicionar o tripulante.\n";
            return false;
        }
    }

    if (quantidade < MAX_TRIPULANTES) {
        if (t.codigo == 0) {  // Se o código for 0, significa que o cargo foi inválido
            cout << "Nao foi possivel adicionar o tripulante devido a um cargo invalido.\n";
            return false;
        }
        listaTripulantes[quantidade++] = t;
        return true;
    } else {
        cout << "Erro: Limite maximo de tripulantes atingido.\n";
        return false;
    }
}

// Listar tripulantes
void Tripulacao::listarTripulantes() {
    if (quantidade == 0) {
        cout << "Nenhum tripulante cadastrado.\n";
        return;
    }
    for (int i = 0; i < quantidade; ++i) {
        cout << "\nTripulante " << i + 1 << ":\n";
        listaTripulantes[i].exibirInformacoes();
    }
}

// Buscar tripulante por código
Tripulacao* Tripulacao::buscarPorCodigo(int cod) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == cod) {
            return &listaTripulantes[i];
        }
    }
    cout << "Tripulante com codigo " << cod << " nao encontrado.\n";
    return nullptr;
}

// Deletar tripulante por código
bool Tripulacao::deletarTripulante(int cod) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == cod) {
            for (int j = i; j < quantidade - 1; ++j) {
                listaTripulantes[j] = listaTripulantes[j + 1];
            }
            --quantidade;
            cout << "Tripulante com codigo " << cod << " foi deletado.\n";
            return true;
        }
    }
    cout << "Tripulante com codigo " << cod << " nao encontrado.\n";
    return false;
}

// Atualizar tripulante por código
bool Tripulacao::atualizarTripulante(int cod, const Tripulacao& novoTripulante) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == novoTripulante.getCodigo() && listaTripulantes[i].getCodigo() != cod) {
            cout << "Erro: Codigo de tripulante duplicado! Nao foi possível atualizar o tripulante.\n";
            return false;
        }
    }

    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == cod) {
            if (novoTripulante.getCargo() == 0) {
                cout << "Erro: Cargo invalido! Nao foi possível atualizar o tripulante.\n";
                return false;
            }
            listaTripulantes[i] = novoTripulante;
            cout << "Tripulante com codigo " << cod << " foi atualizado.\n";
            return true;
        }
    }
    cout << "Tripulante com codigo " << cod << " nao encontrado.\n";
    return false;
}

// Exibir informações do tripulante
void Tripulacao::exibirInformacoes() const {
    cout << "Codigo: " << codigo
         << "\nNome: " << nome
         << "\nEndereco: " << endereco
         << "\nTelefone: " << telefone
         << "\nCargo: " << (cargo == PILOTO ? "Piloto" :
                          (cargo == COPILOTO ? "Copiloto" : "Comissario")) << endl;
}

// Métodos de acesso
void Tripulacao::setNome(const char* n) {
    if (strlen(n) > 0 && strlen(n) < TAM_NOMESS) {
        strcpy(nome, n);
    } else {
        cout << "Nome invalido! Deve conter entre 1 e " << TAM_NOMESS - 1 << " caracteres.\n";
    }
}

void Tripulacao::setEndereco(const char* end) {
    if (strlen(end) > 0 && strlen(end) < TAM_ENDERECO) {
        strcpy(endereco, end);
    } else {
        cout << "Endereco invalido! Deve conter entre 1 e " << TAM_ENDERECO - 1 << " caracteres.\n";
    }
}

void Tripulacao::setTelefone(const char* tel) {
    if (strlen(tel) > 0 && strlen(tel) < TAM_TELEFONE) {
        strcpy(telefone, tel);
    } else {
        cout << "Telefone invalido! Deve conter entre 1 e " << TAM_TELEFONE - 1 << " caracteres.\n";
    }
}

void Tripulacao::setCodigo(int cod) {
    if (cod > 0) {
        codigo = cod;
    } else {
        cout << "Codigo invalido! Deve ser maior que zero.\n";
    }
}

int Tripulacao::getCodigo() const {
    return codigo;
}

const char* Tripulacao::getNome() const {
    return nome;
}

int Tripulacao::getCargo() const {
    return cargo;
}

bool Tripulacao::setCargo(int c) {
    if (c == PILOTO || c == COPILOTO || c == COMISSARIO) {
        cargo = c;
        return true;  // Cargo válido
    } else {
        cout << "Erro: Cargo invalido! Nao sera possivel cadastrar o tripulante.\n";
        return false;  // Cargo inválido
    }
}

// Método de busca por código e cargo
 Tripulacao* Tripulacao::buscarPorCodigo(int cod, int cargo) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaTripulantes[i].getCodigo() == cod && listaTripulantes[i].getCargo() == cargo) {
            return &listaTripulantes[i]; // Retorna o endereço do tripulante encontrado
        }
    }
    return nullptr; // Se não encontrar, retorna nullptr
}
