

#define mux_enb_pin  11
#define lvl_trans_en_pin 13
#define a_pin A2
#define b_pin A1
#define c_pin A3
#define batt_stby 9
#define scl A5
#define sda A4



int i = 1;
int value = 0;


void setup() {
  // put your setup code here, to run once:

pinMode(batt_stby, OUTPUT);
pinMode(mux_enb_pin, OUTPUT);
pinMode(lvl_trans_en_pin, OUTPUT);
pinMode(a_pin, INPUT);
pinMode(b_pin, OUTPUT);
pinMode(c_pin, OUTPUT);
pinMode(DAC0, OUTPUT);
pinMode(scl, OUTPUT);
pinMode(sda, OUTPUT);

digitalWrite(lvl_trans_en_pin, HIGH);
digitalWrite(mux_enb_pin, HIGH);


digitalWrite(a_pin, LOW);
digitalWrite(b_pin, LOW);
digitalWrite(c_pin, LOW);
digitalWrite(batt_stby, LOW);
digitalWrite(scl, HIGH);
digitalWrite(sda, HIGH);

analogWriteResolution(10);



}

void loop() {
  // put your main code here, to run repeatedly:

//analogWrite(DAC0, 426);
//delay(40);
//analogWrite(DAC0, 626);
//delay(40);




}
