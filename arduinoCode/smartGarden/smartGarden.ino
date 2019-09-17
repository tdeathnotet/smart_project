#include "DHT.h"
#include <BH1750FVI.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//__________________ตั้งค่า Wifi และ Saver___________________________
const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";
//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";



String statusDevice = "";
const String IP =  "http://192.168.1.13:4000";  //ip *เครื่อง *Server
HTTPClient http;

#define PIN 16 //Relay pin ( gpio16 , D0 ) for ESP8266


//___________________ตั้งค่า Sensor ___________________________________________
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);  //ขาเซ็นเซอร์แสงเป็น D1, D2 (scl, sda)
#define DHTPIN 14     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);


void httpGet(){  //รับค่าจาก Saver เป็น http gets
    

    
    http.begin(IP + "/control/smartgarden/status");
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      String button = root["status"];   //Check JSON
      //Serial.println(http.GET());
      
 //____________________รับปุ่มTV_______________________________________     
        if(button == "ON" ){
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,HIGH); // Pin D0 is HIGH
          statusDevice = button;
          //command
        }
        if(button == "OFF" ){
          //command
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,LOW); // Pin D0 is LOW
          statusDevice = button;
        }

        
    sensor();   //อ่านค่าจาก Sensor   
    send_toSQL();  //ส่งข้อมูลไปเก็บยัง Data
    jsonBuffer.clear();
   }
     http.end();   //Close connection
}


void sensor(){
  //_______________เช็นเซอร์อุหภูมิ_________________________
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
        //________________________เซ็นเซอร์แสง____________________
  uint16_t lux = LightSensor.GetLightIntensity(); 
    
    
//______________________________แสดงค่าออกทาง หน้าจอ________________________
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t  ");
  Serial.print("Light: "); Serial.print(lux); Serial.println(" lux");  //แสดงค่าความเข้มของแสงออกทาง serial
}


void send_toSQL(){ 
//_____________________JSON HTTP______________________________________________________________________________________
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      StaticJsonBuffer<500> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& root = JSONbuffer.createObject(); 
      root["column"] = "sensor_humi";
      root["value"] =  dht.readHumidity();
      root["column2"] = "sensor_tempC";
      root["value2"] = dht.readTemperature();
      root["column3"] = "sensor_tempF";
      root["value3"] = dht.readTemperature(true);
      root["column4"] = "sensor_light";
      root["value4"] = LightSensor.GetLightIntensity();
      root["status"] = statusDevice;  //สถานะการทำงานของ pump

      
      char JSONmessageBuffer[500];
      root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
     // Serial.println(JSONmessageBuffer);

      http.begin(IP + "/control/api/smart_garden");      //ปลายทางที่เราจะส่ง JSONไป
      http.addHeader("Content-Type", "application/json");  //Specify content-type header

      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
      String payload = http.getString(); //Get the response payload
//      Serial.print("httpCode :");
//      Serial.println(payload);    //Print request response payload
//      Serial.println(httpCode);   //Print HTTP return code
      //http.end();  //Close connection  
    }else {
      Serial.println("Error in WiFi connection"); 
    }   
}


void setup() {
  Serial.begin(115200);
  Serial.println("DHTxx test!");

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

  

  
//_____________________________เปิดขา Sensor__________________________-
  dht.begin();
  LightSensor.begin();
  pinMode(PIN,OUTPUT);


}


void loop() {
  httpGet();
  
  delay(1000);
}
