//
// Created by unifmnalesso on 09/10/2023.
//
#include <stdio.h>
#include "library.h"
#include <string.h>

void escrita (Cadastro *pessoas, int *usados){
    FILE *f = fopen("arquivo.bin","wb"); //abre o arquivo como escrita em binario
    fwrite(pessoas,sizeof (Cadastro),1000,f); //escreve o array tarefas no arquivo
    fclose(f); //fecha o arquivo
    FILE *i = fopen("arquivo.bin","ab"); //abre o arquivo como apendice em binario
    fwrite(&usados,sizeof(int),1,i); //escreve o endereco da variavel valortarefa no arquivo
    fclose(i); //fecha o arquivo
}
void leitura (Cadastro *pessoas, int *usados){
    FILE* f = fopen("arquivo.bin","rb"); //abre o arquivo como leitura em binario
    fread(pessoas,sizeof(Cadastro),1000,f); //le o array tarefas no arquivo
    fread(&usados,sizeof(int),1,f); //le os valores do inteiro para n
    fclose(f); //fecha o arquivo
}

void NovoCliente (Cadastro *pessoas,int *usados, ExtratoCliente *grupo[]){
    while (1){//abre o loop para cadastrar o usuario
        char mensagem[4]; //cria a variavel para guardar resposta da proxima pergunta
        printf("\nQuer continuar a operacao: (Sim ou Nao) R: \n"); //pergunta se a pessoa quer continuar
        scanf("%s",mensagem); //recebe a mensagem
        int positivo = stricmp(mensagem,"Sim"); //compara o que tiver na variavel com a palavra sim
        if (positivo == 0) {//se for igual, faz a operação abaixo
            printf("Digite seu nome: "); //pede o nome do usuario
            scanf("%s", pessoas[*usados].nome); //guarda o nome na variavel nome (dentro da struct)
            printf("Digite seu CPF: "); //pede o CPF do usuario
            scanf("%s", pessoas[*usados].cpf); //guarda o nome na variavel nome (dentro da struct)
            while (1){ //abre o loop para cadastrar o tipo de conta do usuario
            printf("Digite o tipo da sua conta: \n" //pede o tipo de conta
                   "1 - Comum;\n"
                   "2 - Plus\n"
                   "R: ");
            int tipotemp;
            scanf("%d", &tipotemp); //guarda a escolha na variavel para realizar a condicional
            if (tipotemp == 2){ //se o valor da variavel for 2, a taxa das operações se torna de 3% e o saldo fica negativo de até 5000.00
                pessoas[*usados].taxa = 0.03;
                pessoas[*usados].minimo = (-5000);
                break; //quebra o loop do tipo de conta e vai para a sessão de senha
            } else if(tipotemp == 1){ //se o valor da variavel for 1, a taxa das operações se torna de 3% e o saldo fica negativo de até 1000.00
                pessoas[*usados].taxa = 0.05;
                pessoas[*usados].minimo = (-3000);
                break; //quebra o loop do tipo de conta e vai para a sessão de senha
            }else{ //caso não seja nem 1 e nem 2, printa a proxima mensagem
                printf("Valor incorreto!\n");
                continue; //faz o loop voltar para o menu
            }
            }
            printf("Digite um valor inicial para colocar na conta: "); //pede ujm valor inicial para conta
            scanf("%lf", &pessoas[*usados].saldo); //guarda o valor na variavel saldo (dentro da struct)
            char senhaconfirma[20]; //variavel para guardar a primeira senha digitada
            char senhatemporaria[20]; //variavel para guardar a segunda senha digitada
            printf("Digite sua senha: "); //pede a primeira senha
            scanf("%s", senhatemporaria); //guarda a primeira senha nesta variavel
            printf("Confirma sua senha? R: "); //pede a segunda senha
            scanf("%s", senhaconfirma); //guarda a segunda senha nesta variavel
            int comparacao = stricmp(senhatemporaria,senhaconfirma); //compara se as senhas são iguais
            if (comparacao == 0){ //se forem iguais, guarda a senha na variavel senha (dentro da struct)
                strcpy(pessoas[*usados].senha,senhatemporaria);
                printf("Conta criada com sucesso!\n");
                //char tmpsaldo[500];
                //sprintf(tmpsaldo, "Conta criada.\n"
                //                  "Deposito : %.2lf", pessoas[*usados].saldo);
                //strcpy(grupo[*usados][0].info,tmpsaldo);
                //pessoas[*usados].transacao = 1;
                *usados+=1;
            } else{ //caso contrário, printa a próxima mensagem e realiza a operação novamente
                printf("Senha incorreta! Realize a operacao novamente!\n");
                continue;
            }
        } else{//caso o usuario nao queira continuar a operação, o loop se encerra e volta para o menu
            break;
        }
    }

}

