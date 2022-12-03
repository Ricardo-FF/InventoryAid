#include <stdio.h> //Biblioteca padrão
#include <stdlib.h> //Biblioteca padrão
#include <time.h> //Biblioteca para manipulação da hora
#include <string.h>//Biblioteca para manipulação de strings

//Iniciando váriaveis globais
//Define a constante MAX que é o limite de caracter para os vetores e de repetição para os for's
#define MAX 20
int opcao;//Global responsável por receber a opção do usuário

//Função que abre o arquivo e retorna o ponteiro para o arquivo
FILE* abreArquivo(){
  //Iniciando váriaveis locais
  FILE* arq; //Ponteiro para o arquivo que contém as palavras
  
  system("clear");//Limpa o console

  arq = fopen("palavras.txt","r");//Abre o arquivo no formato somente leitura e atribui para o ponteiro arq

//Retorna o ponteiro para o arquivo
return (arq);
}

//Procedimento do menu inicial do jogo
void menu_inicial(){
  system("clear");//Limpa o console
  
  printf("Bem-Vindo ao jogo das palavras!!\n\n");
  printf("1 - Jogar\n");
  printf("2 - Ajuda (Recomendado)\n");
  printf("3 - Sair\n\n");
  printf("Digite uma opção(Número):\n");
  
  scanf("%d", &opcao);//Recebe o input da opção
  direciona(opcao);//Chama a função de direcionamento
}

//Procedimento que exibe a ajuda do jogo
void ajuda(){
  //Iniciando váriaveis locais
  char sair;//Usada para verificar se o usuário quer sair da ajuda
  
  system("clear");//Limpa o console
  
  printf("Ajuda :)\n\n");
  printf("O jogo funciona da seguinte forma:\n\n");
  printf("O jogador terá 1 chance a cada letra que a palavra que precisa ser adivinhada tiver.\n");
  printf("Por exemplo, a palavra \"Bola\" tem 4 letras então o jogador terá 4 chances.\n\n");
  printf("Caso queira adicionar palavras novas é possível adicioná-las no arquivo \"palavras.txt\".\n\n");
  printf("ATENÇÃO: Não utilizar caracteres especiais no arquivo e deixar apenas 1 palavra por linha!!!\n\n");
  printf("Bom Jogo!!! :P\n\n");
  printf("Digite \"q\" para sair da ajuda.\n");
  
  do{
    scanf("%c",&sair);//Lê oinput do usuário para  fechar a ajuda
  }while(sair != 'q');
  
  menu_inicial();//Chama o procedimento que exibe o menu
}
//Sorteia umapalavra noarquivo e retorna o ponteiro para o vetor com a palavra sorteada
char * sorteiaPalavra(int nump){
  FILE* arq;//Ponteiro para o arquivo aberto
  char c; //Char que armazena temporáriamente cada caracter
  static char array[MAX]; //Array que armazena a palavra
  int ctrl=0,i=0;//Variaveis de controle
  
  arq = abreArquivo();//Função que abre o arquivo

  //Escreve a palavra sorteada para um array
  do{
    if(ctrl == nump){
      if(c >= 'a' && c <= 'z'){
        array[i] = c;
      }
      i++;
    }
    if(c == '\n'){
      ctrl++;
    }

    c = fgetc(arq);
  }while (c != EOF);
  
fclose(arq);//Fecha o arquivo
//Retorna o ponteiro para o vetor com a palavra sorteada
return array;
}

//Procedimento responsável pelo jogo em sí
void jogo(){
  char *p, chute[MAX], acerto[MAX]; //Ponteiro que recebe a palavra sorteada e vetor que recebe o chute
  int tamanhos, chance; //Armazena o tamanho da palavra sorteada e o número de chances
  int ctrl=0;//Variavel de controle para validação
  
  p = sorteiaPalavra(myrand(contaPalavras()));//recebe o ponteiro para a palavra sorteada
  tamanhos = strlen(p);//Verifica o tamanho da palavra sorteada
  chance = tamanhos;//Define o número de chances

  //Executa o jogo enquanto o jogador tiver chances
  do{
  printf("Você possui %d chances!!\n\n",chance);
  printf("A palavra possuí %d letras.\n", tamanhos);
  printf("Chute uma palavra:\n");
  scanf("%s",chute); //Lê o chute do usuário
  
  chance--;
    
  //For encadeado que valida se alguma das letras da palavra chutada existe na palavra sorteada
    for (int i = 0; i < tamanhos; i++) {
      for (int e = 0; e < tamanhos; e++){
        if(chute[i]==*(p+e)){
          printf("Há uma letra \"%c\" na posição %d\n\n",chute[i],e+1);//Informa as letras acertadas e a posição
          acerto[i] = chute[i];//Adiciona as letras acertadas em um vetor
        }
      }//Valida que as chances acabaram e informa que o jogador perdeu e qual a palavra que deveria adivinhar
      if(chance == 0){
        printf("Você perdeu :(\n");
        printf("A palavra era \"");
        for (int e = 0; e < tamanhos; e++){
          printf("%c",*(p+e));
        }
      printf("\"");
      }
    }
    //Controle para saber se o jogador acertou todas as letras na ordem certa
    for(int f = 0; f < MAX;f++){
      if(acerto[f] == *(p+f)){
        ctrl+=1;
      }else{
        ctrl=0;
        break;
      }
    }
    //Valida a vitória do jogador e informa o mesmo
    if(ctrl==MAX){
      system("clear");
      printf("Você Acertou!! :)");
      system("sleep 6");//Espera 6 segundos antes de quebrar o do/while
      break;
    }else{
      //Reseta o vetor usado para verificar as letras acertadas, impede que fique sujeira
      for (int i = 0; i < MAX; i++) {
        acerto[i] = NULL;
      }
    }
    printf("\n");
  }while(chance > 0);//Repete o "do" enquanto o usuário tiver chances

menu_inicial();//Chama o procedimento responsável pela tela de inicial
}

//Função que direciona o usuário entre as telas
int direciona(int op){
  
  switch(op){
    case(1):
      jogo();//Chama o procedimento responsável pelo jogo
    break;
    case(2):
      ajuda();//Chama o procedimento responsável pela tela de ajuda
    case(3):
      exit(0);//Termina do programa
    default:
      menu_inicial();//Chama o procedimento responsável pela tela de inicial caso não haja opção válida
  }
}

int myrand(int limit){
  int r; //Número aleatório
  
  srand(time(0));//Alimenta a seed do número aleatório com a hora atual
  
  r = rand() % limit;

return r;//Retorna o número aleatório
}

//Função que conta quantas palavras há no arquivo
int contaPalavras(){
  FILE* arq;//Ponteiro para o arquivo aberto
  char c; //Char que armazena temporáriamente cada caracter
  int contador=1;//Variavel que recebe o resultado da contagem
  
  arq = abreArquivo();//Função que abre o arquivo
  //Percorre o Arquivo até o final contando as palavras
  do{
    if(c == '\n'){
      contador++;
    }
    c = fgetc(arq);
  }while (c != EOF);
  
  fclose(arq);//Fecha o arquivo
//Retorna a quantidade de palavras
return contador;
}

int main(void) {
  
  menu_inicial();//Chama o procedimento que exibe o menu

}