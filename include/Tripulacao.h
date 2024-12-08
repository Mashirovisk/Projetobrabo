#ifndef TRIPULACAO_H
#define TRIPULACAO_H

#include <iostream>
#include <cstring>

#define TAM_ENDERECO 100
#define TAM_TELEFONE 15
#define MAX_TRIPULANTES 100 // M�ximo de tripulantes
#define TAM_NOMESS 50

class Tripulacao {
private:
    int codigo;  // ID do tripulante
    char nome[TAM_NOMESS];
    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    int cargo;  // 1 - Piloto, 2 - Copiloto, 3 - Comiss�rio

    // Vetor est�tico para gerenciar tripulantes
    static Tripulacao listaTripulantes[MAX_TRIPULANTES];
    static int quantidade; // Quantidade atual de tripulantes cadastrados

public:


    // Construtores
    Tripulacao();
    Tripulacao(int cod, const char* n, const char* end, const char* tel, int c);

    // M�todos para gerenciar tripulantes
    static bool adicionarTripulante(const Tripulacao& t);
    static void listarTripulantes();
    static Tripulacao* buscarPorCodigo(int cod);
    static bool deletarTripulante(int cod);
    static bool atualizarTripulante(int cod, const Tripulacao& novoTripulante);

    // M�todos da inst�ncia
    void exibirInformacoes() const;

    // Getters
    int getCodigo() const;
    const char* getNome() const;
    int getCargo() const;  // Retorna o cargo como inteiro

    // Setters com valida��es
    void setCodigo(int cod);
    void setNome(const char* n);
    void setEndereco(const char* end);
    void setTelefone(const char* tel);
    bool setCargo(int c);  // Aceita 1 (Piloto), 2 (Copiloto) ou 3 (Comiss�rio)

    // M�todo de busca por c�digo e cargo
    static Tripulacao* buscarPorCodigo(int cod, int cargo);
    static void salvarEmArquivoBinario(const char* nomeArquivo);
    static void carregarDeArquivoBinario(const char* nomeArquivo);
};

#endif // TRIPULACAO_H
