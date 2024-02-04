    // the number of the pushbutton pin

int cuckooRelay = 7;
//==================================MODEL IDLE STATE===================================
int idleState = 0;
const unsigned long noButtonPushSampleIntervalMs = 1000;

unsigned long longCountMax = 10; //500*25 = 12500= 12.5 seconds 600x1000 = 10 minutes

int longIdleCount = 0;
long timer = 0;
unsigned long idlePreviousMillis = 0;

long idleStartTime = 0;

void resetCounter()  // set counter to 0
{
  Serial.println("button not pushed start counter");
  longIdleCount = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(cuckooRelay,OUTPUT);
  digitalWrite(cuckooRelay,LOW);
}

void loop()
{
  
  // put your main code here, to run repeatedly:

  // idle state if the model is inactive to avoid sticking execute the following every N minutes
  if (idleState == 0) // if button not pushed
  {
    Serial.println("start counter");
    Serial.println("human override countdown:");
    idleState = 1;
  }
  else if (idleState == 1)
  {
    // delay between current time and last time
    if (millis() - idlePreviousMillis >= noButtonPushSampleIntervalMs) // check between the last time and the current time difference is greater than the interval
    {
      idlePreviousMillis = millis();
      longIdleCount++;  //  start counting
      Serial.println(longIdleCount);

      if (longIdleCount >= longCountMax) // yes the count on the timer has exceeded 12 seconds
      {
        
        digitalWrite(cuckooRelay, HIGH);
        timer = millis();
        idleState = 2;
      }
    }
  }
  else if(idleState == 2 && millis()>= timer + 3 * 1000)
  {
    resetCounter();
    digitalWrite(cuckooRelay, LOW);
    idleState = 0;
  }
 
}
