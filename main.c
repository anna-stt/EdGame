#include <stdio.h>        // printf e scanf 
#include <conio.h>        // getch
#include <string.h>       // strcmp
#include <stdlib.h>       // exit    
#include <locale.h>       // setlocale

#define FALSE   0         // constante falsa
#define TRUE   !FALSE     // constante verdadeira

typedef struct {          // registro 
    int codigo;       
    int damage;
    char *lore;

} INFORMACAO;

typedef struct arv {
       INFORMACAO info;   // dados do registro
       struct arv *esq;   // ponteiro para o filho esquerdo
       struct arv* subd;  // ponteiro para o nodo da direita
       struct arv* sube;  // ponteiro para o nodo da esquerda
} ARVORE; 


/***********************************************/ 
/* Definicao das Funcoes                       */
/***********************************************/
void entrada_dados   ( ARVORE* aux );         // leitura dos dados de entrada
void imprime_ARVORE  ( ARVORE* aux );         // visualiza arvore em tela, todos os registros
void cria_ARVORE     ( ARVORE** r );          // inicializa arvore com NULL
void insere          ( ARVORE** r );          // inclui um novo registro na arvore, sempre na folha
int  busca           ( int matricula, ARVORE** a, ARVORE** p ); // procura na arvore um codigo
void sucessor        ( ARVORE* p, ARVORE** q, ARVORE** b );     // procura registro posterior de um codigo
void antecessor      ( ARVORE* p, ARVORE** q, ARVORE** b );     // procura registro anterior de um codigo
void remove_cod          ( ARVORE** r );          // exclui um regitro por codigo
void insere_recursivo( ARVORE** r, int cod ); // inclui um novo registro na arvore
void busca_recursivo ( ARVORE *p, int cod );  // procura na arvore um codigo
ARVORE* remove_recursivo( ARVORE **p, int cod ); // exclui um regitro por codigo
// Funcoes para salvar e carregar 
void salva_arvore    ( ARVORE *r );           // salva a lista para um txt
void salva_codigo( ARVORE *r, FILE *arquivo); // salva um codigo no txt
void carrega_arvore  ( ARVORE **r );          // le uma lista de um txt
void carrega_codigo( ARVORE **r, ARVORE *no); // carrega um codigo do txt


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/
int main( void ){

    char op;                                  // opcao do menu                               
    ARVORE* r, *p;                            // declaracao da ARVORE, vari�vel do tipo ARVORE = ARVORE de ponteiros
    int cod;  // variaveis de balanceamento

    setlocale(LC_ALL, "Portuguese");
    //cria_ARVORE( &r );
    while( 1 ){
         printf( "\n /---------------------------------------------------/" ); 
         printf( "\n Programa de registros - Menu                         " );
         printf( "\n [1] Cria ARVORE                                      " );
         printf( "\n [2] Insere                                           " );
         printf( "\n [3] Remove                                           " );
         printf( "\n [4] Imprime                                          " );         
         printf( "\n [5] Insere recursivo                                 " );
         printf( "\n [6] Busca recursivo                                  " );         
         printf( "\n [7] Remove recursivo                                 " );          
         printf( "\n [8] Salva lista                                     " );
         printf( "\n [9] Carrega lista                                   " );
         printf( "\n [0] Para sair do programa                            " );         
         printf( "\n /---------------------------------------------------/" );      
         printf( "\n Opcao: " );
         op = getche(); // tecla de opcao do menu

        switch( op ) {
           case '1':   // rotina cria ARVORE       
                   cria_ARVORE( &r );
                   break;

           case '2':   // rotina inclui nodo no final da ARVORE (folha)
                   insere( &r );    
                   break;

           case '3':   // rotina exclui nodo da ARVORE
                   remove_cod( &r );
                   break;

           case '4':   // rotina imprime nodos da ARVORE
                   imprime_ARVORE( r );
                   break;                   

           case '5':  // rotina recursiva do inclui nodo da ARVORE
                   printf("\n Digite o novo codigo: ");
                   scanf("%d", &cod);
                   insere_recursivo( &r, cod );
                  // calcula_altura( &r );         // calcula e armazena a altura de cada no
                  // verifica_balanceamento( &r ); // verifica balanceamento da ARVORE
                   break; 

           case '6':  // rotina recursiva que busca um registro da ARVORE                                                
                   printf("\n Buscar o codigo: ");
                   scanf("%d", &cod);
                   busca_recursivo( r, cod );                   
                   break;

           case '7':  // rotina recursiva que busca um registro da ARVORE                                                
                   printf("\n Remove codigo: ");
                   scanf("%d", &cod);
                   remove_recursivo( &r, cod );                  
                  // calcula_altura( &r ); 
                   break;

            case '8': // rotina salva a ARVORE em um arquivo txt              
                    salva_arvore( r );     
                    break;

            case '9': // rotina carrega uma ARVORE existente de um txt              
                    carrega_arvore( &r );
                    break;

           case '0':  // termino do programa                                                 
                   exit( 1 ); 
                   break;                

           default : 
                   printf( "\n Digite uma opcao!" );
                   break;
        } // switch( op )

        printf( "\n" );
        system("pause");
        system("cls");
     } // fim do while( 1 )

 return 0;
} // fim do programa principal

