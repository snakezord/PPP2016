#define ESTRUTURA_H_INCLUDED
#include <ctype.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 200
#define ANO 2017
/* --------------ESTRUTURAS--------------*/

typedef struct disciplina
{
    char *nome;
    char *regente;
}Disciplina;

typedef struct sala
{
    char *nome;
}Sala;

typedef struct data
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct hora
{
    int hora;
    int minutos;
}Hora;


typedef struct aluno
{
    int *numero_de_estudante;
    int *ano_de_matricula;
    char *nome;
    char *curso;
    char *regime;
}Aluno;


/* ----------------------------------*/
typedef struct node_alunos *Lista_Alunos;
typedef struct node_salas *Lista_Salas;
typedef struct node_exames *Lista_Exames;
/* ----------------------------------*/

typedef struct exame
{
    char *nome;
    char *epoca;
    Disciplina *disciplina;
    Data data;
    Hora hora;
    Hora duracao;
    Hora fim;
    Lista_Alunos alunos_inscritos;
    Lista_Salas salas;
}Exame;


typedef struct aluno_exames {
    Aluno a;
    Lista_Exames inscrito;
}Aluno_Exames;


/* ----------------------------------*/
typedef struct node_disciplinas* Lista_Disciplinas;
typedef struct node_aluno_exames *Lista_Aluno_Exames;
/* ----------------------------------*/

/* --------------LISTAS--------------*/


typedef struct node_alunos
{
    Aluno aluno;
    Lista_Alunos next;
}Node_Lista_Alunos;


typedef struct node_disciplinas
{
    Disciplina disciplina;
    Lista_Disciplinas next;
}Node_Lista_Disciplinas;


typedef struct node_exames
{
    Exame exame;
    Lista_Exames next;
}Node_Lista_Exames;

typedef struct node_salas
{
    Sala sala;
    Lista_Salas next;
}Node_Lista_Salas;

typedef struct node_aluno_exames
{
    Aluno_Exames data;
    Lista_Aluno_Exames next;
} Node_Lista_Aluno_Exames;


/* --------------FUNCOES--------------*/
int compara_horas(Hora a,Hora b);
int compara_datas(Data a,Data b);
int max_dia_mes(int ano,int mes);
void horas_possiveis(Hora hora_disponivel[], int n, int hora, int minutos);
int verifica_hora(Hora *hora);
int devolve_int(char *temp);
void recebe_str(int *num);
int verifica_epoca(char*epoca);
char verifica_resposta();
void confirma_resposta(char print[], int *num, char str[]);
Lista_Aluno_Exames cria_lista_aluno_exames();
void procura_lista_aluno_exames(Lista_Aluno_Exames lista, int numero_estudante, Lista_Aluno_Exames *ant, Lista_Aluno_Exames *atual);
void insere_lista_aluno_exames(Lista_Aluno_Exames *lista, Aluno al);
void verifica_lista_aluno_exames(Lista_Aluno_Exames lista, Aluno al);
int aceitavel_exame(Exame ex, Aluno al);
void insere_aluno_alex_exames(Lista_Aluno_Exames lista, Aluno aluno, Exame novo);
void inscrever_alunos(Lista_Alunos l_alunos, Lista_Exames l_exames, Lista_Aluno_Exames submeter);
void imprime_alunos_inscritos_exame(Lista_Exames lista);
void imprime_exames_inscritos_aluno(Lista_Aluno_Exames lista, Lista_Alunos l_alunos);
Lista_Alunos cria_lista_alunos();
void procura_lista_alunos(Lista_Alunos lista, int numero_estudante, Lista_Alunos *ant, Lista_Alunos *atual);
void remove_da_lista_alunos(Lista_Alunos lista, int numero_estudante);
void insere_lista_aluno(Lista_Alunos *lista, Aluno novo);
void imprime_lista_alunos(Lista_Alunos lista);
void elimina_aluno_da_lista(Lista_Alunos lista);
int aluno_existe(Lista_Alunos lista, int numero_estudante);
void cria_aluno(Lista_Alunos lista);
void escolhe_aluno(Lista_Alunos *lista);
void altera_aluno(Lista_Alunos lista);
int tamanho_da_lista_alunos(Lista_Alunos lista);
Lista_Disciplinas cria_lista_disciplinas();
void procura_lista_disciplinas(Lista_Disciplinas lista, Disciplina chave, Lista_Disciplinas *ant, Lista_Disciplinas *atual);
void remove_da_lista_disciplina_aux(Lista_Disciplinas lista, Disciplina chave);
void imprime_lista_disciplinas(Lista_Disciplinas lista);
void insere_lista_disciplina(Lista_Disciplinas lista, Disciplina nova);
void cria_disciplina(Lista_Disciplinas lista);
void escolhe_disciplina(Lista_Disciplinas *lista);
void altera_disciplina(Lista_Disciplinas *lista);
void remove_da_lista_disciplina(Lista_Disciplinas lista);
Lista_Exames cria_lista_exames();
Lista_Salas cria_lista_salas();
void imprime_lista_salas(Lista_Salas lista);
void imprime_lista_exames(Lista_Exames lista);
int procura_sala(Lista_Exames lista, Sala sala);
void procura_lista_exames(Lista_Exames lista, char *nome, char *epoca, Lista_Exames *ant, Lista_Exames *atual);
void remove_da_lista_exame_aux(Lista_Exames lista, char *nome, char *epoca);
void insere_lista_exame(Lista_Exames *lista, Exame novo);
void insere_lista_sala(Lista_Salas lista, Sala nova);
void escolhe_sala(Lista_Exames lista, Sala nova);
void aux_data_possivel_sala(Lista_Exames lista, Lista_Exames *node, Data data);
void aux_hora_possivel_sala(Lista_Exames lista, Lista_Exames *node, Hora hora, Hora fim);
void possivel_sala(Lista_Exames lista, Data data, Hora hora, Hora fim, Lista_Salas sala_exame);
void escolhe_exame(Lista_Exames lista, Lista_Exames *ant, Lista_Exames *atual);
void remove_da_lista_exame(Lista_Exames lista, Lista_Aluno_Exames lista2);
void escreve_alunos(Lista_Alunos lista);
void escreve_disciplinas(Lista_Disciplinas lista);
void escreve_exames(Lista_Exames exams);
void le_aluno(Lista_Alunos lista);
void le_exame(Lista_Exames lista);
void le_disciplinas(Lista_Disciplinas lista);
void cria_exame(Lista_Exames lista, Lista_Disciplinas disciplinas);
int mesma_hora(Hora inicio1, Hora final1, Hora inicio2, Hora final2);
void epoca_exame(char str[]);
void regime(char str[]);
void menu_alunos(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams);
void menu_exames(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams);
void menu_disciplinas(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams);
void menu(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams);
