#include <Arduino.h>
//#include <WiFiManager.h> 
#include <IRremoteESP8266.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>  //5.08
#include <IRutils.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRsend.h>


//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[50] = "http://192.168.1.11:4000";  //หาจาก cmd  #ipconfig 
String IP = "";
const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";
HTTPClient http;

//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";

const uint16_t kRecvPin = D5;  //ขารับสัญญาณ IR
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint16_t kIrLed = D6;  // ขาส่งสัญญาณ IR
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.




#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;


IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results


//flag for saving data
bool shouldSaveConfig = false;
//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


void getAndSendTV(String Data){
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
     Serial.print("Button :"); Serial.println(Data);
     Serial.print("command[");Serial.print(buffSize);Serial.print("] :"); Serial.println(jsonCommand);
     
 //------------------ฟังก์ชั้น แปลงค่าString เป็น int  --------------------------------------------------------------------------------------------------
     uint16_t command[buffSize];
     toIntArray(jsonCommand,buffSize,command);   
     irsend.sendRaw(command,buffSize, 38); //IR SEND 
    }
     http.end();   //Close connection
}

void getAndSendAC(String Data){
    String url = (IP + "/control/ac/" + Data) ; // คอลัม
//    Serial.print("url  ");Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();                                                       
    if(httpCode > 0){   //Check the returning code  

//      const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 3500;
//      DynamicJsonBuffer jsonBuffer(bufferSize);

    const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 3000;
    DynamicJsonBuffer jsonBuffer(capacity);

    
    JsonArray& JSONcoder = jsonBuffer.parseArray(http.getString());
    //JsonArray& root = jsonBuffer.parseArray(http.getString());

     String jsonCommand = JSONcoder[0][Data]; // Command MySQL
     int buffSize = JSONcoder[0][Data+"Buff"]; // Command MySQL
      // Output to serial monitor
     Serial.print("Button :"); Serial.println(Data);
     Serial.print("command[");Serial.print(buffSize);Serial.print("] :"); Serial.println(jsonCommand);
     
 //------------------ฟังก์ชั้น แปลงค่าString เป็น int  --------------------------------------------------------------------------------------------------
     uint16_t command[buffSize];
     toIntArray(jsonCommand,buffSize,command);   
     irsend.sendRaw(command,buffSize, 38); //IR SEND 
      
     jsonBuffer.clear();
    }
     http.end();   //Close connection
}


