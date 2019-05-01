#include "DHT.h"
#define DHTPIN 2     // к какому пину будет подключен вывод Data

// подключаем библиотеку I2C:
#include <Wire.h>
// подключаем библиотеку датчика BH1750:
#include <BH1750.h>

//выбор используемого датчика
#define DHTTYPE DHT11   // DHT 11 

//инициализация датчика
DHT dht(DHTPIN, DHTTYPE);

// объявляем объект lightMeter:
BH1750 lightMeter;

void setup() {
  Serial.begin(9600); 
  dht.begin();

  pinMode(13, OUTPUT);
  Serial.begin(9600); //инициализация послед. порта
  lightMeter.begin(); //инициализация датчика BH1750
}

void loop() {
  // чтение температуры и влажности займет примерно 250 миллисекунд
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // проверяем правильные ли данные получили
  if (isnan(t) || isnan(h)) {
    Serial.println("Error reading from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %t");
    Serial.print('\n');
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }

  //считываем показания с BH1750:
  uint16_t lux = lightMeter.readLightLevel();
  if(lux<80) digitalWrite(13,HIGH);
  else digitalWrite(13,LOW); 
  //выводим показания в послед. порт:
  Serial.print("Light: ");
  Serial.println(String(lux) + " lx");
  Serial.print("-------------------------");
  Serial.print('\n');
  delay(3000); //задержка 30 сек
  
}
