#include <Adafruit_Sensor.h>
#include <DHT.h> 
#include <DHT_U.h>
#include <BH1750FVI.h> 
#include <ArduinoJson.h>  //v.5.0
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager


  //_______________เช็นเซอร์อุหภูมิ_________________________
  float h ; //ความชื้น
  float t ; //องศาเซลเซียส
  float f ; //องศาฟาเรนไฮ
  uint16_t lux ; //ความเข้มของแสง
//______________________SERVER________________________

//define your default values here, if there are different values in config.json, they are overwritten.
char server[50] = "http://192.168.1.11:4000";  //หาจาก cmd  #ipconfig 
String IP = "";
String statusDevice = "OFF";
HTTPClient http;

#define PIN 16 //Relay pin ( gpio16 , D0 ) for ESP8266

//___________________ตั้งค่า Sensor ___________________________________________
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);  //ขาเซ็นเซอร์แสงเป็น D1, D2 (scl, sda)
#define DHTPIN 14     // what digital pin we're connected to D5,gpio14
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT_Unified dht(DHTPIN, DHTTYPE); //DHT setup


//_______________________flag for saving data___________________________
bool shouldSaveConfig = false;
//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}



void httpGet(){  //รับค่าจาก Saver เป็น http get
    http.begin(IP + "/control/smartgarden/status"); //url ที่รับค่ามา
    int httpCode = http.GET();                                             
    if(httpCode > 0){   //Check the returning code    
      StaticJsonBuffer<300> jsonBuffer;  //จองพื้นที่300ไบต์ ให้กับตัวแปร jsonBuffer
      JsonObject& root = jsonBuffer.parseObject(http.getString()); //อ่านค่าจาก http get และมาเก็บในตัวแปร json root
      String button = root["status"];   // ให้ปุ่ม Button = "status" ของjson
      //Serial.println(http.GET());
      
        if(button == "ON" ){  // เช็คสถานะ ว่ากดปุ่ม "ON" อยู่หรือไม่
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,HIGH); // ให้ Relay ทำงาน
          statusDevice = button; // ให้สถานะการทำงานของ solenoid valve = ON
          //delay(1000);
          //command
        }
        else{  // ถ้าไม่ 
          //command
          Serial.println(" SMART GARDEN : " + button );
          digitalWrite(PIN,LOW); // ให้สถานะการทำงานของ solenoid valve = OFF
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
    dht.temperature().getEvent(&event); //
    if (isnan(event.temperature)) {  //เช็คว่า sensor มีการอ่านค่าอยู่หรือไม่
      Serial.println("Error reading temperature!");
    }
    else { //เก็บค่าไว้ในตัวแปรอุณหภูมิ และ แสดงค่าผ่านทาง Serial
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
    dht.humidity().getEvent(&event);  //เช็คว่า sensor มีการอ่านค่าอยู่หรือไม่
    if (isnan(event.relative_humidity)) {
      Serial.println("Error reading humidity!");
    }
    else {   //เก็บค่าไว้ในตัวแปรความชื้น และ แสดงค่าผ่านทาง Serial
      Serial.print("Humidity: ");
      h = event.relative_humidity;
      Serial.print(h);
      Serial.print("%\t");
    }

   //________________________เซ็นเซอร์แสง____________________
   lux = LightSensor.GetLightIntensity();   //อ่านค่า Sensor แสง
  Serial.print("Light: "); Serial.print(lux); Serial.println(" lux");  //แสดงค่าความเข้มของแสงออกทาง serial
}

void toServer(){  //ส่งค่า Sensor ไปยัง Server ผ่าน http post
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
//      JSONbuffer.clear();
      http.end();  //Close connection  
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  //_____________________________Ceonnect Wifi____________________________________________

  //___________________________WiFiManager_________________________
  WiFiManagerParameter custom_server("server", "Server address", server, 40);   
  
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  //add all your parameters here
  wifiManager.addParameter(&custom_server);
  //reset settings - for testing
  wifiManager.resetSettings();  //อย่าใส่ commnent ออก เพราะจะรีเซ็ตทุกครั้ง ...

  if (!wifiManager.autoConnect("SMART_GARDEN", "admin")) {   //ssid & password เข้าตั้งค่า ip และหาข้อมูล
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("Connected!......  :)");
  //read updated parameters
  strcpy(server, custom_server.getValue());
  IP = String(server); 
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  
//_____________________________เปิดขา Sensor__________________________-
  dht.begin();
  LightSensor.begin();
  pinMode(PIN,OUTPUT);

}


void loop() {
   if (WiFi.status() == WL_CONNECTED) {  //เช็คการเชื่อมต่อของ Wifi
    sensor();   //อ่านค่าจาก Sensor   
    httpGet(); //ส่งไปแสดงค่า ยังหน้าเว็บ
    toServer();  //ส่งข้อมูลไปเก็บยัง Data
    delay(500); //No more than 0.5 Hz sampling rate (once every 2 seconds)
  }else {   
      Serial.println("Error in WiFi connection");  
    }
}
