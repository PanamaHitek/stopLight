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


  TimeRelatedEvents();
}

void TimeRelatedEvents() {
  SecondAfter = millis();
  if ((SecondAfter - SecondBefore) > 1000) {
    SecondBefore = SecondAfter;

    Segundos++;
    if (Segundos == 60) {
      Segundos = 0;
      Minutos++;
      EEPROM.write(2, Minutos);
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
