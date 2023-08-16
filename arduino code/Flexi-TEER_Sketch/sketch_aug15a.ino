

# define mux_enb_pin  11
#define lvl_trans_en_pin 13
#define a_pin A2
#define b_pin A1
#define c_pin A3
#define batt_stby 9






void setup() {
  // put your setup code here, to run once:

pinMode(batt_stby, OUTPUT);
pinMode(mux_enb_pin, OUTPUT);
pinMode(lvl_trans_en_pin, OUTPUT);
pinMode(a_pin, OUTPUT);
pinMode(b_pin, OUTPUT);
pinMode(c_pin, OUTPUT);
pinMode(DAC0, OUTPUT);

digitalWrite(lvl_trans_en_pin, HIGH);
//digitalWrite(mux_enb_pin), HIGH);


digitalWrite(a_pin, HIGH);
digitalWrite(b_pin, HIGH);
digitalWrite(c_pin, HIGH);
digitalWrite(batt_stby, LOW);

analogWrite(DAC0, 384);



int level = 500;
analogReference(500);




}

void loop() {
  // put your main code here, to run repeatedly:





//analogWrite(DAC0, 384);
//delay(1000);



}
