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

//String tv_On = "",tv_volUp = "",tv_volDown = "";
//int buffOn,buffVolUp,buffVolDown; //buffer botton decoder

//const char* MY_SSID = "26SW_WIFI_2.4G";
//const char* MY_PWD =  "58543206";

const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.




//void convertStrtoArr();
#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;



IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

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
String httpJSON(String Data,String rawData){ 

      //_____________________JSON HTTP___________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<3000> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject(); 

      
      JSONencoder[Data] = rawData;    //input String to Json 
      //JSONencoder["Button"] = "TV_ON"; 
      
      char JSONmessageBuffer[3000];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);
      HTTPClient http;
      http.begin("http://192.168.1.24:4000/control/api/json");      //ปลายทางที่เราจะส่ง JSONไป
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


void setup() {

  Serial.begin(115200);
  Serial.printf("\nIRrecvDumpV2 is now running and waiting for IR input on Pin "
                  "%d\n", kRecvPin);
  #if DECODE_HASH
    // Ignore messages with less than minimum on or off pulses.
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
//    irsend.begin();
}

char input;

void loop() {
    if(irrecv.decode(&results)) {
      if(Serial.available()){
          input = Serial.read();
//___________________________________________________TV REMOTE__________________________________________________
        
 /*----------------------------------Decode Tv remote  ' 0 ' ON Button-----------------------------------------*/       
         if( input == '0'){  
            Serial.println("You Select TV remote & Decoder ON Button ");  
            int buffOn = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_On = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
           yield(); 
            // uint16_t command[bufferSize];
            Serial.print("tv_On[");Serial.print(buffOn);Serial.print("] :");Serial.println(tv_On);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");  
            httpJSON("tv_On",tv_On);
          }
 /*----------------------------------Decode Tv remote  ' + ' Vol+ Button -----------------------------------------*/             
          else if( input == '+'){   
            Serial.println("You Select TV remote & Decoder Vol+ Button");
            int buffVolUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_volUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
           yield(); 
            // uint16_t command[bufferSize];
            Serial.print("tv_volUp[");Serial.print(buffVolUp);Serial.print("] :");Serial.println(tv_volUp);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_volUp",tv_volUp);      
          } 
  /*----------------------------------Decode Tv remote  ' - ' vol- Button-----------------------------------------*/     
           else if( input == '-'){   
            Serial.println("You Select TV remote & Decoder vol- Button");
            int buffVolDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_volDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_volDown[");Serial.print(buffVolDown);Serial.print("] :");Serial.println(tv_volDown);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_volDown",tv_volDown);     
          }  
/*----------------------------------Decode Tv remote  ' 5 ' OK Button -----------------------------------------*/ 
           else if( input == '5'){   
            Serial.println("You Select TV remote & Decoder OK Button");
            int buffOK = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_OK = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_OK[");Serial.print(buffOK);Serial.print("] :");Serial.println(tv_OK);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_OK",tv_OK);     
          }  
/*----------------------------------Decode Tv remote  ' 8 ' ▲ Button-----------------------------------------*/
           else if( input == '8'){   
            Serial.println("You Select TV remote & Decoder ▲ Button");
            int buffUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Up = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Up[");Serial.print(buffUp);Serial.print("] :");Serial.println(tv_Up);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Up",tv_Up);     
          }    
/*----------------------------------Decode Tv remote  ' 4 ' ◀ Button-----------------------------------------*/
           else if( input == '4'){   
            Serial.println("You Select TV remote & Decoder ◀ Button");
            int buffLeft = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Left = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Left[");Serial.print(buffLeft);Serial.print("] :");Serial.println(tv_Left);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Left",tv_Left);     
          } 
/*----------------------------------Decode Tv remote  ' 6 ' ▶ Button-----------------------------------------*/ 
           else if( input == '6'){   
            Serial.println("You Select TV remote & Decoder ▶ Button");
            int buffRight = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Right = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Right[");Serial.print(buffRight);Serial.print("] :");Serial.println(tv_Right);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Right",tv_Right);     
          }
/*----------------------------------Decode Tv remote  ' 2 ' ▼ Button-----------------------------------------*/ 
           else if( input == '2'){   
            Serial.println("You Select TV remote & Decoder ▼ Button");
            int buffDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Down = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Down[");Serial.print(buffDown);Serial.print("] :");Serial.println(tv_Down);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Down",tv_Down);     
          }
/*----------------------------------Decode Tv remote  ' 9 ' CH ▲ Button-----------------------------------------*/
           else if( input == '9'){   
            Serial.println("You Select TV remote & Decoder CH ▲ Button");
            int buffCHUp = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHUp = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHUp[");Serial.print(buffCHUp);Serial.print("] :");Serial.println(tv_CHUp);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_CHUp",tv_CHUp);     
          }
/*----------------------------------Decode Tv remote  ' 3 ' CH ▼ Button-----------------------------------------*/ 
           else if( input == '3'){   
            Serial.println("You Select TV remote & Decoder CH ▼ Button");
            int buffCHDown = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_CHDown = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_CHDown[");Serial.print(buffCHDown);Serial.print("] :");Serial.println(tv_CHDown);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_CHDown",tv_CHDown);     
          }
/*----------------------------------Decode Tv remote  ' 1 ' ↺Return,Exit Button-----------------------------------------*/ 
           else if( input == '1'){   
            Serial.println("You Select TV remote & Decoder ↺Return,Exit Button");
            int buffReturn = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Return = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Return[");Serial.print(buffReturn);Serial.print("] :");Serial.println(tv_Return);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Return",tv_Return);     
          }
/*----------------------------------Decode Tv remote  ' 7 ' Mute Button-----------------------------------------*/  
            else if( input == '7'){   
            Serial.println("You Select TV remote & Decoder Mute Button");
            int buffMute = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
            String tv_Mute = resultToSourceCode(&results);// Feed the WDT as the text output can take a while to print.
            // uint16_t command[bufferSize];
            Serial.print("tv_Mute[");Serial.print(buffMute);Serial.print("] :");Serial.println(tv_Mute);
            // yield(); 
            Serial.println("Decoder Success!!"); Serial.println("");
            httpJSON("tv_Mute",tv_Mute);     
          }
          //int timeout = millis();
          Serial.println("Next Button Encoder ");  
      }
   }    
}
