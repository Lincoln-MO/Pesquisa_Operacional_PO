#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;


/*
    @author Lincoln
    @date 29/11/2023
*/

struct Espolios { 
    vector<int> Espolio; // Espolios representa uma solução candidata
    int id; //ID do item
    double valor; // Valor total do Espolios
    double peso; // Peso total do Espolios
    double tamanho; // tamanho dos Espolios

};

void LerMatriz_de_Arquivo(const string& Nome_do_arquivo, vector<vector<double>>& matriz) {
    ifstream file(Nome_do_arquivo);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << Nome_do_arquivo << "." << endl;
        return;
    }

    string linha;
    vector<double> Linha_matriz; // Movido para fora do loop

    while (getline(file, linha)) {
        istringstream iss(linha);

        string NomeItem;
        iss >> NomeItem; // Lê o nome do item

        Linha_matriz.clear(); // Limpa o vetor para reutilização

        double value;
        while (iss >> value) {
            Linha_matriz.push_back(value); // Lê os valores numéricos do item
        }

        if (!Linha_matriz.empty()) {
            matriz.push_back(Linha_matriz);
        }
    }

    file.close();
}

void imprimirMatriz(const vector<vector<double>>& matriz) {
    if (matriz.empty()) {
        cout << "Matriz vazia." << endl;
        return;
    }

    int larguraColuna = 10; // Defina a largura da coluna para alinhamento

    for (const auto& linha : matriz) {
        for (double valor : linha) {
            cout << setw(larguraColuna) << valor;
        }
        cout << endl;
    }
}

vector<string> Retorna_Nomes_itens(const vector<vector<double>>& matriz) {
    vector<string> nomes;

    for (const auto& linha : matriz) {
        if (!linha.empty()) {
            nomes.push_back(to_string(static_cast<int>(linha[0]))); // Converte diretamente o número em string
        }
    }

    return nomes;
}

vector<vector<double>> CriarNovaTabela(const vector<vector<double>>& matrizOriginal, const vector<string>& raridades) {
    vector<vector<double>> novaMatriz;
    double id = -1;

    // Iterando sobre a matriz original
    for (const auto& linha : matrizOriginal) {
        // Calculando o tamanho da linha uma vez
        size_t tamanhoLinha = linha.size();

        for (size_t j = 0; j < tamanhoLinha - 2; ++j) {
            vector<double> novaLinha;

            // Atualizando os valores com base na linha original
            id = id + 1; // ID é o número da linha
            double raridade = j; // Raridade é o número da coluna
            double tamanho = linha[tamanhoLinha - 2]; // Tamanho na penúltima coluna
            double peso = linha[tamanhoLinha - 1]; // Peso na última coluna
            double valor = linha[j]; // Valor é o valor da célula

            // Adicionando as informações extras na linha
            novaLinha.push_back(id);
            novaLinha.push_back(raridade);
            novaLinha.push_back(tamanho);
            novaLinha.push_back(peso);
            novaLinha.push_back(valor);

            // Adicionando a linha na nova matriz
            novaMatriz.push_back(novaLinha);
        }
    }

    return novaMatriz;
}

// Função para sortear uma linha aleatória da matriz
vector<double> SortearLinha( vector<vector<double>>& matriz, mt19937& gen) {
    uniform_int_distribution<> distribuicao(0, matriz.size() - 1); // Distribuição uniforme entre 0 e o tamanho da matriz - 1

    int indiceAleatorio = distribuicao(gen); // Obtém um índice aleatório dentro dos limites

    return matriz[indiceAleatorio]; // Retorna a linha correspondente ao índice sorteado
}

//Funcao que sorteia 10 itens aleatorio para simular que cairam de um bau.
vector<vector<double>> Bau_Gold( vector<vector<double>>& matriz, mt19937& gen){
    vector<vector<double>> Itens_Sorteados;

    for(int i = 0; i < 20;i++){
        vector<double> linhaSorteada = SortearLinha(matriz, gen);
        Itens_Sorteados.push_back(linhaSorteada);
    }

    return Itens_Sorteados;
}

