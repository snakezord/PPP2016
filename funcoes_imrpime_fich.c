#include "estrutura.h"

/* importa_disciplinas importa todas informaçoes da Lista_disciplinas lista para ficheiro
 * disciplinas.txt */
void importa_disciplinas(Lista_Disciplinas lista){
    FILE *disciplinas;
    char *p;

    disciplinas = fopen("disciplinas.txt", "w");
    while(lista->next != NULL) {
        lista = lista->next;
        p = strchr(lista->disciplina.nome, '\n');
        *p = '\0';
        fprintf(disciplinas, "%s,", lista->disciplina.nome);

        p = strchr(lista->disciplina.regente, '\n');
        *p = '\0';
        fprintf(disciplinas," %s;\n", lista->disciplina.regente);
    }
    fclose(disciplinas);

}


/* importa_dalunos importa todas informaçoes da Lista_Alunos lista para ficheiro
 * alunos.txt */

void importa_alunos(Lista_Alunos lista) {
    FILE *alunos;
    char *p;

    alunos = fopen("alunos.txt", "w");
    while(lista->next != NULL) {
        lista = lista->next;

        p = strchr(lista->aluno.nome, '\n');
        *p = '\0';
        fprintf(alunos, " %s,", lista->aluno.nome);

        fprintf(alunos, "%d,", *lista->aluno.numero_de_estudante);

        p = strchr(lista->aluno.curso, '\n');
        *p = '\0';
        fprintf(alunos, " %s,", lista->aluno.curso);

        fprintf(alunos, " %d,", *lista->aluno.ano_de_matricula);

        p = strchr(lista->aluno.regime, '\n');
        *p = '\0';
        fprintf(alunos, " %s;\n", lista->aluno.regime);
    }
    fclose(alunos);
}

/* imrpime_info_exames mostra quase toda info necessaria dos exames no fich
 * exames.txt */


void imrpime_info_exames(Exame head, FILE *exames) {
        fprintf(exames, "%s, ", head.nome);
        fprintf(exames, "%s, ", head.epoca);
        fprintf(exames, "%d/ ", head.data.dia);
        fprintf(exames, "%d/ ", head.data.mes);
        fprintf(exames, "%d, ", head.data.ano);
        fprintf(exames, "%d: ", head.hora.hora);
        fprintf(exames, "%d, ", head.hora.minutos);
        fprintf(exames, "%d: ", head.duracao.hora);
        fprintf(exames, "%d, ", head.duracao.minutos);
        fprintf(exames, "%d: ", head.fim.hora);
        fprintf(exames, "%d;\n", head.fim.minutos);
}


/* importa_exames importa toda data de Lista_Exames lista para fich exames.txt */

void importa_exames(Lista_Exames head) {
    FILE *exames;
    Lista_Alunos alunos, copia;
    Lista_Salas salas, copia_disciplina;
    int i;

    exames = fopen("exames.txt", "w");
    fprintf(exames, "%d", *head->exame.nome );
    fprintf(exames, "%d", *head->exame.epoca );

    while(head->next != NULL) {
        head = head->next;
        i = 0;

        imrpime_info_exames(head->exame, exames);
        alunos = head->exame.alunos_inscritos;
        copia = alunos;
        while(copia->next != NULL) {
            copia = copia->next;
            i++;
        }

        fprintf(exames, "%d;", i);
        while(alunos->next != NULL) {
            alunos = alunos->next;
            fprintf(exames, " %d,", *alunos->aluno.numero_de_estudante);
        }

        i = 0;
        salas = head->exame.salas;
        copia_disciplina = salas;
        while(copia_disciplina->next != NULL) {
            copia_disciplina = copia_disciplina->next;
            i++;
        }

        fprintf(exames, "\n%d;", i);
        while(salas->next != NULL) {
            salas = salas->next;
            fprintf(exames, " %s.", salas->sala.nome);
        }
    }
    fclose(exames);
}

/* importa_aluno_exames importa toda data de Lista_Aluno_Exames lista para
 * fich aluno_exames.txt */
void importa_aluno_exames(Lista_Aluno_Exames head) {
    FILE *al_exames;
    int n;
    Lista_Exames copia;

    al_exames = fopen("aluno_exames.txt", "w");

    while(head->next != NULL) {
        head = head->next;

        fprintf(al_exames, "%d; ", *head->data.a.numero_de_estudante);

        copia = head->data.inscrito;
        n = 0;
        while(copia->next != NULL) {
            copia = copia->next;
            n++;
        }
        fprintf(al_exames, "%d;", n);

        while(head->data.inscrito->next != NULL) {
            head->data.inscrito = head->data.inscrito->next;
            fprintf(al_exames, " %d,", head->data.inscrito->exame.nome);
            fprintf(al_exames, " %d,", head->data.inscrito->exame.epoca);
        }
        fprintf(al_exames, "\n");
    }
    fclose(al_exames);
}



