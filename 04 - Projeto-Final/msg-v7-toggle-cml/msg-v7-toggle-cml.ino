/*
 *     Fonte de Estudo:
 *          Projeto Curto Circuito - Módulo HC12 – Conectando dois Arduinos (Emissor) 
 *          http://hausofpayne.weebly.com/hc12teletype.html
 * 
 *      observacoes: 
 *            a) porta serial possui um buffer de 64bytes;
 *            b) a funcao read() le retirando o byte do buffer, caso queira mante-lo usar funcao peek()
 *            c) available() retorna o numero de bytes no buffer
 * 
 * Números de dispositivos: 10; 
 * identificados de 0 ate 9;
 * sintaxe do comando : *ab*c 
 * 
 * onde:
 *      a -> dezena correspondente ao numero da porta. Ex.: 01, 02, 03, 10, 11, 12;
 *      b -> unidade correspondente ao numero da porta. Ex.: 01, 02, 03, 10, 11, 12;
 *      c -> endereço de destino.
 * 
 */

#include <SoftwareSerial.h> // Inclui Biblioteca
int i = 0;
int j = 0; // contador para uso no timer1
int k = 0; // contado para uso no timer2
// indentificador do dispositivo, ID do arduino
int id = 1;

unsigned long lasttime = 0;

// portas de comunicacao do arduino. Atentar para ligacao crossover entre arduino e modulo hc-12
SoftwareSerial HC12(2, 3); // Primeiro parametro RX e segundo parametro TX 

char input;
String msgTX = "";
String msgRX = "";

int incomingByte;

void setup()
{
  DDRB = 0b00100001; // habilita como saida os pinos 08 e 13
  HC12.begin(9600);                  // Taxa de transferência do HC12
  Serial.begin(9600);                // Taxa de transferência da Serial
  PORTB = 0b00000000;

/*
 * ciclo de maquina = 1/16Mhz = 62,5n
 * estouro = timer0 x prescaler X ciclo de maquina = ?
 * estouro = 155 x 1024 x (1/16Mhz) = 9,92ms equivalente 10ms      
 *  
 */

  // Configuração do TIMER2
  TCCR2A = 0;                //limpa registrador
  TCCR2B = 0;                //limpa registrador
  TCNT2  = 0;                //zera temporizador
  OCR2A = 155;            // carrega registrador de comparação: 16MHz/1024/1Hz = 15625 ou 0X3D09
  TCCR2A |= (1 << WGM21);    // modo CTC=1 e modo normal=0
  TCCR2B |= (1<<CS22)|(1 << CS21) | (1 << CS20);   // prescaler de 1024: CS12 = 1 e CS10 = 1  
  TIMSK2 |= (1 << OCIE2A);  // habilita interrupção por igualdade de comparação

  // Configuração do TIMER1
  TCCR1A = 0;                //limpa registrador
  TCCR1B = 0;                //limpa registrador
  TCNT1  = 0;                //zera temporizador
  OCR1A = 15625;            // carrega registrador de comparação: 16MHz/1024/1Hz = 15625 ou 0X3D09
  TCCR1B |= (1 << WGM12);    // modo CTC=1 e modo normal=0
  TCCR1B |= (1<<CS12)|(1 << CS10);   // prescaler de 1024: CS12 = 1 e CS10 = 1  
  TIMSK1 |= (1 << OCIE1A);  // habilita interrupção por igualdade de comparação

} /* ###### FIM SETUP ###### */
void loop()
{
  /* #### Inicio bloco de envio #### */
  // se tiver byte no buffer da serial satifaca a condicao
  if (Serial.available()>0)    
  {                   
    input=Serial.read(); // realiza leitura do buffer serial, conforme encontra retira o byte
    if (input != '\r' && input != '\n')  // retirada dos bytes de recuo de carro e nova linha
    {            
      msgTX += char(input);  // monta a string dos caracteres colocados no buffer da serial     
    }
  }
  else
  {
    //delay(200); // gera um atraso antes iniciar transferencia
    // Se tiver msg tranfere pelo modulo HC-12
    if(msgTX.length() != 0)     
    {
      // Se for comando insere id do dispositivo ao fim do comenado
      if(msgTX[0]=='*'){
        msgTX = msgTX + String(id);
      }
      // tranfere a msg byte a byte pelo modulo HC-12
      for (int i = 0; i < msgTX.length(); i++)
      {
        HC12.write(msgTX.charAt(i));  
      }
      // no fim da TX imprime o conteudo transmitido
      Serial.println(msgTX);
      // limpa a string com conteudo transmitido    
      msgTX = "";   
    }
  } /* #### FIM bloco de envio #### */
  
  /* ####### Inicio bloco de recepcao ####### */
  while (HC12.available() > 0)
  {
    delay(5);   // gera um atraso antes realizar leitura do buffer 
    incomingByte = HC12.read();   // leitura do que chega pelo RX no modulo HC-12
    if (incomingByte != '\r' && incomingByte != '\n')       // retirada dos bytes de recuo de carro e nova linha
    {
      msgRX = msgRX + char(incomingByte);    // monta string por meio da recepcao de caracter e caractere
    }
  }

  if(msgRX.charAt(0)!='*' && msgRX.length() != 0)
  {
    Serial.print("MSG Recebida:");
    Serial.println(msgRX);
    msgRX = "";
  }
  else if(msgRX.charAt(0)=='*' && msgRX.length() != 0)
  {
    Serial.print("Comando Recebido :");
    Serial.println(msgRX);
       
    //Verifica se comando é para o seu ID, senão reenvia o comando 
    if(msgRX.substring(4,5).toInt() == id)
    {
     /* 
      * Utilizado millis para resolver problema do reenvio
      */
      //if(millis()-lasttime >= 2000)
      //{ 
        trataComandos(msgRX);
        lasttime = millis(); 
      //}
    }
    else
    {
      reenviaComandos(msgRX);
    }
    msgRX = "";
  } /* ####### FIM bloco de recepcao ####### */
} /* ###### FIM LOOP ###### */



