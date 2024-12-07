#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <iostream>
#include <string.h>

#define TAM_NOMES 50
#define TAM_ENDERECO 100
#define TAM_TELEFONE 15
#define MAX_PASSAGEIROS 100 // Máximo de passageiros

class Passageiro {
private:
    int codigo;
    char nome[TAM_NOMES];
    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    bool fidelidade; // true = sim, false = não
    int pontosFidelidade;

    // Vetor estático para gerenciar passageiros
    static Passageiro listaPassageiros[MAX_PASSAGEIROS];
    static int quantidade; // Quantidade atual de passageiros cadastrados

public:
    // Construtores
    Passageiro();
    Passageiro(int cod, const char* n, const char* end, const char* tel, bool fid);

    // Métodos para gerenciar passageiros
    static bool adicionarPassageiro(const Passageiro& p);
    static void listarPassageiros();
    static Passageiro* buscarPorCodigo(int cod);

    // Métodos da instância
    void adicionarPontos(int pontos);
    void exibirInformacoes() const;

    // Getters
    int getCodigo() const;
    const char* getNome() const;

    // Setters com validações
    void setCodigo(int cod);
    void setNome(const char* n);
    void setEndereco(const char* end);
    void setTelefone(const char* tel);
    void setFidelidade(bool fid);

    static bool deletarPassageiro(int cod); // Novo método
    static bool atualizarPassageiro(int cod, const Passageiro& novoPassageiro);
};

#endif // PASSAGEIRO_H