void httpGet(){
  
    http.begin(IP + "/control/remote_on/button");
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
      Serial.println(" . ");
 //____________________รับปุ่มTV_______________________________________     
        if(button == "tv_On" ){
          getAndSendTV(button);
        }
        if(button == "tv_Up" ){
          getAndSendTV(button);
        }
        if(button == "tv_Down" ){
          getAndSendTV(button);
        }
        if(button == "tv_Left" ){
          getAndSendTV(button);
        }
        if(button == "tv_Right" ){
          getAndSendTV(button);
        }
        if(button == "tv_OK" ){
          getAndSendTV(button);
        }
        if(button == "tv_VolUp" ){
          getAndSendTV(button);
        }
        if(button == "tv_VolDown" ){
          getAndSendTV(button);
        }
        if(button == "tv_CHUp" ){
          getAndSendTV(button);
        }
        if(button == "tv_CHDown" ){
          getAndSendTV(button);
        }
        if(button == "tv_Return" ){
          getAndSendTV(button);
        }
        if(button == "tv_Mute" ){
          getAndSendTV(button);
        }
//____________________รับปุ่ม AC _______________________________________ 
        if(button =="air_power"){ 
          getAndSendAC(button);
        }
        if(button =="air_speedFan"){ 
          getAndSendAC(button);
        }
        if(button =="air_tempUp"){ 
          getAndSendAC(button);
        }
        if(button =="air_tempDown"){ 
          getAndSendAC(button);
        }
        if(button =="air_swing"){ 
          getAndSendAC(button);
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


void decodeToSQL(String buttonCode,String rawData,String buttonBuff,int buff){ 
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

      http.begin(IP + "/control/api/remote_tv");      //ปลายทางที่เราจะส่ง JSONไป
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


//__________________api รหัส ac to SQL_____________________________________________________________________________


void decode_airToSQL(String buttonCode,String rawData,String buttonBuff,int buff){ 
//_____________________JSON HTTP______________________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<3500> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 
      
      JSONencoder["column"] = buttonCode;    //ชื่อคอลัม
      JSONencoder["value"] = rawData;  //ข้อมูลที่ส่งไป
      JSONencoder["column2"] = buttonBuff;    //ชื่อคอลัม
      JSONencoder["value2"] = buff;  //ข้อมูลที่ส่งไป
      
      char JSONmessageBuffer[3500];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);

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

void decoder_tvRemote(){
    http.begin(IP + "/control/remote/decode/tv_button");
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
     //Serial.print("jsonCommand: ");Serial.println(http.getString());
//     String On = http.getString();
//     Serial.println("jsonCommand: " + On);
  
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      String button = root["Button"];   //Check JSON
      String Status = root["Status"];
      //Serial.println(http.GET());
      Serial.println("jsonbutton :" + button);
      Serial.println("Status :" + Status);

 //______________________ เช็คว่ามีการรับค่าจากรีโมตไหม_______________________________________________________________     
       

  /*----------------------------------Decode Tv remote  On Button-----------------------------------------*/  
          if(Status == "1" && button == "tv_On"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int buffOn = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            
            String tv_On = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("tv_On[");Serial.print(buffOn);Serial.print("] :");Serial.println(tv_On);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decodeToSQL(button,tv_On, "tv_OnBuff" ,buffOn);
        }
  /*----------------------------------Decode Tv remote  ' + ' vol+ Button-----------------------------------------*/ 
         if(Status == "1" && button == "tv_VolUp"){   
            Serial.println("You Select TV remote & Decoder Vol+ Button");
            int buffVolUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_VolUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_volUp[");Serial.print(buffVolUp);Serial.print("] :");Serial.println(tv_VolUp);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL( "tv_VolUp", tv_VolUp, "tv_VolUpBuff", buffVolUp );
          } 
  /*----------------------------------Decode Tv remote  ' - ' vol- Button-----------------------------------------*/     
           if( Status == "1" && button == "tv_VolDown"){   
            Serial.println("You Select TV remote & Decoder vol- Button");
            int buffVolDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_VolDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_volDown[");Serial.print(buffVolDown);Serial.print("] :");Serial.println(tv_VolDown);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL( "tv_VolDown", tv_VolDown, "tv_VolDownBuff", buffVolDown );
          }
            
/*----------------------------------Decode Tv remote  ' 5 ' OK Button -----------------------------------------*/ 
           if( Status == "1" && button == "tv_OK"){   
            Serial.println("You Select TV remote & Decoder OK Button");
            int buffOK = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_OK = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_OK[");Serial.print(buffOK);Serial.print("] :");Serial.println(tv_OK);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_OK",tv_OK,"tv_OKBuff",buffOK);
          }  
/*----------------------------------Decode Tv remote  ' 8 ' ▲ Button-----------------------------------------*/
           if( Status == "1" && button == "tv_Up" ){   
            Serial.println("You Select TV remote & Decoder ▲ Button");
            int buffUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Up = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Up[");Serial.print(buffUp);Serial.print("] :");Serial.println(tv_Up);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Up",tv_Up,"tv_UpBuff",buffUp);
          }   
/*----------------------------------Decode Tv remote  ' 2 ' ▼ Button-----------------------------------------*/ 
           if( Status == "1" && button == "tv_Down" ){   
            Serial.println("You Select TV remote & Decoder ▼ Button");
            int buffDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Down = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Down[");Serial.print(buffDown);Serial.print("] :");Serial.println(tv_Down);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Down",tv_Down,"tv_DownBuff",buffDown);  
          } 
/*----------------------------------Decode Tv remote  ' 4 ' ◀ Button-----------------------------------------*/
           if( Status == "1" && button == "tv_Left" ){   
            Serial.println("You Select TV remote & Decoder ◀ Button");
            int buffLeft = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Left = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Left[");Serial.print(buffLeft);Serial.print("] :");Serial.println(tv_Left);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Left",tv_Left,"tv_LeftBuff",buffLeft);    
          } 
/*----------------------------------Decode Tv remote  ' 6 ' ▶ Button-----------------------------------------*/ 
           if( Status == "1" && button == "tv_Right"){   
            Serial.println("You Select TV remote & Decoder ▶ Button");
            int buffRight = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Right = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Right[");Serial.print(buffRight);Serial.print("] :");Serial.println(tv_Right);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Right",tv_Right,"tv_RightBuff",buffRight); 
          }
/*----------------------------------Decode Tv remote  ' 9 ' CH ▲ Button-----------------------------------------*/
           if( Status == "1" && button == "tv_CHUp"){   
            Serial.println("You Select TV remote & Decoder CH ▲ Button");
            int buffCHUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHUp[");Serial.print(buffCHUp);Serial.print("] :");Serial.println(tv_CHUp);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_CHUp",tv_CHUp,"tv_CHUpBuff",buffCHUp);
          }
/*----------------------------------Decode Tv remote  ' 3 ' CH ▼ Button-----------------------------------------*/ 
           if( Status == "1" && button == "tv_CHDown"){   
            Serial.println("You Select TV remote & Decoder CH ▼ Button");
            int buffCHDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHDown[");Serial.print(buffCHDown);Serial.print("] :");Serial.println(tv_CHDown);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_CHDown",tv_CHDown,"tv_CHDownBuff",buffCHDown); 
          }
