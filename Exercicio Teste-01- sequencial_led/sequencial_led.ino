/*
 * Exercício do canal do Youtube Bincando com Ideias - aula 05
 * https://www.youtube.com/watch?v=qBZP4Mm46Ig&list=PL7CjOZ3q8fMc3OmT7gD7N6sLLFfXsXGZi&index=6&t=0s
 * 
 * Codificado por Alisson
 * 
 */


int pinLed[9] = {2,3,4,5,6,7,8,9,10};

void setup()
{
  // put your setup code here, to run once:
  int i;
  for(i = 0;i <= 9;i++)
  {
    pinMode(pinLed[i], OUTPUT);
  }
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int i;
  for(i = 0;i <= 9;i++)
  {
    digitalWrite(pinLed[i], HIGH);
    delay(100); 
  }
  for(i = 9;i >= 0;i--)
  {
    digitalWrite(pinLed[i], LOW);
    delay(100); 
  }
}
