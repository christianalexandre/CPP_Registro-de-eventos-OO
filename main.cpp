#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <locale.h> // pt-br
#include <unistd.h> // função sleep

using namespace std;

/*
	Classe responsavel por armezanar as informações do evento
*/
class Evento {
	private:
		
		int id; // valor chave
		string data; // xx/xx/xx
		string hora; // xx:xx
		string tipo; // PERDA para perda de vídeo e DETEC para detecção de movimento
		
	public:
		
		// sem parametro
		Evento():Evento(0, "", "", ""){
		}
		
		// com parametro
		Evento(int id, string data, string hora, string tipo){
			
			this->id = id;
			this->data = data;
			this->hora = hora;
			this->tipo = tipo;
			
		}
		
		// set's
		void setId(int id){
			this->id = id;
		}
		
		void setData(string data){
			this->data = data;
		}
		
		void setHora(string hora){
			this->hora = hora;
		}
		
		void setTipo(string tipo){
			this->tipo = tipo;
		}
		
		// get's
		int getId(){
			return this->id;
		}
		
		string getData(){
			return this->data;
		}
		
		string getHora(){
			return this->hora;
		}
		
		string getTipo(){
			return this->tipo;
		}	
		
};

/*
	DVR ou Digital Video Recorder se trata de um equipamento para gravar imagens de câmeras de segurança, eles existem em diversos modelos
	Nesse trabalho iremos imaginar que estamos com um gravador que tenha 4 canais (câmeras) sendo representado por 1, 2, 3 e 4.
*/

class Dvr {
	private:		
		
		int quantidade; // controla quantos registros tem no vetor de eventos
		Evento* eventos[50]; // cria um vetor da classe eventos
	
	public:	
	
		// sem parametro
		Dvr(){	
			this->quantidade = 0;		
		}
	
		// set's
		void setQuantidade(int quantidade){
			this->quantidade = quantidade;
		}
		
		// get's
		int getQuantidade(){
			return this->quantidade;
		}
		
		/*
			Insere um registro no final do vetor eventos
		*/		
		int inserirFinal(int id, string tipo, string data, string hora){
			
			if(getQuantidade() < 50){
				
				for(int i=0; i<getQuantidade(); i++){
					
					if(eventos[i]->getId() == id){
						
						system("cls");
						cout << endl << "\t" << ">>>> O ID informado já existe <<<<" << "\t" << endl;
						sleep(1);
						
						return 0;
						
					}
					
				}
											
				Evento* novo = new Evento;				
				novo->setId(id);
				novo->setTipo(tipo);
				novo->setData(data);
				novo->setHora(hora);			
	
				eventos[getQuantidade()]= novo;	
				
				setQuantidade(getQuantidade() + 1);				
				
				return 1;
				
			}
			else {
				system("cls");
				cout << endl << "\t" << ">>>> A lista está cheia <<<<" << "\t" << endl;
				sleep(1);
				return 0;				
			}		
			
		}
		
		/*
			Exclui um registro do vetor a partir da ID
		*/
		int excluirId(int id){
			
			system("cls");
			cout << endl << "\t" << ">>>> Excluir por ID <<<<" << "\t" << endl << endl;
			
			for(int i=0; i<getQuantidade(); i++){
					
				if(eventos[i]->getId() == id){
					
					for(int j=i; j<getQuantidade(); j++){
						eventos[j] = eventos[j + 1];
					}	
					
					setQuantidade(getQuantidade() - 1);	
					
					system("cls");
					cout << endl << "\t" << ">>>> ID excluido com sucesso <<<<" << "\t" << endl << endl;				
						
					sleep(1);
					return 1;
				}					
				
			}
			
			return 0;
		}
		
		/*
			Exclui um registro do vetor a partir do primeiro tipo localizado
		*/
		int excluirTipo(string tipo){
			
			system("cls");
			cout << endl << "\t" << ">>>> Excluir por Tipo <<<<" << "\t" << endl << endl;
			
			for(int i=0; i<getQuantidade(); i++){
					
				if(eventos[i]->getTipo() == tipo){
					
					for(int j=i; j<getQuantidade(); j++){
						eventos[j] = eventos[j + 1];
					}	
					
					setQuantidade(getQuantidade() - 1);	
					
					system("cls");
					cout << endl << "\t" << ">>>> Registro excluido com sucesso <<<<" << "\t" << endl << endl;				
						
					sleep(1);
					return 1;
				}					
				
			}
			
			return 0;
		}
		
