#include "Sensors.h"
#include "Motors.h"
Serial pc(USBTX, USBRX);

class BLE {
    protected:
        RawSerial* hm10;
        Motors* AB;
        Sensor *S1,*S2,*S3,*S4,*S5,*S6;
        char sel;
    public:
        BLE(RawSerial* HM, Motors* MT, Sensor* Sen1, Sensor* Sen2, Sensor* Sen3, Sensor* Sen4, Sensor* Sen5, Sensor* Sen6) : hm10(HM), AB(MT), S1(Sen1),S2(Sen2),S3(Sen3),S4(Sen4),S5(Sen5),S6(Sen6){
            hm10->baud(9600);
            hm10->attach(callback(this,&BLE::Selection), Serial::RxIrq);
        }
        void ReadChar (void) {
            if (hm10->readable()){
                sel = hm10->getc();
            }
        }
        void Selection(void) {
            ReadChar();
            pc.printf("%c \n", sel);
            switch (sel) {
            case 'A':
                S1->Toggle();
                break;
            case 'B':
                S2->Toggle();
                break;
            case 'C':
                S3->Toggle();
                break;
            case 'D':
                S4->Toggle();
                break;
            case 'E':
                S5->Toggle();
                break;
            case 'F':
                S6->Toggle();
                break;
            }
        }
    
};