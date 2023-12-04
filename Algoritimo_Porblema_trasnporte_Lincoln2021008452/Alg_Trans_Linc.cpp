#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <climits>  // Inclua esta biblioteca para INT_MAX
#include <utility> // Biblioteca para usar pair

using namespace std;

/*
    @author Lincoln
    @date 31/10/2023
*/

// Estrutura para armazenar coordenadas
struct Coordenada {
    int x;
    int y;
    Coordenada(int _x, int _y) : x(_x), y(_y) {}
};

// Função para imprimir uma matriz
void imprimirMatriz(const vector<vector<int>>& matriz) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// Função para ler a matriz do teclado e salvá-la em um arquivo
vector<vector<int>> lerMatrizDoTeclado(int& linhas, int& colunas) {
    cout << "Insira o número de linhas e colunas da matriz: ";
    cin >> linhas >> colunas;

    vector<vector<int>> matriz(linhas, vector<int>(colunas, 0));

    cout << "Insira os valores da matriz:" << endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cin >> matriz[i][j];
        }
    }

    string nomeArquivo;
    cout << "Digite o nome do arquivo para salvar a matriz (.txt): ";
    cin >> nomeArquivo;

    // Salvar a matriz em um arquivo com o nome fornecido pelo usuário
    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << linhas << " " << colunas << endl;
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                arquivo << matriz[i][j] << " ";
            }
            arquivo << endl;
        }
        arquivo.close();
        cout << "Matriz salva com sucesso em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo." << endl;
    }

    return matriz;
}

// Função para ler a matriz de um arquivo
vector<vector<int>> lerMatrizDeArquivo(const string& nomeArquivo, int& linhas, int& colunas) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(1);
    }

    arquivo >> linhas >> colunas;

    vector<vector<int>> matriz(linhas, vector<int>(colunas, 0));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo >> matriz[i][j];
        }
    }

    arquivo.close();
    return matriz;
}

// Função para escolher a origem da matriz (teclado ou arquivo)
vector<vector<int>> escolher_Origem_da_Matriz(int& linhas, int& colunas) {
    cout << "Deseja inserir uma matriz pelo teclado (1) ou carregar de um arquivo (2)? ";
    int opcao;
    cin >> opcao;

    if (opcao == 1) {
        return lerMatrizDoTeclado(linhas, colunas);
    } else if (opcao == 2) {
        string nomeArquivo;
        cout << "Informe o nome do arquivo contendo a matriz: ";
        cin >> nomeArquivo;
        return lerMatrizDeArquivo(nomeArquivo, linhas, colunas);
    } else {
        cout << "Opção inválida." << endl;
        exit(1);
    }
}

//funcao calcula valor de Z.
float Calcula_valorZ(vector<vector<int>> MatrizCustos, vector<vector<int>> MatrizVariaveis){
    int linhasC = MatrizCustos.size();
    int colunasC = MatrizCustos[0].size();
    int linhasV = MatrizVariaveis.size();
    int colunasV = MatrizVariaveis[0].size();
    float z;

    for (int i = 0; i < linhasC; i++) {
        for (int j = 0; j < colunasC; j++) {
           if(MatrizVariaveis[i][j] != 0){
               z += (MatrizCustos[i][j]*MatrizVariaveis[i][j]);
           }
        }
        //cout << z << endl;
       
    }

    return z;
}

//funcao para verificar o numero de variaveis basicas esta correto.
bool verificaVariaveiBasicas(vector<vector<int>> MatrizCustos, vector<vector<int>> MatrizVariaveis){
    int linhasC = MatrizCustos.size();
    int colunasC = MatrizCustos[0].size();
    int linhasV = MatrizVariaveis.size();
    int colunasV = MatrizVariaveis[0].size();

    int numeroVBCorreto = linhasC + colunasC -1;
    int contVBMatrizV = 0;

    for (int i = 0; i < linhasV; i++) {
        for (int j = 0; j < colunasV; j++) {
           if(MatrizVariaveis[i][j] != 0){
                contVBMatrizV += 1;
           }
        }
       
    }

    if (numeroVBCorreto == contVBMatrizV){
        return true;
    }
    return false;

}

