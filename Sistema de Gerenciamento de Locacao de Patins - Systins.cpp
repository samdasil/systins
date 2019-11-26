#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>


//	SISTEMA DE GERENCIAMENTO DE LOCAÇÃO DE PATINS
//		-DALYANA GÓES CAVALCANTE
//		-HELOYSE FERREIRA
//		-RENAN ARCANJO
//		-SAMMY SILVA
//	SISTEMAS DE INFORMAÇÃO - FAMETRO - 3º
//	DISCIPLINA: ESTRUTURA DE DADOS AVANÇADOS


//REGISTROS
typedef struct{
	char bairro[30], rua[50], cep[10];
	int nCasa;
}endereco;

typedef struct{
	int hor, min;
}hora;

typedef struct{
	int dia, mes, ano;
}data;

typedef struct{
	char nome[20], login[15], senha[15];
}administrador;

typedef struct{
	int matricula;
	char nome[50],rg[10], cpf[16],login[15], senha[15];
	endereco end;
}funcionario;

typedef struct{
	int codigo, tamanho, box;
	char modelo[20],status[20];
}patins;

typedef struct{
	char nome[50], cpf[16], rg[10];
	int tamanho;
}cliente;

typedef struct{
	float valor;
	int qtd_minutos;
}preco;

typedef struct{
	hora h_ini, h_fin;
	int codigo, patins, tempoTotal;
	float valorTotal,preco;
	char cliente[20],status[20];
	data date;
}aluguel;

//PROCEDIMENTOS
void CriarArquivos();
void Sobre(char nome[], int x);
void RealizarLogin(char loginp[],int x, char senhap[],int y);
void Administrador(administrador adm);
void Funcionario(funcionario f);

void CadastrarFuncionario(funcionario f, char nome[], int x);
void CadastrarPatins(patins p, char nome[], int x);
void CadastrarCliente(cliente c, char nome[], int x);
void RealizarAluguel(aluguel g, char nome[], int x);
void RealizarPagamento(aluguel g, char nome[], int x);

void ListarFuncionarios(funcionario f,char nome[], int x);
void ListarPatins(patins p, char nome[], int x);
void ListarClientes(cliente c, char nome[], int x);
void ListarAlugueisTudo(aluguel g, char nome[], int x);
void ListarAlugueisAbertos(aluguel g, char nome[], int x);

void PesquisarFuncionario(funcionario f, char nome[], int x);
void PesquisarPatins(patins p, char nome[], int x);
void PesquisarCliente(cliente c, char nome[], int x);
void PesquisarAluguel(aluguel g, char nome[], int x);

void AlterarFuncionario(funcionario f, char nome[], int x);
void AlterarPatins(patins p, char nome[], int x);
void AlterarCliente(cliente c, char nome[], int x);
void AlterarPreco(preco r, char nome[], int x);

void ExcluirFuncionario(funcionario f, char nome[], int x);
void ExcluirPatins(patins p, char nome[], int x);
void ExcluirCliente(cliente c, char nome[], int x);
void CancelarAluguel(aluguel g, char nome[], int x);

void RelatorioFaturamentoDiario(aluguel g, char nome[], int x);
void RelatorioFaturamentoMensal(aluguel g, char nome[], int x);

//FUNÇÕES
int ValidaMatricula(funcionario f);
int ValidaCpf(char cpf[], int x, char file[20], int y);
int ValidaBox(int box);
int IncrementaCodigoPatins();
int IncrementaCodigoAluguel();
int VerificarDisponibilidadePatins(int codPatins);
int AtualizarPatinsLocado(int codPatins);
int AtualizarPatinsDevolvido(int codPatins);
int ValidaData(int dia, int mes, int ano);
int ValidaExclusaoCliente(cliente c);
//preco LerPreco();

//PONTEIROS GLOBAIS
FILE *pf;// Ponteiro Funcionario
FILE *pc;// Ponteiro Cliente
FILE *pp;// Ponteiro Patins
FILE *pa;// Ponteiro Aluguel
FILE *pr;// Ponteiro pReco
//FUNCAO PRINCIPAL
int main(){

	char loginp[15];
    char senhap[15];
    char data[15];
    int tecla = 0;

    CriarArquivos();
    
    do{
	    system("color 3F");
	    system("cls");
	    
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\n\t                     [ENTER] Entrar no sistema                     \n");
		printf("\n\t                      [ESC]  Para sair digite                      \n");
		tecla = getch();
		
		if(tecla == 13){
			do{
				printf("\n\n\t\t\t\t  Login: ");
		    	fflush(stdin);
		    	gets(loginp);
			}while(strcmp(loginp,"")==0);
			do{
				printf("\n\t\t\t\t  Senha: ");
		    	fflush(stdin);
		    	gets(senhap);
			}while(strcmp(senhap,"")==0);
		
		    //procedimento ira verificar se é o administrador, se não for , passa para  teste de funcionario.
		    RealizarLogin(loginp,15,senhap,15);	
		}else if(tecla == 27){
			exit(0);
		}	
	}while((tecla != 27) && (tecla != 13));
		
}

//PROCEDIMENTO DE LOGIN
void RealizarLogin(char loginp[],int x, char senhap[],int y){
	administrador adm;
	funcionario f;
	int cont=0, tecla;

	//INICIALIZAÇÃO DO ADMINISTRADOR DO SISTEMA
	strcpy(adm.nome,"Administrador");
	strcpy(adm.login,"admin");
	strcpy(adm.senha,"123");

	//verificar se Administrador
	do{
		if((strcmp(strupr(adm.login),strupr(loginp))==0) && (strcmp(strupr(adm.senha),strupr(senhap))==0)){
			Administrador(adm);
		}else{
			if((pf = fopen("funcionarios.dat","rb")) == NULL){
				printf("\tErro ao verificar login e senha.\n");
				getch();
			}else{
				rewind(pf);
				while(!feof(pf)){
					fread(&f,sizeof(funcionario),1,pf);
					if(!feof(pf)){
						if((strcmp(strupr(f.login),strupr(loginp))==0) && (strcmp(strupr(f.senha),strupr(senhap))==0)){
							cont=1;
							Funcionario(f);
						}else{
							cont=0;
						}
					}
				}
				if(cont == 0){
					printf("\n\n\n\tLogin ou senha incorreto.\n");
					printf("\tPressione qualquer tecla para tentar novamente\n\tOu pressione a tecla [ESC] no teclado para SAIR.\n");
					tecla = getch();
					if(tecla == 27){
						exit(0);
					}else{
						main();
					}
				}
			}
		}
	}while(tecla != 27);
}

//PROCEDIMENTOS DE CADASTROS
void CadastrarFuncionario(funcionario f, char nome[], int x){
	char confirm, senha[20], cadeia[10], cpf[16], file[20];
	int res, valida, aux=0, flag=0;

	strcpy(file,"funcionarios.dat");
	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Funcionario -> Cadastro                                    |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Cadastro de Funcionario \t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	do{
		printf("\tMatricula : ");
		scanf("%d", &f.matricula);
		//validar matricula
		res = ValidaMatricula(f);

		if(res == 0){
			printf("\tMatricula ja existe. Informe outra.\n\n");
		}
		sprintf(cadeia, "%d",f.matricula);//coloca o inteiro como string
		//conta quantos caracteres tem a matricula
		if(strlen(cadeia)!= 5){
			printf("\tA matricula deve conter 5 digitos.\n\n");
		}
	}while((res == 0) || (strlen(cadeia) != 5));

	do{
		printf("\tNome e Sobrenome: ");
		fflush(stdin);
		gets(f.nome);
	}while(strcmp(f.nome,"")==0);

	do{
		printf("\tRG        : ");
		fflush(stdin);
		gets(f.rg);
	}while(strcmp(f.rg,"")==0);

	do{
		aux = 0;
		printf("\tCPF       : ");
		fflush(stdin);
		gets(f.cpf);
		strcpy(cpf,f.cpf);
		valida = ValidaCpf(cpf,16, file,20);
		if(strlen(cpf) != 11){
			printf("\tCPF nao tem 11 digitos. Verifique e tente novamente.\n");
			aux = 1;
		}
		if(valida == 0){
			printf("\tCPF ja cadastrado. Tente novamente\n");
			aux = 1;
		}
	}while((aux == 1) || (strcmp(f.cpf,"")==0));

	do{
		printf("\tBairro    : ");
		fflush(stdin);
		gets(f.end.bairro);
	}while(strcmp(f.end.bairro,"")==0);

	do{
		printf("\tRua       : ");
		fflush(stdin);
		gets(f.end.rua);
	}while(strcmp(f.end.rua,"")==0);

	do{
		printf("\tCep       : ");
		fflush(stdin);
		gets(f.end.cep);
	}while(strcmp(f.end.cep,"")==0);

	do{
		printf("\tNo Casa   : ");
		scanf("%d", &f.end.nCasa);
	}while(f.end.nCasa == NULL);

	do{
		printf("\tLogin     : ");
		fflush(stdin);
		gets(f.login);
	}while(strcmp(f.login,"")==0);

	do{
		printf("\tSenha     : ");
		fflush(stdin);
		gets(f.senha);
		printf("\tConfirme a senha: ");
		fflush(stdin);
		gets(senha);
		if(strcmp(f.senha,senha)!=0){
			printf("\tSenhas nao coincidem.Tente Novamente.\n");
		}
	}while((strcmp(f.senha,senha)!=0) || (strcmp(f.senha,"")==0 || strcmp(senha,"")==0));

	do{
		flag=0;
		printf("\t---------------------------------------------------------------------\n");
		printf("\tConfirme os dados e selecione se deseja salvar o Funcionario: %s ?\n",strupr(f.nome));
		printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao: [ ]\b\b");
		fflush(stdin);
		scanf("%c",&confirm);

		if(confirm == '1'){
			if((pf = fopen("funcionarios.dat","ab+")) == NULL){
				printf("\tErro ao tentar abrir arquivo.\nConsulte o programador.\n\t");
				getch();
				exit(0);

			}else{
				rewind(pf);
					fwrite(&f,sizeof(funcionario),1,pf);
				fclose(pf);

				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
				printf("\t|                Funcionario adicionado com sucesso!                |\n");
				printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
				flag=1;
			}

		}else if(confirm == '2'){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                       Operacao cancelada!                         |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
			flag=1;
		}else{
			printf("\n\tOpcao invalida.Tente novamente.\n");
		}
	}while(confirm != '1' && confirm != '2');
	system("pause");
}//fim procedimento cadastrar funcionario

