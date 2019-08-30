
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino

//AC_sumsung

//on
uint16_t rawDataOn_Off[349] = {644, 17788,  3040, 8906,  562, 434,  560, 1476,  512, 456,  484, 510,  482, 512,  510, 484,  544, 450,  558, 436,  562, 432,  564, 1450,  540, 430,  566, 428,  564, 1452,  538, 430,  564, 454,  540, 1448,  542, 1478,  512, 1478,  456, 1532,  488, 1502,  530, 436,  564, 432,  566, 428,  564, 430,  564, 430,  564, 430,  564, 428,  566, 432,  562, 432,  560, 434,  562, 454,  540, 456,  540, 454,  540, 458,  526, 468,  480, 514,  482, 512,  516, 480,  556, 438,  560, 432,  566, 428,  564, 430,  564, 430,  566, 430,  564, 430,  564, 430,  564, 432,  562, 434,  560, 454,  540, 452,  542, 458,  536, 456,  502, 1516,  456, 1532,  520, 1470,  538, 1452,  538, 2932,  3038, 8902,  566, 1450,  540, 430,  564, 432,  562, 432,  564, 454,  542, 454,  540, 454,  540, 456,  538, 456,  498, 1518,  484, 486,  544, 452,  552, 1462,  538, 430,  564, 1450,  538, 1452,  540, 1450,  538, 1450,  540, 1450,  540, 1450,  540, 458,  536, 458,  478, 514,  482, 514,  510, 482,  548, 446,  562, 432,  566, 430,  564, 430,  564, 430,  566, 428,  566, 428,  568, 430,  564, 432,  562, 432,  562, 434,  560, 454,  542, 454,  540, 458,  536, 458,  480, 514,  482, 512,  512, 482,  552, 442,  560, 434,  564, 432,  562, 430,  564, 430,  564, 430,  564, 430,  564, 430,  566, 430,  562, 434,  562, 454,  540, 454,  540, 454,  552, 2920,  3046, 8924,  478, 1536,  482, 486,  544, 452,  556, 438,  564, 434,  562, 430,  564, 430,  564, 430,  564, 428,  566, 1450,  540, 432,  562, 434,  562, 1448,  540, 1480,  510, 458,  482, 1534,  484, 486,  514, 1500,  536, 1454,  540, 1450,  538, 1452,  538, 1452,  538, 1450,  538, 1452,  540, 1448,  540, 458,  538, 458,  480, 514,  480, 1534,  490, 1500,  534, 1456,  538, 430,  588, 406,  564, 432,  562, 430,  564, 430,  564, 1450,  564, 1424,  540, 454,  540, 1478,  510, 1480,  452, 516,  482, 514,  540, 1474,  532, 1456,  538, 432,  562, 432,  562, 432,  562, 432,  562, 432,  588, 408,  562, 432,  588, 1424,  540, 1450,  540, 1478,  456, 1534,  562};  // SAMSUNG_AC

