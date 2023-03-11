#include "LibLSM303DLHC.hpp"

// private -------------------------------------------------------------------- 
float  LSM303DLHC_ACC::fullScale2gToG(int16_t lsb, int8_t axis) {
    switch (axis) {
    case 1:
        if (lsb > 0) {
            return ((float)lsb * 0.00006133464);
        }
        else {
            return ((float)lsb * 0.00005841121);
        }
        break;
    case 2:
        if (lsb > 0) {
            return ((float)lsb * 0.00006194251);
        }
        else {
            return ((float)lsb * 0.00006167129);
        }
        break;
    case 3:
        if (lsb > 0) {
            return ((float)lsb * 0.00006469979);
        }
        else {
            return ((float)lsb * 0.00006133464);
        }
        break;
    default:
        break;
    }
    return 0;
}

float  LSM303DLHC_ACC::fullScale4gToG(int16_t lsb, int8_t axis) {
    switch (axis) {
    case 1:
        if (lsb > 0) {
            return ((float)lsb * 0.0001242544);
        }
        else {
            return ((float)lsb * 0.0001242544);
        }
        break;
    case 2:
        if (lsb > 0) {
            return ((float)lsb * 0.0001242544);
        }
        else {
            return ((float)lsb * 0.0001242544);
        }
        break;
    case 3:
        if (lsb > 0) {
            return ((float)lsb * 0.0001310272);
        }
        else {
            return ((float)lsb * 0.0001237623);
        }
        break;
    default:
        break;
    }
    return 0;
}

float  LSM303DLHC_ACC::fullScale8gToG(int16_t lsb, int8_t axis) {
    switch (axis) {
    case 1:
        if (lsb > 0) {
            return ((float)lsb * 0.0002470355);
        }
        else {
            return ((float)lsb * 0.0002470355);
        }
        break;
    case 2:
        if (lsb > 0) {
            return ((float)lsb * 0.0002470355);
        }
        else {
            return ((float)lsb * 0.0002470355);
        }
        break;
    case 3:
        if (lsb > 0) {
            return ((float)lsb * 0.0002637130);
        }
        else {
            return ((float)lsb * 0.0002460629);
        }
        break;
    default:
        break;
    }
    return 0;
}

float  LSM303DLHC_ACC::fullScale16gToG(int16_t lsb, int8_t axis) {
    switch (axis) {
    case 1:
        if (lsb > 0) {
            return ((float)lsb * 0.0007692307);
        }
        else {
            return ((float)lsb * 0.0007692307);
        }
        break;
    case 2:
        if (lsb > 0) {
            return ((float)lsb * 0.0007692307);
        }
        else {
            return ((float)lsb * 0.0007692307);
        }
        break;
    case 3:
        if (lsb > 0) {
            return ((float)lsb * 0.0007911392);
        }
        else {
            return ((float)lsb * 0.0007621951);
        }
        break;
    default:
        break;
    }
    return 0;
}

void LSM303DLHC_ACC::dataReadyInt1_set() {
    uint8_t reg;
    readReg(CTRL_REG3, &reg);
    reg |= 0x10;
    writeReg(CTRL_REG3, reg);
}

// public ----------------------------------------------------------------------
uint8_t LSM303DLHC_ACC::whoAmI() {
    uint8_t reg;
    readReg(WHO_AM_I_ADDR, &reg);
    return reg;
}

void LSM303DLHC_ACC::resetSoft() {
    // reset do stanów początkowych ponieważ po sof resecie sią nie kasują
    writeReg(CTRL_REG1, 0x00);
    writeReg(CTRL_REG2, 0x00);
    writeReg(CTRL_REG3, 0x00);
    writeReg(CTRL_REG4, 0x00);
    writeReg(CTRL_REG5, 0x00);
    writeReg(CTRL_REG6, 0x00);
    writeReg(REFERENCE, 0x00);
    writeReg(FIFO_CTRL_REG, 0x00);
    writeReg(INT1_CFG, 0x00);
    writeReg(INT1_THS, 0x00);
    writeReg(INT1_DURATION, 0x00);
    writeReg(INT2_CFG, 0x00);
    writeReg(INT2_THS, 0x00);
    writeReg(INT2_DURATION, 0x00);
    writeReg(CLICK_CFG, 0x00);
    writeReg(CLICK_SOURCE, 0x00);
    writeReg(CLICK_THS, 0x00);
    writeReg(TIME_LIMIT, 0x00);
    writeReg(TIME_LATENCY, 0x00);
    writeReg(TIME_WINDOW, 0x00);
    writeReg(CTRL_REG5, 0x80);
}

