#include <iostream>
#include <string.h>
#include <locale.h>

using namespace std;

/*
- JHENIFER LA�S BARBOSA 24014979
- JO�O PEDRO DUARTE GIATTI 24019083
*/

struct Biblioteca{
    int id;
    char autor[100];
    char titulo[100];
    int paginas;
    int ano;
    int estoque;
    //emprestimos; NOME DAS PESSOAS QUE EMPRESTARAM O LIVRO
};
//
int livroIndex = -1; //VARIAVEL PARA CONTROLAR O INDICE NO ARRAY BIBLIOTECA(Banco de Dados)
//
void cadastroDeLivros(Biblioteca livro[100]){
    //INICIALIZANDO AS VARIAVEIS
    int id;
    char autor[100];
    char titulo[100];
    int paginas;
    int ano;
    int estoque;
    //PEGANDO OS INPUTS DAS VARIAVEIS
    cout << "DIGITE O CODIGO DO LIVRO: ";
    cin >> id;
    cout << "DIGITE O NOME DO AUTOR DO LIVRO: ";
    cin >> autor;
    cout << "DIGITE O TITULO DO LIVRO: ";
    cin >> titulo;
    cout << "DIGITE A QUANTIDADE DE PAGINAS DO LIVRO: ";
    cin >> paginas;
    cout << "DIGITE O ANO DE PUBLICACAO DO LIVRO: ";
    cin >> ano;
    cout << "DIGITE A QUANTIDADE EM ESTOQUE DO LIVRO(min 1, max 10): ";
    cin >> estoque;
    //VERIFICAÇÃO DE ESTOQUE
    if (estoque > 10 || estoque < 1) {
        cout << "QUANTIDADE INVALIDA!!!" << endl << "LIVRO NAO CADASTRADO";
    }
    else {
        if(livroIndex < 100){
            livroIndex++;
            //
            livro[livroIndex].id = id;
            strcpy(livro[livroIndex].autor, autor);
            strcpy(livro[livroIndex].titulo, titulo);
            livro[livroIndex].paginas = paginas;
            livro[livroIndex].ano = ano;
            livro[livroIndex].estoque = estoque;
        }
        else{
            cout << "FALHA NO CADASTRO";
            cout << "QUANTIDADE DE LIVROS CADASTRADOS EXCEDIDA";
        }
    }
}
//
void consultaDeLivros(){
	int comandoCDL = 1;
	cout << "CONSULTA DE LIVROS" << endl;
    cout << "------------------" << endl;
    cout << "[1]. Listar todos os Livros" << endl;
    cout << "[2]. Buscar livro" << endl;
    cout << "[3]. Cancelar" << endl;
    cin >> comandoCDL;
    while(true){
	    if(comandoCDL == 1){
	    	for(int i = 0; i < livroIndex; i++){
	    		cout << "Livro " << livroIndex << endl;
			}
		}else if(comandoCDL == 2){
			
		}else if(comandoCDL == 3){
			break;
		}
	}
}
int main(){
	setlocale(LC_ALL, "Portuguese");
    Biblioteca livro[100]; //ARRAY QUE GUARDA AS INFORMAÇOES COM TODOS OS LIVROS(max de 100 livros)
    //
    int opcao = 1;
    //
    while(opcao >= 1 && opcao <= 6){
        cout << "SISTEMA BIBLIOTECA" << endl;
        cout << "------------------" << endl;
        cout << "[1]. CADASTRO DE LIVROS" << endl;
        cout << "[2]. CONSULTA DE LIVROS" << endl;
        cout << "[3]. EMPRÉSTIMO DE LIVROS" << endl;
        cout << "[4]. DEVOLUÇÃO DE LIVROS" << endl;
        cout << "[5]. REMOÇÃO DE LIVROS" << endl;
        cout << "[6]. SAIR DO SISTEMA" << endl;
        cout << "OPCAO: ";
        //
        cin >> opcao;
        //
        if(opcao == 1){ //CADASTRO DE LIVROS
            cadastroDeLivros(livro);
        }
        else if(opcao == 2){ //CONSULTA DE LIVROS
            consultaDeLivros();
        }
        else if(opcao == 3){ //EMPRÉSTIMO DE LIVROS
            //emprestimoDeLivros();
        }
        else if(opcao == 4){ //DEVOLUÇÃO DE LIVROS
            //devolucaoDeLivros();
        }
        else if(opcao == 5){ //REMOÇÃO DE LIVROS
            //remocaoDeLivros();
        }
        else{
            cout << "SAINDO DO SISTEMA... OBRIGADO POR UTILIZAR NOSSO SISTEMA";
        }
    }

    return 0;
}