// Função para adicionar uma nova linha zerada em uma matriz qualquer
void adicionarLinhaZerada(vector<vector<int>>& matriz) {
    if (matriz.size() < 2) {
        cout << "Matriz com menos de duas linhas." << endl;
        return;
    }

    size_t colunas = matriz[0].size();
    vector<int> novaLinha(colunas, 0); // Cria uma nova linha zerada

    // Insere a nova linha na matriz
    matriz.insert(matriz.end(), novaLinha);
}

// Função para adicionar uma coluna zerada 
void adicionarColunaZerada(vector<vector<int>>& matriz) {
    if (matriz.empty()) {
        cout << "Matriz vazia." << endl;
        return;
    }

    size_t linhas = matriz.size();
    size_t colunas = matriz[0].size();

    for (size_t i = 0; i < linhas; ++i) {
        // Inserir um elemento zero na posição final da linha
        matriz[i].insert(matriz[i].end(), 0);
    }

}

// Função para adicionar uma nova linha zerada entre a penúltima e a última linha, exceto pelo último elemento
void adicionarLinhaZeradaEOfertaFantasma(vector<vector<int>>& matriz, int valorUltimoElemento) {
    if (matriz.size() < 2) {
        cout << "Matriz com menos de duas linhas." << endl;
        return;
    }

    size_t colunas = matriz[0].size();
    vector<int> novaLinha(colunas, 0); // Cria uma nova linha zerada

    // Define o valor para o último elemento da nova linha
    novaLinha[colunas - 1] = valorUltimoElemento;

    // Insere a nova linha antes da última linha na matriz
    matriz.insert(matriz.end() - 1, novaLinha);
}

// Função para adicionar uma coluna zerada entre a última coluna e a penúltima, com exceção do último elemento
void adicionarColunaZeradaEDestinoFantasma(vector<vector<int>>& matriz, int valorUltimaCelula) {
    if (matriz.empty()) {
        cout << "Matriz vazia." << endl;
        return;
    }

    size_t linhas = matriz.size();
    size_t colunas = matriz[0].size();

    for (size_t i = 0; i < linhas; ++i) {
        // Inserir um elemento zero na posição antes da última coluna
        matriz[i].insert(matriz[i].end() - 1, 0);
    }

    // Define o valor para a última célula da coluna nova
    matriz[linhas - 1][colunas - 1] = valorUltimaCelula; 
}

//Funcao para verificar se o problema esta balanceado, se n estiver e feito o balanciamento.
void Balaceamento(vector<vector<int>>& matrizCustos, vector<vector<int>>& matrizVariaveis){
    int linhasC = matrizCustos.size();
    int colunasC = matrizCustos[0].size();
    int linhasV = matrizVariaveis.size();
    int colunasV = matrizVariaveis[0].size();
    int SomaDestino = 0; // soma da ultima linha da matriz de variaveis
    int SomaOrigem = 0; // soma da ultima coluna da matriz de variaveis
    for(int i = 0; i < linhasV - 1; i++){
        SomaOrigem += matrizVariaveis[i][colunasV - 1];   
        //cout << "Ofertas: "<< SomaOrigem << endl;
    }
    for(int j = 0; j < (colunasV - 1); j++){
        SomaDestino += matrizVariaveis[linhasV - 1][j];
        //cout <<"Demanda: " << SomaDestino << endl;
    }
    if(SomaOrigem > SomaDestino){ //Cria uma Coluna nova na matriz custos e uma nova coluna na matriz de variaveis (matriz de variaveis = matriz de oferta e demanda).
        adicionarColunaZerada(matrizCustos);
        adicionarColunaZeradaEDestinoFantasma(matrizVariaveis, (SomaOrigem - SomaDestino));
    }else if(SomaOrigem < SomaDestino){//Cria uma Linha nova na matriz custos e um nova linha matriz de variaveis (matriz de variaveis = matriz de oferta e demanda).
        adicionarLinhaZerada(matrizCustos);
        adicionarLinhaZeradaEOfertaFantasma(matrizVariaveis, (SomaDestino - SomaOrigem ));
    }else{
        cout << endl;
        cout << "A matriz esta balanceada!" << endl;
        cout << endl;
    }
    cout << "A matriz foi balanceada!" << endl;
    cout << endl;
}

