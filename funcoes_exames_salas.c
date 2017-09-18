#include "estrutura.h"

/* cria_lista_exames devolve uma nova Lista_Exames */
Lista_Exames cria_lista_exames()
{
    Lista_Exames info;

    info = (Lista_Exames)malloc(sizeof(Node_Lista_Exames));
    if(info != NULL)
        info->next = NULL;
    else
        printf("Ocorreu erro na alocacao de memoria!");
    return info;
}

/* cria_lista_salas devolve uma nova Lista_Salas */

Lista_Salas cria_lista_salas(){
    Lista_Salas info;

    info = (Lista_Salas)malloc(sizeof (Node_Lista_Salas));
    if(info != NULL)
        info->next = NULL;
     else
        printf("Ocorreu erro na alocacao de memoria!");
    return info;
}


/* imprime_lista_salas imprime a lista da Lista_Salas */
void imprime_lista_salas(Lista_Salas lista){
    Lista_Salas s = lista->next;

    while(s){
        printf("Sala: %s \n", s->sala.nome);
        s = s->next;
    }
}

/* imprime_lista_exames imprime a lista da Lista_Exames */
void imprime_lista_exames(Lista_Exames lista)
{
    Lista_Exames exam = lista->next;

    printf("\n@@@ Lista de exames @@@\n");
    while (exam){
        printf("Nome: %s\n", exam->exame.nome);
        printf("%s\n", exam->exame.epoca);
        printf("Disciplina: %s\n", exam->exame.disciplina->nome);
        printf("Regente : %s\n", exam->exame.disciplina->regente);
        printf("Data: %d / %d / %d\n", exam->exame.data.dia, exam->exame.data.mes, exam->exame.data.ano);
        printf("Hora: %d : %d\n", exam->exame.hora.hora, exam->exame.hora.minutos);
        printf("Fim: %d : %d\n", exam->exame.fim.hora, exam->exame.fim.minutos);
        imprime_lista_salas(exam->exame.salas);
        printf("\n-------------------------------------------------\n");
        exam = exam->next;
    }
}

/* procura_sala tenta econtrar uma sala na Lista_Exames
 *
 * verifica em todos os exames na Lista_Exames a Lista_Salas associada ao exame
 * se encontrar a sala
 *      returns 1
 * Se não
 *      returns 0
*/
int procura_sala(Lista_Exames lista, Sala sala){
    Lista_Salas copia;
    int num = 0;

    while(lista->next != NULL){
        lista = lista->next;
        copia = lista->exame.salas;
        while(copia->next != NULL){
            copia = copia->next;
            if(copia->sala.nome == sala.nome)
                num = 1;
        }
    }
    return num;
}


/* procura_lista_exames procura um exame por nome e epoca na Lista_Exames
 * Se encontrar, o atual vai para a posição do exame procurado
 * Se não encontrar, o atual passa a NULL
 */
void procura_lista_exames(Lista_Exames lista, char *nome, char *epoca, Lista_Exames *ant, Lista_Exames *atual)
{
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && (strcmp((*atual)->exame.nome, nome)&& strcmp((*atual)->exame.epoca, epoca)) != 0)
        {
            *ant = *atual;
            *atual = (*atual)->next;
        }
        if((*atual) != NULL && (strcmp((*atual)->exame.nome, nome)&& strcmp((*atual)->exame.epoca, epoca)) != 0)
            *atual = NULL;
}

/* remove_da_lista_exame_aux remove exame da Lista_Exames */
void remove_da_lista_exame_aux(Lista_Exames lista, char *nome, char *epoca)
{
    Lista_Exames ant, atual;

    procura_lista_exames(lista, nome, epoca, &ant, &atual);
    if(atual != NULL){
        ant->next = atual ->next;
        free(atual);
    }
}

/*insere_lista_exame insere um exame novo na Lista_Exames*/
void insere_lista_exame(Lista_Exames *lista, Exame novo){
    Lista_Exames node, ant, useless;

    node = (Lista_Exames)malloc(sizeof(Node_Lista_Exames));
    if(node != NULL){
        node->exame = novo;
        procura_lista_exames(*lista, novo.nome, novo.epoca, &ant, &useless);
        node->next = ant->next;
        ant->next = node;
    }
}

