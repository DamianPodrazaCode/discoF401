#include <Arduino.h>
#include "LibLSM303DLHC.hpp"

volatile bool fDRDY = true;
void irqDataReady() {
    fDRDY = true;
}

LSM303DLHC_ACC myAccel(irqDataReady);

void setup() {

    uint8_t ret = myAccel.whoAmI();
    if (ret == myAccel.id) {
        myAccel.resetSoft();
        myAccel.fullScaleSelect_set(myAccel.FullScaleSelect_2_g);
        myAccel.hpfFreq_set(myAccel.HpfFreq_odr400_1);
        myAccel.hpfMode_set(myAccel.HpfMode_normal2);
        myAccel.hpfOn_set(true);
        myAccel.on(myAccel.OnOdr_400_Hz);
    }
    else { // error ID
        while (1) { 
            delay(1);
        }
    }
}

//int16_t buffi16[3];
float buffF[3];
char buffSerial[256];

void loop() {
    if (fDRDY) {
        fDRDY = false;
        myAccel.data_get(buffF);
        sprintf(buffSerial, "%f,%f,%f", buffF[0], buffF[1], buffF[2]);
        // myAccel.dataRaw_get(buffi16);
        // sprintf(buffSerial, "%d,%d,%d", buffi16[0], buffi16[1], buffi16[2]);
        Serial.println(buffSerial);
    }
}