#include "estrutura.h"

/* cria_lista_disciplinas devolve uma nova Lista_Disciplinas */
Lista_Disciplinas cria_lista_disciplinas()
{
    Lista_Disciplinas info;

    info = (Lista_Disciplinas)malloc(sizeof(Node_Lista_Disciplinas));
    if(info != NULL)
        info->next = NULL;
    else
        printf("Ocorreu erro na alocacao de memoria!");
    return info;
}

/* procura_lista_disciplinas procura uma disciplina chave na Lista_Disciplinas
 * Se encontrar, o atual vai para a posição da disciplina procurada (chave)
 * Se não encontrar, o atual passa a NULL
 */
void procura_lista_disciplinas(Lista_Disciplinas lista, Disciplina chave, Lista_Disciplinas *ant, Lista_Disciplinas *atual)
{
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && strcmp((*atual)->disciplina.nome,chave.nome) != 0)
        {
            *ant = *atual;
            *atual = (*atual)->next;
        }
        if((*atual) != NULL && strcmp((*atual)->disciplina.nome,chave.nome) != 0)
            *atual = NULL;
}

/* remove_da_lista_disciplina_aux remove disciplina chave da Lista_Disciplinas */
void remove_da_lista_disciplina_aux(Lista_Disciplinas lista, Disciplina chave)
{
    Lista_Disciplinas ant, atual;

    procura_lista_disciplinas(lista, chave, &ant, &atual);
    if(atual != NULL){
        ant->next = atual->next;
        free(atual);
    }
}

/* imprime_lista_disciplinas imprime a lista da Lista_Disciplinas */
void imprime_lista_disciplinas(Lista_Disciplinas lista)
{
    Lista_Disciplinas disc = lista->next;

    printf("@@@ LISTA ATUAL DE DISCIPLINAS @@@ \n\n");
    while (disc){
        printf("Nome da disciplina: %s\n", disc->disciplina.nome);
        printf("Regente da cadeira: %s\n", disc->disciplina.regente);
        printf("-------------------------------------------------\n\n");
        disc = disc->next;
    }
}


/* cria_disciplina cria uma nova disciplina e insere-a na Lista_Disciplinas
 *
 * Pede ao utilizador o nome da nova disciplina
 *
 * Verifica se a disciplina com esse nome já existe
 *      Se já existe, imprime "Ja existe disciplina chamada: %s"
 *      e continua
 *
 *      else pede o nome do regente da cadeira
 *      e insere na lista a nova disciplina
*/
void cria_disciplina(Lista_Disciplinas lista){
    Disciplina nova;
    Lista_Disciplinas atual, useless;

    printf("@@@ Esta a criar uma nova disciplina @@@\n\n");

    printf("Nome: \n");
    nova.nome = (char*)malloc(MAX * sizeof(char));
    fflush(stdin);
    fgets(nova.nome, MAX, stdin);

    procura_lista_disciplinas(lista, nova, &useless, &atual);
    if(atual != NULL){
        printf("Ja existe disciplina com esse nome");
    }else {
        printf("Nome do regente: \n");
        nova.regente = (char *)malloc(MAX * sizeof(char));
        fflush(stdin);
        fgets(nova.regente, MAX, stdin);

        insere_lista_disciplina(lista, nova);
    }

}

/* escolhe_disciplina pergunta ao utilizador qual disciplina na Lista_Disciplinas pertendem escolher
 *
 * imprime a lista para utilizador escolher
 * o utilizador escreve o nome da disciplina e essa é guardada na variável nome_disciplina
 *
 * percorre pela cópia da lista(que é a copia da Lista_Disciplinas ) até encontrar o mesmo nome da disciplina
 *
 * se não encontrar, é imprimido "Essa disciplina nao existe."
 * E pede outro nome
 *
 * quando econcontra o mesmo nome da disciplina, vai até a posição da disciplina na lista
 * devolvendo a disciplina nessa posição
*/
void escolhe_disciplina(Lista_Disciplinas *lista)
{
    char *nome_disciplina = (char *)malloc(MAX * sizeof(char));
    Lista_Disciplinas copia;
    int n, i;

    do{
        copia = *lista;
        n = 0;
        printf("Qual desciplina? \n");
        imprime_lista_disciplinas(copia);
        fflush(stdin);
        fgets(nome_disciplina, MAX, stdin);

        while((strcmp(copia->disciplina.nome, nome_disciplina) != 0) && (copia->next != NULL))
        {
            copia = copia -> next;
            n++;
        }
        if(strcmp(copia->disciplina.nome, nome_disciplina) != 0)
            printf("Essa disciplina nao existe. \n");
    }while(strcmp(copia->disciplina.nome, nome_disciplina) != 0);

    for(i = 0; i < n; i++){
        *lista = (*lista)->next;
    }
    free(nome_disciplina);
}