		/*
			Altera um registro a partir da ID
		*/
		int alterarId(int id, string tipo, string data, string hora){
			
			system("cls");
			cout << endl << "\t" << ">>>> Alterar por ID <<<<" << "\t" << endl << endl;
			
			for(int i=0; i<getQuantidade(); i++){
					
				if(eventos[i]->getId() == id){
					
					Evento* novo = new Evento;				
					novo->setId(id);
					novo->setTipo(tipo);
					novo->setData(data);
					novo->setHora(hora);			
		
					eventos[i]= novo;		
					
					system("cls");
					cout << endl << "\t" << ">>>> Registro alterado com sucesso <<<<" << "\t" << endl << endl;				
						
					sleep(1);
					return 1;
				}					
				
			}
			
			return 0;
		}
		
		/*
			Altera um registro a partir do Tipo
			Encontará a primeira aparição do tipo e irá alterar
			Não permite alterar a ID para evitar duplicatas
		*/
		int alterarTipo(string tipo, string data, string hora){
			
			system("cls");
			cout << endl << "\t" << ">>>> Alterar por Tipo <<<<" << "\t" << endl << endl;
			
			for(int i=0; i<getQuantidade(); i++){
					
				if(eventos[i]->getTipo() == tipo){
					
					Evento* novo = new Evento;	
					novo->setId(eventos[i]->getId());			
					novo->setTipo(tipo);
					novo->setData(data);
					novo->setHora(hora);			
		
					eventos[i]= novo;		
					
					system("cls");
					cout << endl << "\t" << ">>>> Registro alterado com sucesso <<<<" << "\t" << endl << endl;				
						
					sleep(1);
					return 1;
				}					
				
			}
			
			return 0;
		}
		
		/*
			Lista o registro com a ID escolhida pelo usuário
			Retorna o primeiro registro com a ID correspondente
		*/
		int listarId(int id){
			
			system("cls");
			cout << endl << "\t" << ">>>> Listagem por ID <<<<" << "\t" << endl << endl;
			cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;
			
			for(int i=0; i<getQuantidade(); i++){
				
				if(eventos[i]->getId() == id){
								
					cout << eventos[i]->getId() << "\t" << eventos[i]->getTipo() << "\t" << eventos[i]->getData() << "\t" << eventos[i]->getHora() << endl;
					
					sleep(3);
					return 1;
				}	
			}
			
			return 0;			
			
		}
		
		/*
			Lista todos os registros do tipo escolhido pelo usuário
			Essa função retornará todos os registros referente ao tipo e não apenas o primeiro para se aproximar do que acontece em um DVR
		*/
		void listarTipo(string tipo){
			
			system("cls");
			cout << endl << "\t" << ">>>> Listagem por tipo <<<<" << "\t" << endl << endl;
			cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;
			
			for(int i=0; i<getQuantidade(); i++){
				
				if(eventos[i]->getTipo() == tipo){
								
					cout << eventos[i]->getId() << "\t" << eventos[i]->getTipo() << "\t" << eventos[i]->getData() << "\t" << eventos[i]->getHora() << endl;
				}	
			}		
			
			sleep(3);
		}
		
		/*
			Lista todos os registros do vetor
		*/
		void listar(){
			
			system("cls");
			cout << endl << "\t" << ">>>> Listagem <<<<" << "\t" << endl << endl;
			cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;
			
			for(int i=0; i<getQuantidade(); i++){
				
				cout << eventos[i]->getId() << "\t" << eventos[i]->getTipo() << "\t" << eventos[i]->getData() << "\t" << eventos[i]->getHora() << endl;
					
			}		
			
			sleep(3);
		}
};

/*
	Captura e retorna a ID inserida pelo usuario
*/
int capturaId(){	

	int id;
	
	cout << endl << endl << "Informe a ID: ";
	cin >> id;
	
	return id;
	
}

/*
	Captura e retorna o tipo inserido pelo usuario
*/
string capturaTipo(){	

	string tipo;
	
	cout << endl << endl << "[PERDA] = Perda de vídeo || [DETEC] Detecção de movimento" << endl;
	cout << endl << "Informe o tipo: ";
	cin >> tipo;
	
	return tipo;
	
}

/*
	Captura e retorna a data inserida pelo usuario
*/
string capturaData(){	

	string data;
	
	cout << endl << endl << "Exemplo de data: XX/XX/XX" << endl;
	cout << endl << "Informe a data: ";
	cin >> data;
	
	return data;
	
}

/*
	Captura e retorna a hora inserida pelo usuario
*/
string capturaHora(){	

	string hora;
	
	cout << endl << endl << "Exemplo de hora: XX:XX" << endl;
	cout << endl << "Informe a hora: ";
	cin >> hora;
	
	return hora;
	
}

