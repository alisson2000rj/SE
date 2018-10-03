/*
 * versao modificada por Alisson Cavalcante
 * heuristica desenvolvida com base nos Sketch: 
 *   - Sweep - by BARRAGAN <http://barraganstudio.com>
 *      - http://www.arduino.cc/en/Tutorial/Sweep
 *   - Debounce existente na IDE 1.8.5 do Arduino
 *      - http://www.arduino.cc/en/Tutorial/Debounce
 *   
 * versao - 2a  *** numero das versoes seguem o padrao "numeroletra". Ex.: 1a Sendo que a letra varia de a-e;   
 * 13/09/2018 - 12:00pm
 *   
 *   
 * Descrição:  
 * 
 *  + A alimentacao do servo motor e feita pelos pinos de 5v e gnd do arduino. 
 *  + Utilizado circuito PULL UP:
 *    - Quando o pushbuttonUP esta em repouso, o pino 7 do arduino recebe o sinal HIGH(1) e quando o botao e pressionado o pino 7 recebe o sinal LOW(0).  
 *    - Quando o pushbuttonDN esta em repouso, o pino 4 do arduino recebe o sinal HIGH(1) e quando o botao e pressionado o pino 4 recebe o sinal LOW(0). 
 *   
*/

// carrega biblioteca que permite controlar o servo motor
#include <Servo.h>

// bloco de declaracao de constantes que indicam quais pinos do circuito do arduino serao utilizados,
//alem de definir a limitacao da rotacao do servo motor
#define pinoServo 9 // pino utilizado para enviar dados ao servo motor 
#define pinobuttonUP 7 // pino de controle que recebe sinal quando o pushbutton e pressionado.
#define pinobuttonDN 4 // pino de controle que recebe sinal quando o pushbutton e pressionado.
#define inicio 40
#define fim 180

// cria o objeto servo
Servo myservo;  

// bloco de variaveis
int pos = inicio; // inicia a variavel de posicao do servo motor em 40 graus    
int readingUP = HIGH; 
int buttonStateUP = HIGH;
int buttonLastStateUP = HIGH;

int readingDN = HIGH;
int buttonStateDN = HIGH;
int buttonLastStateDN = HIGH;

// Para variaveis de tempo foi utilizado unsigned long, pois aumenta o valor positivo que a variavel pode armazenar 
unsigned long lastDebounceTime = 0;  // Ultimo registro do tempo do debounce 
unsigned long debounceDelay = 50;  // tempo de debounce 50ms (0,5s). Se o tempo desta variavel for maior que o 
                                   // tempo que se leva pressionando o pushbutton a condicao nunca sera satisfeita.

void setup() {
  // ativa o uso da ferramenta serial monitor. Esta ferramenta ajuda no debug do codigo fonte. 
  Serial.begin(9600);
  myservo.attach(pinoServo);  // atribui o pino do arduino ao objeto do servo motor - pino para controle
  pinMode(pinobuttonUP, INPUT); // atribui o pino do arduino ao pushbuttonUP
  pinMode(pinobuttonDN, INPUT); // atribui o pino do arduino ao pushbuttonDN
  myservo.write(inicio); // direciona o servo motor para posicao inicial 
}
void loop() {
  
  // *** Bloco 1 *** - estado inicial, botao em repouso, variaveis recebem sinal HIGH(1). Quando o botao e
  //pressionado a variavel recebe LOW (0).
  readingUP = digitalRead(pinobuttonUP);
  readingDN = digitalRead(pinobuttonDN);

  // *** Bloco 2 *** - executado se ocorrer mudanca no valor do pushbutton em relacao ao ultimo estado registrado
  //na execucao do loop. Ou seja, se o botao for pressionado. Ou se o interruptor mudou, devido a ruído ou pressão:
  if ((readingUP != buttonLastStateUP)||(readingDN != buttonLastStateDN))
  {
    lastDebounceTime = millis();
  }

  // *** bloco 3 *** - realiza o debounce, controle do bounce. Permite a execução do bloco se a subtracao entre
  // o tempo atual e o ultimo tempo de debounce registrado for maior que o tempo configurado para o debounce
  // delay. Se o tempo da variavel debounceDelay for maior que o tempo que se leva pressionando o pushbutton
  // a condicao nunca sera satisfeita.
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    // *** bloco 4 *** - executado se houver mudanca no estado do botao pushbutton. Ou seja, se o estado 
    // atual do botao pushbutton for diferente do estado registrado por buttonState na ultima vez que foi
    // satisfeita a condicao. 
    if (readingUP != buttonStateUP)
    {
      buttonStateUP = readingUP;

      // bloco 5 - Se o botao pushbuttonUP for pressionado (HIGH) a condicao e atendida na segunda rodada 
      // apos pressionamento do botao. ou seja quando o botao retornar ao estao HIGH (1).
      if(buttonStateUP == LOW)
      {
        // quando a variavel for incrementada e atingir o valor 150 o servo motor retornara
        //para a posicao de grau 30
        if (pos < fim) 
        {
          pos += 20; // atribui inicialmente 20 graus e vai somando de 20 em 20
          myservo.write(pos); // envia comando para o servo motor girar 
          delay(15); // espera 15 milessimos de segundo para que o servo possa procurar a posição
        }
      }
    }
    if (readingDN != buttonStateDN)
    {
      buttonStateDN = readingDN;

      // *** bloco 5 *** - Se o botao pushbuttonDN for pressionado (HIGH) a condicao e atendida na segunda
      // rodada apos pressionamento do botao. ou seja quando o botao retornar ao estao HIGH (1).
      if(buttonStateDN == LOW)
      {
        // quando a variavel for incrementada e atingir o valor 150 o servo motor retornara para a
        // posicao de grau 30
        if (pos > inicio) 
        {
          pos -= 20; // atribui inicialmente 20 graus e vai somando de 20 em 20
          myservo.write(pos); // envia comando para o servo motor girar 
          delay(15); // espera 15 milessimos de segundo para que o servo possa procurar a posição
        }
      }
    }
  }
  Serial.print("pos: ");
  Serial.println(pos);
  // *** bloco 6 *** - registra o ultimo estado do botao pushbuttonUP em buttonLastStateUP e pushbuttonDN
  //em buttonLastStateDN
  buttonLastStateUP = readingUP;
  buttonLastStateDN = readingDN;
}
