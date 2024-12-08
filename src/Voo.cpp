#include "include/Voo.h"
#include "include/Assento.h"
#include <iostream>
#include <cstring>  // Para usar fun��es de manipula��o de strings como strcpy
#include <fstream>
#include <cstdio>    // Necess�rio para leitura e grava��o de arquivos
using namespace std;

// Definindo as vari�veis est�ticas



Voo Voo::Voos[MAX_VOOS];
int Voo::qntVoo = 0;

Voo::Voo() {
    // Construtor padr�o
    id = 0;
    origem[0] = '\0';
    destino[0] = '\0';
    data[0] = '\0';
    hora[0] = '\0';
    pilot_id = 0;
    copilot_id = 0;
    flightAtt_id = 0;
    tarifa = 0.0;
    status = false;
    tripCadastrados=false;
    qntAss=0;
    qntRess=0;

}

Voo::Voo(int id, const char* origem, const char* destino, const char* data, const char* hora, float tarifa) {
    this->id = id;
    strcpy(this->origem, origem);
    strcpy(this->destino, destino);
    strcpy(this->data, data);
    strcpy(this->hora, hora);
    this->tarifa = tarifa;
    this->status = true;  // Voo ativo por padr�o
    qntAss=0;
    qntRess=0;
}

int Voo::getId() const {
    return id;
}

const char* Voo::getOrigem() const {
    return origem;
}

const char* Voo::getDestino() const {
    return destino;
}

const char* Voo::getData() const {
    return data;
}

const char* Voo::getHora() const {
    return hora;
}

int Voo::getPilotId() const {
    return pilot_id;
}

int Voo::getCopilotId() const {
    return copilot_id;
}

int Voo::getFlightAttId() const {
    return flightAtt_id;
}

double Voo::getTarifa() const {
    return tarifa;
}

bool Voo::getStatus() const {
    return status;
}

void Voo::setId(int novo_id) {
    id = novo_id;
}

void Voo::setOrigem(const char* nova_origem) {
    strcpy(origem, nova_origem);
}

void Voo::setDestino(const char* novo_destino) {
    strcpy(destino, novo_destino);
}

void Voo::setData(const char* nova_data) {
    strcpy(data, nova_data);
}

void Voo::setHora(const char* nova_hora) {
    strcpy(hora, nova_hora);
}

void Voo::setPilotId(int novo_pilot_id) {
    pilot_id = novo_pilot_id;
}

void Voo::setCopilotId(int novo_copilot_id) {
    copilot_id = novo_copilot_id;
}

void Voo::setFlightAttId(int novo_flightAtt_id) {
    flightAtt_id = novo_flightAtt_id;
}

void Voo::setTarifa(double nova_tarifa) {
    if(nova_tarifa<0){
        cout<<"Erro: valor negativo";
        return;
    }
    tarifa = nova_tarifa;
}

void Voo::setStatus(bool novo_status) {
    status = novo_status;
}



bool Voo::tripulanteDup(int id){
    for(int i=0;i<Voo::qntVoo;i++){
        if(!Voos[i].tripCadastrados){
            continue;
        }
        for(int j=0;j<MAX_TRIPULACAO;j++){
            if(Voos[i].tripulacao_on[j].getCodigo()==id){
                return true;
            }
        }
    }
    return false;
}





