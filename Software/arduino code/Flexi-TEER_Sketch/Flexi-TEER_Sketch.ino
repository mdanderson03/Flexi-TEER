/********LIBRARIES*********/

#include "FlexiTeer_pinout.h"
#include <Adafruit_ADS1X15.h>
#include <Adafruit_MCP4725.h>
#include <Arduino.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h>

/********GLOBAL_VARIABLES*********/
bool measure = false;
bool current_increase = false;
bool current_decrease = false;
bool channel_change = false;
bool init_success = false;
float multiplier = 0; //value to multiplier is assigned during ADC init in setup function
byte channel_iterator = B00000;
signed int output_current_setpoint = 20;
float lcd_refresh_time = 2000; //time in ms between data updates for LCD screen
float freq = 12.5; //set frequency in hertz for AC square wave
float switch_time = 1/(freq*2) * 1000; //time between AC flips in ms
unsigned long previousMillis = 0;
unsigned long previousLCDMillis = 0;


signed int pos_dac_value_bits = (output_current_setpoint + 185.64)/0.0907;
float pos_real_current = pos_dac_value_bits * 0.0907 - 185.64; //converts to real current generated
signed int neg_dac_value_bits = (-output_current_setpoint + 185.64)/0.0907;
float neg_real_current = neg_dac_value_bits * 0.0907 - 185.64; //converts to real current generated

int pos_neg_state = 1; //0=negative state, 1=positive state
float resistance = 0;
int resistance_average_count = 0;

Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
Adafruit_MCP4725 dac;
LiquidCrystalI2C_RS_EN(lcd, 0x27, false)



void setup() {
  Serial.begin(115200);
  /********GPIO_CONFIG*********/
  pinMode(mux_enb_pin, OUTPUT);
  pinMode(lvl_trans_en_pin, OUTPUT);
  pinMode(a_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(c_pin, OUTPUT);
  pinMode(d_pin, OUTPUT);
  //pinMode(neg_5v_en, OUTPUT);
  //pinMode(DAC0, OUTPUT);
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(periph_en, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button_enter, INPUT);
  pinMode(button_esc, INPUT);
  pinMode(button_up, INPUT);
  pinMode(button_right, INPUT);
  pinMode(button_left, INPUT);
  pinMode(button_down, INPUT);

  digitalWrite(lvl_trans_en_pin, HIGH);
  digitalWrite(mux_enb_pin, HIGH);
  //digitalWrite(neg_5v_en, HIGH);
  digitalWrite(periph_en, HIGH);

  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);
  digitalWrite(d_pin, LOW);

  /********ADC_CONFIG*********/
 //                                                                ADS1015  ADS1115
 //                                                                 -------  -------
  //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  multiplier = 3.00F; 

  if (!ads.begin()) {
    Serial.println("ADC init .... fail.");
    init_success = false;
  }


  /********BUILT_IN_DAC_CONFIG*********/
  //#define DAC_RESOLUTION    (10)
  //analogReference(AR_EXTERNAL);
  //analogWrite(DAC0, 426);

  /********EXTERNAL_DAC_CONFIG*********/
  dac.begin(0x60);

  /********LCD_CONFIG*********/
  Wire.begin();
  Serial.println("LCD init.");
  lcd.begin(16, 2);
  lcd.configureBacklightPin(3);
  lcd.backlight();
  lcd.print("click Enter");
  lcd.setCursor(0, 1);
  lcd.print("to start");


}


/********MAIN_LOOP*********/
void loop() {

  delay(1);
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= switch_time){
    if (pos_neg_state == 1){
      //record new previous time
      previousMillis = currentMillis;

      //make positive current
      dac.setVoltage(pos_dac_value_bits, false);
      //wait for capacitance to saturate
      delay(switch_time/2);

      // make pos voltage measurement
      int adc_value_bits = ads.readADC_Differential_0_1();
      float adc_value_volts = 100*(adc_value_bits + 1)*multiplier/5;
      adc_value_volts = adc_value_volts*0.01;
      float resistance_measurement = 1000*adc_value_volts/pos_real_current;
      resistance = ((resistance * resistance_average_count) + resistance_measurement)/(resistance_average_count + 1);
      //add 1 to average count
      resistance_average_count += 1;



      //flip state 
      pos_neg_state = 0;
    }

    else {
      //record new previous time
      previousMillis = currentMillis;

      //make positive current
      dac.setVoltage(neg_dac_value_bits, false);
      //wait for capacitance to saturate
      delay(switch_time/2);

      // make pos voltage measurement
      int adc_value_bits = ads.readADC_Differential_0_1();
      float adc_value_volts = 100*(adc_value_bits + 1)*multiplier/5;
      adc_value_volts = adc_value_volts*0.01;
      float resistance_measurement = 1000*adc_value_volts/neg_real_current;
      resistance = ((resistance * resistance_average_count) + resistance_measurement)/(resistance_average_count + 1);
      //add 1 to average count
      resistance_average_count += 1;

      //flip state 
      pos_neg_state = 1;
    }
}


if (currentMillis - previousLCDMillis >= lcd_refresh_time){
  //update LCD previous time
  previousLCDMillis = currentMillis;

  // update LCD with new resistance info
  lcd.setCursor(0, 1);
  lcd.print("R="); 
  lcd.print(resistance);
  lcd.print(" Ohm    "); 

  lcd.setCursor(0, 0);
  lcd.print("I="); 
  lcd.print(pos_real_current);
  lcd.print(" uA"); 

}
  

  
}
