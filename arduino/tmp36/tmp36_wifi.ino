#include <WiFi.h>
#include "plotly_streaming_wifi.h"

#define tmp36sensor_pin 0

// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
#define nTraces 1
// View your tokens here: https://plot.ly/settings
// Supply as many tokens as data traces
// e.g. if you want to ploty A0 and A1 vs time, supply two tokens
char *tokens[nTraces] = {"25tm9197rz"};
// arguments: username, api key, streaming token, filename
plotly graph("workshop", "v6w5xlbx9j", tokens, "filename", nTraces);



int status = WL_IDLE_STATUS;     // the Wifi radio's status
char ssid[] = "wifi_network_name"; //  your network SSID (name)
char pass[] = "wifi_network_password"; // // your network password

void wifi_connect(){
    // attempt to connect using WPA2 encryption:
    Serial.println("... Attempting to connect to WPA network...");
    status = WiFi.begin(ssid, pass);
    // if you're not connected, stop here:
    if ( status != WL_CONNECTED) {
      Serial.println("... Couldn't get a WiFi connection, trying again");
      wifi_connect();
    }
    // if you are connected, print out info about the connection:
    else {
      Serial.println("... Connected to network");
    }
}

void setup() {
  graph.maxpoints = 100;
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  wifi_connect();

  bool success;
  success = graph.init();
  if(!success){while(true){}}
  graph.openStream();
}

void loop() {
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(tmp36sensor_pin);
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  float temperatureC = (voltage - 0.5) * 100;
  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  graph.plot(millis(), temperatureC, tokens[0]);
  delay(500);
}
