#include "ClosedCube_HDC1080.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <SoftwareSerial.h>

#include <config2.h>


const char* wifiSSD = WIFI_SSID_NAME;
const char* wifiPassword = WIFI_PASSWORD;
const char* serverName = SERVER_NAME;


String temperature, humidity, soilString;
int soil0,soil1,soil2,soil3;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000; // in seconds

int debugSerialBaud = DEBUG_SERIAL_BAUD;
int soilFetcherSerialBaud = SOIL_FETCHER_SERIAL_BAUD;

SoftwareSerial SoilfetcherSerial(0, 2); // RX, TX
ClosedCube_HDC1080 hdc1080;


void setup() {
  Serial.begin(debugSerialBaud);
  SoilfetcherSerial.begin(soilFetcherSerialBaud);
  hdc1080.begin(0x40);

  WiFi.begin(wifiSSD, wifiPassword);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

  temperature = String(hdc1080.readTemperature(), 1);
  humidity = String(hdc1080.readHumidity(), 1);
  
  while(SoilfetcherSerial.available() > 0) {
    soilString = SoilfetcherSerial.readStringUntil('\n');
    int index0 = soilString.indexOf(' ');
    int index1 = soilString.indexOf(' ', index0+1);
    int index2 = soilString.indexOf(' ', index1+1);
    soil0 = soilString.substring(0, index0).toInt();
    soil1 = soilString.substring(index0+1, index1).toInt();
    soil2 = soilString.substring(index1+1, index2).toInt();
    soil3 = soilString.substring(index2+1).toInt();
  }

  Serial.println(soilString);
  Serial.println(soil0);
  Serial.println(soil1);
  Serial.println(soil2);
  Serial.println(soil3);
  Serial.println(temperature + " " + humidity);

  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
  
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "soil0=" + String(soil0) + "&soil1=" + String(soil1)  + "&soil2=" + String(soil2)  + "&soil3=" + String(soil3) +"&temperature=" + temperature + "&humidity=" + humidity;           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.println(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  
  delay(timerDelay);
}
