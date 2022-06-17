#include <AD9833.h>


#define FNC_PIN 7

AD9833 gen(FNC_PIN);

void setup() {
  // put your setup code here, to run once:
  gen.Begin();
  gen.ApplySignal(SQUARE_WAVE, REG0, 500000);
  gen.EnableOutput(true);


}

void loop() {
  // put your main code here, to run repeatedly:

}
