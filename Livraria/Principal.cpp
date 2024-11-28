#include <iostream>
#include <ctime>
#include <fstream> 

using namespace std;

struct Cliente {
	int cpf  = 0;
	char nome[50] = "";
	int totalAlugueis = 0;
};

struct Livro {
	int idLivro = 0;
	char titulo[50] = "";
	char autor[50] = "";
	char genero[50] = "";
	int totalAlugeis = 0;
	bool disponivel = true;
};

struct Aluguel {
	int idAluguel = 0;
	int idLivro = 0;
	int cpfCliente = 0;
	tm dataAluguel = {};
	tm dataDevolucao = {};
	bool devolvido  = false;
};

struct Cliente clientes[100] = {};
struct Livro livros[100] = {};
struct Aluguel alugueis[100] = {};

int indiceLivro = 0;
int indiceCliente = 0;
int indiceAluguel = 0;

int opcao = -1;

void menu();         
void cadastro();      
void consulta();
void efetuarAluguel();
void devolucao();
void relatorio();
void deletar();
void salvarArquivo();

int buscarLivro(int id)
{
	for (int i = 0; i < indiceLivro; i++)
	{
		if (id == livros[i].idLivro)
		{
			return i;
		}
	}

	return -1;
}

int buscarCliente(int cpf)
{
	for (int i = 0; i < indiceCliente; i++)
	{
		if (cpf == clientes[i].cpf)
		{
			return i;
		}
	}

	return -1;

}

int buscarAluguel(int id)
{
	for (int i = 0; i < indiceAluguel; i++)
	{
		if (id == alugueis[i].idAluguel)
		{
			return i;
		}
	}

	return -1;
}

