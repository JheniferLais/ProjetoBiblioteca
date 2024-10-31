#include <iostream>
#include <string.h> // NOLINT(*-deprecated-headers)
using namespace std;

//Jhenifer Lais Barbosa 24014979
//Joao Pedro Duarte Giatti 24019083
//Jean Yuki Kimura 24008214
//Layra Angeli Campiol 24015714
//Lorenna Lima Barbosa 24006765

struct Livro {
    int id;
    char autor[100];
    char titulo[100];
    int paginas;
    int ano;
    int estoque;
    char emprestimos[10][100];
};

int livroIndex = -1; //Controla indice no array biblioteca
Livro biblioteca[100]; //Array que guarda as informacoes de todos os livros (maximo de 100 livros)

//Funcao para imprimir o cabecalho do sistema
void printSistemaBiblioteca(){
    cout << "-----------------------------------------" << endl;
    cout << "\tSISTEMA BIBLIOTECA   " << endl;
    cout << "-----------------------------------------" << endl;
}

//Funcao para imprimir os detalhes de um livro
void printLivro(int i){
    printSistemaBiblioteca();
    cout << "\tID: " << biblioteca[i].id << endl;
    cout << "\tAUTOR: " << biblioteca[i].autor << endl;
    cout << "\tTITULO: " << biblioteca[i].titulo << endl;
    cout << "\tPAGINAS: " << biblioteca[i].paginas << endl;
    cout << "\tANO: " << biblioteca[i].ano << endl;
    cout << "\tESTOQUE: " << biblioteca[i].estoque << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\tEMPRESTIMOS: " << endl;

    bool semEmprestimos = true;
    for (int j = 0; j < 10; j++) {
        if (strlen(biblioteca[i].emprestimos[j]) > 0) {
            cout << "\t[" << j + 1 << "]: " << biblioteca[i].emprestimos[j] << endl;
            semEmprestimos = false;
        }
    }
    if (semEmprestimos) {
        cout << "\tSem registros de emprestimos." << endl;
    }
    cout << endl;
}

//Funcao para realizar cadastro de livros
void cadastroDeLivros(){

    //Validacao para nao exceder o limite de livros cadastrados
    if (livroIndex > 99){
        cout << "FALHA NO CADASTRO: Limite de livros excedido!" << endl;
        return;
    }

    //Inicializando as variaveis
    int id;
    char autor[100];
    char titulo[100];
    int paginas, ano, estoque;

    //Print do cabecalho do sistema
    printSistemaBiblioteca();

    //Entrada do id e validacao se ja existe
    cout << "DIGITE O CODIGO DO LIVRO: ";
    cin >> id;
    for (int i = 0; i <= livroIndex; i++) {
        if (biblioteca[i].id == id) {
            cout << "\tFALHA NO CADASTRO: ID ja cadastrado!" << endl;
            return;
        }
    }

    //Entrada do nome do autor e validacao do tamanho da string
    cout << "DIGITE O NOME DO AUTOR DO LIVRO(max 100 caracteres): ";
    cin.ignore();
    cin.getline(autor, 100);
    if (strlen(autor) == 0) {
        cout << "FALHA NO CADASTRO: Nome do autor tem tamanho invalido." << endl;
        return;
    }

    //Entrada do titulo e validacao do tamanho da string
    cout << "DIGITE O TITULO DO LIVRO(max 100 caracteres): ";
    cin.getline(titulo, 100);
    if (strlen(titulo) == 0) {
        cout << "FALHA NO CADASTRO: Titulo do livro tem tamanho invalido." << endl;
        return;
    }

    //Entrada da quantidade de paginas e validacao de min
    cout << "DIGITE A QUANTIDADE DE PAGINAS DO LIVRO(min 1): ";
    cin >> paginas;
    if (paginas <= 0) {
        cout << "FALHA NO CADASTRO: Digite um número positivo para as paginas: ";
        return;
    }

    //Entrada de ano de publicacao e validacao de max ano atual
    cout << "DIGITE O ANO DE PUBLICACAO DO LIVRO: ";
    cin >> ano;
    if (ano > 2024) {
        cout << "FALHA NO CADASTRO: Digite um ano valido (menor ou igual a 2024): ";
        return;
    }

    //Entrada de estoque e validacao de quantidade max e min
    cout << "DIGITE A QUANTIDADE EM ESTOQUE DO LIVRO (min 1, max 10): ";
    cin >> estoque;
    if (estoque < 1 || estoque > 10) {
        cout << "FALHA NO CADASTRO: Digite um número entre 1 e 10 para o estoque: ";
        return;
    }

    //Adicionando o livro na biblioteca caso tudo esteja correto
    livroIndex++;
    biblioteca[livroIndex].id = id;
    strcpy(biblioteca[livroIndex].autor, autor);
    strcpy(biblioteca[livroIndex].titulo, titulo);
    biblioteca[livroIndex].paginas = paginas;
    biblioteca[livroIndex].ano = ano;
    biblioteca[livroIndex].estoque = estoque;

    //Inicializando os registros de emprestimos
    for (int i = 0; i < 10; i++) {
        strcpy(biblioteca[livroIndex].emprestimos[i], "");
    }

    //Mensagem de sucesso no cadastro
    cout << "Livro cadastrado com sucesso!" << endl;
}

