int i=0;
void setup()
{
  DDRB |= 1 << 5; // Ativa o pino 13 (PB5) como OUTPUT para o LED - Legenda: 0 INPUT - 1 OUTPUT
  
  // Configuração do TIMER1
  TCCR1A = 0;                //limpa registrador
  TCCR1B = 0;                //limpa registrador
  TCNT1  = 0;                //zera temporizador
 
  OCR1A = 15625;            // carrega registrador de comparação: 16MHz/1024/1Hz = 15625 ou 0X3D09
  TCCR1B |= (1 << WGM12);    // modo CTC=1 e modo normal=0
  TCCR1B |= (1<<CS12)|(1 << CS10);   // prescaler de 1024: CS12 = 1 e CS10 = 1  
  TIMSK1 |= (1 << OCIE1A);  // habilita interrupção por igualdade de comparação
}
void loop()
{
  //loop principal. a manipulação do led é feita na ISR
}
 
ISR(TIMER1_COMPA_vect)          // interrupção por igualdade de comparação no TIMER1
{
 //modo CTC zera o timer quando atingido valor de comparação
  i++;
  if(i==4)
  { 
    PORTB ^= (1 << 5); // Inverte o estado do bit 5 
    i=0;
  }
}
