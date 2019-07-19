#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {5, 6, 7, 8}; 
byte colPins[COLS] = {2, 3, 4}; 
char pass = '6';

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
  
void loop(){

  char customKey = customKeypad.getKey();
  if(customKey == pass)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
    digitalWrite(LED_BUILTIN, LOW);
  }
  /*char customKey[1];

  for(int i = 0; i < 1; i++)
  {
    char ch = customKeypad.getKey();
    
    while(ch == NO_KEY) 
    {
      ch = customKeypad.getKey();
    }
    
    if(customKey[i] != NO_KEY)
    {
      customKey[i] = ch;
      Serial.println(customKey[i]);
    }
  }

  boolean flag = true;
  for(int i = 0; i < 1; i++)
  {
    if(customKey[i]!=pass[i]) 
    {
      flag = false;
      break;
    }
  }
  
  if(flag)
  {
     digitalWrite(LED_BUILTIN, HIGH);
     delay(5000);
     digitalWrite(LED_BUILTIN, LOW);
  }*/
}

 
