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
const String IP =  "http://192.168.1.10:4000";

//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";

const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.




#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;



IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void httpJSON(String buttonCode,String rawData,String buttonBuff,int buff){ 
//_____________________JSON HTTP______________________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<3000> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 
      
      JSONencoder["column"] = buttonCode;    //ชื่อคอลัม
      JSONencoder["value"] = rawData;  //ข้อมูลที่ส่งไป
      JSONencoder["column2"] = buttonBuff;    //ชื่อคอลัม
      JSONencoder["value2"] = buff;  //ข้อมูลที่ส่งไป
      
      char JSONmessageBuffer[3000];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);
      HTTPClient http;
      http.begin(IP + "/control/api/remote_ac");      //ปลายทางที่เราจะส่ง JSONไป
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




//void httpGetAndSendIR(String Data,int buffSize){
//  if (WiFi.status() == WL_CONNECTED) {
//    HTTPClient http;  //Object of class HTTPClient
//    String url = (IP + "/control/tv/" + Data) ; // คอลัม
////    Serial.print("url  ");Serial.println(url);
//    http.begin(url);
//    int httpCode = http.GET();
//                                                                
//    if(httpCode > 0){   //Check the returning code    
//    const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 3000;
//    DynamicJsonBuffer jsonBuffer(bufferSize);
//    JsonArray& JSONcoder = jsonBuffer.parseArray(http.getString());       // Parsing
//     
//     String jsonCommand = JSONcoder[0][Data]; // Command MySQL
//      //String jsonCommand = JSONcoder["tv_On"]; // Command MySQL
//      //int buffSize = JSONcoder["tv_buffOn"]; //Buffer Button tv_On
//    
//     
//      // Output to serial monitor
//     Serial.print("jsonCommand: ");Serial.println(jsonCommand);
//     
// //------------------ฟังก์ชั้น แปลงค่าString เป็น int  --------------------------------------------------------------------------------------------------
//     uint16_t command[buffSize];
//     toIntArray(jsonCommand,buffSize,command);   
//     //irsend.sendRaw(command,buffSize, 38); //IR SEND
//     
//    }
//     http.end();   //Close connection
//
//  }
//}
//
//
//
//
//void toIntArray(String str,int buffSize ,uint16_t* command){
//    int str_len = str.length()+1;
//    int arr[buffSize];
//    char toCovrChar[str_len] ;
//    str.toCharArray(toCovrChar,str_len); //เปลี่ยน String เป็น Char
//    char *p = strtok(toCovrChar , ",");
//    size_t index = 0; 
//    while( p != nullptr && index < buffSize){
//      arr[index++] = atoi(p);
//      p = strtok(NULL,",");
//    } 
//    Serial.print("command[");Serial.print(buffSize);Serial.print("] :");
//    command[buffSize]; //กดหมดจำนวนbuffer ให้กับ command
//    for(size_t i = 0; i < index; i++){
//      command[i] = (uint16_t)arr[i]; //ให้array แต่ละตัวของcommand เท่าarr[i]
//      Serial.print(command[i]);
//      if(i < index - 1)
//        Serial.print(", "); //โชว์ data ของ command แต่ละตัว
//    }
//}

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
//    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
//    WiFiManager wm;
//    wm.resetSettings();
//    bool res;
//    // res = wm.autoConnect(); // auto generated AP name from chipid
//    res = wm.autoConnect("SMART_HOME"); // เชื่อมต่อ wifi เพื่อนเข้าไป ตั้งค่าการเชื่อต่อ wifi
//    if(!res) {
//        Serial.println("Failed to connect");
//        // ESP.restart();
//    } 
//    else {
//        //if you get here you have connected to the WiFi    
//        Serial.println("connected...yeey :)");
//    }

  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);

  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.print("WIFI connected! , to IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  
    Serial.println("--------- DECODE AC REMOTE-------------");
    Serial.println("Enter ' 0 ' ON Button ");
    Serial.println("Enter ' + ' Temp+ Button ");
    Serial.println("Enter ' - ' Temp- Button ");
    Serial.println("Enter ' 8 ' Fan ▲ Button");
    Serial.println("Enter ' 2 ' Fan ▼ Button");
//    irsend.begin();  //เปิดpin ในการส่ง IR

//tv_Mute[99] :3460, 1754,  416, 424,  444, 1320,  416, 424,  446, 422,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  446, 424,  444, 1320,  418, 422,  446, 424,  444, 424,  446, 422,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 1322,  416, 424,  444, 422,  446, 1318,  418, 1320,  418, 422,  444, 424,  446, 422,  444, 1318,  418, 424,  444, 424,  444, 1320,  418, 1318,  418, 424,  444, 1320,  418


}



void loop() {
    if(irrecv.decode(&results)) {
      if(Serial.available()){
          char input = Serial.read();
//___________________________________________________TV REMOTE__________________________________________________
        
 /*----------------------------------Decode Tv remote  ' 0 ' ON Button-----------------------------------------*/       
         if( input == '0'){  
            Serial.println("You Select AC remote & Decoder Power Button ");  
            int air_powerBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_power = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_power[");Serial.print(air_powerBuff);Serial.print("] :");Serial.println(air_power);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            httpJSON( "air_power", air_power, "air_powerBuff", air_powerBuff );
          }
          
          else if(input == '+'){
            Serial.println("You Select AC remote & Decoder Power Button ");  
            int air_tempUpBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_tempUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_tempUp[");Serial.print(air_tempUpBuff);Serial.print("] :");Serial.println(air_tempUp);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            httpJSON( "air_tempUp", air_tempUp, "air_tempUpBuff", air_tempUpBuff );
          }
          else if(input == '-'){
            Serial.println("You Select AC remote & Decoder Power Button ");  
            int air_tempDownBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_tempDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_tempDown[");Serial.print(air_tempDownBuff);Serial.print("] :");Serial.println(air_tempDown);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            httpJSON( "air_tempDown", air_tempDown, "air_tempDownBuff", air_tempDownBuff );
          }
          else if(input == '8'){
            Serial.println("You Select AC remote & Decoder Power Button ");  
            int air_speedFanBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_speedFan = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_speedFan[");Serial.print(air_speedFanBuff);Serial.print("] :");Serial.println(air_speedFan);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            httpJSON( "air_speedFan", air_speedFan, "air_speedFanBuff", air_speedFanBuff );
          }
      }
   } Serial.println("Next Button Encoder ");   
}
