//  variaveis
int estado = 0;
boolean apertado = false;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  switch(estado){
    case 0:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      if(!digitalRead(10))
        estado = 1;
      delay(50);
      break;
     case 1:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      if(digitalRead(10))
        estado = 2;
      delay(50);
      break;
     case 2:
      if(!digitalRead(10))
        estado = 3;
      delay(50);
      break;
     case 3:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      if(digitalRead(10))
        estado = 4;
      delay(50);
      break;
     case 4:
      if(!digitalRead(10))
        estado = 5;
      delay(50);
      break;
     case 5:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      if(digitalRead(10))
        estado = 6;
      delay(50);
      break;
     case 6:
      if(!digitalRead(10))
        estado = 7;
      delay(50);
      break;
     case 7:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      if(digitalRead(10))
        estado = 8;
      delay(50);
      break;
     case 8:
      if(!digitalRead(10))
        estado = 9;
      delay(50);
      break;
     case 9:
      if(digitalRead(10))
        estado = 0;
      delay(50);
      break;
  }
}
