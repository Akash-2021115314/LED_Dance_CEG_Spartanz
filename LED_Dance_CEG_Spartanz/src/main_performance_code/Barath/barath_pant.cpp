// // Lead dancer code 

// // Import required libraries
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <FastLED.h>
// #include <ESPmDNS.h>
// #include <Ticker.h>
// #include<Arduino.h>

// Ticker asyncTicker;

// int led_on = 0 ; 

// // Replace with your network credentials
// const char* ssid = "Sourav";
// const char* password = "sourav123";

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
		
// 		document.getElementById('toggle-btn').addEventListener('change', function() { 
      
      
         
//        });
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
//       if(led_on != 1 ) led_on = 1 ; 
//       else led_on = 2 ; 
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

// #define NUM_LEDS  246
// #define LED_PIN   2

// CRGB leds[NUM_LEDS];

// void DrawMarquee(){
//   static byte j = HUE_BLUE ;
//   j+=4 ;
//   byte k = j;

//   CRGB c;
//   for(int i = 0 ;i<NUM_LEDS;i++){
//     leds[i]=c.setHue(k+=8);
//   }

//   static int scroll = 0;
//   scroll++;
//   for(int i =scroll%20 ;i<NUM_LEDS;i+=20){
//     leds[i] = CRGB::Black;
//   }

//   delay(50);
// }



// void phaseBeat(){
//     uint8_t sinBeat   = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
//   uint8_t sinBeat2  = beatsin8(30, 0, NUM_LEDS - 1, 0, 85);
//   uint8_t sinBeat3  = beatsin8(30, 0, NUM_LEDS - 1, 0, 170);

//   // If you notice that your pattern is missing out certain LEDs, you
//   // will need to use the higher resolution beatsin16 instead. In this
//   // case remove the 3 lines above and replace them with the following:
//   // uint16_t sinBeat   = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
//   // uint16_t sinBeat2  = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
//   // uint16_t sinBeat3  = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

//   leds[sinBeat]   = CRGB::Blue;
//   leds[sinBeat2]  = CRGB::Red;
//   leds[sinBeat3]  = CRGB::White;
  
//   fadeToBlackBy(leds, NUM_LEDS, 10);

//   EVERY_N_MILLISECONDS(10){
//     Serial.print(sinBeat);
//     Serial.print(",");
//     Serial.print(sinBeat2);
//     Serial.print(",");
//     Serial.println(sinBeat3);
//   }

//   FastLED.show();
// }




// unsigned long startTime = 0; 
// void asyncFunction() {
//   // Code to run asynchronously every second
//   //Serial.println("This code runs asynchronously every second.");
//   //if(!ledState) ESP.restart() ;
//   Serial.print("Ticker value:") ; 
//   Serial.println(led_on) ; 
//   if(led_on == 2){

//     FastLED.clear() ; 
//     FastLED.show() ; 
//     ESP.restart() ; 
//   } 
//   // You can add your custom code here...
// }
// void setup(){
//   // Serial port for debugging purposes
//   Serial.begin(9600);


//    asyncTicker.attach(1, asyncFunction);

//   Serial.print("Connecting to ");
//   Serial.println(ssid);
  
//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
  
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
  
//     if(!MDNS.begin("barath_leg")){
//     Serial.println("Error starting mDNS") ; 
//   }
//   else{
//     Serial.println("mDNS server began")  ; 
//   }

//   Serial.println("");
//   Serial.println("Connected..!");
//   Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

//   ws.onEvent(eventHandler);
//   server.addHandler(&ws);

//   // Route for root / web page
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html, processor);
//   });

//    server.on("/request", HTTP_GET, [](AsyncWebServerRequest *request){
//     if(led_on != 1 ) led_on = 1 ; 
//       else led_on = 2 ;

//     ledState = !ledState ;  

//     request->send(200, "text/plain", "Request received successfully");
//   });


//   // Start server
//   server.begin();

//   //FASTLED setup 
//   FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
//   FastLED.setBrightness(100);
// }

// void loop() {
//   ws.cleanupClients();
  

