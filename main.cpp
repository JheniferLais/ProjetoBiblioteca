#include <iostream>
#include <string.h>
#include <locale.h>
#include <ctype.h> // para o isdigit() e isalpha()

using namespace std;

/*
- JHENIFER LAÍS BARBOSA 24014979
- JOÃO PEDRO DUARTE GIATTI 24019083
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
void consultaDeLivros(Biblioteca livro[100]){
	int comandoCDL;
    bool continuar = true;

    while(continuar){
        cout << "CONSULTA DE LIVROS" << endl;
        cout << "------------------" << endl;
        cout << "[1]. Listar todos os Livros" << endl;
        cout << "[2]. Buscar livro" << endl;
        cout << "[3]. Cancelar" << endl;
        cin >> comandoCDL;

        if(comandoCDL == 1){
            // LISTAR TODOS OS LIVROS
            if(livroIndex == -1) {
                cout << "Nenhum livro cadastrado!" << endl;
            } else {
                for(int i = 0; i <= livroIndex; i++){
                    cout << "Livro " << i+1 << ": " << endl;
                    cout << "ID: " << livro[i].id << endl;
                    cout << "Título: " << livro[i].titulo << endl;
                    cout << "Autor: " << livro[i].autor << endl;
                    cout << "Número de Páginas: " << livro[i].paginas << endl;
                    cout << "Estoque: " << livro[i].estoque << endl;
                    cout << "------------------" << endl;
                }
            }
        } else if(comandoCDL == 2){
            // BUSCAR LIVRO POR TITULO OU ID
            bool encontrado = false;
            int i = 0;
            int isNumeric = 1;
            char buscaTituloId[100];
            cout << "Digite o Título ou o ID do livro: ";
            cin >> buscaTituloId;
            
            // VERIFICAÇÃO DE ENTRADA NÚMERICA (titulo ou id)
            while (buscaTituloId[i] != '\0') {
                if (!isdigit(buscaTituloId[i])) {
                    isNumeric = 0;
                    break;
                }
                i++;
            }
            
            if (isNumeric) {
                // BUSCA POR ID
                for (int k = 0; k <= livroIndex; k++) {
                    char idString[10]; // controle para armazenar o ID como string
                    sprintf(idString, "%d", livro[k].id); // converte int para string
                
                    if (strcmp(idString, buscaTituloId) == 0) {
                        cout << "Livro Encontrado!:\n";
                        cout << "ID: " << livro[k].id << endl;
                        cout << "Título: " << livro[k].titulo << endl;
                        cout << "Autor: " << livro[k].autor << endl;
                        cout << "Número de Páginas: " << livro[k].paginas << endl;
                        cout << "Estoque: " << livro[k].estoque << endl;
                        cout << "------------------" << endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "Livro não encontrado por ID.\n";
                }
            } else {
                // BUSCA POR TITULO
                for (int k = 0; k <= livroIndex; k++) {
                    if (strcmp(livro[k].titulo, buscaTituloId) == 0) {
                        cout << "Livro Encontrado!:\n";
                        cout << "ID: " << livro[k].id << endl;
                        cout << "Título: " << livro[k].titulo << endl;
                        cout << "Autor: " << livro[k].autor << endl;
                        cout << "Número de Páginas: " << livro[k].paginas << endl;
                        cout << "Estoque: " << livro[k].estoque << endl;
                        cout << "------------------" << endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "Livro não encontrado por título.\n";
                }
            }
        } else if(comandoCDL == 3){
            continuar = false;
        }
    }
}

int main(){
	setlocale(LC_ALL, "Portuguese");
    Biblioteca livro[100]; //ARRAY QUE GUARDA AS INFORMAÃ‡OES COM TODOS OS LIVROS(max de 100 livros)
    //
    int opcao = 1;
    //
    while(opcao >= 1 && opcao <= 6){
        cout << "SISTEMA BIBLIOTECA" << endl;
        cout << "------------------" << endl;
        cout << "[1]. CADASTRO DE LIVROS" << endl;
        cout << "[2]. CONSULTA DE LIVROS" << endl;
        cout << "[3]. EMPRÃ‰STIMO DE LIVROS" << endl;
        cout << "[4]. DEVOLUÃ‡ÃƒO DE LIVROS" << endl;
        cout << "[5]. REMOÃ‡ÃƒO DE LIVROS" << endl;
        cout << "[6]. SAIR DO SISTEMA" << endl;
        cout << "OPCAO: ";
        //
        cin >> opcao;
        //
        if(opcao == 1){ //CADASTRO DE LIVROS
            cadastroDeLivros(livro);
        }
        else if(opcao == 2){ //CONSULTA DE LIVROS
            consultaDeLivros(livro);
        }
        else if(opcao == 3){ //EMPRÃ‰STIMO DE LIVROS
            //emprestimoDeLivros();
        }
        else if(opcao == 4){ //DEVOLUÃ‡ÃƒO DE LIVROS
            //devolucaoDeLivros();
        }
        else if(opcao == 5){ //REMOÃ‡ÃƒO DE LIVROS
            //remocaoDeLivros();
        }
        else if(opcao == 6){
            cout << "SAINDO DO SISTEMA... OBRIGADO POR UTILIZAR NOSSO SISTEMA";
        }
    }

    return 0;
}
