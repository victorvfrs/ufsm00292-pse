/**
 * \file
 *
 * \brief Exemplos diversos de tarefas e funcionalidades de um sistema operacional multitarefas.
 *
 */
/**
 * \mainpage Sistema operacional multitarefas
 *
 * \par Exemplso de tarefas
 *
 * Este arquivo contem exemplos diversos de tarefas e 
 * Este arquivo contem exemplos diversos de tarefas e
 * funcionalidades de um sistema operacional multitarefas.
 *
 *
 * \par Conteudo
 *
 * -# Inclui funcoes do sistema multitarefas (atraves de multitarefas.h)
 * -# Inicialização do processador e do sistema multitarefas
 * -# Criação de tarefas de demonstração
 *
 */
/*
 * Inclusao de arquivos de cabecalhos
 */
#include <asf.h>
#include "stdint.h"
#include "multitarefas.h"
/*
 * Prototipos das tarefas
 */
void tarefa_A(void);
void tarefa_B(void);
void tarefa_C(void);
void tarefa_D(void);
void tarefa_E(void);
void tarefa_F(void);
void tarefa_G(void);
void tarefa_H(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_A			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_B			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_C			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_D			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_E			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_F			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_G			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_H			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_A[TAM_PILHA_A];
uint32_t PILHA_TAREFA_B[TAM_PILHA_B];
uint32_t PILHA_TAREFA_C[TAM_PILHA_C];
uint32_t PILHA_TAREFA_D[TAM_PILHA_D];
uint32_t PILHA_TAREFA_E[TAM_PILHA_E];
uint32_t PILHA_TAREFA_F[TAM_PILHA_F];
uint32_t PILHA_TAREFA_G[TAM_PILHA_G];
uint32_t PILHA_TAREFA_H[TAM_PILHA_H];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];


/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	system_init();
	

	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */

	CriaTarefa(tarefa_A, "Tarefa A", PILHA_TAREFA_A, TAM_PILHA_A, 5); // Maior prioridade

    CriaTarefa(tarefa_G, "Tarefa G", PILHA_TAREFA_G, TAM_PILHA_G, 4);

    CriaTarefa(tarefa_B, "Tarefa B", PILHA_TAREFA_B, TAM_PILHA_B, 3);

    CriaTarefa(tarefa_F, "Tarefa F", PILHA_TAREFA_F, TAM_PILHA_F, 2);
	
	CriaTarefa(tarefa_H, "Tarefa H", PILHA_TAREFA_F, TAM_PILHA_H, 2);

    /* Suspende todas as Threads exceto a de maior prioridade (tarefa_1) */


	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	

	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	ConfiguraMarcaTempo();

	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	

	/* Nunca chega aqui */
	while (1)
	{
	}
}
/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_A(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;
		TarefaEspera(100);
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE); /* Liga LED. */

		//TarefaContinua(2)

	}
}

void tarefa_B(void)
{
	volatile uint32_t b = 0,k = 0;
	for(;;)
	{
		b++;
		//TarefaSuspende(2);
		//TarefaEspera(10);
		k=100000;while(--k);
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE); 	/* Turn LED off. */
	}
}

/* Tarefas de exemplo que usam funcoes para suspender as tarefas por algum tempo (atraso/delay) */
void tarefa_C(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;

		/* Liga LED. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */

		/* Desliga LED. */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
	}
}

void tarefa_D(void)
{
	volatile uint16_t b = 0;
	for(;;)
	{
		b++;
		TarefaEspera(5);	/* tarefa se coloca em espera por 5 marcas de tempo (ticks) */
	}
}

/* Tarefas de exemplo que usam funcoes de semaforo */

semaforo_t SemaforoTeste = {0,0}; /* declaracao e inicializacao de um semaforo */

void tarefa_E(void)
{

	uint32_t a = 0;			/* inicializações para a tarefa */

	for(;;)
	{

		a++;				/* código exemplo da tarefa */

		TarefaEspera(3); 	/* tarefa se coloca em espera por 3 marcas de tempo (ticks) */

		SemaforoLibera(&SemaforoTeste); /* tarefa libera semaforo para tarefa que esta esperando-o */

	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_F(void)
{

	uint32_t b = 0;	    /* inicializações para a tarefa */

	for(;;)
	{

		b++; 			/* código exemplo da tarefa */

		SemaforoAguarda(&SemaforoTeste); /* tarefa se coloca em espera por semaforo */

	}
}

/* soluçao com buffer compartihado */
/* Tarefas de exemplo que usam funcoes de semaforo */

#define TAM_BUFFER 20
uint8_t buffer[TAM_BUFFER]; /* declaracao de um buffer (vetor) ou fila circular */

semaforo_t SemaforoCheio = {0,0}; /* declaracao e inicializacao de um semaforo */
semaforo_t SemaforoVazio = {TAM_BUFFER,0}; /* declaracao e inicializacao de um semaforo */

void tarefa_G(void)
{

	uint8_t a = 1;			/* inicializações para a tarefa */
	uint8_t i = 0;

	for(;;)
	{
		SemaforoAguarda(&SemaforoVazio);

		buffer[i] = a++;
		i = (i+1)%TAM_BUFFER;

		SemaforoLibera(&SemaforoCheio); /* tarefa libera semaforo para tarefa que esta esperando-o */


		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

		TarefaEspera(10); 	/* tarefa se coloca em espera por 10 marcas de tempo (ticks), equivale a 10ms */
	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_H(void)
{
	static uint8_t f = 0;
	volatile uint32_t valor, k = 0;

	for(;;)
	{
		volatile uint8_t contador;

		do{
			REG_ATOMICA_INICIO();
			contador = SemaforoCheio.contador;
			REG_ATOMICA_FIM();

			if (contador == 0)
			{
				TarefaEspera(100);
			}

		} while (!contador);

		SemaforoAguarda(&SemaforoCheio);

		valor = buffer[f];
		f = (f+1) % TAM_BUFFER;

		k=100000;while(--k);
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);

		(void)valor;	/* leitura da variável para evitar aviso (warning) do compilador */

		SemaforoLibera(&SemaforoVazio);
	}
}