//   while(led_on == 1 ){
  
 
//   //Pudhiya manidha boomiku vaa frame 
//   // song bit starts at 00:04 sec ends at 00:11 ; so totally 7 seconds 
//   //140 LEDs in 7 seconds if delay is 50
//   //frame1 code starts 

//   int  end = 145  ;  
//   int counter1 = 0 , counter2 = 145 ; 
//   //for idea 1 pant code 
//   // int counter3=288 , counter4 = 375 ; 
//  leds[0] = CRGB::Blue ; 
//   FastLED.show() ; 
//   for(int i = 0 ; i < end ; i++){
//     //counter1 and counter2 is for shirt 
//     //pant code must be added 
//     // leds[counter1] = CRGB::Blue ; 
//     // leds[counter2] = CRGB::Blue ; 
//     // leds[counter3] = CRGB::Blue ; 
//     // leds[counter4] = CRGB::Blue ; 
//     counter1++ ; counter2++ ; 
//     // counter3++ ; counter4++ ; 
//     delay(50) ; 
//     // FastLED.show() ; 
   
//   }
  
//   //this delay is for blue light to be visible till pudhiya manidha fully ends 
//   delay(5000) ; 
  
 
//   //appo sillunu oru kaathu - blackout 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   delay(5000) ; //maybe 4 seconds ku maathikalaam 


  
//   //yellow for red heart frame 
//   fill_solid(leds , NUM_LEDS , CRGB::Blue) ; 
//   FastLED.show();
//   delay(8900); 

//   end = 10 ; 
//   for(int i = 0 ; i < end ;i++){
//     // FastLED.clear() ; 
//     // FastLED.show() ; 
//     delay(50) ; 
//     // fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//     // FastLED.show() ; 
//     delay(50) ; 
    
//   }
   
//   //palichunu irukura heart frame 
//   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//   FastLED.show() ; 
//   delay(20000) ; 
//   // startTime = millis();  // Record the start time
//   //   while (millis() - startTime < 20000) {  // Run for 5 seconds
//   //         rainbowCycle(20) ; 
//   //   }
  
 

//   //blackout 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   delay(3600) ; //maybe 4 seconds ku maathikalaam 

//   //wings frame 
//   fill_solid(leds , NUM_LEDS , CRGB::Purple) ; 
//   FastLED.show() ; 
//   delay(9000) ; 


//   //blue heart frame 
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
//   delay(10200) ; 


//   //moon frame 
//   fill_solid(leds , NUM_LEDS , CRGB::Purple) ; 
//   FastLED.show() ; 
//   delay(18200) ; 

//   //vinmeengal thaan unthan kanmeenele
//   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//   FastLED.show() ; 
//   delay(10000) ;

//   // startTime = millis();  // Record the start time
//   //   while (millis() - startTime < 10000) {  // Run for 5 seconds
//   //         phaseBeat() ; 
//   //   }

  

//   //blackout 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   delay(1200) ; //maybe 4 seconds ku maathikalaam
  


//   //muqabala code 
//   //ooo ra ra uyya ra ra 
//   //moonwalk half shirt and half leg code 
//   //pant code adikanum 
//   int s = 42 ; 
//   int e = 207 ; 
//   fill_solid(&leds[s], e - s + 1, CRGB::Orange);

// //   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//   FastLED.show() ; 
//   delay(5800) ; 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   end = 140 ; 
//   //half shirt one color another another color 
//   int startLED  = 131; 
//   int endLED = 219;  
// //   fill_solid(&leds[startLED], endLED - startLED + 1, CRGB::Orange);
// //   FastLED.show() ; 
//   delay(500) ; 
//   FastLED.clear() ; 
//    startLED  = 0; 
//   endLED = 130;  
// //   fill_solid(&leds[startLED], endLED - startLED + 1, CRGB::Orange);
// //   FastLED.show() ; 
//   delay(500) ; 


  
//   // FastLED.clear() ; 


//   //oo eh oo code uh 

