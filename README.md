# Komodo-poisoner
Komodo Poisoner - criado para fins educacionais e de estudo apenas - é uma aplicação que recebe dados de um payload de monitoramento remoto. 

É um programa estilo RAT (Remote Administration Tool) voltado  a ser utilizado no app terminal Termux Android. 
O software cria um executável para windows e recebe a input do teclado do pc hospedeiro e sua tela em tempo real; 

Desenvolvido em C++, pode ser utilizado tanto em uma distribuição Linux Desktop quanto em um terminal mobile como o Termux.

## Dependências:
**# Ubuntu:** sudo apt-get install mingw-w64 

**#Termux:** pkg install llvm-mingw-w64

## Referências:

**Morning Tech Talk - C++ Coding (Low-Level Keyboard Hook for Windows): https://youtu.be/QIWw0jZqGKA?si=pDTlnEKFph_NosR3**

**Função SetWindowsHookExA (winuser.h): https://learn.microsoft.com/pt-br/windows/win32/api/winuser/nf-winuser-setwindowshookexa**

**Função LowLevelKeyboardProc: https://learn.microsoft.com/pt-br/windows/win32/winmsg/lowlevelkeyboardproc**

**Estrutura KBDLLHOOKSTRUCT (winuser.h): https://learn.microsoft.com/pt-pt/windows/win32/api/winuser/ns-winuser-kbdllhookstruct**

**Função MapVirtualKeyA (winuser.h): https://learn.microsoft.com/pt-pt/windows/win32/api/winuser/nf-winuser-mapvirtualkeya**

**Função UnhookWindowsHookEx (winuser.h): https://learn.microsoft.com/pt-pt/windows/win32/api/winuser/nf-winuser-unhookwindowshookex**

**Referência para detectar telhas com o atalho SHIFT: https://pt.m.wikipedia.org/wiki/Ficheiro:Qwerty_pt_BR-ABNT2.svg**

AINDA EM DESENVOLVIMENTO

# Diário de bordo
## Dia 11: 24/3/2024
### Objetivo: Desenvolver o Keylogger.

### **O que foi feito:**

• Refatorando o código, e dividindo-o em mais arquivos.

• Criação de uma classe para tratamento de erros.


## Dia 10: 20/3/2024
### Objetivo: Desenvolver o Keylogger.

### **O que foi feito:**

• O código começou a ser refatorado para ficar mais legivel e seguir os padrões de Clean Code.

## Dia 9: 26/1/2024
### Objetivo: Desenvolver o Keylogger.

### **O que foi feito:**

• O Key logger agora diferencia teclas maiúsculas e minúsculas detectando o Shift e Caps Lock.

• A conexão foi melhorada permanecendo estável e permitindo envio e recebimento de dados (ainda não está completamente funcional).

## Dia 8: 13/1/2024
### Objetivo: Desenvolver o Keylogger
**Bugs a serem corrigidos:**

• Keylogger somente envia duas capturas ao servidor;

• Builder não compila corretamente o arquivo .exe.

### **O que foi feito:**

• Agora o programa elimina arquivos temporários criados pelo builder.

• O keylogger conta com o melhor método para detectar as teclas pressionadas pelo usuário.

## Dia 7: 11/1/2023
### Objetivo: Desenvolver o Keylogger.
### **O que foi feito:**

• Continuação do desenvolvimento do keylogger para Windows.

## Dia 6: 17/12/2023
### Objetivo: Desenvolver o Keylogger.
### **O que foi feito:**

• Andamento do desenvolvimento do keylogger para windows.

## Dia 5: 16/12/2023
### Objetivo: Desenvolver o Keylogger.
### **O que foi feito:**

• Andamento do desenvolvimento do keylogger para windows.

## Dia 4: 13/12/2023
### Objetivo: Desenvolver o Keylogger.
### **O que foi feito:**

• Andamento do desenvolvimento do keylogger para windows: estudando como capturar as teclas do modo mais eficiente.

## Dia 3: 11/12/2023
### Objetivo: Desenvolver o Keylogger.
### **O que foi feito:**

•	Agora ao terminar a compilação no builder o usuário pode escolher se quer chamar o listener.

•	Foi adicionado um menu de help ao listener.

•	A função de receber o log do teclado diretamente no terminal está pronta do lado do servidor

## Dia 2: 07/12/2023
### Objetivo: Corrigir a função do compilador para funcionar no termux
### **O que foi feito:**

•	O programa agora pode ser compilado sem erros no Termux.

## Dia 1: 06/12/2023
### Objetivo: Subir o código principal para o github
### **O que foi feito:**

•	Comecei a organizar melhor o conteúdo do executável para Windows.

•	O compilador funciona e o software windows se conecta o server no linux.

• Agora ao executar o client no windows, não é exibida a tela do cmd (-mwindows no linker).
