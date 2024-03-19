#include <stdio.h>
#include <stdlib.h>

void jogar_jogo(char tabuleiro[3][3],char simbolo_1,char simbolo_2);
void jogar_ply(char tabuleiro[3][3],char simbolo);
int verifica_fim(char tabuleiro[3][3],char simbolo_jogador_1);
void escolher_simbolo(char *simbolo_x, char *simbolo_o);
void printar_tabuleiro(char tabuleiro[3][3]);



int main(){
    /*
        declaraçoes:
            -tabuleiro 3 por 3 com seus espaços vazios 
            -definir os simbolos dos jogadosres 1 e 2
            
        input:
            -pedido -> input do usuario para escolher entre duas opçoes : 1.jogar o jogo , 2.escolher simbolo
        
        funçoes:
            -escolher_simbolo() -> muda o simbolo dos jogadores { recebe : os dois simbolos ja declarados para alteraçao}
            -jogar_jogo() -> começa o jogo {recebe: tabuleiro, os dois simbolos dos jogadores}
    */

    char tabuleiro[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char simbolo_jogador_1 = 'X';
    char simbolo_jogador_2 = 'O';
    int pedido;
    printf("******************************************  JOGO DA VELHA   ****************************************** \n");
    do {
        printf("    1. Comecar a jogar \n");
        printf("    2. Escolher Simbolo \n");
        scanf(" %d",&pedido);
    }while (pedido != 1 && pedido != 2);
    
    if ( pedido ==2 ){
        escolher_simbolo(&simbolo_jogador_1,&simbolo_jogador_2);
    }
    jogar_jogo(tabuleiro,simbolo_jogador_1,simbolo_jogador_2);

    return 0;
}

void jogar_ply(char tabuleiro[3][3],char simbolo){
    /*
        funçao recebe: 
            - tabuleiro , simbolo do jogador da rodada 

        declaraçoes:
            -i e j para receber a posiçao do tabuleiro
        
        loop do while:
            -continua pedindo a posiçao ate ser uma posiçao valida
        
        -> Assim q achar uma posiçao valida é adicionado o simbolo naquela posiçao [i][j] digitada 
    */
    int i,j;
    do{
        printf("---------------- jogador %c ---------------- \n ",simbolo);
        printf("    Escolha uma posicao entre 0 - 2 \n");
        printf("     ESCREVA O VALOR : Linha (espaco) Coluna \n");
        scanf(" %d %d", &i, &j);

    } while( i<0 || i>2 || j<0 || j>2 || tabuleiro[i][j] !=' ');
    tabuleiro[i][j] = simbolo;
}

int verifica_fim(char tabuleiro[3][3],char simbolo_jogador_1){
    /*
        funçao recebe:
            - tabuleiro, simbolo do jogador 1

        -> O simbolo do jogador 1 vai ser usado para fazer uma comparaçao e saber qual valor("resultado") retornar 
        -> Verifica se há um vencedor. Checa todas as linhas, colunas e diagonais para encontrar três símbolos iguais.
        -> Retorna 1 se o jogador 1 ganha (símbolo X ou alternativo), 2 se o jogador 2 ganha, ou 0 se o jogo ainda não acabou.
        -> Assume que o jogo continua se qualquer espaço estiver vazio, indicando um jogo ainda em progresso.

    */
    
    //verifica as linhas e as colunas se tem um vencedor
    for (int i = 0; i<3; i++){
        if (tabuleiro[i][0]==tabuleiro[i][1] && tabuleiro[i][1]==tabuleiro[i][2] && tabuleiro[i][0] != ' '){
           return (tabuleiro[i][0]==simbolo_jogador_1 ? 1 : 2);
        }
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' '){
             return (tabuleiro[0][i]==simbolo_jogador_1 ? 1 : 2);
        }
        }


    //verifica a diagonal se tem um vencedor
    if (
        (tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2] && tabuleiro[0][0] != ' ') ||
        (tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0] && tabuleiro[0][2] != ' ')) {
            return (tabuleiro[1][1]==simbolo_jogador_1 ? 1 : 2);
        }

    //verificar se tem opçoes para jogar
    for (int v=0; v<3; v++)
    {
        for(int k=0; k<3; k++){
            if (tabuleiro[v][k] == ' '){
                return 0;
            }
        }
    }
    return 0;
}

