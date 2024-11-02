#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOGADORES 25
#define MAX_TIMES 20
#define MAX_PARTIDAS 10
#define MAX_EVENTOS 50
#define MAX_RODADAS 38

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
    char estado[3];
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

Time times[MAX_TIMES];
int totalTimes = 0;
Rodada rodadas[MAX_RODADAS];
int totalRodadas = 0;

void cadastrarTime() {                 //funcionando
    if (totalTimes >= MAX_TIMES) return;
    printf("Nome do time: ");
    scanf(" %[^\n]%*c", times[totalTimes].nome);
    printf("Estado do time: ");
    scanf(" %[^\n]%*c", times[totalTimes].estado);
    times[totalTimes].totalJogadores = times[totalTimes].pontos = 0;
    times[totalTimes].golsFeitos = times[totalTimes].golsSofridos = 0;
    times[totalTimes].cartoesAmarelos = times[totalTimes].cartoesVermelhos = times[totalTimes].faltas = 0;
    totalTimes++;
}

void excluirTime() {                //funcionando
    int index;
    printf("Indice do time a excluir: ");
    scanf("%d", &index);
    if (index < 0 || index >= totalTimes) return;
    for (int i = index; i < totalTimes - 1; i++) times[i] = times[i + 1];
    totalTimes--;
}

void cadastrarJogador() {             //funcionando
    int timeIndex;
    if (totalTimes == 0) return;
    printf("Indice do time (0 a %d): ", totalTimes - 1);
    scanf("%d", &timeIndex);
    if (timeIndex < 0 || timeIndex >= totalTimes || times[timeIndex].totalJogadores >= MAX_JOGADORES) return;
    Jogador *j = &times[timeIndex].jogadores[times[timeIndex].totalJogadores++];
    printf("Nome do jogador: ");
    scanf(" %[^\n]%*c", j->nome);
    printf("Posicao (MEI, ATA, ZAG, LAT, GOL): ");
    scanf(" %[^\n]%*c", j->posicao);
    printf("Idade: ");
    scanf("%d", &j->idade);
    printf("Numero da camisa: ");
    scanf("%d", &j->numeroCamisa);
    j->gols = j->cartoesAmarelos = j->cartoesVermelhos = 0;
}

void excluirJogador() {             //funcionando
    int timeIndex, jogadorIndex;
    printf("Indice do time: ");
    scanf("%d", &timeIndex);
    printf("Indice do jogador: ");
    scanf("%d", &jogadorIndex);
    if (timeIndex < 0 || timeIndex >= totalTimes || jogadorIndex < 0 || jogadorIndex >= times[timeIndex].totalJogadores) return;
    for (int i = jogadorIndex; i < times[timeIndex].totalJogadores - 1; i++) 
        times[timeIndex].jogadores[i] = times[timeIndex].jogadores[i + 1];
    times[timeIndex].totalJogadores--;
}

void cadastrarRodada() {                //funcionando parcialmente
    if (totalRodadas >= MAX_RODADAS) return;
    Rodada *novaRodada = &rodadas[totalRodadas++];
    printf("Numero de partidas: ");
    scanf("%d", &novaRodada->totalPartidas);
    for (int i = 0; i < novaRodada->totalPartidas; i++) {
        int time1Index, time2Index;
        printf("Partida %d - Time 1: ", i + 1);
        scanf("%d", &time1Index);
        printf("Time 2: ");
        scanf("%d", &time2Index);
        if (time1Index < 0 || time1Index >= totalTimes || time2Index < 0 || time2Index >= totalTimes || time1Index == time2Index) continue;
        Partida *p = &novaRodada->partidas[i];
        p->time1 = &times[time1Index];
        p->time2 = &times[time2Index];
        p->golsTime1 = p->golsTime2 = p->totalEventos = 0;
    }
}

void adicionarEvento(Partida *partida) {       // n funciona
    if (partida->totalEventos >= MAX_EVENTOS) return;
    Evento *evento = &partida->eventos[partida->totalEventos++];
    printf("Minuto do evento: ");
    scanf("%d", &evento->minuto);
    printf("Descricao: ");
    scanf(" %[^\n]%*c", evento->descricao);
}

