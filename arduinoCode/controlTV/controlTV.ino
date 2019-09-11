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




#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;



IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results
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
        else if(Status == "1" && button == "tv_volUp"){   
            Serial.println("You Select TV remote & Decoder Vol+ Button");
            int buffVolUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_volUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_volUp[");Serial.print(buffVolUp);Serial.print("] :");Serial.println(tv_volUp);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL( "tv_volUp", tv_volUp, "tv_VolUpBuff", buffVolUp );
          } 
  /*----------------------------------Decode Tv remote  ' - ' vol- Button-----------------------------------------*/     
           else if( Status == "1" && button == "tv_volDown"){   
            Serial.println("You Select TV remote & Decoder vol- Button");
            int buffVolDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_volDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_volDown[");Serial.print(buffVolDown);Serial.print("] :");Serial.println(tv_volDown);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL( "tv_volDown", tv_volDown, "tv_volDownBuff", buffVolDown );
          }
            
/*----------------------------------Decode Tv remote  ' 5 ' OK Button -----------------------------------------*/ 
           else if( Status == "1" && button == "tv_OK"){   
            Serial.println("You Select TV remote & Decoder OK Button");
            int buffOK = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_OK = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_OK[");Serial.print(buffOK);Serial.print("] :");Serial.println(tv_OK);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_OK",tv_OK,"tv_OKBuff",buffOK);
          }  
/*----------------------------------Decode Tv remote  ' 8 ' ▲ Button-----------------------------------------*/
           else if( Status == "1" && button == "tv_Up" ){   
            Serial.println("You Select TV remote & Decoder ▲ Button");
            int buffUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Up = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Up[");Serial.print(buffUp);Serial.print("] :");Serial.println(tv_Up);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Up",tv_Up,"tv_UpBuff",buffUp);
          }   
/*----------------------------------Decode Tv remote  ' 2 ' ▼ Button-----------------------------------------*/ 
           else if( Status == "1" && button == "tv_Down" ){   
            Serial.println("You Select TV remote & Decoder ▼ Button");
            int buffDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Down = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Down[");Serial.print(buffDown);Serial.print("] :");Serial.println(tv_Down);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Down",tv_Down,"tv_DownBuff",buffDown);  
          } 
/*----------------------------------Decode Tv remote  ' 4 ' ◀ Button-----------------------------------------*/
           else if( Status == "1" && button == "tv_Left" ){   
            Serial.println("You Select TV remote & Decoder ◀ Button");
            int buffLeft = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Left = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Left[");Serial.print(buffLeft);Serial.print("] :");Serial.println(tv_Left);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Left",tv_Left,"tv_LeftBuff",buffLeft);    
          } 
/*----------------------------------Decode Tv remote  ' 6 ' ▶ Button-----------------------------------------*/ 
           else if( Status == "1" && button == "tv_Right"){   
            Serial.println("You Select TV remote & Decoder ▶ Button");
            int buffRight = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Right = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Right[");Serial.print(buffRight);Serial.print("] :");Serial.println(tv_Right);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Right",tv_Right,"tv_RightBuff",buffRight); 
          }
/*----------------------------------Decode Tv remote  ' 9 ' CH ▲ Button-----------------------------------------*/
           else if( Status == "1" && button == "tv_CHUp"){   
            Serial.println("You Select TV remote & Decoder CH ▲ Button");
            int buffCHUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHUp[");Serial.print(buffCHUp);Serial.print("] :");Serial.println(tv_CHUp);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_CHUp",tv_CHUp,"tv_CHUpBuff",buffCHUp);
          }
/*----------------------------------Decode Tv remote  ' 3 ' CH ▼ Button-----------------------------------------*/ 
           else if( Status == "1" && button == "tv_CHDown"){   
            Serial.println("You Select TV remote & Decoder CH ▼ Button");
            int buffCHDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHDown[");Serial.print(buffCHDown);Serial.print("] :");Serial.println(tv_CHDown);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_CHDown",tv_CHDown,"tv_CHDownBuff",buffCHDown); 
          }
/*----------------------------------Decode Tv remote  ' 1 ' ↺Return,Exit Button-----------------------------------------*/ 
           else if(  Status == "1" && button == "tv_Return" ){   
            Serial.println("You Select TV remote & Decoder ↺Return,Exit Button");
            int buffReturn = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Return = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Return[");Serial.print(buffReturn);Serial.print("] :");Serial.println(tv_Return);
            Serial.println("Decoder Success!!"); Serial.println("");
            decodeToSQL("tv_Return",tv_Return,"tv_ReturnBuff",buffReturn);
          }
/*----------------------------------Decode Tv remote  ' 7 ' Mute Button-----------------------------------------*/  
            else if( Status == "1" && button == "tv_Mute" ){   
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


  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);

  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.print("WIFI connected! , to IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  
//    Serial.println("--------- DECOD TV REMOTE-------------");
//    Serial.println("Enter ' 0 ' ON Button ");
//    Serial.println("Enter ' 5 ' OK Button");
//    Serial.println("Enter ' 8 ' ▲ Button");
//    Serial.println("Enter ' 2 ' ▼ Button");
//    Serial.println("Enter ' 4 ' ◀ Button");
//    Serial.println("Enter ' 6 ' ▶ Button");
//    Serial.println("Enter ' + ' Vol+ Button ");
//    Serial.println("Enter ' - ' vol- Button ");
//    Serial.println("Enter ' 9 ' CH ▲ Button");
//    Serial.println("Enter ' 3 ' CH ▼ Button");
//    Serial.println("Enter ' 1 ' ↺Return,Exit Button");
//    Serial.println("Enter ' 7 ' Mute Button");  

    irsend.begin();  //เปิดpin ในการส่ง IR

}



void loop() {
    if(irrecv.decode(&results)){
      decoder_tvRemote();
      //delay(200);
      Serial.println("Next.... "); 
    }
    httpGet();
    
    //delay(1000);
}