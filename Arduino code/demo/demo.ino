// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License
//
// This example shows how to deserialize a JSON document with ArduinoJson.
//
// https://arduinojson.org/v6/example/parser/

#include <ArduinoJson.h>
#include <AtWiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
const int lcd_pixel_width = 320;
const int lcd_pixel_height = 240;

const char* ssid = "yourssid";
const char* password =  "yourpassword";

void setup() {

  //lcd init
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(lcd_pixel_width / 2, lcd_pixel_height / 2, 100, TFT_GREEN);

  //serial init
  Serial.begin(115200);
  while (!Serial); // Wait for Serial to be ready
  delay(1000);

  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP Address: ");
  Serial.println (WiFi.localIP()); // prints out the device's IP address
}


void loop() {
  const uint16_t port = 5000; // Default port
  const char* host = "192.168.6.65";  // Target Server IP Address
  Serial.print("Connecting to ");
  Serial.println(host);

  while (1) {
    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("Connection failed.");
      Serial.println("Waiting 5 seconds before retrying...");
      delay(5000);
      return;
    }

    // This will send a request to the server
    //uncomment this line to send an arbitrary string to the server
    //client.print("Send this data to the server");
    //uncomment this line to send a basic document request to the server
    client.print("GET / HTTP/1.1\n\n"); // sending HTTP GET request
    int maxloops = 0;
    //wait for the server's reply to become available
    while (!client.available() && maxloops < 1000) {
      maxloops++;
      delay(1); //delay 1 msec
    }
    if (client.available() > 0) {
      //read back one line from the server
      String line = client.readString(); // Read from the server response
      // Proceed various line-endings
      line.replace("\r\n", "\n");
      line.replace('\r', '\n');
      line.replace("\n", "\r\n");
      Serial.print(line);
      Serial.println("start json processing...");
      jsonParser(line);
    } else {
      Serial.println("client.available() timed out ");
    }

    Serial.println("Closing connection.");
    client.stop();

    Serial.println("Waiting 2 seconds before restarting...");
    delay(2000);
  }
}

int jsonParser(String line) {
  int jsonPosition = line.indexOf("json");
  if (jsonPosition != -1) {
    line = line.substring(jsonPosition + 4, line.length());
    //Serial.println(line);
    StaticJsonDocument<200> json_msg;
    char json[line.length() + 1] = "null";
    line.toCharArray(json, line.length() + 1);
    Serial.println(json);
    DeserializationError error = deserializeJson(json_msg, json);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return 0;
    }
    String color = json_msg["color"];
    Serial.print("color:");
    Serial.println(color);
    jsonCommandProcessing(color);
  }
}

int jsonCommandProcessing(String color){
  if(color == "blue"){
      tft.fillCircle(lcd_pixel_width / 2, lcd_pixel_height / 2, 100, TFT_BLUE);
      Serial.println("change color to blue...");
  }
  if(color == "green"){
      tft.fillCircle(lcd_pixel_width / 2, lcd_pixel_height / 2, 100, TFT_GREEN);
      Serial.println("change color to green...");
  }
}