/* altera_info_disciplina altera a informação de uma certa disciplina
 *
 * imprime o nome atual da disciplina
 * pergunta ao utilizador se este pretende mudar o nome da disciplina
 *
 * imprime o nome atual do regente atual da disciplina
 * pergunta ao utilizador se este pretende mudar o nome do regente da disciplina
 *
 * se o utilizador quiser mudar, simplismente pressiona 's' e serão pedidos novos dados
*/
void altera_info_disciplina(Disciplina *disc){

    printf("Nome da disciplina atual: %s", disc->nome);
    confirma_resposta("Novo nome: \n", 0,disc->nome);

    printf("Nome do regente atual: %s", disc->regente);
    confirma_resposta("Novo nome: \n", 0 ,disc->regente);
}

/* altera_disciplina altera os dados da disciplina na Lista_Disciplinas
 *
 * verifica se existem desciplinas na lista
 * pergunta ao utilizador qual disciplina querem mudar
 * e muda os dados da disciplina
*/
void altera_disciplina(Lista_Disciplinas *lista){
    if((*lista)->next != NULL) {
            printf("@@@ Esta a alterar os dados de uma disciplina @@@\n\n");
            escolhe_disciplina(lista);
            altera_info_disciplina(&(*lista)->disciplina);
        } else {
            printf("Nao existem disciplinas guardadas\n");
        }
}

/* remove_da_lista_disciplina simplesmente remove da Lista_Disciplinas a disciplina que o utilizador quer
 *
 * verifica se existem disciplinas na lista
 *
 * pergunta ao utilizador qual disciplina querem remover
 * e remove da Lista_Disciplinas
*/
void remove_da_lista_disciplina(Lista_Disciplinas lista){
    Lista_Disciplinas copia = lista;

    if(lista->next != NULL){
        printf("@@@ A REMOVER UMA DISCIPLINA  @@@\n\n");
        escolhe_disciplina(&lista);

        remove_da_lista_disciplina_aux(copia, lista->disciplina);
        printf("A disciplina foi removida. \n\n");
    }else{
        printf("Nao existem disciplinas guardadas\n");
    }
}

/*insere_lista_disciplina insere uma disciplina nova na Lista_Disciplinas*/
void insere_lista_disciplina(Lista_Disciplinas lista, Disciplina nova)
{
    Lista_Disciplinas node;

    node = (Lista_Disciplinas)malloc(sizeof(Node_Lista_Disciplinas));
    node->disciplina = nova;

    while(lista->next != NULL){
        lista = lista->next;
    }
    lista->next = node;
    lista = node;
    lista->next = NULL;
}

void escreve_disciplinas(Lista_Disciplinas lista)
{
    FILE *fp;
    Lista_Disciplinas disc;
    disc = lista->next;
    fp = fopen("disciplinas.txt", "w");
    if (fp == NULL)
        printf("Ficheiro inexistente");
    while(disc != NULL)
        {
            fprintf(fp, "%s\n", disc->disciplina.nome);
            fprintf(fp, "%s\n", disc->disciplina.regente);
            disc = disc->next;
        }
    fclose(fp);
}

/*void le_disciplinas(Lista_Disciplinas lista)
{
    FILE *fp;
    char linha[MAX];
    fp = fopen("disciplinas.txt", "r");
    if (fp == NULL)
        printf("Ficheiro inexistente\n");
    while(fgets(linha,MAX,fp)!=NULL)
    {
        Lista_Disciplinas aux = malloc(sizeof(Node_Lista_Disciplinas));
        aux->next = lista->next;
        lista->next = aux;

        linha[strlen(linha)-1] = '\0';
        strcpy(aux->disciplina.nome, linha);

        fgets(linha, MAX, fp);
        linha[strlen(linha)-1] = '\0';
        strcpy(aux->disciplina.regente, linha);
    }
    fclose(fp);
}
*/
