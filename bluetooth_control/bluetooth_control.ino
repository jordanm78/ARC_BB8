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
if(command!="")
{
  Serial.println(command);
}
parsedString = getValue(command, ':', 0);
if(parsedString !=0)
{
  Serial.println(parsedString);
}
parsedString = getValue(command, ':', 1);
if(parsedString !=0)
{
  Serial.println(parsedString);
}
 
 
  
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

  
        }
        else
        {
        command += BluetoothCharacter;
        }
      } 
    }
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
  
        }
        else
        {
        serialCommand += Character;
        delay(1); //Delay 1 millisecond to allow more serial data to arrive.
        }
      } 
    }
  else
{

}
return serialCommand;
}


String getValue(String data, char separator, int index)
{

  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
