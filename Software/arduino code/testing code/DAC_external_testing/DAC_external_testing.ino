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
#include <Arduino.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h>

/********GLOBAL_VARIABLES*********/
int i = -1;
int dac_value = 0;
int dummy_int = 0;
signed int test_currents[] = {
  45, 10, -10, -45
};    
signed int output_current_setpoint = 0;
Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
LiquidCrystalI2C_RS_EN(lcd, 0x27, false)
int buttonState = 0;
volatile bool execute = false;


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

  analogWriteResolution(10);

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
    dac_value = (200*output_current_setpoint*0.005/74 + 1.65) / (3.3/1024);
  
    Serial.print("DAC value = ");
    Serial.println(dac_value);
    Serial.print("DAC value = ");
    Serial.println(dac_value);

    //dummy_int = dummy_int + 10;
    analogWrite(DAC0, dac_value);

    //analogWrite(DAC0, dac_value);
    lcd.print("DACV = ");
    lcd.print(dac_value*3.3/1024);
    lcd.setCursor(0, 1);
    lcd.print("Iset = ");
    lcd.print(output_current_setpoint);
    lcd.print(" uA");
    execute = false;
  }
  //analogWrite(DAC0, 426);
  //delay(40);
  //analogWrite(DAC0, 626);
  //delay(40);
}
