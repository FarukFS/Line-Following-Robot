#include "mbed.h"
#include "QEI.h"
#include "OneWire_Methods.h"
#include "ds2781.h"
#include "Encoder.h"
#include "BLE.h"
#define CENTRE 0.153
#define KT 0.007
#define GR 18.75
#define WHEEL_RADIUS 0.040

DigitalInOut one_wire_pin(PC_14); //Pin for battery sensors, must be InOut as it transfers and receives data.
Motors* AB = new Motors(PB_1, PB_15, PC_10, PC_12, PC_11); // PWM1, PWM2, Bipolar1, Bipolar2, Enable.
QEI* Enc_A = new QEI(PA_13,PA_14, NC, 256, QEI::X2_ENCODING);
QEI* Enc_B = new QEI(PC_8,PC_5, NC, 256, QEI::X2_ENCODING);
Encoder Encoders(Enc_A, Enc_B);
RawSerial* hm10 = new RawSerial(PA_11, PA_12); //UART6 TX,RX
Sensor *S1= new Sensor(PC_0,PC_4), *S2= new Sensor(PC_1,PB_13), *S3= new Sensor(PB_0,PA_10), *S4= new Sensor(PA_4,PB_3), *S5= new Sensor(PA_1,PB_5), *S6= new Sensor(PA_0,PB_4);


float calcDC (float speed) {
    int VoltageReading; 
    float VBatt;
    VoltageReading = ReadVoltage();
    VBatt = VoltageReading*0.00976;
    return ((KT * (speed/WHEEL_RADIUS) * GR) + VBatt) / (2.0 * VBatt);
}

int main() {
    BLE MyBLE(hm10,AB,S1,S2,S3,S4,S5,S6);
    AB->setFreq(20000);
    AB->setSpeed(0.5,0.5);
    
    while (1) {
    }
    
};