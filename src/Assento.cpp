#include "include/Assento.h"
#include "include/Voo.h"
#include <iostream>

    using namespace std;

    Assento* Assento::listaAssento[MAXASSENTOS];
    int Assento::qntAsse=0;




    Assento::Assento(){
        num=0;
        voo_id=0;
        status=0;
    }



    Assento::Assento(int numero,int vooId,int st){
        num =numero;
        voo_id=vooId;
        status=st;
    }


    int Assento::getNum()const{
        return num;
    }
    int Assento::getVooId()const{
        return voo_id;
    }
    int Assento::getstatus()const{
        return status;
    }
    void Assento::setNum(int numero){
        if(numero<0){
            cout<<"Erro: numero negativo";
            return;
        }
        num=numero;
    }
    void Assento::setVooId(int vooId){
        voo_id=vooId;
    }
    void Assento::setStatus(int st){
        status=st;
    }

    void Assento::CadastrarAssento(){

        int numero,vooId,status;


        cout<<"Digite o numero do assento:";
        cin>>numero;



        cout<<"Digite o ID do voo:";
        cin>>vooId;
        Voo* verificar = Voo::buscarporId(vooId);
        if (verificar == nullptr) {
                cout << "Voo nao existe!" << endl;
                return;
        }


        for(int i=0;i<qntAsse;i++){
            if(listaAssento[i]->getNum()==numero&&listaAssento[i]->getVooId()==vooId){
                cout << "Erro: Assento ja cadastrado!" << endl;
                return;
            }
        }


        cout<<"Digite o status do assento (0 para disponivel,1 para ocupado)"<<endl;
        cin>>status;

        Assento* novoassento=new Assento(numero,vooId,status);
        if(qntAsse < MAXASSENTOS){
            listaAssento[qntAsse]=novoassento;
            qntAsse++;
            cout<<"Cadastrado com sucesso"<<endl;
        }else{
             cout<<"Erro: limite alcancado!"<<endl;
        }




        verificar->adicionarAssento(novoassento);

     }


void Assento::ListarAssentos() {
    if (qntAsse == 0) {
        cout << "Nenhum assento cadastrado!" << endl;
        return;
    }

    for (int i = 0; i < qntAsse; i++) {
        cout << "Assento: " << listaAssento[i]->getNum() << ", Voo ID: " << listaAssento[i]->getVooId()
             << ", Status: " << (listaAssento[i]->getstatus() == 0 ? "Disponível" : "Ocupado") << endl;
    }
}
void Assento::Deletar(int num){

    Assento* ass=buscarporId(num);
    if(ass==nullptr){
        cout<<"Assento nao encontrado"<<endl;
        return;
    }
    int voo_id=ass->getVooId();
    Voo* voo_assento= Voo::buscarporId(voo_id);
    if(voo_assento!=nullptr){
        voo_assento->DeletarAssento(num);
    }
    for(int i=0;i<qntAsse;i++){
        if(listaAssento[i]->getNum()==num){
            Assento* ParaDeletar=listaAssento[i];
            for(int j=i;j<qntAsse-1;j++){
                listaAssento[j]=listaAssento[j+1];
            }
            qntAsse--;
            cout<<" Assento " <<num<<" deletado com sucesso! "<<endl;
            delete ParaDeletar;
            return;

        }

    }
    cout<<"Assento nao encontrado "<<endl;
}


Assento* Assento::buscarporId(int id){
        for(int i=0;i<qntAsse;i++){
            if(listaAssento[i]->getNum() == id){
                return listaAssento[i];
            }
        }
        return nullptr;
    }

void Assento::AtualizarAssento() {

    int novoStatus;
    cout << "Digite o novo status do assento (0 para disponível, 1 para ocupado): ";
    cin >> novoStatus;
    setStatus(novoStatus);
    cout << "Status atualizado com sucesso!" << endl;
}