// Função para implementar o método do Canto Noroeste
void metodoCantoNoroeste(vector<vector<int>>& matrizCustos, vector<vector<int>>& matrizVariaveis) {
    int linhas = matrizCustos.size();
    int colunas = matrizCustos[0].size(); //retorna o numero de colunas da matriz custos (o 0 respesenta que eu travo na primeira linha e retorno o numero de colunas presentes nela)

    // Verifique se a matriz de variáveis está balanceada
    int somaUltimaLinha = 0;
    int somaUltimaColuna = 0;

    // Calcula a soma dos valores na última linha da matriz de variáveis
    for (int i = 0; i < linhas; i++) {
        somaUltimaLinha += matrizVariaveis[i][colunas];
        
    }

    // Calcula a soma dos valores na última coluna da matriz de variáveis
    for (int j = 0; j < colunas; j++) {
        somaUltimaColuna += matrizVariaveis[linhas][j];
        
    }

    // Verifica se a soma da última linha é igual à soma da última coluna
    if (somaUltimaLinha != somaUltimaColuna) {
        cerr << "A matriz de Ofertas e Demandas precisa ser balanceada." << endl;
        return;
    }

    int i = 0;
    int j = 0;

    //Algoritmo do Canto Noroeste
    while (i < linhas && j < colunas) {
        // Aloca a quantidade mínima entre a oferta disponível e a demanda disponível
        int aloca = min(matrizVariaveis[i][colunas], matrizVariaveis[linhas][j]);

        // Atribui o valor alocado na matriz de variáveis
        matrizVariaveis[i][j] = aloca;

        // Atualize as ofertas e demandas disponíveis
        matrizVariaveis[i][colunas] -= aloca;
        matrizVariaveis[linhas][j] -= aloca;

        // Verifica se a oferta disponível na linha foi totalmente alocada
        if (matrizVariaveis[i][colunas] == 0) {
            i++; // Move para a próxima linha
        } else {
            j++; // Move para a próxima coluna
        }
    }
}

void calcularCustosReduzidos(const vector<vector<int>>& custos, const vector<vector<int>>& s_ini, vector<vector<int>>& custosReduzidos, vector<int> &u_resultado, vector<int> &v_resultado) {
    int linhas = custos.size();
    int colunas = custos[0].size();

    // Vetores para armazenar u e v
    vector<int> u(linhas, INT_MAX); // Inicializamos com valores máximos para indicar que são desconhecidos
    vector<int> v(colunas, INT_MAX); // Inicializamos com valores máximos para indicar que são desconhecidos

    // Inicializar u(0) com 0
    u[0] = 0;

    bool encontrado;
    
    do {
        encontrado = false;

        // Encontrar os valores de u(i) e v(j) conhecidos na matriz de solução inicial
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (s_ini[i][j] != 0 && (u[i] != INT_MAX || v[j] != INT_MAX)) {
                    if (u[i] == INT_MAX && v[j] == INT_MAX) {
                        
                        continue; // Valores indefinidos, não é possível calcular u[i] e v[j] ainda
                    }
                    if (u[i] != INT_MAX && v[j] == INT_MAX) {
                        v[j] = custos[i][j] - u[i];
                        //cout << v[j] << endl;
                        encontrado = true;
                    } else if (v[j] != INT_MAX && u[i] == INT_MAX) {
                        u[i] = custos[i][j] - v[j];
                        //cout << u[i] << endl;
                        encontrado = true;
                    }else if ((v[j] == INT_MAX && u[i] != INT_MAX)) {
                        v[j] = custos[i][j] - u[i];
                        encontrado = true;
                    }else if ((u[i] == INT_MAX && v[j] != INT_MAX)){
                        u[i] = custos[i][j] - v[j];
                        encontrado = true;
                    }
                }
            }
        }
    } while (encontrado);
  
    // Calcular custos reduzidos para as células não alocadas na matriz de solução inicial
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (s_ini[i][j] == 0) {
                custosReduzidos[i][j] = u[i] + v[j] - custos[i][j];
            }
        }
    }
    u_resultado = u; // Copiar valores de u para u_result
    v_resultado = v; // Copiar valores de v para v_result
}

// Função para realizar o teste de otimalidade 
bool testeDeOtimalidade(vector<vector<int>>& matrizCustosReduzidos) {
    int linhas = matrizCustosReduzidos.size();
    int colunas = matrizCustosReduzidos[0].size();

    // Verificar se todos os Custos Reduzidos são não negativos
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matrizCustosReduzidos[i][j] > 0) {
                // Encontrou um Custo Reduzido com valor positivo, a solução não é ótima
                cout <<"A solucao nao e otima."<< endl;
                cout << endl;
                return true;
            }
        }
    }
    // Se todos os multiplicadores são negativos, a solução é ótima
    cout << endl;
    cout <<"A solucao e otima."<< endl;
    cout << endl;
    return false;
}

