int sensor_pin = A0; // conectar el sensor de humedad al pin analógico A0 del nodeMCU
int humedad;


void setup() {
pinMode(5,OUTPUT);
Serial.begin(9600); // Inicia la comunicación serial
Serial.println("Iniciando la detección de humedad...");
delay(2000);

}

void loop() {

humedad = analogRead(sensor_pin); //Los valores varian entre 0 - 1023 para tierra húmeda a seca
humedad  = map(humedad,1024,410,0,100); //Escalamiento de valores 
Serial.print("Humedad de la tierra: ");
Serial.print(humedad);
Serial.println("%");
Serial.println(analogRead(sensor_pin));

delay(1000);

if (humedad>=50)
{
  digitalWrite(5,LOW);
}
else
{
  digitalWrite(5,HIGH);
}

}