void registrarGol(Partida *partida) {    //funcionando
    int jogadorIndex;
    Jogador *jogador;
    printf("Escolha o jogador que marcou o gol:\n");

    // Listar jogadores do time 1
    printf("Jogadores do time 1:\n");
    for (int i = 0; i < partida->time1->totalJogadores; i++) {
        printf("%d. %s\n", i, partida->time1->jogadores[i].nome);
    }

    // Listar jogadores do time 2
    printf("Jogadores do time 2:\n");
    for (int i = 0; i < partida->time2->totalJogadores; i++) {
        printf("%d. %s\n", i + partida->time1->totalJogadores, partida->time2->jogadores[i].nome);
    }

    // Escolher jogador
    scanf("%d", &jogadorIndex);

    // Verificar se o jogador pertence ao time 1 ou time 2
    if (jogadorIndex < partida->time1->totalJogadores) {
        jogador = &partida->time1->jogadores[jogadorIndex];
        partida->golsTime1++;
    } else {
        jogadorIndex -= partida->time1->totalJogadores;
        jogador = &partida->time2->jogadores[jogadorIndex];
        partida->golsTime2++;
    }

    // Atualizar gols do jogador
    jogador->gols++;
    printf("Gol registrado para %s do time %s\n", jogador->nome, jogadorIndex < partida->time1->totalJogadores ? partida->time1->nome : partida->time2->nome);
}

void atualizarClassificacao(Partida *partida) {        //funcionando parcialmente
    if (partida->golsTime1 > partida->golsTime2) partida->time1->pontos += 3;
    else if (partida->golsTime1 < partida->golsTime2) partida->time2->pontos += 3;
    else {
        partida->time1->pontos++;
        partida->time2->pontos++;
    }
}

void relatorioClassificacao() {            //funcionando 
    printf("\n--- Classificacao Geral ---\n");
    for (int i = 0; i < totalTimes; i++) {
        printf("Time: %s, Pontos: %d\n", times[i].nome, times[i].pontos);
    }
}

void relatorioArtilharia() {              //funcionando
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

void relatorioEstatisticas() {     //n ta funcionando
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
        printf("\n1. Cadastrar Time\n2. Excluir Time\n3. Cadastrar Jogador\n4. Excluir Jogador\n5. Cadastrar Rodada\n");
        printf("6. Adicionar Evento\n7. Registrar Gol\n8. Atualizar Classificacao\n9. Relatorio Classificacao\n");
        printf("10. Relatorio Artilharia\n11. Relatorio Estatisticas\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarTime(); break;
            case 2: excluirTime(); break;
            case 3: cadastrarJogador(); break;
            case 4: excluirJogador(); break;
            case 5: cadastrarRodada(); break;
            case 6: if (totalRodadas > 0) adicionarEvento(&rodadas[totalRodadas - 1].partidas[0]); break;
            case 7:
                if (totalRodadas > 0) {
                    int rodadaIndex, partidaIndex;
                    printf("Selecione a rodada (0 a %d): ", totalRodadas - 1);
                    scanf("%d", &rodadaIndex);
                    if (rodadaIndex < 0 || rodadaIndex >= totalRodadas) break;

                    printf("Selecione a partida (0 a %d): ", rodadas[rodadaIndex].totalPartidas - 1);
                    scanf("%d", &partidaIndex);
                    if (partidaIndex < 0 || partidaIndex >= rodadas[rodadaIndex].totalPartidas) break;

                    registrarGol(&rodadas[rodadaIndex].partidas[partidaIndex]);
                }
                break;
            case 8: if (totalRodadas > 0) atualizarClassificacao(&rodadas[totalRodadas - 1].partidas[0]); break;
            case 9: relatorioClassificacao(); break;
            case 10: relatorioArtilharia(); break;
            case 11: relatorioEstatisticas(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(opcao != 0);

    return 0;
}