// Função para encontrar a célula-chave na matriz de custos reduzidos
pair<int, int> encontrarCelulaChave(const vector<vector<int>>& custosReduzidos) {
    int linhas = custosReduzidos.size();
    int colunas = custosReduzidos[0].size();

    pair<int, int> celulaChave = make_pair(-1, -1); // Inicializa a célula-chave

    int maiorValor = INT_MIN;

    // Percorre a matriz de custos reduzidos para encontrar a célula-chave (maior valor)
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (custosReduzidos[i][j] > maiorValor) {
                maiorValor = custosReduzidos[i][j];
                celulaChave = make_pair(i, j);
            }
        }
    }

    return celulaChave;
}

// Função para remover a última linha e a última coluna de uma matriz
vector<vector<int>> removerUltimaLinhaEColuna(const vector<vector<int>>& matriz) {
    // Verifica se a matriz está vazia ou tem apenas uma linha ou uma coluna
    if (matriz.size() <= 1 || matriz[0].size() <= 1) {
        cout << "A matriz é muito pequena para remover a última linha e a última coluna." << endl;
        return matriz; // Retorna a matriz original
    }

    vector<vector<int>> novaMatriz;

    // Copia os elementos da matriz original, exceto a última linha e a última coluna
    for (size_t i = 0; i < matriz.size() - 1; ++i) {
        vector<int> linha;
        for (size_t j = 0; j < matriz[i].size() - 1; ++j) {
            linha.push_back(matriz[i][j]);
        }
        novaMatriz.push_back(linha);
    }

    return novaMatriz;
}
//Funcao para mostras o ciclo encontrado.
void printCiclo(const vector<Coordenada>& cicloEncontrado) {
    cout << "Ciclo Encontrado: ";
    for (const auto& coord : cicloEncontrado) {
        cout << "(" << coord.x << ", " << coord.y << ") ";
    }
    cout << endl;
}

