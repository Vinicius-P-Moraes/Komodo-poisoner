//Header para interpretaÃ§Ã£o do comando digitado pelo usuÃ¡rio

#include<string>

struct info_interpretador
{
  std::string ip;
  int porta;
  const char*  funcao;
  int error_code;
};

bool hifen_encontrado;
std::string ip;
std::string _port;
int port;

int ip_extractor(char comando[command_size]){
  int i = 0;
  hifen_encontrado = false;

  do{
    if(comando[i] == '-'){
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
    if(comando[i] == '-'){
      break;
    }
    if(comando[i] != ' '){
      ip += comando[i];
    }
    ++i;
  }
  return 0;
}


int port_extractor(char comando[command_size]){
  int i = 0;
  hifen_encontrado = false;

  do{
    if(comando[i] == '-'){
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
    if(comando[i] != ' '){
      _port += comando[i];
    }
    ++i;
  }
  port = std::stoi(_port);
  return 0;
}

info_interpretador interpretador(char comando[command_size])
{
  std::string aux_comando; //recebe o resultado de Copy para comparaÃ§Ãµes.
  int i = 0;

  //Instancia a variÃ¡vel de resposta
  info_interpretador _info_interpretador;

  //Procura pelo comando do listener:

  //Seta o tamanho da var auxiliar para o tamanho da string que quero encintrar
  aux_comando.resize(sizeof(listener_identifyer));

  //Varre o comando procurando por listener:
  for(i = 0; i != sizeof(comando) -1; i++){
    aux_comando = teste.substr(i, sizeof(listener_identifyer));
    std::cout << "Examinando: " << aux_comando << "\n";
    if (aux_comando == listener_identifyer){
      _info_interpretador.funcao = listener_identifyer;
      break;
    } else if(aux_comando == builder_identifyer){
      _info_interpretador.funcao = builder_identifyer;
      break;
    } else{
      //NÃ£o chamou nem uma funÃ§Ã£o
      _info_interpretador.error_code = 1;
      return = _info_interpretador;
      exit;
    }
  }


  if(comando[0] == 'l'){
    if(port_extractor(comando) == 0){
      std::cout << "Porta extraida com sucesso\n";
    }else{
      std::cout << "Erro ao extrair a porta\n";
    }
    std::cout << "Iniciando Listener\n";


//std::thread listener(open_listener);
//    listener.join();


  }else if(comando[0] == 'b'){
    if(ip_extractor(comando) == 0){
      std::cout << "IP extraido com sucesso";
    }else{
      std::cout << "Erro ao extrair o IP\n";
    }

    if(port_extractor(comando) == 0){
      std::cout << "Porta extraida com sucesso\n";
    }else{
      std::cout << "Erro ao extrair a porta\n";
    }
    std::cout << "Chamando Builder\n";
  

//  builder();

    std::cout << "\nDeseja iniciar o Listener? (s/n)\n";
    std::cout << "$Builder$: ";
    memset(comando, 0, command_size);
    std::cin.getline(comando, command_size);
    if(comando[0] == 's' || comando[0] == 'S'){
  

//    std::thread listener(open_listener);
  //    listener.join();
    


}else{
      exit(1);
    }
  }

  return _info_interpretador;
}
