
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
