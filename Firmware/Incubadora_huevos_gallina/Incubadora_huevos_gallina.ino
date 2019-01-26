/*
  Project : Incubadora huevos
  Version : 1.1
  Date    : 27/01/2019
  Author  : Carlos Andres Betancourt
  Company : Circuitos Creativos SAS
  Comments: Controlador ON-OFF rango 37.5-38.5 grados Celsius

  Chip type               : ATmega328P-AU
  Program type            : Application
  AVR Core Clock frequency: 8.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 512
  ------------------------------------------------------------
  Conexiones electricas

  Sensor temperatura DS18B20
  1 VSS pin to ground
  2 VCC pin to 3.3V
  3 OUT pin to A4 pin in Arduino
  ---------------------------------------------------------------*/

//Incluimos las librerias y archivos de cabecera necesarios
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <LowPower.h>
#include <OneWire.h>
#include "Descriptors.h"
//-------------------------------------------------------------

//Instanciamos los objetos de las librerias
LiquidCrystal lcd(RS, RW, EN, D4, D5, D6, D7); //Display LCD 1602
OneWire oneWire(WIRE_BUS); //pin de datos del DS18B20
DallasTemperature ds18b20(&oneWire);
//-------------------------------------------------------------

//Declaramos las variables necesarias
float temp;     //almacena datos de temperatura en Celsius (ºC)
String hum = "NO DATA";
//--------------------------------------------------------------

void setup() {
  pinMode(MOT, OUTPUT);
  pinMode(BOM, OUTPUT);

  ds18b20.begin();  //Iniciamos el sensor de temperatura

  lcd.begin(COLUMNA, FILA);

  lcd.setCursor(3, 0);
  lcd.print("INCUBADORA");
  lcd.setCursor(1, 1);
  lcd.print("HUEVOS GALLINA");
  delay(2000);
  lcd.clear();

  digitalWrite(MOT, LOW);
  digitalWrite(BOM, LOW);
}

void loop() {
  // ponemos el MCU en modo sleep por 2 segundos para ahorrar consumo de energia
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);

  //Condicion para verificar si el sensor esta conectado
  ds18b20.requestTemperatures(); //Prepara el sensor para la lectura
  //mostrar_error(2, 0);

  //Realizamos las mediciones de temperatura y humedad
  temp = ds18b20.getTempCByIndex(0);  //leemos la temperatura
  delayMicroseconds(100);

  //Visualizamos los datos en la LCD
  mostrar_temp(1 , 0, temp);
  mostrar_hum(1, 1, hum);

  //Comparaciones de temperatura
  if (temp < TEMP_MIN) {
  digitalWrite(MOT, HIGH);
    digitalWrite(BOM, HIGH);
  }
  else if (temp > TEMP_MAX) {
  digitalWrite(MOT, LOW);
    digitalWrite(BOM, LOW);
  }
}