//   //dancer 2 on 
//   //color change to green shirt && blue pant 
// //   int startLED1  = 43; 
// //   int endLED1 = 220;  
// //   fill_solid(&leds[startLED1], endLED1 - startLED1 + 1, CRGB::Blue);
// //   FastLED.show() ; 
// //   startLED1 = 0 ; 
// //   endLED1 = 42 ; 
// //   fill_solid(&leds[startLED1], endLED1 - startLED1 + 1, CRGB::Green);
// //   FastLED.show() ; 

//   //pant blue color 
//   delay(2100) ; 

//   //oo oh oo On 
//   //on dancer2
//   fill_solid(leds , NUM_LEDS , CRGB::Red); //on dancer2 
//   FastLED.show() ; 
//   delay(800) ; 

//   //on dancer3
//   //oo oh oo On 
//   //oo eh oh oh.....
//   // fill_solid(leds , NUM_LEDS , CRGB::Blue); //on dancer3
//   // FastLED.show() ; 
//   delay(3400) ; 

//   //off dancer2 ; 
//     FastLED.clear() ; 
//   FastLED.show() ; 
//   delay(400) ; 


//   //off dancer3 ; 
//   // fill_solid(leds , NUM_LEDS , CRGB::Purple) ; 
//   // FastLED.show() ; 
//   delay(400) ; 


//   //aaya oo aaj meh 
//   //dancer1 ; 
//   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//   FastLED.show() ; 
//   delay(2100) ; 
//   FastLED.clear() ;
//   FastLED.show() ;  
//   //clear dancer1 here 

//   // tak 
//   //dancer 2 on ; 
//   fill_solid(leds , NUM_LEDS , CRGB::Blue) ; 
//   FastLED.show() ; 
//   delay(500) ; 
//    FastLED.clear() ; 
//    FastLED.show() ; 
//   //clear dancer 2 here 


//   //tak 
//   //dancer1 on ; 
// //   fill_solid(leds , NUM_LEDS , CRGB::Blue) ; 
//  FastLED.clear()  ;
//   FastLED.show() ; 
//   delay(500) ; 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   //clear dancer 1 here 


//   //tak 
//   //lekin jayoonga dhil mera...
//   //dancer3 on ; 
//    fill_solid(leds , NUM_LEDS , CRGB::Green) ; 
//    FastLED.show() ; 
//   delay(3200) ;
//   //clear dancer 3 here 


//   //tak 
//   //dancer 3 on ; 
//    fill_solid(leds , NUM_LEDS , CRGB::Blue) ; 
//    FastLED.show() ; 
//   delay(700) ;
//   //clear dancer 3 

//   //tak 
//   //dancer 1 on ; 
// //   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.clear() ; 
//   FastLED.show() ; 
//   delay(700) ;
//   FastLED.clear() ; 
//   //clear dancer 1 


  


//   //tak 
//   //dancer 2 on ; 
//   fill_solid(leds , NUM_LEDS , CRGB::Green) ; 
//   FastLED.show() ; 
//   delay(800) ;

//   //rub uh koiyi mujhe thoose thoo muje 
  
//   //dancer1 on ; 
//   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
//   FastLED.show() ; 
//   delay(5100) ;
//   FastLED.clear() ; 
//   FastLED.show() ; 

//   //dancer1 body ; 
//   //rainbow 
//   // fill_solid(leds , NUM_LEDS , CRGB::White) ; 
//   // FastLED.show() ; 
//   // delay(3000) ;


// //thooka muse chahaas mila  , oh eh ho // data sheet 
// //   fill_solid(leds , NUM_LEDS , CRGB::Orange) ; 
// //   FastLED.show() ; 
//    FastLED.clear() ; 
//    FastLED.show() ; 
//   delay(3200) ; 

//   //dancer 2 right hand ; 
  

//   // dancer3 left hand ; 

//   //muqala muqabala lele...

//   startTime = millis();  // Record the start time
//   uint16_t  x;
//   int       scale;
//   uint16_t  t;
//     while (millis() - startTime < 4200) {  // Run for 5 seconds
//           x = 0;
//           t = millis() / 5;
//           scale = beatsin8(10, 10, 30);
          