void Voo::cadastrarVoo(){

    Voo voo;
    char origem[TAM_NOME],destino[TAM_NOME],data[TAM_NOME],hora[TAM_NOME];

    int piloto_Id,copiloto_Id,Comissario_Id;
    float tarifa;
    bool status;


    cout<< "Digite a id do voo"<<endl;
    cin >> voo.id;
    cin.ignore();

    for(int i=0;i<qntVoo;i++){
        if(Voos[i].id==voo.id){
            cout<< "Erro id repetido!"<<endl;
            return;
        }
    }

    cout << "Digite a origem do voo" << endl;
    cin.getline(origem, TAM_NOME);
    cout << "Digite o destino do voo" << endl;
    cin.getline(destino, TAM_NOME);
    cout << "Digite a data do voo" << endl;
    cin.getline(data, TAM_NOME);
    cout << "Digite a hora do voo" << endl;
    cin.getline(hora, TAM_NOME);

    cout << "Digite a tarifa do voo" << endl;
    cin >> tarifa;
    cin.ignore(); // Para limpar o buffer do cin

    cout<< "Digite o id do piloto"<<endl;
    cin>>  piloto_Id;



    Tripulacao* Piloto =Tripulacao::buscarPorCodigo(piloto_Id,1);
    if(Piloto==nullptr){
        cout<< "Piloto nao existe"<<endl;
        return;
    }
    if(tripulanteDup(piloto_Id)){
        cout << "Piloto em outro voo" << endl;
        return;
    }


    cout<< "Digite o id do Copiloto"<<endl;
    cin>>   copiloto_Id;

    Tripulacao* Copiloto =Tripulacao::buscarPorCodigo(copiloto_Id,2);
    if(Copiloto==nullptr){
        cout<< "Copiloto nao existe"<<endl;
        return;
    }


    if(tripulanteDup(copiloto_Id)){
        cout << "Copiloto em outro voo" << endl;
        return;
    }



    cout<< "Digite o id do Comissario"<<endl;
    cin>>  Comissario_Id;

    Tripulacao* Comissario =Tripulacao::buscarPorCodigo(Comissario_Id,3);
    if(Comissario==nullptr){
        cout<< "Comissario nao existe"<<endl;
        return;
    }
    if(tripulanteDup(Comissario_Id)){
        cout << "Comissario em outro voo" << endl;
        return;
    }

    voo.setOrigem(origem);
    voo.setDestino(destino);
    voo.setData(data);
    voo.setHora(hora);
    voo.setTarifa(tarifa);



    voo.tripulacao_on[0] = *Piloto;
    voo.tripulacao_on[1] = *Copiloto;
    voo.tripulacao_on[2] = *Comissario;
    voo.tripCadastrados=true;

    if(Piloto!=nullptr&&Copiloto!=nullptr){
        voo.status=true;

    }else{
        voo.status=false;
    }

    Voos[qntVoo++]=voo;

    if (voo.status) {
        cout << "Voo cadastrado com sucesso e esta ativo!" << endl;
    } else {
        cout << "Voo cadastrado, mas esta inativo (sem piloto ou copiloto)." << endl;
    }

}

void Voo::listarVoos() {
    if (qntVoo == 0) {
        cout << "Nenhum voo cadastrado!" << endl;
        return;
    }

    cout << "Lista de Voos Cadastrados:" << endl;
    for (int i = 0; i < qntVoo; i++) {
        Voo voo = Voos[i];

        cout << "ID do Voo: " << voo.getId() << endl;
        cout << "Origem: " << voo.getOrigem() << endl;
        cout << "Destino: " << voo.getDestino() << endl;
        cout << "Data: " << voo.getData() << endl;
        cout << "Hora: " << voo.getHora() << endl;
        cout << "Tarifa: " << voo.getTarifa() << endl;

        if (voo.getStatus()) {
            cout << "Status: Ativo" << endl;
        } else {
            cout << "Status: Inativo" << endl;
        }

        cout << "Tripulacao:" << endl;
        // Verifique se a fun��o `getNome` est� funcionando corretamente para os tripulantes
        cout << "Piloto: " << voo.tripulacao_on[0].getNome() << endl;
        cout << "Copiloto: " << voo.tripulacao_on[1].getNome() << endl;
        cout << "Comiss�rio: " << voo.tripulacao_on[2].getNome() << endl;

        cout << "-----------------------------" << endl;

        cout<<"Assentos Disponiveis:"<<endl;
        cout<<"Status 0-Disponivel 1-indisponivel:"<<endl;
        for(int j=0;j<voo.qntAss;j++){
            Assento* Assento =voo.Assentos_on[j];
            cout<< "Assento ID: "<<Assento->getNum() << " Status " <<Assento->getstatus()<<endl;
        }
        cout<<"--------------------------------"<<endl;

        for(int k=0;k<voo.qntRess;k++){
            Reserva* Reserva = voo.Reservas_on[k];
            cout<<"Reserva ID:"<<Reserva->getReserva_id();
            cout <<"Passageiro ID:"<<Reserva->getPassageiro_id();
        }


    }
}

