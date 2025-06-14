#include <Adafruit_MAX31865.h>
//use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 bbq_sensor = Adafruit_MAX31865(15);
Adafruit_MAX31865 meat_sensor = Adafruit_MAX31865(5);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      4300.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  1000.0


//display setup
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include "Fonts/FreeSans18pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"

const uint8_t bbq_stearing[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0x07, 0xe4, 0x00, 0x0f, 0xec, 0x00, 0x0f, 0xfc, 0x00, 0x1f, 0xfe, 0x00, 0x1f, 0xfe, 0x00, 0x1e, 0xfe, 0x00, 0x1e, 0x7e, 0x00, 0x0e, 0x3e, 0x00, 0x0e, 0x1c, 0x00, 0x07, 0x1c, 0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00};
const uint8_t bbq_smoking[] = {0x01, 0x00, 0x03, 0x00, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0xc0, 0x07, 0xe0, 0x03, 0xf0, 0x03, 0xf0, 0x09, 0xf8, 0x18, 0xf8, 0x1c, 0x78, 0x0c, 0x78, 0x0e, 0x70, 0x04, 0x70, 0x04, 0x40};
const uint8_t bbq_grilling[] = {0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x0e, 0x00, 0x06, 0x17, 0x00, 0x23, 0x2b, 0x80, 0x11, 0x35, 0x00, 0x19, 0x3a, 0x00, 0x0f, 0x3c, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x00, 0x01, 0x20, 0x00, 0x06, 0x18, 0x00, 0x0e, 0x1c, 0x00, 0x1c, 0x0e, 0x00, 0x38, 0x07, 0x00, 0x70, 0x03, 0x80, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00};
const uint8_t bbq_baking[] = {0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x1e, 0x78, 0x30, 0x0c, 0x70, 0x0e, 0x60, 0x86, 0x63, 0x86, 0xe3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7, 0x63, 0xc6, 0xe0, 0x07, 0xe0, 0x07, 0xff, 0xff, 0x00, 0x00};


