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
char* encrypt(const char* str) {
    // Aloca uma string dinâmica
    char* str_result = (char*) malloc(sizeof(char) * (TAMANHO_SENHA + 1));

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

            printf("\nCaractere: '%d'", str_result[i]);
            // Informa se o processo de criptografia deu errado
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

  //colcando para português
    setlocale(LC_ALL, "portuguese");

    // Envia os arquivos para serem lidos na função e retornarem para uma nova string, já criptografados
    for(int i=0; i<10; i++){
        LeArquivo(arquivo[i]);
    }

return 0;
}


char* LeArquivo(char arquivo[]){
    char senhas[500] = "";
    char temp[50] = "";

    // Abre o arquivo e verifica se ele existe/deu problema
    FILE *fsenhas;
    fsenhas = fopen(arquivo, "a+");
    if (fsenhas == NULL)
        printf("problemas ao abrir o aquivo %s!", arquivo);

    // Lê o conteúdo de dentro do arquivo e imprime na tela
    while(fgets(temp, 30, fsenhas)!=NULL){
		strcat(senhas, temp);
		//puts(temp);
		// Colocar uma lógica para que ele retorne uma string já criptografada
		// Ou colocar uma lógica para ele retornar as strings
	}
	printf("Senhas do arquivo: %s \n", arquivo);
    puts(senhas);
	Descriptografa(senhas);
    strcpy(senhas, "");
    fclose(fsenhas);
    puts("\n");
}

void Descriptografa(char senhas[]){
    char senha[5] = "";
    char senhas_novas[sizeof(senhas)] = "";
    int j=0;

    for(int i=0; senhas[i]!='\0'; i++){
        if (senhas[i] != '\n') {
            if (j < sizeof(senha) - 1) { // Evitar estouro
                senha[j++] = senhas[i];
                senha[j] = '\0'; // Garantir que sempre esteja terminada
            }
        }else {
            puts("criptografou");
            strcat(senhas_novas, encrypt(senha)); // Concatenar versão criptografada
            strcat(senhas_novas, "\n"); // Adicionar quebra de linha
            j = 0;
            memset(senha, 0, sizeof(senha)); // Limpar `senha`
        }
    }
    puts(senhas_novas);
}
