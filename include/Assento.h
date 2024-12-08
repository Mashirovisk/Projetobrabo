#ifndef ASSENTO_H
#define ASSENTO_H

#define MAXASSENTOS 20

class Assento
{
    private:
    int num;
    int voo_id;
    int status;

    static Assento* listaAssento[MAXASSENTOS];
    static int qntAsse;




    public:


    Assento();
    Assento(int numero,int vooId,int st);


    int getNum()const;
    int getVooId()const;
    int getstatus()const;
    void setNum(int numero);
    void setVooId(int vooId);
    void setStatus(int st);



    static void CadastrarAssento();
    static void ListarAssentos();


    static Assento* buscarporId(int id);
    static void Deletar(int num);

    void AtualizarAssento();
    static int buscarstatus(int id);
    static void carregarDeArquivoBinario(const char* nomeArquivo);
    static void salvarEmArquivoBinario(const char* nomeArquivo);





};

#endif // ASSENTO_H