void jogar_jogo(char tabuleiro[3][3],char simbolo_1,char simbolo_2){
    /*
        funçao recebe:
            - tabuleiro, simbolo do jogador 1 e do jogador 2 
        
        declaraçoes:
            -jogadas -> vai ser usado para contar o numero de jogadas 
            -resultado -> armazena um numero interio que representa quem é o vencedor/empatou
        
        jogar_ply() -> funçao para colocar o simbolo do jogador no tabuleiro
        verifica_fim() -> retorna um inteiro com o resultado (podendo ser no valor de  1, 2, 0)
        printar_tabuleiro() -> printa o tabuleiro 

        switch case:
            -analize o valor da variavel resultado e printa a resposta
    */

    int jogadas=0;
    int resultado= 0;
    while (jogadas <9 && resultado == 0){
        //verifica de quem é a vez de jogar seguinta a ordem --- par -> jogador 1 impar -> jogador 2
        if (jogadas % 2 == 0 ){
            jogar_ply(tabuleiro,simbolo_1);
        }
        else{
            jogar_ply(tabuleiro,simbolo_2);
        }
        //a partir da 4 jogada começa a verificar se tem um vencedor 
        if (jogadas > 3){
            resultado = verifica_fim(tabuleiro,simbolo_1);
        }
        //printa o tabuleiro ataulizado toda vez 
        printar_tabuleiro(tabuleiro);
        //contador do loop while 
        jogadas++;
        }
    
    switch (resultado)
    {
        case 1:
            printf("!!!!!!!!!!!!!!  JOGADOR %c GANHOU  !!!!!!!!!!!!!!",simbolo_1);
            break;
        case 2:
            printf("!!!!!!!!!!!!!!  JOGADOR %c GANHOU  !!!!!!!!!!!!!!",simbolo_2);
            break;
        default:
            printf("O jogo empatou :( :( :( :( :( :( :( :( ");
            break;
    }
}

void printar_tabuleiro(char tabuleiro[3][3]){
    /*
        funçao recebe:
            -tabuleiro
        
        -> funçao printa o tabuleiro
    */
    printf(" %c | %c | %c \n",tabuleiro[0][0],tabuleiro[0][1],tabuleiro[0][2]);
    printf("---------------\n");
    printf(" %c | %c | %c \n",tabuleiro[1][0],tabuleiro[1][1],tabuleiro[1][2]);
    printf("---------------\n");
    printf(" %c | %c | %c \n",tabuleiro[2][0],tabuleiro[2][1],tabuleiro[2][2]);
}

void escolher_simbolo(char *simbolo_x, char *simbolo_o){
    /*
        funçao recebe:
            -recebe os dois simbolos ja declarados 

        declaraçoes:
            jogador_1 -> vai alocar o novo simbolo digitado pelo jogador 1
            jogador_2 -> vai alocar o novo simbolo digitado pelo jogador 2

        -> Faz alteraçao nas variaveis:    simbolo_x( novo simbolo jogador 1 )   e   simbolo_0( novo simbolo do jogador 2)
        
    */
    // alterar o valor do simbolo_x
    char jogador_1;
    printf(" Simbolo do jogador 1: ");
    scanf(" %c",&jogador_1);
    *simbolo_x = jogador_1;

    //alterar o valor do simbolo_o
    char jogador_2;
    printf(" Simbolo do jogador 2: ");
    scanf(" %c",&jogador_2);
    *simbolo_o = jogador_2;
}