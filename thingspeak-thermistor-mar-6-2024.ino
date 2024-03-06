//#include <WiFiS3.h>
#include "WiFiS3.h"
//#include <ThingSpeak.h>
#include "ThingSpeak.h"
#include "ArduinoR43DigitDisplay.h"
#include "Arduino_LED_Matrix.h"
#include "fonts.h"
ArduinoLEDMatrix matrix;
#include "arduino_secrets.h" 

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
 
WiFiClient client;
unsigned long myChannelNumber = 23-secret-84;
const char * myWriteAPIKey = "0MMB-secret-LL698";
/* -------------------------------------------------------------------------- */
void setup() {
/* -------------------------------------------------------------------------- */  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  matrix.begin();
  randomSeed(analogRead(0));
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
  }
  
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    ThingSpeak.begin(client);
    // wait 10 seconds for connection:
    delay(10000);
  }
  
  printWifiStatus();
 
  Serial.println("\nStarting connection to ThingSpeak...");
  // if you get a connection, report back via serial:

}
uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
void loop() {
  while (true){
    int ThermistorPin = 0; // Analog input pin for thermistor voltage
    int Vo; // Integer value of voltage reading
    float R = 10000; // Fixed resistance in the voltage divider
    float logRt,Rt,T;
    float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
    Vo = analogRead(ThermistorPin);
    Rt = R*( 1023.0 / (float)Vo - 1.0 );
    logRt = log(Rt);
    T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;
    float tf=T*9/5+32;
    Serial.println(" Vo = "+(String)Vo);
    Serial.println(" Rt = "+(String)Rt);
    Serial.println(" degC = "+(String)T);
    Serial.println(" degF = "+(String)tf);
    Serial.println();
    Serial.print("Data sent to ThingSpeak = ");
    Serial.println(tf);
    delay (25000);
    ThingSpeak.setField(1,tf);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    drawNumber(tf,frame);
      matrix.renderBitmap(frame, 8, 12);
      delay(1000);

      clear_frame();
delay(2000);
}
}
/* -------------------------------------------------------------------------- */
void printWifiStatus() {
/* -------------------------------------------------------------------------- */  
  // print the SSID of the network you're attached to:
  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
void clear_frame() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 12; col++) {
      frame[row][col] = 0;
    }
}
}
