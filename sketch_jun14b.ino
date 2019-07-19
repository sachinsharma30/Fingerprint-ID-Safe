#include <Keypad.h>
#include <Password.h>
 
String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
 
//initialize password to 1234
//you can use password.set(newPassword) to overwrite it
Password password = Password( "1234" );
 
byte maxPasswordLength = 6; 
byte currentPasswordLength = 0;
const byte ROWS = 4; // Four rows
const byte COLS = 3; // 3 columns
 
//Define the keymap
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
 
byte rowPins[ROWS] = {5, 6, 7, 8}; 
byte colPins[COLS] = {2, 3, 4}; 

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup(){
   Serial.begin(9600);
}
 
void loop(){
   char key = keypad.getKey();
   if (key != NO_KEY){
      delay(60); 
      switch (key){
      case '#': checkPassword(); break;
      case '*': resetPassword(); break;
      default: processNumberKey(key);
      }
   }
}
 
void processNumberKey(char key) {
   Serial.print(key);
   currentPasswordLength++;
   password.append(key);
   if (currentPasswordLength == maxPasswordLength) {
      checkPassword();
   } 
}

void checkPassword() {
   if (password.evaluate()){
      Serial.println(" OK.");
   } else {
      Serial.println(" Wrong passwowrd!");
   } 
   resetPassword();
}

void resetPassword() {
   password.reset(); 
   currentPasswordLength = 0; 
}