const uint8_t meat_fish[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1f, 0x00, 0x30, 0x7f, 0x70, 0x39, 0xff, 0x58, 0x1f, 0xff, 0x7c, 0x1f, 0xff, 0x7c, 0x39, 0xff, 0x78, 0x30, 0xff, 0x70, 0x00, 0x1f, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t meat_chicken[] = {0x18, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7e, 0x03, 0x00, 0x3f, 0x0f, 0x00, 0x3f, 0x9f, 0x80, 0x3f, 0xdf, 0x00, 0x33, 0xcf, 0x00, 0x38, 0x0f, 0x80, 0x1f, 0x3e, 0x00, 0x1f, 0xfe, 0x00, 0x0f, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x01, 0xc0, 0x00, 0x01, 0x40, 0x00, 0x01, 0x40, 0x00, 0x07, 0x80, 0x00};
const uint8_t meat_pig[] = {0x00, 0x00, 0xf1, 0x8f, 0x8f, 0xf1, 0x98, 0x19, 0xb0, 0x0d, 0xe2, 0x47, 0x62, 0x46, 0x40, 0x02, 0x43, 0xc2, 0x46, 0x62, 0x65, 0xa6, 0x26, 0x64, 0x33, 0xcc, 0x1c, 0x38, 0x07, 0xe0, 0x00, 0x00};
const uint8_t meat_sheep[] = {0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x07, 0x38, 0x00, 0x08, 0x04, 0x00, 0x18, 0x06, 0x00, 0x20, 0x01, 0x00, 0x34, 0xc9, 0x00, 0x3f, 0xff, 0x00, 0x28, 0x05, 0x00, 0x69, 0x25, 0x80, 0x48, 0x04, 0x80, 0xf8, 0x07, 0xc0, 0x0c, 0xcc, 0x00, 0x04, 0xc8, 0x00, 0x04, 0xc8, 0x00, 0x02, 0xd0, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00};
const uint8_t meat_beef[] = {0x80, 0x00, 0x80, 0xe0, 0x03, 0x80, 0x7b, 0xef, 0x00, 0x47, 0xf1, 0x00, 0x27, 0xf2, 0x00, 0x67, 0xf3, 0x00, 0x67, 0xf3, 0x00, 0x03, 0xe0, 0x00, 0x0b, 0xe8, 0x00, 0x0b, 0xe8, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x03, 0xe0, 0x00};
const uint8_t firstscreen[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0xe3, 0xe0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x03, 0xc7, 0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x07, 0x8e, 0x38, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x07, 0x1c, 0x7c, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x0e, 0x38, 0xfe, 0x00, 0x00, 0x00, 0x07, 0x00, 0x1c, 0x71, 0xc7, 0x00, 0x00, 0x80, 0x07, 0xc0, 0x38, 0x63, 0x8f, 0x00, 0x00, 0xc0, 0x03, 0xe0, 0x70, 0xc7, 0x1e, 0x00, 0x00, 0x60, 0x01, 0xe0, 0x61, 0x8e, 0x3c, 0x00, 0x00, 0x30, 0x01, 0xe0, 0x63, 0x1c, 0x78, 0x00, 0x00, 0x18, 0x00, 0xe0, 0x76, 0x38, 0xf0, 0x00, 0x00, 0x1c, 0x00, 0xe0, 0x7c, 0x61, 0xe0, 0x00, 0x00, 0x0f, 0x00, 0xe0, 0x7c, 0xc3, 0xc0, 0x00, 0x00, 0x07, 0x80, 0xe0, 0x7f, 0x87, 0x80, 0x00, 0x00, 0x03, 0xe1, 0xe0, 0x7f, 0x0f, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x7f, 0x9c, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// Declare a global variable to store the meat temperature
int meat_temperature = 0;
int bbq_temperature = 0;

int meat_temperature2 = 68; // FAKE
int bbq_temperature2 = 423; // FAKE



// setup everything to make it online
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "SKY2PYDM"; //setup Wi-Fi
char pass[] = "EzS6jXdTT2p5"; //setup pass
#define BLYNK_TEMPLATE_ID "TMPL5FMb-BCAU"
#define BLYNK_TEMPLATE_NAME "ESP32 Template"
#define BLYNK_AUTH_TOKEN "PxzR3NWBU8wawXP1VbY0KPMy48wj2FhY"
BlynkTimer timer;


// Button setup
const byte interruptPin = 4;
volatile bool state = LOW;
int MeatType = 0;













void setup() {
  Serial.begin(115200);
  pinMode( interruptPin, INPUT_PULLUP );
 attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_button_pressed, FALLING);

  // setup BBQ reading
  bbq_sensor.begin(MAX31865_3WIRE);  
  meat_sensor.begin(MAX31865_3WIRE);  

  // validate that display is conneted
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, TemperatureToCloud);

    display.clearDisplay();
    display.drawBitmap(30, 0, firstscreen, 60, 60, 1);
    display.display();
    delay(2000);


}


void loop() {
  // call temperature reading functions
  read_bbq_temperature();
  read_meat_temperature();
  bbq_display();
  Blynk.run();
  timer.run();
  

    if (state)//if an interrup has occured


        if (digitalRead(interruptPin))//if button is released let ISR set flag.
        {
            attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_button_pressed, FALLING );
            state = false;//reset interrupt flag
        }

            
    }

void ISR_button_pressed(void) 
{
    if (!state)//set flag to low if flag is true
    {
        state = true;//set flag
        detachInterrupt( digitalPinToInterrupt(interruptPin) );
            {
            MeatType++;                     // Increment the mode
    if (MeatType > 4) {             // If the mode is greater than 4, reset it to 0
      MeatType = 0;
    }
        
    }//if
}


}

void read_bbq_temperature() {
  uint16_t rtd_bbq = bbq_sensor.readRTD();
  float ratio_bbq = rtd_bbq;
  ratio_bbq /= 32768;
  bbq_temperature = bbq_sensor.temperature(RNOMINAL, RREF);
  bbq_temperature = bbq_temperature * 1.8 + 32; // Convert to F
  Serial.print("Temperature BBQ = ");
  Serial.println(bbq_temperature);
  delay(80);
}

