#pragma once

#include <stdint.h>
#include "HWPort.hpp"

class LSM303DLHC_ACC:HWPort {

private: // --------------------------------------------------------------------  
    enum LSM303DLHC_ACC_REG {
        ACC_I2C_ADDRESS = (0x32 >> 1),
        WHO_AM_I_ADDR = 0x0F,  // device identification register 
        CTRL_REG1 = 0x20,  // Control register 1 acceleration 
        CTRL_REG2 = 0x21,  // Control register 2 acceleration 
        CTRL_REG3 = 0x22,  // Control register 3 acceleration 
        CTRL_REG4 = 0x23,  // Control register 4 acceleration 
        CTRL_REG5 = 0x24,  // Control register 5 acceleration 
        CTRL_REG6 = 0x25,  // Control register 6 acceleration 
        REFERENCE = 0x26,  // Reference register acceleration 
        STATUS_REG = 0x27,  // Status register acceleration 
        OUT_X_L = 0x28,  // Output Register X acceleration 
        OUT_X_H = 0x29,  // Output Register X acceleration 
        OUT_Y_L = 0x2A,  // Output Register Y acceleration 
        OUT_Y_H = 0x2B,  // Output Register Y acceleration 
        OUT_Z_L = 0x2C,  // Output Register Z acceleration 
        OUT_Z_H = 0x2D,  // Output Register Z acceleration 
        FIFO_CTRL_REG = 0x2E,  // Fifo control Register acceleration 
        FIFO_SRC_REG = 0x2F,  // Fifo src Register acceleration 
        INT1_CFG = 0x30,  // Interrupt 1 configuration Register acceleration 
        INT1_SOURCE = 0x31,  // Interrupt 1 source Register acceleration 
        INT1_THS = 0x32,  // Interrupt 1 Threshold register acceleration 
        INT1_DURATION = 0x33,  // Interrupt 1 DURATION register acceleration 
        INT2_CFG = 0x34,  // Interrupt 2 configuration Register acceleration 
        INT2_SOURCE = 0x35,  // Interrupt 2 source Register acceleration 
        INT2_THS = 0x36,  // Interrupt 2 Threshold register acceleration 
        INT2_DURATION = 0x37,  // Interrupt 2 DURATION register acceleration 
        CLICK_CFG = 0x38,  // Click configuration Register acceleration 
        CLICK_SOURCE = 0x39,  // Click 2 source Register acceleration 
        CLICK_THS = 0x3A,  // Click 2 Threshold register acceleration 
        TIME_LIMIT = 0x3B,  // Time Limit Register acceleration 
        TIME_LATENCY = 0x3C,  // Time Latency Register acceleration 
        TIME_WINDOW = 0x3D,  // Time window register acceleration 
    };
    // --------------------------------------------------------------------  

public: // --------------------------------------------------------------------  
    typedef enum {
        OnOdr_POWER_DOWN = 0x00,
        OnOdr_1_Hz = 0x17,
        OnOdr_10_Hz = 0x27,
        OnOdr_25_Hz = 0x37,
        OnOdr_50_Hz = 0x47,
        OnOdr_100_Hz = 0x57,
        OnOdr_200_Hz = 0x67,
        OnOdr_400_Hz = 0x77,
        // OnOdr_1620_Hz_LPM = 0x8f,
        // OnOdr_1344_Hz = 0x97,
        // OnOdr_5376_Hz_LPM = 0x9f,
    } OnOdr_t;

    typedef enum {
        HpfFreq_odr1_0_02 = 0x00,
        HpfFreq_odr1_0_008 = 0x10,
        HpfFreq_odr1_0_004 = 0x20,
        HpfFreq_odr1_0_002 = 0x30,
        HpfFreq_odr10_0_2 = 0x00,
        HpfFreq_odr10_0_08 = 0x10,
        HpfFreq_odr10_0_04 = 0x20,
        HpfFreq_odr10_0_02 = 0x30,
        HpfFreq_odr25_0_5 = 0x00,
        HpfFreq_odr25_0_2 = 0x10,
        HpfFreq_odr25_0_1 = 0x20,
        HpfFreq_odr25_0_05 = 0x30,
        HpfFreq_odr50_1 = 0x00,
        HpfFreq_odr50_0_5 = 0x10,
        HpfFreq_odr50_0_2 = 0x20,
        HpfFreq_odr50_0_1 = 0x30,
        HpfFreq_odr100_2 = 0x00,
        HpfFreq_odr100_1 = 0x10,
        HpfFreq_odr100_0_5 = 0x20,
        HpfFreq_odr100_0_2 = 0x30,
        HpfFreq_odr200_4 = 0x00,
        HpfFreq_odr200_2 = 0x10,
        HpfFreq_odr200_1 = 0x20,
        HpfFreq_odr200_0_5 = 0x30,
        HpfFreq_odr400_8 = 0x00,
        HpfFreq_odr400_4 = 0x10,
        HpfFreq_odr400_2 = 0x20,
        HpfFreq_odr400_1 = 0x30,
        HpfFreq_odr1600_32 = 0x00,
        HpfFreq_odr1600_16 = 0x10,
        HpfFreq_odr1600_8 = 0x20,
        HpfFreq_odr1600_4 = 0x30,
        HpfFreq_odr5000_100 = 0x00,
        HpfFreq_odr5000_50 = 0x10,
        HpfFreq_odr5000_25 = 0x20,
        HpfFreq_odr5000_12 = 0x30,
    } HpfFreq_t;

