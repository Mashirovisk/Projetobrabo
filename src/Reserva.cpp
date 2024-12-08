#include "include/Reserva.h"
#include <iostream>
#include "include/Voo.h"
#include "include/Passageiro.h"
#include "include/Assento.h"

#include <fstream>
using namespace std;

Reserva* Reserva::Reservas[MAXRESERVA];
int Reserva::qntRes =0;;




Reserva::Reserva() {
    // Construtor padrão
    reserva_id=0;
    voo_Id= 0;
    Assento_id=0;
    Passageiro_id=0;
    qntRes=0;
}


Reserva::Reserva(int reservaId, int vooId, int passageiroId, int assentoId) {
    this->reserva_id = reservaId;
    this->voo_Id = vooId;
    this->Passageiro_id = passageiroId;
    this->Assento_id = assentoId;

    // Depuração
    cout << "Construtor de Reserva chamado com valores: "
         << reservaId << ", " << vooId << ", " << passageiroId << ", " << assentoId << endl;
}

/*
Reserva::Reserva(int id, int vooId, int passageiroId, int assentoId) {
    reserva_id = id;
    voo_Id = vooId;
    Passageiro_id = passageiroId;
    Assento_id = assentoId;
}
*/

// Getter e Setter para voo_Id
    int Reserva::getVoo_Id() {
    return voo_Id;
}

    void Reserva::setVoo_Id(int id) {
        voo_Id = id;
    }

    // Getter e Setter para Assento_id
    int Reserva::getAssento_id() {
        return Assento_id;
    }

    void Reserva::setAssento_id(int id) {
        Assento_id = id;
    }

    // Getter e Setter para Passageiro_id
    int Reserva::getPassageiro_id() {
        return Passageiro_id;
    }

    void Reserva::setPassageiro_id(int id) {
        Passageiro_id = id;
    }


int  Reserva:: getReserva_id() {
        return reserva_id;
    }

void Reserva::setReserva_id(int id) {
        reserva_id = id;
    }








    void Reserva::CadastrarReserva() {

    int voo_Id, Assento_id, Passageiro_Id, reservaid;

    cout << "Digite o numero da reserva: ";
    cin >> reservaid;

    cout << "Digite o Id do voo: ";
    cin >> voo_Id;

    // Verifica se o voo existe
    Voo* verificar = Voo::buscarporId(voo_Id);
    if (verificar == nullptr) {
        cout << "Voo nao existe!" << endl;
        return;
    }

    // Verifica se a reserva já existe
    for (int i = 0; i < qntRes; i++) {
        if (Reservas[i]->getReserva_id() == reservaid && Reservas[i]->getVoo_Id() == voo_Id) {
            cout << "Erro: Reserva ja cadastrada!" << endl;
            return;
        }
    }

    cout << "Digite o Id do Passageiro: ";
    cin >> Passageiro_Id;
    Passageiro* verificarpas = Passageiro::BuscarPasporId(Passageiro_Id);

    if (verificarpas == nullptr) {
        cout << "Passageiro nao existe!" << endl;
        return;
    }

    // Verificar se o passageiro já tem uma reserva para o voo
    for (int i = 0; i < qntRes; i++) {
        if (Reservas[i]->getPassageiro_id() == Passageiro_Id && Reservas[i]->getVoo_Id() == voo_Id) {
            cout << "Erro: Passageiro ja possui reserva para este voo!" << endl;
            return;
        }
    }

    // Verificar o assento
    cout << "Digite o Assento do voo: ";
    cin >> Assento_id;

    Assento* verificarAssento = Assento::buscarporId(Assento_id);
    if (verificarAssento == nullptr) {
        cout << "Assento nao existe!" << endl;
        return;
    }

    // Verifica o status do assento
    int verificarStatus = Assento::buscarstatus(Assento_id);
    if (verificarStatus == 1) {
        cout << "Assento ocupado!" << endl;
        return;
    }

    // Atualiza o status do assento para ocupado
    verificarAssento->setStatus(1);

    // Adicionar pontos de fidelidade se o passageiro for fiel
    if (verificarpas->getfidelidade()) {
        verificarpas->adicionarPontos(10); // Adiciona 10 pontos ao passageiro fiel
        cout << "Parabens! Você ganhou 10 pontos de fidelidade." << endl;
    }

    // Cria a nova reserva
    Reserva* novaReserva = new Reserva(reservaid, voo_Id, Assento_id, Passageiro_Id);

    // Verifica se o limite de reservas foi alcançado
    if (qntRes < MAXRESERVA) {
        Reservas[qntRes] = novaReserva;
        qntRes++;
        cout << "Cadastro com sucesso!" << endl;
    } else {
        cout << "Erro: Limite de reservas alcançado!" << endl;
    }

    // Adiciona a nova reserva ao voo
    verificar->adicionarReserva(novaReserva);
}
