/*insere_lista_sala insere uma sala nova na Lista_Salas*/
void insere_lista_sala(Lista_Salas lista, Sala nova){
    Lista_Salas node;

    node = (Lista_Salas)malloc(sizeof(Node_Lista_Salas));
    node->sala = nova;

    while(lista->next != NULL){
        lista = lista->next;
    }
    lista->next = node;
    lista = node;
    lista->next = NULL;
}

/* epoca_exame faz o utilizados escolher a epoca do exame entre as possíveis */
void epoca_exame(char str[]){
    char *temp = (char*)malloc(MAX * sizeof(char));

    while(temp[0] != '1' && temp[0] != '2' && temp[0] != '3'){
        printf("\t1.Epoca Normal\n\t2.Epoca de Recurso\n\t3.Epoca Especial\n");
        fgets(temp, MAX, stdin);

        switch(temp[0]){
            case '1':
                strcpy(str, "Epoca Normal");
                break;
            case '2':
                strcpy(str, "Epoca de Recurso");
                break;
            case '3':
                strcpy(str, "Epoca Especial");
                break;
            default:
                printf("Escolha errada. \n\n");
        }
    }
    free(temp);
}


/* escolhe_sala cria uma nova sala que não esta ocupada por outro exame
 *
 * pergunta ao utilizador que sala querem
 * verifica se está ocupada(procura_sala)
 * se esta está, pede outra sala
*/
void escolhe_sala(Lista_Exames lista, Sala nova){
    char *temp = (char*)malloc(MAX * sizeof(char));

    do{
        printf("Sala: \n");
        fflush(stdin);
        fgets(temp, MAX, stdin);
        strncpy((nova).nome, temp, 1);

        if(procura_sala(lista, nova) == 1)
            printf("Sala %s esta ocupada. \n", temp);
    }while(procura_sala(lista, nova) == 1);
    free(temp);
}

/* aux_data_possivel_sala compara as datas dos exames na lista á data
 * e insere na lista *node os exames com mesma data
 *
 * passa por todos os exames na lista e se estes tem mesma data
 * insere-os na lista *node
*/
void aux_data_possivel_sala(Lista_Exames lista, Lista_Exames *node, Data data){
    while(lista->next != NULL){
        lista = lista->next;

        if(compara_datas(lista->exame.data, data) == 0)
            insere_lista_exame(node, lista->exame);
    }
}

/* aux_hora_possivel_sala é a funcao auxiliar da funcao 'possivel_sala' compara as
 * horas dos exames na lista ao inicio(hora) do exame e o fim.
 * e insere na lista *node os exames que estão a mesma hora(mesma_hora)
 *
 * passa por todos os exames na lista e se mesma_hor for verdade
 * insere-os na lista *node
*/
void aux_hora_possivel_sala(Lista_Exames lista, Lista_Exames *node, Hora hora, Hora fim){
    Hora inicio_ex, fim_ex;
    int mesma_hor;

    while(lista->next != NULL){
        lista = lista->next;
        inicio_ex = lista->exame.hora;
        fim_ex = lista->exame.fim;
        mesma_hor = mesma_hora(inicio_ex, fim_ex, hora, fim);

        if(mesma_hor){
            insere_lista_exame(node, lista->exame);
        }
    }
}

/* possivel_sala verifica quais salas estão ocupadas numa certa data e hora
 * e guarda-as em salas_node
 *
 * primeiro verifica quais exames têm a mesma data e guarda-os em exames_node
 *
 * depois ve em exames_node quais exames estão a mesma hora e guarda-os em salas_node
 * imprime salas_node
 * pede ao utilizador para escolher sala(escolhe_sala)
 *
 * e insere essa sala que está disponível na Lista_Salas sala
*/
void possivel_sala(Lista_Exames lista, Data data, Hora hora, Hora fim, Lista_Salas sala_exame){
    Lista_Exames exames_node = cria_lista_exames();
    Lista_Exames salas_node = cria_lista_exames();
    Lista_Exames copia;
    Sala nova;

    aux_data_possivel_sala(lista, &exames_node, data);

    if(exames_node->next != NULL){
            aux_hora_possivel_sala(exames_node, &salas_node, hora, fim);
            copia = salas_node;

        if(salas_node ->next != NULL)
            printf("@@@ Salas estao ocupadas @@@\n");

        while(salas_node->next != NULL) {
            salas_node = salas_node->next;
            imprime_lista_salas(salas_node->exame.salas);
            printf("-------------------------------------------------\n");
        }

        escolhe_sala(copia, nova);
    } else
        escolhe_sala(salas_node, nova);

    insere_lista_sala(sala_exame, nova);
}

