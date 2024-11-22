#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////Vetor de inteiros //////////////////

int* criar_vetor(int* tamanho) {
    printf("Quantos elementos deseja no vetor? ");
    scanf("%d", tamanho);

    // aloca dinamicamente o vetor
    int* vetor = (int*) malloc(*tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1); // Encerra o programa em caso de erro de alocao
    }

    // preenche o vetor com valores fornecidos pelo usuário
    for (int i = 0; i < *tamanho; i++) {
        printf("Digite o valor para a posicao %d: ", i);
        scanf("%d", &vetor[i]);
    }

    return vetor;
}
int busca_linear(int* vetor, int tamanho, int numero) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == numero) {
            return i; // retorna se foi encontrado ou nao
        }
    }
    return -1; // retorna -1 se nao achar 
}
void ordenar_vetor(int* vetor, int tamanho) { // ordena o vetor para busca linear
    int aux;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Troca os elementos
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
int busca_binaria(int* vetor, int tamanho, int numero) { // funcao que faz a busca binaria
    ordenar_vetor(vetor,tamanho);
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        if (vetor[meio] == numero) {
            return meio; // se econtrado ou nao
        } else if (vetor[meio] < numero) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // retorna -1 se nao econtrar
}




////////////////Gerenciamento de alunos //////////////////
typedef struct cadastro{    // definicao da estrutura struct
    char nome[50];
    int matricula; 
    float nota1, nota2, nota3;
    float media;
} cadastro;

cadastro* cadastrar_alunos(cadastro* alunos, int* total_alunos) { // funcao que cadastra o aluno
    int num_novos;
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &num_novos);

    if (*total_alunos + num_novos > 100) {
        printf("Erro: Limite maximo de 100 alunos atingido.\n"); // limte maximo de alunos
        return alunos;
    }

    // aloca dinamicamente o vetor de acordo com a entrada
    alunos = realloc(alunos, (*total_alunos + num_novos) * sizeof(cadastro)); 
    if (alunos == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    // faz a leitura das informacoes do aluno
    for (int i = 0; i < num_novos; i++) {
        printf("\nCadastro do aluno %d:\n", *total_alunos + 1);
        printf("Nome: ");
        setbuf(stdin, NULL);
        fgets(alunos[*total_alunos].nome,sizeof(alunos[*total_alunos].nome),stdin);
        printf("Matricula: ");
        scanf("%d", &alunos[*total_alunos].matricula);
        printf("Nota 1: ");
        scanf("%f", &alunos[*total_alunos].nota1);
        printf("Nota 2: ");
        scanf("%f", &alunos[*total_alunos].nota2);
        printf("Nota 3: ");
        scanf("%f", &alunos[*total_alunos].nota3);
        // faz a media das 3 notas
        alunos[*total_alunos].media = (alunos[*total_alunos].nota1 + alunos[*total_alunos].nota2 + alunos[*total_alunos].nota3) / 3;

        (*total_alunos)++;
    }
    return alunos;
}

void buscar_aluno_linear(cadastro* alunos, int total_alunos) { // funcao de busca linear
    int matricula_pesquisada;
    printf("\nDigite a matricula que deseja buscar: ");
    scanf("%d", &matricula_pesquisada);

    // Busca no vetor inteiro a matricula
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].matricula == matricula_pesquisada) {
            printf("\nAluno encontrado:\n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Notas: %.2f, %.2f, %.2f\n", alunos[i].nota1, alunos[i].nota2, alunos[i].nota3);
            printf("Media: %.2f\n", alunos[i].media);
            return; // Sai da funcao apos encontrar o aluno
        }
    }

    printf("Nenhum aluno encontrado com a matricula %d.\n", matricula_pesquisada); // caso nao enconte a matricula
}
void ordena(cadastro* alunos, int n) { //bubble pra ordenar o vetor de acordo com a matricula
    int i, j; //iteradores
    cadastro aux;
    for (j = n - 1; j > 0; j--) {
        for (i = 0; i < j; i++) {
            if (alunos[i].matricula > alunos[i + 1].matricula) { 
                aux = alunos[i];
                alunos[i] = alunos[i + 1];
                alunos[i + 1] = aux;
            }
        }
    }
}

