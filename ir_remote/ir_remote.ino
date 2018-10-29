void setup() 
{
  Serial.begin(115200);
  cli();
  
  //CTC mode with OC2A toggle on CM (Arduino pin 11)
  //TCCR2A = 0b0100 0010
  TCCR2A = 0x42;

  //pre-scaler of 1
  TCCR2B = 0x01;

  //freq = 16e6 / (2 * (209 + 1)) = 38.10 kHz
  //freq = 16e6 / (2 * (210 + 1)) = 37.91 kHz
  //freq = 16e6 / (2 * (142 + 1)) = 55.94 kHz
  //freq = 16e6 / (2 * (141 + 1)) = 56.34 kHz
  OCR2A = 209;

  //don't forget to make 11 an OUTPUT
  DDRB |= (1 << PB3);

  sei();
  
  TCCR2A |= 0x40; //turn on toggle on compare match
}

void loop() 
{
  Serial.println(digitalRead(2)); //reads the IR sensor on pin 7 and writes its value to the serial monitor
  delay(10);
}

