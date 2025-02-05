/*
 * Taller IoT PUCP Verano 2025
 * Ingeniería de las Telecomunicaciones 
 * Proyecto: Maceta IoT
 * Actividad: Detectar y monitorear la humedad de la planta en una maceta
 */

#define BLYNK_TEMPLATE_ID "TMPL2hOPxH8Eb" // CAMBIAR EL ID QUE SE COPIA DE BLYNK
#define BLYNK_TEMPLATE_NAME "Maceta IoT" // CAMBIAR EL NOMBRE QUE SE COPIA DE BLYNK
#define BLYNK_AUTH_TOKEN "xicoQ_kAHEFRFVGy3XIh7AZMPeu-8wBZ" //CAMBIAR POR TOKEN DE BLYNK

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "telecomunicaciones"; //Escribe el nombre la red WiFi
char pass[] = "telecom2025"; //Escribe la contraseña de la red WiFi

BlynkTimer timer;

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define hardware type, size, and pins
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CLK_PIN   14 // GPIO14 (HSCLK) D5 de nodeMCU
#define DATA_PIN  13 // GPIO16 (HMOSI) D7 de nodeMCU
#define CS_PIN    15 //  GPIO15 (HCS) D8 de nodeMCU

int sensor_pin = A0; // conectar el sensor de humedad al pin analógico A0 del nodeMCU
int humedad,sensor;

// Create a MAX72xx object
MD_MAX72XX display = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Bitmaps for animations
byte smiley[2][8] = {
  {0b00111100, 0b01000010, 0b10100101, 0b10000001, 0b10100101, 0b10011001, 0b01000010, 0b00111100},
  {0b00111100, 0b01000010, 0b10100101, 0b10000001, 0b10111101, 0b10000001, 0b01000010, 0b00111100}
};
byte heart[2][8] = {
  {0b00000000, 0b01100110, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},
  {0b00000000, 0b01100110, 0b10111101, 0b10011001, 0b01000010, 0b00100100, 0b00011000, 0b00000000}
};

// Scrolling text message
const char *scrollingText = "TelecomPUCP";
uint16_t scrollDelay = 100; // Delay between shifts in milliseconds
uint16_t displayTime = 500; // Time each frame is shown in milliseconds
int brightnessLevel = 8; // Set brightness level (0 is minimum, 15 is maximum)



void envia_datos()
{

  sensor = analogRead(sensor_pin); //Los valores varian entre 0 - 1023 para tierra húmeda a seca
  humedad  = map(sensor,410,1023,100,0); //Escalamiento de valores 

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, humedad);
    Serial.print("Humedad de la tierra: ");
    Serial.print(humedad);
    Serial.println("%");
    Serial.println(sensor);
    delay(1000);

    if (humedad>=50)
    {
       playAnimation(heart, 2, 2);
      //digitalWrite(5,LOW);

      }
    else
    {
      playAnimation(smiley, 2, 2);
      //digitalWrite(5,HIGH);
    }
}

void playAnimation(byte animation[][8], int frameCount, int repeat) {
  for (int r = 0; r < repeat; r++) {
    for (int i = 0; i < frameCount; i++) {
      displayFrame(animation[i]);
      delay(displayTime); // Wait before showing next frame
    }
  }
}

void displayFrame(byte frame[8]) {
  for (int i = 0; i < 8; i++) {
    display.setRow(0, i, frame[i]); // Display each row of the bitmap
  }
  display.update(); // Ensure the display is updated
}


void setup()
{
  display.begin(); // Initialize the display
  display.control(MD_MAX72XX::INTENSITY, brightnessLevel); // Set the brightness level
  display.clear(); // Clear the display
  Serial.begin(9600); // Inicia la comunicación serial
  Serial.println("Iniciando la detección de humedad...");
 
  delay(100);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, envia_datos);
}

void loop() {
  Blynk.run();
  timer.run();
}
