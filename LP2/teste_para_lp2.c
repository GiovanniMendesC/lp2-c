#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>

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
    int num_de_arquivos = sizeof(arquivo) / sizeof(arquivo[0]);

    clock_t inicio, fim;
    double tempo_total;

    setlocale(LC_ALL, "portuguese"); //colcando para português

    HANDLE processos[num_de_arquivos];
    DWORD ids_processos[num_de_arquivos];
    DWORD status_processos[num_de_arquivos];

    inicio = clock();


    // Envia os arquivos para serem lidos e criptografados
    for(int i=0; i<num_de_arquivos; i++){
        processos[i] = CreateThread(
            NULL,
            0,
            LeArquivo,
            arquivo[i],
            0,
            &ids_processos[i]
        );

        if(processos[i] == NULL){
            printf("Erro ao criar processo para o arquivo %s\n", arquivo[i]);
            status_processos[i]=1;
        }
    }

    for (int i = 0; i < num_de_arquivos; i++) {
            if (processos[i] != NULL) {
                WaitForSingleObject(processos[i], INFINITE);
                GetExitCodeThread(processos[i], &status_processos[i]);
                CloseHandle(processos[i]);
            }
    }

    fim = clock();
    tempo_total = (double)(fim-inicio) / CLOCKS_PER_SEC;

    // Exibe os resultados
    printf("\nResultados:\n");

    for (int i = 0; i < num_de_arquivos; i++) {
        printf("Arquivo: %s, Status: %s\n",
               arquivo[i],
               status_processos[i] == 0 ? "Sucesso" : "Falha");
    }

    printf("Tempo total de execução: %.2f segundos\n", tempo_total);

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
    char senhas_novas[500] = "";

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
