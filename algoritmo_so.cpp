#include<stdio.h>
#include<conio.c>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
//Registro dos processos.
typedef struct processo{
	int name;
	int aux;
	int t_chegada;
	int t_execucao;
	int t_entrada;
	int t_saida;
	int t_espera;
	int tr;
	int prioridade;
	processo* prox;
	processo* ant;
};
//função para limpar a memoria utilizada pelo fifo e sjf.
processo* limpa_1(processo* lista){//recebe a lista como parametro.
	if(lista){
		processo* aux=lista;
		lista=aux->prox;
		free(aux);
		limpa_1(lista);
	}
	else
		return lista;
}
processo* limpa_2(processo* lista,processo* ultimo,int log){
	if(lista!=ultimo||log!=1){
		processo* aux=lista;
		lista=aux->prox;
		free(aux);
		log=1;
		limpa_2(lista,ultimo,log);
	}
	else
		return lista;
}
//Função para imprimir os programas FIFO e SJF.
void imprime_1(processo* lista){
	if(lista){
		printf("\n\t_________________________________\n");
		printf("\n\tLinhado Tempo de P%d.\n",lista->name);
		printf("\n\tTempo de Chegada: %d:\tTempo de Execucao: %d:.\n",lista->t_chegada,lista->t_execucao);
		printf("\n\tTempo de Entrada :  %d :\tTempo de saida: %d :.\n",lista->t_entrada,lista->t_saida);
		printf("\n\tTempo de Espera: %d:\tTURNAROUND: %d:.\n",lista->t_espera,lista->tr);
	}
}
//Função Para imprimir os Programas ROUND ROBIE e PRIORIDADE.
void imprime_2(processo* lista,processo* ultimo,int log,int diferencia){
	if(lista!=ultimo||log!=1){
		printf("\n-_______________________________________________________________________________\n");
		lista->tr=lista->t_espera+lista->t_execucao;
		if(diferencia==1)
			printf("\n\tLinhado Tempo de P%d\tPRIORIDADE: %d.\n",lista->name,lista->prioridade);
		else
			printf("\n\tLinha do Tempo de P%d.\n",lista->name);
		printf("\nTempo de Chegada: %d:\tTempo de Execucao: %d:.\n",lista->t_chegada,lista->t_execucao);
		printf("Tempo de Espera: %d:\tTURNAROUND: %d:.\n",lista->t_espera,lista->tr);
		log=1;
		imprime_2(lista->prox,ultimo,log,diferencia);
	}	
}
//Função responçavel pela organização dos processos atraves da sua ordem de chegada.
//Para Todos os programas. FIFO, SJF, ROUDIN ROBIE. 
void OrganizaProcesso(processo* lista,processo* novo){//Função que recebe a lista e o novo.
	if(lista){//Ver se a lista existe. Ponto de Parada.
		if(!lista->prox){//Ver o proximo da lista é nulo.
			novo->prox=NULL;//Se for, o proximo da lista será o novo.
			novo->ant=lista;//O anterior do novo será a lista.
			lista->prox=novo;//O proximo da lista será o novo.
			return;//Retorna para função SetProcesso.
		}//Fim Se
		if(lista->prox->t_chegada>novo->t_chegada){//Verifica se o novo será o proximo da lista.
			novo->prox=lista->prox;//Se for,O Proximo de novo será o proximo da lista.
			novo->ant=lista;//O anterior do novo será a lista.
			lista->prox=novo;//O proximo da lista será o novo
			return;	//Retorna para função SetProcesso.
		}//Fim Se
		if(lista->prox->t_chegada==novo->t_chegada)//Ve se o tempo de chegada é igual.
			if(novo->t_execucao<lista->prox->t_execucao){//Ver quem tem o tempo de execução menor.
				novo->prox=lista->prox;//Se for,O Proximo de novo será o proximo da lista.
				novo->prox->ant=novo;//O anterior do proximo será o novo.
				lista->prox=novo;//O proximo da lista será o novo.
				novo->ant=lista;//O anterior do novo será a lista.
			return;//Retorna para função SetProcesso.
		}//Fim Se 
		// Senão ocorrer nenhuma dessas possiilidades.
		OrganizaProcesso(lista->prox,novo);//Chama a função novamente mandando o proximo da lista e o novo.
	}//Fim Se
}//Fim Organiza.
//Essa Função é responçavel pelo Cadastro de todos os processos. FIFO, SJF, ROUND ROBIE.
processo* SetProcesso(processo* lista,int i){//Recebe como parametro a lista e i.
	system("cls");//Limpa a tela.
	processo* novo;//Cria um novo processo.
	novo=(processo*)malloc(sizeof(processo));//Aloca esse processo em um espaço vazio de memoria.
	novo->name=i+1;//Define o nome do processo que será i+1;
	printf("\n\tDigite o tempo de chegada de P%d.\n\t",novo->name);//Imprime na tela. 
	scanf(" %d",&novo->t_chegada);//Ler o tempo de chegada.
	printf("\n\tDigite o tempo de execucao de P%d.\n\t",novo->name);//Imprime na tela;
	scanf(" %d",&novo->t_execucao);//Ler o tempo de execução.
	novo->aux=novo->t_execucao;//O tempo de aux será o de execução. Aux variavel auxiliar para 
	//não alterar o valor do tempo de execução utiliza-se ela. Caso do ROUND ROBIE
	novo->t_espera=0;//Tempo de espera srecebera 0;
	novo->t_entrada=0;//Tempo de entrada recebera 0;
	novo->t_saida=0;//Tempo de saida recebera 0;
	novo->prox=NULL;//O proximo do Novo será NULO//
	if(!lista){//Verifica se a lista existe.
		novo->prox=lista;//Se não existir, o novo será a lista, seu proximo será NULO.
		novo->ant=lista;//Seu Anterior também será nulo.
		return novo;//Retorna o Novo ao programa Principal.
	}//fim se
	if(lista->t_chegada>novo->t_chegada){//Verifica se o novo será o primeiro da lista.
		novo->prox=lista;//Se for, o proximo do novo será a lista.
		novo->ant=NULL;//O anterior de novo será NULO.
		return novo;//Retorna o Novo ao programa pricipal;
	}//Fim se
	if(lista->t_chegada==novo->t_chegada){//Verifica se o novo tem tempo de chegada igual a lista.
		if(lista->t_execucao>novo->t_execucao){//Verifica se o novo menor tempo de execução.	
			novo->prox=lista;//Se for, o proximo do novo será a lista.
			novo->ant=NULL;//O anterior de novo será NULO.
			return novo;//Retorna o Novo ao programa pricipal
		}//fim se;
	}//Fim se 
	if(!lista->prox){//Verifica se o proximo da lista é nulo.
			novo->prox=NULL;//Se for o proximo de novo será nulo.
			novo->ant=lista;//O anterior do novo será a lista.
			lista->prox=novo;//O proximo da lista será o novo.
			lista->ant=NULL;//O anterior da lista será nulo.
			return lista;//Retorna a lista ao programa principal.
	}//Fim se
	OrganizaProcesso(lista,novo);//Chama a função para organizar o novo na lista.
	return lista;//Retorna a lista ao programa principal.
}//fim SetProcesso
//Função que simulara a execução do FIFO.
void simulafifo(processo* lista,int te){//Recebe como parametro a lista e a linha do tempo.
	if(lista){//Verifica se a lista existe. Ponto de Parada.
		if(lista->t_chegada<=te){//Verifica se a lista tem o tempo de chegada menor que a linha do tempo
			lista->t_entrada=te;//O tempo de entrada será a linha do tempo.
			lista->t_saida=(lista->t_entrada)+(lista->t_execucao);//A saida será a entrada mais a execução.
			lista->t_espera=(lista->t_entrada)-(lista->t_chegada);//O tempo de espera será a entrada menos a chegada.
			lista->tr=(lista->t_espera)+(lista->t_execucao);//O TR será espera + execução.
			te+=(lista->t_execucao);//Linha do tempo recebe o tempo de execução + ele.
			imprime_1(lista);//Chama imprime_1 mandando a lista.
			simulafifo(lista->prox,te);//Chama a função novamente mandando o proximo e a linha do tempo. .
		}//Fim se.
		else{//Se a lista ainda não estive chegado. Tempo ocioso;
			te+=1;//Linha do tempo mais recebe 1.
			simulafifo(lista,te);//Chama a função simula fifo novamente com a lista e te.
		}//Fim else
	}//Fim se
}//Fim simula fifo.
//Função responsavel pelo FIFO.
processo* GetFifo(processo* lista){//Recebe como parametro a lista.
	system("cls");//Limp]a a tela.
	int te=lista->t_chegada;//Cria te com o tempo de chegada do primeiro.
	simulafifo(lista,te);//Chama a função para simular o fifo.
	printf("\n\n");//Pula duas linhas.
	system("PAUSE");//Pede ao usuario uma tecla para voltar ao programa principal;
	lista=limpa_1(lista);
	return lista;
}//Fim GetFifo
//Daqui para baixo SJF.
//TE== LINHA DO TEMPO.
int contador(processo* lista,int te,int cont){//Conta o numero de processo menor que TE.
	if(lista){//Verifica se a lista existe. Ponto de parada.
		if(lista->t_chegada<=te){//Verifica se a chegada da lista é menor ou igual te.
			cont+=1;//Cont recebe mais 1.
			contador(lista->prox,te,cont);//Chama a função novamente com o proximo da lista, te e cont
		}//Fim se
		else//else kkk
			return cont;//Retora cont ao simulaSjf
	}//fim se
	else//else kkk
		return cont;//Retora cont ao simulaSjf
}//Fim contador.
//Função para ver qual processo ira executar. Menor tempo de trabalho.
int execucao_menor(processo* lista,int te,int aux){//Recebe como paramentro a lista, te e aux.
//Aux irá receber o menor tempo de execução para ver qual programa irá executar.
	if(lista){//Verifica se alista existe. Ponto de parada.
		if(lista->t_chegada<=te){//Verifica se a lista tem o tempo de chegada menor ou igual  te.
			if(lista->t_execucao<aux){//Verifica se a execução é menor que aux.
				aux=lista->t_execucao;//Aux recebe esse tempo de execução.
				execucao_menor(lista->prox,te,aux);//Chama a função novamente com o proximo da lista, te, aux.
			}//FIm se.
			else//else kkk
				execucao_menor(lista->prox,te,aux);//chama a função novamente com o proximo da lista,te ,aux.
		}//fim se.
		else//else kkk
			return aux;// retorna aux ao programa principal.
	}//fim se
	else//else kkk
		return aux;// retorna aux ao programa principal.
}//fim execução_menor.
//PAra falar que existe.
void simulasjf(processo* lista,int te);
//Função para organizar o sjf caso o cont for maior que 1. 
void org_sjf(processo* lista,processo* inicial,int te,int aux){//Parametro lista, incio, te e aux.
//Incio é a propria lista so que não será alterado.
	if(lista){//Verifica se a lista existe. Ponto de parada.
		if(lista->prox->t_chegada<=te&&lista->prox->t_execucao==aux){//Verifica se a lista é o programa a ser executado.
			processo* a;//Cria um processo chamado a.
			lista->prox->t_entrada=te;//Tempo de entrada sera te.
			lista->prox->t_saida=te+lista->prox->t_execucao;//Saida sera te + execução.
			lista->prox->t_espera=lista->prox->t_entrada-lista->prox->t_chegada;//Espera será te - chegada.
			lista->prox->tr=lista->prox->t_espera+lista->prox->t_execucao;//Te será espera + execução;
			te+=lista->prox->t_execucao;//Te mais recebe execução.
			imprime_1(lista->prox);//Chama a função para imprimir mandando a lista.
			a=lista->prox;//a recebe o proximo da lista.
			lista->prox=a->prox;//lista recebe a.
			a->ant=NULL;//deleta a lista.
			a->prox=inicial;//o procimo de a recebe o inicio.
			lista=a;// lista será a agora.
			simulasjf(lista->prox,te);//Retorna ao programa simulasjf.
		}//fim se
		else//else kkk
			org_sjf(lista->prox,inicial,te,aux);//chama função novamente com o proximo da lista, o inicio , te e aux.
	}//fim se
}//Fim Org_sjf
//Função de Simulação do SJF.
void simulasjf(processo* lista,int te){//Recebe como parametro a lista e te.
	if(lista){//verifica se a lista existe. ponto de parada.
		int cont=0;//contador.
		cont=contador(lista,te,cont);//chama a função para contar numero de processos que existe para executar.
		if(cont==0){//Se cont == 0. Tempo ocioso.
			te+=1;//Te mais receb 1.
			simulasjf(lista,te);//Chama a função novamente, com a lista e te.
		}//Fim se.
		if(cont==1){//Se cont for igual a 1. Unico processo para executar.
			lista->t_entrada=te;//Entrada recebe te.
			lista->t_saida=te+lista->t_execucao;//Saida recebe te  + execução.
			lista->t_espera=lista->t_entrada-lista->t_chegada;//Espera recebe entrada - chegada.
			lista->tr=lista->t_espera+lista->t_execucao;//TR recebe espera + execução.
			te+=lista->t_execucao;//te mais recebe execução.
			imprime_1(lista);//Chama a função para imprimir a lista.
			simulasjf(lista->prox,te);//chama a função novamente com o proximo da lista.
		}//fim se.
		if(cont>1){//Se o cont for maior que 1. Mais de um processo para executar.
			int aux=execucao_menor(lista,te,99999999);
			if(lista->t_chegada<=te&&lista->t_execucao==aux){//verifica se a lista é o processo a ser executado.
				lista->t_entrada=te;// Se for, entrada recebe te.
				lista->t_saida=te+lista->t_execucao;//Saida receb te+ execução;
				lista->t_espera=lista->t_entrada-lista->t_chegada;//espera recebe entrada - saida.
				lista->tr=lista->t_espera+lista->t_execucao;//tr recebe espera + execução.
				te+=lista->t_execucao;//Te mais recebe execução.
				imprime_1(lista);//Chama a função para imprimir mandando a lista.
				simulasjf(lista->prox,te);//Chama a função simulasjf novamente mandando o proximo da lista, te
			}//fim se.
			else{//else kkkk
				org_sjf(lista,lista,te,aux);//chama a função para oraganizar e simular o processo adeuqando.
			}//fim senão.
		}//fim se.
	}//fim se
}//fim simula sjf
//Função responsavel pelo SJF.
processo* GetSjf(processo* lista){//recebe como parametro a lista.
	system("cls");//limpa a tela.
	int te=lista->t_chegada;//te recebe o tempo de chegada do primeiro.
	simulasjf(lista,te);//chama a função para simular o sjf.
	printf("\n\n");
	system("PAUSE");//espera uma tecla do usuario parra voltar ao menu principal.
	lista=limpa_1(lista);
	return lista;
}//fim GetSjf;
//Daqui para baixo RR;
//Função para ver se ainda a processos para executar ou se ja foram todos executados.
bool Para(processo* lista,processo* ultimo,int log){//Paramentro lista, lista, log.
	if(lista!=ultimo||log!=1){//Verifica se a lista é diferente do outimo ou log diferente de 1.
		if(lista->aux>0){//Verifica se a lista ainda pode executar.
			log=1;//log recebe 1.
			return 1;//Retorna log. Programa não irar fechar.
		}//Fim se
		else{//Else kkkk
			log=1;//Log recebe 1.
			Para(lista->prox,ultimo,log);//Chama a função novamente. Mandando o proximo, ultimo e log.
		}//fim senão.
	}//fim se 
	else//else kkk
		return 0;// retorna 0 e o programa irar parar.
}//fim para.
//Função para aumentar o tempo de espera dos processos fora o q está em execução.
void espera(processo* lista,processo* ultimo,int te,int aux){//paramentro lista, ultimo , te e aux.
	if(lista!=ultimo){//verifica se a lista é diferente do ultimo.
		if(lista->t_chegada<=te&&lista->aux>0){//Verifica se o processo é menor que te e ainda tem tempo para executar;
			lista->t_espera+=aux;// processo ira receber mais um aux no seu tempo de espera.
			espera(lista->prox,ultimo,te,aux);//chama a função novamente mandando o proximo da lista, ultimo , te e aux.
		}//Fim se.
		else{// Else kkk
			espera(lista->prox,ultimo,te,aux);//chama a função novamente mandando o proximo da lista, ultimo , te e aux.
		}//fim senão.
	}//fim se.
	else//else kkk
		return;// retorna para a função simularr
}//fim espera.
processo* Verifica_RR(processo* lista,processo* ultimo,int log,int aux,int chegada,int name,int te){
//Recebe como referencia, lista, lista,aux,chegada,te;
	while(lista!=ultimo||log!=1){
		if(lista->t_chegada<=te&&lista->aux>0){
			if(lista->t_saida==aux&&lista->aux>0){
				if(lista->t_chegada<chegada){
					chegada=lista->t_chegada;
					aux=lista->t_entrada;
					log=1;
					name=lista->name;
				}
				if(lista->t_chegada==chegada){
					if(lista->name<name){
						aux=lista->t_entrada;
						chegada=lista->t_chegada;
						name=lista->name;
					}	
				}
			}
			if(lista->t_saida<aux){
				chegada=lista->t_chegada;
				aux=lista->t_saida;
				name=lista->name;
				log=1;
			}
			log=1;
			lista=lista->prox;
		}
		else
			lista=lista->prox;
	}
	log=0;
	while(lista!=ultimo||log!=1){
		if(lista->name==name){
			log=1;	
			return lista;
		}
		else{
			log=1;
			lista=lista->prox;
		}
	}
}
//Fução responçavel por verificar ociosidade no Round Robie e no Prioridade.
bool ociosidade(processo* lista,processo* ultimo,int te,int log){//recebe como parametro a lista, lista,te e log.
	if(lista!=ultimo||log!=1){//Função para verificar a parada. Esquemas anteriores.
		if(lista->t_chegada<=te&&lista->aux>0){//Verifica se a chegada da lista é menor que te e se o seu aux é maior que 0;
			log=1;//Log recebe 1;
			return 1;//Retorna 1 para a função simularr. Indica que não a ociosidade.
		}//fim se.
		else{//else kkk
			log=1;//log recebe 1;
			ociosidade(lista->prox,ultimo,te,log);//chama a função novamente mandando o procimo da lista.
		}//fim senao;
	}//fim se;
	else//else kkkk
		return 0;// retorna 0 a função simularr. Indica que tera tempo ocioso.
}//fim ociosidade.
//Função responsavel pela simulação do ROUND ROBIE.
void simularr(processo* lista,processo* ultimo,int te,int q){//Recebe como parametro a lista, NULL, te e quantum.
	if(Para(lista,lista,0)==1){//Verifica se a processos a executar. Caso 1 . Entra no se.
		if(ociosidade(lista,lista,te,0)==0){//Verifica se a tempo ocioso.
			te+=1;//Se sim, te mais recebe 1.
			simularr(lista,ultimo,te,q);//chama a função novamente sem alterar nada.
		}//Fim se;
		else{//else kkkk//Senão ouver tempo ocioso;
			if(lista=Verifica_RR(lista,lista,0,99999999,99999999,9999999999,te)){//Chama a função que verificara qual processo será executado.
					if(lista->aux>0&&lista->t_chegada<=te){
						if(lista->aux>0&&lista->aux<q){//Verifica se o aux é maior que 0 e menor que o qauantum.
							lista->t_entrada=te;//Entrada recebe te;
							lista->t_saida=te+lista->aux;//Saida recebe te + aux//
							if(lista->aux==lista->t_execucao){//Verifica se o processo ainda não foi executado.
								lista->t_espera= lista->t_entrada - lista->t_chegada;//Espera recebera entrada menos a chegada.
							}//Fim se;
							espera(lista->prox,lista,te,lista->aux);//Chama a função para aumentar o tempo de espera dos outros processos.
							te+=lista->aux;//te recebe mais aux.
							lista->aux-=lista->aux;//aux recebera 0;
							ultimo=lista;//ultimo recebe a lista;
							printf("\nP%d\tTE- %d\tTS- %d\tTempo Restante- %d\n",lista->name,lista->t_entrada,lista->t_saida,lista->aux);//Imprime nome, tempo de entra, e saida;
							simularr(ultimo->prox,ultimo,te,q);//chama a função novamente mandando o proximo.
						}//Fim se;		
						if(lista->aux>=q){//Verifica se aux é maior ou igual a q;
							lista->t_entrada=te;//Entrada recebe te;
							lista->t_saida=te+q;//Saida recebe te + q;
							ultimo=lista;//Ultimo recebe a lista;
							if(lista->aux==lista->t_execucao){//Verifica se o processo não foi executado.
								lista->t_espera= lista->t_entrada-lista->t_chegada;//Espera recebe entrada menos chegada;
							}//fim se;
							te+=q;//te mais recebe q;
							lista->aux-=q;//aux menos recebe q;
							espera(lista->prox,lista,te,q);	//chama a função para aumentar o tempo de espera dos outros processos.						
							printf("\nP%d\tTE- %d\tTS- %d\tTempo Restante- %d.\n",lista->name,lista->t_entrada,lista->t_saida,lista->aux);//Imprime nome, entrada e saida;
							simularr(ultimo->prox,ultimo,te,q);//chama a função novamente mandando o proximo da lista.
						}//fim se.
					}//fim se//
					else
						simularr(ultimo->prox,ultimo,te,q);
			}//fim se
			else{//else kkkk
				simularr(lista->prox,ultimo,te,q);//chama a função mandando o proximo da lista;
			}//fim senao;
		}//fim senão;
	}//fim se;
}//fim simularr;
//Função para fazer a lista se tornar circular, Round Robie e Prioridade.
processo* circular(processo* lista,processo* primeiro){//Recebe como paramentro a lista e a lista;
	if(!lista->prox){//Verifica se o proximo existe;
		lista->prox=primeiro;// se o proximo não existir, o proximo será o primeiro.
		return primeiro;//retorna o primeiro.
	}//fim se;
	else//else kkk
		circular(lista->prox,primeiro);	//chama a função novamente mandando a o procimo e o primeiro.
}//Fim circular.
//Função responçavel pelo Round Robie.
processo* GetRr(processo* lista){//Recebe como parametro a lista.
	system("cls");//Limpa a tela.
	int te=lista->t_chegada;//Cria te recebendo o tempo de chegada do primeiro.
	int quantum;//cria o quantum;;
	printf("\n\tDigite o valor quantum.\n\t");//Imprime na tela.
	scanf(" %d",&quantum);//Ler o quantum;;
	if(quantum>0){
		lista=circular(lista,lista);//Chama a função para criar a lista circular.
		system("cls");//Limpa a tela;
		processo* aux=NULL;//Cria aux;
		simularr(lista,aux,te,quantum);//chama a função para simular o Round Robie;
		imprime_2(lista,lista,0,0);//Chama a função para imprimir.
		printf("\n\n");//Pula 2 linhas.
		system("PAUSE");//Espera uma tecla do usuario para voltar ao programa principal.
		lista=limpa_2(lista,lista,0);//Limpa da memoria os espaços utilizado pelo programa.
		return lista;//Retorna a lista ao menu principal
	}
	else{
		printf("\nValor Invalido.\n");
		system("PAUSE");
		return lista;
	}
}//Fim GetRr
//Aqui Para baixo Parte do Prioridade.
void OrganizaPrioridade(processo* lista,processo* novo){//Função para organizaros processos doPrioridade.
	if(lista){//Verifica se a lista existe. Ponto de parada.
		if(!lista->prox){//Verifica se o proximo da lista existe.
			novo->prox=NULL;//O proximo do novo será Nulo.
			lista->prox=novo;//O proximo da lista será o novo.
			return;//Retorna para GetPrioridade.
		}//Fim Se
		if(lista->prox->t_chegada>novo->t_chegada){//Verifica quem tem o tempo de chegada menor.
			novo->prox=lista->prox;//O proximo de novo será o rpoximo da lista.
			lista->prox=novo;//O proximo da lista sera o novo.
			return;	//Retorna para GetPrioridade.
		}//Fim se.
		if(lista->prox->t_chegada==novo->t_chegada)//Verifica se o tempo de chegada de novo e lista são iguais.
			if(novo->prioridade<lista->prox->prioridade){//verifica se o novo tem prioridade menor.
				novo->prox=lista->prox;//O proximo de novo será o proximo da lista.
				lista->prox=novo;//O proximo da lista será o novo.
				return;//Retorna ao GetPrioridade.
			}//fim se.
			if(novo->prioridade==lista->prioridade)
				if(novo->t_execucao<lista->t_execucao){
					novo->prox=lista->prox;//O proximo de novo será o proximo da lista.
					lista->prox=novo;//O proximo da lista será o novo.
					return;//Retorna ao GetPrioridade
				}
		OrganizaPrioridade(lista->prox,novo);//Chama a função novamente mandando o proximo da lista e o novo.
	}//fim se.
}//Fim OrganizaPrioridade.
//Função responsavel pelo cadastro dos processos de prioridade.
processo* SetPrioridade(processo* lista,int i){//Recebe como parametro a lista e i;
	processo* novo;//Cria o processo novo;
	novo=(processo*)malloc(sizeof(processo));//Cria e aloca um espaço de memoria para o novo.
	system("cls");//Limpa a tela.
	novo->name=i+1;//O nome do novo será i+1;
	printf("\n\tDigite o tempo de chegada de P%d.\n\t",novo->name);//Imprime na tela.
	scanf(" %d",&novo->t_chegada);//Le o tempo de chegada.
	printf("\n\tDigite o tempo de execucao de P%d.\n\t",novo->name);//Imprime na tela.
	scanf(" %d",&novo->t_execucao);//le o tempo de execução.
	novo->aux=novo->t_execucao;//Aux recebe o tempo de execução.
	//Como No RR o aux que será alterado assim não usaremos o tempo de execução e sim aux;
	printf("\n\tDigite a prioridade de P%d.\n\t",novo->name);//Imprime na tela;
	scanf(" %d",&novo->prioridade);//Le a prioridade.
	novo->t_espera=0;//Espera recebe 0.
	novo->t_entrada=0;//Entrada recebe 0;
	novo->t_saida=0;//Saida recebe 0;
	novo->prox=NULL;//Proximo de novo recebe nulo.
	if(!lista){//Verifica se a lista existe.
		novo->prox=lista;//O proximo de novo será a lista== Nulo.
		return novo;//retorna o novo ao programa principal.
	}//Fim se;
	if(lista->t_chegada>novo->t_chegada){//Verifica se o tempo de chegada do no é menor que o da lista;
		novo->prox=lista;//proximo de novo recebe a lista;
		return novo;//retorna novo ao programa principal.
	}//Fim se.
	if(lista->t_chegada==novo->t_chegada){//Verifica se lista e novo tem tempo de chegada igual.
		if(lista->prioridade>novo->prioridade){//Verifica se o novo tem a prioridade menor.
			novo->prox=lista;//O proximo de novo será a lista.
			return novo;//Retorna novo ao programa principal. 
		}//Fim se.
	}//Fim se.
	if(!lista->prox){//Verifica se o proximo da lista é nulo;
			novo->prox=NULL;//O proximo de novo será nulo.
			lista->prox=novo;//O proximo da lista será o novo;
			return lista;//retorna a lista ao programa principal.
	}//fim se;
	OrganizaPrioridade(lista,novo);//Chama a função para organizar e incluir novo na lista.
	return lista;//retorna a lista ao programa principal.
}//Fim SetPrioridade.
//Função para verificar e definir qual processo será executado no prioridade.
processo* Verifica_Prioridade(processo* lista,processo* ultimo,processo* aux,int log,int executar,int chegada,int t_exe,int prio,int nome,int te){
//Recebe como parametro a lista, o ultimo, aux, log, executar,chegada, prio e te;	
//Executar tempo sem executar do processo.
	while(lista!=ultimo||log!=1){//Ponto de parada como anteriores desse tipo;
		if(lista->t_chegada<=te&&lista->aux>0){//Verifica se o tempo de chegada é menor ou igual te e se aux é maior que 0;
			if(lista->prioridade==prio&&lista->aux>0){//Verifica se a prioridade da lista é igual prio.
				if(lista->t_saida<executar&&lista->aux>0){//Verifica se o tempo de saida é menor que executar.
					t_exe=lista->t_execucao;
					executar=lista->t_saida;//executar recebe o tempo de saida da lista.
					chegada=lista->t_chegada;//Chegada recebe o tempo de chegada da lista;
					prio=lista->prioridade;//Prio recebe a prioridade da lista.
					log=1;//Log recebe 1;
					nome=lista->name;
				}//fim se.
				if(lista->t_saida==executar&&lista->aux>0){
					if(lista->t_chegada==chegada){
						if(lista->t_execucao<t_exe){
							t_exe=lista->t_execucao;
							executar=lista->t_saida;//executar recebe o tempo de saida da lista.
							chegada=lista->t_chegada;//Chegada recebe o tempo de chegada da lista;
							prio=lista->prioridade;//Prio recebe a prioridade da lista.
							log=1;//Log recebe 1;
							nome=lista->name;
						}
					}
					if(lista->t_chegada<chegada&&lista->aux>0){
						t_exe=lista->t_execucao;
						executar=lista->t_saida;//executar recebe o tempo de saida da lista.
						chegada=lista->t_chegada;//Chegada recebe o tempo de chegada da lista;
						prio=lista->prioridade;//Prio recebe a prioridade da lista.
						log=1;//Log recebe 1;
						nome=lista->name;
					}
				}
			}//fim se;
			if(lista->prioridade<prio&&lista->aux>0){//Verifica se a prioridade da lista é menor que prio;
				t_exe=lista->t_execucao;
				executar=lista->t_saida;//executar recebe tempo de saida da lista.
				chegada=lista->t_chegada;//chegada recebe tempo de chegada da lista.
				prio=lista->prioridade;//prio recebe prioridade da lista.
				nome=lista->name;
				log=1;// Log recebe 1;
			}//fim se.
			log=1;
			lista=lista->prox;//lista recebe o proximo da lista.
		}//fim se 
		else{//else kkkk
			log=1;//log recebe 1.
			lista=lista->prox;//lista recebe o proximo da lista.
		}//fim senão;
	}//fim enquanto.
	log=0;//Log recebe 0;
	while(lista!=ultimo||log!=1){//Ponto de parada como anteriores.
		if(lista->name==nome&&lista->aux>0){
		//Verifica se lista é o processo a ser executado.
			if(aux){
				if(aux->prioridade<=prio&&aux->aux>0){
					log=1;
					return aux;
				}
				else{//else kkk.
					log=1;//Log recebe 1;
					return lista;//Retorna a lista ao programa principal.
			}//fim senão;
			}//fim se;
			else{//else kkk
				log=1;//log recebe 1.
				return lista;//lista recebe o proximo da lista.
			}//fim senão;
		}//fim enquanto.
		else
			log=1;
			lista=lista->prox;
		}
	return aux;//retorna o ultimo ao programa principal. AUX.
}//Fim VerificaPrioridade.
//Função que simula o Prioridade.
void SimulaPrioridade(processo* lista,processo* ultimo,int te){//Recebe como parametro lista, lista e te.
	if(Para(lista,lista,0)==1){//Chama a função para. Se retornar um indica que ainda a processos para serem executados.
			if(ociosidade(lista,lista,te,0)==0){//Verifica ociosidade, se retornar 0 indica tempo ocioso.
				te+=1;//Te mais recebe 1.
				SimulaPrioridade(lista,ultimo,te);//Chama a função novamente.
			}//Fim se.
			else{//Senão ouver tempo ocioso.
				lista=Verifica_Prioridade(lista,lista,ultimo,0,99999999,99999999,99999999,999999999,999999999999,te);
				//Chama função para verificar qual processo será executado.
				if(lista->t_chegada<=te&&lista->aux>0){//Verifica se a lista é menor ou igual te;
					lista->t_entrada=te;//Entrada recebe te;
					lista->t_saida=te+1;//Saida recebe te +1;
					if(lista!=ultimo&&ultimo!=NULL)//If o processo ainda não foi executado.
						printf("TS- %d\tPrioridade- %d\n",ultimo->t_saida,ultimo->prioridade);//Imprime.
					if(lista!=ultimo)//If a lista for diferente do ultimo.
						printf("\n\tP%d\tTE- %d\t",lista->name,lista->t_entrada);//Imprime
					ultimo=lista;//Ultimo recebe a lista.
					if(lista->t_execucao==lista->aux)//Verifica se o processo ainda não foi executado.
						lista->t_espera=lista->t_entrada-lista->t_chegada;//espera recebe entrada - chegada.
					lista->aux-=1;//aux menos recebe 1;
					espera(lista->prox,lista,te,1);//chama a função para aumentar o tempo de espera dos outros processos.
					te+=1;//te mais recebe 1;
					SimulaPrioridade(lista,ultimo,te);//Chama a função novamente.
				}//Fim se;
				else{//Se o tempo de chegada for maior que te.
					SimulaPrioridade(lista->prox,ultimo,te);//Chama a função mandando o proximo da lista.
				}//fim se.
			}//Fim senão;
		}//fim se.
	else
		printf("TS- %d\tPrioridade- %d\n",ultimo->t_saida,ultimo->prioridade);//Imprime.
}//Fim SimulaPrioridade.
//Função responsavel pelo prioridade.
processo* GetPrioridade(processo* lista){//Recebe como parametro a lista.
	system("cls");//Limpa a tela.
	int te=lista->t_chegada;//cria te recebento o tempo de chegada do primeiro;
	lista=circular(lista,lista);//Faz a lista ficar circular.
	system("cls");//Limpa a tela.
	SimulaPrioridade(lista,NULL,te);//Chama a função que simulara o prioridade mandando a lista, nulo e te.
	imprime_2(lista,lista,0,1);//Chama a função para imprimir.
	printf("\n\n");//Pula duas linhas.
	system("PAUSE");//Espera uma tecla do ususrio;
	limpa_2(lista,lista,0);	//Chama a função para limpar os espaços de memoria utilizados pelo programa.
	return lista;//Retorna a lista ao programa principal.
}//fim GetPrioridade.
//Programa Principal. MENU.
int main(){
	setlocale(LC_ALL,"Portuguese");
	processo* lista=NULL;
	int numero;
	char op='0';
	while(op!='5'){
		system("cls");
		fflush(stdin);
		printf("\n\tALGORITMO DE ESCALONAMENTO.\n");
		printf("\n\t1- Para executar o FIFO.\n");
		printf("\n\t2- Para executar o SJF.\n");
		printf("\n\t3- Para executar o RAUND ROBIE.\n");
		printf("\n\t4- Para executar o PRIORIDADE.\n\t");
		printf("\n\t5- Para Sair do PROGRAMA.\n");
		scanf(" %c",&op);
		system("cls");
		if(op=='5')
				break;
		if(op>'0'&&op<'6'){
			system("cls");
			printf("\n\t___________________________________\n");
			printf("\n\tDigite a quantidade de processos.\n\t");
			scanf(" %d",&numero);
			if(numero<=0){
					printf("\n\tQuantidade Invalida.\n\n");
					system("PAUSE");
					system("cls");
					continue;
			}
			system("cls");
			switch(op){
				case '1':{
					lista=NULL;
					for(int i=0;i<numero;i+=1)
						lista=SetProcesso(lista,i);
					system("cls");
					lista=GetFifo(lista);	
					break;
				}
				case '2':{
					lista=NULL;
					for(int i=0;i<numero;i+=1)
						lista=SetProcesso(lista,i);
					system("cls");
					lista=GetSjf(lista);
					break;
				}
				case '3':{
					lista=NULL;
					for(int i=0;i<numero;i+=1)
						lista=SetProcesso(lista,i);
					system("cls");
					lista=GetRr(lista);
					break;
				}
				case '4':{
					lista=NULL;
					for(int i=0;i<numero;i+=1)
						lista=SetPrioridade(lista,i);
					system("cls");
					lista=GetPrioridade(lista);	
					break;
				}
			}
		}
		else{
			printf("\nOpção Invalida!\n");
			system("PAUSE");
		}
	}
}