void buscar_aluno_binaria(cadastro* alunos, int total_alunos) { // funcao de busca binaria pela matricula
    ordena(alunos,total_alunos ); // ordena antes de fazer a busca binaria
    int matricula_pesquisada;
    printf("\nDigite a matricula que deseja buscar: ");
    scanf("%d", &matricula_pesquisada);

    int esquerda = 0;
    int direita = total_alunos - 1; // divide o vetor em direita e esquerda
    int meio;
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        if (alunos[meio].matricula == matricula_pesquisada) {
            printf("\nAluno encontrado:\n");
            printf("Nome: %s\n", alunos[meio].nome);
            printf("Matricula: %d\n", alunos[meio].matricula);
            printf("Notas: %.2f, %.2f, %.2f\n", alunos[meio].nota1, alunos[meio].nota2, alunos[meio].nota3);
            printf("Media: %.2f\n", alunos[meio].media);
            return; // se encontrar o aluno sai da funcao
        } else if (alunos[meio].matricula < matricula_pesquisada) {
            esquerda = meio + 1; 
        } else {                        // vai fatiando até encontrar a matricula
            direita = meio - 1;
        }
    }
    printf("Nenhum aluno encontrado com a matricula %d.\n", matricula_pesquisada); // caso nao ache a matricula
}

int main (){
////////////////Vetor de inteiros //////////////////

    int tamanho;
    int* vetor = NULL;
    int numero, resultado;
////////////////Gerenciamento de alunos //////////////////

    cadastro* alunos = NULL; // ponteiro para vetor de struct
    int total_alunos = 0;
    int menu = 10;

    while(menu != 0){ // menu do programa
        printf("\nEscolha uma opcao para prosseguir:\n \n Vetor de Inteiros:\n\n 1- Criar vetor de inteiros\n 2- Busca linear no vetor \n 3- Busca binaria no vetor");
        printf("\n\n Gerenciar Alunos: \n\n 4- Cadastrar Aluno\n 5- Buscar aluno (Busca linear)\n 6- Buscar aluno (Busca binaria)\n 7- Sair\n Opcao:");
        scanf("%d", &menu);
        
////////////////Vetor de inteiros //////////////////
        if(menu == 1){ // criar vetor
         vetor = criar_vetor(&tamanho);
        } else if (menu == 2){ // busca linear
                printf("\nDigite o numero que deseja buscar (Busca Linear):\n ");
                scanf("%d", &numero);
                resultado = busca_linear(vetor, tamanho, numero);
                printf("%d", resultado);
                if (resultado != -1) {
                    printf("\nNumero %d foi encontrado.\n", numero);
                } else {
                    printf("\nNumero %d nao foi encontrado.\n", numero);
                }
        } else if(menu == 3){ //busca binaria
                printf("Digite o numero que deseja buscar (Busca Binaria): ");
                scanf("%d", &numero);
                resultado = busca_binaria(vetor, tamanho, numero);
                if (resultado != -1) {
                    printf("\nNumero %d foi encontrado.\n", numero);
                } else {
                    printf("\nNumero %d nao foi encontrado.\n", numero);
                }
        
////////////////Gerenciamento de alunos //////////////////

        } else if(menu == 4){ // cadastra os alunos
        alunos = cadastrar_alunos(alunos, &total_alunos);
        } else if (menu == 5) {
            if(total_alunos == 0) {
                printf("Nenhum aluno foi cadastrado ainda\n"); // permite que se faca busca somente se houver alunos
            }   else {
                buscar_aluno_linear(alunos, total_alunos); 
            }
        } else if( menu == 6){
            if(total_alunos == 0) {
                printf("Nenhum aluno foi cadastrado ainda\n");
            }   else {
                buscar_aluno_binaria(alunos, total_alunos); 
            }
        } else if( menu == 7){
            printf("Saiu");
            menu = 0;
        } else{
            printf("Opcao invalida");
        }
    }
    free(vetor); // libera a memoria alocada
    free(alunos);

    return 0;
}
