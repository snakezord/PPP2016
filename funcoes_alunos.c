#include "estrutura.h"

/* cria_lista_alunos devolve uma nova Lista_Alunos */
Lista_Alunos cria_lista_alunos()
{
    Lista_Alunos info;

    info = (Lista_Alunos)malloc(sizeof(Node_Lista_Alunos));
    if(info != NULL)
        info->next = NULL;
    else
        printf("Ocorreu erro na alocacao de memoria!");
    return info;
}

/* procura_lista_alunos procura um aluno pelo numero_estudante na Lista_Alunos
 * Se encontrar, o atual vai para a posição do aluno procurado (numero_estudante)
 * Se não encontrar, o atual passa a NULL
 */
void procura_lista_alunos(Lista_Alunos lista, int numero_estudante, Lista_Alunos *ant, Lista_Alunos *atual)
{
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && *(*atual)->aluno.numero_de_estudante < numero_estudante)
    {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if((*atual) != NULL && *(*atual)->aluno.numero_de_estudante != numero_estudante){
        *atual = NULL;
    }
}

/* remove_da_lista_alunos remove um aluno da Lista_Alunos */
void remove_da_lista_alunos(Lista_Alunos lista, int numero_estudante){
    Lista_Alunos ant, atual;

    procura_lista_alunos(lista, numero_estudante, &ant, &atual);
    if(atual != NULL){
        ant->next = atual->next;
        free(atual);
    }
}

/* insere_lista_aluno insere um novo aluno na Lista_Alunos */
void insere_lista_aluno(Lista_Alunos *lista, Aluno novo){
    Lista_Alunos node, ant, useless;

    node = (Lista_Alunos)malloc(sizeof(Node_Lista_Alunos));
    if(node != NULL){
        node->aluno = novo;
        procura_lista_alunos(*lista, *novo.numero_de_estudante, &ant, &useless);
        node->next = ant->next;
        ant->next = node;
    }
}

/* imprime_lista_alunos imprime a lista da Lista_Alunos */
void imprime_lista_alunos(Lista_Alunos lista)
{
    Lista_Alunos alun;
    alun = lista->next;
    printf("@@@ LISTA ACTUAL DE ALUNOS @@@\n\n");
    while (alun){
        printf("Nome: %s\n",alun->aluno.nome);
        printf("No de estudante: %d\n",*alun->aluno.numero_de_estudante);
        printf("Ano de matricula: %d\n",*alun->aluno.ano_de_matricula);
        printf("Curso: %s\n",alun->aluno.curso);
        printf("Regime: %s\n",alun->aluno.regime);
        printf("-------------------------------------------------\n\n");
        alun = alun->next;
    }
}

/* regime pergunta ao utilizador qual o regime que quer escolher e guarda-o em str*/
void regime(char str[]){
    char *temp =(char*)malloc(MAX* sizeof(char));

    while(temp[0] != '1' && temp[0] != '2' &&  temp[0] != '3' && temp[0] != '4' && temp[0] != '5'){
        printf("\t1.Normal\n\t2.Trabalhador-estudante\n\t3.Atleta\n\t4.Dirigente associativo\n\t5.Aluno de Erasmus\n");
        fflush(stdin);
        fgets(temp, MAX, stdin);

        switch(temp[0]) {
            case '1':
                strcpy(str, "Normal\n");
                break;
            case '2':
                strcpy(str, "Trabalhador-estudante\n");
                break;
            case '3':
                strcpy(str, "Atleta\n");
                break;
            case '4':
                strcpy(str, "Dirigente associativo\n");
                break;
            case '5':
                strcpy(str, "Aluno de Erasmus\n");
                break;
            default:
                printf("Escolha errada \n");
        }
    }
    free(temp);
}

/* elimina_aluno_da_lista simplesmente remove da Lista_Alunos o aluno que o utilizador quer
 *
 * verifica se existem alunos na Lista_Alunos
 *
 * pergunta ao utilizador qual aluno quere
 * e depois remove-o da Lista_Alunos
*/
void elimina_aluno_da_lista(Lista_Alunos lista)
{
    Lista_Alunos copia = lista;

    if(lista->next != NULL){
        printf("@@@ A REMOVER UM ALUNO  @@@\n\n");
        escolhe_aluno(&lista);

        remove_da_lista_alunos(copia, *lista->aluno.numero_de_estudante);
        printf("Aluno foi removido\n\n");
    } else{
        printf("Nao existem alunos guardados");
    }
}

