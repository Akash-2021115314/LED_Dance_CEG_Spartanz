// // Import required libraries
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <FastLED.h>
// #include <ESPmDNS.h>

// #define INTERNAL_LED 2 
// // Replace with your network credentials
// const char* ssid = "Sourav";
// const char* password = "sourav123";
// // const char* ssid = "Sourav";
// // const char* password = "sourav123";

// bool ledState = 0;
// const int ledPin = 2;

// // Create AsyncWebServer object on port 80
// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html>
//   <head>
//     <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
//     <title>ESP32 WebSocket Server</title>
//     <style>
//     html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
//     body{margin-top: 50px;}
//     h1{color: #444444;margin: 50px auto;}
//     p{font-size: 19px;color: #888;}
//     #state{font-weight: bold;color: #444;}
//     .switch{margin:25px auto;width:80px}
//     .toggle{display:none}
//     .toggle+label{display:block;position:relative;cursor:pointer;outline:0;user-select:none;padding:2px;width:80px;height:40px;background-color:#ddd;border-radius:40px}
//     .toggle+label:before,.toggle+label:after{display:block;position:absolute;top:1px;left:1px;bottom:1px;content:""}
//     .toggle+label:before{right:1px;background-color:#f1f1f1;border-radius:40px;transition:background .4s}
//     .toggle+label:after{width:40px;background-color:#fff;border-radius:20px;box-shadow:0 2px 5px rgba(0,0,0,.3);transition:margin .4s}
//     .toggle:checked+label:before{background-color:#4285f4}
//     .toggle:checked+label:after{margin-left:42px}
//     </style>
//   </head>
//   <body>
//     <h1>ESP32 WebSocket Server</h1>
//     <div class="switch">
//       <input id="toggle-btn" class="toggle" type="checkbox" %CHECK%>
//       <label for="toggle-btn"></label>
//     </div>
//     <p>On-board LED: <span id="state">%STATE%</span></p>

//     <script>
// 	  window.addEventListener('load', function() {
// 		var websocket = new WebSocket(`ws://${window.location.hostname}/ws`);
// 		websocket.onopen = function(event) {
// 		  console.log('Connection established');
// 		}
// 		websocket.onclose = function(event) {
// 		  console.log('Connection died');
// 		}
// 		websocket.onerror = function(error) {
// 		  console.log('error');
// 		};
// 		websocket.onmessage = function(event) {
// 		  if (event.data == "1") {
// 			document.getElementById('state').innerHTML = "ON";
// 			document.getElementById('toggle-btn').checked = true;
// 		  }
// 		  else {
// 			document.getElementById('state').innerHTML = "OFF";
// 			document.getElementById('toggle-btn').checked = false;
// 		  }
// 		};
		
// 		document.getElementById('toggle-btn').addEventListener('change', function() { websocket.send('toggle');
//       fetch("http://spartanz1.local/request");
      
    
//      });
// 	  });
// 	</script>
//   </body>
// </html>
// )rawliteral";

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
//   AwsFrameInfo *info = (AwsFrameInfo*)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//     data[len] = 0;
//     if (strcmp((char*)data, "toggle") == 0) {
//       ledState = !ledState;
//       ws.textAll(String(ledState));
//     }
//   }
// }

// void eventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
//   switch (type) {
//     case WS_EVT_CONNECT:
//       Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//       break;
//     case WS_EVT_DISCONNECT:
//       Serial.printf("WebSocket client #%u disconnected\n", client->id());
//       break;
//     case WS_EVT_DATA:
//       handleWebSocketMessage(arg, data, len);
//       //digitalWrite(ledPin, ledState);
//       break;
//     case WS_EVT_PONG:
//     case WS_EVT_ERROR:
//       break;
//   }
// }

// String processor(const String& var){
//   if(var == "STATE"){
//       return ledState ? "ON" : "OFF";
//   }
//   if(var == "CHECK"){
//     return ledState ? "checked" : "";
//   }
//   return String();
// }


// // //FastLED setup 

// #define NUM_LEDS  100
// #define LED_PIN   2

// CRGB leds[NUM_LEDS];



// // IPAddress staticIP(192,168,204,195) ; 
// // IPAddress gateway(192,168,204,180) ; 
// // IPAddress subnet(255,255,255,0) ; 
// // IPAddress dns1(192,168,204,180) ; 
// // IPAddress dns2(0,0,0,0) ; 


// void setup(){
//   // Serial port for debugging purposes
//   Serial.begin(9600);

//   // pinMode(ledPin, OUTPUT);
//   // digitalWrite(ledPin, LOW);

//   // Serial.print("Connecting to ");
//   // Serial.println(ssid);
  

//   // if(WiFi.config(staticIP , gateway , subnet , dns1 , dns2) == false){
//   //   Serial.println("Configuration failed!"); 
//   // }

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
  
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }

//   if(!MDNS.begin("spartanz1")){
//     Serial.println("Error starting mDNS") ; 
//   }
//   else{
//     Serial.println("mDNS server began")  ; 
//   }



//   Serial.print("Local IP:") ; Serial.println(WiFi.localIP()) ; 
//   Serial.print("Subnet Mask:") ; Serial.println(WiFi.subnetMask()) ; 
//   Serial.print("Gateway IP:") ; Serial.println(WiFi.gatewayIP()) ; 
//   Serial.println("DNS 1:");  Serial.println(WiFi.dnsIP(0)); 
//   Serial.println("DNS 2:"); Serial.println(WiFi.dnsIP(1)); 

  
//   Serial.println("");
//   Serial.println("Connected..!");
//   Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

//   ws.onEvent(eventHandler);
//   server.addHandler(&ws);

//   // Route for root / web page
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html, processor);
//   });

//   server.on("/request", HTTP_GET, [](AsyncWebServerRequest *request){
//     Serial.println("I got request from the chrome browser") ; 
//     ledState = !ledState ; 
//     //request->send_P(200, "text/html", index_html, processor);
//   });

  

//   // Start server 
//   server.begin();
//   MDNS.addService("http", "tcp", 80);
//   //FASTLED setup 
//   FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
//   FastLED.setBrightness(100);


//   pinMode(INTERNAL_LED , OUTPUT) ; 
// }

// void loop() {
//   // ws.cleanupClients();
//   uint8_t initialHue=0;
//    const uint8_t deltaHue=16;
//    const uint8_t hueDensity=4;
//   while(ledState){
//     delay(500) ; 
//     fill_solid(leds, NUM_LEDS, CRGB::Yellow); 
//     FastLED.show() ; 
//      delay(500) ; 
//     fill_solid(leds, NUM_LEDS, CRGB::Brown); 
//     FastLED.show() ; 
//     delay(500) ; 
//     fill_solid(leds, NUM_LEDS, CRGB::Red);
//     FastLED.show() ; 
//     delay(500) ; 
//     fill_rainbow(leds,NUM_LEDS,initialHue-=hueDensity,deltaHue);
//     FastLED.show();
//     delay(1000) ; 
//     FastLED.clear() ;
//     FastLED.show() ; 
//     fill_solid(leds, NUM_LEDS, CRGB::Black);
//     Serial.println("before the loop") ; 
//     for(int i = 0 ;i < NUM_LEDS ; i++){
//       leds[i] = CRGB::Blue ; 
//       FastLED.show() ; 
//       delay(100) ; 
//     }
    

//     FastLED.clear() ; 
//     FastLED.show() ; 


//     //Serial.println("I am working")  ; 
//   }
 
// }