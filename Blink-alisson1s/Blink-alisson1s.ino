/*
 * Versao by alisson
 * modificado 25 ago 2018
 * utilizada com referencia o exemplo blink existente no programa do arduino
 * http://www.arduino.cc/en/Tutorial/Blink
 
 * Blink - 1s ( 1segundo )
 Utiliza o pino 13 como saida para fornecer sinal positivo ou negativo ao LED a cada 1 segundo.
 
*/

// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void setup()
{
  // inicializa o pino 13 como saida de dados 
  pinMode(13, OUTPUT);
}

// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void loop()
{
  digitalWrite(13, HIGH);  // envia sinal positivo para o led
  delay(1000); // funcao que gera atraso de 1000ms ou 1s
  digitalWrite(13, LOW);  // envia sinal negativo  para o led
  delay(1000); // funcao que gera atraso de 1000ms ou 1s
}
