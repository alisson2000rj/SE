/*
 * Versao by alisson
 * modificado 20 set 2018
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
void writePonto(byte dot)   
{  
  digitalWrite(9, dot);
}

//Funcao que aciona o display
void sevenSegWrite(byte digit)  
{
  byte pin = 2;
  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount)  
  { 
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
    writePonto(1);  //Liga o ponto
    delay(100);   //Aguarda 100 milisegundos
}

int softPot = A0;
// define o tamanho da linha
const int GRAPH_LENGTH = 100; 

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino 9 do Arduino ligado ao segmento PONTO
  writePonto(0);  // Inicia com o ponto desligado
  pinMode(softPot, INPUT);
}

void loop() 
{
  // faz a leitura do valor de saida no softpot no pino A0 do arduino (pino analógico)
  int softPotADC = analogRead(softPot);
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
}