/* aluno_existe confirma a existencia de um aluno
 * na Lista_Alunos ao procurar o numero_estudante
 *
 * se o numero_estudante for encontrado é impresso
 * "Ja existe um estudante com esse numero "
 * e return 1
 * else return 0
*/
int aluno_existe(Lista_Alunos lista, int numero_estudante){
Lista_Alunos atual, useless;

    procura_lista_alunos(lista, numero_estudante, &useless, &atual);
    if(atual != NULL){
        printf("Ja existe um estudante com esse numero\n");
        return 1;
    }
    return 0;
}

/* cria_aluno cria um novo aluno e insere-o na Lista_Alunos
 *
 * pede ao utilizador o numero_estudante e verifica se este ja existe
 * depois pede o nome, curso, ano da matricula e regime
 *
 * finalmente insere na Lista_Alunos
*/
void cria_aluno(Lista_Alunos lista)
{
    int len, i;
    Aluno novo;
    char nome[MAX];
    char curso[MAX];
    char regim[MAX];
    printf("@@@ Esta a criar um novo aluno @@@\n\n");

    printf("Numero de estudante: (Apenas numeros com 10 digitos)\n");
    novo.numero_de_estudante = (int*)malloc(sizeof(int));
    recebe_str(novo.numero_de_estudante);

    if(aluno_existe(lista, *novo.numero_de_estudante) == 0){
        do{
            i = 0;
            len = strlen(novo.nome) - 1;
            printf("Nome: (Apenas letras)\n");
            novo.nome = (char *)malloc(MAX * sizeof(char));
            fflush(stdin);
            fgets(nome, MAX,stdin);
            nome[strlen(nome)-1] = '\0';
            strcpy(novo.nome,nome);
            i++;
        }while((i < len) && isdigit(novo.nome[i]));

        do{
            i = 0;
            len = strlen(novo.curso) - 1;
            printf("Curso: (Apenas letras)\n");
            novo.curso = (char *)malloc(MAX* sizeof(char));
            fflush(stdin);
            fgets(curso, MAX, stdin);
            curso[strlen(curso)-1] = '\0';
            strcpy(novo.curso,curso);
            i++;
        }while((i < len) && isdigit(novo.curso[i]));

        do{
            printf("Ano: (1,2,3)\n");
            novo.ano_de_matricula = (int *)malloc(sizeof(int));
            recebe_str(novo.ano_de_matricula);
        }while(*novo.ano_de_matricula < 1 || *novo.ano_de_matricula > 3);
        printf("Regime: \n");

        novo.regime = (char *)malloc(MAX * sizeof(char));
        regim[strlen(regim)-1] = '\0';
        strcpy(novo.regime,regim);
        regime(novo.regime);
        insere_lista_aluno(&lista, novo);

    }
}

/* escolhe_aluno pede ao utilizador qual aluno da Lista_Alunos quer escolher
 *
 * imprime a lista atual de alunos para escolher
 * o utilizador escreve o numero de estudante e esse é guardado no numero_estudante
 *
 * a copia da lista(que é a copia da Lista_Alunos) é percorrida até encontrar o mesmo numero_estudante
 *
 * se não for encontrado, imprime "Estudante nao existe"
 * e pede outro numero
 *
 * quando encontra o mesmo numero de estudante, vai a posição desse aluno na lista
 * devolvendo o aluno nessa posição
*/
void escolhe_aluno(Lista_Alunos *lista){

    int numero_estudante, i, n;
    Lista_Alunos copia;

    do{
        copia = *lista;
        n = 0;
        printf("Qual aluno?(numero de aluno)\n");
        imprime_lista_alunos(copia);
        recebe_str(&numero_estudante);

        while((*copia->aluno.numero_de_estudante != numero_estudante) && (copia->next != NULL)){
            copia = copia->next;
            n++;
        }
        if(*copia->aluno.numero_de_estudante != numero_estudante)
            printf("Estudante nao existe\n");
    }while(*copia->aluno.numero_de_estudante != numero_estudante);

    for(i = 0; i < n; i++) {
        *lista = (*lista)->next;
    }
}