void LSM303DLHC_ACC::on(OnOdr_t val) {
    dataReadyInt1_set();
    waitMs(10);
    writeReg(CTRL_REG1, val);
    waitMs(250);
}

void LSM303DLHC_ACC::fullScaleSelect_set(FullScaleSelect_t val) {
    fullScaleGlobal = val;
    writeReg(CTRL_REG4, val);
}

void LSM303DLHC_ACC::hpfFreq_set(HpfFreq_t val) {
    uint8_t reg;
    readReg(CTRL_REG2, &reg);
    reg &= 0xcf;
    reg |= val;
    writeReg(CTRL_REG2, reg);
}

void LSM303DLHC_ACC::hpfOn_set(bool val) {
    if (val) {
        uint8_t reg;
        readReg(CTRL_REG2, &reg);
        reg |= 0x08;
        writeReg(CTRL_REG2, reg);
    }
    else {
        uint8_t reg;
        readReg(CTRL_REG2, &reg);
        reg &= 0xf7;
        writeReg(CTRL_REG2, reg);
    }
}

void LSM303DLHC_ACC::hpfMode_set(HpfMode_t val) {
    uint8_t reg;
    readReg(CTRL_REG2, &reg);
    reg &= 0x3f;
    reg |= val;
    writeReg(CTRL_REG2, reg);
}

void LSM303DLHC_ACC::hpfReference_set(uint8_t val) {
    writeReg(REFERENCE, val);
}


void LSM303DLHC_ACC::dataRaw_get(int16_t* buff) {
    uint8_t buff8[6];
    readReg(OUT_X_L, &buff8[0]);
    readReg(OUT_X_H, &buff8[1]);
    readReg(OUT_Y_L, &buff8[2]);
    readReg(OUT_Y_H, &buff8[3]);
    readReg(OUT_Z_L, &buff8[4]);
    readReg(OUT_Z_H, &buff8[5]);
    buff[0] = ((uint16_t)buff8[1] << 8) | buff8[0];
    buff[1] = ((uint16_t)buff8[3] << 8) | buff8[2];
    buff[2] = ((uint16_t)buff8[5] << 8) | buff8[4];
}

void LSM303DLHC_ACC::data_get(float* buff) {
    uint8_t buff8[6];
    readReg(OUT_X_L, &buff8[0]);
    readReg(OUT_X_H, &buff8[1]);
    readReg(OUT_Y_L, &buff8[2]);
    readReg(OUT_Y_H, &buff8[3]);
    readReg(OUT_Z_L, &buff8[4]);
    readReg(OUT_Z_H, &buff8[5]);
    int16_t buff16[3];
    buff16[0] = ((uint16_t)buff8[1] << 8) | buff8[0];
    buff16[1] = ((uint16_t)buff8[3] << 8) | buff8[2];
    buff16[2] = ((uint16_t)buff8[5] << 8) | buff8[4];

    switch (fullScaleGlobal) {
    case  FullScaleSelect_2_g:
        buff[0] = fullScale2gToG(buff16[0], 1);
        buff[1] = fullScale2gToG(buff16[1], 2);
        buff[2] = fullScale2gToG(buff16[2], 3);
        break;
    case  FullScaleSelect_4_g:
        buff[0] = fullScale4gToG(buff16[0], 1);
        buff[1] = fullScale4gToG(buff16[1], 2);
        buff[2] = fullScale4gToG(buff16[2], 3);
        break;
    case  FullScaleSelect_8_g:
        buff[0] = fullScale8gToG(buff16[0], 1);
        buff[1] = fullScale8gToG(buff16[1], 2);
        buff[2] = fullScale8gToG(buff16[2], 3);
        break;
    case  FullScaleSelect_16_g:
        buff[0] = fullScale16gToG(buff16[0], 1);
        buff[1] = fullScale16gToG(buff16[1], 2);
        buff[2] = fullScale16gToG(buff16[2], 3);
        break;

    default:
        buff[0] = 0; buff[1] = 0; buff[2] = 0;
        break;
    }
}

LSM303DLHC_ACC::LSM303DLHC_ACC(void(*irqDRD)(void)) {
    init(irqDRD, ACC_I2C_ADDRESS);
}
LSM303DLHC_ACC::~LSM303DLHC_ACC() {}

// MAGNTOMETR /////////////////////////////////////////////////////////////////////////////////////
// private -------------------------------------------------------------------- 
// public ---------------------------------------------------------------------
LSM303DLHC_MAG::LSM303DLHC_MAG() {}
LSM303DLHC_MAG::~LSM303DLHC_MAG() {}