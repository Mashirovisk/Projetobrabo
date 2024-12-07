#include "include/Passageiro.h"
#include <iostream>
using namespace std;

// Inicializa��o do vetor est�tico e da quantidade
Passageiro Passageiro::listaPassageiros[MAX_PASSAGEIROS];
int Passageiro::quantidade = 0;

// Construtor padr�o
Passageiro::Passageiro() : codigo(0), fidelidade(false), pontosFidelidade(10) {
    strcpy(nome, "");
    strcpy(endereco, "");
    strcpy(telefone, "");
}

// Construtor parametrizado
Passageiro::Passageiro(int cod, const char* n, const char* end, const char* tel, bool fid)
    : fidelidade(fid), pontosFidelidade(10) {
    setCodigo(cod);
    setNome(n);
    setEndereco(end);
    setTelefone(tel);
}

// Adicionar pontos de fidelidade
void Passageiro::adicionarPontos(int pontos) {
    if (pontos > 0) {
        pontosFidelidade += pontos;
    } else {
        cout << "Pontos inv�lidos! Apenas valores positivos s�o permitidos.\n";
    }
}

// Exibir informa��es
void Passageiro::exibirInformacoes() const {
    cout << "Codigo: " << codigo
         << "\nNome: " << nome
         << "\nEndere�o: " << endereco
         << "\nTelefone: " << telefone
         << "\nFidelidade: " << (fidelidade ? "Sim" : "N�o")
         << "\nPontos de Fidelidade: " << pontosFidelidade << endl;
}

// Getters
int Passageiro::getCodigo() const {
    return codigo;
}

const char* Passageiro::getNome() const {
    return nome;
}

// Setters com valida��es
void Passageiro::setCodigo(int cod) {
    if (cod > 0) {
        codigo = cod;
    } else {
        cout << "Codigo invalido! Deve ser maior que zero.\n";
        codigo = 0;  // Se o c�digo for inv�lido, definimos como 0
    }
}

void Passageiro::setNome(const char* n) {
    if (strlen(n) > 0 && strlen(n) < TAM_NOMES) {
        strcpy(nome, n);
    } else {
        cout << "Nome invalido! Deve conter entre 1 e " << TAM_NOMES - 1 << " caracteres.\n";
    }
}

void Passageiro::setEndereco(const char* end) {
    if (strlen(end) > 0 && strlen(end) < TAM_ENDERECO) {
        strcpy(endereco, end);
    } else {
        cout << "Endere�o invalido! Deve conter entre 1 e " << TAM_ENDERECO - 1 << " caracteres.\n";
    }
}

void Passageiro::setTelefone(const char* tel) {
    if (strlen(tel) > 0 && strlen(tel) < TAM_TELEFONE) {
        strcpy(telefone, tel);
    } else {
        cout << "Telefone invalido! Deve conter entre 1 e " << TAM_TELEFONE - 1 << " caracteres.\n";
    }
}

void Passageiro::setFidelidade(bool fid) {
    fidelidade = fid;
}

// M�todos est�ticos
bool Passageiro::adicionarPassageiro(const Passageiro& p) {
    // Verificar se o c�digo do novo passageiro j� existe
    if (p.getCodigo() <= 0) {  // Se o c�digo for inv�lido (menor ou igual a zero)
        cout << "Erro: Codigo invalido! O passageiro nao sera adicionado.\n";
        return false;
    }

    for (int i = 0; i < quantidade; ++i) {
        if (listaPassageiros[i].getCodigo() == p.getCodigo()) {
            cout << "Erro: Passageiro com o codigo " << p.getCodigo() << " ja existe.\n";
            return false;
        }
    }

    // Se n�o encontrar c�digo repetido e o c�digo for v�lido, adicionar o passageiro
    if (quantidade < MAX_PASSAGEIROS) {
        listaPassageiros[quantidade++] = p;
        return true;
    } else {
        cout << "Erro: Limite maximo de passageiros atingido.\n";
        return false;
    }
}



void Passageiro::listarPassageiros() {
    if (quantidade == 0) {
        cout << "Nenhum passageiro cadastrado.\n";
        return;
    }
    for (int i = 0; i < quantidade; ++i) {
        cout << "\nPassageiro " << i + 1 << ":\n";
        listaPassageiros[i].exibirInformacoes();
    }
}

Passageiro* Passageiro::buscarPorCodigo(int cod) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaPassageiros[i].getCodigo() == cod) {
            return &listaPassageiros[i];
        }
    }
    cout << "Passageiro com codigo " << cod << " nao encontrado.\n";
    return nullptr;
}

// Deletar passageiro pelo c�digo
bool Passageiro::deletarPassageiro(int cod) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaPassageiros[i].getCodigo() == cod) {
            // Desloca os passageiros restantes para preencher o espa�o vazio
            for (int j = i; j < quantidade - 1; ++j) {
                listaPassageiros[j] = listaPassageiros[j + 1];
            }
            --quantidade; // Reduz a contagem de passageiros
            cout << "Passageiro com codigo " << cod << " foi deletado.\n";
            return true;
        }
    }
    cout << "Passageiro com codigo " << cod << " nao encontrado.\n";
    return false;
}

// Atualizar informa��es de um passageiro pelo c�digo
bool Passageiro::atualizarPassageiro(int cod, const Passageiro& novoPassageiro) {
    for (int i = 0; i < quantidade; ++i) {
        if (listaPassageiros[i].getCodigo() == cod) {
            listaPassageiros[i] = novoPassageiro;
            cout << "Passageiro com codigo " << cod << " foi atualizado.\n";
            return true;
        }
    }
    cout << "Passageiro com codigo " << cod << " nao encontrado.\n";
    return false;
}
