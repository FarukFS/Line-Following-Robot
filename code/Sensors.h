class Sensor {
    protected:
        AnalogIn SensorOutput;
        DigitalOut DarlingtonIn;
        uint16_t value;
        char cval;
    public:
        Sensor(PinName Output, PinName DIn) : SensorOutput(Output), DarlingtonIn(DIn){
            DarlingtonIn = 0; //Set to Bipolar Mode of operation.
        }
        
        void TurnOn(void) {
            DarlingtonIn = 1;
        }  
        
        void TurnOff(void) {
            DarlingtonIn = 0;
        }
        
        void Toggle(void) {
            if (DarlingtonIn == 0) {
                DarlingtonIn = 1;
            }
            else if (DarlingtonIn == 1) {
                DarlingtonIn = 0;
            }
        }
        
        bool Status (void) {
            if (DarlingtonIn == 0) {
                return 0;
                }
            else if (DarlingtonIn == 1) {
                return 1;
                }
        }
        
        char ReturnVal(void) {
            value = SensorOutput.read_u16();
            cval = (char) (value/256.0f);
            /*if (hm10->writeable()){
                hm10->putc(cval);
                } */
            return cval;
            }
            
      /*  void SelectVal(void) {
            if (hm10->readable()){
                select = hm10->getc();
            }
        } */
};