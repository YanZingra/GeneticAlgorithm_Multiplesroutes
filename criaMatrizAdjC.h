#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include<cstdio>
#include <cmath>
#define PI 3.14159265358979323846

using namespace std;
struct RetornaCaminho
{
	vector<vector<int>>caminho;

	RetornaCaminho() {};
};
class MadJ {

public:
	//Inicio variaveis calculos matriz adjacencias e quantidade alunos,vans e escolas
	double lat, lon;
	char type;
	int num;
	int cont = 0;
	int tam = cont;
	int numEscola, numAlunos, numVans;
	//int fileType;
	vector<vector<double>> mat;//matriz com os dados do Pontos.txt
	vector<vector<double>> matrizAdjacente;//matriz adjacente calculada
	vector<double> row;

	string metodoAlgoritmo, numeraGF, numeraVG, geracoes, cruzGF, cruzVG, mutaGF, mutaVG;
	string arquivoGF = "fitGeral";//modelo nome: || cont�m  FitXGeracoes  GeracoesXFit100- .txt
	string arquivoVG = "fitVans";
	string arquivoCaminho = "fCaminho";
	string arquivoDP = "dp";
	string tipoArquivo = ".txt";
	//Fim das variaveis geracao de graficos


	MadJ(int numArquivo)
	{
		//fileType =numArquivo;
		armDadosTxt(numArquivo);
		//criaMadj(numArquivo);
		numEscola = qtdEscola();
		numVans = qtdVan();
		numAlunos = qtdAluno();
	}

	MadJ()
	{
	}

	vector<vector<double>>retornaMatrizAdj() {
		return matrizAdjacente;
	}

	void armDadosTxt(int selecionaArquivo) {	//Armazena os dados do txt na matriz(mat) vector de vector
		string names[18] = { "pontosA-5Vans-5Escolas.txt","pontosA-7Vans-5Escolas.txt","pontosA-10Vans-5Escolas.txt","pontosA-5Vans-7Escolas.txt","pontosA-7Vans-7Escolas.txt","pontosA-10Vans-7Escolas.txt","pontosA-5Vans-10Escolas.txt","pontosA-7Vans-10Escolas.txt","pontosA-10Vans-10Escolas.txt","pontosC-5Vans-5Escolas.txt","pontosC-7Vans-5Escolas.txt","pontosC-10Vans-5Escolas.txt","pontosC-5Vans-7Escolas.txt","pontosC-7Vans-7Escolas.txt","pontosC-10Vans-7Escolas.txt","pontosC-5Vans-10Escolas.txt","pontosC-7Vans-10Escolas.txt","pontosC-10Vans-10Escolas.txt" };
		string nomeArquivo;
		nomeArquivo = names[selecionaArquivo];

		ifstream file(nomeArquivo);

		while (!file.eof())
		{
			double a;
			file >> a;
			row.push_back(a);
			//Insere na matriz a linha de dados lida no arquivo Pontos.txt 
			if (row.size() == 5)
			{
				mat.push_back(row);
				row.clear();
			}
			fflush(stdin);
		}
		file.close();
	}


	void criaMadj(int selecionaArquivo) {
		vector<vector<double>> matAdj;							//Declarando Matriz de adjacencias matAdj || VARIAVEL DE RETORNO
		string nomeArquivo;
		double deg2radMultiplier = PI / 180;
		double radius = 6378.137;
		double latitude1 = 0;
		double longitude1 = 0;
		double latitude2 = 0;
		double longitude2 = 0;
		double dist = 0;				//Vari�vel Para receber o c�lculo da dist�ncia entre pontos

		string names[18] = { "MA-pontosA-5Vans-5Escolas.txt","MA-pontosA-7Vans-5Escolas.txt","MA-pontosA-10Vans-5Escolas.txt","MA-pontosA-5Vans-7Escolas.txt","MA-pontosA-7Vans-7Escolas.txt","MA-pontosA-10Vans-7Escolas.txt","MA-pontosA-5Vans-10Escolas.txt","MA-pontosA-7Vans-10Escolas.txt","MA-pontosA-10Vans-10Escolas.txt","MA-pontosC-5Vans-5Escolas.txt","MA-pontosC-7Vans-5Escolas.txt","MA-pontosC-10Vans-5Escolas.txt","MA-pontosC-5Vans-7Escolas.txt","MA-pontosC-7Vans-7Escolas.txt","MA-pontosC-10Vans-7Escolas.txt","MA-pontosC-5Vans-10Escolas.txt","MA-pontosC-7Vans-10Escolas.txt","MA-pontosC-10Vans-10Escolas.txt" };
		nomeArquivo = names[selecionaArquivo];
		ofstream out(nomeArquivo);					//construtor arquivo
		vector<double> rowAdj;									//Declarando Vector rowAdj(Linha de dados dentro do vector matAdj)

		for (int j = 0; j < mat.size(); j++)
		{
			latitude1 = mat[j][0] * deg2radMultiplier;	//Latitude Primeira coluna da linha do arquivo
			longitude1 = mat[j][1] * deg2radMultiplier;	//Longitude Segunda coluna da linha do arquivo

			for (int i = 0; i < mat.size(); i++)
			{
				latitude2 = mat[i][0] * deg2radMultiplier;  //Latitude Primeira coluna da linha do arquivo
				longitude2 = mat[i][1] * deg2radMultiplier;	//Longitude Segunda coluna da linha do arquivo
				dist = acos(sin(latitude1) * sin(latitude2) + cos(latitude1) * cos(latitude2) * cos(longitude2 - longitude1)) * radius;//sqrt(pow((latitude1 - latitude2), 2) + pow((longitude1 - longitude2), 2));	//C�lculo Dist�ncia esf�rica 

				rowAdj.push_back(dist);			//Inserindo dist�ncia calculada  em rowAdj
				out << dist << "\t";			//Separando dados no txt
				if (rowAdj.size() == mat.size())//50)
				{
					matAdj.push_back(rowAdj);	//Insere Coluna na Matriz Adjacente
					rowAdj.clear();				//Limpa rowAdj	
					out << endl;
				}
			}
		}
		latitude1 = 0;
		longitude1 = 0;
		latitude2 = 0;
		longitude2 = 0;
		//cout << endl << matAdj[0].size() << matAdj.size()<<"Madjacencias size\n";/////////////////////////////
		out.close();
		matrizAdjacente = matAdj;
		//return matAdj;
	}

