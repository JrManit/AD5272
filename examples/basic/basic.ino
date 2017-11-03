#include <AD5272.h>

#define POT_ADDR 0x2E

// creates communication object with address 0x2E
AD5272 digital_pot(POT_ADDR);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialises the communication via I2C
  // and enables RDAC adjustment through digital interface
  if(digital_pot.init() != 0);
    Serial.println("Cannot send data to the IC.");
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the current RDAC value
  int ret = digital_pot.read_rdac();
  Serial.print("Read RDAC Value: ");
  Serial.println(ret, DEC);

  // set new value to RDAC (0~1024)
  uint16_t data = 512;
  ret = digital_pot.write_data(AD5272_RDAC_WRITE, data);
  if(ret != 0)  // check if data is sent successfully
    Serial.println("Error!");
    
  // copy RDAC value to 50TP memory
  ret = digital_pot.write_data(AD5272_50TP_WRITE, 0);
  if(ret != 0)    // check if data is sent successfully
    Serial.println("Error!");
  
  // read the new RDAC value
  ret = digital_pot.read_rdac();
  Serial.print("New RDAC Value: ");
  Serial.println(ret, DEC);
}
