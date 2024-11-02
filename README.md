### Documentação do Código

Este projeto em C é um sistema de gerenciamento de um campeonato de futebol, que permite o cadastro de times e jogadores, gerenciamento de rodadas e partidas, registro de eventos durante os jogos, e geração de relatórios de classificação e artilharia.

#### Estruturas de Dados
- **`Jogador`**: Representa um jogador com atributos como nome, posição, idade, número da camisa, gols, cartões amarelos e vermelhos.
- **`Time`**: Representa um time, incluindo nome, estado, jogadores e estatísticas relacionadas (pontos, gols feitos e sofridos, etc.).
- **`Evento`**: Descreve eventos que acontecem durante uma partida, como gols e faltas, com registro do minuto e uma descrição.
- **`Partida`**: Representa uma partida entre dois times, armazenando os gols de cada time e eventos ocorridos.
- **`Rodada`**: Agrupa partidas realizadas em uma rodada específica.

#### Funções
1. **`cadastrarTime()`**: Cadastra um novo time, solicitando o nome e o estado. A função inicializa os contadores de estatísticas do time.
2. **`excluirTime()`**: Exclui um time com base no índice fornecido pelo usuário, realocando os times restantes para manter a ordem.
3. **`cadastrarJogador()`**: Adiciona um novo jogador a um time existente, solicitando informações como nome, posição e idade.
4. **`excluirJogador()`**: Remove um jogador de um time específico, realocando os jogadores restantes.
5. **`cadastrarRodada()`**: Cadastra uma nova rodada e associa partidas a times existentes, inicializando os dados das partidas.
6. **`adicionarEvento()`**: Adiciona um evento a uma partida específica, registrando o minuto e uma descrição. (Nota: apresenta uma limitação no funcionamento.)
7. **`registrarGol()`**: Registra um gol em uma partida, permitindo que o usuário escolha o jogador responsável e atualize a contagem de gols.
8. **`atualizarClassificacao()`**: Atualiza a pontuação dos times com base no resultado de uma partida.
9. **`relatorioClassificacao()`**: Gera um relatório da classificação geral, mostrando os pontos de cada time.
10. **`relatorioArtilharia()`**: Mostra os jogadores que marcaram gols e a quantidade de gols feitos.
11. **`relatorioEstatisticas()`**: Exibe estatísticas detalhadas de cada time, incluindo gols feitos e sofridos, e quantidade de cartões e faltas. (Nota: possui limitações em algumas versões).

#### Funcionalidades do Menu Principal
O programa é controlado por um menu interativo que permite as seguintes opções:
- **1**: Cadastrar Time
- **2**: Excluir Time
- **3**: Cadastrar Jogador
- **4**: Excluir Jogador
- **5**: Cadastrar Rodada
- **6**: Adicionar Evento a uma partida
- **7**: Registrar Gol em uma partida
- **8**: Atualizar Classificação
- **9**: Relatório de Classificação
- **10**: Relatório de Artilharia
- **11**: Relatório de Estatísticas por Time
- **0**: Sair

#### Notas e Limitações
- Algumas funções, como `adicionarEvento()` e `relatorioEstatisticas()`, podem precisar de ajustes para pleno funcionamento.
- O sistema trabalha com limites pré-definidos de times, jogadores, partidas, e eventos, conforme as constantes (`MAX_TIMES`, `MAX_JOGADORES`, etc.).

