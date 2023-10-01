

#define mux_enb_pin  11
#define lvl_trans_en_pin 13
#define a_pin A2
#define b_pin A1
#define c_pin A3
#define batt_stby 9



int i = 1;
int value = 0;


void setup() {
  // put your setup code here, to run once:

pinMode(batt_stby, INPUT);
pinMode(mux_enb_pin, OUTPUT);
pinMode(lvl_trans_en_pin, OUTPUT);
pinMode(a_pin, INPUT);
pinMode(b_pin, OUTPUT);
pinMode(c_pin, OUTPUT);
pinMode(DAC0, OUTPUT);

digitalWrite(lvl_trans_en_pin, HIGH);
digitalWrite(mux_enb_pin, HIGH);


//digitalWrite(a_pin, LOW);
digitalWrite(b_pin, LOW);
digitalWrite(c_pin, LOW);
//digitalWrite(batt_stby, LOW);

analogWriteResolution(10);

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:



analogWrite(DAC0, i);
delay(400);
value = analogRead(a_pin);
Serial.print(value);
Serial.print("_");
Serial.print(i);
Serial.println(' ');
delay(2000);

i = i + 50;

if(i>1000){
  i = 1;
}




}