//temp+
uint16_t rawDataUp[233] = {604, 17938,  2990, 8952,  464, 530,  488, 1526,  480, 490,  518, 476,  518, 476,  544, 450,  520, 476,  520, 474,  520, 476,  520, 1496,  494, 500,  494, 500,  514, 1504,  466, 502,  552, 444,  518, 1496,  462, 1528,  466, 1524,  492, 1496,  502, 1488,  518, 450,  544, 452,  544, 452,  516, 480,  516, 478,  516, 500,  494, 488,  508, 502,  548, 444,  556, 440,  520, 476,  486, 506,  490, 504,  516, 478,  518, 476,  518, 478,  516, 428,  566, 474,  520, 476,  544, 450,  518, 478,  544, 452,  542, 452,  542, 474,  520, 474,  494, 500,  492, 390,  670, 438,  518, 476,  488, 508,  488, 506,  546, 448,  544, 1472,  492, 1498,  492, 1496,  518, 1472,  492, 2980,  2990, 8974,  494, 1496,  518, 478,  518, 478,  552, 440,  516, 480,  464, 530,  488, 508,  488, 504,  518, 478,  518, 1496,  520, 448,  546, 448,  520, 476,  544, 450,  518, 1494,  522, 1468,  520, 476,  514, 1502,  496, 1494,  490, 1500,  462, 1526,  518, 1472,  514, 1476,  494, 1494,  518, 1472,  518, 452,  544, 452,  516, 480,  540, 1470,  498, 1520,  520, 1470,  488, 482,  518, 476,  488, 506,  490, 504,  544, 450,  546, 448,  518, 1496,  516, 454,  544, 1470,  520, 1470,  492, 480,  540, 476,  494, 1524,  492, 1498,  526, 442,  518, 478,  488, 506,  488, 506,  542, 452,  542, 452,  518, 478,  518, 1496,  492, 1496,  518, 1472,  492, 1496,  520};  //Up
//temp-
uint16_t rawDataDown[233] = {580, 15838,  2992, 8972,  494, 502,  492, 1524,  466, 502,  558, 436,  518, 478,  518, 476,  488, 506,  492, 502,  518, 476,  518, 1498,  492, 476,  544, 450,  544, 1470,  494, 478,  516, 480,  530, 1480,  492, 1524,  466, 1524,  498, 1492,  440, 1550,  464, 504,  518, 476,  520, 476,  520, 474,  544, 450,  518, 474,  548, 446,  518, 478,  544, 452,  516, 480,  514, 504,  492, 502,  518, 478,  518, 476,  514, 478,  464, 530,  520, 474,  490, 506,  490, 504,  544, 450,  544, 450,  546, 448,  546, 448,  518, 476,  520, 476,  544, 452,  542, 452,  516, 478,  516, 504,  492, 502,  492, 504,  492, 502,  552, 1464,  492, 1498,  462, 1526,  492, 1498,  494, 2978,  2992, 8950,  516, 1498,  518, 450,  520, 478,  542, 452,  544, 450,  540, 476,  518, 474,  494, 502,  492, 502,  556, 1460,  492, 476,  488, 506,  490, 504,  544, 452,  518, 1496,  520, 1470,  494, 474,  520, 1496,  494, 1496,  492, 1496,  494, 1524,  490, 1500,  494, 1494,  492, 1496,  464, 1526,  518, 450,  518, 478,  516, 476,  520, 1496,  518, 1470,  518, 1472,  518, 476,  494, 500,  492, 502,  492, 504,  514, 478,  556, 440,  518, 1496,  464, 504,  492, 1524,  518, 1472,  492, 476,  544, 1470,  518, 452,  542, 1472,  494, 480,  538, 476,  494, 498,  522, 476,  516, 478,  550, 444,  520, 474,  518, 1496,  464, 1526,  518, 1472,  518, 1472,  492};  // SAMSUNG_AC

//FAN HATAri

//uint16_t rawDataOn_Off[71] = {8994, 4496,  560, 546, 
//586, 1700,  538, 548,  584, 540,  558, 574,  564,
//546,  584, 542,  558, 574,  564, 1700,  532, 574,
//564, 1700,  532, 1706,  564, 1702,  536, 1700,  534,
//1704,  564, 1702,  536, 1700,  534, 572,  562, 546, 
//586, 542,  560, 1704,  566, 540,  560, 572,  564, 546, 
//586, 542,  560, 1704,  564, 1698,  540, 1698,  534, 572, 
//564, 1698,  534, 1706,  564, 1698,  540, 39892,  8994, 2254,  564};  // NEC 40BF8877
// Example Samsung A/C state captured from IRrecvDumpV2.ino

//uint16_t rawDataSpeed[71] = {9038, 4446,  610, 500,  632, 1654,  584, 498,  632, 494,  624, 512,  608, 520,  612, 492,  628, 504,  612, 1628,  626, 504,  612, 1654,  600, 1636,  612, 1626,  610, 1654,  602, 1636,  612, 1654,  586, 1652,  598, 506,  610, 1654,  600, 1638,  610, 494,  626, 508,  608, 498,  632, 496,  624, 508,  610, 1628,  626, 504,  610, 500,  632, 1630,  608, 1630,  624, 1636,  612, 1654,  584, 39836,  9038, 2186,  632};  // NEC 40BFB04F
//uint16_t rawDataSwing[71] = {8988, 4518,  536, 548,  584, 1702,  536, 548,  584, 542,  558, 572,  564, 546,  586, 542,  558, 572,  564, 1700,  532, 574,  564, 1698,  534, 1704,  564, 1702,  536, 1700,  532, 1706,  562, 1702,  536, 1700,  530, 574,  564, 1700,  532, 574,  564, 546,  586, 540,  558, 572,  564, 546,  586, 540,  560, 1706,  562, 542,  558, 1706,  564, 1702,  536, 1702,  530, 1706,  564, 1700,  536, 39884,  8990, 2254,  564};  // NEC 40BFA05F
uint16_t rawDataIComfort[71] = {9012, 4470,  586, 540,  560, 1704,  564, 540,  560, 572,  564, 544,  586, 542,  560, 572,  564, 546,  586, 1700,  536, 546,  586, 1700,  538, 1700,  532, 1706,  564, 1700,  538, 1700,  532, 1704,  564, 1700,  536, 548,  584, 1702,  536, 546,  586, 1700,  538, 546,  586, 540,  560, 572,  564, 546,  584, 1702,  536, 546,  586, 1700,  536, 546,  586, 1700,  538, 1700,  532, 1706,  564, 39858,  9016, 2228,  558};  // NEC 40BFA857


