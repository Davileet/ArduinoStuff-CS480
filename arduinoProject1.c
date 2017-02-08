/*Project 1 - CS 480
 * 
 * David Thompson
 * September 26, 2016
 * 
 * Program used to control vairous sensors and LEDs with the Arduino.
 */

#include <dht.h>
dht DHT;
#define DHT11_PIN 2

const int greenLed5 = 13;
const int greenLed4 = 12;
const int greenLed3 = 11;
const int greenLed2 = 10;
const int greenLed1 = 9;
const int redLed = 8;

const int potentPin = A0;
const int photoPin = A1;
const int pinDHT11 = A2;
const int pirPin = 2;
const int switchPin = 3;

int state = LOW;
int pirVal = 0;

long unsigned int pause = 5000;  
long unsigned int lowIn;  
boolean lockLow = true;
boolean takeLowTime;  

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
  delay(500); //Delay to let system boot.

  //Set LEDs as output objects.
  pinMode(greenLed5, OUTPUT);
  pinMode(greenLed4, OUTPUT);
  pinMode(greenLed3, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(greenLed1, OUTPUT);
  pinMode(redLed, OUTPUT);
  
  analogReference(DEFAULT);

  //Set our input devices from the potentiometer and the switch.
  pinMode(potentPin,INPUT);
  pinMode(switchPin, INPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  
  Serial.println("Enter T to read from thermistor, or L to read from photoresistor.");
}

// the loop routine runs over and over again forever:
void loop() {
  //Get the values from potentiometer and photoresister and set them to integers
  int potentpirValue = analogRead(A0);
  int photopirValue = analogRead(A1);
  int val = analogRead(A2);
                          

  //If a character is available to grab in serial monitor then read it.
  if (Serial.available()) {
    char ch = Serial.read();

    //If letter entered is T flash once and read temperature from sensor and display.
    if (ch == 'T' || ch == 't') {
      //Single flash
      digitalWrite(redLed, HIGH);
      delay(350);
      digitalWrite(redLed, LOW);
      delay(500);

      //LED on while reading temp.
      digitalWrite(redLed, HIGH);
      delay(2000);
      
      int chk = DHT.read11(DHT11_PIN);
      Serial.print("Temperature = ");
      Serial.println(DHT.temperature);
      Serial.print("Humidity = ");
      Serial.println(DHT.humidity);
      
      delay(1000);
      digitalWrite(redLed, LOW);
    }

    //If character entered is an L, flash twice and read from photoresistor. 
    if (ch == 'L' || ch == 'l') {  
      //Two flashes    
        digitalWrite(redLed, HIGH);
        delay(250);
        digitalWrite(redLed,LOW);
        delay(250);
        digitalWrite(redLed,HIGH);
        delay(250);
        digitalWrite(redLed,LOW);
        delay(500);

        //LED on while reading
        digitalWrite(redLed, HIGH);

        //Low light situation.
        if(photopirValue < 530) {
          digitalWrite(redLed, HIGH);
          Serial.println("Low Lighting!");
          delay(2000);
        }

        //Bright light situation.
        else {
          digitalWrite(redLed, HIGH);
          Serial.println("Bright Lighting!");
          delay(2000);
        }
        
        digitalWrite(redLed,LOW);
    }

    //Else a letter was entered that was not recognized.
    else {
      digitalWrite(redLed, HIGH);
      delay(1000);
      digitalWrite(redLed,LOW);
      delay(1000);
      digitalWrite(redLed,HIGH);
      delay(1000);
      digitalWrite(redLed,LOW);
    }
  }

//If the switch is flipped to one side.
if (digitalRead(switchPin) == HIGH) {
  
       if(digitalRead(pirPin) == HIGH){
          digitalWrite(greenLed1, HIGH);   
          digitalWrite(greenLed2, HIGH);
          digitalWrite(greenLed3, HIGH);
          digitalWrite(greenLed4, HIGH);
          digitalWrite(greenLed5, HIGH);   //the led visualizes the sensors output pin state

            if(lockLow){  //makes sure we wait for a transition to LOW before any further output is made:
              lockLow = false;            
              Serial.print("motion detected");
              delay(50);
         }         
         takeLowTime = true;
       }

        if(digitalRead(pirPin) == LOW){       
          digitalWrite(greenLed1, LOW);   
          digitalWrite(greenLed2, LOW);
          digitalWrite(greenLed3, LOW);
          digitalWrite(greenLed4, LOW);
          digitalWrite(greenLed5, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
    } 

//If switch is on the other side
if (digitalRead(switchPin) == LOW) {

   //Various potentiometer values and the LEDs that must be on accordingly.
    if (potentpirValue < 11) {
    digitalWrite(greenLed1, LOW);   
    digitalWrite(greenLed2, LOW);
    digitalWrite(greenLed3, LOW);
    digitalWrite(greenLed4, LOW);
    digitalWrite(greenLed5, LOW);
    }
    else if (potentpirValue > 10 && potentpirValue < 201) {
      digitalWrite(greenLed1, HIGH);   
      digitalWrite(greenLed2, LOW);
      digitalWrite(greenLed3, LOW);
      digitalWrite(greenLed4, LOW);
      digitalWrite(greenLed5, LOW);
    }
    else if (potentpirValue > 200 && potentpirValue < 401) {
      digitalWrite(greenLed1, HIGH);   
      digitalWrite(greenLed2, HIGH);
      digitalWrite(greenLed3, LOW);
      digitalWrite(greenLed4, LOW);
      digitalWrite(greenLed5, LOW);
    }
    else if (potentpirValue > 400 && potentpirValue < 601) {
      digitalWrite(greenLed1, HIGH);   
      digitalWrite(greenLed2, HIGH);
      digitalWrite(greenLed3, HIGH);
      digitalWrite(greenLed4, LOW);
      digitalWrite(greenLed5, LOW);
    }
    else if (potentpirValue > 600 && potentpirValue < 801) {
      digitalWrite(greenLed1, HIGH);   
      digitalWrite(greenLed2, HIGH);
      digitalWrite(greenLed3, HIGH);
      digitalWrite(greenLed4, HIGH);
      digitalWrite(greenLed5, LOW);
    }
    else if (potentpirValue > 800) {
      digitalWrite(greenLed1, HIGH);   
      digitalWrite(greenLed2, HIGH);
      digitalWrite(greenLed3, HIGH);
      digitalWrite(greenLed4, HIGH);
      digitalWrite(greenLed5, HIGH);
    }
  }
}
