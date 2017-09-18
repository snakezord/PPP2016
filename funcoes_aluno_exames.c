#include "estrutura.h"

/* cria_lista_aluno_exames devolve uma nova Lista_Aluno_Exames*/
Lista_Aluno_Exames cria_lista_aluno_exames()
{
    Lista_Aluno_Exames info;

    info = (Lista_Aluno_Exames)malloc(sizeof(Node_Lista_Aluno_Exames));
    if(info != NULL)
        info->next = NULL;
    else
        printf("Ocorreu erro na alocacao de memoria!");
    return info;
}

/* procura_lista_aluno_exames procura o numero de aluno na Lista_Aluno_Exames
 * Se encontrar, o atual vai para a posição do numero de estudante Aluno_Exames procurado
 * Se não encontrar, o atual passa a NULL
 */
void procura_lista_aluno_exames(Lista_Aluno_Exames lista, int numero_estudante, Lista_Aluno_Exames *ant, Lista_Aluno_Exames *atual)
{
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && *(*atual)->data.a.numero_de_estudante < numero_estudante)
    {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if((*atual) != NULL && *(*atual)->data.a.numero_de_estudante != numero_estudante)
        *atual = NULL;
}

/* insere_lista_aluno_exames insere o novo Aluno_Exames na Lista_Aluno_Exames *lista
 * associando Aluno al com Lista_Exames vazia*/
void insere_lista_aluno_exames(Lista_Aluno_Exames *lista, Aluno al){
    Lista_Aluno_Exames node, ant, useless;
    Aluno_Exames novo;

    novo.a = al;
    novo.inscrito = cria_lista_exames();

    node = (Lista_Aluno_Exames)malloc(sizeof(Node_Lista_Aluno_Exames));
    if(node != NULL){
        node->data = novo;
        procura_lista_aluno_exames(*lista, *novo.a.numero_de_estudante, &ant, &useless);
        node->next = ant->next;
        ant->next = node;
    }
}

/* verifica_lista_aluno_exames verifica se existe Aluno al na Lista_Aluno_Exames lista
 *
 * se a lista for vazia, o Aluno al é adicionado á lista
 *
 * se a lista não estiver vazia, veririfca se o Aluno al está na lista
 *
*/
void verifica_lista_aluno_exames(Lista_Aluno_Exames lista, Aluno al){
    Lista_Aluno_Exames atual, useless;

    if(lista->next != NULL){
        procura_lista_aluno_exames(lista, *al.numero_de_estudante, &useless, &atual);
        if(atual == NULL)
            insere_lista_aluno_exames(&lista, al);
    }else{
        insere_lista_aluno_exames(&lista, al);
    }
}

/* aceitavel_exame verifica se o aluno é elegível para o Exame ex
 *
 * se o exame tiver Epoca Especial
 *      e se o aluno tiver o regime normal e tiver o ano_de_matricula diferente
 *      do último ano (3). O aluno não é elegível para o exame.
 *          imprime "Este aluno nao esta elegivel para este exame."
 *          e returns 1
 *      else o aluno é elegível para o exame e returns 0
 * else o exame não tem condicoes especiais então returns 0
*/
int aceitavel_exame(Exame ex, Aluno al){
    if(strncmp(ex.epoca, "Epoca Especial", 14) == 0){
        if((strncmp(al.regime, "Normal", 6) == 0) && (*al.ano_de_matricula != 3)){
            printf("Este aluno nao pode fazer este exame. \n");
            return 1;
        } else return 0;
    }else return 0;
}

/* insere_aluno_alex_exames insere exame no Aluno al em Lista_Aluno_Exames
 * lista
 *
 * depois procura pelo aluno na lista e devolve o atual(O sítio na Lista_Aluno_Exames onde o aluno está)
 *
 * insere o novo exame na Lista_Exames inscrito na estrutura Aluno_Exames
*/
void insere_aluno_alex_exames(Lista_Aluno_Exames lista, Aluno al, Exame novo){
    Lista_Aluno_Exames atual, useless;

    procura_lista_aluno_exames(lista, *al.numero_de_estudante, &useless, &atual);
    insere_lista_exame(&atual->data.inscrito, novo);
    }


