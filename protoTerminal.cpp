#include <iostream>
#include <dirent.h>
#include <string.h>

using namespace std;

int main() {
    string current_dir = "./"; // diretório atual
    string command; // comando a ser executado

    while (true) {
        // mostrar o diretório atual como prompt
        cout << current_dir << "$ ";

        // ler o comando do usuário
        getline(cin, command);

        // verificar qual comando foi digitado
        if (command == "cd") {
            // mudar para o diretório raiz
            current_dir = "./";
        } else if (command.substr(0, 3) == "cd ") {
            // extrair o nome do diretório do comando
            string new_dir = command.substr(3);

            // verificar se o diretório existe
            DIR* dir = opendir(new_dir.c_str());
            if (dir) {
                // se existir, mudar para o novo diretório
                current_dir = new_dir + "/";
                closedir(dir);
            } else {
                // se não existir, mostrar uma mensagem de erro
                cout << "bash: cd: " << new_dir << ": No such file or directory" << endl;
            }
        } else if (command == "ls") {
            // listar os arquivos e diretórios no diretório atual
            DIR* dir = opendir(current_dir.c_str());
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL) {
                cout << entry->d_name << endl;
            }
            closedir(dir);
        }
        else if(command == "pwd"){
            //imprimir o caminho do diretorio atual
            char* cwd = new char[PATH_MAX];


            if(getcwd(cwd, PATH_MAX)!= NULL){
                std::cout << cwd << std::endl;
            }else{
                std::cerr << "Error getting current directory" << std::endl;
            }
            delete[] cwd;

        } else {
            // se o comando não for reconhecido, mostrar uma mensagem de erro
            cout << "bash: " << command << ": command not found" << endl;
        }
    }

    return 0;
}