void introducao(){
    printf("\n");
    printf("\tPressione para começar!\n");
    getchar();
    system("cls");

    printf("\n");
    printf("\tO ano é 616 pós-queda. O Reino de Vok, é dilacerado por uma guerra civil\n");
    printf("\tque parece não ter fim. Soldados marcham sem destino, velhas alianças\n");
    printf("\tdesmoronam, e histórias de ouro, glória e traições ecoam como sussurros\n");
    printf("\tentre ruínas. Heróis surgem apenas para desaparecer, tornando-se poeira na\n");
    printf("\tvastidão do esquecimento.\n");
    printf("\n");
    printf("\t[...]\n");
    getchar();

    printf("\tMas você? Você não é um herói. É apenas mais um sortudo — ou talvez\n");
    printf("\tamaldiçoado — a habitar Del Vall, uma cidade pequena e esquecida, longe do\n");
    printf("\tecoar das espadas e do rugido dos exércitos.\n");
    printf("\n");
    printf("\t[...]\n");
    getchar();

    printf("\tSeus olhos ardem. Você os aperta com força, tentando afastar a estranheza\n");
    printf("\tde um sonho pesado, quase palpável. Quando a visão finalmente se ajusta,\n");
    printf("\tpercebe o mundo ao seu redor: a luz tremulante das tochas, o cheiro forte\n");
    printf("\tde álcool e suor, o som de canecos batendo, risadas descompassadas e o\n");
    printf("\tritmo de uma melodia bárdica. Está debruçado sobre uma mesa de madeira\n");
    printf("\tgasta, cercado por copos vazios. A boca amarga denuncia uma noite de\n");
    printf("\texcessos.\n");
    printf("\n");
    printf("\t[...]\n");
    getchar();

    printf("\tVocê está na Vaca Pelada — a melhor e única taverna de Del Vall.\n");
    getchar();
}


/************************************************ 
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * saida   : nodo com dados                     *
 ************************************************/
void entrada_dados( ARVORE* aux ){ 

    /*  printf( "\n\n Codigo: %d", aux->info.codigo ); */  
    aux->subd = NULL;    // nao aponta
    aux->sube = NULL;    // nao aponta
}

/*************************************************
 * imprime_ARVORE                                *
 * objetivo: rotina para imprimir dados          *
 * entrada : ARVORE                              *
 * saida   : dados em tela                       *
 *************************************************/ 
void imprime_ARVORE( ARVORE* aux ){    

    if(aux != NULL){
        printf("\nC�digo: %d", aux->info.codigo);
        imprime_ARVORE(aux->sube);
        imprime_ARVORE(aux->subd);
    } else
        printf("\n �rvore vazia!");


}

