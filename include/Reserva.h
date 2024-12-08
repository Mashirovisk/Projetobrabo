#ifndef RESERVA_H
#define RESERVA_H
#include "Voo.h"


const int MAXRESERVA =20;
class Reserva
{
    private:

    int reserva_id;
    int voo_Id;
    int Assento_id;
    int Passageiro_id;

    static Reserva* Reservas[MAXRESERVA];
    static int qntRes;




    public:

    Reserva();
    //(int id, int vooId, int passageiroId, int assentoId);
    Reserva(int reservaId, int vooId, int passageiroId, int assentoId);

    // Getter e Setter para voo_Id
    int getVoo_Id();


    void setVoo_Id(int id);

    // Getter e Setter para Assento_id
    int getAssento_id();


   void setAssento_id(int id);

    // Getter e Setter para Passageiro_id
    int getPassageiro_id();


    void setPassageiro_id(int id);

    int getReserva_id();

    void setReserva_id(int id);

    static void CadastrarReserva();
    static void listarReservas();

    static Reserva* buscarporId(int id);
    static void Deletar(int num);
    void AtualizarReserva(int reservaId);


    static void salvarEmArquivoBinario(const char* nomeArquivo);
    static void carregarDeArquivoBinario(const char* nomeArquivo);




};

#endif // RESERVA_H

