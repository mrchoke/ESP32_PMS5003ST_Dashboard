/**
 * Test by MrChoke
 * APMODE
 **/
 
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "BLINKER_PMSX003ST.h"

//pin (RX16,TX17)
HardwareSerial pmsSerial(2);

BLINKER_PMSX003ST pms;

const char * domain = "pms5003st";

const char* ssid     = domain;
const char* password = "1234567890";

unsigned long Timer1;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Read CPU Temp

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

// WebSocket

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->text(JsonPMS());
  } else if(type == WS_EVT_DISCONNECT){
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_PONG){
    client->text(JsonPMS());
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } else if(type == WS_EVT_DATA){
     // not implement yet
  }
}

// Start Sensor

void StartPMS(){
    Serial.println(F("\nStart"));

    pmsSerial.begin(9600);
    pms.begin(pmsSerial);
    //  pms.wakeUp();
    pms.setMode(PASSIVE);
    Serial.println(F("PMS5003ST Start.."));
    
}

// Read into Json

String JsonPMS(){
    pms.request();
    if(!pms.read()){
        return "{\"status\":\"error\"}";
    }
     String data = "{";
  data += "\"system\": [";
   data += "{\"name\": \"temp\",\"val\":" + String((temprature_sens_read() - 32) / 1.8) + "}";
   data += ",{\"name\":\"mem\",\"val\":\"" + String(esp_get_free_heap_size()/1024) +" KB\"}";
  data += "]";
  data += ",\"aqi\": [";
   data += "{\"name\":\"us\",\"val\":" + String(pms.getAQI(AQI_BASE_US))  + ",\"level\":" + String(pms.getAQILevel(AQI_BASE_US)) + ",\"base\":\"" + String(pms.getMainPollu(AQI_BASE_US)) +"\"}";
   data += ",{\"name\":\"cn\",\"val\":" + String(pms.getAQI(AQI_BASE_CN)) + ",\"level\":" + String(pms.getAQILevel(AQI_BASE_CN)) + ",\"base\":\"" + String(pms.getMainPollu(AQI_BASE_CN)) +"\"}";
  data += "]";
  data += ",\"cf1\": [";
   data += "{\"name\":\"pm1.0\",\"val\":" + String(pms.getPmCf1(1))  +"}";
   data += ",{\"name\":\"pm2.5\",\"val\":" + String(pms.getPmCf1(2.5))  +"}";
   data += ",{\"name\":\"pm10.0\",\"val\":" + String(pms.getPmCf1(10))  +"}";
  data += "]";
  data += ",\"ato\": [";
   data += "{\"name\":\"pm1.0\",\"val\":" + String(pms.getPmAto(1))  +"}";
   data += ",{\"name\":\"pm2.5\",\"val\":" + String(pms.getPmAto(2.5))  +"}";
   data += ",{\"name\":\"pm10.0\",\"val\":" + String(pms.getPmAto(10))  +"}";
  data += "]";
   data += ",\"pcs\": [";
   data += "{\"name\":\"pcs0.3\",\"val\":" + String(pms.getPcs(0.3))  +"}";
   data += ",{\"name\":\"pcs0.5\",\"val\":" + String(pms.getPcs(0.5))  +"}";
   data += ",{\"name\":\"pcs1.0\",\"val\":" + String(pms.getPcs(1))  +"}";
   data += ",{\"name\":\"pcs2.5\",\"val\":" + String(pms.getPcs(2.5))  +"}";
   data += ",{\"name\":\"pcs5.0\",\"val\":" + String(pms.getPcs(5))  +"}";
   data += ",{\"name\":\"pcs10.0\",\"val\":" + String(pms.getPcs(10))  +"}";
  data += "]";
   data += ",\"env\": [";
   data += "{\"name\":\"formaldehyde\",\"val\":\"" + String(pms.getForm())+"\"}";
   data += ",{\"name\":\"temp\",\"val\":\"" + String(pms.getTemp())+"\"}";
   data += ",{\"name\":\"humidity\",\"val\":\"" + String(pms.getHumi())+"\"}";
  data += "]";
  data += ",\"network\": [";
   data += "{\"name\":\"mac\",\"val\":\"" + String(WiFi.macAddress())+"\"}";
   data += ",{\"name\":\"ip\",\"val\":\"" + (WiFi.softAPIP()).toString() +"\"}";
  data += "]";
  
  data += "}";
  return data;
  data = String();
}

// Start mDNS

void StartDNS() {
  if (!MDNS.begin(domain)) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);
}

//Start WebServer and WebSocket

void StartWeb(){
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

// Test Scan WiFi
 server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){
  String json = "[";
  int n = WiFi.scanComplete();
  if(n == -2){
    WiFi.scanNetworks(true,true);
  } else if(n){
    for (int i = 0; i < n; ++i){
      if(i) json += ",";
      json += "{";
      json += "\"rssi\":"+String(WiFi.RSSI(i));
      json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
      json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
      json += ",\"channel\":"+String(WiFi.channel(i));
      json += ",\"secure\":"+String(WiFi.encryptionType(i));
      json += "}";
    }
    WiFi.scanDelete();
    if(WiFi.scanComplete() == -2){
      WiFi.scanNetworks(true);
    }
  }
  json += "]";
  request->send(200, "application/json", json);
   json = String();
  });

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.onNotFound([](AsyncWebServerRequest *request){
    Serial.printf("NOT_FOUND: ");
    if(request->method() == HTTP_GET)
      Serial.printf("GET");
    else if(request->method() == HTTP_POST)
      Serial.printf("POST");
    else if(request->method() == HTTP_DELETE)
      Serial.printf("DELETE");
    else if(request->method() == HTTP_PUT)
      Serial.printf("PUT");
    else if(request->method() == HTTP_PATCH)
      Serial.printf("PATCH");
    else if(request->method() == HTTP_HEAD)
      Serial.printf("HEAD");
    else if(request->method() == HTTP_OPTIONS)
      Serial.printf("OPTIONS");
    else
      Serial.printf("UNKNOWN");
    Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

    if(request->contentLength()){
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    }

    int headers = request->headers();
    int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    }

    int params = request->params();
    for(i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isFile()){
        Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
      } else if(p->isPost()){
        Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      } else {
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }

    request->send(404);
  });

 // for dev
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
}

// Start Access Point

void StartWiFi(){
   Serial.println();
   Serial.println();
   Serial.print(F("Configuring access point... "));
   Serial.println(ssid);
   
  WiFi.softAP(ssid, password);
  WiFi.softAPsetHostname(domain);
  Serial.printf("AP IP address: %s\n",WiFi.softAPIP().toString().c_str());
}


void setup() {
    Serial.begin(115200);
   // mount FS
    if(!SPIFFS.begin()){
        Serial.println("SPIFFS Mount Failed");
    }
    StartPMS();
    delay(500);
    StartWiFi();
    StartWeb();
    StartDNS();
}

void loop() {

 // if has Client Sent them all every 3sec
 
  if (millis() - Timer1 >= 3000) {
     Timer1 = millis();
    if(ws.count()) {
      // Serial.println(ws.count());
       ws.textAll(JsonPMS());
    }
   
  }

  
  
  }
 
