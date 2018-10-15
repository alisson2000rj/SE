
/*
 * Codigo com time por oveflow
 */

#define ledPin 13
// variavel que ira contar o tempo de acordo com o prescaler definido.
int i=0;
 
void setup()
{
  pinMode(ledPin, OUTPUT);
 
  // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS12)|(0 << CS11)|(1 << CS10);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
  
  TCNT1 = 49911;                    // incia timer com valor para que estouro ocorra em 1 segundo. Para que o timer estoure a cada segundo
                                     // é necessário iniciar seu valor com a diferença entre o seu valor máximo (65536) e o período desejado
                                    // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção de estouro do TIMER1
}
void loop()
{
  //loop principal. a manipulação do led é feita na ISR
}

ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  TCNT1 = 49911;// Renicia TIMER
  i++;
  if(i==10)
  {
    digitalWrite(ledPin, !digitalRead(ledPin)); //inverte estado do led
    i=0;
  }
}
