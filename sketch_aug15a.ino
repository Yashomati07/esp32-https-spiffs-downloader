#include <WiFi.h>
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <WiFiClientSecure.h>

const char*ssid = "Saloni07";
const char*passward = "7741881095";

const char*fileURL = "https://raw.githubusercontent.com/espressif/esp-idf/master/README.md";
const char*filePath = "/downloaded_file.bin";

void setup(){
  Serial.begin(115200);
  delay(1000);

  Serial.printf("Free heap at start: %d bytes\n", ESP.getFreeHeap());

  if(!SPIFFS.begin(true)){
    Serial.println("Failed to mount SPIFFS");
    return;
  }
 Serial.printf("Total SPIFFS space: %d bytes \n", SPIFFS.totalBytes());
 Serial.printf("Used SPIFFS space: %d bytes \n", SPIFFS.usedBytes());

 WiFi.begin(ssid, passward);
 Serial.printf("Connecting to WiFi...");
 while(WiFi.status() !=WL_CONNECTED){
  delay(500);
  Serial.printf(".");
  yield();
 } 
 Serial.printf("Connected");

 Serial.printf("Free heap after WiFi connection: %d bytes\n", ESP.getFreeHeap());

 downloadFile();
}

void downloadFile(){
  HTTPClient http;
  WiFiClientSecure client;

  client.setInsecure();

  Serial.println("Starting download...");
  http.begin(client, fileURL);
  http.setTimeout(5000);

  int httpCode = http.GET();

  if(httpCode== HTTP_CODE_OK){
    int contentLength = http.getSize();
    Serial.printf("File size: %d bytes\n", contentLength);

    if(contentLength>(SPIFFS.totalBytes()-SPIFFS.usedBytes())){
      Serial.println("Error: Not enough space in SPIFFS to store the file");
      http.end();
      return;
    }

    File file = SPIFFS.open(filePath, FILE_WRITE);
    if(!file){
      Serial.println("Failed to open file for writing");
      http.end();
      return;
    }

    const int bufferSize = 4096;
    uint8_t buffer[bufferSize];
    int totalBytesRead = 0;
    unsigned long startTime = millis();

    Serial.printf("Fress heap before download:%d bytes\n", ESP.getFreeHeap());

    WiFiClient*stream = http.getStreamPtr();
    while (http.connected()&&(totalBytesRead<contentLength || contentLength == -1)){
      size_t bytesAvailable= stream->available();
      if(bytesAvailable){
        int bytesRead = stream->readBytes(buffer, min((size_t)bufferSize, bytesAvailable));
        file.write(buffer, bytesRead);
        totalBytesRead += bytesRead;
        Serial.printf("Downloaded %d bytes\n", totalBytesRead);
        yield();
      }
      yield();
    }
    file.close();

    Serial.printf("Free heap after download: %d bytes\n", ESP.getFreeHeap());

    unsigned long endTime = millis();
    float timeTaken = (endTime - startTime)/1000.0;
    float speed = (totalBytesRead/timeTaken)/1024.0;
    Serial.printf("Downloade completed in %2f seconds\n", timeTaken);
    Serial.printf("Average speed: %2f KBps\n", speed);

    if(speed<400){
      Serial.printf("Warning: Speed is below 400 KBps");
    }
  }else{
    Serial.printf("HTTP GET failed, error code: %d\n", httpCode);
  }
  http.end();
}

void loop() {
  //put your main code here, to run repeatedly:
}