#include "HWPort.hpp"

void HWPort::init(void (*irqDRD)(void), uint8_t i2cAddress) {
    myI2cAddress = i2cAddress;
    pinMode(ACC_INT1, INPUT);
    attachInterrupt(ACC_INT1, irqDRD, RISING);
    delay(10);
    myI2C.begin();
    myI2C.setClock(400000);
}

void HWPort::readReg(uint8_t reg, uint8_t* data) {
    myI2C.beginTransmission(myI2cAddress);
    myI2C.write(reg);
    myI2C.endTransmission();
    myI2C.requestFrom(myI2cAddress, 1);
    *data = myI2C.read();
}

void HWPort::writeReg(uint8_t reg, uint8_t data) {
    myI2C.beginTransmission(myI2cAddress);
    myI2C.write(reg);
    myI2C.write(data);
    myI2C.endTransmission(true);
}

HWPort::HWPort() {
    myI2C.setSCL(I2C_SCL);
    myI2C.setSDA(I2C_SDA);
}

HWPort::~HWPort() {
    myI2C.end();
}