void ApagarCliente (Cadastro *pessoas, int *usados, ExtratoCliente *grupo){
    char cpf[11]; //cria a variavel cpf para a verificação
    printf("Digite o cpf a ser removido: "); //pergunta qual cpf deve ser removido
    scanf("%s",cpf); //guarda o cpf digitado na variavel cpf
    int i;
    for (i = 0; i <= *usados+1; ++i) { //verifica em cada usuario cadastrado (atraves de usados) se o cpf existe
        int resultado = stricmp(cpf,pessoas[i].cpf); //faz a comparação do cpf digitado com os cpfs armazenados na variavel cpf
        if(resultado == 0){//se existir, esse loop de cpf se encerra e vai para proxima operação
            break;
        } else if(resultado != 0 && i>*usados){ //caso contrario, o programa printa a proxima mensagem e retorna o loop do inicio
            printf("CPF nao encontrado!\n");
            return;
        }else{//caso aconteça qualquer outra operação diferente das outras, o programa volta para o menu
            continue;
        }
    }
    while (1){ //loop de confirmação de senha
        char senhaconfirma[20]; //variavel para guardar a primeira senha digitada
        strcpy(senhaconfirma,pessoas[i].senha); //função que guarda a informação de senha do cpf digitado na primeira senha digitada
        char senhatemporaria[20]; //variavel para guardar a segunda senha digitada
        printf("Digite sua senha: "); //pede para digitar a segunda senha
        scanf("%s", senhatemporaria); //guarda a segunda senha na variavel
        int comparacao = stricmp(senhatemporaria,senhaconfirma); //compara se a primeira senha é igual a segunda
        if (comparacao == 0){//se for igual o loop quebra e vai para proxima operação
            break;
        } else {//caso contrario, printa a proxima mensagem e volta o programa para o menu
            printf("Senha incorreta! Realize a operacao novamente!\n");
            continue;
        }
    }

    int j;
    for (j = 0; j < 1001; ++j) { //verifica se o cpf existe dentro da struct
        int comparacao = stricmp(cpf,pessoas[j].cpf); //compara o cpf digitado com o cpf da struct
        if(comparacao == 0){ //se o cpf existir, a operação se realiza
            break;
    }
        }if(j==1001){ //i é equivalente ao valor dos indices do array, nosso array contendo 1000 espaços se ele percorrer 1001 como demonstrado no if significa que ele não existe no array, considerando o 1001 como um codigo de erro
        printf("CPF nao encontrado!\n");

    }else{//caso contrário, ele percorre as pessoas que existem na struct
        for (int h = j; h < 999; ++h) {
            pessoas[h] = pessoas[h+1];
            //grupo[h] = grupo[h+1];
            //printf("%s",pessoas[h].nome);//temporario
        }
    }
    *usados-=1; //retira o usuario de usados
    printf("Operacao concluida com sucesso!\n\n"); //finaliza a operação

    


}
void ListarClientes (Cadastro *pessoas, int *usados){
    printf("\n=========================================================================\n");
    for (int i = 0; i < *usados; ++i) { //vai fazer o loop de todos os usuarios cadastrados pela variavel usados
        printf("Usuario %d:\n",i+1); //printa o numero do usuario
        printf("Nome: %s\n",pessoas[i].nome); //printa o nome do usuario armazenado
        printf("CPF:%s\n",pessoas[i].cpf); //printa o cpf do usuario armazenado
        printf("-------------------------------------------------------------------------\n");
    }
    printf("=========================================================================\n\n");

}

