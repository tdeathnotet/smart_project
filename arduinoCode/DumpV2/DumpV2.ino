#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <IRutils.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRsend.h>

const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";

//const char* MY_SSID = "26SW_WIFI_2.4G";
//const char* MY_PWD =  "58543206";

const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.




//void convertStrtoArr();
int toIntArray();
void httpJSON();


#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;



IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results




void setup() {
  Serial.begin(kBaudRate);
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
  
  irsend.begin();
}



void loop() {

  if (irrecv.decode(&results)) {
   //rawLengthData----------------------------------------------------------------
    Serial.println("");
    int bufferSize = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
    uint16_t command[bufferSize];

 //rawData------------------------------------------------------------------
     //Serial.print("&results :"); 
     String rawData = resultToSourceCode(&results);

     Serial.print("rawData[");Serial.print(bufferSize);Serial.print("] :");
     Serial.println(rawData);
     Serial.print("sendJSON[");Serial.print(bufferSize);Serial.print("] :");
     httpJSON(rawData);  //ส่งJSON ไปยัง http
     toIntArray(rawData,bufferSize,command);  //ฟังก์ชั้น Char* to Int Array  

     //irsend.sendRaw(command,bufferSize, 38);  // Send a raw data capture at 38kHz.
  }
    
}

int toIntArray(String str,int buffSize ,uint16_t* command){
    int str_len = str.length()+1;
    int arr[buffSize];
    char toCovrChar[str_len] ;
    str.toCharArray(toCovrChar,str_len); //เปลี่ยน String เป็น Char
    char *p = strtok(toCovrChar , ",");
    size_t index = 0; 
    while( p != nullptr && index < buffSize){
      arr[index++] = atoi(p);
      p = strtok(NULL,",");
    } 
    //Serial.print("command[");Serial.print(buffSize);Serial.print("] :");
    command[buffSize]; //กดหมดจำนวนbuffer ให้กับ command
    for(size_t i = 0; i < index; i++){
      command[i] = (uint16_t)arr[i]; //ให้array แต่ละตัวของcommand เท่าarr[i]
      Serial.print(command[i]);
      if(i < index - 1)
        Serial.print(", "); //โชว์ data ของ command แต่ละตัว
    }
}
void httpJSON(String rawData){
      //_____________________JSON HTTP___________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<3000> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 
      JSONencoder["ON"] = rawData;    //input String to Json
      JSONencoder["volUP"] = rawData;   
      char JSONmessageBuffer[3000];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);
      HTTPClient http;
      http.begin("http://192.168.1.13:4000/control/api/jsonn");      //ปลายทางที่เราจะส่ง JSONไป
      http.addHeader("Content-Type", "application/json");  //Specify content-type header

  
      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
      String payload = http.getString();                                        //Get the response payload
      Serial.print("httpCode :");
      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
//      http.POST(JSONmessageBuffer);
//      http.getString(); 
      http.end();  //Close connection
    }else {
      Serial.println("Error in WiFi connection"); 
    }
}
