# Descrição do Programa
Este algoritmo foi desenvolvido para encontrar o inventário mais otimizado ao sair de uma Dungeon (DG) onde são encontrados itens aleatórios com diferentes tamanhos, pesos e valores. O objetivo é maximizar o lucro, levando em conta as restrições de peso e espaço da mochila. Utilizando técnicas de algoritmo genético, busquei identificar as soluções mais eficientes para esse desafio, criando um sistema capaz de encontrar as melhores combinações de itens para alcançar o máximo benefício dentro das limitações impostas.

Este algoritmo implementa um algoritmo genético para resolver o problema da "Mochila Compartimentada". Neste problema, você tem uma série de itens com diferentes valores, pesos, tamanhos e raridades.  O objetivo é preencher uma mochila dividida em compartimentos de forma a maximizar o valor total dos itens que podem ser colocados na mochila, respeitando as restrições de peso e tamanho de cada compartimento.

O algoritmo começa lendo uma matriz de itens de um arquivo e cria uma nova tabela com informações adicionais sobre os itens. Em seguida, simula a descoberta de itens em uma masmorra e gera soluções iniciais aleatórias para acomodar esses itens na mochila.

A função principal do algoritmo é a otimização das soluções por meio de um processo de evolução. Isso é feito em várias etapas:

- Inicialização da População: Criação de uma população inicial de soluções candidatas (espólios) de forma aleatória.
- Avaliação do Fitness: Cada solução é avaliada com base na sua capacidade de atender às restrições da mochila e ao valor total dos itens.
- Seleção: Seleção dos espólios mais promissores para reprodução com base em sua aptidão (valor total dos itens).
- Crossover: Cruzamento entre os espólios selecionados para gerar novas soluções (filhos).
- Mutação: Aplicação de mutação nos espólios para introduzir variações na população.
- Substituição: Atualização da população com os novos espólios gerados e preservação dos melhores indivíduos (elite) de gerações anteriores.

O algoritmo segue esse ciclo por várias gerações, buscando melhorar continuamente as soluções encontradas. Ao final, apresenta as melhores soluções obtidas para resolver o problema da mochila compartimentada, exibindo o valor total, peso e tamanho das soluções encontradas.
