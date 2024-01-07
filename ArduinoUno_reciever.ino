#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C.h>

short ambient;
#define PIN A0

LiquidCrystal_I2C lcd (0x27, 16,2);  //
int c = 0;

void  setup () {

  Serial.begin(9600);
  pinMode(A0,INPUT);
  ambient = analogRead(PIN);  //Surrounding light value 
  Serial.println("Value of ambient light is ");
  Serial.print(ambient);

   // Lcd initialization 
  lcd.init();
  // Turning on the backlight on LCD. 
  lcd.backlight();
  
  // Start message 
  lcd.print ("BabuSona");
  lcd.print(" 1.0");
  delay(5000);
  lcd.setCursor(0, 1);
  lcd.print("Laser now");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Decoded Text");
  
}

int j = 0;   //this will controll when to store data
String dedcode = "";  //This will recieve data in the form of 1010

void loop () {
  short input = analogRead(PIN);  //reading from the solar panel 
  short final = input - ambient;  //reading without surrounding value
  short outt;
  if(abs(final) > 15){
    outt=1;               //convert analogue to binary
  }else{
    outt=0;
  }

  if(outt ==0){
    j = 1;
  }
  if(dedcode.length()>50){
    j=0;
  }
  if (j==1){
    dedcode += String(outt);
    Serial.println(dedcode);
  }
  
  char outtp = "";
  String inputt = dedcode; // recieved data to decoder
  String inputString = "";

  for (int k = 0; k < inputt.length(); k++) {
    char incomingChar = inputt.charAt(k);

    if (k % 1 == 0) {
        inputString += incomingChar;     //here modulo by 1 because here 
    }                                    //we recive 1 bit at a time
                                         //(if repeated then modulo by 2 i.e 1100)
    if (inputString.length() == 8) {
      int decimalValue = strtol(inputString.c_str(), NULL, 2);
      outtp= char(decimalValue);
      Serial.println(outtp);             //when we recive 8 bits,convert it to charachter
      Serial.println(outtp);             //and prints to the display
      
      c+=1;
       if (c==15){
      lcd.clear();
      lcd.setCursor(0, 0);      //code to clear text when row is fully filled
      lcd.print("Decoded Text");
      c = 0;
    }
   // printing the value in the display
      lcd. setCursor (c, 1);
      lcd. print (outtp);
      delay(100);
      inputString = "";
      dedcode="";
      j=0;
    }
  }  
  delay (100);
}
