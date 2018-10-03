

/*
 * Versao by alisson
 * modificado 25 ago 2018
 * utilizada com referencia o exemplo blink existente na IDE do arduino
 * http://www.arduino.cc/en/Tutorial/Blink
 
 * Blink - 1touch acelerate
 Utiliza o pino 13 como saida para fornecer sinal positivo ao LED.
 O estado do pino 13 muda conforme e alterado o estado do pino 7, que esta ligado a uma chave pushbutton. Ao pressionar a chave, o pino 7
 recebe sinal negativo, e consequentemente o sinal e reproduzido no pino 13.

 * Circuito utiliza um resistor de pull up: pino 7 recebendo 5v, com chave aberta. Com chave fechada o pino 7 recebe 0v.
 */

//variaveis globais
unsigned long tempo = 0;
unsigned long tempoup = 1000; // utilizada para armazenar o tempo quando pressionado o botao btnup, iniciada com 1000
unsigned long tempodown = 0; // utilizada para armazenar o tempo quando pressionado o botao btndown
unsigned long tempodif = 0; // utilizada para armazenar diferenca de tempo no pressionamento dos dois butoes
int spd = 1000;
int btnup;
int btndown;

// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void setup()
{
  // ativa monitor serial para ajudar na depuracao do codigo
  Serial.begin(9600);
  
  // inicializa o pino 13 conhecido como LED_BUILTIN para saida de dados - output.
  pinMode(13, OUTPUT);
  
  // pino 7 comeca com estado de 5v, HIGH - INPUT
  btnup = digitalRead(7);
  // pino 4 comeca com estado de 5v, HIGH - INPUT
  btndown = digitalRead(4);
}

// bloco setup roda uma unica vez quando pressionado reset ou ligado a placa pela primeira vez
void loop()
{
  
  // armazena na variavel btnup o valor lido no pino 7
  btnup = digitalRead(7); 
  //Registra o momento que o pushbutton btnup foi pressionado 
  if(btnup == LOW)
  {
    delay(10);
    if(btnup == digitalRead(7))
    {
      tempoup = millis();
      Serial.println("um ");
    
    }
  }
  
  // armazena na variavel btndown o valor lido no pino 4
  btndown = digitalRead(4); 
  //Registra o momento que o pushbutton btndown foi pressionado 
  if(btndown == LOW)
  {
    delay(10);
    if(btndown == digitalRead(4))
    {
      tempodown = millis();
      Serial.println("dois ");
    
    }
  }
  // Realiza a subtracao de tempos entre tempoup e tempodown
  if (tempoup<tempodown)
  {
    tempodif=(tempodown-tempoup);
  }
  else 
  {
    tempodif=(tempoup-tempodown);
  }

  // se tempodif for menor que 500, o led ficara acesso ate que o tempo seja maior. isso ocorrera apos pressonamento de um dos botoes.
  if (tempodif<500)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    // se o valor do tempo corrente (retornado pela funcao millis) menos o valor do tempo armazenado na variavel tempo for maior ou igual
    // ao valor da variavel spd divido 2, entao o o valor de saida do pino 13 sera positivo 
    if((millis() - tempo) >= spd/2)
    {
      digitalWrite(13, HIGH);
    }
    if((millis() - tempo) < spd/2)
    {
      digitalWrite(13, LOW);
    }
    if((millis() - tempo) >= spd)
    {
     tempo=millis();
    }
    // condicao que acelera a piscada do led quando o pushbutton up e acionado
    if((btnup == LOW) && (spd>100))
    {
      // tempo de espera para eliminar o efeito bounce. trabalho em conjunto com segundo teste condicional.
      delay(100);
      if(btnup == digitalRead(7))
      {
        spd=spd-100;
        Serial.print("spd: "); // imprime o valor existente em spd - ponto de referencia para ajuda na depuracao do codigo fonte
        Serial.println(spd);
      }
    }
    // condicao que diminui a piscada do led quando o pushbutton down e acionado
    if((btndown == LOW) && (spd<1000))
    {
      // tempo de espera para eliminar o efeito bounce. trabalho em conjunto com segundo teste condicional.
      delay(100);
      if(btndown == digitalRead(4))
      {
        spd=spd+100;
        Serial.print("spd: "); // imprime o valor existente em spd - ponto de referencia para ajuda na depuracao do codigo fonte
        Serial.println(spd);
      }
    }
  }
}

