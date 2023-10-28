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
volatile bool execute = false;
int buttonState = 0;
int i = -1;
uint32_t dac_value_bits = 0;
uint32_t adc_value_bits = 0;
float dac_value_volts = 0;
int adc_value_volts = 0;
float resistance = 0;
signed int output_current_setpoint = 100;
signed int test_currents[] = {
  100, 50, 10, -10, -50, -100
};  


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
  digitalWrite(pd_adc_driver_pin, HIGH);
  digitalWrite(neg_5v_en, HIGH);


  digitalWrite(a_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);

  //#define DAC_RESOLUTION    (10)
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
  delay(10);
  if (digitalRead(button_enter) == HIGH){
    execute = true;
  }
  else{
    execute = false;
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
  adc_value_bits = abs(ads.readADC_Differential_0_1());
  adc_value_volts = adc_value_bits*3;
  Serial.print(adc_value_volts);
  Serial.println("mV");
  resistance = adc_value_volts/(5*output_current_setpoint);
  Serial.print(resistance);
  Serial.println("kOhm");
  delay(200);

  if(execute){
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
    dac_value_volts = dac_value_bits*5/4095;

    Serial.print("output_current_setpoint = ");
    Serial.println(output_current_setpoint);
    Serial.print("actual output_current_setpoint = ");
    Serial.println(75*(dac_value_volts - 2.5)/200/5000);
    Serial.print("DAC value bits = ");
    Serial.println(dac_value_bits);
    Serial.print("DAC value volts = ");
    Serial.println(dac_value_volts);

    dac.setVoltage(dac_value_bits, false);

    lcd.print("DACV = ");
    lcd.print(dac_value_volts);
    lcd.setCursor(0, 1);
    lcd.print("Iset = ");
    lcd.print(output_current_setpoint);
    lcd.print(" uA");
    execute = false;
  }
}
