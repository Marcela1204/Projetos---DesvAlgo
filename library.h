//
// Created by unifmnalesso on 09/10/2023.
//

#ifndef PROJETO2_LIBRARY_H
#define PROJETO2_LIBRARY_H

#endif //PROJETO2_LIBRARY_H

typedef struct {//Struct de cadastro dos clientes
    char nome[100];
    char cpf[11];
    double saldo;
    char senha[20];
    double taxa;
    double minimo;
    int transacao;
}Cadastro;

typedef struct {//struct do extrato do cliente
    char info[1000];
}ExtratoCliente;

void NovoCliente (Cadastro *,int *, ExtratoCliente *[]);//Função Novo Cliente
void ApagarCliente (Cadastro *,int *, ExtratoCliente *);//Função Apagar cliente
void ListarClientes (Cadastro *, int *);// Função listar clientes
void Debito (Cadastro *, int *, ExtratoCliente *[]);// Função de débito
void Deposito (Cadastro *,int *);//Função de deposito
void Extrato (Cadastro *, int *, ExtratoCliente *);//Função de extrato
void Transferencia (Cadastro *, int *);//Função de transferencia
void escrita(Cadastro *, int *);//Função de escrita do arquivo
void leitura(Cadastro *pessoas, int *);//Função de leitura do arquivo
