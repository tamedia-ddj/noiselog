// **************
// Include for WLAN
// **************

#include <ESP8266WiFi.h>

// Config the Wifi Access.
const char* ssid     = "XXXXX";
const char* password = "XXXXX";

// Config the URL.
const char* host = "XXXXX";
const char* streamId   = "noiselog.php";

const char* sensor = "nameofthesensor";

// **************
// Include for the Sensor
// **************

#include <Arduino.h>
#include <Wire.h>

// **************
// Definition for noise level monitoring
// **************

const int sampleWindow = 1000; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {

// **************
// Setup for WLAN
// **************

  Serial.begin(57600);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

int value = 0;
}
void loop() {

// **************
// Mesure the noise level
// **************

   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts

   float noise = (100 * volts);
   Serial.println(100 * volts);



  delay(15000);

// **************
// Send the data over the Wifi to the server
// **************

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/noiselog/";
  url += streamId;
  url += "?";
  url += "sensor=";
  url += sensor;
  url += "&noise=";
  url += noise;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");

}
