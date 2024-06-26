#include "Sensor.h"

byte _command[] = {
    0x01, // Address
    0x03, // Function Code
    0x01, // Start Address HI
    0xF4, // Start Address Lo
    0x00, // Number of Points HI
    0x10, // Number of Points Lo
    0x04, // Error Check Low
    0x08  // Error Check Hi
};

Sensor::Sensor()
{
}

Sensor::Sensor(HardwareSerial *serialPort, gpio_num_t rx, gpio_num_t tx, long baudRate)
{
    _serialPort = serialPort;
    _baudRate = baudRate;
    _serialPort->begin(_baudRate, SERIAL_8N1, rx, tx);
}

bool Sensor::getDataReady(sensor_data_t &sensor_data)
{
    _sensor_Write();
    delay(10);
    return _sensor_Read(sensor_data);
}

void Sensor::_sensor_Write()
{
    _serialPort->write(_command, sizeof(_command));
}

bool Sensor::_sensor_Read(sensor_data_t &_data)
{

    if (_serialPort->available())
    {
        _serialPort->readBytes(_rx_buff, sizeof(_rx_buff));
    }

    byte commandByte = _rx_buff[8];
    byte lengthByte = _rx_buff[10];

    uint16_t commandID = (uint16_t)commandByte;
    uint8_t dataLengthID = lengthByte;

    if (dataLengthID == 32)
    {
        _data.airSpeed = static_cast<float>((_rx_buff[11] << 8) | _rx_buff[12]) / 100.0; // Convert to m/s
        _data.airStrength = (_rx_buff[13] << 8) | _rx_buff[14];
        _data.windDirectionCardinal = (_rx_buff[15] << 8) | _rx_buff[16];
        _data.windDirectionDegrees = (_rx_buff[17] << 8) | _rx_buff[18];
        _data.humidity = static_cast<float>((_rx_buff[19] << 8) | _rx_buff[20]) / 10.0;    // Convert to %RH
        _data.temperature = static_cast<float>((_rx_buff[21] << 8) | _rx_buff[22]) / 10.0; // Convert to °C
        _data.pressure = static_cast<float>((_rx_buff[29] << 8) | _rx_buff[30]) / 10.0;    // Convert to kPa

        return true;
    }

    return false;
}
