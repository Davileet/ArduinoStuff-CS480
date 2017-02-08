#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

const int greenLED = A1;
//const int pinDHT11 = A0;

union {
byte tempByte[sizeof(float)];
float temp;
} temperature;

float myTemp = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t) || isnan(f)) {
   Serial.println("Failed to read from DHT sensor!");
   return;
    }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 if (Serial.available() > 0){
      char data = Serial.read();
//    }


  if(data == 'n'){
      digitalWrite(greenLED, LOW);
    }

  if(data == 'y'){
      digitalWrite(greenLED, HIGH);

      temperature.temp = f;

      Serial.print(temperature.temp);
      Serial.flush();
    }
 }

}
