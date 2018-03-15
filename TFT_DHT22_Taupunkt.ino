// First all the DHT22 stuff
// lib for DHT22
#include <DHT.h>

//define input PIN of DHT22 inside (DHTPIN1 to MEGA PIN 11)
//define input PIN of DHT22 outside (DHTPIN2 to MEGA PIN 12)
#define DHTPIN1 11 
#define DHTPIN2 12
#define DHTTYPE DHT22 //DHT11, DHT21, DHT22

   //no idea what this is for
   DHT dht1(DHTPIN1, DHTTYPE);
   DHT dht2(DHTPIN2, DHTTYPE);
   

//this is original Sketch from TFT Demo
#include <Adafruit_GFX.h>
#include <gfxfont.h>

// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.4\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
 
  }

  tft.begin(identifier);

     //Try to insert lines from DHT22 Sketch with no knowledge but good will 
       dht1.begin();
       dht2.begin();

 
}

void loop(void) {
//insert the DT22 stuff
  float h1 = dht1.readHumidity();     //Luftfeuchte auslesen
  float t1 = dht1.readTemperature();  //Temperatur auslesen
  float h2 = dht2.readHumidity();     //Luftfeuchte auslesen
  float t2 = dht2.readTemperature();  //Temperatur auslesen
  //reducing delta of sensors by correction of lower value. 
  float kt1 = t1 * 1.0245;
  float kh1 = h1 * 0.95;
  float kh2 = h2 * 0.95;

  //build string from text + value
  String S1 = "1: ";
  String B = " ";
  String S2 = "2: ";
  String all1 = S1 + kt1 + B + kh1;
  String all2 = S2 + t2 + B + kh2;
  
  //tft stuff from original sketch
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("   Temp.  Hum.  DP");
  tft.println();
  tft.println(all1);
  tft.println();
  tft.println(all2);
  
  delay(5000);
}