	int qtdEscola() //Calcula a quantidade de escolas no Pontos.txt
	{
		int qtd = 0;
		for (int a = 0; a < mat.size(); a++) {
			if (mat[a][2] == 03)
			{
				qtd = qtd + 1;
			}
		}
		//cout << "\n" << qtd << " escolas!\n";//////////////////////////////////////
		return qtd;
	}


	int qtdVan() //Calcula a quantidade de vans no Pontos.txt
	{
		int qtd = 0;
		for (int a = 0; a < mat.size(); a++) {
			if (mat[a][2] == 02)
			{
				qtd = qtd + 1;
			}
		}
		//cout << "\n" << qtd << " Vans!\n";//////////////////////////////////
		return qtd;
	}
	int qtdAluno() //Calcula a quantidade de alunos no Pontos.txt
	{
		int qtd = 0;
		for (int a = 0; a < mat.size(); a++) {
			if (mat[a][2] == 01)
			{
				qtd = qtd + 1;
			}
		}
		//cout << "\n" << qtd << " alunos!\n";////////////////////////////////
		return qtd;
	}
	vector<vector<int>>AlunosPorEscola() /*Retorna um vector<vector<double>> no que separa os alunos por escola. Exemplo:    22  23  24
																															 01  10  07
																															 13  12  15
	alunos 01 e 13 s�o da escola de posi��o 22 na matriz de adjacencias.
	alunos 10 e 12 s�o da escola de posi��o 23 na matriz de adjacencias.
	alunos 07 e 15 s�o da escola de posi��o 24 na matriz de adjacencias.
	*/
	{
		double aux;

		vector<vector<int>> AlunosPorEscola(numEscola);
		//int quantidadeEscolas= qtdEscola();
		//int quantidadeAlunos = qtdAluno();
		//int quantidadeVans = qtdVan();
		int contadorPosicaoEscola = numAlunos + numVans;
		int idEscola;
		for (int i = 0; i < numEscola; i++)
		{
			AlunosPorEscola[i].push_back(contadorPosicaoEscola);//insere todas as escolas na primeira posicao de cada linha
			contadorPosicaoEscola += 1;
		}
		contadorPosicaoEscola = 0;
		for (int a = 0; a < mat.size(); a++)
		{
			if (mat[a][2] == 1) //Verificando se � aluno pelo txt de pontos(Pontos.txt)
			{
				idEscola = mat[a][4];// atribui escola do aluno

				AlunosPorEscola[idEscola].push_back((int)mat[a][3]);//insere numero do aluno na martiz no local correspondente a sua escola
			}

		}
		return AlunosPorEscola;
	}

	//vetor|| posi��o: alunos //conteudo: escola dele

	vector<int> retornaEscolaDoALuno()
	{
		//int qtd = qtdAluno();
		vector<int> VetorEscolas;
		for (int a = 0; a < numAlunos; a++)
		{
			VetorEscolas.push_back(mat[a][4]);
		}
		//cout << "\n"<<VetorEscolas.size()<<" "<<numAlunos <<"\n";
		/*for (int h = 0; h < VetorEscolas.size(); ++h)
		{


				cout << VetorEscolas[h];
				cout << " ";


		}*/
		return VetorEscolas;
	}

