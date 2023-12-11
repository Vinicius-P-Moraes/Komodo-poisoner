# Komodo-poisoner
Komodo Poisoner - criado para fins educacionais e de estudo apenas - é uma aplicação que recebe dados de um payload de monitoramento remoto. 

É um programa estilo RAT (Remote Administration Tool) voltado  a ser utilizado no app terminal Termux Android. 
O software cria um executável para windows e recebe a input do teclado do pc hospedeiro e sua tela em tempo real; 

Desenvolvido em C++, pode ser utilizado tanto em uma distribuição Linux Desktop quanto em um terminal mobile como o Termux.

## Instruções:
**#Ubuntu:** sudo apt-get install mingw-w64 

**#Termux:** pkg install llvm-mingw-w64

AINDA EM DESENVOLVIMENTO
# Diário de bordo
## Dia 3: 11/07/2023
### Objetivo: Desenvolver o Keylogger
**O que foi feito:**

•	Agora ao terminar a compilação no builder o usuário pode escolher se quer chamar o listener.

## Dia 2: 07/12/2023
### Objetivo: Corrigir a função do compilador para funcionar no termux
**O que foi feito:**

•	O programa agora pode ser compilado sem erros no Termux.

## Dia 1: 06/12/2023
### Objetivo: Subir o código principal para o github
**O que foi feito:**

•	Comecei a organizar melhor o conteúdo do executável para Windows.

•	O compilador funciona e o software windows se conecta o server no linux.

• Agora ao executar o client no windows, não é exibida a tela do cmd (-mwindows no linker).
