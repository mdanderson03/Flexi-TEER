#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

#define mux_enb_pin  11
#define lvl_trans_en_pin 13
#define a_pin A2
#define b_pin A1
#define c_pin A3
#define pd_adc_driver_pin A7
#define batt_stby 9



int i = 1;
int value = 0;


void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);

delay(2000);

Serial.println("Hello!");

Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");


pinMode(batt_stby, OUTPUT);
pinMode(mux_enb_pin, OUTPUT);
pinMode(lvl_trans_en_pin, OUTPUT);
pinMode(a_pin, INPUT);
pinMode(b_pin, OUTPUT);
pinMode(c_pin, OUTPUT);
pinMode(pd_adc_driver_pin, OUTPUT);
pinMode(DAC0, OUTPUT);

digitalWrite(lvl_trans_en_pin, HIGH);
digitalWrite(mux_enb_pin, HIGH);


digitalWrite(a_pin, LOW);
digitalWrite(b_pin, LOW);
digitalWrite(c_pin, LOW);
digitalWrite(pd_adc_driver_pin, HIGH);
digitalWrite(batt_stby, LOW);

analogWriteResolution(10);


ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)

if (!ads.begin()) {
  Serial.println("Failed to initialize ADS.");
  while (1);
}

}




void loop() {
  // put your main code here, to run repeatedly:
int16_t results;
float   multiplier = 3.0F; 


analogWrite(DAC0, 426);


//results = ads.readADC_Differential_0_1();

//Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");







//delay(40);
//analogWrite(DAC0, 626);
//delay(40);




}