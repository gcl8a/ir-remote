void setup()
{
  Serial.begin(115200);
  Serial.println("Hi");

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

  TCCR2A |= 0x40; //turn on toggle on compare match

  attachInterrupt(digitalPinToInterrupt(2), InterruptHandlerPin2, CHANGE);

  sei();
}

volatile uint8_t dataReady = 0;

volatile uint32_t startTime = 0;
volatile uint32_t endTime = 0;

void loop()
{
  if(dataReady)
  {
    noInterrupts();
    uint32_t deltaTime = endTime - startTime;
    interrupts();
    
    Serial.print(deltaTime); 
    Serial.print('\n');

    dataReady = 0;
  }
}

void InterruptHandlerPin2(void)
{
  if(digitalRead(2) == HIGH) //blocking
  {
    startTime = millis();
  }
  else
  {
    endTime = millis();
    dataReady = 1;
  }
}