//funcao para realizar consulta de livros
void consultaDeLivros(){

    //Valida se existe livros cadastrados
    if (livroIndex == -1) {
        cout << "FALHA NA CONSULTA: Nao ha livros cadastrados!" << endl;
        return;
    }

    int comandoCDL;
    bool continuar = true;

    while(continuar){
        printSistemaBiblioteca();
        cout << "\t[1]. CONSULTAR TODOS OS LIVROS" << endl;
        cout << "\t[2]. CONSULTA POR TITULO OU ID" << endl;
        cout << "\t[3]. Cancelar" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "OPCAO: ";
        cin >> comandoCDL;

        //Lista todos os livros
        if(comandoCDL == 1){
            for(int i = 0; i <= livroIndex; i++){
                printLivro(i);
            }
            continuar = false;
        }

        //Lista o livro baseado em id ou titulo
        else if(comandoCDL == 2){
            bool encontrado = false;
            int i = 0;
            int isNumeric = 1;
            char buscaTituloId[100];
            cout << "DIGITE O TITULO OU ID PARA A CONSULTA: ";
            cin.ignore();
            cin.getline(buscaTituloId, 100);

            //Valida de entrada numerica (titulo ou id)
            while (buscaTituloId[i] != '\0') {
                if (!isdigit(buscaTituloId[i])) {
                    isNumeric = 0;
                    break;
                }
                i++;
            }

            //Lista baseado em id
            if (isNumeric) {
                for (int k = 0; k <= livroIndex; k++) {

                    //Controle para armazenar o id como string
                    char idString[10];

                    //Converte int para string
                    sprintf(idString, "%d", biblioteca[k].id);

                    if (strcmp(idString, buscaTituloId) == 0) {
                        printLivro(k);
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "FALHA NA CONSULTA: Livro nao encontrado por ID!" << endl;
                }
            }

            // Lista baseado em titulo
            else {
                //Converte o titulo armazenado para minusculas para comparação
                for (int k = 0; k <= livroIndex; k++) {
                    //Converte o titulo armazenado para minusculas para comparação
                    char tituloArmazenado[100];
                    strcpy(tituloArmazenado, biblioteca[k].titulo);
        
                //Converte para minusculas
                for (int j = 0; tituloArmazenado[j]; j++) {
                    tituloArmazenado[j] = tolower(tituloArmazenado[j]);
                }

                char tituloBuscadoMin[100]; 
                strcpy(tituloBuscadoMin, buscaTituloId);
                for (int j = 0; tituloBuscadoMin[j]; j++) {
                    tituloBuscadoMin[j] = tolower(tituloBuscadoMin[j]);
                }

                if (strcmp(tituloArmazenado, tituloBuscadoMin) == 0) {
                    printLivro(k);
                    encontrado = true;
                    break;
                    }
                }

                if (!encontrado) {
                    cout << "FALHA NA CONSULTA: Livro nao encontrado por titulo!" << endl;
                }
            }
        }

        //Sai da consulta de livros
        else if(comandoCDL == 3){
            continuar = false;
        }

        //Valida se a opcao existe
        else{
            cout << "FALHA NA CONSULTA: Opcao invalida" << endl;
        }
    }
}

//Funcao para realizar emprestimos de livros
void emprestimoDeLivros(){

    //Valida se existe livros cadastrados
    if (livroIndex == -1) {
        cout << "FALHA NO EMPRESTIMO: Nao ha livros cadastrados!" << endl;
        return;
    }

    //Inicializando as variaveis
    int cod;
    char nome[100];

    //Print do cabecalho do sistema
    printSistemaBiblioteca();

    //Entrada do codigo do livro
    cout << "DIGITE O CODIGO DO LIVRO PARA O EMPRESTIMO: ";
    cin >> cod;

    //Procura o livro pelo id fornecido
    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id && biblioteca[i].estoque > 0) {

            //Mostra o livro para o usuario
            printLivro(i);

            //Usuario fornece seu nome para o registro de emprestimos
            cout << "DIGITE SEU NOME PARA O EMPRESTIMO: ";
            cin.ignore();
            cin.getline(nome, 100);

            //Faz a logica de emprestimo (inclui o nome do usuario e retira 1 da quantia em estoque)
            for (int j = 0; j < 10; j++) {
                if (strlen(biblioteca[i].emprestimos[j]) == 0) {
                    strcpy(biblioteca[i].emprestimos[j], nome);
                    biblioteca[i].estoque--;
                    cout << "Livro emprestado com sucesso!" << endl;
                    return;
                }
            }

            //Caso nao tenha livro em estoque
            cout << "FALHA NO EMPRESTIMO: Sem estoque!" << endl;
            return;
        }
    }

    //Caso o livro nao seja encontrado ou nao tenha estoque
    cout << "FALHA NO EMPRESTIMO: Livro nao encontrado ou sem estoque!" << endl;
}

