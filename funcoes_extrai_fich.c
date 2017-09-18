#include "estrutura.h"

/* extrai_disciplinas invia toda informacao de disciplinas.txt to Lista_Disciplinas lista */

void append(FILE *fich, char chave, char *string1) {
    char *string2 = (char*)malloc(MAX * sizeof(char));

    while(!strchr(string1, chave)) {
        fscanf(fich, "%s", string2);
        strcat(string1, " ");
        strcat(string1, string2);
    }
    free(string2);
}

void procura_string(FILE *fich, char chave, char *string) {
    char *p;

    append(fich, chave, string);
    p = strchr(string, chave);
    *p = 0;
    strcat(string, "\n");
}


void recebe_string_fich(FILE *fich, char chave, char **str_aux, char *string) {

    procura_string(fich, chave, string);
    *str_aux= string;
}

void recebe_string_fich_fscan(FILE *fich, char chave, char **str_aux) {
    char *string = (char*)malloc(MAX * sizeof(char));

    fscanf(fich, "%s", string);
    procura_string(fich, chave, string);
    *str_aux = string;
}


void extrai_disciplinas(Lista_Disciplinas head) {
    FILE *disciplinas;
    Disciplina temp;
    char *string = (char*)malloc(MAX * sizeof(char));

    disciplinas = fopen("disciplinas.txt", "r");

    while(fscanf(disciplinas, "%s", string) != EOF) {
            recebe_string_fich(disciplinas, ',', &temp.nome, string);

            recebe_string_fich_fscan(disciplinas, ';', &temp.regente);
            string = (char*)malloc(MAX * sizeof(char));
            insere_lista_disciplina(head, temp);
    }
    fclose(disciplinas);
}



