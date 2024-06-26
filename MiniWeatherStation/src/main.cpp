#include <Arduino.h>
#include <HardwareSerial.h>
#include "Sensor.h"

Sensor env_sensor(&Serial1, GPIO_NUM_32, GPIO_NUM_33, 9600);
sensor_data_t data;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
}

void loop()
{

  if (env_sensor.getDataReady(data))
  {

    printf("Wind Speed: %.2f m/s\n", data.airSpeed);
    printf("Wind Strength: %d \n", data.airStrength);
    printf("Wind Direction (Cardinal): %d\n", data.windDirectionCardinal);
    printf("Wind Direction (Degrees): %d°\n", data.windDirectionDegrees);
    printf("Humidity: %.1f %%RH\n", data.humidity);
    printf("Temperature: %.1f °C\n", data.temperature);
    printf("Pressure: %.1f kPa\n", data.pressure);
  }
  delay(5000);
}