	//FUNCOES .txt DOS GRAFICOS
	void criaGraficoGeracaoFit(vector<double> GeracaoFit, vector<RetornaCaminho> caminho, int numGeracoes, int individuos, int cruzamento, int mutacao, int qtdEscolas, int qtdVans, int contaExecucaoGF, int PAC, int peso) {
		if (contaExecucaoGF < 10)
		{
			if (PAC == 1)
			{
				arquivoGF = "fitGeralA";
			}
			else
			{
				arquivoGF = "fitGeralC";
			}
			arquivoGF = 'p' + to_string(peso) + " -" + arquivoGF + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec0" + to_string(contaExecucaoGF) + tipoArquivo;
		}
		else
		{
			if (PAC == 1)
			{
				arquivoGF = "fitGeralA";
			}
			else
			{
				arquivoGF = "fitGeralC";
			}
			arquivoGF = 'p' + to_string(peso) + " -" + arquivoGF + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec" + to_string(contaExecucaoGF) + tipoArquivo;
		}

		//GeracoesXFit100-
		ofstream out(arquivoGF);					//construtor arquivo

		for (int i = 0; i < GeracaoFit.size(); i++)
		{
			out << GeracaoFit[i] << " ";			//Separando dados no txt
		}
		out << endl;


		out.close();
	}


	void criaGraficoGeracaoFit(vector<double> GeracaoFit, vector<RetornaCaminho> caminho, int numGeracoes, int individuos, int cruzamento, int mutacao, int qtdEscolas, int qtdVans, int contaExecucaoGF, int PAC, int peso, vector<vector<double>> distVans) {
		if (contaExecucaoGF < 10)
		{
			if (PAC == 1)
			{
				arquivoGF = "fitGeralA";
			}
			else
			{
				arquivoGF = "fitGeralC";
			}
			arquivoGF = 'p' + to_string(peso) + " -" + arquivoGF + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec0" + to_string(contaExecucaoGF) + tipoArquivo;
		}
		else
		{
			if (PAC == 1)
			{
				arquivoGF = "fitGeralA";
			}
			else
			{
				arquivoGF = "fitGeralC";
			}
			arquivoGF = 'p' + to_string(peso) + " -" + arquivoGF + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec" + to_string(contaExecucaoGF) + tipoArquivo;
		}

		//GeracoesXFit100-
		ofstream out(arquivoGF);					//construtor arquivo

		for (int i = 0; i < GeracaoFit.size(); i++)
		{
			out << GeracaoFit[i] << " ";			//Separando dados no txt
		}
		out << endl;

		for (int i = 0; i < distVans.size(); i++)
		{
			for (int j = 0; j < distVans[i].size(); j++)
			{
				out << distVans[i][j] << " ";
			}
			out << endl;
		}
		out.close();
	}

	void caminho(vector<RetornaCaminho> caminho, int numGeracoes, int individuos, int cruzamento, int mutacao, int qtdEscolas, int qtdVans, int contaExecucaoGF, int PAC, int peso)
	{
		if (contaExecucaoGF < 10)
		{
			if (PAC == 1)
			{
				arquivoCaminho = "fCaminhoA";
			}
			else
			{
				arquivoCaminho = "fCaminhoC";
			}
			arquivoCaminho = 'p' + to_string(peso) + " -" + arquivoCaminho + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec0" + to_string(contaExecucaoGF) + tipoArquivo;
		}

		else
		{
			if (PAC == 1)
			{
				arquivoCaminho = "fCaminhoA";
			}
			else
			{
				arquivoCaminho = "fCaminhoC";
			}
			arquivoCaminho = 'p' + to_string(peso) + " -" + arquivoCaminho + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + "Exec" + to_string(contaExecucaoGF) + tipoArquivo;
		}

		ofstream out(arquivoCaminho);
		for (int geracoes = 0; geracoes < caminho.size(); geracoes++)
		{
			for (int van = 0; van < caminho[geracoes].caminho.size(); van++)
			{
				for (int posicaoDoCaminho = 0; posicaoDoCaminho < caminho[geracoes].caminho[van].size(); posicaoDoCaminho++)
				{
					//cout << caminho[geracoes].caminho[van][posicaoDoCaminho];
					//                              Latitude                                                 Longitude
					out << mat[caminho[geracoes].caminho[van][posicaoDoCaminho]][0] << " " << mat[caminho[geracoes].caminho[van][posicaoDoCaminho]][1] << " ";
				}
				if (van < caminho[geracoes].caminho.size() - 1)
				{
					out << ",";
				}
			}
			out << endl;
		}
		//arquivoCaminho = "fCaminho";
		out.close();
	}
	void criaArquivoDP(vector<double>DpVans, int numGeracoes, int individuos, int cruzamento, int mutacao, int qtdEscolas, int qtdVans, int PAC, int peso)
	{
		if (PAC == 1)
		{
			arquivoDP = "dpA";
		}
		else
		{
			arquivoDP = "dpC";
		}
		arquivoDP = arquivoDP + '-' + to_string(numGeracoes) + "ger-" + to_string(individuos) + "ind-" + to_string(cruzamento) + "cru-" + to_string(mutacao) + "mut" + '(' + to_string(qtdEscolas) + "e-" + to_string(qtdVans) + 'v' + ')' + 'p' + to_string(peso) + tipoArquivo;
		ofstream out(arquivoDP);
		for (int i = 0; i < DpVans.size() - 1; i++)
		{
			out << DpVans[i] << " ";
		}
		out << DpVans[DpVans.size() - 1];
		out.close();
	}

};