void CadastrarPatins(patins p, char nome[], int x){
	char confirm;
	int res, aux=0, aux2=0, retBox, box;

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Patins -> Cadastro                                         |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Cadastro de Patins \t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	//do{
		res = IncrementaCodigoPatins();
		p.codigo = res;
		printf("\tCodigo  : %d\n",p.codigo);
		//scanf("%d", &p.codigo);
	//}while(p.codigo == NULL);

	do{
		printf("\tModelo  : ");
		fflush(stdin);
		gets(p.modelo);
	}while(strcmp(p.modelo,"")==0);

	do{
		printf("\tTamanho : ");
		scanf("%d", &p.tamanho);
	}while(p.tamanho == NULL);

	do{
		aux = 0;
		aux2 = 0;
		printf("\tBox     : ");
		scanf("%d", &p.box);
		box = p.box;
		retBox = ValidaBox(box);
		if(retBox == 0){
			printf("\tBox ja utilizado.\n\tTente outro.\n\n");
			aux = 1;
		}
		if((box <= 0) || (box >=20)){
			printf("\tBox invalido, limite = 20.\n");
			aux2=1;
		}
	}while((p.box == NULL) || (aux == 1) || (aux2 == 1));

	strcpy(p.status, "disponivel");

	do{
		printf("\t---------------------------------------------------------------------\n");
		printf("\tSalvar Patins: %s ?\n",strupr(p.modelo));
		printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao: [ ]\b\b");
		fflush(stdin);
		scanf("%c",&confirm);

		if(confirm == '1'){
			if((pp = fopen("patins.dat","ab+")) == NULL){
				printf("\tErro ao tentar abrir arquivo.\nConsulte o programador.\n\t");
				getch();
				exit(0);
			}else{
				rewind(pp);
					fwrite(&p,sizeof(patins),1,pp);
				fclose(pp);

				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
				printf("\t|                Patins adicionado com sucesso!                     |\n");
				printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
			}
		}else if(confirm == '2'){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                       Operacao cancelada!                         |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}else{
			printf("\n\tOpcao invalida.Tente novamente.\n");
		}
	}while(confirm != '1' && confirm != '2');
	system("pause");
}//fim procedimento cadastrar patins

void CadastrarCliente(cliente c, char nome[], int x){
	char confirm, cpf[20], file[20];
	int retCpf, aux = 0;

	strcpy(file,"clientes.dat");
	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Cliente -> Cadastro                                        |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Cadastro de Cliente\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	do{
		aux = 0;
		printf("\tCPF      : ");
		fflush(stdin);
		gets(c.cpf);
		strcpy(cpf,c.cpf);
		retCpf = ValidaCpf(cpf,20, file, 16);
		if(strlen(cpf) > 11){
			printf("\tCPF nao contem 11 digitos. Verifique e tente novamente.\n");
			aux = 1;
		}
		if(retCpf == 0 ){
			printf("\tCPF ja cadastrado.\n\tFavor verifique os dados e tente novamente.\n");
			aux = 1;
		}
	}while((strcmp(c.cpf,"")==0) || (aux == 1));

	do{
		printf("\tNome e Sobrenome: ");
		fflush(stdin);
		gets(c.nome);
	}while(strcmp(c.nome,"")==0);

	do{
		printf("\tRG       : ");
		fflush(stdin);
		gets(c.rg);
	}while(strcmp(c.rg,"")==0);

	do{
		printf("\tTamanho  : ");
		scanf("%d", &c.tamanho);
	}while(c.tamanho == NULL);

	do{
		printf("\t---------------------------------------------------------------------\n");
		printf("\tSalvar Cliente: %s ?\n",strupr(c.nome));
		printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao: [ ]\b\b");
		fflush(stdin);
		scanf("%c",&confirm);

		if(confirm == '1'){
			if((pc = fopen("clientes.dat","ab+")) == NULL){
				printf("\tErro ao tentar abrir arquivo.\nConsulte o programador.\n\t");
				getch();
				exit(0);
			}else{
				rewind(pc);
					fwrite(&c,sizeof(cliente),1,pc);
				fclose(pc);

				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
				printf("\t|                Cliente adicionado com sucesso!                    |\n");
				printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
			}
		}else if(confirm == '2'){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                       Operacao cancelada!                         |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}else{
			printf("\n\tOpcao invalida.Tente novamente.\n");
		}
	}while(confirm != '1' && confirm != '2');
	system("pause");
}//fim procedimento cadastrar cliente

void RealizarAluguel(aluguel g, char nome[], int x){
	char confirm, cpf[20], file[20];
	int aux=0, res, retCpf, resPat, codPatins, resAlter, valData, dia, mes, ano;
	preco r;

	strcpy(file,"clientes.dat");
	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Novo                                            |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t| Realizar Aluguel\t\t\t| Logado como: %s|\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	//do{
		res = IncrementaCodigoAluguel();
		g.codigo = res;
		printf("\tCodigo      : 	%d \n",g.codigo);
	//	scanf("%d", &g.codigo);
	//}while(g.codigo == NULL);

	do{
		aux = 0;
		printf("\tCPF-Cliente : ");
		fflush(stdin);
		gets(g.cliente);
		strcpy(cpf,g.cliente);
		retCpf = ValidaCpf(cpf,20, file, 20);
		if(strlen(cpf) > 11){
			printf("\tCPF contem mais de 11 digitos. Verifique e tente novamente.\n");
			aux = 1;
		}
		if(retCpf != 0 ){
			printf("\tCPF nao cadastrado.\n\tFavor verifique os dados e tente novamente.\n");
			aux = 1;
		}
	}while((strcmp(g.cliente,"")==0) || (aux == 1));

	do{
		aux = 0;
		printf("\tCod. Patins : ");
		scanf("%d", &g.patins);
		codPatins = g.patins;
		resPat = VerificarDisponibilidadePatins(codPatins);
		if(resPat == 0){
			//printf("\tPatins indisponivel, ja esta alugado.\n");
			aux = 1;
		}
	}while((g.patins == NULL) || (aux == 1));

	printf("\t--- Hora Inicio --- \n");
	do{
		aux = 0;
		printf("\tHora (hh)   : ");
		scanf("%d", &g.h_ini.hor);
		if((g.h_ini.hor < 0) || (g.h_ini.hor > 23)){
			printf("\tHora invalida. Tente novamente.\n\t");
			g.h_ini.hor=0;
			system("pause");
			aux=1;
		}
		//printf("\taux = %d\n",aux);
	}while((g.h_ini.hor == NULL) || (aux != 0));

	do{
		aux=0;
		printf("\tMinuto (mm) : ");
		scanf("%d", &g.h_ini.min);
		if((g.h_ini.min < 0) || (g.h_ini.min > 59)){
			printf("\tMinuto invalido. Tente novamente.\n\t");
			g.h_ini.min=0;
			system("pause");
			aux=1;
		}
	}while((g.h_ini.min == NULL) || (aux != 0));

	printf("\t----- Data ----- \n");
	do{
		printf("\tDia: ");
		scanf("%d", &g.date.dia);
		dia = g.date.dia;
		printf("\tMes: ");
		scanf("%d", &g.date.mes);
		mes = g.date.mes;
		printf("\tAno: ");
		scanf("%d", &g.date.ano);
		ano = g.date.ano;
		valData = ValidaData(dia,mes,ano);
		if(valData == 0){
			//funcao esta retornando mensagem de erro
			getch();
		}
	}while(valData == 0);

	//lendo o preco do arquivo
	if((pr = fopen("preco.dat","rb"))==NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pr);
		while(!feof(pr)){
			fread(&r,sizeof(preco),1,pr);
		}
	}
	
	//LerPreco();

	g.preco      = (r.valor / r.qtd_minutos);
	fclose(pr);
	g.h_fin.hor  = 0;
	g.h_fin.min  = 0;
	g.tempoTotal = 0;
	g.valorTotal = 0;
	strcpy(g.status,"aberto");
	
	do{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Aluguel -> Novo                                            |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t| Realizar Aluguel\t\t\t| Logado como: %s|\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\t+-------------------------------------------------------------------+");
		printf("\n\n\tCodigo      : %d ",g.codigo);
		printf("\n\tCliente     : %s ",g.cliente);
		//printf("\n\tCPF         : %s ",cpf);//nao fica salvo no arquivo só é exibido
		printf("\n\tPatins      : %d ",g.patins);
		printf("\n\tHora Inicial: %d:%dh ",g.h_ini.hor,g.h_ini.min);
//		printf("\n\tHora Final  : %d:%dh ",g.h_fin.hor,g.h_fin.min);
//		printf("\n\tTempo Total : %dminutos ",g.tempoTotal);
//		printf("\n\tValor Total : R$ %.2f ",g.valorTotal);
		printf("\n\tData        : %d-%d-%d",g.date.dia,g.date.mes,g.date.ano);
		printf("\n\tStatus      : %s ",g.status);
		printf("\n\n\t+-------------------------------------------------------------------+\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tConfirmar: Salvar Aluguel ?\n");
		printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao: [ ]\b\b");
		fflush(stdin);
		scanf("%c",&confirm);

		if(confirm == '1'){
			if((pa = fopen("aluguel.dat","ab+")) == NULL){
				printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
				exit(0);
			}else{
				resAlter = AtualizarPatinsLocado(codPatins);
				if(resAlter == 1){
					rewind(pa);
						fwrite(&g,sizeof(aluguel),1,pa);
					fclose(pa);

					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
					printf("\t|                Aluguel realizado com sucesso!                     |\n");
					printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
				}else{
					printf("\tErro ao tentar salvar dados.\n\tConsulte o programador.\n\t");
					getch();
					exit(0);
				}
			}
		}else if(confirm == '2'){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                       Operacao cancelada!                         |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}else{
			printf("\n\tOpcao invalida.Tente novamente.\n");
		}
	}while(confirm != '1' && confirm != '2');
	system("pause");

}// fim procedimento realizar aluguel