void Voo::deletarVoo(int id){
    bool VooEncontrado=false;

    for(int i=0;i<qntVoo;i++){
        if(Voos[i].id==id){
            VooEncontrado=true;


            for(int j=i;j<qntVoo-1;j++){
                Voos[j]=Voos[j+1];
            }

            qntVoo--;
            cout << "Voo com id" << id<<"deletado com sucesso!"<<endl;
            break;
        }
    }

    if(!VooEncontrado){
       cout << "Voo com Id" << id<<"n�o encontrado"<<endl;
    }

}

void Voo::atualizarVoo(int id) {
    bool vooEncontrado = false;
    int piloto_Id, copiloto_Id, Comissario_Id;
    float tarifa;
    char origem[TAM_NOME], destino[TAM_NOME], data[TAM_NOME], hora[TAM_NOME];

    for (int i = 0; i < qntVoo; i++) {
        if (Voos[i].id == id) {
            vooEncontrado = true;
            Voo& voo = Voos[i];

            // Atualizando os dados do voo
            cout << "Atualizando dados do voo ID: " << id << endl;
            cin.ignore();
            cout << "Digite a nova origem do voo: ";
            cin.getline(origem, TAM_NOME);
            voo.setOrigem(origem);

            cout << "Digite o novo destino do voo: ";
            cin.getline(destino, TAM_NOME);
            voo.setDestino(destino);

            cout << "Digite a nova data do voo: ";
            cin.getline(data, TAM_NOME);
            voo.setData(data);

            cout << "Digite a nova hora do voo: ";
            cin.getline(hora, TAM_NOME);
            voo.setHora(hora);

            cout << "Digite a nova tarifa do voo: ";
            cin >> tarifa;
            voo.setTarifa(tarifa);
            cin.ignore();  // Para limpar o buffer

            // Atualizando a tripula��o
            cout << "Digite o novo id do piloto: ";
            cin >> piloto_Id;
            Tripulacao* Piloto = Tripulacao::buscarPorCodigo(piloto_Id, 1);
            if (Piloto == nullptr) {
                cout << "Piloto n�o existe!" << endl;
                return;
            }
            if(tripulanteDup(piloto_Id)){
                cout << "Piloto em outro voo" << endl;
                return;
            }


            cout << "Digite o novo id do copiloto: ";
            cin >> copiloto_Id;
            Tripulacao* Copiloto = Tripulacao::buscarPorCodigo(copiloto_Id, 2);
            if (Copiloto == nullptr) {
                cout << "Copiloto nao existe!" << endl;
                return;
            }
            if(tripulanteDup(copiloto_Id)){
                cout << "Copiloto em outro voo" << endl;
                return;
            }
            if(tripulanteDup(Comissario_Id)){
                cout << "Comissario em outro voo" << endl;
                return;
            }

            cout << "Digite o novo id do comiss�rio: ";
            cin >> Comissario_Id;
            Tripulacao* Comissario = Tripulacao::buscarPorCodigo(Comissario_Id, 3);
            if (Comissario == nullptr) {
                cout << "Comissario nao existe!" << endl;
                return;
            }

            // Atualizando os dados da tripula��o
            voo.tripulacao_on[0] = *Piloto;
            voo.tripulacao_on[1] = *Copiloto;
            voo.tripulacao_on[2] = *Comissario;

            // Atualizando o status
            if (Piloto != nullptr && Copiloto != nullptr) {
                voo.setStatus(true);
            } else {
                voo.setStatus(false);
            }

            cout << "Voo ID " << id << " atualizado com sucesso!" << endl;
            break;
        }
        cout<<endl;
    }

    if (!vooEncontrado) {
        cout << "Voo com ID " << id << " nao encontrado!" << endl;
    }
}



    Voo* Voo::buscarporId(int id){
        for(int i=0;i<qntVoo;i++){
            if(Voos[i].getId() == id){
                return &Voos[i];
            }
        }
        return nullptr;
    }


int Voo::adicionarAssento(Assento* assento){
    Assentos_on[qntAss++]=assento;
}