vector<Espolios> InicializarEspolios(int tamanho_populacao, int tamanho_mochila, int peso_mochila, vector<vector<double>>& itens_encontrados) {
    vector<Espolios> populacao_Espolios;

    for (int i = 0; i < tamanho_populacao; ++i) {
        Espolios espolio;
        espolio.id = i;
        espolio.valor = 0;
        espolio.peso = 0;
        espolio.tamanho = 0;

        while ((espolio.peso <= peso_mochila) && (espolio.tamanho <= tamanho_mochila)) {
            int random_item = rand() % itens_encontrados.size();

            if (espolio.peso + itens_encontrados[random_item][3] <= peso_mochila &&
                espolio.tamanho + itens_encontrados[random_item][2] <= tamanho_mochila) {
                espolio.Espolio.push_back(random_item);
                espolio.valor += itens_encontrados[random_item][4];
                espolio.peso += itens_encontrados[random_item][3]; 
                espolio.tamanho += itens_encontrados[random_item][2]; 
            }
            if (espolio.peso + itens_encontrados[random_item][3] > peso_mochila || espolio.tamanho + itens_encontrados[random_item][2] > tamanho_mochila) {
                break;
            }
        }

        populacao_Espolios.push_back(espolio);
    }

    return populacao_Espolios;
}

void calcularValoresPesosTamanhos(vector<Espolios>& espolio, vector<vector<double>>& itens) {
    for (Espolios& indiv : espolio) {
        double total_valor = 0, total_peso = 0, total_tamanho = 0;

        for (int indice_item : indiv.Espolio) {
            total_valor += itens[indice_item][4]; // Acesso ao valor do item
            total_peso += itens[indice_item][3];  // Acesso ao peso do item
            total_tamanho += itens[indice_item][2]; // Acesso ao tamanho do item
        }

        indiv.valor = total_valor;
        indiv.peso = total_peso;
        indiv.tamanho = total_tamanho;
    }
}


