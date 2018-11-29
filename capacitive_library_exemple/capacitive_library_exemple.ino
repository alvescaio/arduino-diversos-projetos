#include <CapacitiveSensor.h>

/*
 * Esboço de Demonstração da Biblioteca CapitiveSense
 * Paul Badger 2008
 * Usa um resistor de alto valor, por exemplo, 10 megohm entre o pino de envio e o pino de recebimento
 * Resistor efeitos sensibilidade, experimente com valores, 50 kilohm - 50 megohm. Valores de resistência maiores produzem valores de sensor maiores.
 * Receber pino é o pino do sensor - experimente diferentes quantidades de folha / metal neste pino
 * Os melhores resultados são obtidos se a folha do sensor e o fio estiverem cobertos com um isolante, como papel ou folha de plástico.
 */

// botoes: 2, 3, 4

const int buzzer = 13;
const int led_pin[3] = {11, 10, 9};
const int freqs[3] = {261.63, 293.66, 329.63};

long randNumber;
int nivel = 0;
long seq[200];

CapacitiveSensor   cs_8_5 = CapacitiveSensor(8,5);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_8_6 = CapacitiveSensor(8,6);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_8_7 = CapacitiveSensor(8,7);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

void setup()                    
{

   cs_8_5 .set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

  pinMode(led_pin[0], OUTPUT);
  pinMode(led_pin[1], OUTPUT);
  pinMode(led_pin[2], OUTPUT);

  digitalWrite(led_pin[0], HIGH);
  digitalWrite(led_pin[1], HIGH);
  digitalWrite(led_pin[2], HIGH);
  delay(2000);
  digitalWrite(led_pin[0], LOW);
  digitalWrite(led_pin[1], LOW);
  digitalWrite(led_pin[2], LOW);  

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
     while(1){
        val_lido = lerToque();
        Serial.print("Valor esperado: ");
        Serial.print(seq[i]);
        Serial.print(" -- Valor lido: ");
        Serial.println(val_lido);
        if(val_lido != 0){
          break;
        }
        delay(50);
     }
     Serial.println("------- Verifica Seq -------");
     if(verificaSeq(i, val_lido)){
        Serial.print("nivel = ");
        Serial.println(nivel);

        tone(buzzer, freqs[seq[i]-1]);
        digitalWrite(led_pin[seq[i]-1], HIGH);
        delay(500);
        noTone(buzzer);
        digitalWrite(led_pin[seq[i]-1], LOW);
        delay(50);
        if(i == nivel){
          nivel++;
          break;
        }
     }else{
        int freq = 0;
        int pisca_led = 0;
        digitalWrite(led_pin[0], HIGH);
        digitalWrite(led_pin[1], HIGH);
        digitalWrite(led_pin[2], HIGH);
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
        digitalWrite(led_pin[0], LOW);
        digitalWrite(led_pin[1], LOW);
        digitalWrite(led_pin[2], LOW);
        noTone(buzzer);
//        digitalWrite(led_pin[1], HIGH);
//        delay(100);
//        digitalWrite(led_pin[1], LOW);
//        delay(50);
//        digitalWrite(led_pin[2], HIGH);
//        delay(100);
//        digitalWrite(led_pin[2], LOW);
//        delay(50);
//        digitalWrite(led_pin[1], HIGH);
//        delay(100);
//        digitalWrite(led_pin[1], LOW);
        delay(2000);
        nivel = 0;
     }
  }
  delay(50);                             // arbitrary delay to limit data to serial port 
}

void reproduzSeq(){
  int i;
  for(i = 0; i <= nivel; i++){
    delay(100);
    tone(buzzer, freqs[seq[i]-1]);
    digitalWrite(led_pin[seq[i]-1], HIGH);
    delay(500);
    noTone(buzzer);
    digitalWrite(led_pin[seq[i]-1], LOW);
  }
}

void produzSeq(){
  // Se o pino de entrada analógica 0 é deixado desconectado,
  // o ruído aleatório analógico irá causar a chamada de randomSeed()
  //  gerar sementes aleatórias diferentes cada vez que o sketch roda.
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

//    Serial.print(millis() - start);        // check on performance in milliseconds
//    Serial.print("\t");                    // tab character for debug window spacing
//
//    Serial.print(total1);                  // print sensor output 1
//    Serial.print("\t");
//    Serial.print(total2);                  // print sensor output 2
//    Serial.print("\t");
//    Serial.println(total3);                // print sensor output 3
    
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

