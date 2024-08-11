#include <SoftwareSerial.h>

#include <config.h>


int debugSerialBaud = DEBUG_SERIAL_BAUD;
int soilFetcherSerialBaud = SOIL_FETCHER_SERIAL_BAUD;

int fetchingIntervalPeriod = FETCHING_INTERVAL_PERIOD;


SoftwareSerial MasterSerial(2, 3); // RX, TX


void setup() {
  Serial.begin(debugSerialBaud);
  MasterSerial.begin(soilFetcherSerialBaud);
}

int soil0 = 0;
int soil1 = 0;
int soil2 = 0;
int soil3 = 0;

void loop() {
  soil0 = analogRead(A0);
  soil1 = analogRead(A1);
  soil2 = analogRead(A2);
  soil3 = analogRead(A3);
  String soilString = String(soil0) + " " + String(soil1) + " " + String(soil2) + " " + String(soil3);
  MasterSerial.println(soilString);
  Serial.println(soilString);
  delay(fetchingIntervalPeriod);
}
