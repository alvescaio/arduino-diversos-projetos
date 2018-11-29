void acendeLeds(int temp){
  if(temp == 1){
    digitalWrite(led_pin[0], HIGH);
    digitalWrite(led_pin[1], HIGH);
    digitalWrite(led_pin[2], HIGH);
  }else if(temp == 0){
    digitalWrite(led_pin[0], LOW);
    digitalWrite(led_pin[1], LOW);
    digitalWrite(led_pin[2], LOW);
  }else if(temp > 1){
    digitalWrite(led_pin[0], HIGH);
    digitalWrite(led_pin[1], HIGH);
    digitalWrite(led_pin[2], HIGH);
    delay(temp);
    digitalWrite(led_pin[0], LOW);
    digitalWrite(led_pin[1], LOW);
    digitalWrite(led_pin[2], LOW);
  }
}

