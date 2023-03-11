#pragma once

#include <stdint.h>
#include "HWPort.hpp"

class L3GD20:HWPort {

private: // --------------------------------------------------------------------  
  enum L3GD20_REG {
    I2C_ADD_L = 0xD5U,
    I2C_ADD_H = 0xD7U,
    WHO_AM_I = 0x0FU,
    CTRL1 = 0x20U,
    CTRL2 = 0x21U,
    CTRL3 = 0x22U,
    CTRL4 = 0x23U,
    CTRL5 = 0x24U,
    REFERENCE = 0x25U,
    OUT_TEMP = 0x26U,
    STATUS = 0x27U,
    OUT_X_L = 0x28U,
    OUT_X_H = 0x29U,
    OUT_Y_L = 0x2AU,
    OUT_Y_H = 0x2BU,
    OUT_Z_L = 0x2CU,
    OUT_Z_H = 0x2DU,
    FIFO_CTRL = 0x2EU,
    FIFO_SRC = 0x2FU,
    INT1_CFG = 0x30U,
    INT1_SRC = 0x31U,
    INT1_THS_XH = 0x32U,
    INT1_THS_XL = 0x33U,
    INT1_THS_YH = 0x34U,
    INT1_THS_YL = 0x35U,
    INT1_THS_ZH = 0x36U,
    INT1_THS_ZL = 0x37U,
    INT1_DURATION = 0x38U
  };
  // --------------------------------------------------------------------  

public: // --------------------------------------------------------------------  
  typedef enum {
    OnOdr_PowerDown = 0x00,
    OnOdr_SLEEP = 0x04,
    OnOdr_95Hz_lf1_32_lf2_12_5 = 0x0f,
    OnOdr_95Hz_lf1_32_lf2_25 = 0x1f,
    OnOdr_190Hz_lf1_54_lf2_12_5 = 0x4f,
    OnOdr_190Hz_lf1_54_lf2_25 = 0x5f,
    OnOdr_190Hz_lf1_54_lf2_50 = 0x6f,
    OnOdr_190Hz_lf1_54_lf2_70 = 0x7f,
    OnOdr_380Hz_lf1_78_lf2_20 = 0x8f,
    OnOdr_380Hz_lf1_78_lf2_25 = 0x9f,
    OnOdr_380Hz_lf1_78_lf2_50 = 0xaf,
    OnOdr_380Hz_lf1_78_lf2_110 = 0xbf,
    OnOdr_760Hz_lf1_93_lf2_30 = 0xcf,
    OnOdr_760Hz_lf1_93_lf2_35 = 0xdf,
    OnOdr_760Hz_lf1_93_lf2_50 = 0xef,
    OnOdr_760Hz_lf1_93_lf2_110 = 0xff
  } OnOdr_t;

  typedef enum {
    OutFilterSelect_hfOFF_lf2OFF = 0x00,
    OutFilterSelect_hfON_lf2OFF = 0x01,
    OutFilterSelect_hfOFF_lf2ON = 0x02,
    OutFilterSelect_hfON_lf2ON = 0x12,
  } OutFilterSelect_t;

