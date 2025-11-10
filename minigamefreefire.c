/*
 * TRABALHO DE FACULDADE: Mini Game FreeFire
 * NÍVEL: NOVATO (Sistema de Inventário)
 * ARQUIVO: minigamefreefire.c
 * * Este código cria a mochila do jogador.
 */

// 1. Bibliotecas
#include <stdio.h>    // Para printf e scanf
#include <string.h>   // Para strcmp (comparar strings)
#include <stdlib.h>   // Apenas para C padrão (embora não usemos system() aqui)

// 2. Constante (Define o tamanho da mochila)
#define MAX_ITENS 10

// 3. Definição da Struct (O "molde" do item)
typedef struct {
    char nome[30];
    char tipo[20]; // Ex: arma, municao, cura
    int quantidade;
} Item;

// 4. "Variáveis Globais" (Dados do Jogo)
// O vetor (array) que é a nossa mochila
Item mochila[MAX_ITENS]; 
// Um contador para saber quantos itens temos
int totalItens = 0; 

// 5. Protótipos das Funções (Avisando o C que elas existem)
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBufferEntrada(); // Função importante para misturar scanf e fgets

/*
 * ========================================
 * FUNÇÃO PRINCIPAL (Onde o jogo roda)
 * ========================================
 */
int main() {
    int opcao; // Variável para guardar a escolha do menu

    // O 'do-while' faz o menu aparecer pelo menos uma vez
    // e repetir até o usuário digitar 0
    do {
        // --- O Menu (Usabilidade) ---
        printf("\n==================================\n");
        printf("     MOCHILA - FREEFIRE (NOVATO)\n");
        printf("==================================\n");
        printf(" Itens na Mochila: [%d de %d]\n", totalItens, MAX_ITENS);
        printf("----------------------------------\n");
        printf(" 1. Coletar Item (Inserir)\n");
        printf(" 2. Descartar Item (Remover)\n");
        printf(" 3. Olhar Mochila (Listar)\n");
        printf(" 4. Procurar Item (Buscar)\n");
        printf(" 0. Sair\n");
        printf("----------------------------------\n");
        printf("Escolha uma opcao: ");

        // Lê a opção (um número)
        scanf("%d", &opcao);

        // !! Importante !!
        // Limpa o "ENTER" que o scanf deixou para trás,
        // para o 'fgets' funcionar depois.
        limparBufferEntrada();

        // 'switch' é como um 'if' para várias opções
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente de novo.\n");
        }

        // Pausa simples para o usuário ler o resultado (se não for sair)
        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar(); // Espera o usuário pressionar ENTER
        }

    } while (opcao != 0); // Repete enquanto a opção for diferente de 0

    return 0; // Termina o programa
}

/*
 * ========================================
 * FUNÇÕES DO SISTEMA
 * ========================================
 */

// Função para Coletar (Inserir)
void inserirItem() {
    // 1. Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Nao cabe mais nada.\n");
        return; // Sai da função
    }

    // 2. Se tem espaço, pede os dados
    printf("\n--- Coletar Item ---\n");
    Item itemNovo; // Cria uma variável 'Item' temporária

    printf("Nome do item: ");
    fgets(itemNovo.nome, 30, stdin);
    itemNovo.nome[strcspn(itemNovo.nome, "\n")] = 0; // Remove o '\n' do fgets

    printf("Tipo (arma, cura, etc): ");
    fgets(itemNovo.tipo, 20, stdin);
    itemNovo.tipo[strcspn(itemNovo.tipo, "\n")] = 0; // Remove o '\n'

    printf("Quantidade: ");
    scanf("%d", &itemNovo.quantidade);
    limparBufferEntrada(); // Limpa o buffer depois do scanf

    // 3. Adiciona o item novo na mochila
    mochila[totalItens] = itemNovo;
    totalItens++; // Aumenta o contador de itens

    printf("\n[SUCESSO] '%s' guardado na mochila!\n", itemNovo.nome);
}

// Função para Descartar (Remover)
void removerItem() {
    // 1. Verifica se tem algo para remover
    if (totalItens == 0) {
        printf("\n[ERRO] Mochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Descartar Item ---\n");
    printf("Qual item quer descartar (nome exato): ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o '\n'

    int indiceEncontrado = -1; // Começa em -1 (não encontrado)

    // 2. Busca o item (Laço 'for')
    for (int i = 0; i < totalItens; i++) {
        // 'strcmp' retorna 0 se os nomes forem iguais
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i; // Guarda a posição (índice)
            break; // Para de procurar
        }
    }

    // 3. Se não encontrou...
    if (indiceEncontrado == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    } 
    // 4. Se encontrou...
    else {
        // "Puxa" todos os itens da frente para trás,
        // cobrindo o item que queremos apagar.
        for (int i = indiceEncontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        totalItens--; // Diminui o contador de itens
        printf("\n[SUCESSO] Item '%s' descartado.\n", nomeBusca);
    }
}

// Função para Olhar a Mochila (Listar)
void listarItens() {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", totalItens, MAX_ITENS);

    if (totalItens == 0) {
        printf("Mochila esta vazia.\n");
        return;
    }

    // Laço 'for' para mostrar cada item
    for (int i = 0; i < totalItens; i++) {
        printf("--------------------------\n");
        printf(" Item %d:\n", i + 1); // (i+1 para não começar do 0)
        printf("   Nome: %s\n", mochila[i].nome);
        printf("   Tipo: %s\n", mochila[i].tipo);
        printf("   Qtd : %d\n", mochila[i].quantidade);
    }
    printf("--------------------------\n");
}

// Função para Procurar (Busca Sequencial)
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[ERRO] Mochila vazia. Nada para buscar.\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\n--- Procurar Item ---\n");
    printf("Qual item quer procurar (nome exato): ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o '\n'

    int encontrado = 0; // '0' é Falso, '1' é Verdadeiro

    // Laço 'for' para busca sequencial
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[ITEM ENCONTRADO!]\n");
            printf("   Nome: %s\n", mochila[i].nome);
            printf("   Tipo: %s\n", mochila[i].tipo);
            printf("   Qtd : %d\n", mochila[i].quantidade);
            
            encontrado = 1; // Marca que encontrou
            break; // Para de procurar
        }
    }

    // Se o laço terminou e 'encontrado' ainda é 0
    if (encontrado == 0) {
        printf("\n[NAO ENCONTRADO] Item '%s' nao esta na mochila.\n", nomeBusca);
    }
}


// Função auxiliar para limpar o buffer de entrada (o "ENTER")
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}