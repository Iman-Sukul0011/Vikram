
#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <LoRa.h>


#define LORA_CS    16
#define LORA_RST   4
#define LORA_DIO0  2
#define SD_CS      5

Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp;


void setup() {
    Serial.begin(115200);
    delay(2000); 
    Wire.begin(21, 22); 
    Serial.println("\n--- VIKRAM 1.0 DIAGNOSTICS ---");
    if (mpu.begin()) {
        Serial.println("[OK] You are Sucessful.");
    } else {
        Serial.println("[FAIL] MPU6050 missing!");
    }
    if (bmp.begin(0x76)) {
        Serial.println("[OK] BMP280 detected at 0x76");
    } else if (bmp.begin(0x77)) {
        Serial.println("[OK] BMP280 detected at 0x77");
    } else {
        Serial.println("[FAIL] BMP280 missing!");
    }
    Serial.print("Testing SD Card... ");
    if (SD.begin(SD_CS)) {
        Serial.println("[OK]");
    } else {
        Serial.println("[FAIL] - Check wiring, FAT32 format, and 5V supply.");
    }
    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);
    if (LoRa.begin(433E6)) {
        Serial.println("[OK] LoRa module active at 433MHz");
    } else {
        Serial.println("[FAIL] LoRa missing! Check Pins 16, 4, 2.");
    }
    Serial.println("--- DIAGNOSTICS COMPLETE ---\n");
}


void loop() {
    delay(1000); 
}