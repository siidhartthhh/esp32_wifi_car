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
<html>
<head>
    <meta name="viewport" content="width= device-width, intial-scale=1">
    <title>ESP32 Car Controler</title>

</head>
<body>
        <h1>ESP Car Remote </h1.>
        <div  class = "slider-bar">
         <div class = "track">
            <label>left</label>
             <input type = "range" min = "-200" max="200" value = "0" oninput ="sendData()" onchange ="reseLeftSlider()">
         </div>
         <div class = "track">
            <label>right</label>
             <input type = "range" min = "-200" max="200" value = "0" oninput ="sendData()" onchange ="reseRightSlider()">
            </div>
        </div>

    
</body>
</html>





)rawliteral";