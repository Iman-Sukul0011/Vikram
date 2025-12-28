#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// --- Configuration ---
const char *ssid = "Vikram_1.0";
const char *password = "KurkureMasala1234";
const int SD_CS_PIN = 5;
#define SEALEVELPRESSURE_HPA (1012.8)

// --- Objects ---
IPAddress localIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);
Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp;
File dataFile;

// --- Data Variables ---
float a_x, a_y, a_z, g_x, g_y, g_z, temp, pressure, altitude;
String wifiStatus = "Establishing AP...";

// --- Prototypes ---
void handleRoot();
void initSensors();
void initSD();
void logToSD();

void setup() {
    Serial.begin(115200);
    initSensors();
    initSD();

    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(localIP, gateway, subnet);
    wifiStatus = "AP Active: http://" + WiFi.softAPIP().toString();
    
    server.on("/", handleRoot);
    server.begin();
    Serial.println("System Ready.");
}

void loop() {
    sensors_event_t a, g, t;
    mpu.getEvent(&a, &g, &t);
    
    a_x = a.acceleration.x; a_y = a.acceleration.y; a_z = a.acceleration.z;
    g_x = g.gyro.x; g_y = g.gyro.y; g_z = g.gyro.z;
    temp = bmp.readTemperature();
    pressure = bmp.readPressure();
    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

    logToSD();
    server.handleClient();
    delay(1000); 
}

void handleRoot() {
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<meta http-equiv='refresh' content='2'>"; // Refresh every 2 seconds
    html += "<style>body{font-family:sans-serif; background:#f0f2f5; text-align:center;} .card{background:white; margin:20px auto; padding:20px; border-radius:10px; width:90%; max-width:500px; box-shadow:0 4px 8px rgba(0,0,0,0.1);} table{width:100%; border-collapse:collapse;} td,th{padding:10px; border:1px solid #ddd; text-align:left;} th{background:#007bff; color:white;}</style>";
    html += "</head><body><div class='card'><h1>VIKRAM 1.0</h1><p>" + wifiStatus + "</p>";
    html += "<table><tr><th>Metric</th><th>Value</th></tr>";
    html += "<tr><td>Altitude</td><td>" + String(altitude, 2) + " m</td></tr>";
    html += "<tr><td>Temperature</td><td>" + String(temp, 1) + " °C</td></tr>";
    html += "<tr><td>Accel X/Y/Z</td><td>" + String(a_x,1)+"/"+String(a_y,1)+"/"+String(a_z,1) + "</td></tr>";
    html += "</table></div></body></html>";
    server.send(200, "text/html", html);
}

void initSensors() {
    Wire.begin();
    if (!mpu.begin()) { Serial.println("MPU Fail"); while(1); }
    if (!bmp.begin(0x76)) { Serial.println("BMP Fail"); while(1); }
}

void initSD() {
    if (SD.begin(SD_CS_PIN)) {
        dataFile = SD.open("/telemetry.csv", FILE_APPEND);
        if (dataFile) {
            dataFile.println("Time,AX,AY,AZ,GX,GY,GZ,T,P,A");
            dataFile.close();
        }
    }
}

void logToSD() {
    dataFile = SD.open("/telemetry.csv", FILE_APPEND);
    if (dataFile) {
        dataFile.printf("%lu,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
                        millis(), a_x, a_y, a_z, g_x, g_y, g_z, temp, pressure, altitude);
        dataFile.close();
    }
}