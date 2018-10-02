/*
 * versao modificada por Alisson Cavalcante
 * heuristica desenvolvida com base nos Sketch: 
 *  - Debounce existente na IDE 1.8.5 do Arduino 
 *  - material encontrado no canal youtube brincando com ideas - Programacao com arduino aula 13 - delay e millis
 *  - http://www.arduino.cc/en/Tutorial/Debounce
 *  
 * versao - 4b  *** numero das versoes seguem o padrao "numeroletra". Ex.: 1a Sendo que a letra varia de a-e;   
 * 03/09/2018 - 12:34pm
 *
Descrição:

  + O circuito de alimentacao do LED e baseado no circuito Pull UP. Onde, o pinos de controle do LED estão sempre recebendo sinal HIGH do pino de +5v ate que a chave pushbutton seja pressionada.
  Entao, os pinos de controle do LED passam a receber sinal LOW do GND. 
     - O algoritmo utilizado e adaptado utilizava o circuito de pull down. Onde, o pino de controle do LED estava sempre recebendo sinal LOW do pino GND ate que a chave pushbutton fosse pressionada.
     Entao, os pinos de controle do LED passavam a receber sinal HIGH do pino de +5v. 

  + O estado inicial e registro do ultimo estado sao declarados como HIGH. Assim, ao ser carregado pela primeira vez o programa de controle recebe estado semelhante ao do circuito eletronico do arduino.  

  + O circuito conta com dois botoes push buttons: 
    - o buttonUP, responsavel por acelerar a frequencia com que o LED pisca. Para isso, ele atua diminuindo o valor da variavel spd; e
    - o buttonDOWN, responsavel por desacelerar a frequencia com que o LED pisca. Para isso, ele atua aumentando o valor da variavel spd.

  + Quando pressionados os dois botoes, e a diferenca no tempo de pressionamento for menor que 500ms (0,5s), o LED ficara acesso sem que ocorra intermitencia no seu estado. 


  + Componentes do circuito:
    - LED ligado do pino 13 ate o GND
    - pushbutton, conhecido com pushbuttonup, ligado do pino 7 até o +5V
    - pushbutton, conhecido com pushbuttonDOWN, ligado do pino 4 até o +5V
    - 1 resistor de 1k ohm ligado do +5v ate o pushbuttonup
    - 1 resistor de 1k ohm ligado do +5v ate o pushbuttonDOWN
    - 1 resistor de 220 ohm ligado do led ate o pino 13 

  
*/

// bloco de declaracao de constantes que indicam quais pinos do circuito do arduino serao utilizados 
#define buttonPinup 7    // indica o pino do arduino que recebera sinal HIGH ate que o buttonUP seja pressionado. **** QUANDO PRESSIONADO RECEBE GND ****. 
#define buttonPindown 4    // indica o pino do arduino que recebera sinal HIGH ate que o buttonDOWN seja pressionado. **** QUANDO PRESSIONADO RECEBE GND ****. 
#define ledPin 13     // indica o pino do arduino que enviara sinal para o LED.

// bloco de declaracao de variaveis de controle de estado
int ledState = HIGH;         // the current state of the output pin
int buttonStatedown = HIGH; // Registra o ultimo estado do buttonDOWN quando satifeita a condicao  the current reading from the input pin
int buttonStateup = HIGH;
int lastButtonStateup = HIGH;   // the previous reading from the input pin
int lastButtonStatedown = HIGH;   // the previous reading from the input pin


// Para variaveis de tempo foi utilizado unsigned long milliseconds, retornara o maior numero que pode ser gravado como um inteiro
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // tempo de debounce 50ms (0,5s). Se o tempo dest avariavel for maior que o tempo que se leva pressionando o pushbutton o a condicao nunca sera satisfeita.

// bloco de variaveis de controle da frequencia com que o LED piscara
int spd = 1000; // frequencia com que o led pisca. Iniciada com 1000ms ou 1s. Ciclo completo aceso/apagado com 2s. 
unsigned long lasttempoled = 0; // acumula o tempo 

// bloco de variaveis de controle que farao com que o LED permaceca acesso ou pisque intermitente
unsigned long tempoup = 0; // utilizada para armazenar o tempo do botao btnup quando pressionado, iniciada com 0ms (0s)
unsigned long tempodown = 550; // utilizada para armazenar o tempo do botao btndown quando pressionado, iniciada com 550ms (1s)
unsigned long tempodif = 0; // utilizada para armazenar diferenca de tempo no pressionamento dos dois botoes, iniciada com 0ms (0s)

void setup()
{
  // ativa o uso da ferramenta serial monitor. Esta ferramenta ajuda no debug do codigo fonte. 
  Serial.begin(9600);

  // Configura os pinos do arduino que serao utilizados. Utiliza como base os valores configurados no bloco de constantes.
  pinMode(buttonPinup, INPUT);
  pinMode(buttonPindown, INPUT);
  pinMode(ledPin, OUTPUT);

  // Configura estado inicial do LED 
  digitalWrite(ledPin, ledState);
}