/* altera_aluno altera informação de aluno na Lista_Alunos
 *
 * verifica se existem alunos na lista
 * pede ao utilizador que aluno quer mudar
 *
 * pede se quer mudar o numero de estudante
 *      se o novo numero para o qual se quer mudar já existe, então pede-se
 *      outro numero de estudante
 * e se quere mudar o nome, curso, ano da matricula e regime
 *
 * se o utilizador quer mudar, simplesmente pressiona 's' e será pedida nova informação
*/
void altera_aluno(Lista_Alunos lista)
{
    int num, res = -1;
    Lista_Alunos copia = lista;


    if(lista->next != NULL){
        printf("\n\n@@@ Esta a  alterar dados de um aluno @@@\n\n");
        escolhe_aluno(&lista);

        num = *lista->aluno.numero_de_estudante;

        do{
            printf("\nNumero de aluno atual: %d\n", *lista->aluno.numero_de_estudante);
            confirma_resposta("Novo numero de aluno: \n", &num, "0");
        } while(num != *lista->aluno.numero_de_estudante && aluno_existe(copia, num) == 1);
        *lista->aluno.numero_de_estudante = num;

        printf("Nome atual: %s\n", lista->aluno.nome);
        confirma_resposta("Novo nome: \n", 0, lista->aluno.nome);

        printf("Curso atual: %s\n", lista->aluno.curso);
        confirma_resposta("Novo curso: \n", 0, lista->aluno.curso);


        num = *lista->aluno.ano_de_matricula;
        do {
            printf("Ano atual:  %d\n", *lista->aluno.ano_de_matricula);
            confirma_resposta("Novo ano: \n", &num, "0");
            if(num < 1 || num > 3)
                printf("Ano invalido. \n");
        } while(num < 1 || num > 3);
        *lista->aluno.ano_de_matricula = num;


        printf("Regime atual: %s\n", lista->aluno.regime);
        confirma_resposta("Novo regime: \n", &res, lista->aluno.regime);
    } else {
        printf("Nao existem alunos guardados");

    }
}


/* tamanho_da_lista_alunos devolve o tamanho da Lista_Alunos */
int tamanho_da_lista_alunos(Lista_Alunos lista){
    int tam = 0;
    while(lista->next != NULL){
        lista = lista->next;
        tam++;
    }
    return tam;
}




void escreve_alunos(Lista_Alunos lista)
{
    FILE *fp;
    Lista_Alunos alun;
    alun = lista->next;
    fp = fopen("alunos.txt", "w");
    if (fp == NULL)
        printf("Ficheiro inexistente");
    while(alun != NULL)
        {
            fprintf(fp, "%d\n", *alun->aluno.numero_de_estudante);
            fprintf(fp, "%s\n", alun->aluno.nome);
            fprintf(fp, "%s\n", alun->aluno.curso);
            fprintf(fp, "%d\n", *alun->aluno.ano_de_matricula);
            fprintf(fp, "%s\n", alun->aluno.regime);
            alun = alun->next;
        }
    fclose(fp);
}


/*
void le_aluno(Lista_Alunos lista)
{
    FILE *fp;
    char linha[MAX];
    fp = fopen("alunos.txt", "r");
    if (fp == NULL)
        printf("Ficheiro inexistente\n");
    while(fgets(linha,MAX,fp)!=NULL)
    {
            Lista_Alunos aux = malloc(sizeof(Node_Lista_Alunos));
            aux->next = lista->next;
            lista->next = aux;

            *aux->aluno.numero_de_estudante = atoi(linha);

            fgets(linha, MAX, fp);
            linha[strlen(linha)-1] = '\0';
            strcpy(aux->aluno.nome, linha);

            fgets(linha, MAX, fp);
            *aux->aluno.ano_de_matricula = atoi(linha);

            fgets(linha, MAX, fp);
            linha[strlen(linha)-1] = '\0';
            strcpy(aux->aluno.curso, linha);

            fgets(linha, MAX, fp);
            linha[strlen(linha)-1] = '\0';
            strcpy(aux->aluno.regime, linha);
        }
    fclose(fp);
}
*/
