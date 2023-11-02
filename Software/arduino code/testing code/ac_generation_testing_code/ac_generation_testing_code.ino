/********PINOUT_DEFINITION*********/
// D0 debug UART RX not used
// D1 debug UART TX not used
#define button_esc 2
#define button_enter 3
#define button_up 4
#define button_right 5
#define button_down 6
#define button_left 7
#define adc_rdy 9
#define batt_stby 9  //charging is done indicator form charger IC
#define batt_chrg 10 //charging is in progress indicator form charger IC
#define mux_enb_pin  11
#define neg_5v_en  12
#define lvl_trans_en_pin 13
// A0 - DAC0
#define b_pin A1
#define a_pin A2
#define c_pin A3
// d_pin connected to AREF
#define sda A4
#define scl A5
#define batt_voltage A6
#define pd_adc_driver_pin A7

/********LIBRARIES*********/

#include <Adafruit_ADS1X15.h>
#include <Adafruit_MCP4725.h>
#include <Arduino.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h>

/********GLOBAL_VARIABLES*********/
int execute = 0;
int buttonState = 0;
int i = -1;
signed int dac_value_bits = 0;
int adc_value_bits = 0;
float dac_value_volts = 0;
float adc_value_volts = 0;
float resistance = 0;
signed int output_current_setpoint = 100;
signed int test_currents[] = {
  100, 50, 10, -10, -50, -100
};  
float   multiplier = 3.00F; 


Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
Adafruit_MCP4725 dac;
LiquidCrystalI2C_RS_EN(lcd, 0x27, false)


/********INITIAL_CONFIG*********/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  Serial.println("Hello!");

  pinMode(mux_enb_pin, OUTPUT);
  pinMode(lvl_trans_en_pin, OUTPUT);
  pinMode(a_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(c_pin, OUTPUT);
  pinMode(DAC0, OUTPUT);
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button_enter, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_enter), onDetectInterrupt, FALLING);

  digitalWrite(lvl_trans_en_pin, HIGH);
  digitalWrite(mux_enb_pin, HIGH);
  digitalWrite(neg_5v_en, HIGH);

  digitalWrite(pd_adc_driver_pin, LOW); // reworked to be the MUX control d
  digitalWrite(a_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);
 //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
  //#define DAC_RESOLUTION    (10)
  //analogReference(AR_EXTERNAL);
  //analogWrite(DAC0, 426);
  dac.begin(0x60);

  if (!ads.begin()) {
    Serial.println("ADC init .... fail.");
  }
  else{
    Serial.println("ADC init .... success.");
  }

  Wire.begin();
  Serial.println("LCD init.");
  lcd.begin(16, 2);
  lcd.configureBacklightPin(3);
  lcd.backlight();
  lcd.print("click Enter");
  lcd.setCursor(0, 1);
  lcd.print("to start");
}

void onDetectInterrupt()
{
  delay(30);
  if (digitalRead(button_enter) == LOW){
    execute = 2;
  }
  else{
    execute = 1;
  }
  
}

/********MAIN_LOOP*********/
void loop() {
  buttonState = digitalRead(button_enter);
  // put your main code here, to run repeatedly:
  if(buttonState == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  if(execute == 1){
    adc_value_bits = -ads.readADC_Differential_0_1();
    adc_value_volts = 100*adc_value_bits*multiplier/5;
    adc_value_volts = adc_value_volts*0.01;
    Serial.print(adc_value_bits);
    Serial.print("bits ");
    Serial.print(adc_value_bits*multiplier);
    Serial.print("mV ");
    Serial.print(adc_value_volts);
    Serial.println("mV");
    resistance = 1000*adc_value_volts/output_current_setpoint;
    Serial.print("R=");
    Serial.print(resistance);
    Serial.println(" Ohm    ");


    lcd.setCursor(0, 1);
    lcd.print("R="); 
    lcd.print(resistance);
    lcd.print(" Ohm    "); 

    delay(200);
  }
  

  if(execute == 2){
    lcd.clear();
    // sizeof(test_currents)/sizeof(test_currents[0]) is used to get an array size use https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/ for reference
    if(i < (sizeof(test_currents)/sizeof(test_currents[0])-1)){
      i = i + 1;
    }
    else{
      i = 0;
    }

    output_current_setpoint = test_currents[i];
    dac_value_bits = (200*output_current_setpoint*0.005/75 + 2.5)*4095 / 5;
    dac_value_volts = 100*dac_value_bits*5/4095;
    dac_value_volts = dac_value_volts*0.01;

    Serial.print("output_current_setpoint = ");
    Serial.println(output_current_setpoint);
    Serial.print("actual output_current_setpoint = ");
    Serial.println(75*(dac_value_volts - 2.5)/200/5000);
    Serial.print("DAC value bits = ");
    Serial.println(dac_value_bits);
    Serial.print("DAC value volts = ");
    Serial.println(dac_value_volts);

    dac.setVoltage(dac_value_bits, false);

    lcd.print("Vd=");
    lcd.print(dac_value_volts);
    lcd.print(" I=");
    lcd.print(output_current_setpoint);
    lcd.print("uA"); 
    execute = 1;
  }
}
