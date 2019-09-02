#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ESP8266WiFi.h"
#include <ArduinoJson.h>


const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";
//const char WEBSITE[] = "192.168.1.13";
//IPAddress server(192,168,1,13); // ipconfig

//const char* MY_SSID = "26SW_WIFI_2.4G";
//const char* MY_PWD =  "58543206";
//const char WEBSITE[] = "192.168.1.2";
String inStringHex = "";
int lastStringLength;



const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const uint16_t panasonicAddress = 0x4004;
uint32_t command;

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

double compiledHex(String msg,int len){ //เรียงค่าHEX
  int r,j;
  uint32_t hex = 0;
  char temp[]="";
        for (j = 0; msg[j] != '\0'; j++){  // แปลงเลขฐาน 16 เป็นฐาน 10
          len--;
          if( msg[j] >= '0' &&  msg[j] <= '9')
              r =  msg[j] - 48;
          else if( msg[j] >= 'a' &&  msg[j] <= 'f')
              r = msg[j] - 87;
           else if( msg[j] >= 'A' &&  msg[j] <= 'F')
                r =  msg[j] - 55;
          hex += r * pow(16,len);
          }
  return hex;
}



void setup() {
  Serial.begin(115200);
  
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("WIFI connected\n ");
  Serial.println("");
  
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
     Serial.println(" port to connect. ");
      //String msg = "ABCDEF";
  irsend.begin();
}

void loop() {
  //WiFiClient client;
 
  //String command = "0, 4494, 558, 574, 560, 1678, 584, 548, 558, 550, 584, 546, 532, 598, 562, 548, 584, 542, 582, 1660, 586, 542, 558, 1684, 556, 1702, 562, 1676";
  while (Serial.available() != 0){
    inStringHex = Serial.readString();
    lastStringLength = inStringHex.length() - 1;
    command = compiledHex(inStringHex,lastStringLength); //เปลี่ยน String เป็น Hex
    Serial.print("INPUT :");
    Serial.print(inStringHex);
    Serial.print("DEC :");
    Serial.println(command);
    Serial.print("Send Hex :" );
    Serial.println(command,HEX);
    //irsend.sendPanasonic(panasonicAddress,command);   //สั่งควบคุมต่าง ๆ  ตย.code 0x40BF8877
    //Serial.println(command);
    Serial.println(" ");  

    
//_____________________JSON HTTP___________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 
      JSONencoder["command"] = inStringHex;    //input String to Json
      char JSONmessageBuffer[300];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);
      HTTPClient http;
      http.begin("http://192.168.1.13:4000/control/api/jsonn");      //ปลายทางที่เราจะส่ง JSONไป
      http.addHeader("Content-Type", "application/json");  //Specify content-type header

  
//      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
//      String payload = http.getString();                                        //Get the response payload
//      Serial.print("httpCode :");
//      Serial.println(httpCode);   //Print HTTP return code
//      Serial.println(payload);    //Print request response payload
      http.POST(JSONmessageBuffer);
      http.getString(); 
      http.end();  //Close connection
    }else {
      Serial.println("Error in WiFi connection"); 
    }
  }
}
