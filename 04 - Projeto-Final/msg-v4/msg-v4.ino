

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
 * sintaxe do comando : *a*bc*d*e 
 * 
 * onde:
 *      a -> valor da operacao; 
 *      bc -> numero da porta formada por dois digitos. Ex.: 01, 02, 03, 10, 11, 12
 *      d -> valor do dado a ser transmitido, 0 ou 1;
 *      e -> endereço de destino
 *  
 * 
 * 
 * 
 */
#include <SoftwareSerial.h> // Inclui Biblioteca
#define buttonPin 7 // pino do button
#define ledPin 13  // pino do LED
#define lamp 8  // pino do LED
int id = 3;
int i = 0;

SoftwareSerial HC12(2, 3);        // Simula RX e TX em outras portas

char input;
String msgTX = "";
String msgRX = "";

int incomingByte;


void setup()
{
  pinMode(lamp, OUTPUT);
  pinMode(ledPin, OUTPUT);            // Declara que ledPin é uma saída
  pinMode(04, OUTPUT);
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
      if(msgTX[0]=='*'){
        msgTX = msgTX + String(id);
      }
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
//#############################################################
  // se for comando retira espaco em branco
  if(msgRX.charAt(0)!='*' && msgRX.length() != 0){
    Serial.print("MSG Recebida:");
    Serial.println(msgRX);
    msgRX = "";
    
  }

  
   if(msgRX.charAt(0)=='*' && msgRX.length() != 0){
  
    Serial.print("Comando Recebido :");
    Serial.println(msgRX);
    //Serial.println(msgRX.charAt(1));

    // se for para o seu id trata o comando, senao reenvia o comando
  // Serial.println(msgRX.substring(8,9).toInt());
    
    if(msgRX.substring(8,9).toInt() == id)
    {
      trataComandos(msgRX);
    }
    else
    {
      reenviaComandos(msgRX);
    }
    
    msgRX = "";
   
  } 
  int buttonState = digitalRead(buttonPin);   // Armazena o estado lógico do botão
  if (buttonState == 1) // Se o botão for pressionado
  {                     
    HC12.write('2');                      // TX pelo modulo HC-12
    
  }
 
}

// Funcao trata comando
void trataComandos(String a) {
  //Serial.print("teste : ");
  //Serial.println(a.charAt(3));
  digitalWrite(a.substring(3, 5).toInt(), a.substring(6).toInt());  
}

// Funcao reenvia comando 
void reenviaComandos(String a) {

  int tam = a.length();
  //Serial.println(tam);
 // Serial.println(a.substring(9,tam));
  String sel = a.substring(9,tam); 

  //int r = sel.indexOf(String(id));
  //Serial.println(r);
  if(sel.indexOf(String(id))!= -1)
  {
    Serial.println("MSG Voltou ao Origem");
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




