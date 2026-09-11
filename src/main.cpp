// Include necessary libraries
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <WebServer.h>


// initialize the web server and WebSocket server
WebServer server(80);
WebSocketsServer webSocket(81);


//wifi settings
const char* ssid = "ESP32_CAR";
const char* password = "12345678";


const char index_html[] PROGMEM = R"rawliteral(
 
<!DOCTYPE HTML>





)rawliteral";