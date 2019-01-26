/*
  Project : Alarma en tiempo real IOT
  Version : 1.0
  Date    : 30/01/2018
  Author  : Carlos Andres Betancourt
  Company : Ingeanialo Industrias
  Comments: Sensor termohigrometro inalambrico con autonomia de 1000 horas

  Chip type               : ATmega328P-AU
  Program type            : Application
  AVR Core Clock frequency: 8.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 512
  commit: La autonomia se consigue enviando datos con frecuencia de 5 minutos
  ------------------------------------------------------------
  Conexiones electricas

  Modulo NFR24L01P de baja potencia con antena integrada
  1 VSS pin to ground
  2 VCC pin to 3.3V
  3 CE pin to digital pin 2
  4 CSN pin to digital pin 3
  5 SCK pin to SCK pin in arduino (13 en Pro mini)
  6 MOSI pin to MOSI pin in arduino (11 en Pro mini)
  7 MISO pin to MISO pin in arduino (12 en Pro mini)
  8 IRQ pin to digital pin 5

  Sensor termohigrometro SHT20
  1 VSS pin to ground
  2 VCC pin to 3.3V
  3 SDA pin to SDA pin in Arduino (A4 en pro mini)
  4 SCL pin to SCL pin in arduino (A5 en pro mini)

  ---------------------------------------------------------------*/

//Incluimos las librerias y archivos de cabecera necesarios
#include <LiquidCrystal.h>
#include <LowPower.h>
#include <Wire.h>
#include "DFRobot_SHT20.h"
#include "Descriptors.h"
//-------------------------------------------------------------

//Instanciamos los objetos de las librerias
LiquidCrystal lcd(RS, RW, EN, D4, D5, D6, D7); //Display LCD 1602
DFRobot_SHT20 sht20;    //Sensor termohigrometro SHT20
//-------------------------------------------------------------

//Declaramos las variables necesarias
//-------------------------------------------------------------

//Definimos las estructuras
typedef struct {
  float temp;     //almacena datos de temperatura en Celsius (ºC)
  float hum;      //almacena datos de humedad relativa (RH%)
}
sensor;
//--------------------------------------------------------------

//Declaramos las estrcuturas
sensor s1;
//--------------------------------------------------------------

void setup() {
  pinMode(MOT, OUTPUT);
  pinMode(BOM, OUTPUT);

  sht20.initSHT20();    //inciamos el sensor SHT20
  delay(100);
  sht20.checkSHT20();   //Chequeamos la conexion con el sensor

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
  while (s1.temp > 120) {
    sht20.initSHT20();    //inciamos el sensor SHT20
    delay(100);
    sht20.checkSHT20();   //Chequeamos la conexion con el sensor
    delay(100);
    s1.temp = sht20.readTemperature();  //leemos la temperatura
    delayMicroseconds(100);
    
    mostrar_error(2,0);
  }

  //Realizamos las mediciones de temperatura y humedad
  s1.temp = sht20.readTemperature();  //leemos la temperatura
  delayMicroseconds(100);
  s1.hum = sht20.readHumidity();      //leemos la humedad
  delayMicroseconds(100);

  //Visualizamos los datos en la LCD
  mostrar_temp(2 , 0, s1.temp);
  mostrar_hum(2, 1, s1.hum);

  //Comparaciones de temperatura
  if (s1.temp < 37.2) {
    digitalWrite(MOT, HIGH);
    digitalWrite(BOM, HIGH);
  }
  else if (s1.temp > 38.2) {
    digitalWrite(MOT, LOW);
    digitalWrite(BOM, LOW);
  }
}