void Reserva::listarReservas() {
    if (qntRes == 0) {
        cout << "Nenhuma reserva cadastrada." << endl;
        return;
    }

    cout << "Lista de Reservas:" << endl;
    for (int i = 0; i < qntRes; i++) {
        if (Reservas[i] != nullptr) {
            cout << "Reserva ID: " << Reservas[i]->getReserva_id() << endl;
            cout << "Voo ID: " << Reservas[i]->getVoo_Id() << endl;
            cout << "Passageiro ID: " << Reservas[i]->getPassageiro_id() << endl;
            cout << "Assento ID: " << Reservas[i]->getAssento_id() << endl;
            cout << "---------------------------" << endl;
        } else {
            cout << "Reserva " << i << " é nula." << endl;
        }
    }
}



void Reserva::Deletar(int num) {
    // Busca pela reserva através do número (id)
    Reserva* reserva = buscarporId(num);  // Método que retorna um ponteiro para a reserva com o id 'num'
    if (reserva == nullptr) {
        cout << "Reserva nao encontrada" << endl;
        return;
    }

    int voo_id = reserva->getVoo_Id();  // Obtém o ID do voo associado à reserva
    Voo* voo_reserva = Voo::buscarporId(voo_id);  // Busca o voo usando o ID
    if (voo_reserva != nullptr) {
        voo_reserva->setStatus(0);
        voo_reserva->DeletarReserva(num);  // Método no Voo que exclui a reserva
    }

    // Agora, iteramos sobre o vetor de reservas e buscamos o id da reserva para excluí-la
    for (int i = 0; i < qntRes; i++) {
        if (Reservas[i]->getReserva_id() == num) {  // Verifica se o id da reserva corresponde ao número informado
            Reserva* ParaDeletar = Reservas[i];  // Ponteiro para a reserva que será deletada
            // Realiza o deslocamento para "remover" o elemento do vetor
            for (int j = i; j < qntRes - 1; j++) {
                Reservas[j] = Reservas[j + 1];  // Desloca as reservas à frente
            }
            qntRes--;  // Decrementa a quantidade de reservas
            cout << "Reserva " << num << " deletada com sucesso!" << endl;
            delete ParaDeletar;  // Deleta a reserva da memória
            return;
        }
    }

    cout << "Reserva nao encontrada" << endl;  // Caso o id não seja encontrado
}


Reserva* Reserva::buscarporId(int id) {
    for (int i = 0; i < qntRes; i++) {  // Itera sobre todas as reservas
        if (Reservas[i]->getReserva_id() == id) {  // Verifica se o id da reserva corresponde ao procurado
            return Reservas[i];  // Retorna o ponteiro da reserva
        }
    }
    return nullptr;  // Retorna nullptr caso não encontre a reserva
}


void Reserva::AtualizarReserva(int reservaId) {
    int voo_Id, Assento_id, Passageiro_Id;

    cout << "Digite o novo Id do voo: ";
    cin >> voo_Id;

    // Verifica se o voo existe
    Voo* verificarVoo = Voo::buscarporId(voo_Id);
    if (verificarVoo == nullptr) {
        cout << "Voo não existe!" << endl;
        return;
    }

    cout << "Digite o novo Id do Passageiro: ";
    cin >> Passageiro_Id;
    Passageiro* verificarpas = Passageiro::BuscarPasporId(Passageiro_Id);

    if (verificarpas == nullptr) {
        cout << "Passageiro não encontrado!" << endl;
        return;
    }

    cout << "Digite o novo Assento do voo: ";
    cin >> Assento_id;

    Assento* verificarAssento = Assento::buscarporId(Assento_id);
    if (verificarAssento == nullptr) {
        cout << "Assento não existe!" << endl;
        return;
    }

    int verificarStatus = Assento::buscarstatus(Assento_id);
    if (verificarStatus == 1) {
        cout << "Assento ocupado!" << endl;
        return;
    }

    // Se houver um assento anterior, libere-o (mude seu status para disponível)
    int assentoAnteriorId = this->getAssento_id(); // Supondo que getAssento_id() retorna o ID do assento atual da reserva
    if (assentoAnteriorId != -1) { // Verifique se há um assento anterior (ID diferente de -1)
        Assento* assentoAnterior = Assento::buscarporId(assentoAnteriorId);
        if (assentoAnterior != nullptr) {
            assentoAnterior->setStatus(0); // Libera o assento anterior (status = 0, disponível)
            cout << "Assento anterior liberado." << endl;
        }
    }

    // Marca o novo assento como ocupado
    verificarAssento->setStatus(1);

    if (verificarpas->getfidelidade()) {
        verificarpas->adicionarPontos(10); // Adiciona 10 pontos ao passageiro fiel
        cout << "O passageiro ganhou 10 pontos de fidelidade." << endl;
    }

    // Atualiza os dados da reserva
    this->setVoo_Id(voo_Id);
    this->setPassageiro_id(Passageiro_Id);
    this->setAssento_id(Assento_id);

    cout << "Reserva atualizada com sucesso!" << endl;

    // Adiciona a reserva atualizada ao voo
    verificarVoo->adicionarReserva(this);
}






