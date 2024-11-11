/* AEP UNICESUMAR 11/11/2024
ALUNOS: GUSTAVO FUMAGALLI BANDEIRA, RENAN HOMIAK GUIMAR�ES, MIGUEL ANTONIO CRUZ CARREIRA
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define MAX_USUARIOS 100
#define TAM_SENHA 20
#define CHAVE_CRIPTOGRAFIA 5
#define ARQUIVO_USUARIOS "usuario.txt"
// vari�vel global
int i;

typedef struct {
    char usuario[50];
    char senha[TAM_SENHA];
} Usuario;

void criptografar(char senha[], int key) {
    for (i = 0; i < strlen(senha); i++) {
        senha[i] = senha[i] + key;
    }
}

void descriptografar(char senha[], int key) {
    for (i = 0; i< strlen(senha); i++) {
        senha[i] = senha[i] - key;
    }
}

void salvarUsuarios(Usuario usuarios[], int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "w");
    if (arquivo == NULL) {
        printf("	Erro ao abrir o arquivo!\n");
        return;
    }
    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%s %s\n", usuarios[i].usuario, usuarios[i].senha); 
    }
    fclose(arquivo);
}

int carregarUsuarios(Usuario usuarios[]) {
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    setlocale(LC_ALL, "Portuguese");
    if (arquivo == NULL) {
        printf("	Arquivo de usu�rios n�o encontrado - Iniciando com base de dados vazia.\n");
        return 0;
    }

    int quantidade = 0;
    while (quantidade < MAX_USUARIOS && fscanf(arquivo, "%s %s", usuarios[quantidade].usuario, usuarios[quantidade].senha) != EOF) {
        quantidade++;
    }
    fclose(arquivo);
    printf("	Usu�rios carregados com sucesso.\n");
    return quantidade;
}

void listarUsuarios(Usuario usuarios[], int quantidade) {
	system("cls");
    printf("\n	--- Lista de Usu�rios ---\n");
    for (i = 0; i < quantidade; i++) {
        printf("	Usu�rio: %s\n", usuarios[i].usuario);
    }
}

void cadastrarUsuario(Usuario usuarios[], int *quantidade) {
	system("cls");
    if (*quantidade >= MAX_USUARIOS) {
        printf("	Limite de usu�rios atingido!\n");
        return;
    }

    Usuario novoUsuario;
    printf("	Digite o nome do usu�rio: ");
    scanf("%s", novoUsuario.usuario);

    printf("	Digite a senha: ");
    scanf("%s", novoUsuario.senha);

    criptografar(novoUsuario.senha, CHAVE_CRIPTOGRAFIA);  // Criptografando antes de salvar

    usuarios[*quantidade] = novoUsuario;
    (*quantidade)++;
    salvarUsuarios(usuarios, *quantidade);
    printf("	Usu�rio cadastrado com sucesso!\n");
}

void excluirUsuario(Usuario usuarios[], int *quantidade) {
    char usuario[50];
    system("cls");
    printf("	Digite o nome do usu�rio a ser exclu�do: ");
    scanf("%s", usuario);

    int encontrado = -1;
    for (i = 0; i < *quantidade; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("	Usu�rio nao encontrado!\n");
        return;
    }

    for (i = encontrado; i < *quantidade - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    (*quantidade)--;
    salvarUsuarios(usuarios, *quantidade);
    printf("	Usu�rio excluido com sucesso!\n");
}

void alterarUsuario(Usuario usuarios[], int quantidade) {
    char usuario[50];
    system("cls");
    printf("	Digite o nome do usu�rio a ser alterado: ");
    scanf("%s", usuario);

    int encontrado = -1;
    for (i = 0; i < quantidade; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("	Usu�rio nao encontrado!!\n");
        return;
    }

    printf("	Digite a nova senha: ");
    scanf("%s", usuarios[encontrado].senha);

    criptografar(usuarios[encontrado].senha, CHAVE_CRIPTOGRAFIA);
    salvarUsuarios(usuarios, quantidade);
    printf("	Senha alterada com sucesso!!\n");
}

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int quantidadeUsuarios = carregarUsuarios(usuarios);
    int opcao;
    setlocale(LC_ALL, "Portuguese");

    do {
        printf("\n	--- Menu ---\n");
        printf("	1. Cadastrar Usu�rio\n");
        printf("	2. Listar Usu�rios\n");
        printf("	3. Excluir Usu�rio\n");
        printf("	4. Alterar Senha\n");
        printf("	5. Sair\n");
        printf("	Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario(usuarios, &quantidadeUsuarios);
                break;
            case 2:
                listarUsuarios(usuarios, quantidadeUsuarios);
                break;
            case 3:
                excluirUsuario(usuarios, &quantidadeUsuarios);
                break;
            case 4:
                alterarUsuario(usuarios, quantidadeUsuarios);
                break;
            case 5:
                printf("	Saindo...\n");
                break;
            default:
                printf("	Op��o inv�lida!\n");
        }
    } while (opcao != 5);

    return 0;
}
