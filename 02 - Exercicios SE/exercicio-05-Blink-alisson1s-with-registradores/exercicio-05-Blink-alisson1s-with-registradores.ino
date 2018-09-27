/*
  Blink

- Registradores de 8bits
 DDRxn: [w] direção do pino n na porta x   // 0 INPUT - 1 OUTPUT
 PORTxn:[w] novo valor ou confguração pull up do pino n na porta x  //  0 LOW - 1 HIGH
 PINxn: [r] valor atual do pino n na porta x
 
#define setBit(valor,bit)       (valor |= (1<<bit))
#define clearBit(valor,bit)     (valor &= ~(1<<bit))
#define testBit(valor,bit)      (valor & (1<<bit))
#define toggleBit(valor, bit)   (valor ^= (1<<bit))

#### Material de apoio
  # Video de apoio Youtube
    https://www.youtube.com/watch?v=-dT4_AAB4iE
    
  # Sites 
    http://renatoaloi.blogspot.com/2015/09/tutorial-matematica-de-bits-no-arduino.html
    http://renatoaloi.blogspot.com/2015/09/arduino-manipulacao-direta-de-portas.html
    https://www.embarcados.com.br/bits-em-linguagem-c/

*/
#define spd 1000
unsigned long lasttempoled = 0; // acumula o tempo 

void setup() {
  // Envia os dados da saida serial para o monitor  
  Serial.begin(9600);

  DDRD |= 0 << 7;  // ativa o pino 7 (PD7) como INPUT - Legenda: 0 INPUT - 1 OUTPUT
  PORTD |= 1 << 7; // Manda Sinal HIGH para o pino 7 (PULL-UP) - Legenda: 0 LOW - 1 HIGH
  DDRB |= 1 << 5; // Ativa o pino 13 (PB5) como OUTPUT para o LED - Legenda: 0 INPUT - 1 OUTPUT
}
void loop() {

  // Referencia - site brincando com ideas - video aula programacao com arduino - aula 13 - delay e millis
  if((millis() - lasttempoled) < spd) // tempo menor que 1000ms retorna LED apagado 
  {
    PORTB &= ~(1 << 5 );              // Desliga o LED - Legenda: 0 LOW - 1 HIGH
  }
  if((millis() - lasttempoled) >= spd) // tempo maior que 1000ms retorna LED aceso
  {
   PORTB |= (1 << 5);                // Liga o LED - Legenda: 0 LOW - 1 HIGH
  }
  if((millis() - lasttempoled) >= spd*2) // tempo maior que 2000ms registra o tempo em lastempoled para uso na proxima rodada
  {
   lasttempoled = millis();
  }  

  Serial.println("etapa 1 ");
  if ((PIND & (1 << 7)) == LOW)
  {
    Serial.print("execuntado while(1)!!!! ");
    PORTB |= (1 << 5); // Liga o LED - Legenda: 0 LOW - 1 HIGH
    int i=0;
    while(i<=5)
    {
      Serial.println("LED acesso por 5 segundos!!!");
      delay(1000);
      i++;
    }
  }
}