//PROCEDIMENTOS DE LISTAR
void ListarFuncionarios(funcionario f,char nome[], int x){

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Funcionario -> Listar                                      |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Listar Funcionarios\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	if((pf = fopen("funcionarios.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pf);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t|MATRIC\t|    NOME\t |     CPF\t |   RG \t | LOGIN    |\n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pf)){
				fread(&f,sizeof(funcionario),1,pf);
				if(!feof(pf)){
					printf("\n\t|%d\t| %s\t |  %s\t |  %s\t | %s ",f.matricula,f.nome, f.cpf, f.rg, f.login);
					printf("\n\t+-------------------------------------------------------------------+");
				}
			}
		fclose(pf);
	}
	printf("\n\t");
	system("pause");
}// fim procedimento listar funcionario

void ListarPatins(patins p, char nome[], int x){

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Patins -> Listar                                           |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Listar Patins\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	if((pp = fopen("patins.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pp);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t|CODIGO\t|    MODELO\t|   TAMANHO\t|  BOX\t|     STATUS \t\n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pp)){
				fread(&p,sizeof(patins),1,pp);
				if(!feof(pp)){
					printf("\n\t|  %d\t|   %s\t|      %d \t|   %d\t|   %s  \t",p.codigo,p.modelo, p.tamanho, p.box, p.status);
					printf("\n\t+-------------------------------------------------------------------+");
				}
			}
		fclose(pp);
	}
	printf("\n\t");
	system("pause");
}// fim procediemento listar patins

void ListarClientes(cliente c, char nome[], int x){

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Cliente -> Listar                                          |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Listar Clientes\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	if((pc = fopen("clientes.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pc);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t|   CPF  \t|    NOME  \t\t|       RG  \t |  TAMANHO\t\n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pc)){
				fread(&c,sizeof(cliente),1,pc);
				if(!feof(pc)){
					printf("\n\t|  %s\t|     %s\t |   %s\t |   %d\t",c.cpf,c.nome, c.rg, c.tamanho);
					printf("\n\t+-------------------------------------------------------------------+");
				}
			}
		fclose(pc);
	}
	printf("\n\t");
	system("pause");
}// fim procediemento listar cliente

void ListarAlugueisTudo(aluguel g, char nome[], int x){

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Listar                                          |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Listar Alugueis\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	if((pa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pa);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t| COD\t| CPF-CLIENTE\t | TEMPO\t|  VALOR    |PATINS |STATUS\t \n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pa)){
				fread(&g,sizeof(aluguel),1,pa);
				if(!feof(pa)){
					printf("\n\t|  %d\t| %s\t | %dmin\t|  R$%.2f  |  %d    |%s |",g.codigo, g.cliente, g.tempoTotal, g.valorTotal, g.patins, g.status);
					printf("\n\t+-------------------------------------------------------------------+");
				}
			}
			//printf("\n\n\tValor total diario: R$ ");
		fclose(pa);
	}
	printf("\n\t");
	system("pause");
}// fim procediemento listar todos os alugueis fechados e abertos

void ListarAlugueisAbertos(aluguel g, char nome[], int x){

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Listar                                          |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Listar Alugueis em Andamento\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	if((pa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pa);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t| COD\t| CPF-CLIENTE\t |  INICIO  |   DATA    | PATINS  |STATUS\t \n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pa)){
				fread(&g,sizeof(aluguel),1,pa);
				if(!feof(pa)){
					if(strcmp(g.status,"aberto")==0){
						printf("\n\t|  %d\t| %s\t |  %d:%dh  | %d-%d-%d |   %d\t | %s  |",g.codigo, g.cliente, g.h_ini.hor, g.h_ini.min, g.date.dia, g.date.mes, g.date.ano, g.patins, g.status);
						printf("\n\t+-------------------------------------------------------------------+");
					}
				}
			}
		fclose(pa);
	}
	printf("\n\t");
	system("pause");
}// fim procediemento listar alugueis abertos


//PROCEDIMENTOS DE ALTERAÇÃO
void RealizarPagamento(aluguel g, char nome[], int x){
	int codAluguel, codPatins, i=0, flag = 0, aux=0, hi, hf, mi, mf, retDev;

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Realizar Pagamento                              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t| Realizar Pagamento\t\t\t| Logado como: %s|\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	printf("\tInforme o codigo do aluguel: ");
	scanf("%d",&codAluguel);

	if((pa = fopen("aluguel.dat","rb+")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pa);

			printf("\t+-------------------------------------------------------------------+");
			printf("\n\t| COD\t| CPF-CLIENTE\t |   INICIO  | VALOR R$  | PATINS |STATUS\t \n");
			printf("\t+-------------------------------------------------------------------+");

			while(!feof(pa)){
				fread(&g,sizeof(aluguel),1,pa);
				if((g.codigo == codAluguel) && (strcmp(g.status,"aberto")==0)){
					codPatins = g.patins;
					printf("\n\t|  %d\t|%s\t | %d:%d min | %.2f\t  |  %d\t  | %s\t |",g.codigo, g.cliente, g.h_ini.hor,g.h_ini.min , g.valorTotal, g.patins, g.status);
					printf("\n\t+-------------------------------------------------------------------+");

					printf("\n\n\t--- Informe a Hora Final --- \n");
					do{
						aux = 0;
						printf("\tHora (hh)   : ");
						scanf("%d", &g.h_fin.hor);
						if((g.h_fin.hor < 0) || (g.h_fin.hor > 24) || (g.h_fin.hor < g.h_ini.hor)){
							printf("\tHora invalida. Tente novamente.\n\t");
							g.h_fin.hor=0;
							aux=1;
						}
						//printf("\taux = %d\n",aux);
					}while((g.h_fin.hor == NULL) || (aux != 0));

					do{
						aux=0;
						printf("\tMinuto (mm) : ");
						scanf("%d", &g.h_fin.min);
						if((g.h_fin.min < 0) || (g.h_fin.min > 59) || ((g.h_ini.hor == g.h_fin.hor) && (g.h_fin.min < g.h_ini.min))){
							printf("\tMinuto invalido. Tente novamente.\n\t");
							g.h_fin.min=0;
							system("pause");
							aux=1;
						}
					}while((g.h_fin.min == NULL) || (aux != 0));

					hi = g.h_ini.hor;
					hf = g.h_fin.hor;
					mi = g.h_ini.min;
					mf = g.h_fin.min;
					g.tempoTotal = 0;

					do{
						if(hi < hf){

							if(mi == 0){
								mi=60;
							}else{
								mi = 60 - mi;
							}

							g.tempoTotal += mi;
							mi=0;
							hi++;
							if(hi == hf){
								g.tempoTotal += mf;
								break;
							}
						}else{
							if(hi == hf){
								g.tempoTotal = mf-mi;
							}
						}
					}while(hi != hf);

					g.valorTotal = g.preco * g.tempoTotal;
					strcpy(g.status,"fechado");
					
					printf("\n\t+-------------------------------------------------------------------+");
					printf("\n\tTempo Total : %d minutos",g.tempoTotal);
					printf("\n\tValor Total : R$ %.2f\n\t",g.valorTotal);
					printf("\n\t+-------------------------------------------------------------------+");
					printf("\n\t[Confirmar]");
					getch();
					//atualizando os valores no banco
					retDev = AtualizarPatinsDevolvido(codPatins);
					if(retDev == 1){
						fseek(pa, i * sizeof(aluguel), SEEK_SET);
						fwrite(&g,sizeof(aluguel),1,pa);

						system("cls");
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
						printf("\t|                Aluguel finalizado com sucesso!                    |\n");
						printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
						flag = 1;
						system("pause");
						break;
					}else{
						printf("\tErro ao tentar salvar os dados.\n\tContate o programador.\n");
						getch();
						exit(0);
					}

				}
				i++;
			}
			if(flag == 0){
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
				printf("\t|                Nenhum registro encontrado!                        |\n");
				printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
				system("pause");
			}
		fclose(pa);
	}
}