void Reserva::salvarEmArquivoBinario(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == nullptr) {
        cout << "Erro ao abrir o arquivo para salvar!" << endl;
        return;
    }

    // Salva a quantidade de reservas no início do arquivo
    fwrite(&qntRes, sizeof(int), 1, arquivo);
    cout << "Número de reservas a serem salvas: " << qntRes << endl;

    // Salva cada reserva no arquivo
    for (int i = 0; i < qntRes; i++) {
        if (Reservas[i] != nullptr) {
            // Exibe a saída de depuração com base na reserva, começando de 1
            cout << "Debug: reserva " << (i + 1) << " - reservaId: " << Reservas[i]->getReserva_id()
                 << ", vooId: " << Reservas[i]->getVoo_Id()
                 << ", passageiroId: " << Reservas[i]->getPassageiro_id()
                 << ", assentoId: " << Reservas[i]->getAssento_id() << endl;

            // Escreve os dados da reserva no arquivo
            fwrite(&Reservas[i]->reserva_id, sizeof(int), 1, arquivo);
            fwrite(&Reservas[i]->voo_Id, sizeof(int), 1, arquivo);
            fwrite(&Reservas[i]->Passageiro_id, sizeof(int), 1, arquivo);
            fwrite(&Reservas[i]->Assento_id, sizeof(int), 1, arquivo);
        }
    }

    fclose(arquivo);
    cout << "Reservas salvas com sucesso no arquivo binário!" << endl;
}



void Reserva::carregarDeArquivoBinario(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == nullptr) {
        cout << "Erro ao abrir o arquivo para carregar!" << endl;
        return;
    }

    // Lê a quantidade de reservas do arquivo
    if (fread(&qntRes, sizeof(int), 1, arquivo) != 1) {
        cout << "Erro ao ler a quantidade de reservas." << endl;
        fclose(arquivo);
        return;
    }

    cout << "Número de reservas a serem carregadas: " << qntRes << endl;

    // Verifica se a quantidade de reservas excede o limite máximo permitido
    if (qntRes > MAXRESERVA) {
        cout << "Erro: número de reservas no arquivo excede o limite permitido!" << endl;
        fclose(arquivo);
        return;
    }

    // Carrega cada reserva do arquivo
    for (int i = 0; i < qntRes; i++) {
        int reservaId, vooId, passageiroId, assentoId;

        // Lê os dados de cada reserva do arquivo
        if (fread(&reservaId, sizeof(int), 1, arquivo) != 1 ||
            fread(&vooId, sizeof(int), 1, arquivo) != 1 ||
            fread(&passageiroId, sizeof(int), 1, arquivo) != 1 ||
            fread(&assentoId, sizeof(int), 1, arquivo) != 1) {
            cout << "Erro ao ler os dados da reserva " << i << "." << endl;
            fclose(arquivo);
            return;
        }

        // Exibe os dados carregados para depuração
        cout << "Debug: reserva " << (i + 1) << " - reservaId: " << reservaId
             << ", vooId: " << vooId
             << ", passageiroId: " << passageiroId
             << ", assentoId: " << assentoId << endl;

        // Criação de uma nova reserva e armazenamento no vetor estático
        if (Reservas[i] != nullptr) {
            delete Reservas[i]; // Libera a memória existente, se necessário
        }
        Reservas[i] = new Reserva(reservaId, vooId, passageiroId, assentoId);
    }

    fclose(arquivo);
    cout << "Reservas carregadas com sucesso do arquivo binário!" << endl;
}



