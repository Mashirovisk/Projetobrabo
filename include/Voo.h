#ifndef VOO_H
#define VOO_H

#include "Tripulacao.h"  // Supondo que Tripulacao seja uma classe já implementada.
#include "Assento.h"  // Assento provavelmente seria uma classe também.
#include "Reserva.h"
#include "Passageiro.h"

class Reserva;  // Declaração antecipada da classe Reserva


const int MAX_VOOS = 20;  // Número máximo de voos
const int MAX_VOO_ASSENTOS = 10;  // Número máximo de assentos por voo
const int MAX_TRIPULACAO = 3;  // Número máximo de tripulantes por voo
const int TAM_NOME = 50;  // Tamanho máximo para nome
const int RESS=20;

class Voo {
private:
    int id;
    char origem[TAM_NOME];
    char destino[TAM_NOME];
    char data[TAM_NOME];
    char hora[TAM_NOME];
    int pilot_id;
    int copilot_id;
    int flightAtt_id;
    double tarifa;
    bool status;

    bool tripCadastrados;


    Reserva *Reservas_on[RESS];
    int qntRess;




    Assento *Assentos_on[MAX_VOO_ASSENTOS];
    int qntAss;

    // Vetor de tripulantes
    Tripulacao tripulacao_on[MAX_TRIPULACAO];
    int contadorTripulacao;


    // Vetor de voos e contador de voos cadastrados
    static Voo Voos[MAX_VOOS];
    static int qntVoo;



public:

    // Construtores
    Voo();  // Construtor padrão
    Voo(int id, const char* origem, const char* destino, const char* data, const char* hora, float tarifa);

    // Getters
    int getId() const;
    const char* getOrigem() const;
    const char* getDestino() const;
    const char* getData() const;
    const char* getHora() const;
    int getPilotId() const;
    int getCopilotId() const;
    int getFlightAttId() const;
    double getTarifa() const;
    bool getStatus() const;

    // Setters
    void setId(int novo_id);
    void setOrigem(const char* nova_origem);
    void setDestino(const char* novo_destino);
    void setData(const char* nova_data);
    void setHora(const char* nova_hora);
    void setPilotId(int novo_pilot_id);
    void setCopilotId(int novo_copilot_id);
    void setFlightAttId(int novo_flightAtt_id);
    void setTarifa(double nova_tarifa);
    void setStatus(bool novo_status);

    // Função para cadastrar um voo
    static void cadastrarVoo();

    static bool tripulanteDup(int id);
    static void listarVoos();
    static void deletarVoo(int id);
    static void atualizarVoo(int id);

    static Voo* buscarporId(int id);
    int adicionarAssento(Assento* assento);

    void DeletarAssento(int num);
    int adicionarReserva(Reserva* reserva);
    void DeletarReserva(int id);


    Voo* buscarstatus(int id);


    static void salvarEmArquivoBinario(const char* nomeArquivo);
    static void carregarDeArquivoBinario(const char* nomeArquivo);



};

#endif  // FIM DO VOO_H