void Debito (Cadastro *pessoas, int *usados, ExtratoCliente *grupo[]){
    char cpf[11]; //cria a variavel cpf para a verificação
    while (1) { //abre o loop de verificacao
        char mensagem[4]; //cria a variavel para guardar resposta da proxima pergunta
        printf("\n");
        printf("Quer continuar a operacao: (Sim ou Nao) R: \n");//pergunta se a pessoa quer continuar
        scanf("%s", mensagem); //recebe a mensagem
        int positivo = stricmp(mensagem, "Sim"); //compara o que tiver na variavel com a palavra sim
        if (positivo == 0) { //se for igual, realiza a operação de verificação do cpf
            printf("Digite seu CPF: "); //pede para digitar o cpf
            scanf("%s",cpf);//guarda na variavel cpf
            int i;
            for (i = 0; i <= *usados+1; ++i) {//verifica se o cpf existe pela variavel usados
                int resultado = stricmp(cpf,pessoas[i].cpf); //compara o cpf digitado com o cpfs armazenados na struct
                if(resultado == 0){//se a comparação for verdadeira, o loop se encerra e vai para proxima operação
                    break;
                } else if(resultado != 0 && i>*usados){//caso contrario, o programa printa a proxima mensagem e retorna o loop do inicio
                    printf("CPF nao encontrado!\n");
                    return;
                }else{//caso aconteça qualquer outra operação diferente das outras, o programa volta para o menu
                    continue;
                }
            }
            while (1){//loop de confirmação de senha
                char senhaconfirma[20];//variavel para guardar a primeira senha digitada
                strcpy(senhaconfirma,pessoas[i].senha);//função que guarda a informação de senha do cpf digitado na primeira senha digitada
                char senhatemporaria[20];//variavel para guardar a segunda senha digitada
                printf("Digite sua senha: ");//pede para digitar a segunda senha
                scanf("%s", senhatemporaria);//guarda a segunda senha na variavel
                int comparacao = stricmp(senhatemporaria,senhaconfirma);//compara se a primeira senha é igual a segunda
                if (comparacao == 0){//se for igual o loop quebra e vai para proxima operação
                    break;
                } else {//caso contrario, printa a proxima mensagem e volta o programa para o menu
                    printf("Senha incorreta! Realize a operacao novamente!\n");
                    continue;
                }
            }

            double valordigitado;//varialvel para receber o valor a ser debitado
            printf("Quanto deseja debitar da conta? R: ");//pede o valor a ser debitado
            scanf("%lf",&valordigitado);//guarda o valor na variavel
            if (pessoas[i].minimo <= pessoas[i].saldo - ((pessoas[i].taxa * valordigitado)+valordigitado)){ //se o minimo disponivel na conta for menor que o saldo da conta - a operação de taxa (do cpf digitado) sob o valor digitado
                pessoas[i].saldo = pessoas[i].saldo - (pessoas[i].taxa * valordigitado)-valordigitado; //o saldo muda e é realizada a operação de debito sob a taxa da conta do cpf digitado
                printf("Seu saldo atual eh: %.2lf", pessoas[i].saldo); //printa o saldo
            } else{//caso contrario, informa que a operação nao pode ser realizada e mostra o saldo
                printf("Valor do debito superior ao valor disponivel na conta!", pessoas[i].saldo);
            }




        } else{//caso o usuario nao queira continuar a operação, o loop se encerra e volta para o menu
            break;
        }
    }

}
void Deposito (Cadastro *pessoas, int *usados) {
    char cpf[11]; //cria a variavel cpf para a verificação
    int i;
    printf("Digite seu cpf para deposito: ");//pede o cpf para fazer o deposito
    scanf("%s",cpf);//guarda o cpf na variavel
    //int exec = 1;
    for (i = 0; i < *usados + 1; ++i) { //percorre o cpfs
        char comparativo[11];//variavel para receber o cpf vindo da struct
        strcpy(comparativo,pessoas[i].cpf);//paga o cpf escolhido e coloca na variavel comparativo para que na proxima operação seja possivel realizar a comparação
        int resultado = stricmp(cpf, comparativo); //faz com que a variavel resutado realize a comparacao entre o cpf digitado e o cpf comparativo

        if (resultado == 0) {//se existir, o loop quebra e para para a proxima operação
            break;
        } else if (resultado != 0 && i > *usados) {//caso contrario, o programa printa a proxima mensagem e retorna o loop do inicio
            printf("CPF nao encontrado!\n");
            return;
        } else {//caso aconteça qualquer outra operação diferente das outras, o programa volta para o menu
            continue;
        }

    }
    printf("Insira o valor a ser depositado: \n");//pede para inserir o valor a ser depositado
    double valor;
    scanf("%lf",&valor);//guarda o valor digitado
    pessoas[i].saldo = pessoas[i].saldo + valor; //realiza o deposito, pegando o valor da variavel saldo da struct e somando com a variavel valor
    printf("Seu saldo atual é %.2lf\n", pessoas[i].saldo);//printa o saldo da conta

}
void Extrato (Cadastro *pessoas ,int *usados, ExtratoCliente *grupo) {
    char cpf[11];
    while (1) {
        char mensagem[4];
        printf("\n");
        printf("Quer continuar a operacao: (Sim ou Nao) R: \n");
        scanf("%s", mensagem);
        int positivo = stricmp(mensagem, "Sim");
        if (positivo == 0) {
            printf("Digite seu CPF: ");
            scanf("%s", cpf);
            int i;
            for (i = 0; i <= *usados + 1; ++i) {
                int resultado = stricmp(cpf, pessoas[i].cpf);
                if (resultado == 0) {
                    break;
                } else if (resultado != 0 && i > *usados) {
                    printf("CPF nao encontrado!\n");
                    return;
                } else {
                    continue;//Isso funciona? O código chega nesse cara? SIM
                }
            }
            while (1) {
                char senhaconfirma[20];
                strcpy(senhaconfirma, pessoas[i].senha);
                char senhatemporaria[20];
                printf("Digite sua senha: ");
                scanf("%s", senhatemporaria);
                int comparacao = stricmp(senhatemporaria, senhaconfirma);
                if (comparacao == 0) {
                    break;
                } else {
                    printf("Senha incorreta! Realize a operacao novamente!\n");
                    continue;
                }
            }


        }
    }
}


}


