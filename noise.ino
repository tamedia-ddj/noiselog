// Die nötigen Erweiterungen werden geladen.
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Wire.h>

// Der Internetzugang wird konfiguriert.
const char* ssid     = "XXXXX";
const char* password = "XXXXX";

// Falls die Daten auf den Server übermittelt werden: Hier wird die Internetadresse des Servers eingetragen,
// auf dem das Empfangsskript läuft (siehe PHP-Datei).
const char* host = "XXXXX";
const char* streamId   = "noiselog.php";

// Definieren eines Namens für den Soundsensor. 
const char* sensor = "nameofthesensor";

// Voreinstellungen für die Tonaufzeichnung. 
const int sampleWindow = 1000; // Die Breite des Samplefensters in Millisekunden wird definiert (50 mS = 20Hz).
unsigned int sample;

void setup() {
  Serial.begin(57600);
  delay(10);

  // Eine Verbindung zum WLAN-Zugangsknoten wird aufgebaut. 
  Serial.print("Verbindung aufbauen mit ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  int value = 0;
}

void loop() {

// Der Schallpegel wird gemessen. 

   unsigned long startMillis = millis();
   unsigned int peakToPeak = 0;
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample; 
         }
         else if (sample < signalMin)
         {
            signalMin = sample; 
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts

   float noise = (100 * volts);
   Serial.println(100 * volts);

  delay(15000);

// Der Messwert wird via das WLAN an den Server geschickt.

  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Die Adresse für den Postrequest wird kreiert.
  String url = "/noiselog/";
  url += streamId;
  url += "?";
  url += "sensor=";
  url += sensor;
  url += "&noise=";
  url += noise;

  Serial.print("URL: ");
  Serial.println(url);
  
  // Die Daten werden geschickt. 
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
  
  // Die Rückmeldung des Servers wird empfangen und ausgegeben. 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Verbindung wird getrennt.");

}