int main(int argc, char** argv) {
	
	// pt-br
	setlocale(LC_ALL, "Portuguese");
	
	// cria o objeto 
	Dvr* dvr = new Dvr();

	// variaveis utilizadas para percorrer pelo menu
	int opcao = 555, opcao2;	
	
	// menu principal
	while(opcao != 99){		
	
		system("cls");
		cout << endl << "\t" << ">>>> Menu de opções <<<<" << "\t" << endl;
		cout << endl;
		cout << "1 - Incluir" << endl;
		cout << "2 - Excluir" << endl;
		cout << "3 - Alterar" << endl;
		cout << "4 - Consultar" << endl;
		cout << "5 - Listar" << endl;		
		cout << "99 - Sair" << endl;
		cout << endl;
		cout << "Digite a opcao desejada: ";
		
		cin >> opcao;	
		
		switch(opcao){
			
			// inclusão
			case 1:
			{
				
				system("cls");
				cout << endl << "\t" << ">>>> Incluir <<<<" << "\t" << endl;
				int id = capturaId();
				string tipo = capturaTipo();
				string data = capturaData();
				string hora = capturaHora();
				
				if(dvr->inserirFinal(id, tipo, data, hora) == 1){
					system("cls");
					cout << endl << "\t" << ">>>> Registro inserido com sucesso <<<<" << "\t" << endl;					
				}		
				else {
					system("cls");
					cout << endl << "\t" << ">>>> Registro não inserido <<<<" << "\t" << endl;
				}		
								
				sleep(1);
				break;
			}
			
			// exclusão
			case 2:
			{
			
				int teste;
								
				system("cls");
				cout << endl << "\t" << ">>>> Excluir <<<<" << "\t" << endl;
				cout << endl;
				
				cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
				cout << "Informe a opção de exclusão: ";
				cin >> opcao2;
				
					if(opcao2 == 1){
					
					int id = capturaId();
					if(dvr->excluirId(id) == 0){
						system("cls");
						cout << endl << "\t" << ">>>> Não existe registro com a ID informada <<<<" << "\t" << endl;
						sleep(2);
					}									
					
					break;
				}
				else if (opcao2 == 2){
					
					string tipo = capturaTipo();
					if(dvr->excluirTipo(tipo) == 0){
						system("cls");
						cout << endl << "\t" << ">>>> Não existe registro com o Tipo informado <<<<" << "\t" << endl;
						sleep(2);
					}							
					
					break;
				}
				else{
					system("cls");
					cout << endl << "\t" << ">>>> Opção inválida <<<<" << "\t" << endl;
					cout << endl;			
					sleep(1);					
					break;
				}
				
			}
			
			// alteração
			case 3:
			{
				
				system("cls");
				cout << endl << "\t" << ">>>> Alterar <<<<" << "\t" << endl;
				cout << endl;
				
				cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
				cout << "Informe a opção de alteração: ";
				cin >> opcao2;
				
				if(opcao2 == 1){
					
					int id = capturaId();
					string tipo = capturaTipo();
					string data = capturaData();
					string hora = capturaHora();
					
					if(dvr->alterarId(id, tipo, data, hora) == 0){
						system("cls");
						cout << endl << "\t" << ">>>> Não existe registro com a ID informada <<<<" << "\t" << endl;
						sleep(2);
					}					
					
					break;
				}
				else if (opcao2 == 2){
					
					string tipo = capturaTipo();
					string data = capturaData();
					string hora = capturaHora();
					
					if(dvr->alterarTipo(tipo, data, hora) == 0){
						system("cls");
						cout << endl << "\t" << ">>>> Não existe registro com o tipo informado <<<<" << "\t" << endl;
						sleep(2);
					}				
					
					break;
				}
				else{
					system("cls");
					cout << endl << "\t" << ">>>> Opção inválida <<<<" << "\t" << endl;
					cout << endl;			
					sleep(1);					
					break;
				}
								
			}
			
			// consultar
			case 4:
			{
								
				system("cls");
				cout << endl << "\t" << ">>>> Consultar <<<<" << "\t" << endl;
				cout << endl;
				
				cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
				cout << "Informe a opção de consulta: ";
				cin >> opcao2;
				
				if(opcao2 == 1){
					int id = capturaId();
					if(dvr->listarId(id) == 0){
						system("cls");
						cout << endl << "\t" << ">>>> Não existe registro com a ID informada <<<<" << "\t" << endl;
						sleep(2);
					}
					break;
				}
				else if (opcao2 == 2){
					string tipo = capturaTipo();
					dvr->listarTipo(tipo);
					break;
				}
				else{
					system("cls");
					cout << endl << "\t" << ">>>> Opção inválida <<<<" << "\t" << endl;
					cout << endl;			
					sleep(1);	
					break;	
				}		
				
			}
			
			// listar
			case 5:
			{
				
				if(dvr->getQuantidade() == 0){
					system("cls");
					cout << endl << "\t" << ">>>> Não há registros <<<<" << "\t" << endl;
					sleep(2);
				}
				else{
					dvr->listar();		
				}
				
				break;	
			}
			
			// sair
			case 99:
			{				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado pelo usuário <<<<" << "\t" << endl;
				cout << endl;
				break;				
			}			
		}	
	}

	return EXIT_SUCCESS;

}
