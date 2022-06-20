#include <MD_AD9833.h>
#include <SPI.h>


// Pins for SPI comm with the AD9833 IC
#define DATA  11  ///< SPI Data pin number
#define CLK   13  ///< SPI Clock pin number
#define FSYNC 10  ///< SPI Load pin number (FSYNC in AD9833 usage)

MD_AD9833  AD(FSYNC);  // Hardware SPI
// MD_AD9833  AD(DATA, CLK, FSYNC); // Arbitrary SPI pins

void setup() {
  // put your setup code here, to run once:

AD.begin();
AD.setMode(MD_AD9833::MODE_SQUARE1);
AD.setFrequency(MD_AD9833::CHAN_0, 5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