/* ########################################################### */
/* ######################## Funcoes ########################## */
/* ########################################################### */

/* Funcao trata comando */
void trataComandos(String a)
{
 /* verifica se a porta endereçada é a 13 ou se é a porta 08. 
  * Tecnica de toggle foi importante para verificar problema de execução de comando duplicado
  * pelo reenvio do multisaltos 
  */
  if(a.substring(1, 3).toInt()==13)
  {
    PORTB ^= (1<<5); // porta 13  
    j = 0;
  } 
  else if (a.substring(1, 3).toInt()==8)
  {
    PORTB ^= (1<<0); //porta 8
    k = 0;
  }
}

/* Funcao reenvia comando */ 
void reenviaComandos(String a)
{
  int tam = a.length();
  String sel = a.substring(5,tam); 
  //int r = sel.indexOf(String(id));
  //Serial.println(r);
  if(sel.indexOf(String(id))!= -1)
  {
    Serial.println("CMD Voltou ao Origem");
  }
  else
  {
    a = a + String(id);
    for (int i = 0; i < a.length(); i++)
    {
      HC12.write(a.charAt(i));  // tranfere pelo modulo HC-12 byte a byte
    } 
    Serial.print("Comando Reenviado: ");
    Serial.println(msgRX);
  }
}

/* Interrupcao igualdade de comparação no TIMER1 */
ISR(TIMER1_COMPA_vect)         
{
 //modo CTC zera o timer quando atingido valor de comparação
  j++; // contador para o numer ode segundos
  if(j==20) // configura contador para 20 segundo 
  { 
    PORTB &= ~(1<<5); // limpa bit porta 13  
    j=0; // zera contador
  }
}

/* Interrupcao igualdade de comparação no TIMER2 */
ISR(TIMER2_COMPA_vect)         
{
 //modo CTC zera o timer quando atingido valor de comparação
  k++; // contador para o numer ode segundos
  if(k==(100*5)) // configura contador para 5 segundos = 10ms * 100 * 5 = 5000ms ou 5s 
  { 
    PORTB &= ~(1<<0); // limpa bit porta 8
    k=0; // zera contador
  }
}