/************************************************
 * cria_ARVORE                                   *
 * objetivo: rotina para inicializar a ARVORE    *
 * entrada : nenhuma                             *
 * saida   : NULL (inicializa ARVORE)            *
 ************************************************/ 
void cria_ARVORE( ARVORE** r ){

    *r = NULL; // arvore criada, raiz nao aponta
    printf( "\n Arvore criada!" );
}

/************************************************* 
 * insere                                        *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE                              *
 * saida   : ARVORE com mais um registro         *
 *************************************************/ 
void insere(ARVORE **r) {
    int codPai, codNovo;
    char lado[10];
    char aux_lore[1000];
    ARVORE *noPai = NULL;

    // Verifica se a arvore esta vazia
    if (*r == NULL) {
        printf("\nA arvore esta vazia. Digite o codigo do nó raiz: ");
        scanf("%d", &codNovo);
        printf("\n Digite o novo lore: ");
        scanf("%s", aux_lore);

        *r = (ARVORE *)malloc(sizeof(ARVORE));
        if (*r != NULL) {
            (*r)->info.codigo = codNovo;
            (*r)->info.lore = strdup(aux_lore);
            (*r)->sube = NULL;
            (*r)->subd = NULL;
            printf("\nRaiz criada com o codigo %d.\n", codNovo);
        } else {
            printf("\nErro ao alocar memória para a raiz!\n");
        }
        return;
    }

    // Solicitar o codigo do nó pai
    printf("\nDigite o codigo do nó pai onde deseja inserir: ");
    scanf("%d", &codPai);

    // Função interna para buscar o nó pai
    ARVORE *buscarNoPai(ARVORE *atual, int codPai) {
        if (atual == NULL) return NULL; // Nó não encontrado
        if (atual->info.codigo == codPai) return atual; // Nó encontrado
        // Busca recursiva nos filhos
        ARVORE *esquerda = buscarNoPai(atual->sube, codPai);
        if (esquerda != NULL) return esquerda; // Encontrou na esquerda
        return buscarNoPai(atual->subd, codPai); // Tenta na direita
    }

    // Localiza o nó pai
    noPai = buscarNoPai(*r, codPai);
    if (noPai == NULL) {
        printf("\nNó pai com codigo %d não encontrado.\n", codPai);
        return;
    }

    // Solicitar o codigo do novo nó
    printf("\n Digite o codigo do novo nó: ");
    scanf("%d", &codNovo);
    printf("\n Digite o novo lore: ");
    scanf("%s", aux_lore);

    // Solicitar o lado para inserção
    printf("\n Deseja inserir na esquerda(e) ou direita(d) do nó pai [%d]? ", codPai);
    scanf("%s", lado);

    if (strcmp(lado, "e") == 0) {
        if (noPai->sube != NULL) {
            printf("\nJá existe um nó na esquerda do nó pai.\n");
        } else {
            noPai->sube = (ARVORE *)malloc(sizeof(ARVORE));
            if (noPai->sube != NULL) {
                noPai->sube->info.codigo = codNovo;
                noPai->sube->info.lore = strdup(aux_lore);
                noPai->sube->sube = NULL;
                noPai->sube->subd = NULL;
                printf("\nNó inserido à esquerda do nó pai %d.\n", codPai);
            } else {
                printf("\nErro ao alocar memória para o nó!\n");
            }
        }
    } else if (strcmp(lado, "d") == 0) {
        if (noPai->subd != NULL) {
            printf("\nJá existe um nó na direita do nó pai.\n");
        } else {
            noPai->subd = (ARVORE *)malloc(sizeof(ARVORE));
            if (noPai->subd != NULL) {
                noPai->subd->info.codigo = codNovo;
                noPai->subd->info.lore = strdup(aux_lore);
                noPai->subd->sube = NULL;
                noPai->subd->subd = NULL;
                printf("\nNó inserido à direita do nó pai %d.\n", codPai);
            } else {
                printf("\nErro ao alocar memória para o nó!\n");
            }
        }
    } else {
        printf("\nOpção inválida. Escolha 'esquerda' ou 'direita'.\n");
    }
}