int AtualizarPatinsLocado(int codPatins){
	int i=0, flag = 0;
	patins p;

	if((pp = fopen("patins.dat","rb+"))== NULL){
		printf("\tErro ao tentar abrir o arquivo. \n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		rewind(pp);
			while(!feof(pp)){
				fread(&p, sizeof(patins),1,pp);
				if(!feof(pp)){
					if(p.codigo == codPatins){
						strcpy(p.status,"alugado");
						fseek(pp,i * sizeof(patins), SEEK_SET);
						fwrite(&p,sizeof(patins),1,pp);
						flag = 1;
						break;
					}
				}
				i++;
			}
		fclose(pp);
	}
	if(flag == 0){
		return 0;
	}else{
		return 1;
	}
}

int AtualizarPatinsDevolvido(int codPatins){
	int i=0, flag = 0;
	patins p;

	if((pp = fopen("patins.dat","rb+"))== NULL){
		printf("\tErro ao tentar abrir o arquivo. \n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		rewind(pp);
			while(!feof(pp)){
				fread(&p, sizeof(patins),1,pp);
				if(!feof(pp)){
					if(p.codigo == codPatins){
						strcpy(p.status,"disponivel");
						fseek(pp,i * sizeof(patins), SEEK_SET);
						fwrite(&p,sizeof(patins),1,pp);
						flag = 1;
						break;
					}
				}
				i++;
			}
		fclose(pp);
	}
	if(flag == 0){
		return 0;//erro
	}else{
		return 1;//devolvido
	}
}

void AlterarFuncionario(funcionario f, char nome[], int x){
	char confirm, senha[20], cpf[16];
	FILE *paf;
	funcionario f2;
	int cont=0, pesqFunc=0, flag=0, aux=0, valida;

	if((paf = fopen("funcionarios.dat","rb+"))== NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Funcionario -> Alterar                                     |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Atualizacao de Funcionario \t\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\n\tMatricula do Funcionario: ");
		scanf("%d", &pesqFunc);

		rewind(paf);
			while(!feof(paf)){
				fread(&f,sizeof(funcionario),1,paf);

				if(pesqFunc == f.matricula){
					aux=1;
					printf("\t+-------------------------------------------------------------------+");
					printf("\n\n\tMatricula   :*** %d ***",f.matricula);
					printf("\n\tNome        : %s ",f.nome);
					printf("\n\tRG          : %s ",f.rg);
					printf("\n\tCPF         : %s ",f.cpf);
					printf("\n\tBairro      : %s ",f.end.bairro);
					printf("\n\tCEP         : %s ",f.end.cep);
					printf("\n\tRua         : %s ",f.end.rua);
					printf("\n\tNo Casa     : %d ",f.end.nCasa);
					printf("\n\tLogin       : %s ",f.login);
					printf("\n\t+-------------------------------------------------------------------+");

					printf("\n\n\tNovos dados: ");

					printf("\n\n\tMatricula : %d \n",f.matricula);

					do{
						printf("\tNome e Sobrenome: ");
						fflush(stdin);
						gets(f.nome);
					}while(strcmp(f.nome,"")==0);

					do{
						printf("\tRG        : ");
						fflush(stdin);
						gets(f.rg);
					}while(strcmp(f.rg,"")==0);

					printf("\tCPF       : *** %d ***\n", f.cpf);


					do{
						printf("\tBairro    : ");
						fflush(stdin);
						gets(f.end.bairro);
					}while(strcmp(f.end.bairro,"")==0);

					do{
						printf("\tCep       : ");
						fflush(stdin);
						gets(f.end.cep);
					}while(strcmp(f.end.cep,"")==0);

					do{
						printf("\tRua       : ");
						fflush(stdin);
						gets(f.end.rua);
					}while(strcmp(f.end.rua,"")==0);

					do{
						printf("\tNo Casa   : ");
						scanf("%d", &f.end.nCasa);
					}while(f.end.nCasa == NULL);

					do{
						printf("\tLogin     : ");
						fflush(stdin);
						gets(f.login);
					}while(strcmp(f.login,"")==0);

					do{
						printf("\tSenha     : ");
						fflush(stdin);
						gets(f.senha);
						printf("\tConfirme a senha: ");
						fflush(stdin);
						gets(senha);
						if(strcmp(f.senha,senha)!=0){
							printf("\tSenhas nao coincidem.Tente Novamente.\n");
						}
					}while((strcmp(f.senha,senha)!=0) || (strcmp(f.senha,"")==0 || strcmp(senha,"")==0));

					do{
						flag=0;
						system("color CF");
						printf("\t---------------------------------------------------------------------\n");
						printf("\tConfirme os dados e selecione se deseja salvar \n\tatualizacao do Funcionario: %s\n",strupr(f.nome));
						printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n\n");
						printf("\t---------------------------------------------------------------------\n");
						printf("\tOpcao: [ ]\b\b");
						fflush(stdin);
						scanf("%c",&confirm);

						switch(confirm){
							case '1':{
								fseek(paf,cont * sizeof(funcionario),SEEK_SET );
								fwrite(&f,sizeof(funcionario),1,paf);

								system("cls");
								printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
								printf("\t|                Funcionario atualizado com sucesso!                |\n");
								printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
								flag = 1;
								break;
							}
							case '2':{
								system("cls");
								printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
								printf("\t|                       Operacao cancelada!                         |\n");
								printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
								flag = 1;
								break;
							}
							default:{
								printf("\n\tOpcao invalida.Tente novamente.\n");
								flag = 0;
							}
						}
					}while(flag != 1);
				}//fim do if de comparacao
				cont++;
				if(flag == 1){
					break;
				}
			}//fim do while de funcionario
		fclose(paf);
		if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum funcionario encontado!                      |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	}
	system("pause");
}

void AlterarPatins(patins p, char nome[], int x){
	char confirm;
	FILE *pap;
	patins p2;
	int cont=0, pesqPatins=0, flag=0, aux=0, valida, aux2=0, valBox=0, box=0, retBox=0, i=0;

	if((pap = fopen("patins.dat","rb+"))== NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Patins -> Alterar                                          |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Atualizacao de Patins\t\t\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\n\tCodigo do Patins: ");
		scanf("%d", &pesqPatins);

		rewind(pap);
			while(!feof(pap)){
				fread(&p,sizeof(patins),1,pap);
				if(!feof(pap)){
					if(pesqPatins == p.codigo){
						i=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCodigo      :*** %d ***",p.codigo);
						printf("\n\tModelo      : %s ",p.modelo);
						printf("\n\tBox         : %d ",p.box);
						printf("\n\tTamanho     : %d ",p.tamanho);
						printf("\n\tStatus      : %s \n",p.status);
						printf("\n\t+-------------------------------------------------------------------+");
						valBox = p.box;//para fazer a atualização com o mesmo box
						if(strcmp(p.status,"alugado")==0){
							printf("\n\n\tErro! Patins alugado, aguarde a devolucao.\n\n\t");
						}else{
							printf("\n\n\tNovos dados: ");

							printf("\n\n\tCodigo      :*** %d ***\n",p.codigo);

							do{
								printf("\tModelo      : ");
								fflush(stdin);
								gets(p.modelo);
							}while(strcmp(p.modelo,"")==0);

							do{
								aux = 0;
								aux2 = 0;
								printf("\tBox         : ");
								scanf("%d", &p.box);
								box = p.box;
								if(box == valBox){
									aux=0;
									aux2=0;
								}else{
									retBox = ValidaBox(box);
									if(retBox == 0){
										printf("\tBox ja utilizado.\n\tTente outro.\n\n");
										aux = 1;
									}
									if((box <= 0) || (box >=20)){
										printf("\tBox invalido, limite = 20.\n");
										aux2=1;
									}
								}

							}while((p.box == NULL) || (aux == 1) || (aux2 == 1));

							do{
								printf("\tTamanho     : ");
								scanf("%d", &p.tamanho);
							}while(p.tamanho == NULL);

							printf("\tStatus      : %s \n", p.status);

							do{
								flag=0;
								system("color CF");
								printf("\t---------------------------------------------------------------------\n");
								printf("\tConfirme os dados e selecione se deseja salvar \n\tatualizacao do Patins: %d\n",p.codigo);
								printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n\n");
								printf("\t---------------------------------------------------------------------\n");
								printf("\tOpcao: [ ]\b\b");
								fflush(stdin);
								scanf("%c",&confirm);

								switch(confirm){
									case '1':{
										fseek(pap,cont * sizeof(patins),SEEK_SET );
										fwrite(&p,sizeof(patins),1,pap);
										
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                Patins atualizado com sucesso!                     |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 1;
										break;
									}
									case '2':{
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                       Operacao cancelada!                         |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 1;
										break;
									}
									default:{
										printf("\n\tOpcao invalida.Tente novamente.\n");
										flag = 0;
									}
								}
							}while(flag != 1);
						}
					}//fim do if de comparacao
				}//fim de if do feof
				cont++;
				if(flag == 1){
					break;
				}
			}//fim do while de patins
		fclose(pap);
		if(i == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum patins encontado!                           |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	}//fim do else de abertura do arquivo para leitura/escrita
	system("pause");
}//fim do procedimento alterar patins

void AlterarCliente(cliente c, char nome[], int x){
	char confirm, senha[20], cpf[16], pesqCli[20];
	FILE *pac;
	cliente c2;
	int cont=0, flag=0, aux=0, valida;

	if((pac = fopen("clientes.dat","rb+"))== NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Cliente -> Alterar                                         |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Atualizacao de Cliente   \t\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\n\tCPF: ");
		fflush(stdin);
		gets(pesqCli);

		rewind(pac);
			while(!feof(pac)){
				fread(&c,sizeof(cliente),1,pac);

				if(strcmp(pesqCli,c.cpf)==0){
					aux=1;
					printf("\t+-------------------------------------------------------------------+");
					printf("\n\n\tCPF         :*** %s *** ",c.cpf);
					printf("\n\tNome        : %s ",c.nome);
					printf("\n\tRG          : %s ",c.rg);
					printf("\n\tTamanho     : %d \n",c.tamanho);
					printf("\n\t+-------------------------------------------------------------------+");

					printf("\n\n\tNovos dados: ");

					printf("\n\n\tCPF         : %s \n",c.cpf);

					do{
						printf("\tNome        : ");
						fflush(stdin);
						gets(c.nome);
					}while(strcmp(c.nome,"")==0);

					do{
						printf("\tRG          : ");
						fflush(stdin);
						gets(c.rg);
					}while(strcmp(c.rg,"")==0);

					do{
						printf("\tTamanho     : ");
						scanf("%d", &c.tamanho);
					}while(c.tamanho == NULL);

					do{
						flag=0;
						system("color CF");
						printf("\t---------------------------------------------------------------------\n");
						printf("\tConfirme os dados e selecione se deseja salvar \n\tatualizacao do Cliente: %s\n",strupr(c.nome));
						printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n\n");
						printf("\t---------------------------------------------------------------------\n");
						printf("\tOpcao: [ ]\b\b");
						fflush(stdin);
						scanf("%c",&confirm);

						switch(confirm){
							case '1':{
								fseek(pac,cont * sizeof(cliente),SEEK_SET );
								fwrite(&c,sizeof(cliente),1,pac);

								system("cls");
								printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
								printf("\t|                Cliente atualizado com sucesso!                    |\n");
								printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
								flag = 1;
								break;
							}
							case '2':{
								system("cls");
								printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
								printf("\t|                       Operacao cancelada!                         |\n");
								printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
								flag = 1;
								break;
							}
							default:{
								printf("\n\tOpcao invalida.Tente novamente.\n");
								flag = 0;
							}
						}
					}while(flag != 1);
				}//fim do if de comparacao
				cont++;
				if(flag == 1){
					break;
				}
			}//fim do while de funcionario
		fclose(pac);
		if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum cliente encontado!                          |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	}
	system("pause");
}// fim do procedimento alterar cliente

void AlterarPreco(preco r, char nome[], int x){
	char confirm;
	int flag=0;

	if((pr = fopen("preco.dat","wb"))== NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tContate o programador.\n");
		getch();
		exit(0);
	}else{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Preco   -> Alterar                                         |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Alteracao de Preco     \t\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\tValor    : ");
		scanf("%f",&r.valor);
		printf("\tQuantidade de Minutos: ");
		scanf("%d",&r.qtd_minutos);


		do{
			flag=0;
			system("color CF");
			printf("\n\t---------------------------------------------------------------------\n");
			printf("\tConfirme os dados e selecione se deseja salvar \n\talteracao de Preco:\n");
			printf("\t\n\t1 - Salvar\n\t2 - Cancelar\n\n");
			printf("\t---------------------------------------------------------------------\n");
			printf("\tOpcao: [ ]\b\b");
			fflush(stdin);
			scanf("%c",&confirm);

			switch(confirm){
				case '1':{
					fwrite(&r,sizeof(preco),1,pr);

					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
					printf("\t|                Preco atualizado com sucesso!                      |\n");
					printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
					flag = 1;
					break;
				}
				case '2':{
					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
					printf("\t|                       Operacao cancelada!                         |\n");
					printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
					flag = 1;
					break;
				}
				default:{
					printf("\n\tOpcao invalida.Tente novamente.\n");
					flag = 0;
				}
			}
		}while(flag != 1);
	}
	fclose(pr);
	system("pause");
}

//PROCEDIMENTOS DE PESQUISA

void PesquisarFuncionario(funcionario f, char nome[], int x){
	int pesqFunc, aux=0;

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Funcionario -> Listar                                      |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Pesquisar Funcionario\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tMatricula do Funcionario: ");
	scanf("%d", &pesqFunc);

	if((pf = fopen("funcionarios.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pf);
			while(!feof(pf)){
				fread(&f,sizeof(funcionario),1,pf);
				if(!feof(pf)){
					if(pesqFunc == f.matricula){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tMatricula   : %d ",f.matricula);
						printf("\n\tNome        : %s ",f.nome);
						printf("\n\tRG          : %s ",f.rg);
						printf("\n\tCPF         : %s ",f.cpf);
						printf("\n\tBairro      : %s ",f.end.bairro);
						printf("\n\tCEP         : %s ",f.end.cep);
						printf("\n\tRua         : %s ",f.end.rua);
						printf("\n\tNo Casa     : %d ",f.end.nCasa);
						printf("\n\tLogin       : %s ",f.login);
						printf("\n\n\t+-------------------------------------------------------------------+");
					}
				}
			}
		fclose(pf);
	}
	printf("\n\t");
	if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum funcionario encontado!                      |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	system("pause");
}// fim procedimento pesquisar funcionario

void PesquisarPatins(patins p, char nome[], int x){
	int pesqPatins, aux=0;

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Patins -> Listar                                           |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Pesquisar Patins\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCodigo do Patins: ");
	scanf("%d", &pesqPatins);

	if((pf = fopen("patins.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pp);
			while(!feof(pp)){
				fread(&p,sizeof(patins),1,pp);
				if(!feof(pp)){
					if(pesqPatins == p.codigo){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCodigo      :*** %d ***",p.codigo);
						printf("\n\tModelo      : %s ",p.modelo);
						printf("\n\tBox         : %d ",p.box);
						printf("\n\tTamanho     : %d ",p.tamanho);
						printf("\n\tStatus      : %s \n",p.status);
						printf("\n\t+-------------------------------------------------------------------+");
					}
				}
			}
		fclose(pp);
	}
	printf("\n\t");
	if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum patins encontado!                           |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	system("pause");
}// fim procedimento pesquisar patins

void PesquisarCliente(cliente c, char nome[], int x){
	int aux=0;
	char pesqCli[20];

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Cliente -> Listar                                          |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Pesquisar Cliente\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCPF  : ");
	fflush(stdin);
	gets(pesqCli);

	if((pc = fopen("clientes.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pc);
			while(!feof(pc)){
				fread(&c,sizeof(cliente),1,pc);
				if(!feof(pc)){
					if(strcmp(pesqCli, c.cpf)==0){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCPF         :*** %s *** ",c.cpf);
						printf("\n\tNome        : %s ",c.nome);
						printf("\n\tRG          : %s ",c.rg);
						printf("\n\tTamanho     : %d \n",c.tamanho);
						printf("\n\t+-------------------------------------------------------------------+");
					}
				}
			}
		fclose(pc);
	}
	printf("\n\t");
	if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum cliente encontado!                          |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	system("pause");
}// fim procedimento pesquisar cliente

void PesquisarAluguel(aluguel g, char nome[], int x){
	int aux=0;
	char pesqAluguel[20];

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Listar Alugueis                                 |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Pesquisar Aluguel\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCPF do Cliente: ");
	fflush(stdin);
	gets(pesqAluguel);

	if((pa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pa);
			while(!feof(pa)){
				fread(&g,sizeof(aluguel),1,pa);
				if(!feof(pa)){
					if(strcmp(pesqAluguel, g.cliente)==0){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCodigo      : %d ",g.codigo);
						printf("\n\tCliente     : %s ",g.cliente);
						//printf("\n\tCPF         : %s ",cpf);//nao fica salvo no arquivo só é exibido
						printf("\n\tPatins      : %d ",g.patins);
						printf("\n\tHora Inicial: %d:%dh ",g.h_ini.hor,g.h_ini.min);
						printf("\n\tHora Final  : %d:%dh ",g.h_fin.hor,g.h_fin.min);
						printf("\n\tTempo Total : %dminutos ",g.tempoTotal);
						printf("\n\tValor Total : R$ %.2f ",g.valorTotal);
						printf("\n\tData        : %d-%d-%d",g.date.dia,g.date.mes,g.date.ano);
						printf("\n\tStatus      : %s ",g.status);
						printf("\n\n\t+-------------------------------------------------------------------+\n");
					}
				}
			}
		fclose(pa);
	}
	printf("\n\t");
	if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum aluguel encontado!                          |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	system("pause");
}// fim procedimento pesquisar aluguel

//PROCEDIMENTOS DE EXCLUSÃO
void ExcluirFuncionario(funcionario f, char nome[], int x){
	int pesqFunc, flag=0, cont=0, aux=0;
	funcionario *f2;
	char del;

	f2 = (funcionario*)malloc(1000*sizeof(funcionario));

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Funcionario -> Excluir                                     |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Excluir Funcionario\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tMatricula do Funcionario: ");
	scanf("%d", &pesqFunc);

	if((pf = fopen("funcionarios.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pf);
			while(!feof(pf)){
				flag=0;
				fread(&f,sizeof(funcionario),1,pf);
				if(!feof(pf)){
					if(pesqFunc == f.matricula){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tMatricula   : %d ",f.matricula);
						printf("\n\tNome        : %s ",f.nome);
						printf("\n\tRG          : %s ",f.rg);
						printf("\n\tCPF         : %s ",f.cpf);
						printf("\n\tBairro      : %s ",f.end.bairro);
						printf("\n\tCEP         : %s ",f.end.cep);
						printf("\n\tRua         : %s ",f.end.rua);
						printf("\n\tNo Casa     : %d ",f.end.nCasa);
						printf("\n\tLogin       : %s ",f.login);
						printf("\n\n\t+-------------------------------------------------------------------+");

						do{
							flag=0;
							system("color 4F");
							printf("\n\n\tTem certeza que deseja excluir ? ");
							printf("\n\t1 - Sim");
							printf("\n\t2 - Nao");
							printf("\n\n\t+-------------------------------------------------------------------+");
							printf("\n\tOpcao [ ]\b\b");
							fflush(stdin);
							scanf("%c", &del);;

							switch(del){
								case '1':{
									system("cls");
									printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
									printf("\t|                Funcionario deletado com sucesso!                |\n");
									printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
									flag = 1;
									break;
								}
								case '2':{
									system("cls");
									printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
									printf("\t|                       Operacao cancelada!                         |\n");
									printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
									flag = 2;
									break;
								}
								default:{
									printf("\n\tOpcao invalida.Tente novamente.\n");
									flag = 0;
								}
							}//fim switch de confirmacao do deletar
						}while((flag != 1) && (flag != 2));

					}//fim de comparacao de matricula
					if(flag != 1){
						f2[cont].matricula = f.matricula;
						strcpy(f2[cont].nome,f.nome);
						strcpy(f2[cont].rg,f.rg);
						strcpy(f2[cont].cpf,f.cpf);
						strcpy(f2[cont].end.bairro,f.end.bairro);
						strcpy(f2[cont].end.cep,f.end.cep);
						strcpy(f2[cont].end.rua,f.end.rua);
						f2[cont].end.nCasa = f.end.nCasa;
						strcpy(f2[cont].login,f.login);
						strcpy(f2[cont].senha,f.senha);
						cont++;
					}
				}//fim de if de feof de arquivo
			}//fim do while
		fclose(pf);
	}//fim do if de abertura do arquivo para leitura

	if(aux==1){
		if((pf = fopen("funcionarios.dat","wb+")) == NULL){
			printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		}else{
			fwrite(f2,sizeof(funcionario),cont,pf);
			fclose(pf);
		}
	}else{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
		printf("\t|                Nenhum funcionario encontado!                    |\n");
		printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
	}

	printf("\n\t");
	system("pause");
}// fim procedimento excluir funcionario

void ExcluirPatins(patins p, char nome[], int x){
	int pesqPatins, flag=0, cont=0, aux=0;
	patins *p2;
	char del;

	p2 = (patins*)malloc(20*sizeof(patins));

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Patins -> Excluir                                          |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Excluir Patins\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCodigo do Patins :");
	scanf("%d", &pesqPatins);

	if((pp = fopen("patins.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pp);
			while(!feof(pp)){
				flag=0;
				fread(&p,sizeof(patins),1,pp);
				if(!feof(pp)){
					if(pesqPatins == p.codigo){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCodigo     :*** %d ***",p.codigo);
						printf("\n\tModelo      : %s ",p.modelo);
						printf("\n\tBox         : %d ",p.box);
						printf("\n\tTamanho     : %d ",p.tamanho);
						printf("\n\tStatus      : %s \n",p.status);
						printf("\n\t+-------------------------------------------------------------------+");

						if(strcmp(p.status,"alugado")==0){
							printf("\n\n\tErro! Patins alugado, aguarde a devolucao.\n\n\t");
						}else{
							do{
								flag=0;
								system("color 4F");
								printf("\n\n\tTem certeza que deseja excluir ? ");
								printf("\n\t1 - Sim");
								printf("\n\t2 - Nao");
								printf("\n\n\t+-------------------------------------------------------------------+");
								printf("\n\tOpcao [ ]\b\b");
								fflush(stdin);
								scanf("%c", &del);;

								switch(del){
									case '1':{
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                Patins deletado com sucesso!                       |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 1;
										break;
									}
									case '2':{
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                       Operacao cancelada!                         |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 2;
										break;
									}
									default:{
										printf("\n\tOpcao invalida.Tente novamente.\n");
										flag = 0;
									}
								}//fim switch de confirmacao do deletar
							}while((flag != 1) && (flag != 2));
						}//fim da condicao que verifica se esta alugado
					}//fim de comparacao de matricula
					if(flag != 1){
						p2[cont].codigo = p.codigo;
						strcpy(p2[cont].modelo,p.modelo);
						p2[cont].box = p.box;
						p2[cont].tamanho = p.tamanho;
						strcpy(p2[cont].status,p.status);
						cont++;
					}
				}//fim de if de feof de arquivo
			}//fim do while
		fclose(pp);
	}//fim do if de abertura do arquivo para leitura

	if(aux==1){
		if((pp = fopen("patins.dat","wb+")) == NULL){
			printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
			getch();
			exit(0);
		}else{
			fwrite(p2,sizeof(patins),cont,pp);
			fclose(pp);
		}
	}else{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
		printf("\t|                Nenhum funcionario encontado!                    |\n");
		printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
	}

	printf("\n\t");
	system("pause");
}// fim procedimento excluir patins

void ExcluirCliente(cliente c, char nome[], int x){
	int flag=0, cont=0, aux=0, valida=0;
	cliente *c2;
	char del, pesqCli[20];

	c2 = (cliente*)malloc(1000*sizeof(cliente));
	
	
	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Cliente -> Excluir                                         |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Excluir Cliente\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCPF: ");
	fflush(stdin);
	gets(pesqCli);

	if((pc = fopen("clientes.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pc);
			while(!feof(pc)){
				flag=0;
				fread(&c,sizeof(cliente),1,pc);
				if(!feof(pc)){
					if(strcmp(pesqCli,c.cpf)==0){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCPF         :*** %s *** ",c.cpf);
						printf("\n\tNome        : %s ",c.nome);
						printf("\n\tRG          : %s ",c.rg);
						printf("\n\tTamanho     : %d \n",c.tamanho);
						printf("\n\t+-------------------------------------------------------------------\n+");
						valida = ValidaExclusaoCliente(c);
						if(valida == 1){
							printf("\n\tErro ao excluir.\n\tLocacao em aberto para esse cliente.\n\t");
							//system("pause");
						}else{
							do{
								flag=0;
								system("color 4F");
								printf("\n\n\tTem certeza que deseja excluir ? ");
								printf("\n\t1 - Sim");
								printf("\n\t2 - Nao");
								printf("\n\n\t+-------------------------------------------------------------------+");
								printf("\n\tOpcao [ ]\b\b");
								fflush(stdin);
								scanf("%c", &del);;

								switch(del){
									case '1':{
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                Cliente deletado com sucesso!                      |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 1;
										break;
									}
									case '2':{
										system("cls");
										printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
										printf("\t|                       Operacao cancelada!                         |\n");
										printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
										flag = 2;
										break;
									}
									default:{
										printf("\n\tOpcao invalida.Tente novamente.\n");
										flag = 0;
									}
								}//fim switch de confirmacao do deletar
							}while((flag != 1) && (flag != 2));
						}
					}//fim de comparacao de matricula
					if(flag != 1){
						strcpy(c2[cont].cpf,c.cpf);
						strcpy(c2[cont].nome,c.nome);
						strcpy(c2[cont].rg,c.rg);
						c2[cont].tamanho = c.tamanho;
						cont++;
					}
				}//fim de if de feof de arquivo
			}//fim do while
		fclose(pc);
	}//fim do if de abertura do arquivo para leitura

	if(aux==1){
		if((pc = fopen("clientes.dat","wb+")) == NULL){
			printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		}else{
			fwrite(c2,sizeof(cliente),cont,pc);
			fclose(pc);
		}
	}else{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
		printf("\t|                Nenhum cliente encontado!                          |\n");
		printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
	}

	printf("\n\t");
	system("pause");
}// fim procedimento excluir cliente

void CancelarAluguel(aluguel g, char nome[], int x){
	int aux=0, cont=0, flag=0;
	char pesqAluguel[20], del;
	FILE *paa;

	system("cls");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Aluguel -> Cancelar Aluguel                                |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Cancelar Aluguel\t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");

	printf("\n\tCPF do Cliente: ");
	fflush(stdin);
	gets(pesqAluguel);

	if((pa = fopen("aluguel.dat","rb+")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{

		rewind(pa);
			while(!feof(pa)){
				fread(&g,sizeof(aluguel),1,pa);
				if(!feof(pa)){
					if((strcmp(pesqAluguel, g.cliente)==0) && (strcmp(g.status,"aberto")==0)){
						aux=1;
						printf("\t+-------------------------------------------------------------------+");
						printf("\n\n\tCodigo      : %d ",g.codigo);
						printf("\n\tCliente     : %s ",g.cliente);
						//printf("\n\tCPF         : %s ",cpf);//nao fica salvo no arquivo só é exibido
						printf("\n\tPatins      : %d ",g.patins);
						printf("\n\tHora Inicial: %d:%dh ",g.h_ini.hor,g.h_ini.min);
						printf("\n\tHora Final  : %d:%dh ",g.h_fin.hor,g.h_fin.min);
						printf("\n\tTempo Total : %dminutos ",g.tempoTotal);
						printf("\n\tValor Total : R$ %.2f ",g.valorTotal);
						printf("\n\tData        : %d/%d/%d ",g.date.dia,g.date.mes,g.date.ano);
						printf("\n\tStatus      : %s ",g.status);
						printf("\n\n\t+-------------------------------------------------------------------\n+");

						do{
							flag=0;
							system("color 4F");
							printf("\n\n\tTem certeza que deseja Cancelar Aluguel ? ");
							printf("\n\t1 - Sim");
							printf("\n\t2 - Nao");
							printf("\n\n\t+-------------------------------------------------------------------+");
							printf("\n\tOpcao [ ]\b\b");
							fflush(stdin);
							scanf("%c", &del);;

							switch(del){
								case '1':{
									strcpy(g.status,"cancelado");
									fseek(pa,cont * sizeof(aluguel),SEEK_SET );
									fwrite(&g,sizeof(aluguel),1,pa);
									AtualizarPatinsDevolvido(g.patins);
									system("cls");
									printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
									printf("\t|                Aluguel cancelado com sucesso!                     |\n");
									printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
									flag = 1;
									break;
								}
								case '2':{
									system("cls");
									printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
									printf("\t|                       Cancelamento nao realizado!                 |\n");
									printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
									flag = 2;
									break;
								}
								default:{
									printf("\n\tOpcao invalida.Tente novamente.\n");
									flag = 0;
								}
							}//fim switch de confirmacao do deletar
						}while((flag != 1) && (flag != 2));
					}//fim do fi de comparacao de cpf
				}//fim do if do feof de comparacao
				cont++;
				if(flag == 1){
					break;
				}
			}//fim do while de aluguel
		fclose(pa);
	}
	printf("\n\t");
	if(aux == 0){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\t+-------------------------------------------------------------------+\n");
			printf("\t|                Nenhum aluguel encontado!                          |\n");
			printf("\t+-------------------------------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\t");
		}
	system("pause");
}// fim procedimento cancelar aluguel

//TELAS PRINCIPAIS
void Administrador(administrador adm){
	char op,op1,op2,op3,op4,op5,op6,op7,op8, op9;
	char nome[20];
	funcionario f;
	cliente c;
	patins p;
	aluguel g;
	preco r;

	strcpy(nome,adm.nome);
	do{
		system("cls");
		system("color 0F");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Menu Principal                                             |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\n\tBem vindo Sr(a) %s\n\n",nome);
		printf("\t1 - Funcionarios\n\n");
		printf("\t2 - Patins\n\n");
		printf("\t3 - Clientes\n\n");
		printf("\t4 - Aluguel\n\n");
		printf("\t5 - Preco\n\n");
		printf("\t6 - Relatorios\n\n");
		printf("\t7 - Sobre\n\n");
		printf("\t0 - Logoff\n\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao [ ]\b\b");
		fflush(stdin);
		scanf("%c",&op);

		//verificação da opcao escolhida Administrador
		switch(op){
			case '1':{// -> Administrador - Funcionarios
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Funcionarios                                               |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Funcionarios\n\n");
					printf("\t2 - Cadastrar Funcionario\n\n");
					printf("\t3 - Alterar Funcionario\n\n");
					printf("\t4 - Pesquisar Funcionario\n\n");
					printf("\t5 - Excluir Funcionario\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op1);

					switch(op1){
						case '1':{
							ListarFuncionarios(f,nome,20);
							break;
						}
						case '2':{
							CadastrarFuncionario(f,nome,20);
							break;
						}
						case '3':{
							AlterarFuncionario(f, nome, 16);
							break;
						}
						case '4':{
							PesquisarFuncionario(f,nome ,20);
							break;
						}
						case '5':{
							ExcluirFuncionario(f,nome ,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Funcionarios.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op1 != '0');
				//system("pause");
				break;
			}//fim case 1 -> Menu - Funcionarios
			case '2':{// -> Menu - Patins
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Administrador -> Patins                                    |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Patins\n\n");
					printf("\t2 - Cadastrar Patins\n\n");
					printf("\t3 - Alterar Patins\n\n");
					printf("\t4 - Pesquisar Patins\n\n");
					printf("\t5 - Excluir Patins\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op2);

					switch(op2){
						case '1':{
							ListarPatins(p,nome,20);
							break;
						}
						case '2':{
							CadastrarPatins(p,nome,20);
							break;
						}
						case '3':{
							AlterarPatins(p,nome,20);
							break;
						}
						case '4':{
							PesquisarPatins(p, nome, 20);
							break;
						}
						case '5':{
							ExcluirPatins(p,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Patins.\n\n\t");
							op2 = 9;
							system("pause");
							break;
						}
					}
				}while(op2 != '0');
				//system("pause");
				break;
			}//fim case 2 -> Menu - Patins
			case '3':{// -> Menu - Clientes
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu ->  Clientes                                                  |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Clientes\n\n");
					printf("\t2 - Cadastrar Cliente\n\n");
					printf("\t3 - Alterar Cliente\n\n");
					printf("\t4 - Pesquisar Cliente\n\n");
					printf("\t5 - Excluir Cliente\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op3);

					switch(op3){
						case '1':{
							ListarClientes(c,nome,20);
							break;
						}
						case '2':{
							CadastrarCliente(c,nome,20);
							break;
						}
						case '3':{
							AlterarCliente(c,nome,20);
							break;
						}
						case '4':{
							PesquisarCliente(c,nome,20);
							break;
						}
						case '5':{
							ExcluirCliente(c,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Clientes.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op3 != '0');
				//system("pause");
				break;
			}//fim case 3 -> Menu - Clientes
			case '4':{// -> Menu - Aluguel
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Aluguel                                                    |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Alugueis\n\n");
					printf("\t2 - Novo Aluguel\n\n");
					printf("\t3 - Realizar Pagamento\n\n");
					printf("\t4 - Pesquisar Aluguel\n\n");
					printf("\t5 - Cancelar Aluguel\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op4);

					switch(op4){
						case '1':{
							ListarAlugueisAbertos(g,nome,20);
							break;
						}
						case '2':{
							RealizarAluguel(g,nome,20);
							break;
						}
						case '3':{
							RealizarPagamento(g, nome,20);
							break;
						}
						case '4':{
							PesquisarAluguel(g, nome, 20);
							break;
						}
						case '5':{
							CancelarAluguel(g, nome, 20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Aluguel.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op4 != '0');
				//system("pause");
				break;
			}//fim case 4 -> Menu - Aluguel
			case '5':{// -> Menu - Preco
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Preco                                                      |\n");
					printf("\t+-------------------------------------------------------------------+\n");

					//lendo o preco do arquivo
					if((pr = fopen("preco.dat","rb"))==NULL){
						//printf("\tPreco nao cadastrado ou erro ao abrir arquivo.\n\tConsulte o programador.\n\t");
						//getch();
						r.valor = 0;
						r.qtd_minutos = 0;
					}else{
						rewind(pr);
						while(!feof(pr)){
							fread(&r,sizeof(preco),1,pr);
						}
					}

					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\tValor : R$ %.2f\n\n",r.valor);
					printf("\tQuantidade de minutos : %d\n\n",r.qtd_minutos);
					printf("\t+-------------------------------------------------------------------+\n\n");
					printf("\t1 - Alterar Preco\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op8);

					switch(op8){
						case '1':{
							system("cls");
							AlterarPreco(r,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Preco.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op8 != '0');
				fclose(pr);
				break;
			}
			case '6':{// -> Menu - Relatorios
				do{
					system("cls");
					system("color 0F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Relatorios                                                 |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Faturamento Diario\n\n");
					printf("\t2 - Faturamento Mensal\n\n");
					printf("\t3 - Locacao\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op9);

					switch(op9){
						case '1':{
							system("cls");
							RelatorioFaturamentoDiario(g, nome, 20);
							break;
						}
						case '2':{
							system("cls");
							RelatorioFaturamentoMensal(g,nome,20);
							break;
						}
						case '3':{
							system("cls");
							ListarAlugueisTudo(g,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Faturamento.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op9 != '0');
				//system("pause");
				break;
			}//fim case 4 -> Menu - Relatorios
			case '7':{
				Sobre(nome,20);
				break;
			}
			case '0':{// -> Administrador - Logoff
				//volta para tela de login
				main();
				break;
			}//fim case 0 -> Administrador - Logoff
			default:{
				printf("\tOpcao invalida para Administrador.\n\n\t");
				op = 'A';//forçar o loop
				system("pause");
			}
		}//fim so switch  -> Administrador
	}while(op != '0');
}//FIM PROCEDIMENTO ADMINISTRADOR()

void Funcionario(funcionario f){
	char op,op1,op2,op3,op4,op5,op6,op7,op8;
	char nome[20];
	cliente c;
	patins p;
	aluguel g;
	preco r;

	strcpy(nome,f.nome);
	do{
		system("cls");
		system("color 1F");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Menu Principal                                             |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\n\tBem vindo Sr(a) %s\n\n",nome);
		printf("\t1 - Patins\n\n");
		printf("\t2 - Clientes\n\n");
		printf("\t3 - Aluguel\n\n");
		printf("\t4 - Relatorios\n\n");
		printf("\t5 - Sobre\n\n");
		printf("\t0 - Logoff\n\n");
		printf("\t---------------------------------------------------------------------\n");
		printf("\tOpcao [ ]\b\b");
		fflush(stdin);
		scanf("%c",&op);

		//verificação da opcao escolhida Funcionario
		switch(op){
			case '1':{// -> Menu Patins
				do{
					system("cls");
					system("color 1F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Patins                                                     |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Patins\n\n");
					printf("\t2 - Cadastrar Patins\n\n");
					printf("\t3 - Alterar Patins\n\n");
					printf("\t4 - Pesquisar Patins\n\n");
					printf("\t5 - Excluir Patins\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op1);

					switch(op1){
						case '1':{
							ListarPatins(p,nome,20);
							break;
						}
						case '2':{
							CadastrarPatins(p,nome,20);
							break;
						}
						case '3':{
							AlterarPatins(p,nome,20);
							break;
						}
						case '4':{
							PesquisarPatins(p, nome, 20);
							break;
						}
						case '5':{
							ExcluirPatins(p,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Patins.\n\n\t");
							op1 = 9;
							system("pause");
							break;
						}
					}
				}while(op1 != '0');
				//system("pause");
				break;
			}//fim case 1 -> Menu - Patins
			case '2':{// -> Menu - Clientes
				do{
					system("cls");
					system("color 1F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu ->  Clientes                                                  |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Clientes\n\n");
					printf("\t2 - Cadastrar Cliente\n\n");
					printf("\t3 - Alterar Cliente\n\n");
					printf("\t4 - Pesquisar Cliente\n\n");
					printf("\t5 - Excluir Cliente\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op2);

					switch(op2){
						case '1':{
							ListarClientes(c,nome,20);
							break;
						}
						case '2':{
							CadastrarCliente(c,nome,20);
							break;
						}
						case '3':{
							AlterarCliente(c,nome,20);
							break;
						}
						case '4':{
							PesquisarCliente(c,nome,20);
							break;
						}
						case '5':{
							ExcluirCliente(c,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Clientes.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op2 != '0');
				//system("pause");
				break;
			}//fim case 2 -> Menu - Clientes
			case '3':{// -> Menu - Aluguel
				do{
					system("cls");
					system("color 1F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Aluguel                                                    |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Listar Alugueis\n\n");
					printf("\t2 - Novo Aluguel\n\n");
					printf("\t3 - Realizar Pagamento\n\n");
					printf("\t4 - Pesquisar Aluguel\n\n");
					printf("\t5 - Cancelar Aluguel\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op3);

					switch(op3){
						case '1':{
							ListarAlugueisAbertos(g,nome,20);
							break;
						}
						case '2':{
							RealizarAluguel(g,nome,20);
							break;
						}
						case '3':{
							RealizarPagamento(g, nome,20);
							break;
						}
						case '4':{
							PesquisarAluguel(g, nome, 20);
							break;
						}
						case '5':{
							CancelarAluguel(g, nome, 20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Aluguel.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op3 != '0');
				//system("pause");
				break;
			}//fim case 3 -> Menu - Aluguel
			case '4':{// -> Menu - Relatorios
				do{
					system("cls");
					system("color 1F");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\t|Menu -> Relatorios                                                 |\n");
					printf("\t+-------------------------------------------------------------------+\n");
					printf("\n\tBem vindo Sr(a) %s\n\n",nome);
					printf("\t1 - Faturamento Diario\n\n");
					printf("\t2 - Faturamento Mensal\n\n");
					printf("\t3 - Locacao\n\n");
					printf("\t0 - Voltar\n\n");
					printf("\t---------------------------------------------------------------------\n");
					printf("\tOpcao [ ]\b\b");
					fflush(stdin);
					scanf("%c",&op4);

					switch(op4){
						case '1':{
							system("cls");
							RelatorioFaturamentoDiario(g, nome, 20);
							break;
						}
						case '2':{
							system("cls");
							RelatorioFaturamentoMensal(g,nome,20);
							break;
						}
						case '3':{
							system("cls");
							ListarAlugueisTudo(g,nome,20);
							break;
						}
						case '0':{
							//Voltar
							break;
						}
						default:{
							printf("\tOpcao invalida para Submenu Faturamento.\n\n\t");
							system("pause");
							break;
						}
					}
				}while(op4 != '0');
				//system("pause");
				break;
			}//fim case 4 -> Menu - Relatorios
			case '5':{
				Sobre(nome,20);
				break;
			}
			case '0':{// -> Funcionario - Logoff
				//volta para tela de login
				
				main();
				break;
			}//fim case 0 -> Funcionario - Logoff
			default:{
				printf("\tOpcao invalida para Funcionario.\n\n\t");
				op = 'A';//forçar o loop
				system("pause");
			}
		}//fim so switch  -> Funcionario
	}while(op != '0');
}//FIM PROCEDIMENTO FUNCIONARIO()

//FUNÇÕES DE VALIDAÇÕES
int ValidaMatricula(funcionario f){
	int cont=0;
	funcionario f2;
	FILE *paf;//ponteiro auxiliar de funcionario

	if((paf = fopen("funcionarios.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(paf);
			while(!feof(paf)){
				fread(&f2,sizeof(funcionario),1,paf);
				if(!feof(paf)){
					if(f.matricula == f2.matricula){
						cont=1;
					}
				}
			}
		fclose(paf);

		if(cont==0){
			return 1;//nao existe
		}else{
			return 0;//existe
		}
	}
}// fim validacao da matricula

int ValidaCpf(char cpf[], int x, char file[20], int y){
	int cont=0;
	cliente c2;
	funcionario f2;
	FILE *pa;//ponteiro auxiliar

	if((pa = fopen(file,"rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pa);
			while(!feof(pa)){
				if(strcmp(file,"funcionarios.dat")==0){
					fread(&f2,sizeof(funcionario),1,pa);
					if(!feof(pa)){
						if(strcmp(cpf,f2.cpf)==0){
							cont=1;
						}
					}
				}else if(strcmp(file,"clientes.dat")==0){
					fread(&c2,sizeof(cliente),1,pa);
					if(!feof(pa)){
						if(strcmp(cpf,c2.cpf)==0){
							cont=1;
						}
					}
				}
			}
		fclose(pa);

		if(cont==0){
			return 1;//nao existe
		}else{
			return 0;//existe
		}
	}
}// fim validacao da Cpf

int ValidaBox(int box){
	int cont=0;
	patins p2;
	FILE *pap;//ponteiro auxiliar do patins

	if((pap = fopen("patins.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pap);
			while(!feof(pap)){
				fread(&p2,sizeof(patins),1,pap);
				if(!feof(pap)){
					if(box == p2.box){
						cont=1;
					}
				}
			}
		fclose(pap);

		if(cont==0){
			return 1;//nao existe
		}else{
			return 0;//existe
		}
	}
}// fim validacao do box do patins

int VerificarDisponibilidadePatins(int codPatins){
	int cont=0, flag = 0;
	patins p2;
	FILE *pap;//ponteiro auxiliar do patins

	if((pap = fopen("patins.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pap);
			while(!feof(pap)){
				fread(&p2,sizeof(patins),1,pap);
				if(!feof(pap)){
					if(codPatins == p2.codigo){
						cont=1;
						if(strcmp(p2.status,"disponivel")==0){
							flag=1;
						}

					}
				}
			}
		fclose(pap);

		if((flag==1) && (cont ==1)){
			return 1;//disponivel
		}else if(cont==0){
			printf("\tCodigo nao existe.\n");
			return 0;//indisponivel
		}else if(cont==1){
			printf("\tPatins indisponivel, esta alugado.\n");
			return 0;
		}
	}
}// fim validacao do box do patins

int IncrementaCodigoPatins(){
	FILE *pap;//ponteiro auxiliar de patins
	patins p2;
	int cont=0, i=0, size=0;

	if((pap = fopen("patins.dat","rb")) == NULL){
		//printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		cont = 1;
		//exit(0);
		//printf("%d\n", cont);
		return cont;
	}else{
		fseek(pap, 0, SEEK_END);
		size = ftell(pap);
//		printf("%d\n",size); // verifica se o arquivo esta vazio
		if(size > 0){
			rewind(pap);
			while(!feof(pap)){
				fflush(stdin);
				fread(&p2,sizeof(patins),1,pap);
				fflush(stdin);
				if(p2.codigo != NULL){
					cont = p2.codigo + 1;
				}
			}
			fclose(pap);
			return cont;
		}else{
			return 1;
		}

	}
}//fim do incrementa codigo patins

int IncrementaCodigoAluguel(){
	FILE *paa;//ponteiro auxiliar de aluguel
	aluguel a2;
	int cont=0, i=0, size=0;

	if((paa = fopen("aluguel.dat","rb")) == NULL){
		//printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		cont = 1;
		//exit(0);
		//printf("%d\n", cont);
		return cont;
	}else{
		fseek(paa, 0, SEEK_END);
		size = ftell(paa);
//		printf("%d\n",size); // verifica se o arquivo esta vazio
		if(size > 0){
			rewind(paa);
			while(!feof(paa)){
				fflush(stdin);
				fread(&a2,sizeof(aluguel),1,paa);
				fflush(stdin);
				if(a2.codigo != NULL){
					cont = a2.codigo + 1;
				}
			}
			fclose(paa);
			return cont;
		}else{
			return 1;
		}
	}
}//fim do incrementa codigo aluguel

int ValidaData(int dia, int mes, int ano){
	int ret=0;
	char qtd[5];

//	dia = g.date.dia;

	switch(mes){
		case 1:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 2:{if((dia < 0) || (dia > 29)){printf("\tMes invalido.\n");ret = 0;}else{ret = 1;}break;}//fevereiro com 29 dias
		case 3:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 4:{if((dia < 0) || (dia > 30)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 5:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 6:{if((dia < 0) || (dia > 30)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 7:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 8:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 9:{if((dia < 0) || (dia > 30)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 10:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 11:{if((dia < 0) || (dia > 30)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		case 12:{if((dia < 0) || (dia > 31)){printf("\tDia invalido.\n");ret = 0;}else{ret = 1;}break;}
		default:{printf("\tMes invalido.\n");ret=0;}
	}

	if(ret == 1){
		sprintf(qtd,"%d",ano);
		if((strlen(qtd) != 4) && (ano < 1990)){
			printf("\tAno invalido.\n");
			ret = 0;
		}else{
			ret = 1;
		}
	}

	if(ret == 1){
		return 1;
	}else{
		printf("\tTente novamente.\n");
//		getch();
		return 0;
	}
}

int ValidaExclusaoCliente(cliente c){
	aluguel g;
	int cont=0;
	FILE *paa;

	if((paa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(paa);
		while(!feof(paa)){
			fread(&g,sizeof(aluguel),1,paa);
			if((strcmp(g.cliente,c.cpf)==0) && (strcmp(g.status,"aberto")==0)){
				cont = 1;
				return 1;
			}
		}
		if(cont == 0){
			return 0;
		}
	}
}

/*preco LerPreco(){
	if(pr = fopen("preco.dat","rb") == NULL){
		printf("\tPreco nao cadastrado ou erro ao abrir o arquivo. \n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(pr);
		while(!feof(pr)){
			fread(&r,sizeof(preco),1,pr);
		}
	}
	return r;
}*/

//SEÇÃO DE RELATORIOS

void RelatorioFaturamentoDiario(aluguel g, char nome[], int x){
	int dia, mes, ano, qtdAlugueis=0, valida=0;
	float valorTotal=0;
	FILE *paa;

	do{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Relatorios -> Faturamento Diario                           |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Relatorio de Faturamento Diario\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");

		printf("\n\tInforme uma data: \n");
		printf("\tDia (dd): ");
		scanf("%d", &dia);
		printf("\tMes (mm): ");
		scanf("%d", &mes);
		printf("\tAno (aaaa): ");
		scanf("%d", &ano);
		printf("\t+-------------------------------------------------------------------+\n\n");
		valida = ValidaData(dia,mes,ano);//valida data
		if(valida == 0){
			getch();
		}
	}while(valida == 0);


	if((paa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(paa);
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Relatorios -> Faturamento Diario                           |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Relatorio de Faturamento Diario\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\tRELATORIO DA DATA : %d/%d/%d\n\n",dia,mes,ano);
		printf("\t+-------------------------------------------------------------------+");
		printf("\n\t| COD\t| CPF-CLIENTE\t | TEMPO(min)  |   VALOR    |PATINS |STATUS\t \n");
		printf("\t+-------------------------------------------------------------------+");
		while(!feof(paa)){
			fread(&g,sizeof(aluguel),1,paa);
			if(!feof(paa)){
				if((g.date.dia == dia) && (g.date.mes == mes) && (g.date.ano == ano) && (strcmp(g.status,"fechado")==0)){
	//				printf("\tQuantidade totaal de locacoes finalizadas: %d ");
					printf("\n\t|  %d\t| %s\t |    %d\t| R$%.2f  |  %d\t |%s  |",g.codigo, g.cliente, g.tempoTotal, g.valorTotal, g.patins, g.status);
					printf("\n\t+-------------------------------------------------------------------+");
					qtdAlugueis++;
					valorTotal += g.valorTotal;
				}
			}
		}
		printf("\n\tQUANTIDADE TOTAL : %d locacoes\n", qtdAlugueis);
		printf("\tVALOR TOTAL      : R$ %.2f\n", valorTotal);
		printf("\n\t+-------------------------------------------------------------------+\n\n\t");
	}
	system("pause");
}

void RelatorioFaturamentoMensal(aluguel g, char nome[], int x){
	int dia, mes, ano, qtdAlugueis=0;
	float valorTotal=0;
	FILE *paa;

	do{
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Relatorios -> Faturamento Mensal                           |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Relatorio de Faturamento Mensal\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");

		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t1-Janeiro   |   2-Fevereiro   |  3-Marco     |  4-Abril \n");
		printf("\t5-Maio      |   6-Junho       |  7 -Julho    |  8 -Agosto \n");
		printf("\t9-Setembro  |   10-Outubro    |  11-Novembro |  12-Dezembro\n");
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\n\tInforme um mes (1..12):[   ]\b\b\b\b ");
		scanf("%d", &mes);

		if((mes > 12) && (mes < 1)){
			printf("\tMes invalido.\n");
		}
	}while((mes >= 12) && (mes < 1));
	//valida data

	if((paa = fopen("aluguel.dat","rb")) == NULL){
		printf("\tErro ao tentar abrir arquivo.\n\tConsulte o programador.\n\t");
		getch();
		exit(0);
	}else{
		rewind(paa);
		system("cls");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t|Menu -> Relatorios -> Faturamento Mensal                           |\n");
		printf("\t+-------------------------------------------------------------------+\n");
		printf("\t Relatorio de Faturamento Mensal\t| Logado como: %s\n",nome);
		printf("\t+-------------------------------------------------------------------+\n\n");
		printf("\tRELATORIO DO MES : %d\n\n",mes);
		printf("\t+-------------------------------------------------------------------+");
		printf("\n\t| COD\t| CPF-CLIENTE\t | TEMPO(min)  |   VALOR    |PATINS |STATUS\t \n");
		printf("\t+-------------------------------------------------------------------+");
		while(!feof(paa)){
			fread(&g,sizeof(aluguel),1,paa);
			if(!feof(paa)){
				if((g.date.mes == mes) && (strcmp(g.status,"fechado")==0)){
	//				printf("\tQuantidade totaal de locacoes finalizadas: %d ");
					printf("\n\t|  %d\t| %s\t |    %d\t| R$%.2f  |  %d\t |%s  |",g.codigo, g.cliente, g.tempoTotal, g.valorTotal, g.patins, g.status);
					printf("\n\t+-------------------------------------------------------------------+");
					qtdAlugueis++;
					valorTotal += g.valorTotal;
				}
			}
		}
		printf("\n\tQUANTIDADE TOTAL : %d locacoes\n", qtdAlugueis);
		printf("\tVALOR TOTAL      : R$ %.2f\n", valorTotal);
		printf("\n\t+-------------------------------------------------------------------+\n\n\t");
	}
	system("pause");
}


void Sobre(char nome[],int x){
	
	system("cls");
	system("color F1");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|               SISTEMA DE LOCACAO DE PATINS - SYSTINS              |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t|Menu -> Sobre                                                      |\n");
	printf("\t+-------------------------------------------------------------------+\n");
	printf("\t Sobre                 \t\t\t| Logado como: %s\n",nome);
	printf("\t+-------------------------------------------------------------------+\n\n");
	printf("\n\t\tSISTEMA DE GERENCIAMENTO DE LOCACAO DE PATINS\n");
	printf("\t\t*******************SYSTINS*******************\n");
	printf("\n\t\tDesenvolvedores: \n");
	printf("\n\t\t\t- DALYANA CAVALCANTE\n");
	printf("\n\t\t\t- HELOYSE FERREIRA\n");
	printf("\n\t\t\t- RENAN ARCANJO\n");
	printf("\n\t\t\t- SAMMY MELO\n");
	printf("\n\t\t*********************************************");
	printf("\n\tSistemas de Informacao - FAMETRO - 3o Periodo - Noturno - 2016\n");
	printf("\n\t\t\t\t[ENTER]");
	getch();
}

void CriarArquivos(){
	FILE *pa;

	//arquivo de funcionarios
	if((pa = fopen("funcionarios.dat","ab"))==NULL){
		printf("\tErro fatal. \n\tConsulte o programador.\n");
	}else{
		fclose(pa);
	}

	//arquivo de clientes
	if((pa = fopen("clientes.dat","ab"))==NULL){
		printf("\tErro fatal. \n\tConsulte o programador.\n");
	}else{
		fclose(pa);
	}

	//arquivo de patins
	if((pa = fopen("patins.dat","ab"))==NULL){
		printf("\tErro fatal. \n\tConsulte o programador.\n");
	}else{
		fclose(pa);
	}

	//arquivo de aluguel
	if((pa = fopen("aluguel.dat","ab"))==NULL){
		printf("\tErro fatal. \n\tConsulte o programador.\n");
	}else{
		fclose(pa);
	}
}
