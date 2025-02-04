/*
 * Taller IoT PUCP Verano 2025
 * Ingeniería de las Telecomunicaciones 
 * Clase LEDs: Matriz de LEDs
 * Actividad: Controlar una matriz de LEDs
 */


#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define  delay_t  2000  // in milliseconds

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

//Hardware SPI Arduino UNO
// CLK Pin  > 13 SCK
// Data Pin > 11 MOSI

#define CS_PIN    D8

// Hardware SPI connection
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

byte heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
byte face[8] = {0x3C,0xEB,0xD7,0x3C,0x08,0x08,0x6A,0x3C};
byte face2[8] = {0x00, 0x24, 0x24, 0x24, 0x00, 0x42, 0x3C, 0x00};
byte arrow[8] = {0xF8,0x10,0x27,0x42,0xF4,0x0F,0x10,0x00};
byte prgta[8] = {0x7E,0xFF,0xC3,0x03,0x1E,0x18,0x00,0x18};
byte alien[8] = {0x18,0x3C,0x7E,0xDB,0xFF,0x24,0x5A,0xA5};
byte roto[8] = {0x00,0x66,0xCF,0xF7,0xEF,0x76,0x2C,0x08};


void setup() {  
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();
  }

void loop() {
  drawShape();
}

void drawShape() {
  for (int j = 0; j <= 6; j++) {
    for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, roto[i]);
  }
    delay(delay_t);
    for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, alien[i]);
  }
    delay(delay_t);
    for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, heart[i]);
  }
    delay(delay_t);
    for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, prgta[i]);
  }
    delay(delay_t);
    for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, face[i]);
  }
    delay(delay_t);
  for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, face2[i]);
  }
    delay(delay_t);
  for (int i = 0; i <= 7; i++) {
    mx.setRow(0, 0, i, arrow[i]);
  }
    delay(delay_t);
  }
}
