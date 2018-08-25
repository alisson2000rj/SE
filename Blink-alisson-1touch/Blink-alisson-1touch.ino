/*
 * Versao by alisson
 * modificado 25 ago 2018
 * utilizada com referencia o exemplo blink existente na IDE do arduino
 * http://www.arduino.cc/en/Tutorial/Blink
 
 * Blink - 1touch
 Utiliza o pino 13 como saida para fornecer sinal positivo ao LED.
 O estado do pino 13 muda conforme e alterado o estado do pino 7, que esta ligado a uma chave pushbutton. Ao pressionar a chave, o pino 7
 recebe sinal negativo, e consequentemente o sinal e reproduzido no pino 13.
*/

// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void setup()
{
  // inicializa os pinos: pino 13 como saida de dados e o pino 7 como entrada de dados 
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

// bloco roda eternamente, loop constante 
void loop()
{
  int btn = digitalRead(7); // realiza leitura do sinal enviado para o pino 7 e armazena seu valor na variavel btn
  digitalWrite(13, btn);   // envia sinal para o led de acordo com o valor armazenado na variavel btn
}