/************************************************ 
 * busca                                        *
 * objetivo: achar nodo                         *
 * entrada : ARVORE e codigo a ser excluído     *
 * saída   : posição ou NULL (não encontrou)    *
 ************************************************/ 
int busca( int cod, ARVORE** a, ARVORE** p ){
   int achou = FALSE;                      // achou = indica se encontrou o codigo na estrutura

   *a = NULL;                              // ponteiro auxiliar para o anterior
   while( ( *p != NULL ) && ( !achou ) )
           if ( (*p)->info.codigo == cod ) // verifica se encontrou o codigo
                achou = TRUE;              // encontrou o codigo na estrutura
           else {
                *a = *p;                   // posiciona ponteiro auxiliar no anterior de p
                if( (*p)->info.codigo > cod )
                    *p = (*p)->sube;       // anda com o ponteiro p para a esquerda, pois o codigo procurado é menor
                else
                    *p = (*p)->subd;       // anda com o ponteiro p para a direita, pois o codigo procurado é maior 
           } // fim if ((*p)->info.codigo == cod)

   return achou; 
}

/*************************************************** 
 * remove                                          *
 * objetivo: rotina para excluir nodo da ARVORE    *
 * entrada : ARVORE                                *
 * saida   : ARVORE                                *
 ***************************************************/ 
void remove_cod( ARVORE** r ){
    ARVORE* p;                         // ponteiro auxiliar
    ARVORE* q;                         // ponteiro auxiliar
    ARVORE* b;                         // ponteiro auxiliar
    ARVORE* a;                         // ponteiro auxiliar para anterior
    int cod, achou;                    // cod = dado de entrada; achou = informa se codigo ja existe na estrutura

    if ( *r == NULL )
         printf("\n Arvore vazia!");
    else
       {    
        printf("\n Codigo de referencia: ");
        fflush( stdin );               // limpa buffer do teclado e faz a entrada de dados
        scanf( "%d", &cod ); 

        p = *r;                        // posiciona ponteiro auxiliar
        achou = busca( cod, &a, &p );  // verifica se codigo a ser inserida ja existe na arvore
        if( achou ){                   // se achou o codigo, remove
            if((( p->sube != NULL ) && ( p->subd != NULL )) || (( p->subd != NULL ) && ( p->sube == NULL ))){
                 sucessor( p, &q, &b );
                 p->info= q->info;     // substitui o codigo 
                 a= b;                 // ponteiros auxiliares sao posicionados na subarvore 
                 p= q;

                 if( p->sube != NULL ) // ajusta subarvore
                     b= p->sube;
                 else
                     b= p->subd;

                 if( p->info.codigo >= a->info.codigo )
                     a->subd= b;
                 else
                     a->sube= b;
            } 

            else 
               if(( p->subd == NULL ) && ( p->sube != NULL )){
                    antecessor( p, &q, &b );
                    p->info= q->info;     // substitui o codigo
                    a= b;                 // ponteiros auxiliares sao posicionados na subarvore 
                    p= q;

                    if( p->subd != NULL ) // ajusta subarvore
                        b= p->subd;
                    else
                        b= p->sube;

                    if( p->info.codigo >= a->info.codigo )
                        a->sube= b;
                    else
                        a->subd= b;
               }  
               else
                  if(( p->subd == NULL ) && ( p->sube == NULL ))
                       if( p == *r )     // remove a raiz quando nao tem filhos
                           *r= NULL;
                       else      
                           if( p->info.codigo >= a->info.codigo )
                               a->subd= NULL;
                           else
                               a->sube= NULL;

            free( p ); // remove registro que substituiu o excluido
       }
   }
}