//Funcao para realizar devolucao de livros
void devolucaoDeLivros() {

    //Valida se existe livros cadastrados
    if (livroIndex == -1) {
        cout << "FALHA NA DEVOLUCAO: Nao ha livros cadastrados!" << endl;
        return;
    }

    //Inicializando as variaveis
    int cod;
    char nome[100];
    bool idEncontrado = false;
    bool emEncontrado = false;

    //Print do cabecalho do sistema
    printSistemaBiblioteca();

    //Entrada do codigo do livro
    cout << "DIGITE O CODIGO DO LIVRO PARA A DEVOLUCAO: ";
    cin >> cod;

    //Procura o livro pelo id fornecido
    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id) {
            idEncontrado = true;

            //Usuario fornece seu nome para ser encontrado no registro de emprestimos
            cout << "DIGITE SEU NOME PARA A DEVOLUCAO: ";
            cin.ignore();
            cin.getline(nome, 100);
            if (strlen(nome) == 0) {
                cout << "ENTRADA INVALIDA! Nome para devolucao tem tamanho invalido." << endl;
                return;
            }

            //Valida se o nome esta nos emprestimos
            for (int j = 0; j < 10; j++) {
                if (strcmp(nome, biblioteca[i].emprestimos[j]) == 0) {
                    emEncontrado = true;

                    //Aumenta o estoque
                    biblioteca[i].estoque++;

                    //Remove o nome do emprestimo
                    for (int k = j; k < 9; k++) {
                        strcpy(biblioteca[i].emprestimos[k], biblioteca[i].emprestimos[k + 1]);
                    }

                    //Limpa o ultimo emprestimo
                    strcpy(biblioteca[i].emprestimos[9], "");

                    //Mensagem de sucesso
                    cout << "Livro devolvido com sucesso!" << endl;
                    break;
                }
            }

            //Valida caso nao tenha livros com registros de emprestimos para o nome fornecido pelo usuario
            if (!emEncontrado) {
                cout << "FALHA NA DEVOLUCAO: Livro sem emprestimos para esse nome!" << endl;
            }
            break;
        }
    }

    //Valida caso nao tenha encontrado o livro
    if (!idEncontrado) {
        cout << "FALHA NA DEVOLUCAO: Livro nao encontrado!" << endl;
    }
}