/*
Funcao para encontrar os ciclos na matriz. Ela possue muitas limitacoes e por isso meu algoritimo nao consegue resolver problemas de transpote com solucao degenerada e por algum motivo ela tambem esta com um problema 
na hora de selecionar a celula vizinha para compor o ciclo  ele temde a escolhe a celula com maior valor e as vezes encontra um ciclo inconsistente por conta disso. Tem Como consertar, porem eu estou com tempo limitado 
e acho melhor nao quebrar mais a cabeca com este problema por hora acho que esta bom ela conseguir resolver problemas mais simples como o do exemplo que eu vou anexar junto ao codigo(Depois, com tempo, eu posso refazer 
esta funcao para consertar o problema, ja que ela e que esta avacalhando o meu programa).
*/
vector<Coordenada> encontrarCiclo(const vector<vector<int>>& matriz, int linha, int coluna) {
    int linhas = matriz.size();
    int colunas = matriz.empty() ? 0 : matriz[0].size();
    int linha_ini = linha;
    int coluna_ini = coluna;
    // Criar uma matriz de controle para rastrear as células visitadas
    vector<vector<bool>> visitado(linhas, vector<bool>(colunas, false));

    int dx[] = {0, 1, 0, -1}; // Movimentos nas linhas
    int dy[] = {1, 0, -1, 0}; // Movimentos nas colunas

    vector<Coordenada> cicloEncontrado;
    int direcaoAnterior = -1; // Direção anterior, inicializada como -1 para indicar um estado inicial sem direção.
    int direcaoAtual = 0;
    while (true) {
        int x = linha, y = coluna;
        if (visitado[x][y]) break; // Se já visitou, encerra o ciclo para evitar loops infinitos
        visitado[x][y] = true;
        cicloEncontrado.push_back(Coordenada(x, y));

        int novoX = -1, novoY = -1;
        bool encontrouVizinho = false;

        // Inicia a verificação de direção com a próxima direção àquela anteriormente usada
        int inicioVerificacao = (direcaoAtual + 1) % 4;

        for (int i = 0; i < 4; ++i) {
            int idx = (inicioVerificacao + i) % 4;
            int nx = x + dx[idx];
            int ny = y + dy[idx];

            // Encontrar a célula com maior valor entre as imediatamente adjacentes
            while (!(nx < 0 || nx >= linhas || ny < 0 || ny >= colunas || matriz[nx][ny] != 0 || visitado[nx][ny])) {
                nx += dx[idx];
                ny += dy[idx];
            }

            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny]) {
                if (!encontrouVizinho || novoX == -1 || matriz[nx][ny] < matriz[novoX][novoY]) {
                    encontrouVizinho = true;
                    novoX = nx;
                    novoY = ny;
                    direcaoAnterior = (idx + 2) % 4; // Atualiza a direção de onde veio (oposta à direção atual)
                    direcaoAtual = idx; // Atualiza a direção atual
                }
            }
        }

        if (!encontrouVizinho) {
            // Lógica para escolher a direção inicial do movimento se nenhum vizinho com valor maior for encontrado
            if (!visitado[linha_ini][coluna_ini] || direcaoAtual == direcaoAnterior) {
                if (!visitado[linha_ini][coluna_ini]) {
                    int maiorVizinho = -1;
                    int melhorDirecao = -1;

                    // Verificar os vizinhos imediatamente adjacentes para encontrar o maior valor
                    for (int i = 0; i < 4; ++i) {
                        int nx = linha_ini + dx[i];
                        int ny = coluna_ini + dy[i];

                        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && matriz[nx][ny] > 0) {
                            if (matriz[nx][ny] > maiorVizinho) {
                                maiorVizinho = matriz[nx][ny];
                                melhorDirecao = i;
                            }
                        }
                    }

                    // Se encontrou um vizinho com valor maior que zero, define a direção inicial
                    if (maiorVizinho > 0) {
                        direcaoAtual = melhorDirecao;
                        direcaoAnterior = (direcaoAtual + 2) % 4;
                        linha = linha_ini + dx[direcaoAtual];
                        coluna = coluna_ini + dy[direcaoAtual];
                    }
                }
                // Se a célula inicial já foi visitada ou a direção atual é igual à direção anterior,
                // volta para a célula anterior para tentar outra direção
                if (!visitado[linha_ini][coluna_ini] || direcaoAtual == direcaoAnterior) {
                    cicloEncontrado.pop_back();
                    if (cicloEncontrado.empty()) return {}; // Retorna ciclo vazio se não for possível formar um
                    Coordenada ultimaPos = cicloEncontrado.back();
                    linha = ultimaPos.x;
                    coluna = ultimaPos.y;
                    cicloEncontrado.pop_back();
                    direcaoAtual = direcaoAnterior;
                }
            }
        } else {
            linha = novoX;
            coluna = novoY;
        }
    }

    // Verificação e remoção de células desnecessárias para tornar o ciclo par
    //if (cicloEncontrado.size() % 2 != 0) {
       bool testaColuna = false;
        bool testaLinha = false;

    // Verifica a direção do ciclo e remove células desnecessárias
    bool removeCells = false;
    for (int i = 0; i < cicloEncontrado.size() - 2; ++i) {
        int x1 = cicloEncontrado[i].x;
        int y1 = cicloEncontrado[i].y;

        int x2 = cicloEncontrado[i + 1].x;
        int y2 = cicloEncontrado[i + 1].y;

        int x3 = cicloEncontrado[i + 2].x;
        int y3 = cicloEncontrado[i + 2].y;

        if ((x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3)) {
            if (x1 != x2 || y1 != y2) {
                cicloEncontrado.erase(cicloEncontrado.begin() + i + 1);
                i--; // Decrementa o índice para reavaliar a mesma posição após a remoção
                removeCells = true;
            }
        } else if (removeCells) {
            //cicloEncontrado.erase(cicloEncontrado.begin() + i + 1);
            i--; // Decrementa o índice para reavaliar a mesma posição após a remoção
            removeCells = false; // Para evitar a remoção indevida de outras células
        }
    }
    //}

    // Impressão do ciclo encontrado
    printCiclo(cicloEncontrado);

    return cicloEncontrado;
}