    typedef enum {
        HpfMode_normal = 0x00,
        HpfMode_reference = 0x40,
        HpfMode_normal2 = 0x80,
        HpfMode_autoresetInt = 0xc0,
    } HpfMode_t;

    typedef enum {
        FullScaleSelect_2_g = 0x08,
        FullScaleSelect_4_g = 0x18,
        FullScaleSelect_8_g = 0x28,
        FullScaleSelect_16_g = 0x38,
    } FullScaleSelect_t;
    // --------------------------------------------------------------------  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: // -------------------------------------------------------------------- 
    FullScaleSelect_t fullScaleGlobal;
    float fullScale2gToG(int16_t lsb, int8_t axis);
    float fullScale4gToG(int16_t lsb, int8_t axis);
    float fullScale8gToG(int16_t lsb, int8_t axis);
    float fullScale16gToG(int16_t lsb, int8_t axis);
    void dataReadyInt1_set();
    // --------------------------------------------------------------------  

public:// -------------------------------------------------------------------- 
    // pobranie id accel
    uint8_t whoAmI();
    const uint8_t id = 0x33; // id które powinno być pobrane po wywołaniu metody whoAmI()
    // zerowanie rejestrów wewnętrznych w accel
    void resetSoft();
    // włączenie accel i ustawienie częstotliwości
    void on(OnOdr_t val);
    // ustawienie zakresu działania accela
    void fullScaleSelect_set(FullScaleSelect_t val);
    // częstotliwość HPF
    void hpfFreq_set(HpfFreq_t val);
    // HPF on
    void hpfOn_set(bool val);
    // tryb pracy HPF
    void hpfMode_set(HpfMode_t val);
    // DS
    void hpfReference_set(uint8_t val);
    // pobranie do bufora danych surowych ale ze znakiem
    void dataRaw_get(int16_t* buff);
     // pobranie danych accela w jednostkach [g]
    void data_get(float* buff);
    // konstruktor przyjmuje wskaźnik do funkcji przerwania data ready
    LSM303DLHC_ACC(void(*irqDRD)(void));
    ~LSM303DLHC_ACC();
    // --------------------------------------------------------------------
};

// MAGNTOMETR /////////////////////////////////////////////////////////////////////////////////////
class LSM303DLHC_MAG {

private: // --------------------------------------------------------------------  
    enum LSM303DLHC_MAG_REG {
        MAG_I2C_ADDRESS = (0x3C >> 1),
        CRA_REG_M = 0x00,  // Control register A magnetic field 
        CRB_REG_M = 0x01,  // Control register B magnetic field 
        MR_REG_M = 0x02,  // Control register MR magnetic field 
        OUT_X_H_M = 0x03,  // Output Register X magnetic field 
        OUT_X_L_M = 0x04,  // Output Register X magnetic field 
        OUT_Z_H_M = 0x05,  // Output Register Z magnetic field 
        OUT_Z_L_M = 0x06,  // Output Register Z magnetic field 
        OUT_Y_H_M = 0x07,  // Output Register Y magnetic field 
        OUT_Y_L_M = 0x08,  // Output Register Y magnetic field 
        SR_REG_M = 0x09,  // Status Register magnetic field 
        IRA_REG_M = 0x0A,  // IRA Register magnetic field 
        IRB_REG_M = 0x0B,  // IRB Register magnetic field 
        IRC_REG_M = 0x0C,  // IRC Register magnetic field 
        TEMP_OUT_H_M = 0x31,  // Temperature Register magnetic field 
        TEMP_OUT_L_M = 0x32  // Temperature Register magnetic field 
    };
    // --------------------------------------------------------------------  

public: // --------------------------------------------------------------------  
    // --------------------------------------------------------------------  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: // --------------------------------------------------------------------  
    // --------------------------------------------------------------------  

public:// --------------------------------------------------------------------  
    LSM303DLHC_MAG();
    ~LSM303DLHC_MAG();
    // --------------------------------------------------------------------  

};


