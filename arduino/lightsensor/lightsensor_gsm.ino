#include <GSM.h>
#include "plotly_streaming_gsm.h"

int photoresistor_pin = A0; //analog pin 0

// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
#define nTraces 2
// View your tokens here: https://plot.ly/settings
// Supply as many tokens as data traces
// e.g. if you want to ploty A0 and A1 vs time, supply two tokens
char *tokens[nTraces] = {"token_1", "token_2"};
// arguments: username, api key, streaming token, filename
plotly graph("plotly_username", "plotly_api_key", tokens, "your_filename", nTraces);

void gsm_connect(){
  // ...
}

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  gsm_connect();

  bool success;
  success = graph.init();
  if(!success){while(true){}}
  graph.openStream();
}

unsigned long x;
int y;

void loop() {
  int sensor_reading = analogRead(photoresistor_pin);
  graph.plot(millis(), sensor_reading, tokens[0]);
}
