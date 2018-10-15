 /*
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
 *      
 */

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  DDRB |= 0b00100000;     //pinMode(13, OUTPUT); ligado ao LED
}

void loop() {
  // read the value from the sensor:
  ADMUX   = 0;                  // usa o canal 0
  ADMUX  |= (1 << REFS0);       // usa Vcc como referencia
  ADCSRA |= (1 << ADEN); // habilita o ADC
  
  ADCSRA |= (1 << ADSC);        // inicia a conversao
  while(ADCSRA & (1 << ADSC)); // espera a conversao
  int v = ADCL;                 // tem que ser lido antes do ADCH
  v = (ADCH << 8) + v;          // valor de 2 bytes
  
  Serial.println(v);
  
  // turn the ledPin on
  PORTB |= (1 << 5);            //digitalWrite(13, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(v);
  // turn the ledPin off:
  PORTB &= ~(1 << 5);            //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(v);
}
