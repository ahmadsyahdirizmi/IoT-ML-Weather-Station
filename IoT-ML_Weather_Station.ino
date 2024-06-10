#include "DHT.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Pin definitions
#define DHTPIN D5
#define DHTTYPE DHT11
#define BMP_SCK  13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS   10
#define LED_PIN D7

// Picture definitions
// Definisi gambar
const uint8_t gambarHujan[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x03, 0xb8, 0x00, 0x00, 0x06, 0x04, 0x00, 
	0x00, 0x7c, 0x06, 0x00, 0x00, 0xc0, 0x02, 0x00, 0x00, 0x80, 0x03, 0x80, 0x01, 0x80, 0x00, 0xc0, 
	0x03, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x10, 
	0x08, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x60, 0x03, 0xff, 0xff, 0xc0, 
	0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xc6, 0x00, 0x00, 0x39, 0xce, 0x00, 
	0x00, 0x4a, 0x5a, 0x00, 0x00, 0x7b, 0xda, 0x00, 0x00, 0x31, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

const uint8_t gambarCerah[] PROGMEM = {
  
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x03, 0x00, 0x00, 0x80, 
	0x01, 0x81, 0x81, 0x80, 0x00, 0xcf, 0xf3, 0x00, 0x00, 0x1f, 0xfa, 0x00, 0x00, 0x38, 0x1c, 0x00, 
	0x00, 0x70, 0x0e, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0xe0, 0x06, 0x00, 0x1e, 0xe0, 0x07, 0xf8, 
	0x1e, 0xe0, 0x07, 0x78, 0x00, 0xe0, 0x06, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x70, 0x0e, 0x00, 
	0x00, 0x38, 0x1c, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0xcf, 0xf3, 0x00, 0x00, 0xc1, 0x03, 0x80, 
	0x01, 0x81, 0x01, 0x80, 0x01, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

const uint8_t gambarBerawan[] PROGMEM = {
  
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0xe0, 0x70, 0x00, 
	0x01, 0xc0, 0x38, 0x00, 0x03, 0x80, 0x1c, 0x00, 0x03, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x3f, 0x00, 
	0x06, 0x00, 0x7f, 0x80, 0x0e, 0x00, 0xe1, 0xc0, 0x3e, 0x01, 0xc0, 0x60, 0x70, 0x03, 0x80, 0x70, 
	0x60, 0x03, 0x00, 0x3c, 0xc0, 0x07, 0x00, 0x0e, 0xc0, 0x0f, 0x00, 0x06, 0xc0, 0x18, 0x00, 0x03, 
	0xc0, 0x30, 0x00, 0x03, 0x60, 0x30, 0x00, 0x03, 0x70, 0x30, 0x00, 0x03, 0x3f, 0xf0, 0x00, 0x07, 
	0x1f, 0xf8, 0x00, 0x0e, 0x00, 0x1f, 0xe6, 0x7c, 0x00, 0x07, 0xe6, 0x78, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

// WiFi credentials
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Firebase configuration
#define API_KEY "your_api_key"
#define DATABASE_URL "your_database_url"

// Global variables
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
String fireStatus1;
String fireStatus2;

void setup() {
  pinMode(DHTPIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Firebase configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Sign up to Firebase
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign-up successful");
    signupOK = true;
  } else {
    Serial.printf("Firebase sign-up failed: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; // Token generation callback

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.RTDB.setString(&fbdo, "LED_STATUS", "0");
  Firebase.RTDB.setString(&fbdo, "cuaca", "0");

  // Initialize BMP280 sensor
  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");
    while (1) delay(10);
  }

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  // Read sensor data
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp.readPressure();
  float a = bmp.readAltitude(1013.25);

  if(Firebase.RTDB.getString(&fbdo,"LED_STATUS")){
      if (fbdo.dataType()=="string"){
        fireStatus1 = fbdo.stringData();
        int l =fireStatus1.toInt();
        Serial.println(a);
        if (l == 1) 
        {                                                          // compare the input of led status received from firebase
          Serial.println("Led Turned ON");                                                        
          digitalWrite(LED_PIN, HIGH);    
        }
        else  
        {                                                  // compare the input of led status received from firebase
          Serial.println("Led Turned OFF");
          digitalWrite(LED_PIN, LOW);                                                         // make external led OFF
        }
      }
    }

// Display data to Oled
  if(Firebase.RTDB.getString(&fbdo,"cuaca")){
      if (fbdo.dataType()=="string"){
        fireStatus2 = fbdo.stringData();
        int c =fireStatus2.toInt();
        if (c == 0) 
        {                                                          // compare the input of led status received from firebase
          Serial.println("Hujan");                                                        
          displayPicture(gambarHujan, "Hujan", t, h);    
        }
        else if(c == 1)  
        {                                                  // compare the input of led status received from firebase
          Serial.println("Berawan");
          displayPicture(gambarBerawan, "Berawan", t, h);                                                         // make external led OFF
        }
        else{
          Serial.println("Cerah");
          displayPicture(gambarCerah, "Cerah", t, h);
        }
      }
    }
    displayData("Pressure:", p/1000, "KPa",
              "Altitude:", a, "m");
    
  // Send data to Firebase
  if (Firebase.ready() && signupOK ) {
    
    if (Firebase.RTDB.setFloat(&fbdo, "data/zero/0/humi",h)){
//      Serial.println("PASSED");
       Serial.print("Humidity: ");
       Serial.println(h);
      
    }
    else {
      Serial.println("FAILED Humi");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "data/zero/0/temp", t)){
//      Serial.println("PASSED");
       Serial.print("Temperature: ");
       Serial.println(t);
    }
    else {
      Serial.println("FAILED temp");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    
    if (Firebase.RTDB.setFloat(&fbdo, "data/zero/0/press", p)){
//      Serial.println("PASSED");
       Serial.print("Pressure: ");
       Serial.println(p);
    }
    else {
      Serial.println("FAILED press");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    if (Firebase.RTDB.setFloat(&fbdo, "data/zero/0/alt", a)){
//      Serial.println("PASSED");
       Serial.print("Altitude: ");
       Serial.println(a);
    }
    else {
      Serial.println("FAILED alt");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }

  Serial.println("______________________________");
}

void displayPicture(const uint8_t* gambar, String c, int t, int h) {
  display.clearDisplay();
  display.drawBitmap(3, 0, gambar, 32, 32, WHITE);
  display.setTextSize(2);
  display.setCursor(40, 10);
  display.print(c);
  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print(" ____________________");
  display.setTextSize(2);
  display.setCursor(4,45);
  display.print(t);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  display.setCursor(64,45);
  display.print("  ");
  display.print(h);
  display.print("%");
  display.display();
  delay(2500);
}

void displayData(const char* label1, float value1, const char* unit1, const char* label2, float value2, const char* unit2){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(label1);
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(value1);
  display.print(" ");
  display.setTextSize(2);
  display.print(unit1);
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print(label2);
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(value2);
  display.print(" ");
  display.setTextSize(2);
  display.print(unit2);
  display.display();
  delay(1500);
}