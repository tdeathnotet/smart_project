#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
 
void setup() {
  Serial.begin(115200);                            //Serial connection
  WiFi.begin("icute3", "thinkbeyond03");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
  }
}
void loop() {
  String command = "0, 4494, 558, 574, 560, 1678, 584, 548, 558, 550, 584, 546, 532, 598, 562, 548, 584, 542, 582, 1660, 586, 542, 558, 1684, 556, 1702, 562, 1676";
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["command"] = command;
 
//    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
//    values.add(20); //Add value to array
//    values.add(21); //Add value to array
//    values.add(23); //Add value to array
// 
//    JsonArray& timestamps = JSONencoder.createNestedArray("timestamps"); //JSON array
//    timestamps.add("10:10"); //Add value to array
//    timestamps.add("10:20"); //Add value to array
//    timestamps.add("10:30"); //Add value to array
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://192.168.1.13:4000/control/api/jsonn");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
  
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
    Serial.print("httpCode :");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection

  } else {
    Serial.println("Error in WiFi connection"); 
  }
  delay(30000);  //Send a request every 30 seconds
}