//Funcao para realizar remocao de livros
void remocaoDeLivros() {

    //Valida se existe livros cadastrados
    if (livroIndex == -1) {
        cout << "FALHA NA REMOCAO: Nao ha livros cadastrados!" << endl;
        return;
    }

    //Inicializando as variaveis
    int cod;
    bool encontrado = false;

    //Print do cabecalho do sistema
    printSistemaBiblioteca();

    //Entrada do codigo do livro
    cout << "DIGITE O CODIGO DO LIVRO PARA REMOCAO: ";
    cin >> cod;

    //Procura o livro pelo id fornecido
    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id) {
            encontrado = true;
            bool semEmprestimos = true;

            //Valida se existe emprestimos
		    for (int j = 0; j < 10; j++) {
		        if (strlen(biblioteca[i].emprestimos[j]) > 0) {
		            semEmprestimos = false;
		        }
		    }
            
            //Caso o livro possa ser removido
		    if (semEmprestimos) {

                //Logica de exclusao
		        for (int j = i; j < livroIndex; j++) {
                biblioteca[j] = biblioteca[j + 1];
	            }

                //reduz o indice dos livros cadastrados
	            livroIndex--;

	            cout << "Livro removido com sucesso!" << endl;
	            break;

            //Caso tenha pendencias de emprestimos para o livro
		    } else {
		    	cout << "FALHA NA REMOCAO: O livro esta com pendencias de emprestimos." << endl;
		    	break;
			}
        }
    }

    //Valida caso nao tenha encontrado o livro
    if (!encontrado) {
        cout << "FALHA NA REMOCAO: Livro nao encontrado!" << endl;
    }
}

//Funcao principal que exibe o menu do sistema
int main() {
    int opcao = 1;
    while (opcao != 6) {
        printSistemaBiblioteca();
        cout << "\t[1]. CADASTRO DE LIVROS" << endl;
        cout << "\t[2]. CONSULTA DE LIVROS" << endl;
        cout << "\t[3]. EMPRESTIMO DE LIVROS" << endl;
        cout << "\t[4]. DEVOLUCAO DE LIVROS" << endl;
        cout << "\t[5]. REMOCAO DE LIVROS" << endl;
        cout << "\t[6]. SAIR DO SISTEMA" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "OPCAO: ";
        cin >> opcao;

        //Valida se a opcao existe no menu
        if (opcao < 1 || opcao > 6) {
            cout << "Opcao invalida! Tente novamente." << endl;
            continue;
        }

        else if (opcao == 1) { //CADASTRO DE LIVROS
            cadastroDeLivros();
        } else if (opcao == 2) { //CONSULTA DE LIVROS
            consultaDeLivros();
        } else if (opcao == 3) { //EMPRESTIMO DE LIVROS
            emprestimoDeLivros();
        } else if (opcao == 4) { //DEVOLUCAO DE LIVROS
            devolucaoDeLivros();
        } else if (opcao == 5) { //REMOCAO DE LIVROS
            remocaoDeLivros();
        } else {  // SAIR DO SISTEMA
            cout << "SAINDO DO SISTEMA... OBRIGADO POR UTILIZAR NOSSO SISTEMA" << endl;
        }
    }
    return 0;
}
