// portowanie sprzętu 
// obsługa SPI
// obsługa przerwania data ready

#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

//klasa podpięcia biblioteki do sprzętu, pod każdy inny sprzęt musi być napisana od nowa
class HWPort {
private:
    // piny sprzętowe
    enum {
        SPI1_SCK = PA5,
        SPI1_MOSI = PA7,
        SPI1_MISO = PA6,
        SPI1_CS = PE3,
        GYRO_INT2 = PE1,    //data ready
        GYRO_INT1 = PE0     //nie wykorzystany
    };

    SPIClass SPI_1; //główny obiekt spi, konfiguracja pinów w konstruktorze

    inline void csLow() { digitalWrite(SPI1_CS, 0); }
    inline void csHigh() { digitalWrite(SPI1_CS, 1); }

protected:
    // odczyt pojedynczej wartości z rejestru
    void readReg(uint8_t reg, uint8_t* data);
    // odczyt kilku rejestrów po kolei 
    void readReg(uint8_t reg, uint8_t* data, uint16_t len);
    // zapis do pojedynczego rejestru
    void writeReg(uint8_t reg, uint8_t data);
    inline void waitMs(uint32_t val) { delay(val); }

public:
    //inicjalizacja pinów, przerwania i SPI, metoda przyjmuje jako parametr wskaźnik do funkcji przerwania data ready
    void init(void(*irqDRD)(void));
    HWPort();
    ~HWPort();
};
