#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define NUM_LETRAS 26
#define ASCII_A 65
#define TAMANHO_SENHA 4

const int COPRIMES[4] = {3, 5, 7, 11};
const int SHIFTS[4] = {7, 11, 13, 17};

char* LeArquivo();

// Fun��o de criptografia fornecida pelo professor
char* encrypt(const char* str) {
    // Aloca uma string din�mica
    char* str_result = (char*) malloc(sizeof(char) * (TAMANHO_SENHA + 1));

    // Verifica se a aloca��o deu certo
    if (!str_result) {
        perror("Erro ao alocar mem�ria");
        exit(EXIT_FAILURE);
    }

    // Aqui faz a criptografia em si
    for (int i = 0; i < TAMANHO_SENHA; i++) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            int val = c - ASCII_A;
            val = (val * COPRIMES[i] + SHIFTS[i]) % NUM_LETRAS;
            str_result[i] = val + ASCII_A;
        } else {
            // Informa se o processo de criptografia deu errado
            perror("Erro: String cont�m caracteres inv�lidos.");
            free(str_result);
            exit(EXIT_FAILURE);
        }
    }

    str_result[TAMANHO_SENHA] = '\0';
    return str_result;
}

int main(){
    char* arquivo[]= {"001.txt", "002.txt", "003.txt",
                      "004.txt", "005.txt", "006.txt",
                      "007.txt", "008.txt", "009.txt",
                      "010.txt"};

  //colcando para portugu�s
    setlocale(LC_ALL, "portuguese");

    // Envia os arquivos para serem lidos na fun��o e retornarem para uma nova string, j� criptografados
    for(int i=0; i<10; i++){
        LeArquivo(arquivo[i]);
    }

return 0;
}


char* LeArquivo(char arquivo[]){
    char senhas[50];

    // Abre o arquivo e verifica se ele existe/deu problema
    FILE *fsenhas;
    fsenhas = fopen(arquivo, "a+");
    if (fsenhas == NULL)
        printf("problemas ao abrir o aquivo %s!", arquivo);

    // L� o conte�do de dentro do arquivo e imprime na tela
    while(fgets(senhas, 30, fsenhas)!=NULL){
		printf("%s", senhas);
		// Colocar uma l�gica para que ele retorne uma string j� criptografada
		// Ou colocar uma l�gica para ele retornar as strings
	}

    fclose(fsenhas);
    puts("\n");
}