/*************************************************** 
 * sucessor                                        *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * saida   : ponteiros auxiliares q e b            *
 ***************************************************/ 
void sucessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->subd;
 while( (*q)->sube != NULL ){          // caminha pela esquerda ate encontrar folha
         *b= *q;                       // atualiza ponteiro para guardar endereco do pai
         *q= (*q)->sube;               // caminha para a esquerda
 }
}

/*************************************************** 
 * antecessor                                      *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * saida   : ponteiros auxiliares q e b            *
 ***************************************************/ 
void antecessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->sube;
 while( (*q)->subd != NULL ){        // caminha pela direita ate encontrar folha
         *b= *q;                     // atualiza ponteiro para guardar endereco do pai
         *q= (*q)->subd;             // caminha para a direita
 }
}         

/************************************************* 
 * insere_recursivo                              *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE e cod                        *
 * saida   : ARVORE com mais um registro         *
 *************************************************/ 
void insere_recursivo( ARVORE** p, int cod ){

        if(*p == NULL ){ // insere
            ARVORE *no = (ARVORE *) malloc (sizeof(ARVORE));
            if(no != NULL ){
                no->info.codigo = cod;
                no->subd = NULL;
                no->sube = NULL;
                *p = no;
            }else
                printf("\n �rvore cheia!");	 
        } else
            if((*p)->info.codigo > cod) // percorre � esquerda
                insere_recursivo(&(*p)->sube, cod);
            else 
                if((*p)->info.codigo < cod) // percorre � direita
                    insere_recursivo(&(*p)->subd, cod);	
                else
                    printf("\nRegisto encontrado!");		
} // desempilha

/***************************************************
 * busca_recursivo                                 *
 * objetivo: rotina para buscar registro por codigo*
 * entrada : ARVORE e cod                          *
 * saida   : ARVORE com mais um registro           *
 ***************************************************/ 
  void busca_recursivo( ARVORE *p, int cod ){

    if( p == NULL || p->info.codigo == cod){
        if(p != NULL) 
            printf("\nC�digo: %d", p->info.codigo);
        else 
            printf("\nRegistro n�o encontrado!");
    }else {
        if(p->info.codigo > cod)
            busca_recursivo(p->sube, cod);
        else 
            if(p->info.codigo < cod)
                busca_recursivo(p->subd, cod);
    } if(p == NULL || p->info.codigo != cod )
        printf("\n�rvore vazia!");


} // desempilha

/****************************************************
 * remove_recursivo                                 *
 * objetivo: rotina para remover registro por codigo*
 * entrada : ARVORE e cod                           *
 * saida   : ARVORE com registro removido           *
 ****************************************************/ 
ARVORE* remove_recursivo( ARVORE **p, int cod ){

    if(*p == NULL)
        printf("\narvore vazia!"); //verificar se a �rvore est� vazia
    else
        if( (*p)->info.codigo > cod ) 
            (*p)->sube= remove_recursivo(&(*p)->sube, cod ); //percorre a esquerda
        else
            if( (*p)->info.codigo < cod )
                (*p)->subd= remove_recursivo(&(*p)->subd, cod ); //percorre a esquerda
            else
                if((*p)->info.codigo == cod){
                    if( (*p)->sube == NULL && (*p)->subd == NULL ){ //verifica se o registro � uma folha
                        free( *p );							  //libera espa�o
                        *p = NULL;	
                        printf("\nRegistro removido com sucesso!");						  //ajusta o ponteiro
                    }else 
                        if((*p)->sube != NULL && (*p)->subd != NULL){
                                ARVORE* temp;
                                while(temp->subd != NULL)
                                    temp = temp->subd;
                                (*p)->info.codigo = temp->info.codigo;
                                temp->info.codigo = cod;
                                (*p)->sube = remove_recursivo(&(*p)->sube, cod);
                                printf("\nRegistro removido com sucesso!");		
                        } else {
                            ARVORE* temp;
                            if((*p)->sube != NULL)
                                temp = (*p)->sube;
                            else
                                temp = (*p)->subd;
                            free(*p);
                            printf("\nRegistro removido com sucesso!");	
                        }

                }


} // desempilha