void loop()
{
  // Bloco 1 - estado inicial, circuito alimentado pelo 5v, botoes em repouso, variaveis recebem sinal HIGH(1). Quando os botoes são pressionados o as variaveis recebem LOW(0).
  int readingUP = digitalRead(buttonPinup);
  int readingDOWN = digitalRead(buttonPindown);
  /*
  Serial.print("readingUP: ");
  Serial.println(readingUP);
  Serial.print("readingDOWN: ");
  Serial.println(readingDOWN);
 */
  // Bloco 2 - executado se ocorrer mudanca nos valores dos botoes buttonUP ou buttondwon em relacao ao ultimo estado registrado na execucao do loop. Ou seja, se os botoes forem pressionados.
  // Se o interruptor mudou, devido a ruído ou pressão:
  if ((readingUP != lastButtonStateup) || (readingDOWN != lastButtonStatedown))
  {
    // reseta o tempo da variavel de registro da ultima vez que ocorreu o debounce
    lastDebounceTime = millis();
   // Serial.println("bloco 2");
  }

  // bloco 3 - que realiza o debounce, controle do bounce. Permite a execução do bloco se a subtracao entre o tempo atual e o ultimo tempo de debounce registrado
  // for maior que o tempo configurado para o debounce delay. Se o tempo da variavel debounceDelay for maior que o tempo que se leva pressionando o pushbutton a condicao nunca sera satisfeita.
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    //Serial.print("bloco 3 : ");
    //Serial.println(millis() - lastDebounceTime);
    
    // bloco 4 - executado se houver mudanca no estado do botao buttonUP. Ou seja, se o estado atual do botao buttonUP for diferente do estado registrado por buttonStateup na ultima vez que foi
    // satisfeita a condicao. 
    if (readingUP != buttonStateup)
    {
      buttonStateup = readingUP;
      // bloco 5 - AUMENTA a velocidade com que o LED pisca. Se o botao buttonUP for pressionado (HIGH) e spd for menor 1000ms (1s). Condicao e atendida na segunda rodada apos pressionamento do botao.
      // ou seja quando o botao retornar ao estao HIGH (1).
      if ((buttonStateup == HIGH)&& (spd>100))
      {
        spd=spd-100;
        Serial.print("spd: ");
        Serial.println(spd);
      }
      if(buttonStateup == HIGH)
      {
        tempoup = millis();
      }
    }

    // bloco 6 - executado se houver mudanca no estado do botao readingDOWN. Ou seja, se o estado atual do botao readingDOWN for diferente do estado registrado por buttonStatedown na ultima vez que foi
    // satisfeita a condicao.
    if (readingDOWN != buttonStatedown)
    {
      buttonStatedown = readingDOWN;
      // bloco 7 - DIMINUI a velocidade com que o LED pisca. Se o botao buttonDOWN for pressionado (HIGH) e spd for menor 1000ms (1s).
      if ((buttonStatedown == HIGH)&& (spd<1000))
      {
        spd=spd+100;
        Serial.print("spd: ");
        Serial.println(spd);
      }
      if(buttonStatedown == HIGH)
      {
        tempodown = millis();
      }
    }
  }

  // Bloco 9 - Realiza a subtracao entre o tempo no qual os botoes buttonUP e buttonDOWN foram pressionados. Resolve o problema com a subtracao caso o segundo termo seja um valor maior que o 
  // primeiro termo. Ja que o tipo da variaval tempodif é unsigned (aceita apenas valores positivos).
  tempodif = max(tempodown,tempoup) - min(tempodown,tempoup);
  //Serial.print("resultado: ");
  //Serial.println(tempodif);
 
  // Bloco 10 - Se a diferenca de tempo entre tempoup e tempodown for menor que 500ms (0,5s) o LED permanecera aceso ate que um dos botoes seja pressionado. Senao, o LED permanecera piscando.
  if (tempodif < 500)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    // bloco 11 - responsavel pela frequencia com que o LED pisca.
    // Referencia - site brincando com ideas - video aula programacao com arduino - aula 13 - delay e millis
    if((millis() - lasttempoled) < spd) // tempo menor que 1000ms retorna LED apagado 
    {
      digitalWrite(13, LOW);
    }
    if((millis() - lasttempoled) >= spd) // tempo maior que 1000ms retorna LED aceso
    {
      digitalWrite(13, HIGH);
    }
    if((millis() - lasttempoled) >= spd*2) // tempo maior que 2000ms registra o tempo em lastempoled para uso na proxima rodada
    {
     lasttempoled = millis();
    }
  }
    
  // bloco 12 - registra o ultimo estado dos botoes buttonUP e buttonDOWN nas variaveis lastButtonState. 
  lastButtonStateup = readingUP;
  lastButtonStatedown = readingDOWN;
}