void read_meat_temperature() {
  // read and print meat temperature
  uint16_t rtd_meat = meat_sensor.readRTD();
  float ratio_meat = rtd_meat;
  ratio_meat /= 32768;
  meat_temperature = meat_sensor.temperature(RNOMINAL, RREF);
  Serial.print("Temperature Meat = ");
  Serial.println(meat_temperature);
  delay(80);
}

void bbq_display() {
    
   display.clearDisplay();
    // Meat temperature
    display.setFont(&FreeSansBold18pt7b);
    display.setTextColor(WHITE);
    display.drawCircle(48, 15, 2, 1);
    display.drawCircle(122, 15, 2, 1);
    display.setCursor(5, 35);

   if (meat_temperature == -242){
    display.print("X");
    }
    else {
    display.print(meat_temperature, 1);
    };




    // BBQ temperature
    display.setCursor(60, 35);


    // if sensor is not connected

    if (bbq_temperature == -403){
    display.print("X");
    }
    else {
    display.print(bbq_temperature, 1);
    };
  

    // BBQ operation type
    display.setFont(NULL);
    display.setCursor(82, 53);
 
 
    if (bbq_temperature >= 0 && bbq_temperature < 250) {
      display.print("Smoking");
      display.drawBitmap(62, 46, bbq_smoking, 16, 16, 1);
      display.fillRoundRect(64, 41, 15, 2, 3, 1);

    } else if (bbq_temperature >= 250 && bbq_temperature < 370) {
      display.print("Baking");
      display.drawBitmap(62, 46, bbq_baking, 16, 16, 1);
      

    } else if (bbq_temperature >= 370 && bbq_temperature < 520) {
      display.print("Grill");
      display.drawBitmap(62, 46, bbq_grilling, 18, 18, 1);
      display.fillRoundRect(64, 41, 40, 2, 3, 1);

    } else if (bbq_temperature >= 520) {
      display.print("Searing");
      display.drawBitmap(62, 46, bbq_stearing, 24, 24, 1);
      display.fillRoundRect(64, 41, 53, 2, 3, 1);

    } else {
      display.print("Error");
    }
   
    //4 gradations of BBQ temperature
    
    display.drawRoundRect(65, 40, 53, 1, 3, 1);
    

    display.fillRect(77, 41, 2, 2, 1);
    display.fillRect(90, 41, 2, 2, 1);
    display.fillRect(103, 41, 2, 2, 1);
    display.fillRect(116, 41, 2, 2, 1);



      // Meat type
   switch (MeatType) {
    case 0:
      display.setCursor(8, 57);
      display.drawBitmap(5, 47, meat_beef, 24, 24, 1);
      display.setCursor(28, 53);
      display.print("48-71");
      break;
    case 1:
      display.setCursor(8, 57);
      display.drawBitmap(5, 47, meat_chicken, 18, 18, 1);
      display.setCursor(28, 53);
      display.print(">79");
      break;
    case 2:
      display.setCursor(8, 57);
      display.drawBitmap(5, 49, meat_pig, 16, 16, 1);
      display.setCursor(28, 53);
      display.print("63-96");
      break;
    case 3:
      display.setCursor(8, 57);    
      display.drawBitmap(5, 45, meat_sheep, 18, 18, 1);
      display.setCursor(28, 53);
      display.print("63-96");
      break;
    case 4:
      display.setCursor(8, 57); 
      display.drawBitmap(4, 45, meat_fish, 24, 24, 1);
      display.setCursor(28, 53);
      display.print(">63");
      break;
  }

  if (Blynk.connected()) {

    //Network
    display.fillRect(127, 0, 1, 8, 1); //1
    display.fillRect(125, 2, 1, 6, 1); //2
    display.fillRect(123, 4, 1, 4, 1); //3
    display.fillRect(121, 6, 1, 2, 1); //4
    }

    // Symbols
    display.setCursor(46, 29);
    display.print("C");
    display.setCursor(120, 29);
    display.print("F");
  
    display.display();

}

void TemperatureToCloud ()
{
  Blynk.virtualWrite(V5, meat_temperature);
  Blynk.virtualWrite(V6, bbq_temperature);
}