//           for (int i = 0; i < NUM_LEDS; i++) {
//               uint8_t noise = inoise8(i * scale + x, t);
//               uint8_t hue = map(noise, 50, 190, 0, 255);
//               leds[i] = CHSV(hue, 255, 255);
//           }
          
//           FastLED.show();
//     }
    
//   //le la 
//   //dancer2 
//   // fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   // FastLED.show() ; 
//   // delay(50) ; 
//   // FastLED.clear();
//   // FastLED.show() ; 
//   // delay(50)  ;
//   delay(100) ; 
//   FastLED.clear() ; 
//     FastLED.show() ; 
  

//   //dancer3
//   // fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   // FastLED.show() ; 
//   // delay(50) ; 
//   // FastLED.clear();
//   //  FastLED.show() ; 
//   delay(50) ; 
  


//   //ohhhh..
//   startTime = millis();  // Record the start time

//     while (millis() - startTime < 1500) {  // Run for 5 seconds
//           x = 0;
//           t = millis() / 5;
//           scale = beatsin8(10, 10, 30);
          
//           for (int i = 0; i < NUM_LEDS; i++) {
//               uint8_t noise = inoise8(i * scale + x, t);
//               uint8_t hue = map(noise, 50, 190, 0, 255);
//               leds[i] = CHSV(hue, 255, 255);
//           }
          
//           FastLED.show();
//     }



//   //le la
//   //dancer2 
//   // fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   // FastLED.show() ; 
//   // delay(50) ; 
//   // FastLED.clear();
//   //  FastLED.show() ; 
//   // delay(50)  ;

//   delay(100) ; 
//     FastLED.clear() ; 
//   FastLED.show() ; 

//   //dancer1
//   // fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   // FastLED.show() ; 
//   // delay(50) ; 
//   // FastLED.clear();
//   //  FastLED.show() ; 
//   delay(1500)  ;
//   // fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   // FastLED.show() ; 




//   //muqabala suvaanallla  lele...
//   // startTime = millis();  // Record the start time

//   // while (millis() - startTime < 5000) {  // Run for 5 seconds
//   //   fill_rainbow(leds, NUM_LEDS, initialHue1 -= hueDensity1, deltaHue1);
//   //   FastLED.show();
//   //   initialHue1++;
//   // }

//   // startTime = millis();  // Record the start time
 
//   // while (millis() - startTime < 5800) {  // Run for 5 seconds
//   //       x = 0;
//   //       t = millis() / 5;
//   //       scale = beatsin8(10, 10, 30);
        
//   //       for (int i = 0; i < NUM_LEDS; i++) {
//   //           uint8_t noise = inoise8(i * scale + x, t);
//   //           uint8_t hue = map(noise, 50, 190, 0, 255);
//   //           leds[i] = CHSV(hue, 255, 255);
//   //       }
        
//   //       FastLED.show();
//   // }

//     startTime = millis();  // Record the start time
//     while (millis() - startTime < 5800) {  // Run for 5 seconds
//           phaseBeat() ; 
//     }
  
  
//   //le la 
//   //dancer2 
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
//   delay(50) ; 
//   FastLED.clear();
//   FastLED.show() ; 
//   delay(50)  ;

//   //dancer3
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
//   delay(50) ; 
//   FastLED.clear();
//    FastLED.show() ; 
  


//   //ohhhh..

//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ;
//   delay(1500)  ;

//   //le la
//   //dancer2 
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
//   delay(50) ; 
//   FastLED.clear();
//    FastLED.show() ; 
//   delay(50)  ;

//   //dancer1
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
//   delay(50) ; 
//   FastLED.clear();
//    FastLED.show() ; 
//   delay(1500)  ;
//   fill_solid(leds , NUM_LEDS , CRGB::Red) ; 
//   FastLED.show() ; 
  

//   //bass drop ku oru  from leg to top light varanum
//   //inga our color varanum



//   //dancer all 

//   FastLED.clear() ; 
//   FastLED.show() ; 
  

   
//   delay(16000) ; 


 




//   //chumma delay 
    
//     delay(20000) ; 
//     FastLED.clear() ; 
//     delay(100) ; 

//   }
  

 
// }