#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Define a struct to hold sensor data
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

class Sensor
{
public:
    Sensor();
    Sensor(HardwareSerial *serialPort, gpio_num_t rx, gpio_num_t tx, long baudRate);
    bool getDataReady(sensor_data_t& sensor_data);

private:
    HardwareSerial *_serialPort;
    long _baudRate;
    void _sensor_Write();
    bool _sensor_Read(sensor_data_t& _data);
    byte _rx_buff[45] = {};
};

#endif // SENSOR_H
