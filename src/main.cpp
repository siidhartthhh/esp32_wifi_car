// Include necessary libraries
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <WebServer.h>

//declaring the func i mad below
void parseData(char* data);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);


// initialize the WebSocket server

WebSocketsServer webSocket(81);


//wifi settings
const char* ssid = "ESP32_CAR";
const char* password = "12345678";

//code for the web based controler that it to be run on the esp
const char index_html[] PROGMEM = R"rawliteral(
 
<!DOCTYPE HTML>
<html>
<head>
        <meta name="viewport" content="width=device-width, initial-scale=1"?>
        <title>ESP Car Controler</title>
    <style>
        body
        {
            background-color: #A9A9A9;
            color: #fff;
            font-family: sans-serif;
            text-align: center;
            margin: 0:
            padding: 20px;
        }

        .controlerSliderBox
        {
            display: flex;
            justify-content: space-around;
            margin-top: 35px;
        }

        .controlerSlider
        {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        input[type=range]
        {
            appearance: slider-vertical;
            width: 50px;
            height: 250px;
            margin-top: 15px;
        }
    </style>    
</head>
<body>
        <h2>ESP Car Controler</h2>
         
       <div class="controlerSliderBox">
          <div class="controlerSlider">
            <label>LEFT</label>
            <input type="range" id="leftControl" min="-250" max="250" value="0" oninput="sendData()" onchange="resetSlider('leftControl')">
          </div>
          
          <div class="controlerSlider">
            <label>RIGHT</label>
            <input type="range" id="rightControl" min="-250" max="250" value="0" oninput="sendData()" onchange="resetSlider('rightControl')">
          </div>
       </div>     



       <script>

            var socket= new WebSocket('ws://' +window.location.hostname+ ':81/');
            

            function sendData()
            {
                var l = document.getElementById('leftControl').value;
                var r = document.getElementById('rightControl').value;

                socket.send(l+','+ r);
            }

            function resetSlider(id)
            {
                document.getElementById(id).value = 0;
                sendData();
            }

       </script>
</body>
</html>





)rawliteral";

// variable for the left and right analog speed value
int leftspeed =0;
int rightspeed =0;

// pins for the left side motors
const int LM_in1 = 12;
const int LM_in2 = 13;
const int LM_Speed = 14;
//pins for the right side motors
const int RM_in1= 11;
const int RM_in2= 10;
const int RM_Speed= 9;

void setup()
{

    Serial.begin(115200);


    //setting up pins
    pinMode(LM_in1, OUTPUT);
    pinMode(LM_in2, OUTPUT);
    pinMode(LM_Speed,OUTPUT);
    pinMode(RM_in1, OUTPUT);
    pinMode(RM_in2, OUTPUT);
    pinMode(RM_Speed, OUTPUT);

    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());

    webSocket.begin();
   webSocket.onEvent(webSocketEvent);

}

void loop()
{

     webSocket.loop();

}






 void parseData(char* data)
    {

        char* commaPosition = strchr(data, ',');

        if  (commaPosition !=NULL)
        {
            *commaPosition ='/0';


            leftspeed = atoi(data);
            rightspeed = atoi(commaPosition + 1);
        }    

            Serial.print("left;");
            Serial.print(leftspeed);
            Serial.print("right;");
            Serial.println(rightspeed);

        

    }

   void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length)
   {

    switch (type)
    {
        case WStype_CONNECTED:
        Serial.println("connecte");
        break;

        case WStype_DISCONNECTED:
        Serial.println("disconnectedd");
        break;

        case WStype_TEXT:
        parseData((char*) payload);
        break;

    }



   }
