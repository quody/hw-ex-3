#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define SECOND 1000000
 
 
//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiSSID[] = "SSID";
const char WiFiPSK[] = "PASS";
 
//////////////////////
//   Server config  //
//////////////////////
const char host[] = "POST ADDRESS";
 
void setup()
{
  Serial.begin(9600);
  connectWiFi();
}
 
void loop()
{
  delay(500);
  senddata();
  //Add some delay so that the ESP has time to complete sending data before goign to sleep
  delay(500); 
  Serial.println("Going to sleep");
  //Sleep one hundred seconds. Note that the sleep time is given in microseconds (10^-6)
  ESP.deepSleep(100*SECOND, WAKE_RF_DEFAULT);
  delay(500);
}
 
void senddata()
{
  WiFiClient client;
  Serial.println("Send post request");
  HTTPClient http;
  http.begin(host);
  //Add some metadata
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("REQUEST_URI", "/post");
  http.addHeader("REQUEST_METHOD", "POST");
  //Do the actual post request
  int httpCode = http.POST("value=1&id=\"TestID\"");
  Serial.println("Return value");
  Serial.println(httpCode);
  http.writeToStream(&Serial);
  http.end();
  Serial.print("End of posting");
}
 
void connectWiFi()
{
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WiFiSSID, WiFiPSK);
 
  // Use the WiFi.status() function to check if the ESP8266
  // is connected to a WiFi network.
  while (WiFi.status() != WL_CONNECTED)
  {
    // Delays allow the ESP8266 to perform critical tasks
    // defined outside of the sketch. These tasks include
    // setting up, and maintaining, a WiFi connection.
    delay(100);
    // Potentially infinite loops are generally dangerous.
    // Add delays -- allowing the processor to perform other
    // tasks -- wherever possible.
  }
  Serial.print("Connected to wifi");
}