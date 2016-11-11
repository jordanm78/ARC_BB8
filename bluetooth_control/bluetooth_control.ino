#include <SoftwareSerial.h>  
#include <Servo.h>
#define RxD 7
#define TxD 6

Servo servoI;    // Pin 4 
Servo servoD;    // Pin 3
String command = "";
String parsedString = "";



  
SoftwareSerial BlueToothSerial(RxD,TxD);
char flag=1;
void setup()
{
   Serial.begin(38400);     
   BlueToothSerial.begin(38400); 
   delay(500);

}
 
void loop()
{
//command = readBluetoothData();
command = readSerialData();
Serial.println(command);
//Serial.println("Hello World!");
parsedString = getValue(command, ':', 0);
//parsedString = "Hello World!";
Serial.println(parsedString);
delay(1000);
 
 
  
}




String readBluetoothData()
{
  char BluetoothCharacter;
if(BlueToothSerial.available())
    {
      command = "";
      while(BlueToothSerial.available())
      {      
        BluetoothCharacter = char(BlueToothSerial.read());
        if(BluetoothCharacter == 10) //ascii 10 is a line feed character command from phone must have a return
        {
         //Serial.println("Command done!");
  
        }
        else
        {
        command += BluetoothCharacter;
        //Serial.print(BluetoothCharacter);
        }
      } 
    }
 Serial.println(command);
 delay(1000);
 return command;    
}


String readSerialData()
{
  char Character;
  String serialCommand;
 serialCommand = "";
 if(Serial.available())
    {
      while(Serial.available())
      {      
        Character = char(Serial.read());
        if(Character == 10) //ascii 10 is a line feed character command from phone must have a return
        {
          //Serial.println("Command done!");
  
        }
        else
        {
        serialCommand += Character;
        Serial.print(Character);
        }
      } 
    }
  else
{
//Serial.println("No Serial Data to Read");
}
return serialCommand;
}


String getValue(String data, char separator, int index)
{
  Serial.println("I am looking through your string");
  Serial.print("Your string is ");
  Serial.println(data);
  Serial.print("I am looking for ");
  Serial.println(separator);
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  Serial.print(data.charAt(i));
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  Serial.println("I found it!");
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