/************************************************
 * salva_arvore                                 *
 * objetivo: salva a ARVORE em formato de txt   *
 * entrada : ARVORE                             *
 * saida   : txt com os dados da ARVORE         *
 ***********************************************/ 
void salva_arvore( ARVORE *r ){
    char nome_arquivo[30];
    FILE *arquivo;                             // declada o ponteiro para o arquivo

    if( r == NULL ){                           // verifica se a arvore esta vazia 
        printf( "\n Nao e possivel salvar uma arvore vazia!" );
        getchar();                             // parada da tela
        return;
    }

    printf( "\n Nomeie o arquivo.: " );
    scanf( "%s", &nome_arquivo );
    strcat( nome_arquivo, ".txt" );            // define o arquivo como .txt, concatena .txt ao nome

    arquivo = fopen( nome_arquivo, "w" );      // abre o arquivo em modo de escrita
    if( arquivo == NULL ){                     // verifica se o arquivo foi criado corretamente
        printf( "\n Erro ao criar arquivo!" );
        getchar();                             // parada da tela
        return;
    }
    salva_codigo( r, arquivo );                // salva os codigos de maneira recursiva no txt

    fclose( arquivo );                         // fecha o arquivo
    printf( "\n Arvore salva com sucesso!" );
    getchar();                                 // parada da tela
}

void salva_codigo( ARVORE *r, FILE *arquivo ){
    fprintf( arquivo, "%d\n", r->info.codigo );
    fprintf( arquivo, "%s\n", r->info.lore );

    if( r->sube != NULL )                      // verifica se o caminho esquerdo esta vazio, se nao continua por ele
        salva_codigo( r->sube, arquivo );      // salva o valor que estiver no caminho esquerdo

    if( r->subd != NULL )                      // verifica se o caminho direito esta vazio, se nao continua por ele
        salva_codigo( r->subd, arquivo );      // salva o valor que estiver no caminho direito
}

void carrega_arvore(ARVORE **r) {
    char nome_arquivo[30];
    FILE *arquivo;

    printf("\n Informe o arquivo: ");
    scanf("%s", nome_arquivo);  // Nome do array já é um ponteiro
    strcat(nome_arquivo, ".txt");

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("\n Arquivo nao encontrado!");
        return;
    }

    cria_ARVORE(r);  // Inicializa a árvore para evitar conflitos
    int cod;
    char lore_aux[1000];

    while (fscanf(arquivo, "%d\n", &cod) == 1) {
        if (fgets(lore_aux, sizeof(lore_aux), arquivo) != NULL) {
            // Remover o caractere de nova linha do final da string (se existir)
            lore_aux[strcspn(lore_aux, "\n")] = '\0';

            ARVORE *no = (ARVORE *)malloc(sizeof(ARVORE));
            if (no != NULL) {
                no->info.codigo = cod;
                no->info.lore = strdup(lore_aux); // Aloca memória para o texto do lore
                no->subd = NULL;
                no->sube = NULL;

                carrega_codigo(r, no);  // Insere o nó na árvore
            } else {
                printf("\n Erro ao alocar memória para o nó!");
                break;
            }
        } else {
            printf("\n Erro ao ler lore do arquivo!");
            break;
        }
    }

    fclose(arquivo);
    printf("\n Arvore carregada com sucesso!");
    getchar();  // Parada da tela
}
void carrega_codigo(ARVORE **r, ARVORE *no) {
    if (*r == NULL) {
        *r = no;
        return;
    }

    if (no->info.codigo > (*r)->info.codigo) {
        carrega_codigo(&(*r)->subd, no);
    } else {
        carrega_codigo(&(*r)->sube, no);
    }
}
