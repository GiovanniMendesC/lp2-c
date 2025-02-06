#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define NUM_LETRAS 26
#define ASCII_A 65
#define TAMANHO_SENHA 4

const int COPRIMES[4] = {3, 5, 7, 11};
const int SHIFTS[4] = {7, 11, 13, 17};

char* LeArquivo();
void Descriptografa(char senhas[]);

// Função de criptografia fornecida pelo professor
char* encrypt(const char* str) { //Recebe uma string

    char* str_result = (char*) malloc(sizeof(char) * (TAMANHO_SENHA + 1)); // Aloca uma string dinâmica

    // Verifica se a alocação deu certo
    if (!str_result) {
        perror("Erro ao alocar memória");
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
            // e o caractere que deu erro
            printf("\nCaractere: '%d'\n", str_result[i]);
            perror("Erro: String contém caracteres inválidos.");
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


    setlocale(LC_ALL, "portuguese"); //colcando para português

    // Envia os arquivos para serem lidos e criptografados
    for(int i=0; i<10; i++){
        LeArquivo(arquivo[i]);
    }

return 0;
}


char* LeArquivo(char arquivo[]){
    char senhas[80] = "";
    char temp[50] = "";

    // Abre o arquivo e verifica se ele existe/deu problema
    FILE *fsenhas;
    fsenhas = fopen(arquivo, "a+");
    if (fsenhas == NULL)
        printf("problemas ao abrir o aquivo %s!", arquivo);

    // Lê o conteúdo de dentro do arquivo e imprime na tela
    while(fgets(temp, 30, fsenhas)!=NULL){
		strcat(senhas, temp);
	}

	printf("Senhas do arquivo: %s \n", arquivo);
    puts(senhas);

	Descriptografa(senhas); // Chama a função para criptografar
    strcpy(senhas, "");

    fclose(fsenhas); // Fecha o arquivo
    puts("\n");
}

void Descriptografa(char senhas[]){
    char senha[5] = "";
    char senhas_novas[80] = "";

    for(int i=0, j=0; senhas[i] != '\0'; i++){
        if(senhas[i] != '\n'){
            senha[j] = senhas[i];
            j++;
        }else{
            printf("\nCriptografando: %s\n", senha);
            strcat(senhas_novas, encrypt(senha));
            strcat(senhas_novas, " ");
            strcpy(senha, "");
            printf("Resultado: %s\n", senhas_novas);
            j=0;
        }
    }
}
