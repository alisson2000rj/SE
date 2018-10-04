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
  ACSR  = 0;              //Configura o Comparador Analógico, ativando com todos os bits igual a 0 
  //ACSR |= (1<<7);         //Desliga o Comparador lógico setando o bit ACD com valor 1 (1<<7)
  DDRB |= 0b00100000;     //pinMode(13, OUTPUT); ligado ao LED
  DDRC |= (0 << 0);       //pinMode(A0, INPUT); ligado ao terminal cursor (pino variavel) do potenciometro 
  DDRC |= (0 << 1);       //pinMode(A1, INPUT); ligado ao 3.3v do arduino
}
void loop() {
  int aco = ACSR;         //Atribui os valores de ACRS a variável aco 
  
  Serial.print("aco1 : ");
  Serial.println(aco);
  aco &= (1 << ACO);      //Realiza operação 'and' com o bit 'ACO' setado em 1 e salva o valor dentro da variavel interia "aco"
  Serial.print("aco2 : ");
  Serial.println(aco);
  if (aco)                //Testa se o valor é verdadeiro, ou seja "1". Se for acende o LED, senão apaga o LED
  {
    PORTB |= (1 << 5); //digitalWrite(13, 1); //configura o bit 5 do registrador PORTB para "1" (LED aceso)
  }
  else
  {
    PORTB &= ~(1<<5); //digitalWrite(13, 0);  //configura o bit 5 do registrador PORTB para "0" (LED apagado)
  }
  
 // Serial.print("A0 : ");
 // Serial.println(analogRead(A0));
 // Serial.print("A1 : ");
//  Serial.println(analogRead(A1));
  
  
}
