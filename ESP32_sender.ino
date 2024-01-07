#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
  pinMode(12,OUTPUT);
 Serial.begin(9600);
 SerialBT.begin("ESP32test"); //Bluetooth device name
 Serial.println("The device has started, now you can pair it with bluetooth!");
 
}
 
// Function to convert text to binary 
String textToBinary(String text) { 
  String binaryResult = ""; 
 
  for (size_t i = 0; i < text.length(); ++i) { 
    char c = text.charAt(i); 
 
    for (int j = 7; j >= 0; --j) { 
      binaryResult += ((c >> j) & 1) ? '1' : '0'; 
    } 
    binaryResult += "111"; // Add 1's between each byte to make delay in decoding next binary 
  } 
 
  return binaryResult; 
}

void loop() { 
  digitalWrite(12,HIGH);
  if (SerialBT.available() > 0) { 
    String inputText = SerialBT.readStringUntil('\n'); // Read the input text until newline character 
 
    // Remove trailing newline characters 
    inputText.trim(); 
 
    // Display the original text 
    Serial.print("Original Text: "); 
    Serial.println(inputText); 
 
    // Convert the text to binary and display 
    String binaryRepresentation = textToBinary(inputText); 
    Serial.print("Binary Representation: "); 
    Serial.println(binaryRepresentation); 
    String abcd = binaryRepresentation; 
    for (size_t i = 0; i < abcd.length(); ++i) { 
      char c = abcd.charAt(i); 
      if (c == '1'){ 
        digitalWrite(12, HIGH); 
        delay(100); 
      }else{ 
        digitalWrite(12,LOW); 
        delay(100); 
      } 
  } 
} 
}
 
