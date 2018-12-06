#include <SPI.h>

//Arduino Uno SPI pinout:
//MOSI    11                            --> PIN DIN
//MISO    12 - Not used in this case
//SCK     13                            --> PIN SCLK
//SS      10                            --> PIN SYNC

const int chipSelectPin = 10;

union DataToSend {
  uint32_t integer ;
  byte byteArray[4] ;
};

uint32_t DAC_chan = 0;
uint32_t DAC_value_digital = 0;
float DAC_value_analog =0;

DataToSend DAC_data = {0};

void setup() {
  Serial.begin(500000);
  //Serial.setTimeout(200);
  SPI.begin();
  //Serial.println("Initializing SPI port...");
  //init the Chip Select HIGH so that it will be pulled down when SPI transfer is needed
  digitalWrite(chipSelectPin, HIGH);
  pinMode(chipSelectPin, OUTPUT);
  //Serial.println("System ready");
}

void loop() {
  if (Serial.available()) {
    //read the serial data into String
    String serialBuffer = Serial.readStringUntil('\r');
    //split the string in CHAN and VALUE based on ";" separator
    int separatorIndex = serialBuffer.indexOf(';');
    DAC_chan = serialBuffer.substring(0, separatorIndex).toInt();
    DAC_value_analog = serialBuffer.substring(separatorIndex + 1).toFloat();//this is the analog DAC VALUE
    //print a summary
    /*Serial.print("Chan: ");
    Serial.println(DAC_chan);
    Serial.print("Value: ");
    Serial.println(DAC_value_analog);*/
    //Transform DAC value from analog to digital
    DAC_value_digital = (DAC_value_analog * 16383) / 204.8;
    //Put data in DAC format
    DAC_data.integer = DAC_chan << 27 | DAC_value_digital << 13;
    //Serial.println(DAC_data.integer, BIN);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
    digitalWrite(chipSelectPin, LOW);
    byte provaBuffer[3];
    provaBuffer[0] = DAC_data.byteArray[3];
    provaBuffer[1] = DAC_data.byteArray[2];
    provaBuffer[2] = DAC_data.byteArray[1];
    SPI.transfer(provaBuffer, 3);
    digitalWrite(chipSelectPin, HIGH);
    SPI.endTransaction();
  }
}
