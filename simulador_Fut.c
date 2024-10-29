#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOGADORES 25
#define MAX_TIMES 20
#define MAX_PARTIDAS 10
#define MAX_EVENTOS 50
#define MAX_RODADAS 38

// Estruturas principais
typedef struct {
    char nome[50];
    char posicao[3];
    int idade;
    int numeroCamisa;
    int gols;
    int cartoesAmarelos;
    int cartoesVermelhos;
} Jogador;

typedef struct {
    char nome[50];
    char estado[2];
    Jogador jogadores[MAX_JOGADORES];
    int totalJogadores;
    int pontos;
    int golsFeitos;
    int golsSofridos;
    int cartoesAmarelos;
    int cartoesVermelhos;
    int faltas;
} Time;

typedef struct {
    int minuto;
    char descricao[100];
} Evento;

typedef struct {
    Time *time1;
    Time *time2;
    int golsTime1;
    int golsTime2;
    Evento eventos[MAX_EVENTOS];
    int totalEventos;
} Partida;

typedef struct {
    Partida partidas[MAX_PARTIDAS];
    int totalPartidas;
} Rodada;

// Variaveis globais
Time times[MAX_TIMES];
int totalTimes = 0;
Rodada rodadas[MAX_RODADAS];
int totalRodadas = 0;

// Funcoes auxiliares
void cadastrarTime() {
    if (totalTimes >= MAX_TIMES) {
        printf("Limite de times alcancado.\n");
        return;
    }
    printf("Digite o nome do time: ");
    scanf(" %[^\n]%*c", times[totalTimes].nome);
    printf("Digite o estado do time (Exemplo: RS, RJ, SP.): ");
    scanf(" %[^\n]%*c", times[totalTimes].estado);
    times[totalTimes].totalJogadores = 0;
    times[totalTimes].pontos = 0;
    times[totalTimes].golsFeitos = 0;
    times[totalTimes].golsSofridos = 0;
    times[totalTimes].cartoesAmarelos = 0;
    times[totalTimes].cartoesVermelhos = 0;
    times[totalTimes].faltas = 0;
    totalTimes++;
}

void cadastrarJogador() {
    int timeIndex;
    if (totalTimes == 0) {
        printf("Nenhum time cadastrado. Cadastre um time primeiro.\n");
        return;
    }
    printf("Escolha o indice do time (0 a %d): ", totalTimes - 1);
    scanf("%d", &timeIndex);
    if (timeIndex < 0 || timeIndex >= totalTimes) {
        printf("Indice de time invalido.\n");
        return;
    }
    if (times[timeIndex].totalJogadores >= MAX_JOGADORES) {
        printf("Limite de jogadores para o time %s alcancado.\n", times[timeIndex].nome);
        return;
    }

    Jogador *jogador = &times[timeIndex].jogadores[times[timeIndex].totalJogadores++];
    printf("Digite o nome do jogador: ");
    scanf(" %[^\n]%*c", jogador->nome);
    printf("Digite a posicao do jogador (Exemplo: MEI, ATA, ZAG): ");
    scanf(" %[^\n]%*c", jogador->posicao);
    printf("Digite a idade do jogador: ");
    scanf("%d", &jogador->idade);
    printf("Digite o numero da camisa do jogador: ");
    scanf("%d", &jogador->numeroCamisa);
    jogador->gols = jogador->cartoesAmarelos = jogador->cartoesVermelhos = 0;

}

void cadastrarRodada() {
    if (totalRodadas >= MAX_RODADAS) {
        printf("Limite de rodadas alcancado.\n");
        return;
    }
    Rodada *novaRodada = &rodadas[totalRodadas];
    novaRodada->totalPartidas = 0;  // Inicializa a rodada sem partidas

    int numPartidas;
    printf("Digite o numero de partidas para esta rodada: ");
    scanf("%d", &numPartidas);

    if (numPartidas > MAX_PARTIDAS) {
        printf("Limite de partidas por rodada excedido. Permitido no maximo %d.\n", MAX_PARTIDAS);
        return;
    }

    // Cadastra cada partida dentro da rodada
    for (int i = 0; i < numPartidas; i++) {
        int time1Index, time2Index;

        printf("Partida %d\n", i + 1);
        printf("Escolha o indice do primeiro time (0 a %d): ", totalTimes - 1);
        scanf("%d", &time1Index);
        printf("Escolha o indice do segundo time (0 a %d): ", totalTimes - 1);
        scanf("%d", &time2Index);

        if (time1Index < 0 || time1Index >= totalTimes || time2Index < 0 || time2Index >= totalTimes || time1Index == time2Index) {
            printf("Indices de times invalidos ou repetidos. Tente novamente.\n");
            i--; // repete a partida atual
            continue;
        }

        // Define a partida na rodada atual
        Partida *partida = &novaRodada->partidas[novaRodada->totalPartidas++];
        partida->time1 = &times[time1Index];
        partida->time2 = &times[time2Index];
        partida->golsTime1 = 0;
        partida->golsTime2 = 0;
        partida->totalEventos = 0;
    }

    totalRodadas++;
    printf("Rodada cadastrada com sucesso.\n");
}