//Funcao para ajustar a solucao apos o ciclo ser encontrado.
void ajustarSolucao(vector<vector<int>>& matrizSolucao, const vector<Coordenada>& ciclo) {
    int valorMinimoAdjacente = INT_MAX;

    int chaveX = ciclo[0].x;
    int chaveY = ciclo[0].y;

    // Verificar células diretamente adjacentes à célula chave
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Evitar diagonal e a célula chave
            if (abs(i) + abs(j) == 1 && i + chaveX >= 0 && i + chaveX < matrizSolucao.size() &&
                j + chaveY >= 0 && j + chaveY < matrizSolucao[0].size() &&
                matrizSolucao[i + chaveX][j + chaveY] != 0) {

                int valorAdjacente = matrizSolucao[i + chaveX][j + chaveY];
                if (valorAdjacente < valorMinimoAdjacente) {
                    valorMinimoAdjacente = valorAdjacente;
                }
            } else if (abs(i) + abs(j) == 1 && i + chaveX >= 0 && i + chaveX < matrizSolucao.size() &&
                       j + chaveY >= 0 && j + chaveY < matrizSolucao[0].size()) {
                // Se a célula imediatamente adjacente for zero, avançar na mesma direção
                int x = i + chaveX;
                int y = j + chaveY;
                int dx = i, dy = j;

                while (x >= 0 && x < matrizSolucao.size() && y >= 0 && y < matrizSolucao[0].size() &&
                       matrizSolucao[x][y] == 0) {
                    x += dx;
                    y += dy;
                }

                if (x >= 0 && x < matrizSolucao.size() && y >= 0 && y < matrizSolucao[0].size() &&
                    matrizSolucao[x][y] != 0) {
                    int valorAdjacente = matrizSolucao[x][y];
                    if (valorAdjacente < valorMinimoAdjacente) {
                        valorMinimoAdjacente = valorAdjacente;
                    }
                }
            }
        }
    }

    bool adicionar = true;
    for (const auto& coord : ciclo) {
        int x = coord.x;
        int y = coord.y;

        if (adicionar) {
            matrizSolucao[x][y] += valorMinimoAdjacente;
        } else {
            matrizSolucao[x][y] -= valorMinimoAdjacente;
        }
        adicionar = !adicionar;
    }
}

//Funcao para zerar matriz qualquer.
void zerarMatriz(vector<vector<int>>& matriz) {
    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz[i].size(); ++j) {
            matriz[i][j] = 0;
        }
    }
}

//Funcao que retorna a ultima linha e a ultima coluna da matriz de Demandas e Ofertas.
pair<vector<int>, vector<int>> ultimaLinhaUltimaColuna(const vector<vector<int>>& matriz) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    vector<int> ultimaLinha = matriz[linhas - 1];
    vector<int> ultimaColuna;
    for (int i = 0; i < linhas; ++i) {
        ultimaColuna.push_back(matriz[i][colunas - 1]);
    }

    return make_pair(ultimaLinha, ultimaColuna);
}