/* hora_exame pede ao utilizador possível hora
 *
 * guarda possíveis horas em hora_disponivel
 * imprime 'n' horas hora_disponivel com um índice associado a cada hora
 * e pede ao utilizador a hora desejada por índice
 *
 * e guarda a Hora *hora escolhida
*/
void hora_exame(Hora *hora, int n, int h, int min) {
    Hora hora_disponivel[n];

    int i;

    do {
        horas_possiveis(hora_disponivel, n, h, min);

        printf("Horas disponiveis:\n\n");
        for (i = 0; i < n; i++) {
            printf("\t%d.\t%d : %d\n", i + 1, hora_disponivel[i].hora, hora_disponivel[i].minutos);
        }

        recebe_str(&i);
    } while(i > n || i <  1);

    (*hora).hora = hora_disponivel[i-1].hora;
    (*hora).minutos = hora_disponivel[i-1].minutos;
}

/* cria_exame cria um novo exame para inserir na Lista_Exames lista
 *
 * primeiro pede-se uma disciplina da Lista_Disciplinas para associar esse novo exame
 * á disciplina (novo.disciplina)
 *
 * depois pede o nome do exame(que pode ser diferente do nome da disciplina associada a esse exame)
 * que é caracteristico para reconhecer o exame (novo.nome)
 *
 * pede o nome da época do exame(novo.epoca)
 *
 * pede a data em que o exame vai ocorrer(novo.data)
 *
 * pede a hora em que o exame começa (novo.hora) e a duração(novo.duracao)
 *
 * calcula quando o exame termina(novo.fim)
 *
 * cria uma nova Lista_Alunos para os alunos a inscrever para este novo exame
 * (novo.alunos_inscritos)
 *
 * cria uma nova Lista_Salas para as salas em que o exame vai ocorrer
 * e pede ao utilizador para afixar a 1ª sala
 *
 * insere o novo exame na Lista_Exames lista
*/
void cria_exame(Lista_Exames lista, Lista_Disciplinas disciplinas){
    Exame novo;
    Lista_Exames copia = lista;


    if(disciplinas->next != NULL){
        printf("@@@ A criar um novo exame @@@\n\n");
        escolhe_disciplina(&disciplinas);
        novo.disciplina = &disciplinas->disciplina;


        printf("Nome do exame: \n");
        novo.nome = (char*)malloc(MAX * sizeof(char));
        fflush(stdin);
        fgets(novo.nome, MAX, stdin);


        printf("Epoca: \n");
        novo.epoca = (char*)malloc(MAX * sizeof(char));
        fflush(stdin);
        epoca_exame(novo.epoca);

        printf("Em que dia/mes/ano se realiza o exame?\n");
        do {
            printf("Ano: \n");
            recebe_str(&novo.data.ano);
        } while(novo.data.ano < ANO);

        do {
            printf("Mes: \n");
            fflush(stdin);
            recebe_str(&novo.data.mes);
        } while(novo.data.mes < 1 || novo.data.mes > 12);

        do {
            printf("Dia: \n");
            fflush(stdin);
            recebe_str(&novo.data.dia);
        } while(novo.data.dia < 1 || novo.data.dia > max_dia_mes(novo.data.ano, novo.data.mes));

        printf("\nA que horas?\n\n");
        hora_exame(&novo.hora, 16, 9, 0);

        printf("\nDuracao?\n\n");
        hora_exame(&novo.duracao, 6, 0 ,30);


        novo.fim.hora = novo.hora.hora + novo.duracao.hora;
        novo.fim.minutos = novo.hora.minutos + novo.duracao.minutos;

        if(novo.fim.minutos == 60){
            novo.fim.minutos = 0;
            novo.fim.hora += 1;
        }

        novo.alunos_inscritos = cria_lista_alunos();

        novo.salas = cria_lista_salas();
        possivel_sala(copia, novo.data, novo.hora, novo.fim, novo.salas);

        insere_lista_exame(&lista, novo);
        printf("\nExame Criado.\n");
    } else {
        printf("Nao existem disciplinas guardadas. \n");
    }
}