//TV

uint16_t rawDataVolUp[99] = {3466, 1744,  398, 444,  422, 1342,  396, 444,  424, 444,  424, 444,  450, 418,  450, 418,  448, 418,  478, 390,  452, 418,  454, 414,  454, 414,  454, 414,  454, 1312,  422, 418,  450, 418,  454, 414,  450, 418,  454, 414,  454, 416,  478, 390,  452, 416,  480, 388,  482, 1282,  426, 414,  450, 418,  452, 416,  454, 414,  452, 416,  452, 414,  456, 412,  454, 414,  452, 416,  456, 412,  482, 386,  480, 388,  452, 416,  482, 1284,  426, 414,  454, 414,  452, 416,  456, 412,  454, 416,  454, 414,  452, 416,  456, 1310,  424, 416,  452, 1314,  396};  // PANASONIC 400401000405
uint16_t rawDataVolDown[99] = {3458, 1754,  418, 422,  444, 1320,  418, 424,  444, 424,  444, 424,  444, 424,  444, 424,  446, 422,  444, 424,  444, 424,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 422,  444, 424,  444, 424,  446, 422,  446, 424,  444, 424,  444, 424,  444, 424,  444, 422,  446, 1320,  418, 422,  444, 424,  444, 424,  444, 424,  444, 426,  444, 422,  446, 424,  444, 424,  444, 1320,  418, 422,  444, 424,  444, 422,  446, 422,  444, 1322,  416, 422,  446, 422,  444, 1320,  418, 424,  444, 424,  444, 424,  444, 424,  444, 1320,  418, 422,  446, 1320,  418};  // PANASONIC 400401008485

void setup() {
  irsend.begin();
  Serial.begin(115200);
  /*#if ESP8266
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  #else  // ESP8266
    Serial.begin(115200, SERIAL_8N1);
  #endif  // ESP8266*/

  delay(3000);

 
}


void loop() {
    if(Serial.available()){
    Serial.println("1.ON_OFF ");
    Serial.println("2.SPEED ");
    Serial.println("3.SWING ");
    Serial.println("4.I-COMFORT ");
    Serial.println("");

    Serial.println("Get The Number to Control FAN Hatari");
     char n = Serial.read();
    switch(n){
      case '1': Serial.println("Turn ON_OFF");
        irsend.sendRaw(rawDataOn_Off, 349, 38);delay(500);// On
        
      break;
      case '2':Serial.println("TEMP + ");
        irsend.sendRaw(rawDataUp, 233, 38);delay(500);
      break;
      case '3':Serial.println("TWMP - ");
        irsend.sendRaw(rawDataDown, 233, 38);delay(500);
      break;
      case '4':Serial.println("Mode I-COMFORT");
        irsend.sendRaw(rawDataIComfort, 71, 38);delay(500);
      break;
       
  }
  
    /*

  irsend.sendRaw(rawData, 71, 38);
  delay(15000);

  
     //all Band
  Serial.println("NEC");
  irsend.sendNEC(0x00FFE01FUL);
  
  delay(2000);
  Serial.println("Sony");
  irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  delay(2000);
  Serial.println("a rawData capture from IRrecvDumpV2");
  Serial.println("a Samsung A/C state from IRrecvDumpV2");
  irsend.sendSamsungAC(samsungState);
  delay(2000);*/
  }
}
