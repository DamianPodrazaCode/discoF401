#include "HWPort.hpp"

void HWPort::init(void(*irqDRD)(void)) {
    pinMode(GYRO_INT2, INPUT);
    attachInterrupt(GYRO_INT2, irqDRD, RISING);

    pinMode(SPI1_CS, OUTPUT);
    csHigh();
    delay(10);
    SPI_1.begin();
}

void HWPort::readReg(uint8_t reg, uint8_t* data) {
    csLow();
    SPI_1.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    SPI_1.transfer(reg | 0x80);
    *data = SPI_1.transfer(0x00);
    SPI_1.endTransaction();
    csHigh();
}

void HWPort::readReg(uint8_t reg, uint8_t* data, uint16_t len) {
    csLow();
    SPI_1.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    SPI_1.transfer(reg | 0xc0);
    SPI_1.transfer(data, len);
    SPI_1.endTransaction();
    csHigh();
}

void HWPort::writeReg(uint8_t reg, uint8_t data) {
    csLow();
    SPI_1.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    SPI_1.transfer(reg);
    SPI_1.transfer(data);
    SPI_1.endTransaction();
    csHigh();
}

HWPort::HWPort() {
    SPI_1.setMOSI(SPI1_MOSI);
    SPI_1.setMISO(SPI1_MISO);
    SPI_1.setSCLK(SPI1_SCK);
}

HWPort::~HWPort() {
    SPI_1.end();
}
