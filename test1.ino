void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(4, HIGH);
  delay(500);
}

void loop()
{
  if (analogRead(A0) > 20)
  {
    digitalWrite(4, HIGH);
    Serial.write('x') ;
    
  }
  else
  {
    digitalWrite(4, LOW);
  }
  if (analogRead(A0) <10)
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
      Serial.write('y') ;
  }
  if ((analogRead(A0) > 10)&&(analogRead(A0) <20))
  {
    digitalWrite(3, HIGH);
    Serial.write('z') ;}
  else
  {
    digitalWrite(3, LOW);
  }

  Serial.println(analogRead(A0));
  delay(20);
}
