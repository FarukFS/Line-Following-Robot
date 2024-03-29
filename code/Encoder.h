#include "C12832.h"
#define WHEEL_RADIUS 0.040
#define PI 3.14159265358979323846

C12832 lcd(D11,D13,D12,D7,D10); //LCD display. PA_7 PA_5 PA_6 PA_8 PB_6


class Encoder {
    protected:
        QEI* Encoder_R;
        QEI* Encoder_L;
        unsigned long count_R, count_L, oldR, oldL, pulses_R, pulses_L;     
        Timer t_R, t_L;  
        float dt_R, dt_L, speed_R, speed_L, trans_Speed, rot_Speed;
    public:
        Encoder(QEI* A, QEI* B): Encoder_R(A), Encoder_L(B){
            Encoder_L->reset();
            Encoder_R->reset();
            count_R = 0;
            count_L = 0;
    }
        float GetSpeedR(void) {
            oldR = count_R;
            count_R = abs (Encoder_R->getPulses());
            dt_R = t_R.read_us();
            if (Encoder_R->getPulses() < 0 ) {
                speed_R = -1 * (((count_R - oldR) / 512.0) / (dt_R/1000000.0))*(2.0*PI*WHEEL_RADIUS);
            }
            else if (Encoder_R->getPulses() > 0 ) {
                speed_R = (((count_R - oldR) / 512.0) / (dt_R/1000000.0))*(2.0*PI*WHEEL_RADIUS);
            }
            t_R.reset();
            t_R.start();
            return speed_R;
        }
        float GetSpeedL(void) {
            oldL = count_L;
            count_L = abs (Encoder_L->getPulses());
            dt_L = t_L.read_us();
            if (Encoder_L->getPulses() < 0 ) {
                speed_L = -1 * (((count_L - oldL) / 512.0) / (dt_L/1000000.0))*(2.0*PI*WHEEL_RADIUS);
            }
            else if (Encoder_L->getPulses() > 0 ) {
                speed_L = (((count_L - oldL) / 512.0) / (dt_L/1000000.0))*(2.0*PI*WHEEL_RADIUS);
            }
            t_L.reset();
            t_L.start();
            return speed_L;
            }
        float GetTransVelocity(void) {
            trans_Speed = (GetSpeedR()+ GetSpeedL())/2.0;
            lcd.locate(0,3);
            lcd.printf("Translational: %f", trans_Speed);
            return trans_Speed;
        }
        float GetAngularVelocity(void) {
            rot_Speed = (trans_Speed)/WHEEL_RADIUS;
            lcd.locate(0,14);
            lcd.printf("Rotational: %f", rot_Speed);
            return rot_Speed;
        }
        long GetPulsesL (void) {
            return (Encoder_L->getPulses());
        }
         long GetPulsesR (void) {
            return (Encoder_R->getPulses());
        }
        void Reset (void) {
            Encoder_R->reset();
            Encoder_L->reset();
        }
};