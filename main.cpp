#include <iostream>
#include <string.h> // NOLINT(*-deprecated-headers)
using namespace std;

//Jhenifer Lais Barbosa 24014979
//João Pedro Duarte Giatti 24019083
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

int livroIndex = -1; //Controla o índice no array biblioteca
Livro biblioteca[100]; //Array que guarda as informações de todos os livros (máximo de 100 livros)

//Função para imprimir o cabeçalho do sistema
void printSistemaBiblioteca(){
    cout << "-----------------------------------------" << endl;
    cout << "\tSISTEMA BIBLIOTECA   " << endl;
    cout << "-----------------------------------------" << endl;
}
//Função para imprimir os detalhes de um livro
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

//Função para realizar cadastro de livros
void cadastroDeLivros(){
    //Inicializando as variáveis
    int id;
    char autor[100];
    char titulo[100];
    int paginas, ano, estoque;

    printSistemaBiblioteca();
    cout << "DIGITE O CODIGO DO LIVRO: ";
    cin >> id;

    //Verifica se o ID já existe
    for (int i = 0; i <= livroIndex; i++) {
        if (biblioteca[i].id == id) {
            cout << "\tFALHA NO CADASTRO: ID já cadastrado!" << endl;
            return;
        }
    }

    //Pegando os inputs das variáveis
    cout << "DIGITE O NOME DO AUTOR DO LIVRO: ";
    cin.ignore();
    cin.getline(autor, 100);
    cout << "DIGITE O TITULO DO LIVRO: ";
    cin.getline(titulo, 100);
    cout << "DIGITE A QUANTIDADE DE PAGINAS DO LIVRO: ";
    cin >> paginas;
    cout << "DIGITE O ANO DE PUBLICACAO DO LIVRO: ";
    cin >> ano;
    cout << "DIGITE A QUANTIDADE EM ESTOQUE DO LIVRO (min 1, max 10): ";
    cin >> estoque;

    //Verificação de estoque
    if (estoque < 1 || estoque > 10) {
        cout << "FALHA NO CADASTRO: Quantidade de estoque invalida!" << endl;
        return;
    }

    //Verificação para não exceder o limite
    if (livroIndex > 99){
        cout << "FALHA NO CADASTRO: Limite de livros excedido!" << endl;
        return;
    }

    //Adicionando o livro à biblioteca
    livroIndex++;
    biblioteca[livroIndex].id = id;
    strcpy(biblioteca[livroIndex].autor, autor);
    strcpy(biblioteca[livroIndex].titulo, titulo);
    biblioteca[livroIndex].paginas = paginas;
    biblioteca[livroIndex].ano = ano;
    biblioteca[livroIndex].estoque = estoque;

    //Inicializando os registros de empréstimos
    for (int i = 0; i < 10; i++) {
        strcpy(biblioteca[livroIndex].emprestimos[i], "");
    }
    cout << "Livro cadastrado com sucesso!" << endl;
}

//fun��o para realizar consulta de livros
void consultaDeLivros(){
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
        cin >> comandoCDL;

        if(comandoCDL == 1){ //Lista todos os livros
            for(int i = 0; i <= livroIndex; i++){
                printLivro(i);
            }
            continuar = false;

        } else if(comandoCDL == 2){ //Lista o livro baseado em id ou titulo
            bool encontrado = false;
            int i = 0;
            int isNumeric = 1;
            char buscaTituloId[100];
            cout << "DIGITE O TITULO OU ID PARA A CONSULTA: ";
            cin.ignore();
            cin.getline(buscaTituloId, 100);

            //Verificação de entrada numerica (titulo ou id)
            while (buscaTituloId[i] != '\0') {
                if (!isdigit(buscaTituloId[i])) {
                    isNumeric = 0;
                    break;
                }
                i++;
            }

            if (isNumeric) { //Lista baseado em id
                for (int k = 0; k <= livroIndex; k++) {
                    char idString[10]; //Controle para armazenar o id como string
                    sprintf(idString, "%d", biblioteca[k].id); //Converte int para string

                    if (strcmp(idString, buscaTituloId) == 0) {
                        printLivro(k);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "FALHA NA CONSULTA: Livro não encontrado por ID!" << endl;
                }

            } else { //Lista baseado em titulo
                for (int k = 0; k <= livroIndex; k++) {
                    if (strcmp(biblioteca[k].titulo, buscaTituloId) == 0) {
                        printLivro(k);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "FALHA NA CONSULTA: Livro não encontrado por titulo!" << endl;
                }
            }

        } else if(comandoCDL == 3){
            continuar = false;
        }
    }
}

//Função para realizar empréstimo de livros
void emprestimoDeLivros(){
    if (livroIndex == -1) {
        cout << "FALHA NO EMPRESTIMO: Nao ha livros cadastrados!" << endl;
        return;
    }

    //Inicializando as variáveis
    int cod;
    char nome[100];

    printSistemaBiblioteca();
    cout << "DIGITE O CODIGO DO LIVRO PARA O EMPRESTIMO: ";
    cin >> cod;

    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id && biblioteca[i].estoque > 0) {
            printLivro(i);
            cout << "DIGITE SEU NOME PARA O EMPRESTIMO: ";
            cin.ignore();
            cin.getline(nome, 100);

            for (int j = 0; j < 10; j++) {
                if (strlen(biblioteca[i].emprestimos[j]) == 0) {
                    strcpy(biblioteca[i].emprestimos[j], nome);
                    biblioteca[i].estoque--;
                    cout << "Livro emprestado com sucesso!" << endl;
                    return;
                }
            }
            cout << "FALHA NO EMPRESTIMO: Sem estoque!" << endl;
            return;
        }
    }
    cout << "FALHA NO EMPRESTIMO: Livro nao encontrado ou sem estoque!" << endl;
}

