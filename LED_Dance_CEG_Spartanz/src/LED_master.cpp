// //this file is responsible for having the code for the lead dancer
// // the esp32 of this dancer will act as both master in the ESP-Now protocol
// // as well as a web server that will be getting HTTP requests from the client to turn on or off

// #include <esp_now.h>
// #include <WiFi.h>
// #include "ESPAsyncWebServer.h"
// #include <Arduino_JSON.h>
// #include <FastLED.h>

// // Replace with your network credentials (WIFI-STATION)
// const char* ssid = "REPLACE_WITH_YOUR_SSID";
// const char* password = "REPLACE_WITH_YOUR_PASSWORD";


// //station credentials 
// const char* ssAP = "ESP32-Access-Point" ; 
// const char* passwordAP = "123456789" ; 


// //Wifi channel for access point 
// #define CHAN_AP 2 

// //message type for the web server client 
// typedef struct struct_message {
//   int id;
//   int toggle_on ; 
// } struct_message;

// struct_message incomingCircuitOnMessage ; 

// //change the following to the recivers' MAC address (obtain them by running WiFi.macAddress() in the slave boards)
// uint8_t broadcastAddress1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// uint8_t broadcastAddress2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


// typedef struct broadcast_message_struct {
//   int start  ;  
//   int end  ; 
//   int time ; 
//   int color ; 
// } broadcast_message_struct;

// broadcast_message_struct broadcast_message ; 

// esp_now_peer_info_t peerInfo;


// JSONVar board;

// AsyncWebServer server(80);
// AsyncEventSource events("/events");


// //FastLED setup 

// #define NUM_LEDS  18
// #define LED_PIN   2

// CRGB leds[NUM_LEDS];



// //this callback function will be triggerd when the data is broadcastd to the slaves 

// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   char macStr[18];
//   Serial.print("Packet to: ");
//   // Copies the sender mac address to a string
//   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//   Serial.print(macStr);
//   Serial.print(" send status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }



// //This callback function will be triggered when the webpage client makes request to the webserver 
// void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) { 
//   // Copies the sender mac address to a string
//   char macStr[18];
//   Serial.print("Packet received from: ");
//   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//   Serial.println(macStr);
//   memcpy(&incomingCircuitOnMessage, incomingData, sizeof(incomingCircuitOnMessage));
  


//     board["id"] = incomingCircuitOnMessage.id ; 
//     board["turnOn"] = incomingCircuitOnMessage.toggle_on ; 
//   String jsonString = JSON.stringify(board);
//   events.send(jsonString.c_str(), "new_readings", millis());
  
//   Serial.printf("Board ID %u: %u bytes\n", incomingCircuitOnMessage.id, len);
//   Serial.printf("Spartanz member wants the circuit to be on ? (0/1):" , incomingCircuitOnMessage.toggle_on) ; 
//   Serial.println();
// }


// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE HTML><html>
// <head>
//    html code for the webpage must be added here 
//   </style>
// </head>
// <body>
 
// </body>
// </html>)rawliteral";



// void setup(){

//     // Initialize Serial Monitor
//   Serial.begin(115200);

//   // Set the device as a Station and Soft Access Point simultaneously
//   WiFi.mode(WIFI_AP_STA);
  
//   // Set device as a Wi-Fi Station
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Setting as a Wi-Fi Station..");
//   }
//   Serial.print("Station IP Address: ");
//   Serial.println(WiFi.localIP());
//   Serial.print("Wi-Fi Channel: ");
//   Serial.println(WiFi.channel());
//   Serial.print("ESP Board MAC Address: "); 
//   Serial.println(WiFi.macAddress()) ; //printing the mac address if needed 


//   //Setting the access point 

//   WiFi.softAP(ssAP , passwordAP) ; 


//    // Print the IP address of the AP
//   Serial.print("AP IP address: ");
//   Serial.println(WiFi.softAPIP());

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }

//   esp_now_register_send_cb(OnDataSent);
  
//   // Once ESPNow is successfully Init, we will register for recv CB to
//   // get recv packer info
//   esp_now_register_recv_cb(OnDataRecv);


//   //ESPNOW adding the slave peers 

//    // register peer
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
//   // register first peer  
//   memcpy(peerInfo.peer_addr, broadcastAddress1, 2);
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
//   // register second peer  
//   memcpy(peerInfo.peer_addr, broadcastAddress2, 2);
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }


//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html);
//   });
   
//   events.onConnect([](AsyncEventSourceClient *client){
//     if(client->lastId()){
//       Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
//     }
//     // send event with message "hello!", id current millis
//     // and set reconnect delay to 1 second
//     client->send("hello!", NULL, millis(), 10000);
//   });
//   server.addHandler(&events);
//   server.begin();


//   //FastLED setup 
//   FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
//   FastLED.setBrightness(100);

// }
// void broadcast(){
//   broadcast_message.start = random(0,20);
//   broadcast_message.end = random(0,20);
//   broadcast_message.color = random(0,20);
//   broadcast_message.time = random(0,20);
 
//   esp_err_t result = esp_now_send(0, (uint8_t *) &broadcast_message, sizeof(broadcast_message_struct));
   
//   if (result == ESP_OK) {
//     Serial.println("Sent with success");
//   }
//   else {
//     Serial.println("Error sending the data");
//   }
// }
// void loop(){
//   static unsigned long lastEventTime = millis();
//   static const unsigned long EVENT_INTERVAL_MS = 5000;
//   if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
//     events.send("ping",NULL,millis());
//     lastEventTime = millis();
//   }

//   delay(500) ; 
//   leds[0] = CRGB::Blue ; 
//   FastLED.show() ; 
//   delay(500) ; 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   broadcast() ; 
  
// }



