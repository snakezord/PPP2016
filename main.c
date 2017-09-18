#include "estrutura.h"
void menu_alunos(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams)
{
    int opcao;

    printf("[1] Criar dados de aluno.\n");
    printf("[2] Alterar dados de aluno.\n");
    printf("[3] Apagar dados de aluno.\n");
    printf("[4] Mostrar exames inscritos por aluno.\n");
    printf("[5] Voltar ao menu anterior.\n");

    recebe_str(&opcao);
    system("cls");

    switch(opcao)
    {
        case 1:
            cria_aluno(alunos);
            escreve_alunos(alunos);
            break;
        case 2:
            altera_aluno(alunos);
            imprime_lista_alunos(alunos);
            escreve_alunos(alunos);
            break;
        case 3:
            elimina_aluno_da_lista(alunos);
            escreve_alunos(alunos);
            break;
        case 4:
            imprime_exames_inscritos_aluno(aluno_exams, alunos);
           /* imprime_exames_inscritos_aluno(aluno_exams, alunos);*/
            break;
        case 5:
            menu(alunos, disciplinas, exams, aluno_exams);
            break;
        default:
            system("cls");
            printf("Opcao invalida!\n");
            }
            menu_alunos(alunos, disciplinas, exams, aluno_exams);

}

void menu_exames(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams)
{
    int opcao;

    printf("[1] Criar exame.\n");
    printf("[2] Inscrever aluno num exame.\n");
    printf("[3] Mostrar exames.\n");
    printf("[4] Mostrar alunos inscritos num exame.\n");
    printf("[5] Apagar exames ja realizados.\n");
    printf("[6] Voltar ao menu anterior.\n");

    recebe_str(&opcao);
    system("cls");

    switch(opcao)
    {
        case 1:
            cria_exame(exams, disciplinas);
            escreve_exames(exams);
            break;
        case 2:
            inscrever_alunos(alunos, exams, aluno_exams);
            break;
        case 3:
            imprime_lista_exames(exams);
            break;
        case 4:
            imprime_alunos_inscritos_exame(exams);
            break;
        case 5:
            remove_da_lista_exame(exams,aluno_exams);
            escreve_exames(exams);
            break;
        case 6:
            menu(alunos, disciplinas, exams, aluno_exams);
            break;

        default:
            system("cls");
            printf("Opcao invalida!\n");
            }
            menu_exames(alunos, disciplinas, exams, aluno_exams);

}
void menu_disciplinas(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams)
{
    int opcao;

    printf("[1] Criar dados de disciplina.\n");
    printf("[2] Alterar dados de disciplina.\n");
    printf("[3] Apagar dados de disciplina.\n");
    printf("[4] Voltar ao menu anterior.\n");

    recebe_str(&opcao);
    system("cls");

    switch(opcao)
    {
        case 1:
            cria_disciplina(disciplinas);
            escreve_disciplinas(disciplinas);
            break;
        case 2:
            altera_disciplina(&disciplinas);
            escreve_disciplinas(disciplinas);
            break;
        case 3:
            remove_da_lista_disciplina(disciplinas);
            escreve_disciplinas(disciplinas);
            break;
        case 4:
            menu(alunos, disciplinas, exams, aluno_exams);
            break;
        default:
            system("cls");
            printf("Opcao invalida!\n");
            }
            menu_disciplinas(alunos, disciplinas, exams, aluno_exams);


}



void menu(Lista_Alunos alunos, Lista_Disciplinas disciplinas, Lista_Exames exams, Lista_Aluno_Exames aluno_exams)
{
    int opcao;

    printf("MENU:\n");
    printf("[1] Alunos\n");
    printf("[2] Disciplinas\n");
    printf("[3] Exames\n");
    printf("[4] Sair\n");


    recebe_str(&opcao);
    system("cls");

    switch(opcao)
    {
        case 1:
            menu_alunos(alunos, disciplinas, exams, aluno_exams);
            break;
        case 2:
            menu_disciplinas(alunos, disciplinas, exams, aluno_exams);
            break;
        case 3:
            menu_exames(alunos, disciplinas, exams, aluno_exams);
            break;
        case 4:
            printf("PROGRAMA TERMINADO.\n");
            break;
          }

}

int main()
{
    Lista_Alunos alunos;
    Lista_Disciplinas disciplinas;
    Lista_Exames exams;
    Lista_Aluno_Exames aluno_exams;

    alunos = cria_lista_alunos();
    disciplinas = cria_lista_disciplinas();
    exams = cria_lista_exames();
    aluno_exams = cria_lista_aluno_exames();

    /*le_aluno(alunos);
    le_exame(exams);
    le_disciplinas(disciplinas);*/
    menu(alunos,disciplinas,exams, aluno_exams);
    imprime_lista_alunos(alunos);
    return 0;
}

