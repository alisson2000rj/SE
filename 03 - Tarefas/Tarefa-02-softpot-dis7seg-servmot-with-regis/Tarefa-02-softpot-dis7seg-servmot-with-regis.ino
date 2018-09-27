/*
 * Versao by alisson
 * modificado 26 set 2018
 * utilizada com referencia o exemplo :

SoftPot_Example.ino
Example sketch for SparkFun's soft membrane potentiometer
  (https://www.sparkfun.com/products/8680)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

- Conecta os pinos da extremidade do softpot's ao 5V and GND.  
- Conecta o pino do meio ao A0.

Conforme a voltagem de saída do softpot muda, a linha grafica exibida no serial monitor muda de posição. 

*/

// carrega biblioteca que permite controlar o servo motor
#include <Servo.h>

// bloco de declaracao de constantes que indicam quais pinos do circuito do arduino serao utilizados, alem de definir a limitacao da rotacao do servo motor
#define pinoServo 13 // PB5 pino utilizado para enviar dados ao servo motor 
#define inicio 20
#define fim 180

Servo myservo;  // cria o objeto servo

// bloco de variaveis
int pos = inicio; // inicia a variavel de posicao do servo motor em 40 graus    

int buttonStateUP = HIGH;
int buttonLastStateUP = HIGH;

int buttonStateDN = HIGH;
int buttonLastStateDN = HIGH;

// Para variaveis de tempo foi utilizado unsigned long, pois aumenta o valor positivo que a variavel pode armazenar 
unsigned long lastDebounceTime = 0;  // Ultimo registro do tempo do debounce 
unsigned long debounceDelay = 50;  // tempo de debounce 50ms (0,5s). Se o tempo desta variavel for maior que o tempo que se leva pressionando o pushbutton a condicao nunca sera satisfeita.



// Declaração do display de 7 segmentos
byte seven_seg_digits[16][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 },  // = Digito 9
                                 { 1,1,1,0,1,1,1 },  // = Digito A
                                 { 0,0,1,1,1,1,1 },  // = Digito B
                                 { 1,0,0,1,1,1,0 },  // = Digito C
                                 { 0,1,1,1,1,0,1 },  // = Digito D
                                 { 1,0,0,1,1,1,1 },  // = Digito E
                                 { 1,0,0,0,1,1,1 }   // = Digito F
                                 };
//Funcao que aciona o ponto no display

//Funcao que aciona o display
void sevenSegWrite(byte digit)  
{
  byte pin = 2;
  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount)  
  { 
    //digitalWrite(pin, seven_seg_digits[digit][segCount]);
    if (pin <=7)
    {
      if(seven_seg_digits[digit][segCount] == 1)
      {
        PORTD |= (1<<pin);
      }
      else
      {
        PORTD &= ~(1<<pin);
      }
    }
    else
    {
     if(seven_seg_digits[digit][segCount] == 1)
      {
        PORTB |= (1<<0);
      }
      else
      {
        PORTB &= ~(1<<0);
      }
    }
    ++pin;
  }
  if(digit >= 6){ PORTB |= (1<<1);  //Liga o ponto
  }
  else{ PORTB &= ~(1<<1);  //Desliga o ponto
  }
}

