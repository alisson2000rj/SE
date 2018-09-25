/*
 * Versao by alisson
 * modificado 12 set 2018
 * utilizada com referencia o exemplo blink existente na IDE do arduino
 * http://www.arduino.cc/en/Tutorial/Blink
 
 * Blink - 1touch-always
 Utiliza o pino 13 como saida para fornecer sinal positivo ao LED.
 O estado do pino 13 muda conforme e alterado o estado do pino 7, que esta ligado a uma chave pushbutton. Ao pressionar a chave, o pino 7
 recebe sinal negativo, e consequentemente o sinal HIGH e fixado no pino 13.

  Descrição:
  
  + O circuito de alimentacao do LED e baseado no circuito Pull UP. Onde, o pinos de controle do LED estão sempre recebendo sinal HIGH do pino de +5v ate que a chave pushbutton seja pressionada.
  Entao, os pinos de controle do LED passam a receber sinal LOW do GND. 
     - O algoritmo utilizado e adaptado utilizava o circuito de pull down. Onde, o pino de controle do LED estava sempre recebendo sinal LOW do pino GND ate que a chave pushbutton fosse pressionada.
     Entao, os pinos de controle do LED passavam a receber sinal HIGH do pino de +5v. 

*/

#define spd 1000
unsigned long lasttempoled = 0; // acumula o tempo 
  
// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void setup()
{
  // ativa o uso da ferramenta serial monitor. Esta ferramenta ajuda no debug do codigo fonte. 
  Serial.begin(9600);
  // inicializa os pinos: pino 13 como saida de dados e o pino 7 como entrada de dados 
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

// bloco roda eternamente, loop constante 
void loop()
{
  int btn = digitalRead(7); // realiza leitura do sinal enviado para o pino 7 e armazena seu valor na variavel btn
  Serial.print("btn: ");
  Serial.println(btn);
  // bloco 1 - responsavel por fixar LED aceso.
  // utiliza uma negação pois o o circuito utilizado e o PULL UP, que mantem o pino 7 alimentado com sinal HIGH. 
  if(!btn)
  {
    digitalWrite(13, HIGH);   // envia sinal para o led de acordo com o valor armazenado na variavel btn
    while(1);
  }
  
  // bloco 2 - responsavel pela frequencia com que o LED pisca.
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
