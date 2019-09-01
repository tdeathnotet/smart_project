#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRsend.h>

const uint16_t kRecvPin = D5;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.




void convertStrtoArr();
int toIntArray();


#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;



IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results




void setup() {
irsend.begin();
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
}



void loop() {
  
  
  if (irrecv.decode(&results)) {
   // Serial.println(); 

//rawLengthData----------------------------------------------------------------
    Serial.println("");
    int bufferSize = uint64ToString(getCorrectedRawLength(&results), 10).toInt();
    Serial.print("RawLength :");
    Serial.println(bufferSize);  //จำนวนทั้งหมดของ Decode


 //rawData------------------------------------------------------------------
     Serial.print("&results :"); 
     String rawData = resultToSourceCode(&results);

    Serial.println(rawData);
    Serial.println();    // Blank line between entries
    yield();             // Feed the WDT (again)


      //ตัวแปรเก็บค่า decode
    toIntArray(rawData,bufferSize);  //ฟังก์ชั้น Char* to Int Array

    
//    Serial.println("bufferSize :");
//    Serial.println(bufferSize);
    //command[bufferSize] = 
   
  }
}

int toIntArray(String str,int buffSize){
    uint16_t command[buffSize];
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
    
    Serial.print("command[");Serial.print(buffSize);Serial.print("] :");
    command[buffSize]; //กดหมดจำนวนbuffer ให้กับ command
    for(size_t i = 0; i < index; i++){
      command[i] = (uint16_t)arr[i]; //ให้array แต่ละตัวของcommand เท่าarr[i]
      Serial.print(command[i]); Serial.print("  ");
    }
    irsend.sendRaw(command,buffSize, 38);  // Send a raw data capture at 38kHz.
    
}
