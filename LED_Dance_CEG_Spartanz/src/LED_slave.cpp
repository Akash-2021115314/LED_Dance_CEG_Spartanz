//this code is responsible for having for recieving brodcast message from master and 
//display the lights in the array 

// #include <esp_now.h>
// #include <WiFi.h>
// #include "ESPAsyncWebServer.h"
// #include <Arduino_JSON.h>
// #include <FastLED.h> 

// //Format of the message that will be coming from the server 
// typedef struct broadcast_message_struct {
//   int start  ;  
//   int end  ; 
//   int time ; 
//   int color ; 
// } broadcast_message_struct;

// broadcast_message_struct recived_message  ;

// uint8_t masterAddress[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

// // Replace with your network credentials (WIFI-STATION)
// const char* ssid = "REPLACE_WITH_YOUR_SSID";
// const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// // WiFi channel for access point
// #define CHAN_AP 2


// //FastLED setup 

// #define NUM_LEDS  18
// #define LED_PIN   2

// CRGB leds[NUM_LEDS];

// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&recived_message, incomingData, sizeof(recived_message));
//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   Serial.print("start: ");
//   Serial.println(recived_message.start);
//   Serial.print("end: ");
//   Serial.println(recived_message.end);
//   Serial.println();


//   //FastLED code 
//   delay(500) ; 
//   leds[0] = CRGB::Red;
//   FastLED.show() ;
//   delay(500) ; 
//   FastLED.clear(); 
//   FastLED.show() ; 

// }


// void setup(){
//     Serial.begin(115200);
    
//     //Set device as a Wi-Fi Station
//     WiFi.mode(WIFI_AP_STA);
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");


//     //Init ESP-NOW
//     if (esp_now_init() != ESP_OK) {
//       Serial.println("Error initializing ESP-NOW");
//       return;
//     }
    
//     // Once ESPNow is successfully Init, we will register for recv CB to
//     // get recv packer info
//     esp_now_register_recv_cb(OnDataRecv);


//       // Add the master as a peer
//     esp_now_peer_info_t peerInfo;
//     peerInfo.channel = CHAN_AP;
//     peerInfo.encrypt = false;
//     memcpy(peerInfo.peer_addr, masterAddress, sizeof(masterAddress));

//     if (esp_now_add_peer(&peerInfo) != ESP_OK) {
//     Serial.println("Failed to add master as peer");



//     //FastLed setup 
//     FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
//     FastLED.setBrightness(100);

//     return;
//   }

//   Serial.println("ESP-NOW Slave is ready");

// }

// void loop(){

// }

