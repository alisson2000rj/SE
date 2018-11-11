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
 */

#include <SoftwareSerial.h> // Inclui Biblioteca
#define buttonPin 7 // pino do button
#define ledPin 13  // pino do LED
#define lamp 8  // pino do LED
SoftwareSerial HC12(2, 3);        // Simula RX e TX em outras portas

char input;
String msgTX = "";
String msgRX = "";

int incomingByte;


void setup()
{
  pinMode(lamp, OUTPUT);
  pinMode(ledPin, OUTPUT);            // Declara que ledPin é uma saída
  pinMode(buttonPin, INPUT);          // Declara que buttonPin é uma entrada
  HC12.begin(9600);                  // Taxa de transferência do HC12
  Serial.begin(9600);                // Taxa de transferência da Serial
  digitalWrite(lamp, HIGH);
}
void loop()
{
  // **** bloco de envio ****
  if (Serial.available()>0)    // se tiver byte no buffer da serial satifaza condicao
  {                   
    input=Serial.read(); // realiza leitura do buffer serial, conform le ja retira o byte
    if (input != '\r' && input != '\n')  // retirada dos bytes de recuo de carro e nova linha
    {            
      msgTX += char(input);  // monta a string dos caracteres colocados no buffer da serial     
    }
  }
  else
  {
    delay(200);
    if(msgTX.length() != 0)     // se tiver msg tranfere pelo modulo HC-12
    {
      for (int i = 0; i < msgTX.length(); i++)
      {
        HC12.write(msgTX.charAt(i));  // tranfere pelo modulo HC-12 byte a byte
      }
      Serial.println(msgTX);  // no fim da TX imprime o conteudo transmitido  
      msgTX = "";  // limpa a string com conteudo transmitido 
    }
  }
  
  // **** bloco de recepcao ****
  while (HC12.available() > 0)
  {
    delay(5);   // gera um atraso antes realizar leitura do buffer 
    incomingByte = HC12.read();   // leitura do que chega pelo RX no modulo HC-12
    if (incomingByte != '\r' && incomingByte != '\n')       // retirada dos bytes de recuo de carro e nova linha
    {
      msgRX = msgRX + char(incomingByte);    // monta string por meio da recepcao de caracter e caractere
    }
  }
  if(msgRX.length() != 0)  // se tiver msg imprime na serial
  {
    Serial.println(msgRX);

    // Se msg recebida for igual a: 
    if (msgRX.endsWith("LED") || msgRX.endsWith("2"))
    {
      digitalWrite(ledPin, HIGH); // acende o LED
    }
    else if (msgRX.endsWith("led"))
    {
      digitalWrite(ledPin, LOW); // apaga o LED
    }
    else if (msgRX.endsWith("LAMPADA"))
    {
      digitalWrite(lamp, LOW); // apaga o LED
    }
    else if (msgRX.endsWith("lampada"))
    {
      digitalWrite(lamp, HIGH); // apaga o LED
    }
    msgRX = "";
  }
     
  int buttonState = digitalRead(buttonPin);   // Armazena o estado lógico do botão
  if (buttonState == 1) // Se o botão for pressionado
  {                     
    HC12.write('2');                      // TX pelo modulo HC-12
    
  }
 
}
