#include <Arduino.h>
//#include <WiFiManager.h> 
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
const String IP =  "http://192.168.1.10:4000";  //ip *เครื่อง *Server
HTTPClient http;

//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";

const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;


const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

int check = 0;



#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;


IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void httpJSON(String Data,String rawData){ 
//_____________________JSON HTTP______________________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<3000> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 

      JSONencoder["column"] = Data;    //ชื่อคอลัม
      JSONencoder["value"] = rawData;  //ข้อมูลที่ส่งไป

      
      char JSONmessageBuffer[3000];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      //Serial.println(JSONmessageBuffer);
      http.begin(IP + "/control/api/json");      //ปลายทางที่เราจะส่ง JSONไป
      http.addHeader("Content-Type", "application/json");  //Specify content-type header

      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
      String payload = http.getString(); //Get the response payload
//      Serial.print("httpCode :");
//      Serial.println(payload);    //Print request response payload
//      Serial.println(httpCode);   //Print HTTP return code
      http.end();  //Close connection  
    }else {
      Serial.println("Error in WiFi connection"); 
    }   
}




void httpGetAndSendIR(String Data){
    String url = (IP + "/control/tv/" + Data) ; // คอลัม
//    Serial.print("url  ");Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();                                                       
    if(httpCode > 0){   //Check the returning code    
    const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 3000;
    DynamicJsonBuffer jsonBuffer(bufferSize);
    JsonArray& JSONcoder = jsonBuffer.parseArray(http.getString());       // Parsing
     
     String jsonCommand = JSONcoder[0][Data]; // Command MySQL
     int buffSize = JSONcoder[0][Data+"Buff"]; // Command MySQL
      // Output to serial monitor
     Serial.print("command[");Serial.print(buffSize);Serial.print("] :"); Serial.println(jsonCommand);
     
 //------------------ฟังก์ชั้น แปลงค่าString เป็น int  --------------------------------------------------------------------------------------------------
     uint16_t command[buffSize];
     toIntArray(jsonCommand,buffSize,command);   
     irsend.sendRaw(command,buffSize, 38); //IR SEND 
    }
     http.end();   //Close connection
}


void httpGet(){
  
    http.begin(IP + "/control/remote_tv/button");
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
     //Serial.print("jsonCommand: ");Serial.println(http.getString());
//     String On = http.getString();
//     Serial.println("jsonCommand: " + On);
  
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      String button = root["Button"];   //Check JSON
//      String button = root["Button"];
      //Serial.println(http.GET());
      Serial.println("jsonCommand: " + button);
      
        if(button == "tv_On" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Up" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Down" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Left" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Right" ){
          httpGetAndSendIR(button);
        }
        else if(button == "tv_OK" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_volUp" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_VolDown" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_CHUp" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_CHDown" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Return" ){
          httpGetAndSendIR(button);
        }
        if(button == "tv_Mute" ){
          httpGetAndSendIR(button);
        }  
    jsonBuffer.clear();
   }
     http.end();   //Close connection
}


void toIntArray(String str,int buffSize ,uint16_t* command){
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
//    Serial.print("command[");Serial.print(buffSize);Serial.print("] :");
    command[buffSize]; //กดหมดจำนวนbuffer ให้กับ command
    for(size_t i = 0; i < index; i++){
      command[i] = (uint16_t)arr[i]; //ให้array แต่ละตัวของcommand เท่าarr[i]
//      Serial.print(command[i]); //โชว์ data ของ command แต่ละตัว
//      if(i < index - 1)
//        Serial.print(", "); 
    }
}


void setup() {
//______________________________Basic Setting__________________________________________    
  Serial.begin(115200);
  Serial.printf("\nIRrecvDumpV2 is now running and waiting for IR input on Pin "
                  "%d\n", kRecvPin);

//______________________________เปิดขา IR recv__________________________________________                 
  #if DECODE_HASH
    // Ignore messages with less than minimum on or off pulses.
    irrecv.setUnknownThreshold(kMinUnknownSize);
  #endif                  // DECODE_HASH
    irrecv.enableIRIn();  // Start the receiver

//_____________________________Ceonnect Wifi____________________________________________
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);

  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.print("WIFI connected! , to IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  
    Serial.println("--------- DECOD TV REMOTE-------------");
    Serial.println("Enter ' 0 ' ON Button ");
    Serial.println("Enter ' 5 ' OK Button");
    Serial.println("Enter ' 8 ' ▲ Button");
    Serial.println("Enter ' 4 ' ◀ Button");
    Serial.println("Enter ' 6 ' ▶ Button");
    Serial.println("Enter ' 2 ' ▼ Button");
    Serial.println("Enter ' + ' Vol+ Button ");
    Serial.println("Enter ' - ' vol- Button ");
    Serial.println("Enter ' 9 ' CH ▲ Button");
    Serial.println("Enter ' 3 ' CH ▼ Button");
    Serial.println("Enter ' 1 ' ↺Return,Exit Button");
    Serial.println("Enter ' 7 ' Mute Button");  
    irsend.begin();  //เปิดpin ในการส่ง IR
}

void loop(){
    httpGet();

}
