#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <ws2tcpip.h>
#include <cstring>
int main() {
WSADATA wsaData;
SOCKET clientSocket = INVALID_SOCKET;
struct sockaddr_in serverAddress;
const char* hello = "Hello from client";
char buffer[1024] = {0};
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
std::cerr << "Falha na inicialização do Winsock" << std::endl;
return -1;
}
/* Criando o socket*/
if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
std::cerr << "Falha na criação do socket" << std::endl;
WSACleanup();
return -1;
}
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = inet_addr("192.16.8.1.21");
if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
std::cerr << "Erro na conexão com o servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
return -1;
}
if (send(clientSocket, hello, strlen(hello), 0) < 0) {
std::cerr << "Erro no envio de dados ao servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
return -1;
}
if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
std::cerr << "Erro na recepção da resposta do servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
return -1;
}
std::cout << "Resposta do servidor: " << buffer << std::endl;
closesocket(clientSocket);
WSACleanup();
return 0;
}