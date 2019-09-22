#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750FVI.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//__________________ตั้งค่า Wifi และ Saver___________________________
const char* MY_SSID = "icute3";
const char* MY_PWD =  "thinkbeyond03";
//const char* MY_SSID = "26SW_AIS2.4G";
//const char* MY_PWD =  "58543206";
  //_______________เช็นเซอร์อุหภูมิ_________________________
  float h ; //ความชื้น
  float t ; //องศาเซลเซียส
  float f ; //องศาฟาเรนไฮ
  uint16_t lux ;
//______________________SERVER________________________

String statusDevice = "OFF";
const String IP =  "http://192.168.1.15:4000";  //ip *เครื่อง *Server
HTTPClient http;

#define PIN 16 //Relay pin ( gpio16 , D0 ) for ESP8266

//___________________ตั้งค่า Sensor ___________________________________________
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);  //ขาเซ็นเซอร์แสงเป็น D1, D2 (scl, sda)
#define DHTPIN 14     // what digital pin we're connected to D5,gpio14
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT_Unified dht(DHTPIN, DHTTYPE);

void httpGet(){  //รับค่าจาก Saver เป็น http gets
    http.begin(IP + "/control/smartgarden/status");
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      String button = root["status"];   //Check JSON
      //Serial.println(http.GET());
      
        if(button == "ON" ){  // pumpทำงาน
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,HIGH); // Pin D0 is HIGH
          statusDevice = button;
          //delay(1000);
          //command
        }
        else{
          //command
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,LOW); // Pin D0 is LOW
          statusDevice = "OFF";
        }
    jsonBuffer.clear();
   }
   http.end();   //Close connection
}

void sensor(){
  //_______________เช็นเซอร์อุหภูมิ_________________________
//  float h = dht.readHumidity(); 
//  float t = dht.readTemperature();
//  float f = dht.readTemperature(true);
    sensors_event_t event;  
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Error reading temperature!");
    }
    else {
      Serial.print("Temperature: ");
      t = event.temperature;
      Serial.print(t);
      Serial.print(" *C\t");
      Serial.print("Temperature: ");
      f = ((1.8 * event.temperature) + 32 );
      Serial.print(f);
      Serial.print(" F\t");
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println("Error reading humidity!");
    }
    else {
      Serial.print("Humidity: ");
      h = event.relative_humidity;
      Serial.print(h);
      
      Serial.print("%\t");
    }
   //________________________เซ็นเซอร์แสง____________________
   lux = LightSensor.GetLightIntensity(); 
  Serial.print("Light: "); Serial.print(lux); Serial.println(" lux");  //แสดงค่าความเข้มของแสงออกทาง serial
}

void toServer(){ 
//_____________________JSON HTTP______________________________________________________________________________________
      StaticJsonBuffer<500> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& root = JSONbuffer.createObject(); 
      root["column"] = "sensor_humi";
      root["value"] =  h;
      root["column2"] = "sensor_tempC";
      root["value2"] = t;
      root["column3"] = "sensor_tempF";
      root["value3"] = f;
      root["column4"] = "sensor_light";
      root["value4"] = lux ;
      root["status"] = statusDevice;  //สถานะการทำงานของ pump
      
      char JSONmessageBuffer[500];
      root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
     // Serial.println(JSONmessageBuffer);

      http.begin(IP + "/control/api/smart_garden");      //ปลายทางที่เราจะส่ง JSONไป
      http.addHeader("Content-Type", "application/json");  //Specify content-type header
      http.POST(JSONmessageBuffer);   //Send the request
      //http.getString(); //Get the response payload
//      Serial.print("httpCode :");
//      Serial.println(payload);    //Print request response payload
//      Serial.println(httpCode);   //Print HTTP return code
      JSONbuffer.clear();
      http.end();  //Close connection  
}


void setup() {
  Serial.begin(115200);
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
   if (WiFi.status() == WL_CONNECTED) { 
    sensor();   //อ่านค่าจาก Sensor   
    httpGet(); //ส่งไปแสดงค่า ยังหน้าเว็บ
    toServer();  //ส่งข้อมูลไปเก็บยัง Data
    delay(500); //No more than 0.5 Hz sampling rate (once every 2 seconds)
  }else {
      Serial.println("Error in WiFi connection"); 
    }
}
