/***************************************************************************
  This is a library for the BMP280 pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  
  Updated by Nathan Heskew for Particle Photon
  
  Updated by Nick Granger-Brown to expose extra functions
  
 ***************************************************************************/
#ifndef __BMP280_H__
#define __BMP280_H__


#include "application.h"
#include "Adafruit_Sensor.h"

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define BMP280_ADDRESS                (0x77)
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    enum
    {
      BMP280_REGISTER_DIG_T1              = 0x88,
      BMP280_REGISTER_DIG_T2              = 0x8A,
      BMP280_REGISTER_DIG_T3              = 0x8C,

      BMP280_REGISTER_DIG_P1              = 0x8E,
      BMP280_REGISTER_DIG_P2              = 0x90,
      BMP280_REGISTER_DIG_P3              = 0x92,
      BMP280_REGISTER_DIG_P4              = 0x94,
      BMP280_REGISTER_DIG_P5              = 0x96,
      BMP280_REGISTER_DIG_P6              = 0x98,
      BMP280_REGISTER_DIG_P7              = 0x9A,
      BMP280_REGISTER_DIG_P8              = 0x9C,
      BMP280_REGISTER_DIG_P9              = 0x9E,

      BMP280_REGISTER_CHIPID             = 0xD0,
      BMP280_REGISTER_VERSION            = 0xD1,
      BMP280_REGISTER_SOFTRESET          = 0xE0,

      BMP280_REGISTER_CAL26              = 0xE1,  // R calibration stored in 0xE1-0xF0

      BMP280_REGISTER_CONTROL            = 0xF4,
      BMP280_REGISTER_CONFIG             = 0xF5,
      BMP280_REGISTER_PRESSUREDATA       = 0xF7,
      BMP280_REGISTER_TEMPDATA           = 0xFA,
    };
       
/*=========================================================================
    CONTROL REGISTER (0xF4) values
    -----------------------------------------------------------------------*/
    enum
    {
        BMP280_CTRL_TEMP_SKIP            = 0<<5;
        BMP280_CTRL_TEMP_OS_1            = 1<<5;
        BMP280_CTRL_TEMP_OS_2            = 2<<5;
        BMP280_CTRL_TEMP_OS_4            = 3<<5;
        BMP280_CTRL_TEMP_OS_8            = 4<<5;
        BMP280_CTRL_TEMP_OS_16           = 5<<5;
    };

    enum
    {
        BMP280_CTRL_PRES_SKIP            = 0<<2;
        BMP280_CTRL_PRES_OS_1            = 1<<2;
        BMP280_CTRL_PRES_OS_2            = 2<<2;
        BMP280_CTRL_PRES_OS_4            = 3<<2;
        BMP280_CTRL_PRES_OS_8            = 4<<2;
        BMP280_CTRL_PRES_OS_16           = 5<<2;
    };
    
    enum
    {
        BMP280_CTRL_MODE_SLEEP           = 0;
        BMP280_CTRL_MODE_FORCED          = 1;
        BMP280_CTRL_MODE_NORMAL          = 3;
    };
 
/*=========================================================================
    CONFIGURATION REGISTER (0xF5) values
    -----------------------------------------------------------------------*/
    enum
    {
        BMP280_CNF_FILTER_OFF            = 0<<2;
        BMP280_CNF_FILTER_C1             = 1<<2;
        BMP280_CNF_FILTER_C2             = 2<<2;
        BMP280_CNF_FILTER_C4             = 3<<2;
        BMP280_CNF_FILTER_C8             = 4<<2;
        BMP280_CNF_FILTER_C16            = 5<<2;
    };
    
    enum
    {
        BMP280_CNF_SMPL_0m5              = 0<<5;
        BMP280_CNF_SMPL_62m5             = 1<<5;
        BMP280_CNF_SMPL_125m             = 2<<5;
        MBP280_CNF_SMPL_250m             = 3<<5;
        BMP280_CNF_SMPL_500m             = 4<<5;
        BMP280_CNF_SMPL_1000m            = 5<<5;
        BMP280_CNF_SMPL_2000m            = 6<<5;
        BMP280_CNF_SMPL_4000m            = 7<<5;
    };
    
    enum
    {
        BMP_CNF_SPI_3WIRE                = 1;
    }
/*=========================================================================*/

/*=========================================================================
    CALIBRATION DATA
    -----------------------------------------------------------------------*/
    typedef struct
    {
      uint16_t dig_T1;
      int16_t  dig_T2;
      int16_t  dig_T3;

      uint16_t dig_P1;
      int16_t  dig_P2;
      int16_t  dig_P3;
      int16_t  dig_P4;
      int16_t  dig_P5;
      int16_t  dig_P6;
      int16_t  dig_P7;
      int16_t  dig_P8;
      int16_t  dig_P9;

      uint8_t  dig_H1;
      int16_t  dig_H2;
      uint8_t  dig_H3;
      int16_t  dig_H4;
      int16_t  dig_H5;
      int8_t   dig_H6;
    } bmp280_calib_data;
/*=========================================================================*/

/*
class Adafruit_BMP280_Unified : public Adafruit_Sensor
{
  public:
    Adafruit_BMP280_Unified(int32_t sensorID = -1);

    bool  begin(uint8_t addr = BMP280_ADDRESS);
    void  getTemperature(float *temp);
    void  getPressure(float *pressure);
    float pressureToAltitude(float seaLevel, float atmospheric, float temp);
    float seaLevelForAltitude(float altitude, float atmospheric, float temp);
    void  getEvent(sensors_event_t*);
    void  getSensor(sensor_t*);

  private:
    uint8_t   _i2c_addr;
    int32_t   _sensorID;
};

*/

class Adafruit_BMP280
{
  public:
    Adafruit_BMP280(void);
    Adafruit_BMP280(int8_t cspin);
    Adafruit_BMP280(int8_t cspin, int8_t mosipin, int8_t misopin, int8_t sckpin);

    bool  begin(uint8_t addr = BMP280_ADDRESS);
    float readTemperature(void);
    float readPressure(void);
    float readAltitude(float seaLevelhPa = 1013.25);
    void  writeRegister(uint8_t regNo, uint8_t value); 

  private:

    void readCoefficients(void);
    uint8_t spixfer(uint8_t x);

    void      write8(byte reg, byte value);
    uint8_t   read8(byte reg);
    uint16_t  read16(byte reg);
    int16_t   readS16(byte reg);
    uint16_t  read16_LE(byte reg); // little endian
    int16_t   readS16_LE(byte reg); // little endian

    uint8_t   _i2caddr;
    int32_t   _sensorID;
    int32_t t_fine;

    int8_t _cs, _mosi, _miso, _sck;

    bmp280_calib_data _bmp280_calib;

};

#endif