//Função para realizar devolução de livros
void devolucaoDeLivros() {
    if (livroIndex == -1) {
        cout << "FALHA NA DEVOLUCAO: Nao ha livros cadastrados!" << endl;
        return;
    }

    //Inicializando as variáveis
    int cod;
    char nome[100];
    bool idEncontrado = false;
    bool emEncontrado = false;

    printSistemaBiblioteca();
    cout << "DIGITE O CODIGO DO LIVRO PARA A DEVOLUCAO: ";
    cin >> cod;

    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id) {  //Procura o codigo inserido
            idEncontrado = true;
            cout << "DIGITE SEU NOME PARA A DEVOLUCAO: ";
            cin.ignore();
            cin.getline(nome, 100);

            for (int j = 0; j < 10; j++) {
                if (strcmp(nome, biblioteca[i].emprestimos[j]) == 0) {  //Verifica se o nome está nos empréstimos
                    emEncontrado = true;
                    biblioteca[i].estoque++;  //Aumenta o estoque

                    //Remove o nome do empréstimo
                    for (int k = j; k < 9; k++) {  //Faz a remoção do nome nos emprestimos
                        strcpy(biblioteca[i].emprestimos[k], biblioteca[i].emprestimos[k + 1]);
                    }

                    //Limpa o último empréstimo
                    strcpy(biblioteca[i].emprestimos[9], "");

                    cout << "Livro devolvido com sucesso!" << endl;
                    break;
                }
            }

            if (!emEncontrado) {
                cout << "FALHA NA DEVOLUCAO: Livro sem emprestimos para esse nome!" << endl;
            }
            break;
        }
    }
    if (!idEncontrado) {
        cout << "FALHA NA DEVOLUCAO: Livro nao encontrado!" << endl;
    }
}

//Função para realizar remoção de livros
void remocaoDeLivros() {
    if (livroIndex == -1) {
        cout << "FALHA NA REMOCAO: Nao ha livros cadastrados!" << endl;
        return;
    }

    int cod;
    bool encontrado = false;
    printSistemaBiblioteca();
    cout << "DIGITE O CODIGO DO LIVRO PARA REMOCAO: ";
    cin >> cod;

    for (int i = 0; i <= livroIndex; i++) {
        if (cod == biblioteca[i].id) {  // Procura o codigo inserido
            encontrado = true;
            for (int j = i; j < livroIndex; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            livroIndex--; //Reduz o índice dos livros cadastrados
            cout << "Livro removido com sucesso!" << endl;
            break;
        }
    }
    //
    if (!encontrado) {
        cout << "FALHA NA REMOCAO: Livro nao encontrado!" << endl;
    }
}

//Função principal que exibe o menu do sistema
int main() {
    int opcao = 1;
    while (opcao >= 1 && opcao <= 6) {
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

        if (opcao == 1) { //CADASTRO DE LIVROS
            cadastroDeLivros();
        } else if (opcao == 2) { //CONSULTA DE LIVROS
            consultaDeLivros();
        } else if (opcao == 3) { //EMPRÉSTIMO DE LIVROS
            emprestimoDeLivros();
        } else if (opcao == 4) { //DEVOLUÇÃO DE LIVROS
            devolucaoDeLivros();
        } else if (opcao == 5) { //REMOÇÃO DE LIVROS
            remocaoDeLivros();
        } else {
            cout << "SAINDO DO SISTEMA... OBRIGADO POR UTILIZAR NOSSO SISTEMA";
            break;
        }
    }
    return 0;
}
