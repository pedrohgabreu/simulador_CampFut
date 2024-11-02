# Sistema de Gerenciamento de Times e Partidas de Futebol

Este projeto em C é um sistema que gerencia times de futebol, jogadores, partidas, e estatísticas. Com ele, é possível cadastrar e excluir times e jogadores, registrar partidas e eventos, gerar relatórios de classificação, artilharia e estatísticas detalhadas de cada time.

## Funcionalidades

1. **Cadastrar Time**
   - Permite o cadastro de times, incluindo o nome e o estado.
2. **Excluir Time**
   - Remove um time cadastrado do sistema.
3. **Cadastrar Jogador**
   - Adiciona jogadores aos times, com informações detalhadas como nome, posição, idade e número da camisa.
4. **Excluir Jogador**
   - Remove um jogador específico de um time.
5. **Cadastrar Rodada**
   - Registra uma nova rodada com uma quantidade específica de partidas e os times envolvidos.
6. **Adicionar Evento**
   - Permite a adição de eventos como cartões e faltas durante uma partida específica.
7. **Registrar Gol**
   - Registra gols feitos por jogadores em uma partida.
8. **Atualizar Classificação**
   - Atualiza a pontuação dos times com base nos resultados das partidas.
9. **Relatório de Classificação**
   - Gera um relatório dos times ordenados por pontos, do maior para o menor.
10. **Relatório de Artilharia**
    - Exibe os jogadores com gols registrados, ordenados pela quantidade de gols.
11. **Relatório de Estatísticas**
    - Mostra estatísticas detalhadas de cada time, incluindo gols feitos, sofridos, cartões e faltas.

## Estruturas de Dados

### Estrutura `Jogador`
Representa os jogadores de um time.
```
typedef struct {
    char nome[50];
    char posicao[3];
    int idade;
    int numeroCamisa;
    int gols;
    int cartoesAmarelos;
    int cartoesVermelhos;
} Jogador;
```
### Estrutura `Time`

Representa um time de futebol.
```
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
```
### Estrutura `Evento`

Representa um evento ocorrido durante uma partida.
```
typedef struct {
    int minuto;
    char descricao[100];
} Evento;
```

### Estrutura `Partida`

Contém informações sobre uma partida entre dois times.
```
typedef struct {
    Time *time1;
    Time *time2;
    int golsTime1;
    int golsTime2;
    Evento eventos[MAX_EVENTOS];
    int totalEventos;
} Partida;
```
### Estrutura `Rodada`

Representa uma rodada de partidas.
```
typedef struct {
    Partida partidas[MAX_PARTIDAS];
    int totalPartidas;
} Rodada;
```

## Instruções de Compilação e Execução
Compilação:

Para compilar o código, use o gcc:

`gcc -o sistema_futebol sistema_futebol.c`

Execução

Para executar o programa, digite:

`./sistema_futebol`

## Instruções de Uso

Ao executar o programa, você verá um menu com opções numeradas:

1. Cadastrar Time
2. Excluir Time
3. Cadastrar Jogador
4. Excluir Jogador
5. Cadastrar Rodada
6. Adicionar Evento
7. Registrar Gol
8. Atualizar Classificacao
9. Relatorio Classificacao
10. Relatorio Artilharia
11. Relatorio Estatisticas
0. Sair
Escolha: 

Selecione a opção desejada digitando o número correspondente e siga as instruções na tela.
Observações Importantes

- A função adicionarEvento() deve ser usada com cautela para evitar que eventos inválidos sejam adicionados.
- atualizarClassificacao() deve ser chamada apenas uma vez por partida para evitar atualizações duplicadas.
- A função relatorioEstatisticas() exibe as estatísticas detalhadas de cada time.

Este projeto é distribuído sob a licença MIT.

Autor: Pedro Henrique Abreu
