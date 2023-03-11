// portowanie sprzętu 
// obsługa i2c
// obsługa przerwania data ready

#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

//klasa podpięcia biblioteki do sprzętu, pod każdy inny sprzęt musi być napisana od nowa
class HWPort {
private:
    // piny sprzętowe
    enum {
        I2C_SDA = PB9,
        I2C_SCL = PB6,
        ACC_INT2 = PE5,     //nie używane
        ACC_INT1 = PE4,     //data redy  
        ACC_DRDY = PE2      //nie używane
    };

uint8_t myI2cAddress;

TwoWire myI2C;//(PB9, PB6);  //sda,scl

protected:
    // odczyt pojedynczej wartości z rejestru
    void readReg(uint8_t reg, uint8_t* data);
    // zapis do pojedynczego rejestru
    void writeReg(uint8_t reg, uint8_t data);
    inline void waitMs(uint32_t val) { delay(val); }

public:
    //inicjalizacja pinów, przerwania i SPI, metoda przyjmuje jako parametr wskaźnik do funkcji przerwania data ready
    void init(void(*irqDRD)(void), uint8_t i2cAddress);
    HWPort();
    ~HWPort();
};
