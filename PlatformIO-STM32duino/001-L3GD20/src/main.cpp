#include <Arduino.h>
#include "LibL3GD20.hpp"

volatile bool fDRDY = true;
void irqDataReady() {
    fDRDY = true;
}

L3GD20 myGyro(irqDataReady);

void setup() {
    Serial.begin(); // Serial to USB CDC, ustawienia w platformio.ini

    uint8_t ret = myGyro.whoAmI();
    if (ret == myGyro.id) {
        myGyro.resetSoft();
        myGyro.fullScaleSelect_set(myGyro.FullScaleSelect_2000_dps);
        myGyro.hpfFreq_set(myGyro.HpfFreq_odr760_0_1);
        //myGyro.hpfReference_set(0x00);
        //myGyro.hpfMode_set(myGyro.HpfMode_reference);    
        myGyro.outFilterSelect(myGyro.OutFilterSelect_hfON_lf2ON);
        myGyro.on(myGyro.OnOdr_760Hz_lf1_93_lf2_110);
    }
    else {
        while (1) { // errorc ID
            delay(1);
        }
    }
}

float buffF[3];
char buffSerial[256];

void loop() {
    if (fDRDY) {
        fDRDY = false;
        myGyro.data_get(buffF);
        sprintf(buffSerial, "%f,%f,%f", buffF[0], buffF[1], buffF[2]);
        Serial.println(buffSerial);
    }
}
