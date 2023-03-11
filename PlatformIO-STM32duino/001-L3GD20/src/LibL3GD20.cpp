#include "LibL3GD20.hpp"

// private --------------------------------------------------------------------  
float L3GD20::fullScale250ToDps(int16_t lsb) {
  return ((float)lsb * 0.00763f);
}

float L3GD20::fullScale500ToDps(int16_t lsb) {
  return ((float)lsb * 0.01526f);
}

float L3GD20::fullScale2000ToDps(int16_t lsb) {
  return ((float)lsb * 0.06107f);
}

void L3GD20::dataReadyInt2_set() {
  uint8_t reg;
  readReg(CTRL3, &reg);
  reg |= 0x08;
  writeReg(CTRL3, reg);
}

// public ----------------------------------------------------------------------
uint8_t L3GD20::whoAmI() {
  uint8_t reg;
  readReg(WHO_AM_I, &reg);
  return reg;
}

void L3GD20::resetSoft() {
  // reset do stanów początkowych ponieważ po soft resecie się nie kasują
  writeReg(CTRL1, 0x00);
  writeReg(CTRL2, 0x00);
  writeReg(CTRL3, 0x00);
  writeReg(CTRL4, 0x00);
  writeReg(CTRL5, 0x00);
  writeReg(REFERENCE, 0x00);
  writeReg(FIFO_CTRL, 0x00);
  writeReg(INT1_CFG, 0x00);
  writeReg(INT1_THS_XH, 0x00);
  writeReg(INT1_THS_XL, 0x00);
  writeReg(INT1_THS_YH, 0x00);
  writeReg(INT1_THS_YL, 0x00);
  writeReg(INT1_THS_ZH, 0x00);
  writeReg(INT1_THS_ZL, 0x00);
  writeReg(INT1_DURATION, 0x00);
  writeReg(CTRL5, 0x80); //soft reset}
}

void L3GD20::on(OnOdr_t val) {
  dataReadyInt2_set();
  waitMs(10);
  writeReg(CTRL1, val);
  waitMs(250);
}

void L3GD20::outFilterSelect(OutFilterSelect_t val) {
  writeReg(CTRL5, val);
}

void L3GD20::hpfFreq_set(HpfFreq_t val) {
  writeReg(CTRL2, val);
}

void L3GD20::hpfMode_set(HpfMode_t val) {
  uint8_t reg;
  readReg(CTRL2, &reg);
  reg |= val;
  writeReg(CTRL2, reg);
}

void L3GD20::hpfReference_set(uint8_t val) {
  writeReg(REFERENCE, val);
}

void L3GD20::dataRaw_get(int16_t* buff) {
  uint8_t buff8[6];
  readReg(OUT_X_L, buff8, 6);
  buff[0] = ((uint16_t)buff8[1] << 8) | buff8[0];
  buff[1] = ((uint16_t)buff8[3] << 8) | buff8[2];
  buff[2] = ((uint16_t)buff8[5] << 8) | buff8[4];
}

void L3GD20::data_get(float* buff) {
  uint8_t buff8[6];
  readReg(OUT_X_L, buff8, 6);
  int16_t buff16[3];
  buff16[0] = ((uint16_t)buff8[1] << 8) | buff8[0];
  buff16[1] = ((uint16_t)buff8[3] << 8) | buff8[2];
  buff16[2] = ((uint16_t)buff8[5] << 8) | buff8[4];

  switch (fullScaleGlobal) {
  case  FullScaleSelect_250_dps:
    buff[0] = fullScale250ToDps(buff16[0]);
    buff[1] = fullScale250ToDps(buff16[1]);
    buff[2] = fullScale250ToDps(buff16[2]);
    break;
  case  FullScaleSelect_500_dps:
    buff[0] = fullScale500ToDps(buff16[0]);
    buff[1] = fullScale500ToDps(buff16[1]);
    buff[2] = fullScale500ToDps(buff16[2]);
    break;
  case  FullScaleSelect_2000_dps:
    buff[0] = fullScale2000ToDps(buff16[0]);
    buff[1] = fullScale2000ToDps(buff16[1]);
    buff[2] = fullScale2000ToDps(buff16[2]);
    break;
  default:
    buff[0] = 0; buff[1] = 0; buff[2] = 0;
    break;
  }
}

void L3GD20::fullScaleSelect_set(FullScaleSelect_t val) {
  fullScaleGlobal = val;
  writeReg(CTRL4, val);
}

L3GD20::L3GD20(void(*irqDRD)(void)) {
  init(irqDRD);
}

L3GD20::~L3GD20() {}
