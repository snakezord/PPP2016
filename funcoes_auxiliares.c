#include "estrutura.h"

/* compara 2as Horas "a" e "b"
 *
 * se "a" e "b" são mesma hora returns 0
 * se "a" esta depois de b returns -1
 * se "a" esta antes de b returns 1
*/
int compara_horas(Hora a,Hora b) {
    if ((a.hora == b.hora) && (a.minutos == b.minutos))
        return 0; /* a = b */
    else if ((a.hora > b.hora) || ((a.hora == b.hora) && (a.minutos > b.minutos)))
        return -1; /* a depois de b */
    else
        return 1; /* b depois de a */

}

/* compara 2as Datas "a" e "b"
 *
 * se "a" e "b" são mesma data returns 0
 * se "a" esta depois de b returns -1
 * se "a" esta antes de b returns 1
*/
int compara_datas(Data a,Data b) {
    if ((a.dia==b.dia) && (a.mes==b.mes) && (a.ano==b.ano))
        return 0; /* a = b */
    if ((a.ano>b.ano) || ((a.ano==b.ano) && (a.mes>b.mes)) || ((a.ano==b.ano) && (a.mes==b.mes) && (a.dia>b.dia)))
        return -1; /* a depois de b */
    else
        return 1; /* b depois de a */
}

/* max_dia_mes devolve o ultimo dia desse especifico mes
 *
 * (verifica se é Fevreiro e se é ano bissexto)
*/
int max_dia_mes(int ano,int mes) {
    int max_dia;

    if(mes == 2) {
        if(ano % 4 == 0) {
            max_dia = 29;
        } else {
            max_dia = 28;
        }
    } else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        max_dia = 30;
    } else {
        max_dia = 31;
    }

    return max_dia;
}

/* horas_possiveis calcula todas as n horas que começam as hora:minutos com espaços de 30min entre cada
 * hora possivel  */
void horas_possiveis(Hora hora_disponivel[], int n, int hora, int minutos) {
    int i;

    for (i = 0; i < n; i++) {
        hora_disponivel[i].hora = hora;
        hora_disponivel[i].minutos = minutos;

        if (minutos == 30) {
            hora += 1;
            minutos -= 30;
        } else {
            minutos += 30;
        }
    }
}

/* mesma_hora compara as horas de dois exames(1 e 2)
 * para verificar se extão sobrepostos
 *
 * returns
 *      veririca se os exames começam na mesma hora (I1_I2 == 0)
 *      ou
 *      veririca se os exames acabam na mesma hora (F1_F2 == 0)
 *      ou
 *      verifica se exame 2 começa no meio do exame 1 (I2_entre1)
 *      ou
 *      verifica se exame 2 acaba no meio do exame 1 (F2_entre1)
*/
int mesma_hora(Hora inicio1, Hora final1, Hora inicio2, Hora final2) {
    int I1_I2, F1_I2, F2_I1, F1_F2;
    int F2_entre1;
    int I2_entre1;

    I1_I2 = compara_horas(inicio1,inicio2);
    F1_F2 = compara_horas(final1, final2);
    F1_I2 = compara_horas(final1, inicio2);
    F2_I1 = compara_horas(inicio1, final2);

    /* exame 2 começa no meio do exame 1*/
    I2_entre1 = (I1_I2 == 1) && (F1_I2 == -1);
    /* exame 2 acaba no meio do exame 1*/
    F2_entre1 = (F2_I1 == 1) && (F1_F2 == -1);
    /* começam na mesma hora (I1_I2 == 0) ou acabam na mesma hora (F1_F2 == 0)*/
    return F2_entre1 || I2_entre1 || (I1_I2 == 0) || (F1_F2 == 0);
}

/* Transforma o char do fgets para inteiro */
int devolve_int(char *temp) {
    int i, num, len = strlen(temp) - 1;

    for(i = 0; i < len; i++) {
        if(!isdigit(temp[i]))
            return 0;
    }
    num = atoi(temp);

    return num;
}

/* recebe o valor do num(int) do fgets */
void recebe_str(int *num) {
    char *temp = (char*) malloc (MAX * sizeof(char));

    fflush(stdin);
    fgets(temp, MAX, stdin);
    *num = devolve_int(temp);
    free(temp);
}





/* questão de sim ou não para confirmar se o utilizador quer mudar alguma coisa */
char verifica_resposta() {
    char *temp = (char*)malloc(MAX * sizeof(char));
    char resposta;

    printf("Pretende alterar(s/n)? ");
    fgets(temp, MAX ,stdin);
    resposta = temp[0];
    free(temp);

    return resposta;
}


/* usada em funcoes_disciplinas.c e funcoes_alunos.c para imprimir a string desejada
* e mudar os seus dados , recebe '0' quando é para alterar strings, recebe '-1' quando é para alterar regime
* e recebe 'outro numero qualquer' quando é para alterar outra coisa qualquer
* nomeadamente numeros como numero de estudante, datas, horas
*/
void confirma_resposta(char print[], int *num, char str[]) {
    char resposta = verifica_resposta();
    char *temp = (char*)malloc(MAX * sizeof(char));

    if(resposta == 's') {
        printf("%s", print);

        if(num == 0) {
            fgets(temp, MAX, stdin);
            strcpy(str, temp);

        } else if(*num == -1) {
            regime(str);

        } else{
            fgets(temp, MAX, stdin);
            *num = devolve_int(temp);
        }
    }
    free(temp);
}
