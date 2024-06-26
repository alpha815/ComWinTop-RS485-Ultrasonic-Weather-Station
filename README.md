# ComWinTop-RS485-Ultrasonic-Weather-Station

Arduino PlatformIO sample project for Small weather station from ComWinTop.

## ComWImTop RS-485 Mini Weather Station Arduino Sample Code

This repository contains sample code for using the ComWImTop RS-485 mini weather station with an Arduino. The code demonstrates how to initialize the weather station sensor, retrieve data, and print the data to the serial monitor.
![image](https://github.com/alpha815/ComWinTop-RS485-Ultrasonic-Weather-Station/assets/56131964/d13b8c2e-f054-4384-a563-e830e2f9bc47)

## Hardware Setup

1. Connect the RS-485 to TTL converter module to your Arduino.
2. Connect the ComWImTop RS-485 mini weather station to the RS-485 converter module.
3. Ensure the connections are as follows:
   - RS-485 A+ to RS-485 A+
   - RS-485 B- to RS-485 B-
   - TTL RX to ESP32 TX (e.g., GPIO_NUM_32)
   - TTL TX to ESP32 RX (e.g., GPIO_NUM_33)
   - Power and ground connections.

## Usage

The sample code initializes the sensor and retrieves data periodically. The retrieved data includes wind speed, wind strength, wind direction (both cardinal and degrees), humidity, temperature, and pressure. The data is printed to the serial monitor for easy viewing.

## Initialization

The weather station sensor is initialized using the `Sensor` class, which requires the hardware serial port, and the TX and RX pin numbers for communication.

```cpp
Sensor env_sensor(&Serial1, GPIO_NUM_32, GPIO_NUM_33, 9600);
Functions Available
Checks if new data is available from the sensor. If new data is available, it is stored in the provided sensor_data_t structure:
getDataReady(sensor_data_t &data):

Data Structure
The sensor_data_t structure holds the sensor data:
struct sensor_data_t
{
    float airSpeed;            // Air speed in meters per second (m/s)
    int airStrength;           // Air strength (wind strength) in dimensionless units
    int windDirectionCardinal; // Wind direction (cardinal) in degrees (0-360)
    int windDirectionDegrees;  // Wind direction in degrees
    float humidity;            // Humidity in percentage (%RH)
    float temperature;         // Temperature in degrees Celsius (°C)
    float pressure;            // Pressure in kilopascals (kPa)
};
output:

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

```

