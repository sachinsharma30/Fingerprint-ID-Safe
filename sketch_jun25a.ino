
/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor
fp:green2,white3,red5v,blackgnd
servo: red5v, blackgnd, yellow8
  Designed specifically to work with the Adafruit BM085 Breakout 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Keypad.h>
#include <Servo.h>
#include <Adafruit_Fingerprint.h>


// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(11, 12);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Servo myFServo;
char* password = "2019";
int position = 0;
const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Servo myKServo;
boolean flag = false;

byte rowPins[ROWS] = {5, 6, 7, 8}; 
byte colPins[COLS] = {2, 3, 4};    

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()  
{
  Serial.begin(9600);
  setLocked(true);
  myKServo.attach(9);
  //while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  myFServo.attach(10);
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  flag = checkPass();
}

void loop()                     // run over and over again
{  
  if(flag)
  {
    //Serial.println("HIHIHIHIHIHIHI");
    getFingerprintIDez();
    //delay(5000);
  }
  else
    Serial.println("incorrect");
    
}

boolean checkPass()
{
  while(true)
  {
    char key = keypad.getKey();
    if (key != NO_KEY){
      Serial.println(key);
    }
    
    if (key == '*' || key == '#')
    {
      position = 0;
      setLocked(true);
      myKServo.write(90);
    }
  
    if (key == password[position])
    {
      position++;  
    }
    
    if (position == 4)
    {
      setLocked(false);
      return true;
    }
  }
}

void setLocked(int locked)
{
  if (locked)
  {
    myKServo.write(90);
  }
  else
  {
    myKServo.write(15);    
  }
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  myFServo.write(15);
  //delay(20000);
 // myServo.write(-45);
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  Serial.println("first");
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  Serial.println("second");

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  Serial.println("third");
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  myFServo.write(15);
  //delay(20000);
 // myServo.write(-45);
  return finger.fingerID; 
}
