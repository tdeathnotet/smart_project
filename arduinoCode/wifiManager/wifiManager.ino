#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager


//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[50] = "http://192.168.1.11:4000";  //หาจาก cmd  #ipconfig 
String IP = "";

//flag for saving data
bool shouldSaveConfig = false;
//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  
  WiFiManagerParameter custom_mqtt_server("server", "Server address", mqtt_server, 40);
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  //reset settings - for testing
  wifiManager.resetSettings();  //อย่าลืมเอา commnent ออก เพราะจะรีเซ็ตทุกครั้ง ...

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
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  IP = String(mqtt_server); 
  Serial.println("local ip");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print("IP input :");
    Serial.println(IP);

    delay(5000);
  


}