/* escolhe_exame pergunta ao utilizador qual exame querem escolher
 *
 * imprime a Lista_Exames lista (imprime_lista_exames)
 * e pede ao utilizador o nome e época associadas ao exame pretendido
 *
 * procura pelo exame (procura_lista_exames)
 * se não existir pergunta de novo
*/
void escolhe_exame(Lista_Exames lista, Lista_Exames *ant, Lista_Exames *atual){
    char *nome;
    char *epoca;
    nome = (char*)malloc(MAX * sizeof(char));
    epoca = (char*)malloc(MAX * sizeof(char));

    do{
        imprime_lista_exames(lista);
        printf("\nQual exame: (Nome e Epoca)\n");

        printf("Nome do exame: \n");
        fflush(stdin);
        fgets(nome, MAX, stdin);


        printf("Epoca: \n");
        fflush(stdin);
        epoca_exame(epoca);

        procura_lista_exames(lista, nome, epoca, ant, atual);
        if(*atual == NULL)
            printf("Nao existe exame com nome %s guardado.\n", nome);
    }while(*atual == NULL);

    free(nome);
    free(epoca);
}

/* remove_da_lista_exame remove exame da Lista_Exames
 *
 * pede ao utilizador para escolher o exame a remover(escolhe_exame)
 *
 * precorre cada nó em Lista_Aluno_Exames para remover esse exame em cada
 * Lista_Exames (remove_da_lista_exame_aux)
 *
 * depois remove o exame na Lista_Exames(remove_da_lista_exame_aux)
*/
void remove_da_lista_exame(Lista_Exames lista, Lista_Aluno_Exames lista2)
{
    Lista_Exames atual, ant;
    Lista_Exames inscrito;

    printf("@@@ A apagar um exame @@@\n\n");
    escolhe_exame(lista, &ant, &atual);


    while(lista2->next != NULL){
        lista2 = lista2 ->next;
        inscrito = lista2->data.inscrito;
        remove_da_lista_exame_aux(inscrito, atual->exame.nome, atual->exame.epoca);
    }
    remove_da_lista_exame_aux(lista, atual->exame.nome, atual->exame.epoca);
}

/* imprime_salas_exame imprime a Lista_Salas de um exame
 *
 * primeiro pede para escolher o exame (escolhe_exame)
 *
 * depois emprime a Lista_Salas desse exame
 */
void imprime_salas_exame(Lista_Exames head) {
    Lista_Exames atual, ant;

    if(head->next != NULL) {
        escolhe_exame(head, &ant, &atual);
        imprime_lista_salas(atual->exame.salas);
    } else
        printf("\n Nao existem exames guardados ");
}

void escreve_exames(Lista_Exames lista)
{
    FILE *fp;
    Lista_Exames exam;
    exam = lista->next;
    fp = fopen("exames.txt", "w");
    if (fp == NULL)
        printf("Ficheiro inexistente");
    while(exam != NULL)
        {
            fprintf(fp, "%s\n", exam->exame.disciplina);
            fprintf(fp, "%s\n", exam->exame.epoca);
            fprintf(fp, "%d\n%d\n%d\n", exam->exame.data.dia, exam->exame.data.mes, exam->exame.data.ano);
            fprintf(fp, "%d\n%d\n", exam->exame.hora.hora, exam->exame.hora.minutos);
            fprintf(fp, "%d\n%d\n", exam->exame.duracao.hora, exam->exame.duracao.minutos);
            /*fprintf(fp, "%s\n", exam->exame.salas.sala);*/
            exam = exam->next;
        }
    fclose(fp);
}

/*void le_exames(Lista_Exames lista)
{
    FILE *fp;
    char linha[MAX];
    fp = fopen("exames.txt", "r");
    if (fp == NULL)
        printf("Ficheiro inexistente\n");
    while(fgets(linha,MAX,fp)!=NULL)
    {
        Lista_Exames aux = malloc(sizeof(Node_Lista_Exames));

        aux->next = lista->next;
        lista->next = aux;

        linha[strlen(linha)-1] = '\0';
        strcpy(aux->exame.disciplina.nome, linha);

        fgets(linha, MAX, fp);
        linha[strlen(linha)-1] = '\0';
        strcpy(aux->exame.epoca, linha);

        fgets(linha, MAX, fp);
        aux->exame.data.dia = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.data.mes = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.data.ano = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.hora.hora = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.hora.minutos = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.duracao.horas = atoi(linha);

        fgets(linha, MAX, fp);
        aux->exame.duracao.minutos = atoi(linha);

        fgets(linha, MAX, fp);
        linha[strlen(linha)-1] = '\0';
        strcpy(aux->exame.salas.sala, linha);

    }
    fclose(fp);
}*/

