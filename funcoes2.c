#include "estrutura.h"

int compara_datas(Data* d1, Data* d2,Hora* h1, Hora* h2){
    int data_1, data_2;
    data_1 = d1->ano*10000 + d1->mes*100 + d1->dia;
    data_2 = d2->ano*10000 + d2->mes*100 + d2->dia;
    if(data_1 > data_2){
            return 1;
        }
    else if(data_1 < data_2){
            return -1;
        }
    else{
            data_1 = h1->hora*100 + h1->minutos;
            data_2 = h2->hora*100 + h2->minutos;
            if(data_1 > data_2){
                    return 1;
                }
            else if(data_1 < data_2){
                return -1;
                }
            else{
                return 0;
                }
        }
}


int verifica_data(Data *data){
    int dia,mes,ano;
    dia = data->dia;
    mes = data->mes;
    ano = data->ano;

    if((dia>=1) && (mes>=1 && mes<= 12) && ano>=0){
        if(mes==2){
            if (dia<=28){
                 return 1;
            }
            else if (((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0))) && dia==29){
                return 1;
            }

        }
        else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia<=30)){
            return 1;
            }

        else if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 8 || mes == 10 || mes == 12) && (dia<=31)){
            return 1;
            }

    }
    return 0;
}

int verifica_hora(Hora *hora){
    int horas,minutos;

    horas = hora->hora;
    minutos = hora->minutos;

    if ((horas < 0) || (horas>23) || (minutos<0) || (minutos>59)){
            return 0;
        }
        return 1;
}

int devolve_int(char *temp) {
    int i, num, len = strlen(temp) - 1;

    for(i = 0; i < len; i++) {
        if(!isdigit(temp[i]))
            printf("Apenas sao permitidos numeros inteiros!");
    }
    num = atoi(temp);

    return num;
}

void recebe_str_to_int(int *num) {
    char *temp = (char*) malloc (MAX * sizeof(char));

    fgets(temp, MAX, stdin);
    *num = devolve_int(temp);
}


int verifica_epoca(char*epoca){
    char *epoca1 = "Normal";
    char *epoca2 = "Recurso";
    char *epoca3 = "Especial";

    if (strcmp(epoca,epoca1)==0)
        return 1;
    else if (strcmp(epoca,epoca2) ==0)
        return 1;
    else if (strcmp(epoca,epoca3)==0)
        return 1;
    else
        return 0;
}

void verifica_aluno_exames(Lista_Aluno_Exames lista, Aluno aluno){
    Lista_Aluno_Exames atual, useless;

    if(lista->next != NULL){
        procura_lista_aluno_exames(lista, aluno.numero_de_estudante, &useless, &atual);
        if(atual == NULL)
            insere_aluno_exames(&lista, aluno);
    }else{
        insere_aluno_exames(&lista, aluno);
    }
}


int tamanho_da_lista_alunos(Lista_Alunos lista){
    int tam = 0;
    while(lista->next != NULL){
        tam++;
    }
    return tam;
}


void swap(Lista_Alunos a, Lista_Alunos b) {
    Aluno temp = a->aluno;

    a->aluno = b->aluno;
    b->aluno = temp;
}

void bubble_sort(Lista_Alunos lista) {
    int swapped;
    Lista_Alunos ptr1, ptr2 = NULL;

    do {
        swapped = 0;
        ptr1 = lista->next;

        while(ptr1->next != ptr2) {
            if(ptr1->aluno.numero_de_estudante > ptr1->next->aluno.numero_de_estudante) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr2 = ptr1;
    }
    while(swapped);
}
