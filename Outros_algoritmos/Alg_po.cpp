#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>  // Inclua esta biblioteca para INT_MAX

using namespace std;

/*
    @author Lincoln
    @date 31/10/2023
*/

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

    //cout << somaUltimaLinha<< endl;
    //cout << somaUltimaColuna<< endl;

    // Verifica se a soma da última linha é igual à soma da última coluna
    if (somaUltimaLinha != somaUltimaColuna) {
        cerr << "A matriz de variáveis não está balanceada." << endl;
        return;
    }


    int i = 0;
    int j = 0;

    // Implemente o algoritmo do Canto Noroeste
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

// Função para realizar o teste de otimalidade (usando metodo de multiplicadores de Lagrange)
bool testeDeOtimalidade(vector<vector<int>>& matrizCustos, vector<vector<int>>& matrizVariaveis) {
    int linhasC = matrizCustos.size();
    int colunasC = matrizCustos[0].size();
    int linhasV = matrizVariaveis.size();
    int colunasV = matrizVariaveis[0].size();

    vector<vector<int>> multiplicadores(linhasC, vector<int>(colunasC, 0));

    // Calcular os multiplicadores de Lagrange
    for (int i = 0; i < linhasC; i++) {
        for (int j = 0; j < colunasC; j++) {
            if (matrizVariaveis[i][j] == 0) {
                // Custo reduzido é positivo, então o multiplicador é zero
                multiplicadores[i][j] = 0;
            } else {
                // Calcular o multiplicador de Lagrange
                int custoReduzido = matrizCustos[i][j];
                for (int k = 0; k < linhasC; k++) {
                    for (int l = 0; l < colunasC; l++) {
                        if (matrizVariaveis[k][l] != 0) {
                            custoReduzido -= multiplicadores[k][l];
                        }
                    }
                }
                multiplicadores[i][j] = custoReduzido;
            }
        }
    }

    // Verificar se todos os multiplicadores de Lagrange são não negativos
    for (int i = 0; i < linhasC; i++) {
        for (int j = 0; j < colunasC; j++) {
            if (multiplicadores[i][j] < 0) {
                // Encontrou um multiplicador negativo, a solução não é ótima
                return false;
            }
        }
    }

    // Se todos os multiplicadores são não negativos, a solução é ótima
    return true;
}

// Função para melhorar a solução usando o método de Stone
void metodoStone(vector<vector<int>>& matrizCustos, vector<vector<int>>& matrizVariaveis) {
    int linhasC = matrizCustos.size();
    int colunasC = matrizCustos[0].size();
    int linhasV = matrizVariaveis.size();
    int colunasV = matrizVariaveis[0].size();

    // Inicializar as variáveis para o método de Stone
    vector<vector<bool>> visitados(linhasC, vector<bool>(colunasC, false));
    vector<vector<int>> caminhos(linhasC, vector<int>(colunasC, 0));

    // Encontrar um ciclo de custo negativo na matriz de custos
    for (int i = 0; i < linhasC; i++) {
        for (int j = 0; j < colunasC; j++) {
            if (!visitados[i][j] && matrizCustos[i][j] < 0) {
                vector<vector<bool>> ciclo(linhasC, vector<bool>(colunasC, false));
                if (encontrarCiclo(matrizCustos, visitados, caminhos, ciclo, i, j)) {
                    // Encontrou um ciclo de custo negativo

                    // Determinar o menor valor no ciclo
                    int menorValorCiclo = INT_MAX; //o INT_MAX é uma constante definida na biblioteca <climits>.
                    for (int k = 0; k < linhasC; k++) {
                        for (int l = 0; l < colunasC; l++) {
                            if (ciclo[k][l]) {
                                menorValorCiclo = min(menorValorCiclo, matrizCustos[k][l]);
                            }
                        }
                    }

                    // Atualizar a matriz de variáveis
                    for (int k = 0; k < linhasC; k++) {
                        for (int l = 0; l < colunasC; l++) {
                            if (ciclo[k][l]) {
                                matrizVariaveis[k][l] += menorValorCiclo;
                            }
                        }
                    }

                    // Reduzir os custos ao longo do ciclo
                    for (int k = 0; k < linhasC; k++) {
                        for (int l = 0; l < colunasC; l++) {
                            if (ciclo[k][l]) {
                                matrizCustos[k][l] -= menorValorCiclo;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Função para encontrar um ciclo na matriz de custos
bool encontrarCiclo(vector<vector<int>>& matrizCustos, vector<vector<bool>>& visitados, vector<vector<int>>& caminhos, vector<vector<bool>>& ciclo, int linha, int coluna) {
    int linhasC = matrizCustos.size();
    int colunasC = matrizCustos[0].size();

    visitados[linha][coluna] = true;
    caminhos[linha][coluna] = 1;

    for (int i = 0; i < linhasC; i++) {
        for (int j = 0; j < colunasC; j++) {
            if (matrizCustos[i][j] < 0 && !visitados[i][j] && i != linha && j != coluna) {
                if (caminhos[i][j] == 1 || encontrarCiclo(matrizCustos, visitados, caminhos, ciclo, i, j)) {
                    ciclo[i][j] = true;
                    return true;
                }
            }
        }
    }

    caminhos[linha][coluna] = 0;
    return false;
}




int main() {
    int linhas, colunas;
    float z;
    vector<vector<int>> matrizCustos;
    vector<vector<int>> matrizVariaveis;

    cout << "Insira a matriz de custos " << endl;
    matrizCustos = escolher_Origem_da_Matriz(linhas, colunas);
    cout << "Insira a matriz de Variaveis " << endl;
    matrizVariaveis = escolher_Origem_da_Matriz(linhas, colunas);
    cout << endl;

    cout << "Matriz de Custos:" << endl;
    imprimirMatriz(matrizCustos);
    cout << endl;
    cout << "Matriz de Variaveis:" << endl;
    imprimirMatriz(matrizVariaveis);
    cout << endl;

    metodoCantoNoroeste(matrizCustos, matrizVariaveis);

    cout << "Matriz de Custos após o método do Canto Noroeste:" << endl;
    imprimirMatriz(matrizCustos);
    cout << endl;
    cout << "Matriz de Variaveis após o método do Canto Noroeste:" << endl;
    imprimirMatriz(matrizVariaveis);
    cout << endl;

    if (verificaVariaveiBasicas(matrizCustos, matrizVariaveis)){
        cout << "O numero de variaveis basicas bate com o esperado. " << endl;
        cout << endl;
    }else{
        cout << "O numero de variavies basicas nao bate com o esperado. " << endl;
        cout << endl;
    }
    
    z = Calcula_valorZ(matrizCustos, matrizVariaveis); 
    cout << " Z = " << z << endl;
    cout << endl;

    return 0;
}
