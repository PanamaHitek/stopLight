/*
---------------------------------------
| Semáforo con Arduino, versión 1.0.0 |        Diseñado por Antony García González, del Panama Hitek Creative Team
---------------------------------------

Este algoritmo le da funcionamiento a un semáforo, cuyo diagrama pictórico se puede encontrar en la dirección
http://panamahitek.com/semaforo-con-arduino-v1-0-0/

Este semáforo no ha sido diseñado para que funcione como el clásico dispositivo de control de tráfico que vemos en
nuestras calles, sino que se construyó para que funcionara como indicador visual del tiempo restante para presentaciones
orales.
Al estar celebrando un ciclo de conferencias, fue necesario para nosotros hayar la manera de indicarle a determinado
expositor el tiempo que le quedaba. Así, la luz verde permanece encendida por 28 minutos, la luz amarilla por 2 minutos
y a partir de los 30 minutos de iniciada la exposición se enciende la luz roja, indicando que el tiempo de la exposición
ha terminado.

El funcionamiento de este dispositivo se puede modificar para que sea usado como semáforo de tránsito. De igual forma
se puede cambiar el tiempo para que sea más o menos tiempo que los 30 minutos preestablecidos.

Los invito a visitar nuestro blog http://panamahitek.com
El dispositivo funcionando en tiempo de ejecución lo pueden apreciar en el siguiente video:
https://www.youtube.com/watch?v=R6xY0yPHS68

*/

#include <EEPROM.h>;
int Minutos;
int Segundos;
int Horas;
int SecondBefore = 0;
int SecondAfter = 0;

void setup() {
  pinMode(4, INPUT); //Interruptor "Reset"

  pinMode(5, OUTPUT); //LED Verde
  pinMode(6, OUTPUT); //LED Amarillo
  pinMode(7, OUTPUT); //LED Rojo

  digitalWrite(7, HIGH);

  if (EEPROM.read(2) != 0) {
    Minutos = EEPROM.read(2);
    Horas = EEPROM.read(3);
  }
  else
  {
    Segundos = 0;
    Minutos = 0;
    Horas = 0;
  }

}

void loop() {

  if (digitalRead(4) == 1) {

    EEPROM.write(2, 0);
    EEPROM.write(3, 0);

    Segundos = 0;
    Minutos = 0;
    Horas = 0;

    //Secuencia de luces parpadeantes cuando se produce el reset

    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(250);
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(250);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(250);
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(250);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(250);
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(250);
    digitalWrite(7, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);


    delay(1000);

  }

  //Función para el control del tiempo
  TimeRelatedEvents();
}

void TimeRelatedEvents() {
  SecondAfter = millis();
  //Conteo de los segundos
  if ((SecondAfter - SecondBefore) > 1000) {
    SecondBefore = SecondAfter;

    Segundos++;
    if (Segundos == 60) {
      Segundos = 0;
      Minutos++;
      EEPROM.write(2, Minutos);
      //Tiempo de duración de la luz verde (28)
      if (Minutos == (28)) {

        digitalWrite(7, HIGH);
        delay(250);
        digitalWrite(7, LOW);
        delay(250);
        digitalWrite(7, HIGH);
        delay(250);
        digitalWrite(7, LOW);
        delay(250);
        digitalWrite(7, HIGH);
        delay(250);

        digitalWrite(7, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        //Serial.println("Amarilo");
      }

      //Tiempo antes de la activación de la luz roja (30 minutos)
      if (Minutos > (29)) {
        digitalWrite(6, HIGH);
        delay(250);
        digitalWrite(6, LOW);
        delay(250);
        digitalWrite(6, HIGH);
        delay(250);
        digitalWrite(6, LOW);
        delay(250);
        digitalWrite(6, HIGH);
        delay(250);

        digitalWrite(7, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        // Serial.println("Rojo");
      }

      if (Minutos > 59) {
        Minutos = 0;
        Horas++;
        EEPROM.write(3, Horas);
      }
    }
  }
}