void Transferencia (Cadastro *pessoas, int *usados){
    char cpf[11];//variavel que guarda o cpf de origem
    char cpf2[11];//variavel que guarda o cpf de destino
    int i;
    int j;
    printf("Digite seu cpf de origem: ");//pede o cpf de origem
    scanf("%s",cpf);//guarda o cpf digitado na variavel cpf
    //int exec = 1;
    for (i = 0; i < *usados + 1; ++i) {//abre o loop para verificação do cpf
        char comparativo[11];//variavel que vai receber o cpf de comparação
        strcpy(comparativo, pessoas[i].cpf); //coloca o cpf vindo da struct na variavel comparativo
        int resultado = stricmp(cpf, comparativo);//compara o cpf de comparativo com o cpf digitado
        if (resultado == 0) {//se existir, o loop quebra e para para a proxima operação
            break;
        } else if (resultado != 0 && i > *usados) {//caso contrario, o programa printa a proxima mensagem e retorna o loop do inicio
            printf("CPF nao encontrado!\n");
            return;
        } else {//caso aconteça qualquer outra operação diferente das outras, o programa volta para o menu
            continue;
        }
    }
    while (1){//loop de confirmação de senha
        char senhaconfirma[20];//variavel para guardar a primeira senha digitada
        strcpy(senhaconfirma,pessoas[i].senha);//função que guarda a informação de senha do cpf digitado na primeira senha digitada
        char senhatemporaria[20];//variavel para guardar a segunda senha digitada
        printf("Digite sua senha: ");//pede a senha
        scanf("%s", senhatemporaria);//guarda a senha digitada na variavel
        int comparacao = stricmp(senhatemporaria,senhaconfirma);//compara se a primeira senha é igual a segunda
        if (comparacao == 0){//se for igual, o loop quebra e passa para proxima operação
            break;
        } else {//caso contrario, printa a proxima mensagem e vai para o menu
            printf("Senha incorreta! Realize a operacao novamente!\n");
            continue;
        }
    }
        printf("Digite seu CPF de destino: ");//pede o cpf para destino da transferencia
        scanf("%s",cpf2);//recebe o cpf
        for (j = 0; j < *usados + 1; ++j) {//abre o loop para verificação do cpf
            char comparativo[11];//variavel que vai receber o cpf de comparação
            strcpy(comparativo, pessoas[j].cpf);//coloca o cpf vindo da struct na variavel comparativo
            int resultado = stricmp(cpf2, comparativo);//compara o cpf de comparativo com o cpf digitado
            if (resultado == 0) {//se existir, o loop quebra e para para a proxima operação
                break;
            } else if (resultado != 0 && j > *usados) {//caso contrario, o programa printa a proxima mensagem e retorna o loop do inicio
                printf("CPF nao encontrado!\n");
                return;
            } else {//caso aconteça qualquer outra operação diferente das outras, o programa volta para o menu
                continue;
            }
        }
        double transferencia;//variavel para receber o valor da transferencia
        printf("quanto deseja transferir? \n");//pede o valor da transferencia
        scanf("%lf", &transferencia);//recebe o valor da tranferencia
        pessoas[i].saldo-=transferencia;//retira do saldo do cpf de origem o valor da tranferencia
        pessoas[j].saldo+=transferencia;//adiciona do saldo do cpf de destino o valor da tranferencia
    printf("O saldo atual da conta de origem é %.2lf\n", pessoas[i].saldo);//printa o saldo do cpf de destino

}