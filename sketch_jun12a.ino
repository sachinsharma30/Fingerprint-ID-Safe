#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 6, 7, 8}; 
byte colPins[COLS] = {2, 3, 4}; 

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() 
{
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  char pass[6] = "123456";
  char userPass[6];
  for(int i=0;i<=5;i++)
  {
    char key = kpd.getKey(); 
    while(key == NO_KEY) 
    {
      key = kpd.getKey();
    }
    if (key != NO_KEY) 
    { 
      userPass[i] = key; 
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  
  boolean flag = true;
  for(int i = 0; i < 5; i++)
  {
    if(userPass[i]!=pass[i])
    {
      flag = false;
      break;
    }
  }
  
  if(flag)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.println("Correct Passcode");
   } else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.println("Incorrect Passcode");
  }
}
