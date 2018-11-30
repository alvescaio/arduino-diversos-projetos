#include <CapacitiveSensor.h>

const int buzzer = 13;
const int led_pin[3] = {11, 10, 9};
const int freqs[3] = {261.63, 293.66, 329.63};
const int velocidade_padrao = 500;
const long tempo_limite_toque = 3000;

long randNumber;
int nivel = 0;
long seq[200];
int velocidade = 500;

CapacitiveSensor   cs_8_5 = CapacitiveSensor(8,5);        // 10 megohm resistor between pins 8 & 5, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_8_6 = CapacitiveSensor(8,6);        // 10 megohm resistor between pins 8 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_8_7 = CapacitiveSensor(8,7);        // 10 megohm resistor between pins 8 & 7, pin 8 is sensor pin, add wire, foil

void setup()                    
{

  cs_8_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  
  pinMode(led_pin[0], OUTPUT);
  pinMode(led_pin[1], OUTPUT);
  pinMode(led_pin[2], OUTPUT);
    
  acendeLeds(2000);  
  pinMode(buzzer, OUTPUT);

}

void loop()                    
{
  Serial.println("------- Produz Seq -------");
  produzSeq();
  Serial.println("------- Reproduz Sequencia -------"); 
  reproduzSeq();
  int i;
  for(i = 0; i <= nivel; i++){
     int val_lido;
     Serial.println("------- Ler Toque -------");
     int estado_sensor_toque = 0;
     boolean exit_while = false;
     long tempo_anterior = millis();
     while(!exit_while){
        val_lido = lerToque();
        Serial.print("Valor esperado: ");
        Serial.print(seq[i]);
        Serial.print(" -- Valor lido: ");
        Serial.println(val_lido);

        switch(estado_sensor_toque){
          case 0:
            if(val_lido != 0){
              estado_sensor_toque = 1;
              tempo_anterior = millis();
            }
            break;          
          case 1:
            if(verificaSeq(i, val_lido)){
              estado_sensor_toque = 2;
              tone(buzzer, freqs[seq[i]-1]);
              digitalWrite(led_pin[seq[i]-1], HIGH);
            }else{
              exit_while = true;
            }
            break;
           case 2:
            tempo_anterior = millis();
            if(!verificaSeq(i, val_lido)){
              exit_while = true;
            }
            break;            
        }
        if((millis() - tempo_anterior > tempo_limite_toque) && nivel > 0){
          break;
        }
        delay(50);
     }
     Serial.println("------- Verifica Seq -------");
     if(estado_sensor_toque == 2){
        Serial.print("nivel = ");
        Serial.println(nivel);
        noTone(buzzer);
        digitalWrite(led_pin[seq[i]-1], LOW);
        delay(50);
        if(i == nivel){
          nivel++;
          if(velocidade > 100){
            velocidade = velocidade - 50; 
          }
          break;
        }
     }else{
        int freq = 0;
        int pisca_led = 0;
        acendeLeds(1);
        for(freq = 2000; freq > 10; freq--){
          tone(buzzer, freq);
          delay(0.8);
          if(freq/100 > 15){
            pisca_led = 0;
          }else if(freq/100 < 15 && freq/100 > 12){
            pisca_led = 1;
          }else if(freq/100 < 9){
            pisca_led = 2;
          }
        }
        acendeLeds(0);
        noTone(buzzer);
        delay(2000);
        nivel = 0;
        velocidade = velocidade_padrao;
     }
  }
  delay(50);
}

void reproduzSeq(){
  int i;
  for(i = 0; i <= nivel; i++){
    delay(100);
    tone(buzzer, freqs[seq[i]-1]);
    digitalWrite(led_pin[seq[i]-1], HIGH);
    delay(velocidade);
    noTone(buzzer);
    digitalWrite(led_pin[seq[i]-1], LOW);
  }
}

void produzSeq(){
  // randomSeed() basicamente "embaralha" a função random().
  randomSeed(analogRead(0));
  seq[nivel] = random(1, 4);
  Serial.print("Seq[");
  Serial.print(nivel);
  Serial.print("] = ");
  Serial.println(seq[nivel]);
  delay(500);
}

boolean verificaSeq(int pos, int val){
  Serial.print("Seq[");
  Serial.print(pos);
  Serial.print("] = ");
  Serial.println(val);
  if(seq[pos] != val){
    return false;
  }

  return true;
}

int lerToque(){
    long start = millis();
    long total1 =  cs_8_5.capacitiveSensor(30);
    long total2 =  cs_8_6.capacitiveSensor(30);
    long total3 =  cs_8_7.capacitiveSensor(30);
    
    if(total1 > 100 && total2 < 100 && total3 < 100){
      return 1;
    }else if(total1 < 90 && total2 > 90 && total3 < 90){
      return 2;
    }else if(total1 < 90 && total2 < 90 && total3 > 90){
      return 3;
    }else if(total1 < 90 && total2 < 90 && total3 < 90){
      return 0;
    }
    
    return 0;
}

