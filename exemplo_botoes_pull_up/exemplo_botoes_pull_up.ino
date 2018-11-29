int botao[] = {2, 3, 4};
const int led_pin[3] = {11, 10, 9};
const int buzzer = 13;

// Mi(E) - 330; Re(D) - 297; Lá(A) - 440
const int E = 330;
const int D = 297;
const int A = 440;

void setup() {
  Serial.begin(9600);
  pinMode(botao[0], INPUT_PULLUP);
  pinMode(botao[1], INPUT_PULLUP);
  pinMode(botao[2], INPUT_PULLUP);

  pinMode(led_pin[0], OUTPUT);
  pinMode(led_pin[1], OUTPUT);
  pinMode(led_pin[2], OUTPUT);
  
  acendeLeds(2000);
  pinMode(buzzer, OUTPUT);

}

int state[] = {0, 0, 0};

void loop() {
  switch(state[0]){
    case 0:
      if(!digitalRead(botao[0])) state[0] = 1;
      delay(10);
      break;
     case 1:
      Serial.println("Botao 1");
      //chama o modo de jogo 1
      tone(buzzer, E);
      acendeLeds(1);      
      state[0] = 2;
      break;
     case 2:
      if(digitalRead(botao[0])){
        noTone(buzzer);
        acendeLeds(0);
        state[0] = 0;
      }
      delay(10);
      break;    
  }

  switch(state[1]){
    case 0:
      if(!digitalRead(botao[1])) state[1] = 1;
      delay(10);
      break;
     case 1:
      Serial.println("Botao 2");
      //chama o modo de jogo 2
      acendeLeds(1);
      tone(buzzer, D);
      state[1] = 2;
      break;
     case 2:
      if(digitalRead(botao[1])){
        noTone(buzzer);
        acendeLeds(0);
        state[1] = 0;
      }
      delay(10);
      break; 
  }

  switch(state[2]){
    case 0:
      if(!digitalRead(botao[2])) state[2] = 1;
      delay(10);
      break;
     case 1:
      Serial.println("Botao 3");
      //chama o modo de jogo 3
      acendeLeds(1);
      tone(buzzer, A);
      state[2] = 2;
      break;
     case 2:
      if(digitalRead(botao[2])){
        noTone(buzzer);
        acendeLeds(0);
        state[2] = 0;
      }
      delay(10);
      break;    
  }

}
