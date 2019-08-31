// IR send----------------------
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ESP8266WiFi.h"

// IR recv----------------------
#include <IRrecv.h>
#include <IRac.h>
#include <IRutils.h>
const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;






const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";
const char WEBSITE[] = "192.168.1.16";

//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";
//const char WEBSITE[] = "192.168.1.116";
String inStringHex = "";
int lastStringLength;

//IR  recv
#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

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

  #if defined(ESP8266)
    Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
  #else  // ESP8266
    Serial.begin(kBaudRate, SERIAL_8N1);
  #endif  // ESP8266
    while (!Serial)  // Wait for the serial connection to be establised.
      delay(50);
  #if DECODE_HASH
    irrecv.setUnknownThreshold(kMinUnknownSize);
  #endif                  // DECODE_HASH
    irrecv.enableIRIn();  // Start the receiver
    
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
     Serial.println(" port to connect. ");
      //String msg = "ABCDEF";
  irsend.begin();
}

void loop() {
  WiFiClient client;
 
  
    if (irrecv.decode(&results)) {

      //IR recv ---------------------------
      int bufferSize = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
    Serial.print("RawLength :");
    Serial.println(bufferSize);  //จำนวนทั้งหมดของ Decode


 //rawData------------------------------------------------------------------
     Serial.print("&results :"); 
    Serial.println(resultToSourceCode(&results));
    Serial.println();    // Blank line between entries
    yield();             // Feed the WDT (again)

  //Connec to Node js

  
//    inStringHex = Serial.readString();
//    lastStringLength = inStringHex.length() - 1;
//    command = compiledHex(inStringHex,lastStringLength); //เปลี่ยน String เป็น Hex
//    Serial.print("INPUT :");
//    Serial.print(inStringHex);
//    Serial.print("DEC :");
//    Serial.println(command);
//    Serial.print("Send Hex :" );
//    Serial.println(command,HEX);
//    //irsend.sendPanasonic(panasonicAddress,command);   //สั่งควบคุมต่าง ๆ  ตย.code 0x40BF8877
//    //Serial.println(command);
//    Serial.println(" ");
    
    //---------------------------------------------------------------------

        if (client.connect(WEBSITE, 4000)){
        Serial.println(inStringHex);
        Serial.println((String)inStringHex);
//        String request =  String(command,HEX); //แปลงค่าจาก intฐาน16 เป็น string ,HEX
        String request =  (String)resultToSourceCode(&results);
        Serial.println("req :");
        Serial.println(request);
//        client.print("POST /control/api/temp?temp=" + request); //ส่งค่า request ผ่าน post
        client.print("POST /control/api/temp?temp=" + (uint64ToString(getCorrectedRawLength(&results), 10)));
        
        client.println(" HTTP/1.1"); 
        client.print("Host: ");
        client.println(WEBSITE);
        client.println("User-Agent: ESP8266/1.0");
        client.println("Connection: close");
        client.println();
       } else  Serial.println(client.connect(WEBSITE, 80));
  }
//delay(3000);
}
