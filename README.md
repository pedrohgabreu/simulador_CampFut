# Controle de Campeonato de Futebol

Este projeto é um sistema de controle de campeonatos de futebol, permitindo o cadastro de times, jogadores, rodadas e partidas, além de registrar eventos de cada partida e gerar relatórios diversos.

## Funcionalidades

- **Cadastro de Times**: Permite o registro de times com nome e estado.
- **Cadastro de Jogadores**: Cada time pode ter até 25 jogadores, com informações como nome, posição, idade e número da camisa.
- **Cadastro de Rodadas**: Possibilita a inclusão de rodadas com múltiplas partidas entre times.
- **Cadastro de Partidas**: Permite o registro de partidas entre os times cadastrados.
- **Registro de Eventos**: Inclui a possibilidade de adicionar eventos durante as partidas, como gols, cartões e faltas.
- **Classificação Geral**: Gera um relatório com a classificação atual dos times, baseado nos resultados das partidas.
- **Artilharia**: Gera um relatório com a lista de jogadores e a quantidade de gols marcados.
- **Estatísticas por Time**: Apresenta estatísticas detalhadas para cada time, como gols feitos, gols sofridos, cartões e faltas.

## Estruturas de Dados

O sistema utiliza as seguintes estruturas de dados:

- `Jogador`: Representa um jogador de futebol, contendo informações como nome, posição, idade, número da camisa e estatísticas (gols, cartões).
- `Time`: Representa um time de futebol, contendo informações como nome, estado, jogadores relacionados e estatísticas (pontos, gols feitos e sofridos).
- `Evento`: Representa um evento durante a partida, como gols e cartões.
- `Partida`: Representa uma partida entre dois times, contendo informações sobre os times, gols e eventos.
- `Rodada`: Agrupa partidas em uma rodada específica.

