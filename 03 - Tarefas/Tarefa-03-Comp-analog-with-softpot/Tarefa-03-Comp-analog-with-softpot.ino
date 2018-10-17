/*
 * Versão adaptada da proposta em sala de aula pelo Prof. Francisco Santanna
 * Adaptação By Alisson 
 * versão(abc): 1a
 * 03/10/2018
 * 
 *   - Registradores de 8bits
 *      DDRxn: [w] direção do pino n na porta x   // 0 INPUT - 1 OUTPUT
 *      PORTxn:[w] novo valor ou confguração pull up do pino n na porta x  //  0 LOW - 1 HIGH
 *      PINxn: [r] valor atual do pino n na porta x
 *
 *      #define setBit(valor,bit)       (valor |= (1<<bit))
 *      #define clearBit(valor,bit)     (valor &= ~(1<<bit))
 *      #define testBit(valor,bit)      (valor & (1<<bit))
 *      #define toggleBit(valor, bit)   (valor ^= (1<<bit))
 *  
 *      ACO = 
 *            HIGH, se AIN0 > AIN1
 *            LOW, se AIN0 <= AIN1
 *            AIN0=PIN6, AIN1=PIN7
 */

void setup() {
  Serial.begin(9600);
  ACSR = 0<<7;     //Ativa o Comparador Analógico. O bit 7 (ACD) configurado com 1 = off - com 0 = ON. 
  DDRB = 0b00110000;     //pinMode(13, OUTPUT) ou bit 5 do registrador DDRB - PB5 e pinMode(12, OUTPUT) ou bit 4 do registrador DDRB - PB4
  DDRC = 0b0000000;       //pinMode(A0, INPUT) ou bit 0 do registrador DDRC - PC0 ; ligado ao terminal cursor (pino variavel) do potenciometro 
                          //pinMode(A1, INPUT) ou bit 1 do registrador DDRC - PC1 ; ligado ao 3.3v do arduino
}
void loop() {
  Serial.print("ACO : ");
  Serial.println(ACSR & (1<<ACO));
 
  if (ACSR & (1<<ACO))   //Realiza a leitura do bit 5 (ACO) do registrador ACSR. Se for diferente de 0 acende o LED, senão apaga o LED
  {
    PORTB |= (1 << 5); //digitalWrite(13, 1); //configura o bit 5 do registrador PORTB para "1" (LED aceso)
  }
  else
  {
    PORTB &= ~(1 << 5); //digitalWrite(13, 0);  //configura o bit 5 do registrador PORTB para "0" (LED apagado)
  }
  if(analogRead(A0)== analogRead(A1))
  {
    PORTB |= (1 << 4); //digitalWrite(13, 1); //configura o bit 5 do registrador PORTB para "1" (LED aceso)
  }
  else
  {
    PORTB &= ~(1 << 4); //digitalWrite(13, 0);  //configura o bit 5 do registrador PORTB para "0" (LED apagado)
  }
  Serial.print("A0 : ");
  Serial.println(analogRead(A0));
  Serial.print("A1 : ");
  Serial.println(analogRead(A1));
  
}