  typedef enum {
    HpfFreq_odr95_8 = 0x00,
    HpfFreq_odr95_4 = 0x01,
    HpfFreq_odr95_2 = 0x02,
    HpfFreq_odr95_1 = 0x03,
    HpfFreq_odr95_0_5 = 0x04,
    HpfFreq_odr95_0_2 = 0x05,
    HpfFreq_odr95_0_1 = 0x06,
    HpfFreq_odr95_0_05 = 0x07,
    HpfFreq_odr95_0_02 = 0x08,
    HpfFreq_odr95_0_01 = 0x09,
    HpfFreq_odr190_15 = 0x00,
    HpfFreq_odr190_8 = 0x01,
    HpfFreq_odr190_4 = 0x02,
    HpfFreq_odr190_2 = 0x03,
    HpfFreq_odr190_1 = 0x04,
    HpfFreq_odr190_0_5 = 0x05,
    HpfFreq_odr190_0_2 = 0x06,
    HpfFreq_odr190_0_1 = 0x07,
    HpfFreq_odr190_0_05 = 0x08,
    HpfFreq_odr190_0_02 = 0x09,
    HpfFreq_odr380_30 = 0x00,
    HpfFreq_odr380_15 = 0x01,
    HpfFreq_odr380_8 = 0x02,
    HpfFreq_odr380_4 = 0x03,
    HpfFreq_odr380_2 = 0x04,
    HpfFreq_odr380_1 = 0x05,
    HpfFreq_odr380_0_5 = 0x06,
    HpfFreq_odr380_0_2 = 0x07,
    HpfFreq_odr380_0_1 = 0x08,
    HpfFreq_odr380_0_05 = 0x09,
    HpfFreq_odr760_56 = 0x00,
    HpfFreq_odr760_30 = 0x01,
    HpfFreq_odr760_15 = 0x02,
    HpfFreq_odr760_8 = 0x03,
    HpfFreq_odr760_4 = 0x04,
    HpfFreq_odr760_2 = 0x05,
    HpfFreq_odr760_1 = 0x06,
    HpfFreq_odr760_0_5 = 0x07,
    HpfFreq_odr760_0_2 = 0x08,
    HpfFreq_odr760_0_1 = 0x09
  } HpfFreq_t;

  typedef enum {
    HpfMode_normal = 0x00,
    HpfMode_reference = 0x10,
    HpfMode_normal2 = 0x20,
    HpfMode_INT1 = 0x30,
  } HpfMode_t;

  typedef enum {
    FullScaleSelect_250_dps = 0x00,
    FullScaleSelect_500_dps = 0x10,
    FullScaleSelect_2000_dps = 0x20,
  } FullScaleSelect_t;
  // --------------------------------------------------------------------  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: // --------------------------------------------------------------------  
  FullScaleSelect_t fullScaleGlobal;
  float fullScale250ToDps(int16_t lsb);
  float fullScale500ToDps(int16_t lsb);
  float fullScale2000ToDps(int16_t lsb);
  void dataReadyInt2_set();
  // --------------------------------------------------------------------  

public:// --------------------------------------------------------------------  
  // pobranie id gyro
  uint8_t whoAmI();
  const uint8_t id = 0xd4; // id które powinno być pobrane po wywołaniu metody whoAmI()
  // zerowanie rejestrów wewnętrznych w gyro
  void resetSoft();
  // włączenie gyro i ustawienie częstotliwości oraz filtrów dolnoprzepustowych
  // parametr val -> np. OnOdr_95Hz_lf1_32_lf2_12_5 to output data rate 95Hz, low pass filter1 32Hz, low pass filter2 12.5Hz, schemat połączeń wewnętrznych DS 
  void on(OnOdr_t val);
  // włączenie lub wyłączenie filtrów HPF i LPF2, filtr LPF1 jest włączany automatycznie przy metodzie on()
  void outFilterSelect(OutFilterSelect_t val);
  // częstotliwość HPF
  void hpfFreq_set(HpfFreq_t val);
  // tryb pracy HPF
  void hpfMode_set(HpfMode_t val);
  // DS
  void hpfReference_set(uint8_t val);
  // pobranie do bufora danych surowych ale ze znakiem
  void dataRaw_get(int16_t* buff);
  // pobranie danych gyro w jednostkach dps(stopni na sekundę)
  void data_get(float* buff);
  // ustawienie zakresu działania żyroskopu
  void fullScaleSelect_set(FullScaleSelect_t val);
  // konstruktor przyjmuje wskaźnik do funkcji przerwania data ready
  L3GD20(void(*irqDRD)(void));
  ~L3GD20();
  // --------------------------------------------------------------------  

};
