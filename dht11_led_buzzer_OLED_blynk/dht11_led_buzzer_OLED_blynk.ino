/*---------------------KRENOVATOR---------------------
  TEMPERATURE and HUMIDITY SENSOR + LED + BUZZER + OLED
  display

  Demonstrates the DHT11 or DHT22 to know its function
  and how to code it with the trigger of LED and
  buzzer. The temperature and humidity will display
  in OLED display

  Get the code at github
  https://github.com/MZulsyahmi/dht11.git

  by M.Zulsyahmi @krenovator
  October 2018
 */

#include "DHT.h"      //include the library of DHT

/*the library for OLED display*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN 0
#define DHTTYPE DHT22
#define buzzer 14
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bf35ecd434294451aa751f48da63af5d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WorstGeneration";
char pass[] = "getnewone";

DHT dht(DHTPIN,DHTTYPE);

int ledG = 15;
int ledY = 13;
int ledR = 12;

WidgetLED red(V1);
WidgetLED yellow(V2);
WidgetLED green(V3);

void setup() {
  Serial.println("Device Started");
  Serial.println("-----------------------------");
  Serial.println("Running DHT!");
  Serial.println("-----------------------------");
  
  Blynk.begin(auth, ssid, pass);

  display.clearDisplay();

  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  pinMode(ledR,OUTPUT);
  pinMode(ledY,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(buzzer,OUTPUT);

  // Clear the buffer/display
  display.clearDisplay();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);

  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print(t);
  display.print(" C");

  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.setTextSize(2);
  display.print(h);
  display.print(" %");
  display.display();
  
  if(t>=20 && t<26){
    digitalWrite(ledG,HIGH);
    digitalWrite(ledY,LOW);
    digitalWrite(ledR,LOW);
    digitalWrite(buzzer,LOW);

    red.off();
    yellow.off();
    green.on();
  }

  else if(t>=26 && t<30){
    digitalWrite(ledG,LOW);
    digitalWrite(ledY,HIGH);
    digitalWrite(ledR,LOW);
    digitalWrite(buzzer,LOW);

    red.off();
    yellow.on();
    green.off();
  }

  else if(t>=30){
    digitalWrite(ledG,LOW);
    digitalWrite(ledY,LOW);
    digitalWrite(ledR,HIGH);
    digitalWrite(buzzer,HIGH);

    red.on();
    yellow.off();
    green.off();
  }
  display.clearDisplay();
  Blynk.run();
}