/*----------------------------------Decode Tv remote  ' 1 ' ↺Return,Exit Button-----------------------------------------*/ 
           if(  Status == "1" && button == "tv_Return" ){   
            Serial.println("You Select TV remote & Decoder ↺Return,Exit Button");
            int buffReturn = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Return = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Return[");Serial.print(buffReturn);Serial.print("] :");Serial.println(tv_Return);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Return",tv_Return,"tv_ReturnBuff",buffReturn);
          }
/*----------------------------------Decode Tv remote  ' 7 ' Mute Button-----------------------------------------*/  
            if( Status == "1" && button == "tv_Mute" ){   
            Serial.println("You Select TV remote & Decoder Mute Button");
            int buffMute = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Mute = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Mute[");Serial.print(buffMute);Serial.print("] :");Serial.println(tv_Mute);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Mute",tv_Mute,"tv_MuteBuff",buffMute);    
          }    
    jsonBuffer.clear();
   }
     http.end();   //Close connection
}

//__________________________________________DECODE รีโมตแอร์___________________________________________________________
void decoder_acRemote(){
    http.begin(IP + "/control/remote/decode/ac_button");
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
     //Serial.print("jsonCommand: ");Serial.println(http.getString());
//     String On = http.getString();
//     Serial.println("jsonCommand: " + On);
  
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      String button = root["Button"];   //Check JSON
      String Status = root["Status"];
      //Serial.println(http.GET());
      Serial.println("jsonbutton :" + button);
      Serial.println("Status :" + Status);

 //______________________ เช็คว่ามีการรับค่าจากรีโมตไหม_______________________________________________________________     
 
  /*----------------------------------Decode AC remote  Power Button-----------------------------------------*/  
          if(Status == "1" && button == "air_power"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int air_powerBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_power = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_power[");Serial.print(air_powerBuff);Serial.print("] :");Serial.println(air_power);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decode_airToSQL(button,air_power, "air_powerBuff" ,air_powerBuff);
          }
          if(Status == "1" && button == "air_tempUp"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int air_tempUpBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_tempUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_tempUp[");Serial.print(air_tempUpBuff);Serial.print("] :");Serial.println(air_tempUp);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decode_airToSQL(button,air_tempUp, "air_tempUpBuff" ,air_tempUpBuff);
          }
          if(Status == "1" && button == "air_tempDown"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int air_tempDownBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_tempDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_tempDown[");Serial.print(air_tempDownBuff);Serial.print("] :");Serial.println(air_tempDown);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decode_airToSQL(button,air_tempDown, "air_tempDownBuff" ,air_tempDownBuff);
          }
          if(Status == "1" && button == "air_speedFan"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int air_speedFanBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_speedFan = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_speedFan[");Serial.print(air_speedFanBuff);Serial.print("] :");Serial.println(air_speedFan);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decode_airToSQL(button, air_speedFan, "air_speedFanBuff" ,air_speedFanBuff);
          }
          if(Status == "1" && button == "air_swing"){
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int air_swingBuff = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String air_swing = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
             // uint16_t command[bufferSize];
            Serial.print("air_swing[");Serial.print(air_swingBuff);Serial.print("] :");Serial.println(air_swing);
            Serial.println("Decoder Success!!"); Serial.println(""); 
            //httpJSON( "tv_On", tv_On, "tv_OnBuff", buffOn );
            decode_airToSQL(button, air_swing, "air_swingBuff" ,air_swingBuff);
          }
    jsonBuffer.clear();
   }
     http.end();   //Close connection
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
    WiFiManagerParameter custom_mqtt_server("server", "Server address", mqtt_server, 40);
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //set config save notify callback
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    //add all your parameters here
    wifiManager.addParameter(&custom_mqtt_server);

    
    //***_____________reset settings - for testing_____________________**
    wifiManager.resetSettings();  //อย่าใส่ commnent ออก เพราะจะรีเซ็ตทุกครั้ง ...
  
    if (!wifiManager.autoConnect("SMART_HOME", "admin")) {   //ssid & password เข้าตั้งค่า ip และหาข้อมูล
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("Connected!......  :)");
    //read updated parameters
    strcpy(mqtt_server, custom_mqtt_server.getValue());
    IP = String(mqtt_server); 
    Serial.println("local ip");
    Serial.println(WiFi.localIP());

    
    irsend.begin();  //เปิดpin ในการส่ง IR

}

void loop() {
    if(irrecv.decode(&results)){
      decoder_tvRemote();  //เข้าฟังชั่นเช็คค่าว่ารับปุ่มทีวีไหนมา decode
      decoder_acRemote(); //เข้าฟังชั่นเช็คค่าว่ารับปุ่มแอร์ไหนมา decode
      Serial.println("Next.... "); 
    }
    httpGet();
}