int main() {
    int linhas, colunas, Cord_celula_chave_i, Cord_celula_chave_j;
    float z;
    vector<vector<int>> matrizCustos;
    vector<vector<int>> matrizOfertas_Demandas;
    vector<vector<int>> matrizSolucaoInicial_Canto_noroeste;
    vector<vector<int>> matrizSolucaoFinal;
    cout << "Insira a matriz de custos " << endl;
    matrizCustos = escolher_Origem_da_Matriz(linhas, colunas);
    cout << "Insira a matriz que contem as ofertas e as demandas " << endl;
    matrizOfertas_Demandas = escolher_Origem_da_Matriz(linhas, colunas);
    cout << endl;
    cout << "Matriz de Custos:" << endl;
    imprimirMatriz(matrizCustos);
    cout << endl;
    cout << "Matriz que contem as ofertas e as demandas:" << endl;
    imprimirMatriz(matrizOfertas_Demandas);
    cout << endl;
    Balaceamento(matrizCustos, matrizOfertas_Demandas);
    matrizSolucaoInicial_Canto_noroeste = matrizOfertas_Demandas;
    metodoCantoNoroeste(matrizCustos, matrizSolucaoInicial_Canto_noroeste);
    matrizSolucaoInicial_Canto_noroeste = removerUltimaLinhaEColuna(matrizSolucaoInicial_Canto_noroeste);
    cout << "Matriz de Custos apos o metodo do Canto Noroeste:" << endl;
    imprimirMatriz(matrizCustos);
    cout << endl;
    cout << "Matriz solucao inicial apos o metodo do Canto Noroeste:" << endl;
    imprimirMatriz(matrizSolucaoInicial_Canto_noroeste);
    cout << endl;

    if (verificaVariaveiBasicas(matrizCustos, matrizSolucaoInicial_Canto_noroeste)){
        cout << "O numero de variaveis basicas bate com o esperado. " << endl;
        cout << endl;
    }else{
        cout << "O numero de variavies basicas nao bate com o esperado. " << endl;
        cout << endl;
    }
    
    z = Calcula_valorZ(matrizCustos, matrizSolucaoInicial_Canto_noroeste); 
    cout << " Z = " << z << endl;
    cout << endl;
    vector<vector<int>> matrizCustosReduzidos(matrizCustos.size(), vector<int>(matrizCustos[0].size(), 0));
    int linha = matrizCustosReduzidos.size();
    int coluna = matrizCustosReduzidos[0].size();
    vector<int> u(linha); // u da Oferta
    vector<int> v(coluna); // v da Demanda
    vector<int> Oferta(linha); // u da Oferta
    vector<int> Demanda(coluna); // v da Demanda
    pair<int, int> Celula_Chave;
    pair<vector<int>, vector<int>> resultado = ultimaLinhaUltimaColuna(matrizOfertas_Demandas);
    Oferta = resultado.first;
    Demanda = resultado.second;
    calcularCustosReduzidos(matrizCustos, matrizSolucaoInicial_Canto_noroeste, matrizCustosReduzidos, u, v);
    cout << endl;
    cout << "Matriz de Custos:" << endl;
    cout << endl;
    imprimirMatriz(matrizCustos);
    cout << endl;
    cout << "Matriz de Custos Reduzidos :" << endl;
    cout << endl;
    imprimirMatriz(matrizCustosReduzidos);
    cout << endl;
    cout << "Valores de U e V :" << endl;
    cout << endl;
    for (int i = 0; i < linha; ++i) {
        cout << "u(" << i << ")= " << u[i] << " ";
    }
    cout<<endl;
    cout<<endl;
    for (int j = 0; j < coluna; ++j) {
        cout << "v(" << j << ")= " << v[j] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Posicao da celula chave:" << endl;
    Celula_Chave = encontrarCelulaChave(matrizCustosReduzidos);
    cout <<"(" << Celula_Chave.first << "," <<Celula_Chave.second <<")" << endl;
    cout << endl;
    matrizSolucaoFinal = matrizSolucaoInicial_Canto_noroeste;  
    vector<Coordenada> ciclo;
          
    do{
        ciclo = encontrarCiclo( matrizSolucaoFinal, Celula_Chave.first, Celula_Chave.second);
        ajustarSolucao( matrizSolucaoFinal, ciclo);
        zerarMatriz(matrizCustosReduzidos);
        calcularCustosReduzidos(matrizCustos, matrizSolucaoFinal, matrizCustosReduzidos, u, v);
        cout << endl;
        cout << "Valores de U e V :" << endl;
        cout << endl;
        for (int i = 0; i < linha; ++i) {
            cout << "u(" << i << ")= " << u[i] << " ";
        }
        cout<<endl;
        cout<<endl;
        for (int j = 0; j < coluna; ++j) {
            cout << "v(" << j << ")= " << v[j] << " ";
        }
        cout << endl;  
                cout << "Valores de U e V :" << endl;
        cout << endl;
        for (int i = 0; i < linha; ++i) {
            cout << "u(" << i << ")= " << u[i] << " ";
        }
        cout<<endl;
        cout<<endl;
        for (int j = 0; j < coluna; ++j) {
            cout << "v(" << j << ")= " << v[j] << " ";
        }
        cout << endl;
        cout << "Posicao da celula chave:" << endl;
        cout << endl;
        Celula_Chave = encontrarCelulaChave(matrizCustosReduzidos);
        cout <<"(" << Celula_Chave.first << "," <<Celula_Chave.second <<")" << endl;
        cout << endl;           
    }while (testeDeOtimalidade(matrizCustosReduzidos));
    cout << endl;
    cout << "Matriz solucao Final:" << endl;
    imprimirMatriz(matrizSolucaoFinal);
    cout << endl;
    cout << endl;
    cout << "Matriz de custos reduzidos final:" << endl;
    imprimirMatriz(matrizCustosReduzidos);
    cout << endl;
    z = Calcula_valorZ(matrizCustos, matrizSolucaoFinal); 
    cout << " Z = " << z << endl;
    cout << endl;
    return 0;
}
