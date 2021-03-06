# Projeto Final da Disciplina de Software Embarcado

---
## Proposta: 

	Controle Automatizado para Escritórios e Laboratórios por meio de Redes de RF with use Arduino 
	
## Motivação: 

	Observação diária da rotina dos monitores responsáveis pelos Laboratórios do Departamento de
	Engenharia da UERJ.
	
## Problema:

	Os monitores precisam:
	
	* abrir/fechar as dependências dos laboratório;
	* ligar/desligar o barramento elétrico dos Laboratórios (djuntores dos circuitos elétricos
	situados dentro dos laboratórios); e
	* ligar/desligar aparelhos condicionadores de ar, ventiladores e projetores de vídeo.

	Essas tarefas são realizadas constantemente no dia a dia, dependendo do uso pelos professores
	e alunos. Para execução da tarefa os monitores precisam se dirigir até os laboratórios, levando-os
	a interromper a execução de outras atividades/tarefas, e a ter que se dividir para atender
	a constante  demanda acadêmica.
	
## Solução:

	Disponibilizar a abertura do laboratório, além da energização de seu barramento elétrico,
	de forma remota. Sendo utilizado uma rede de RF with use arduino, tendo sua administração
	centralizada na sala do monitores.
	
## Melhorias

	- Multisalto
		- Protocolo de comunicação
		- Uso do Monitor Serial
		- Formato dos comandos : *1*13*1*1
		- ID por dispositivo
		- Comando carrega caminho
		- Cancela comando reconhecido
	- Interrupção
		- Timer1 - 20s
		- Timer2 - 5s

## Componentes Eletrônicos:
		
	Atuadores:
		a) Módulo relé 5v;
		b) LED;
		c) Lâmpada.
		
## Vídeo no Youtube
	https://www.youtube.com/watch?v=-eoNIaAJXKQ&t=149s

<!--
By Alisson Cavalcante e Silva
26/10/2018
-->