void adicionarEvento(Partida *partida) {
    if (partida->totalEventos >= MAX_EVENTOS) return;
    Evento *evento = &partida->eventos[partida->totalEventos++];
    printf("Digite o minuto do evento: ");
    scanf("%d", &evento->minuto);
    printf("Digite a descricao do evento (gol, falta, cartao, etc.): ");
    scanf(" %[^\n]%*c", evento->descricao);
}

void cadastrarPartida() {
    if (totalRodadas >= MAX_RODADAS) {
        printf("Limite de rodadas alcancado.\n");
        return;
    }

    int time1Index, time2Index;
    printf("Escolha o indice do primeiro time (0 a %d): ", totalTimes - 1);
    scanf("%d", &time1Index);
    printf("Escolha o indice do segundo time (0 a %d): ", totalTimes - 1);
    scanf("%d", &time2Index);

    if (time1Index < 0 || time1Index >= totalTimes || time2Index < 0 || time2Index >= totalTimes || time1Index == time2Index) {
        printf("Indices de time invalidos ou repetidos.\n");
        return;
    }

    Partida *partida = &rodadas[totalRodadas].partidas[rodadas[totalRodadas].totalPartidas++];
    partida->time1 = &times[time1Index];
    partida->time2 = &times[time2Index];
    partida->golsTime1 = partida->golsTime2 = 0;
    partida->totalEventos = 0;
}

void registrarGol(Partida *partida, Time *time) {
    if (time == partida->time1) {
        partida->golsTime1++;
        time->golsFeitos++;
        partida->time2->golsSofridos++;
    } else {
        partida->golsTime2++;
        time->golsFeitos++;
        partida->time1->golsSofridos++;
    }
}

void atualizarClassificacao(Partida *partida) {
    if (partida->golsTime1 > partida->golsTime2) {
        partida->time1->pontos += 3;
    } else if (partida->golsTime1 < partida->golsTime2) {
        partida->time2->pontos += 3;
    } else {
        partida->time1->pontos += 1;
        partida->time2->pontos += 1;
    }
}

void relatorioClassificacao() {
    printf("\n--- Classificacao Geral ---\n");
    for (int i = 0; i < totalTimes; i++) {
        printf("Time: %s, Pontos: %d\n", times[i].nome, times[i].pontos);
    }
}

void relatorioArtilharia() {
    printf("\n--- Artilharia ---\n");
    for (int i = 0; i < totalTimes; i++) {
        for (int j = 0; j < times[i].totalJogadores; j++) {
            Jogador jogador = times[i].jogadores[j];
            if (jogador.gols > 0) {
                printf("Jogador: %s, Gols: %d\n", jogador.nome, jogador.gols);
            }
        }
    }
}

void relatorioEstatisticas() {
    printf("\n--- Estatisticas por Time ---\n");
    for (int i = 0; i < totalTimes; i++) {
        Time *time = &times[i];
        printf("Time: %s, Gols Feitos: %d, Gols Sofridos: %d, Cartoes Amarelos: %d, Cartoes Vermelhos: %d, Faltas: %d\n",
               time->nome, time->golsFeitos, time->golsSofridos, time->cartoesAmarelos, time->cartoesVermelhos, time->faltas);
    }
}

int main() {
    int opcao;
    do {
        printf("\n1. Cadastrar Time\n2. Cadastrar Jogador\n3. Cadastrar Partida\n4. Cadastrar Rodada\n");
        printf("5. Adicionar Evento\n6. Registrar Gol\n7. Atualizar Classificacao\n8. Relatorio Classificacao\n");
        printf("9. Relatorio Artilharia\n10. Relatorio Estatisticas\n0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarTime(); break;
            case 2: cadastrarJogador(); break;
            case 3: cadastrarPartida(); break;
            case 4: cadastrarRodada(); break; // Chama a função para cadastrar rodada
            case 5:
                if (totalRodadas > 0) {
                    adicionarEvento(&rodadas[totalRodadas - 1].partidas[rodadas[totalRodadas - 1].totalPartidas - 1]);
                }
                break;
            case 6:
                if (totalRodadas > 0) {
                    registrarGol(&rodadas[totalRodadas - 1].partidas[rodadas[totalRodadas - 1].totalPartidas - 1], rodadas[totalRodadas - 1].partidas[rodadas[totalRodadas - 1].totalPartidas - 1].time1);
                }
                break;
            case 7: atualizarClassificacao(&rodadas[totalRodadas - 1].partidas[rodadas[totalRodadas - 1].totalPartidas - 1]); break;
            case 8: relatorioClassificacao(); break;
            case 9: relatorioArtilharia(); break;
            case 10: relatorioEstatisticas(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(opcao != 0);

    return 0;
}