// Função para imprimir um vetor de qualquer estrutura
void imprimirVetor( vector<Espolios>& vetor) {
    for ( auto& item : vetor) {
        // Imprimir campos específicos da estrutura T
        cout << "Valor: " << item.valor << ", Peso: " << item.peso << ", Tamanho: " << item.tamanho << ", Espolio: ";
        for ( auto& element : item.Espolio) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void RemoverIndividuo(vector<Espolios>& populacao, int indice) {
    if (indice >= 0 && indice < populacao.size()) {
        populacao.erase(populacao.begin() + indice); // Remove o indivíduo na posição 'indice'
    } else {
        cout << "Índice inválido. Não é possível remover o indivíduo." << endl;
    }
}

// Função para encontrar o índice de um indivíduo na população com base no seu ID
int EncontrarIndicePorID(const vector<Espolios>& populacao, int id) {
    for (int i = 0; i < populacao.size(); ++i) {
        if (populacao[i].id == id) {
            return i; // Retorna o índice se o ID for encontrado
        }
    }
    return -1; // Retorna -1 se o ID não for encontrado na população
}

void AvaliarFitness(vector<Espolios>& Lista_Espolio, vector<vector<double>>& itens, int tamanho_max, int peso_max) {
    for (Espolios& espolio : Lista_Espolio) {
        double valor_total = 0;
        double peso_total = 0;
        double tamanho_total = 0;
        bool estouro_peso = false;
        bool estouro_tamanho = false;

        // Calcula o valor total, peso total e tamanho total dos itens no espólio
        for (int indice_item : espolio.Espolio) {
            valor_total += itens[indice_item][4]; // Acesso ao valor do item
            peso_total += itens[indice_item][3];  // Acesso ao peso do item
            tamanho_total += itens[indice_item][2]; // Acesso ao tamanho do item
            if (peso_total > peso_max) {
                estouro_peso = true;
                break;
            }
            if (tamanho_total > tamanho_max) {
                estouro_tamanho = true;
                break;
            }
        }

        // Verifica se houve estouro de peso ou tamanho
        if (estouro_peso || estouro_tamanho) {
            valor_total = 0; // Se houver estouro, define o valor total do espólio como zero
        }

        espolio.valor = valor_total; // Define o valor total do Espólio como sua aptidão
    }
}


vector<Espolios> Selecao(const vector<Espolios>& populacao, int numero_selecionados) {
    vector<Espolios> selecionados;
    double soma_aptidoes = 0.0;

    // Calcula a soma total das aptidões (valores) dos Espolios na população
    for (const auto& espolio : populacao) {
        soma_aptidoes += espolio.valor;
    }

    // Realiza a seleção dos Espolios
    double tamanho_intervalo = soma_aptidoes / numero_selecionados;
    double valor_inicial = ((double)rand() / (RAND_MAX)) * tamanho_intervalo;
    double ponteiro = valor_inicial;

    for (int i = 0; i < numero_selecionados; ++i) {
        size_t j = 0;
        double soma_parcial = populacao[0].valor;

        while (soma_parcial < ponteiro) {
            ++j;
            soma_parcial += populacao[j].valor;
        }

        selecionados.push_back(populacao[j]);
        ponteiro += tamanho_intervalo;
    }

    return selecionados;
}

void Crossover(const vector<Espolios>& pais1, const vector<Espolios>& pais2, vector<Espolios>& filhos1, vector<Espolios>& filhos2, vector<vector<double>>& itens_encontrados) {
    int ponto_corte = rand() % pais1.size();

    filhos1.insert(filhos1.end(), pais1.begin(), pais1.begin() + ponto_corte);
    filhos1.insert(filhos1.end(), pais2.begin() + ponto_corte, pais2.end());

    filhos2.insert(filhos2.end(), pais2.begin(), pais2.begin() + ponto_corte);
    filhos2.insert(filhos2.end(), pais1.begin() + ponto_corte, pais1.end());

    // Recalcula os valores, pesos e tamanhos dos filhos
    calcularValoresPesosTamanhos(filhos1, itens_encontrados);
    calcularValoresPesosTamanhos(filhos2, itens_encontrados);
}

void Mutacao(vector<Espolios>& espolio, double taxa_mutacao, vector<vector<double>>& itens, int tamanho_max, int peso_max) {
    for (auto& indiv : espolio) {
        if (((double)rand() / RAND_MAX) < taxa_mutacao) {
            int posicao = rand() % indiv.Espolio.size(); // Posição aleatória no vetor Espolio

            // Gera um novo item aleatório
            int novo_item = rand() % itens.size();

            // Verifica se adicionar o novo item excede as restrições da mochila
            if (indiv.peso - itens[indiv.Espolio[posicao]][3] + itens[novo_item][3] <= peso_max &&
                indiv.tamanho - itens[indiv.Espolio[posicao]][2] + itens[novo_item][2] <= tamanho_max) {
                indiv.Espolio[posicao] = novo_item;
            }
        }
    }
    // Recalcula os valores, pesos e tamanhos após a mutação
    calcularValoresPesosTamanhos(espolio, itens);
}


void SubstituicaoElite(vector<Espolios>& populacao, vector<Espolios>& novos_filhos, int num_elite, int tamanho_maximo) {
    // Ordena os novos filhos por valor (ou outra métrica de aptidão)
    sort(novos_filhos.begin(), novos_filhos.end(), [](const Espolios& a, const Espolios& b) {
        return a.valor > b.valor; // Ordena em ordem decrescente de valor
    });

    int tamanho_atual = populacao.size();
    int tamanho_novos_filhos = novos_filhos.size();
    int tamanho_final = min(tamanho_atual + tamanho_novos_filhos, tamanho_maximo);

    vector<Espolios> nova_populacao;
    nova_populacao.reserve(tamanho_final);

    // Mantém os 'num_elite' melhores indivíduos (elite) da geração anterior
    copy(populacao.begin(), populacao.begin() + min(num_elite, tamanho_atual), back_inserter(nova_populacao));

    // Substitui os demais indivíduos menos aptos pelos novos filhos gerados
    copy(novos_filhos.begin(), novos_filhos.begin() + min(tamanho_novos_filhos, tamanho_maximo - num_elite), back_inserter(nova_populacao));

    populacao = move(nova_populacao); // Atualiza a população com a nova geração
}

vector<Espolios> Loop_de_Geracoes(vector<Espolios>& populacao, int num_geracoes, double taxa_mutacao, vector<vector<double>>& itens_encontrados, int num_elite, int tamanho_max, int peso_max) {
    const int tamanho_populacao = populacao.size(); // Tamanho da população inicial

    for (int k = 0; k < num_geracoes; ++k) { // Para cada geração (num_geracoes > 1 significa que a cada tantas geracoes)
        // Avaliação do fitness da população atual
        AvaliarFitness(populacao, itens_encontrados, tamanho_max, peso_max);

        vector<Espolios> nova_populacao; // Nova população gerada nesta geração
        nova_populacao.reserve(tamanho_populacao * 2); // Reserva espaço para evitar realocações frequentes

        for (int i = 0; i < tamanho_populacao; ++i) { // Para cada indivíduo na população
            // Seleção de pai1 e pai2
            vector<Espolios> pais1 = Selecao(populacao, 2);
            vector<Espolios> pais2 = Selecao(populacao, 2);

            // Criação de dois filhos a partir dos pais usando crossover
            vector<Espolios> filhos1;
            vector<Espolios> filhos2;
            Crossover(pais1, pais2, filhos1, filhos2, itens_encontrados);

            // Aplicação de mutação nos filhos
            Mutacao(filhos1, taxa_mutacao, itens_encontrados, tamanho_max, peso_max);
            Mutacao(filhos2, taxa_mutacao, itens_encontrados, tamanho_max, peso_max);

            // Adição dos filhos à nova população
            nova_populacao.insert(nova_populacao.end(), filhos1.begin(), filhos1.end());
            nova_populacao.insert(nova_populacao.end(), filhos2.begin(), filhos2.end());
            //cout << "Individuo " << i + 1 << " concluida." << endl;
        }

        // Ordena a nova população
        sort(nova_populacao.begin(), nova_populacao.end(), [](const Espolios& a, const Espolios& b) {
            return a.valor > b.valor; // Ordena em ordem decrescente de valor
        });

        // Mantém apenas os melhores indivíduos (elite)
        nova_populacao.resize(tamanho_populacao);

        // Atualização da população para a nova geração
        populacao = move(nova_populacao);

        // Adiciona prints para verificar o progresso
        //cout << "Individuo " << geracao + 1 << " concluida." << endl;
    }

    cout << "Loop de geracao concluido." << endl;

    return populacao; // Retorno da população final após as iterações
}

vector<Espolios> AlgoritmoGenetico(vector<Espolios>& Solucao_ini, vector<vector<double>>& itens_encontrados_na_masmorra, int tamanho_populacao, int tamanho_maximo_mochila, int peso_maximo_mochila, int num_geracoes, double taxa_mutacao, int num_elite, int num_geracoes_sem_melhora, mt19937& gen, int Quantidade_solucoes_iniciais) {
    vector<Espolios> Espolios_na_Mochila = Solucao_ini;
    int tamanho_Max_pop = Quantidade_solucoes_iniciais;
    int geracoes_sem_melhora = 0;
    int geracao_atual = 0;

    while ( geracao_atual < num_geracoes) {
        AvaliarFitness(Espolios_na_Mochila, itens_encontrados_na_masmorra, tamanho_maximo_mochila, peso_maximo_mochila);
        SubstituicaoElite(Espolios_na_Mochila, Espolios_na_Mochila, num_elite, tamanho_Max_pop);
        Espolios_na_Mochila = Loop_de_Geracoes(Espolios_na_Mochila, 1, taxa_mutacao, itens_encontrados_na_masmorra, num_elite, tamanho_maximo_mochila, peso_maximo_mochila);
        geracao_atual++;
        cout << "Geracao " << geracao_atual << " concluida." << endl;
        if (Espolios_na_Mochila[0].valor > Espolios_na_Mochila[1].valor) {
            geracoes_sem_melhora = 0;
        } else {
            geracoes_sem_melhora++;
        }

        if (geracoes_sem_melhora > num_geracoes_sem_melhora) {
            cout << "Atingiu o numero maximo de geracoes sem melhora." << endl;
            break;
        }
    }

    return Espolios_na_Mochila;
}


void imprimirSolucao(const vector<Espolios>& item) {
    if (item.empty()) {
        cout << "Vetor de solucoes vazio." << endl;
        return;
    }

    cout << "Valor: " << item[0].valor << ", Peso: " << item[0].peso << ", Tamanho: " << item[0].tamanho << ", Espolio: ";
    for (auto& element : item[0].Espolio) {
        cout << element << " ";
    }
    cout << endl;
}

int main(){
    int Quantidade_solucoes_iniciais = 80; // Defina o tamanho da população inicial
    int num_geracoes = 30;
    int Tamanho_Maximo_Mochila = 20;
    int Capacidade_compartimento = 1;
    int Peso_maximo_mochila = 20;
    double taxa_mutacao = 0.1; 
    int num_elite = 10; // Especifique o número de indivíduos elite que você deseja manter
    int num_geracoes_sem_melhora = 3;
    random_device rd; // Gerador de números aleatórios
    mt19937 gen(rd()); // Mersenne Twister como gerador de números aleatórios

    vector<vector<double>> Matriz_de_Itens;
    LerMatriz_de_Arquivo("Matriz_itens.txt", Matriz_de_Itens);
    cout << "   Cracked    Flawed    Normal      Fine Exquisite   Perfect   Tamanho      peso" <<endl;
    imprimirMatriz(Matriz_de_Itens);
    vector<string> raridades = {"Cracked", "Flawed", "Normal", "Fine", "Exquisite", "Perfect"};
    vector<string> Nomes = {"Safira_azul", "Diamante", "Esmeralda", "Rubi","Pulseira_de_ouro_estampada ","Adaga_Cerimonial","Calice","Coroa","Pote","Pergaminho"};
    vector<string> Nomes_itens = Retorna_Nomes_itens(Matriz_de_Itens);
    vector<vector<double>> Matriz_Itens_compl = CriarNovaTabela( Matriz_de_Itens, raridades);
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "        id  Raridade   tamanho      peso     valor" <<endl;
    imprimirMatriz(Matriz_Itens_compl);
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "*************************ITENS ENCONTRADOS NA MASMORRA******************************" << endl;
    cout << "        id  Raridade   tamanho      peso     valor" <<endl;
    vector<vector<double>> Itens_encontrados_na_masmorra = Bau_Gold(Matriz_Itens_compl, gen);
    imprimirMatriz(Itens_encontrados_na_masmorra);
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    
    //vector<vector<bool>> MatrizCompartimentos(5, vector<bool>(4,false)); // matriz para saber se os compartimentos da mochila estoa ocupados
    //vector<vector<double>> MatrizMochila(5, vector<double>(4,0)); // matriz para saber qual item ocupa a celula (vamos saber pelo valor da celula, que sera o id do item. Itens com mais de 1 de tamanho ocupam duas celulas, pois cada celula so suporta 1 de tamanho, sempre imadiatamentre adjascentes.)

    vector<Espolios> solucoes_iniciais_Espolio_masmorra = InicializarEspolios(Quantidade_solucoes_iniciais, Tamanho_Maximo_Mochila, Peso_maximo_mochila, Itens_encontrados_na_masmorra);
    
    cout << "*************************SOLUCOES INICIAIS RANDOMICAS**************************" << endl;
    cout << endl;
    imprimirVetor(solucoes_iniciais_Espolio_masmorra);
    cout << endl;
    //AvaliarFitness(solucoes_iniciais_Espolio_masmorra, Itens_encontrados_na_masmorra);
    cout << endl;
    // Executando o algoritmo genético para resolver o problema da mochila compartimentada
    vector<Espolios> melhores_solucoes = AlgoritmoGenetico(solucoes_iniciais_Espolio_masmorra, Itens_encontrados_na_masmorra, Quantidade_solucoes_iniciais, Tamanho_Maximo_Mochila, Peso_maximo_mochila, num_geracoes, taxa_mutacao, num_elite, num_geracoes_sem_melhora, gen, Quantidade_solucoes_iniciais);

    // Exibindo as melhores soluções encontradas
    cout << endl;
    cout << "********************Melhores solucoes encontradas*************************:" << endl;
    cout << endl;
    imprimirSolucao(melhores_solucoes);
    
    return 0;
}