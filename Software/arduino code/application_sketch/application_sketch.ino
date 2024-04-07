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
signed int output_current_setpoint = 100;
int current_iterator = -1;
signed int test_currents[] = {
  -100, -50, -10, 10, 50, 100
};  

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
  //pinMode(DAC0, OUTPUT);
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button_enter, INPUT);
  pinMode(button_esc, INPUT);
  pinMode(button_up, INPUT);
  pinMode(button_right, INPUT);
  pinMode(button_left, INPUT);
  pinMode(button_down, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_enter), onDetectInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_esc), onDetectInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_up), onDetectInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_right), onDetectInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_left), onDetectInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_down), onDetectInterrupt, FALLING);

  digitalWrite(lvl_trans_en_pin, HIGH);
  digitalWrite(mux_enb_pin, HIGH);
  digitalWrite(neg_5v_en, HIGH);

  digitalWrite(pd_adc_driver_pin, LOW); // reworked to be the MUX control d
  digitalWrite(a_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);

  /********ADC_CONFIG*********/
 //                                                                ADS1015  ADS1115
 //                                                                -------  -------
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  multiplier = 3.00F; 
  
    Serial.println("Hello!");
  if (!ads.begin()) {
    Serial.println("ADC init .... fail.");
    init_success = false;
  }
  else{
    Serial.println("ADC init .... success.");
    init_success = true;
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

void channel_selector(){
  Serial.print("channel selector");
  channel_iterator = channel_iterator+1;
   Serial.print(channel_iterator & 0B0001);
   Serial.print(channel_iterator & 0B0010);
   Serial.print(channel_iterator & 0B0100);
   Serial.println(channel_iterator & 0B1000);
  /*
  digitalWrite(pd_adc_driver_pin, LOW); // reworked to be the MUX control d
  digitalWrite(a_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);
  */
}

void onDetectInterrupt(){
  delay(30);
  if (digitalRead(button_enter) == LOW){
    measure = false;
    current_increase = true;
  }
  else
  {
    if (digitalRead(button_esc) == LOW){
      measure = false;
      current_decrease = true;
      channel_selector();
    }
    else
    {
      if (digitalRead(button_up) == LOW)
      {
        measure = true;
        current_increase = false;
        current_decrease = false;
        channel_selector();
      }
      else
      {
        if (digitalRead(button_right) == LOW)        {
        measure = true;
        current_increase = false;
        current_decrease = false;
        channel_selector();
        }
        else{
        measure = true;
        current_increase = false;
        current_decrease = false;
        }
      }
    }
  }
  /*
  if (digitalRead(button_esc)==HIGH && digitalRead(button_enter ==HIGH)){
    measure = true;
    current_increase = false;
    current_decrease = false;
  }
  
  */
}

/********MAIN_LOOP*********/
void loop() {
  int buttonState = digitalRead(button_enter);
  if(buttonState == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  if(measure == true && init_success == true){
    int adc_value_bits = -ads.readADC_Differential_0_1();
    float adc_value_volts = 100*adc_value_bits*multiplier/5;
    adc_value_volts = adc_value_volts*0.01;
    //Serial.print(adc_value_bits);
    //Serial.print("bits ");
    //Serial.print(adc_value_bits*multiplier);
    //Serial.print("mV ");
    //Serial.print(adc_value_volts);
    //Serial.println("mV");
    float resistance = 1000*adc_value_volts/output_current_setpoint;
    //Serial.print("R=");
    //Serial.print(resistance);
    //Serial.println(" Ohm    ");


    lcd.setCursor(0, 1);
    lcd.print("R="); 
    lcd.print(resistance);
    lcd.print(" Ohm    "); 

    delay(200);
  }
  
  if(channel_change == true){

  }

  if(current_increase == true || current_decrease == true){
    // sizeof(test_currents)/sizeof(test_currents[0]) is used to get an array size use https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/ for reference
    if (current_increase){
      if(current_iterator < sizeof(test_currents)/sizeof(test_currents[0])-1){
        current_iterator = current_iterator + 1;
      }
      else{
        current_iterator = 0;
      }
    }

    if(current_decrease){
     if(current_iterator > 0){
        current_iterator = current_iterator - 1;
      }
      else{
       current_iterator = (sizeof(test_currents)/sizeof(test_currents[0])-1);
      }
    }
  
    

    if (current_iterator<0){
      lcd.clear();
      lcd.print("Something went wrong");
    }

    output_current_setpoint = test_currents[current_iterator];
    signed int dac_value_bits = (200*output_current_setpoint*0.005/75 + 2.5)*4095 / 5;
    float dac_value_volts = 100*dac_value_bits*5/4095;
    dac_value_volts = dac_value_volts*0.01;
    dac.setVoltage(dac_value_bits, false);

    Serial.print("output_current_setpoint = ");
    Serial.println(output_current_setpoint);
    Serial.print("actual output_current_setpoint = ");
    Serial.println(75*(dac_value_volts - 2.5)/200/5000);
    Serial.print("DAC value bits = ");
    Serial.println(dac_value_bits);
    Serial.print("DAC value volts = ");
    Serial.println(dac_value_volts);

    lcd.clear();
    lcd.print("Vd=");
    lcd.print(dac_value_volts);
    lcd.print(" I=");
    lcd.print(output_current_setpoint);
    lcd.print("uA"); 

    current_increase = false;
    current_decrease = false;
    measure = true;
  }
}
