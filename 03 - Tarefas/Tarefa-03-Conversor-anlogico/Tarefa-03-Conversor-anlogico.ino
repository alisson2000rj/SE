
int ledPin = 13;      // select the pin for the LED


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
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
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(v);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(v);
}