void Voo::DeletarAssento(int num){

    if(qntAss<=0){
        cout<<"Nao ha assentos para deletar"<<endl;
        return;
    }
    for(int i=0;i<qntAss;i++){
        if(Assentos_on[i]->getNum()==num){
            for(int j=i;j<qntAss-1;j++){
                Assentos_on[j]=Assentos_on[j+1];
            }
            qntAss--;
            cout<<" Assento " <<num<<" deletado com sucesso! "<<endl;
            return;
        }

    }
    cout<<"Assento nao encontrado"<<endl;
}

int Voo::adicionarReserva(Reserva* reserva){
    Reservas_on[qntRess++]=reserva;
}

void Voo::DeletarReserva(int id) {

    if(qntRess <= 0){
        cout << "Nao ha Reservas para deletar" << endl;
        return;
    }

    for (int i = 0; i < qntRess; i++) {
        if (Reservas_on[i]->getReserva_id() == id) {
            // Obter o ID do assento associado � reserva
            int assento_id = Reservas_on[i]->getAssento_id();  // M�todo que retorna o ID do assento da reserva

            // Buscar o assento usando o ID
            Assento* assento = Assento::buscarporId(assento_id);
            if (assento != nullptr) {
                assento->setStatus(0);  // Alterar status do assento para "livre" (presumindo que "0" � livre)
                cout << "Status do assento alterado para 'livre'" << endl;
            }

            // Remover reserva do vetor (deslocando os elementos)
            for (int j = i; j < qntRess - 1; j++) {
                Reservas_on[j] = Reservas_on[j + 1];  // Desloca as reservas � frente
            }
            qntRess--;  // Decrementa a quantidade de reservas
            cout << "Reserva " << id << " deletada com sucesso!" << endl;
            return;
        }
    }

    cout << "Reserva n�o encontrada!" << endl;  // Caso o id n�o seja encontrado
}

void Voo::carregarDeArquivoBinario(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == nullptr) {
        printf("Erro ao abrir o arquivo para carregar!\n");
        return;
    }

    // Carrega a quantidade de voos
    fread(&qntVoo, sizeof(int), 1, arquivo);

    for (int i = 0; i < qntVoo; i++) {
        Voo& voo = Voos[i];

        // Carrega os dados b�sicos do voo
        fread(&voo, sizeof(Voo), 1, arquivo);

        // Carrega os assentos associados ao voo
        fread(&voo.qntAss, sizeof(int), 1, arquivo);
        for (int j = 0; j < voo.qntAss; j++) {
            voo.Assentos_on[j] = new Assento();
            fread(voo.Assentos_on[j], sizeof(Assento), 1, arquivo);
        }

        // Carrega as reservas associadas ao voo
        fread(&voo.qntRess, sizeof(int), 1, arquivo);
        for (int k = 0; k < voo.qntRess; k++) {
            voo.Reservas_on[k] = new Reserva();
            fread(voo.Reservas_on[k], sizeof(Reserva), 1, arquivo);
        }
    }

    fclose(arquivo);
    printf("Dados dos voos, assentos e reservas carregados com sucesso!\n");
}


void Voo::salvarEmArquivoBinario(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == nullptr) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    // Salva a quantidade de voos
    fwrite(&qntVoo, sizeof(int), 1, arquivo);

    for (int i = 0; i < qntVoo; i++) {
        Voo& voo = Voos[i];

        // Salva os dados b�sicos do voo
        fwrite(&voo, sizeof(Voo), 1, arquivo);

        // Salva os assentos associados ao voo
        fwrite(&voo.qntAss, sizeof(int), 1, arquivo); // Quantidade de assentos
        for (int j = 0; j < voo.qntAss; j++) {
            fwrite(voo.Assentos_on[j], sizeof(Assento), 1, arquivo);
        }

        // Salva as reservas associadas ao voo
        fwrite(&voo.qntRess, sizeof(int), 1, arquivo); // Quantidade de reservas
        for (int k = 0; k < voo.qntRess; k++) {
            fwrite(voo.Reservas_on[k], sizeof(Reserva), 1, arquivo);
        }
    }

    fclose(arquivo);
    printf("Dados dos voos, assentos e reservas salvos com sucesso!\n");
}

