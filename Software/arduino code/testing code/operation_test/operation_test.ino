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
  Serial.println("ADC Range: +/- 4.096V (1 bit = 2mV/ADS1015, 0.1875mV/ADS1115)");


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

  ads1015.setGain(GAIN_ONE);



  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

}




void loop() {
  // put your main code here, to run repeatedly:
int16_t results;
float resistance;


delay(20);
analogWrite(DAC0, 426);
delay(20);
results = ads.readADC_Differential_0_1();
Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.println("mV)");
results = abs(results);
resistance = 40.9 * results;
Serial.print("Resistance: "); Serial.print(results); Serial.print("("); Serial.println("ohm)");


delay(20);
analogWrite(DAC0, 626);
delay(20);
results = ads.readADC_Differential_0_1();
Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.println("mV)");
results = abs(results);
resistance = 40.9 * results;
Serial.print("Resistance: "); Serial.print(results); Serial.print("("); Serial.println("ohm)");




}