void cadastroLivro()
{
	int id;


	if (indiceLivro < 100)
	{
		cout << "Digite a identificacao do livro: ";
		cin >> id;

		if (buscarLivro(id) == -1)
		{
			cout << "Digite o titulo do livro: ";
			cin.ignore();
			cin.getline(livros[indiceLivro].titulo, 50);

			cout << "Digite o autor do livro: ";
			cin.getline(livros[indiceLivro].autor, 50);

			cout << "Digite o genero do livro: ";
			cin.getline(livros[indiceLivro].genero, 50);

			livros[indiceLivro].idLivro = id;

			indiceLivro++;

			cout << "Livro cadastrado com sucesso!" << endl;
		}
		else
		{
			cout << "Livro ja cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de livros cheio" << endl;
	}
}

void cadastroCliente()
{
	int cpf;
	

	if (indiceCliente < 100)
	{
		cout << "Digite o cpf do cliente: ";
		cin >> cpf;

		if (buscarCliente(cpf) == -1)
		{
			cout << "Digite o nome do cliente: ";
			cin.ignore();
			cin.getline(clientes[indiceCliente].nome, 50);

			clientes[indiceCliente].cpf = cpf;

			indiceCliente++;

			cout << "Cliente  cadastrado com sucesso!" << endl;
		}
		else
		{
			cout << "Cliente ja cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de clientes cheio" << endl;
	}
}

void cadastro()
{
	do
	{
		cout << "-------------------------------" << endl;
		cout << "         CADASTRO" << endl;
		cout << "-------------------------------" << endl;

	   cout << "1. Cadastrar livro" << endl
			<< "2. Cadastrar cliente" << endl
			<< "0. Voltar " << endl
			<< "Digite uma das opcoes acima: " << endl;
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			cadastroLivro();
			break;
		case 2:
			cadastroCliente();
			break;
		case 0:
			cout << "Voltando..." << endl;
			menu();
			break;
		default:
			cout << "Opcao invalida do menu." << endl;
			break;
		}
	} while (opcao != 0);
}

void consultaLivros()
{
	if (indiceLivro > 0)
	{
		int id;

		cout << "Digite a identificao do livro: ";
		cin >> id;

		int posicao = buscarLivro(id);

		if (posicao != -1)
		{
			cout << "Identificacao: " << livros[posicao].idLivro << " | Titulo: " << livros[posicao].titulo << " | Autor: " << livros[posicao].autor << " | Genero: " << livros[posicao].genero;

			if (livros[posicao].disponivel == 1)
			{
				cout << " | Disponibilidade: Disponivel" << endl << endl;
			}
			else
			{
				cout << " | Disponibilidade: indisponivel" << endl << endl;
			}
		}
		else
		{
			cout << "Livro não cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de livros vazio."<< endl;
	}
}

void consultaClientes()
{
	if (indiceCliente > 0)
	{
		int id;

		cout << "Digite o cpf do cliente: ";
		cin >> id;

		int posicao = buscarCliente(id);

		if (posicao != -1)
		{
			cout << "CPF: " << clientes[posicao].cpf << " | Nome: " << clientes[posicao].nome << endl << endl;
		}
		else
		{
			cout << "Cliente não cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de clientes vazio." << endl;
	}
}

void consultaAlugueis()
{
	if (indiceAluguel> 0)
	{
		int id;

		cout << "Digite a identificacao do aluguel: ";
		cin >> id;

		int posicao = buscarAluguel(id);

		if (posicao != -1)
		{
			cout << "Id: " << alugueis[posicao].idAluguel << " | Id Livro: " << alugueis[posicao].idLivro << " | CPF Cliente: " << alugueis[posicao].cpfCliente
				<< " | Aluguel: " << alugueis[posicao].dataAluguel.tm_mday << "/" << alugueis[posicao].dataAluguel.tm_mon + 1 << "/" << alugueis[posicao].dataAluguel.tm_year + 1900
				<< " | Devolucao: " << alugueis[posicao].dataDevolucao.tm_mday << "/" << alugueis[posicao].dataDevolucao.tm_mon + 1 << "/" << alugueis[posicao].dataDevolucao.tm_year + 1900;

			if (alugueis[posicao].devolvido == false)
			{
				cout << " | Status: " << "Nao devolvido" << endl << endl;
			}
			else
			{
				cout << " | Status: " << "Devolvido" << endl << endl;
			}
		}
		else
		{
			cout << "Aluguel não cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de alugueis vazio." << endl;
	}
}

void consulta()
{
	do
	{
		cout << "-------------------------------" << endl;
		cout << "         CONSULTA" << endl;
		cout << "-------------------------------" << endl;

		cout << "1. Consultar livros" << endl
			<< "2. Consultar clientes" << endl
			<< "3. Consultar alugueis" << endl
			<< "0. Voltar " << endl
			<< "Digite uma das opcoes acima: " << endl;
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			consultaLivros();
			break;
		case 2:
			consultaClientes();
			break;
		case 3:
			consultaAlugueis();
			break;
		case 0:
			cout << "Voltando..." << endl;
			menu();
			break;
		default:
			cout << "Opcao invalida do menu." << endl;
			break;
		}
	} while (opcao != 0);
}

void efetuarAluguel()
{
	int id;
	int idLivro;
	int cpfCliente;\

	if (indiceAluguel < 100)
	{
		cout << "Digite a identificacao do aluguel: ";
		cin >> id;

		if (buscarAluguel(id) == -1)
		{
			cout << "Digite o id do livro: ";
			cin >> idLivro;

			if (buscarLivro(idLivro) != -1)
			{
				if (livros[buscarLivro(idLivro)].disponivel == 1)
				{
					cout << "Digite o cpf do cliente: ";
					cin >> cpfCliente;

					if (buscarCliente(cpfCliente )!= -1)
					{
						alugueis[indiceAluguel].idAluguel = id;
						alugueis[indiceAluguel].idLivro = idLivro;
						alugueis[indiceAluguel].cpfCliente = cpfCliente;

						time_t agora = time(nullptr);
						localtime_s(&alugueis[indiceAluguel].dataAluguel, &agora);

						alugueis[indiceAluguel].dataDevolucao = alugueis[indiceAluguel].dataAluguel;
						alugueis[indiceAluguel].dataDevolucao.tm_mday += 7;
                        mktime(&alugueis[indiceAluguel].dataDevolucao);

						clientes[buscarCliente(cpfCliente)].totalAlugueis++;
						livros[buscarLivro(idLivro)].totalAlugeis++;
						livros[buscarLivro(idLivro)].disponivel = false;

						cout << "Alguel efetuado com sucesso!" << endl;

						cout << "Data de devolucao: "<< alugueis[indiceAluguel].dataDevolucao.tm_mday << "/" << alugueis[indiceAluguel].dataDevolucao.tm_mon + 1 << "/" << alugueis[indiceAluguel].dataDevolucao.tm_year + 1900 << endl;

						indiceAluguel++;
					}
					else
					{
						cout << "Cliente não cadastrado no sistema!" << endl;
					}
				}
				else
				{
					cout << "O livro esta alugado" << endl;
				}
			}
			else
			{
				cout << "Livro não cadastrado no sistema!" << endl;
			}
		}
		else
		{
			cout << "Aluguel ja cadastrado no sistema!" << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de alugueis cheio!"<< endl;
	}
}

void devolucao()
{
	if (indiceAluguel > 0)
	{
		int id;

		cout << "Digite a identificacao do aluguel: ";
		cin >> id;

		if (buscarAluguel(id) != -1)
		{
			if (alugueis[buscarAluguel(id)].devolvido == false)
			{
				alugueis[buscarAluguel(id)].devolvido = true;

				livros[buscarLivro(alugueis[buscarAluguel(id)].idLivro)].disponivel = true;

				cout << "Devolucao efetuada com sucesso!" << endl;
			}
			else
			{
				cout << "Devolucao ja feita no sistema." << endl;
			}
		}
		else
		{
			cout << "Aluguel não efetuado no sistema." << endl;
		}

	}
	else
	{
		cout << "Sistema de cadastro de alugueis vazio." << endl;
	}
}

void relatorioTodosLivros()
{
	if (indiceLivro > 0)
	{
		for (int i = 0; i < indiceLivro; i++)
		{
			cout << "Identificacao: " << livros[i].idLivro << " | Titulo: " << livros[i].titulo << " | Autor: " << livros[i].autor << " | Genero: " << livros[i].genero;

			if (livros[i].disponivel == 1)
			{
				cout << " | Disponibilidade: Disponivel" << endl << endl;
			}
			else
			{
				cout << " | Disponibilidade: indisponivel" << endl << endl;
			}
		}
	}
	else
	{
		cout << "Sistema de cadastro de livros vazio." << endl;
	}
}

void relatorioTodosClientes()
{
	if (indiceCliente > 0)
	{
		for (int i = 0; i < indiceCliente; i++)
		{
			cout << "CPF: " << clientes[i].cpf << " | Nome: " << clientes[i].nome << endl << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de clientes vazio." << endl;
	}
}

void relatorioTodosAlugueis()
{
	if (indiceAluguel > 0)
	{
		for (int i = 0; i < indiceAluguel; i++)
		{
			cout << "Id: " << alugueis[i].idAluguel << " | Id Livro: " << alugueis[i].idLivro << " | CPF Cliente: " << alugueis[i].cpfCliente
				<< " | Aluguel: " << alugueis[i].dataAluguel.tm_mday << "/" << alugueis[i].dataAluguel.tm_mon + 1 << "/" << alugueis[i].dataAluguel.tm_year + 1900
				<< " | Devolucao: " << alugueis[i].dataDevolucao.tm_mday << "/" << alugueis[i].dataDevolucao.tm_mon + 1 << "/" << alugueis[i].dataDevolucao.tm_year + 1900;

			if (alugueis[i].devolvido == false)
			{
				cout << " | Status: " << "Nao devolvido" << endl << endl;
			}
			else
			{
				cout << " | Status: " << "Devolvido" << endl << endl;
			}
		}
	}
	else
	{
		cout << "Sistema de cadastro de clientes vazio." << endl;
	}
}

void relatorioDevolucoesAtrasadas()
{
	if (indiceAluguel > 0)
	{
		bool existe = false;

		time_t agora = time(nullptr);
		tm dataAtual;
		localtime_s(&dataAtual, &agora);
	
		for (int i = 0; i < indiceAluguel; i++)
	    {
			if (alugueis[i].devolvido == false)
			{
				if (mktime(&alugueis[i].dataDevolucao) < agora)
				{
					existe = true;

					cout << "ID Aluguel: " << alugueis[i].idAluguel << " | ID Livro: " << alugueis[i].idLivro << " | CPF Cliente: " << alugueis[i].cpfCliente 
						<< " | Data de devolução prevista: " << alugueis[i].dataDevolucao.tm_mday << "/" << alugueis[i].dataDevolucao.tm_mon + 1 << "/" << alugueis[i].dataDevolucao.tm_year + 1900 << endl;

				}
		    }
	    }

		if (existe == false)
		{
			cout << "Nao foi encontrada devolucoes atrasadas no sistema." << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de alugueis vazio" << endl;
	}
}

void relatorio()
{
	do
	{
		cout << "-------------------------------" << endl;
		cout << "       RELATORIOS" << endl;
		cout << "-------------------------------" << endl;

		cout << "1. Listar Livros" << endl
			<< "2. Listar Clientes" << endl
			<< "3. Listar alugueis" << endl
			<< "4. Devolucoes atrasadas" << endl
			<< "0. Voltar " << endl
			<< "Digite uma das opcoes acima: " << endl;
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			relatorioTodosLivros();
			break;
		case 2:
			relatorioTodosClientes();
			break;
		case 3:
			relatorioTodosAlugueis();
			break;
		case 4:
			relatorioDevolucoesAtrasadas();
			break;
		case 0:
			cout << "Voltando..." << endl;
			menu();
			break;
		default:
			cout << "Opcao invalida do menu." << endl;
			break;
		}
	} while (opcao != 0);
}

void deletarLivro()
{
	if (indiceLivro > 0)
	{
		int idLivro;

		cout << "Digite a identificacao do livro: ";
		cin >> idLivro;

		if (buscarLivro(idLivro) != -1)
		{
			for (int i = buscarLivro(idLivro); i < indiceLivro; i++)
			{
				livros[i] = livros[i + 1];
			}

			livros[indiceLivro - 1].idLivro = 0;
			livros[indiceLivro - 1].titulo[0] = '\0';
			livros[indiceLivro - 1].autor[0] = '\0';
			livros[indiceLivro - 1].genero[0] = '\0';
			livros[indiceLivro - 1].totalAlugeis = 0;
			livros[indiceLivro - 1].disponivel = true;

			indiceLivro--;

			cout << "Livro deletado do sistema com sucesso!" << endl;
		}
		else
		{
			cout << "Livro não cadastrado no sistema." << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de livros vazio." << endl;
	}
}

void deletarCliente()
{
	if (indiceCliente > 0)
	{
		int cpf;

		cout << "Digite a identificacao do cliente: ";
		cin >> cpf;

		if (buscarCliente(cpf) != -1)
		{
			for (int i = buscarCliente(cpf); i < indiceCliente; i++)
			{
				clientes[i] = clientes[i + 1];
			}

			clientes[indiceCliente - 1].cpf = 0;
			clientes[indiceCliente - 1].nome[0] = '\0';
			clientes[indiceCliente - 1].totalAlugueis = 0;

			indiceCliente--;

			cout << "Cliente deletado do sistema com sucesso!" << endl;
		}
		else
		{
			cout << "Cliente não cadastrado no sistema." << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de clientes vazio." << endl;
	}
}

void deletarAluguel()
{
	if (indiceAluguel > 0)
	{
		int id;

		cout << "Digite a identificacao do aluguel: ";
		cin >> id;

		if (buscarAluguel(id) != -1)
		{
			int c = buscarCliente(alugueis[buscarAluguel(id)].cpfCliente);

			if (c != -1)
			{
				clientes[c].totalAlugueis--;
			}

			int l = buscarLivro(alugueis[buscarAluguel(id)].idLivro);

			if (l != -1)
			{
				livros[l].totalAlugeis--;
			}

			for (int i = buscarAluguel(id); i < indiceAluguel; i++)
			{
				alugueis[i] = alugueis[i + 1];
			}

			alugueis[indiceAluguel - 1].idAluguel = 0;
			alugueis[indiceAluguel - 1].idLivro = 0;
			alugueis[indiceAluguel - 1].cpfCliente = 0;
			alugueis[indiceAluguel - 1].dataAluguel = {};
			alugueis[indiceAluguel - 1].dataDevolucao = {};
			alugueis[indiceAluguel - 1].devolvido = false;

			indiceAluguel--;

			cout << "Aluguel deletado do sistema com sucesso!" << endl;
		}
		else
		{
			cout << "Aluguel não cadastrado no sistema." << endl;
		}
	}
	else
	{
		cout << "Sistema de cadastro de alugueis vazio." << endl;
	}
}

void deletar()
{
	do
	{
		cout << "-------------------------------" << endl;
		cout << "         DELETAR" << endl;
		cout << "-------------------------------" << endl;

	   cout << "1. Deletar livro" << endl
			<< "2. Deletar cliente" << endl
			<< "3. Deletar aluguel" << endl
			<< "0. Voltar " << endl
			<< "Digite uma das opcoes acima: " << endl;
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			deletarLivro();
			break;
		case 2:
			deletarCliente();
			break;
		case 3:
			deletarAluguel();
			break;
		case 0:
			cout << "Voltando..." << endl;
			menu();
			break;
		default:
			cout << "Opcao invalida do menu." << endl;
			break;
		}
	} while (opcao != 0);
}

void salvarArquivo()
{
	ofstream arquivo("Relatorio_Livraria.txt");

	if (!arquivo)
	{
		cout << "Erro ao abrir o arquivo" << endl;
	}
	    arquivo << "-----------------------------" << endl;
	    arquivo << endl<< "   LIVROS" << endl<<endl;
		arquivo << "-----------------------------" << endl;

	for (int i = 0; i < indiceLivro; i++)
	{
		arquivo << "Identificacao: " << livros[i].idLivro << endl;
		arquivo << "Titulo: " << livros[i].titulo << endl;
		arquivo << "Autor: " << livros[i].autor << endl;
		arquivo << "Genero: " << livros[i].autor << endl;
		arquivo << "Quantidade de alugueis: " << livros[i].totalAlugeis << endl;

		if (livros[i].disponivel == true)
		{
			arquivo << "Disponibilidade: Disponivel " << endl;
			arquivo << "-----------------------------" << endl;
		}
		else
		{
			arquivo << "Disponibilidade: Indisponivel " << endl;
			arquivo << "-----------------------------" << endl;
		}
	}

	    arquivo << endl<<"    Clientes" << endl<< endl;
		arquivo << "-----------------------------" << endl;

	for (int i = 0; i < indiceCliente; i++)
	{
		arquivo << "CPF: " << clientes[i].cpf << endl;
		arquivo << "Nome: " << clientes[i].nome << endl;
		arquivo << "Quantidade de alugueis: " << clientes[i].totalAlugueis << endl;
		arquivo << "-----------------------------" << endl;
	}

	    arquivo <<endl<< "    Alugueis" << endl << endl;
		arquivo << "-----------------------------" << endl;

	for (int i = 0; i < indiceAluguel; i++)
	{
		arquivo << "Identificacao: " << alugueis[i].idAluguel << endl;
		arquivo << "Id livro: " << alugueis[i].idLivro << endl;
		arquivo << "CPF cliente: " << alugueis[i].cpfCliente << endl;
		arquivo << "Data do aluguel: " << alugueis[i].dataAluguel.tm_mday << "/" << alugueis[i].dataAluguel.tm_mon + 1 << "/" << alugueis[i].dataAluguel.tm_year + 1900 << endl;
		arquivo << "Data de devolucao: " << alugueis[i].dataDevolucao.tm_mday << "/" << alugueis[i].dataDevolucao.tm_mon + 1 << "/" << alugueis[i].dataDevolucao.tm_year + 1900 << endl;

		if (alugueis[i].devolvido == true)
		{
			arquivo << "Devolucao: Devolvido " << endl;
			arquivo << "-----------------------------" << endl;
		}
		else
		{
			arquivo << "Devolucao: Nao devolvido " << endl;
			arquivo << "-----------------------------" << endl;
		}
	}
	

	arquivo.close();

	cout << "Arquivo de texto salvo com sucesso!" << endl;
}

void menu()
{
	do
	{
		cout << "-------------------------------" << endl;
		cout << "       MENU PRINCIPAL" << endl;
		cout << "-------------------------------" << endl;

		cout << "1. Cadastro" << endl
			 << "2. Consulta" << endl
			 << "3. Aluguel" << endl
			 << "4. Devolucao" << endl
			 << "5. Relatorios" << endl
			 << "6. Deletar" << endl
			 << "7. Salvar arquivo de texto" << endl
			 << "0. Sair " << endl
			 << "Digite uma das opcoes acima: " << endl;
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			cadastro();
			break;
		case 2:
			consulta();
			break;
		case 3:
			efetuarAluguel();
			break;
		case 4:
			devolucao();
			break;
		case 5:
			relatorio();
			break;
		case 6:
			deletar();
			break;
		case 7:
			salvarArquivo();
			break;
		case 0:
			cout << "Volte sempre! Saindo..." << endl;
			break;
		default:
			cout << "Opcao invalida do menu." << endl;
			break;
		}
	} while (opcao != 0);
}

int main() {

	while (opcao != 0)
	{
		menu();
	}

	return 0;
}
