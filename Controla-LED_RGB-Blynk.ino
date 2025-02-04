/*
 * Taller IoT PUCP Verano 2025
 * Ingeniería de las Telecomunicaciones 
 * Clase Blynk: RGB_Blynk
 * Actividad: Controlar un LED RGB desde una app 
 */

#define BLYNK_TEMPLATE_ID "TMPL2JJUb2Lug" //copiar desde la web de Blynk Cloud
#define BLYNK_TEMPLATE_NAME "RGB  IoT" //copiar desde la web de Blynk Cloud
#define BLYNK_AUTH_TOKEN "LfHCPG0r41sVckCiCcOQJAg_mIPgH-uM" //copiar desde la web de Blynk Cloud

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


const int redled = 14;//D5
const int greenled = 12;//D6
const int blueled = 13;//D7


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ASUS"; //your hotspot name
char pass[] = "111sssaaa"; //your hotspot password name



void setup()
{
 Serial.begin(9600);

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

 delay(100);
 Blynk.begin(auth, ssid, pass);
 //Blynk.virtualWrite(V1, 35, 250, 200);
}


// Uso de un pin virtual
// IMPORTANTE: esta fuera del loop
BLYNK_WRITE(V1)
{
  // Como se usa un pin virtual, los datos que vienen de la aplicación
  // se recepcionan de esta manera
  int r = param[0].asInt(); // Se define que este dato es un entero
  int g = param[1].asInt();
  int b = param[2].asInt();
  Serial.print("V1: r = ");
  Serial.print(r);
  Serial.print("\t g=");
  Serial.print(g);
  Serial.print("\t b=");
  Serial.println(b);

// para zeRGBa se debe escalar valores de 0 - 255 (8bits) a 0 -1023 (valor analógico)
//  long factor = 1023.0/255.0;
  r = map(r, 0, 255, 762, 1023);
  g = map(g, 0, 255, 762, 1023);
  b = map(b, 0, 255, 762, 1023);
  

  // Al ser un LED con ánodo común, se tienen que invertir los valores
  r = 1023 - r;
  g = 1023 - g;
  b = 1023 - b;
  Serial.print("FINAL: r = ");
  Serial.print(r);
  Serial.print("\t g=");
  Serial.print(g);
  Serial.print("\t b=");
  Serial.println(b);

  // Estos valores se escriben en los pines indicados
  analogWrite(D5 ,r);
  analogWrite(D6, g);
  analogWrite(D7, b);
}


void loop() {
  Blynk.run();
}
