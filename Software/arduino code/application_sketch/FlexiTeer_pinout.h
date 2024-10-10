/********PINOUT_DEFINITION*********/
// D0 debug UART RX not used
// D1 debug UART TX not used
#define button_esc 2
#define button_enter 3
#define button_up 4
#define button_right 5
#define button_down 6
#define button_left 7
#define adc_rdy 8
#define periph_en 9
#define batt_stby A0  //charging is done indicator form charger IC
#define batt_chrg 10 //charging is in progress indicator form charger IC
#define mux_enb_pin  A2
#define neg_5v_en  12
#define lvl_trans_en_pin 13
// A0 - DAC0
#define b_pin A3
#define a_pin A6
#define c_pin A1
#define d_pin 11
#define sda A4
#define scl A5
#define batt_voltage A7
// #define pd_adc_driver_pin not used anymore. Left floating.