int softPot = A0;
const int GRAPH_LENGTH = 100; // define o tamanho da linha

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600); // Envia os dados da saida serial para o monitor 
  /*
  pinMode(2, OUTPUT); // PD2 Pino 2 do Arduino ligado ao segmento A
  pinMode(3, OUTPUT); // PD3 Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); // PD4 Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); // PD5 Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); // PD6 Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); // PD7 Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); // PB0 Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); // PB1 Pino 9 do Arduino ligado ao segmento PONTO

  pinMode(pinobuttonUP, INPUT); // PB4 atribui o pino 12 do arduino ao pushbuttonUP
  pinMode(pinobuttonDN, INPUT); // PB3 atribui o pino 11 do arduino ao pushbuttonDN
  pinMode(softPot, INPUT); // PC0 Pino A0 do Arduino
  */
  DDRD |= 0b11111100; // semelhante ao pimode entre pino 2 ao 7 - PD2 ate PD7 - segmento A ate F - OUTPUT
  DDRB |= 0b00000011; // semelhante ao pimode entre pino 8 ao 9 - PB0 ate PB1 - segmento G ate PONTO - OUTPUT, e pinos 11 e 12 pushbutton do servo motor - INPUT  
  DDRC |= (0 << 0);
  //digitalWrite(pinobuttonUP, HIGH);
  PORTB |= (1 << 4);
  //digitalWrite(pinobuttonDN, HIGH);
  PORTB |= (1 << 3);
  
  myservo.attach(pinoServo);  // PB5 atribui o pino 13 do arduino ao objeto do servo motor - pino para controle
  myservo.write(inicio);
}
void loop() 
{
  // faz a leitura do valor de saida no softpot no pino A0 do arduino (pino analógico)
  int softPotADC = analogRead(softPot); // Pino A0 - PC0 
  // realiza um mapeapento "de" - "para" dos valores de saida entregue pelo softpot. 
  // No caso abaixo ele realiza um mapeamento de um valor maior para um valor menor  
  int softPotPosition = map(softPotADC, 0, 1023, 0, GRAPH_LENGTH);
  // inicia a impressao da linha grafica
  Serial.print("<");
  // permite o icremento do contador "i" ate o valor declarado em graph_lenght  
  for (int i=0; i<GRAPH_LENGTH; i++)
  {
    // quando o valor do contado "i" for igual ao valor de saida do softpot sera impresso o pipe "|"
    // senao sera impresso o traco "-"
    if (i == softPotPosition) Serial.print("|");
    else Serial.print("-");
  }
  Serial.print("> (" + String(softPotADC) + ")");
  Serial.println(softPotPosition/10);
  sevenSegWrite(softPotPosition/10);

  
//################################################################################################

  // *** Bloco 2 *** - executado se ocorrer mudanca no valor do pushbutton em relacao ao ultimo estado registrado na execucao do loop. Ou seja, se o botao for pressionado. 
  // Ou se o interruptor mudou, devido a ruído ou pressão:
  if (((PINB & (1<<4)) != buttonLastStateUP)||((PINB & (1<<3)) != buttonLastStateDN)) // push button pinos 11 e 12
  {
    lastDebounceTime = millis();
  }
  // *** bloco 3 *** - realiza o debounce, controle do bounce. Permite a execução do bloco se a subtracao entre o tempo atual e o ultimo tempo de debounce registrado
  // for maior que o tempo configurado para o debounce delay. Se o tempo da variavel debounceDelay for maior que o tempo que se leva pressionando o pushbutton a condicao nunca sera satisfeita.
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // *** bloco 4 *** - executado se houver mudanca no estado do botao pushbutton. Ou seja, se o estado atual do botao pushbutton for diferente do estado registrado por buttonState na ultima vez que foi
    // satisfeita a condicao. 
    if ((PINB & (1<<4)) != buttonStateUP)
    {
      buttonStateUP = (PINB & (1<<4));
      // bloco 5 - Se o botao pushbuttonUP for pressionado (HIGH) a condicao e atendida na segunda rodada apos pressionamento do botao.
      // ou seja quando o botao retornar ao estao HIGH (1).
      if(buttonStateUP == LOW)
      {
        if (pos < fim) // quando a variavel for incrementada e atingir o valor 150 o servo motor retornara para a posicao de grau 30
        {
          pos += 40; // atribui inicialmente 20 graus e vai somando de 20 em 20
          myservo.write(pos); // envia comando para o servo motor girar 
        }
      }
    }
    if ((PINB & (1<<3)) != buttonStateDN)
    {
      buttonStateDN = (PINB & (1<<3));
      // *** bloco 5 *** - Se o botao pushbuttonDN for pressionado (HIGH) a condicao e atendida na segunda rodada apos pressionamento do botao.
      // ou seja quando o botao retornar ao estao HIGH (1).
      if(buttonStateDN == LOW)
      {
        if (pos > inicio) // quando a variavel for incrementada e atingir o valor 150 o servo motor retornara para a posicao de grau 30
        {
          pos -= 40; // atribui inicialmente 20 graus e vai somando de 20 em 20
          myservo.write(pos); // envia comando para o servo motor girar 
        }
      }
    }
  }
  Serial.print("pos: ");
  Serial.println(pos);
  // *** bloco 6 *** - registra o ultimo estado do botao pushbuttonUP em buttonLastStateUP e pushbuttonDN em buttonLastStateDN
  buttonLastStateUP = (PINB & (1<<4));
  buttonLastStateDN = (PINB & (1<<3));
}