/* inscrever_alunos inscreve um aluno em exame
 *
 * se a Lista_Exames e a Lista_Alunos não estiverem vazias
 *      pede ao utilizador qual exame quer
 *      e pede ao utilizaodor qual aluno quer
 *      verifica se o aluno é aceitável para o exame(aceitavel_exame)
 *      se for
 *         verifica se o aluno já está na Lista_Aluno_Exames
 *         e verifica se a (Lista_Alunos alunos_inscritos), associada a estrutura Exame, está vazia
 *         se estiver:
 *              insere o aluno á (Lista_Alunos alunos_inscritos)(insere_lista_aluno) e á (Lista_Aluno_Exames submeter)
 *              associando o aluno á exame (insere_aluno_alex_exames)
 *         se não estiver:
 *              procura o aluno na (Lista_Alunos alunos_inscritos)
 *              se encontrar, significa que esse aluno já está inscrito no exame
 *              depois ordena a lista(bubble_sort) e insere o aluno á (Lista_Alunos alunos_inscritos)
 *              e á (Lista_Aluno_Exames submeter)
 *              associando o aluno á exame (insere_aluno_alex_exames)
 *
 *              no final verifica se estão 30 alunos inscritos no exame
 *              se estiverem, significa que a sala está cheia e portanto pede outra sala
*/
void inscrever_alunos(Lista_Alunos l_alunos, Lista_Exames l_exames, Lista_Aluno_Exames submeter){
    int numero_alunos;
    Lista_Exames ex_copia = l_exames, ant, atual;
    Lista_Alunos inscritos, atual_2, useless;

    if(l_exames->next != NULL && l_alunos->next != NULL){
        printf("\n\n@@@ Inscricao de Aluno @@@\n\n");
        escolhe_exame(l_exames, &ant, &atual);

        escolhe_aluno(&l_alunos);

        if(aceitavel_exame(atual->exame, l_alunos->aluno) != 1){

            verifica_lista_aluno_exames(submeter, l_alunos->aluno);
            inscritos = atual->exame.alunos_inscritos;

            if(inscritos->next == NULL){
                insere_lista_aluno(&inscritos, l_alunos->aluno);
                insere_aluno_alex_exames(submeter, l_alunos->aluno, atual->exame);
                } else{
                    numero_alunos = tamanho_da_lista_alunos(inscritos);
                    procura_lista_alunos(inscritos, *l_alunos->aluno.numero_de_estudante, &useless, &atual_2);

                    if(atual_2 != NULL){
                        printf("Aluno ja esta inscrito \n");
                    } else{
                        insere_lista_aluno(&inscritos, l_alunos->aluno);
                        insere_aluno_alex_exames(submeter, l_alunos->aluno, atual->exame);

                        if(numero_alunos % 30 == 0){
                            printf("SALA CHEIA. \n");
                            possivel_sala(ex_copia, atual->exame.data,atual->exame.hora, atual->exame.fim, atual->exame.salas);
                        }

                    }
                }
            }
        }
        else{
            if(l_exames->next == NULL){
                printf("Nao existem exames guardados\n");
            }
            if(l_alunos->next == NULL){
                printf("Nao existem alunos guardados\n");
            }
        }
}


/* imprime_alunos_inscritos_exame imprime os alunos inscritos num exame*/
void imprime_alunos_inscritos_exame(Lista_Exames lista){
    Lista_Alunos inscritos;
    Lista_Exames ant, atual;

    if(lista->next != NULL){

        printf("@@@ Lista de alunos inscritos por exame @@@ \n\n");

        escolhe_exame(lista, &ant, &atual);
        inscritos = atual->exame.alunos_inscritos;

        if(inscritos->next != NULL)
            imprime_lista_alunos(inscritos);
        else
            printf("Nao existem alunos inscritos. \n");
    }
    else{
        printf("Nao existem exames. \n");
    }
}



/* imprime_exames_inscritos_aluno imprime os exames inscritos por aluno
 *
 * pede ao utilizador para escolher o aluno(escolhe_aluno)
 * e procura na Lista_Aluno_Exames o aluno
 *
 * se não encontrar, imprime "O aluno nao esta
 * inscrito" em exames"
 *
 * se concontrar, imprime a Lista_Exames associada a esse aluno.
*/
void imprime_exames_inscritos_aluno(Lista_Aluno_Exames lista, Lista_Alunos l_alunos) {
    Lista_Aluno_Exames ant, atual;

    if(l_alunos->next != NULL){
        printf("@@@ Lista de exames inscritos por aluno @@@ \n\n");

        escolhe_aluno(&l_alunos);
        procura_lista_aluno_exames(lista, *l_alunos->aluno.numero_de_estudante, &ant, &atual);

        if(atual == NULL) {
            printf("O aluno nao esta inscrito.\n\n");
        } else {
            imprime_lista_exames(atual->data.inscrito);
        }
    } else {
        printf("Nao existem alunos inscritos\n");
    }
}


