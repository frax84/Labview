#include <SPI.h>

//Arduino Uno SPI pinout:
//MOSI    11                            --> PIN DIN
//MISO    12 - Not used in this case
//SCK     13                            --> PIN SCLK
//SS      10                            --> PIN SYNC


/// HOW THIS WORKS //
/* Labview send commands (defined by "labviewCommand" data type) and data. Data are the frequency (recorded in "periodDelay" data type) and amplitude of 31 channel square waves (31CHSW) (channel 0 is used as bias to allow biphasic square wave).
   Program works cycling the simple sequence: load High values of 31CHSW, wait half period, load Low values of 31CHSW, wait half period.
   To increase speed of the algorithm Hi and Low values of 31CHSW are pre-calculated using the functions "formatSquareWave()" and "swapWaveBytes()" and then transferred already formatted using the function "LoadAllToDAC()"

*/


#define DEBUG 1   //DEBUG 1 is enabled

//CONSTANT DEFINITION

const double VDD = 204.8;
const int chipSelectPin = 10;


//DATATYPES DEFINITION

typedef union  {
  uint32_t integer ;
  byte byteArray[4] ;
} uint32toBytes;

typedef union  {
  uint16_t integer;
  byte byteArray[2];
} uint16toBytes;

typedef union  {
  uint16_t integer[31];
  byte byteArray[62];
} payloadArray;

typedef struct {
  uint32_t highVal;
  uint32_t lowVal;
} squareWaveData;

typedef enum {
  M_ERROR = 255,
  NONE = 0,
  START,
  STOP,
  LOAD_ARRAY,
  UPDATE_CHANNEL,
  UPDATE_FREQUENCY,
} labviewCommand;


//VARIABLES DECLARATION

uint16toBytes payloadLenght = {0}; //stores the lenght in Bytes of the data payload
uint16toBytes periodDelay;    //stores the period in us of the squarewave
payloadArray payloadarray;    //stores the amplitude of the 31 channels in digital value
squareWaveData waveData[32] = {0};   //stores the high and low values of channel 1-31 and the bias reference of channel 0

boolean go = false;
uint32_t digital_half_vdd = 0;
byte waveDataHi[96];    //stores the values of the HI values of the square wave in digital form properly inverted and ready to be send
byte waveDataLo[96];   //stores the values of the LO values of the square wave in digital form properly inverted and ready to be send

void setup() {
  Serial.begin(500000);
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);   //init the Chip Select as OUTPUT...
  digitalWrite(chipSelectPin, HIGH);    //...and put it HIGH so that it will be pulled down when SPI transfer is needed
  digital_half_vdd = uint32_t (VDD / (2.*0.0125));    //calculate only once the digital value of half of VDD
  while (!Serial) {
    //wait for Serial port to connect
  }
}

void loop() {
  if (Serial.available()) {
    labviewCommand command = labviewCommand(Serial.read());   //the 1st byte is the command
    Serial.print("Cmd ricevuto: ");
    Serial.println(command);
    Serial.readBytes(payloadLenght.byteArray, 2);   //next 2 bytes are the Payload lenght
    switch (command) {
      case START:   //this is used to start to produce the square wave
        Serial.println("Cmd: START");
        break;
      case STOP:    //this is used to stop producing the square wave
        Serial.println("Cmd: STOP");
        break;
      case LOAD_ARRAY:    //this is used to load the amplitude of the 31 channel available. Channel 0 is the reference
        Serial.println("Cmd: LOAD ARRAY");
        break;
      case UPDATE_CHANNEL:    //this is used to update the amplitude of a single channel during runtime
        Serial.println("Cmd: UPDATE CHANNEL");
        break;
      case UPDATE_FREQUENCY:    //this is used to update the frequency of the produced square wave during runtime
        Serial.println("Cmd: UPDATE FREQUENCY");
        break;
      default:
      Serial.println("No command detected");
        break;
    }
  }
  if (go) {
    /*loadAllToDAC(waveDataHi);
      delayMicroseconds(periodDelay.integer / 2);
      loadAllToDAC(waveDataLo);
      delayMicroseconds(periodDelay.integer / 2);*/
    Serial.println("GO ATTIVO");
    delay(1000);
  } else {
    //LOAD ALL TO ZERO
  }
}

void formatChannelData(uint8_t chan, uint16toBytes chanData) {    //TO DEBUG
  waveData[chan].highVal = digital_half_vdd + uint32_t(chanData.integer);
  waveData[chan].lowVal = digital_half_vdd - uint32_t(chanData.integer);
  waveData[chan].highVal = (uint32_t(chan) << 27) | (waveData[chan].highVal << 13);    //build the data as required by AD5535
  waveData[chan].lowVal =  (uint32_t(chan) << 27) | (waveData[chan].lowVal << 13);
  swapChannelBytes(chan);
}

void formatWaveData() {
  waveData[0].highVal = digital_half_vdd << 13;  //Channel 0 is the offset reference = Vdd/2
  waveData[0].lowVal =  digital_half_vdd << 13;  //build the data as required by AD5535
  for (uint32_t i = 1; i < 32; i++) {
    waveData[i].highVal =  digital_half_vdd + uint32_t(payloadarray.integer[i - 1]); //The real values to send will be VDD/2 + VALUE...
    waveData[i].lowVal = digital_half_vdd - uint32_t(payloadarray.integer[i - 1]); // ...and VDD/2 - VALUE
    waveData[i].highVal = (i << 27) | (waveData[i].highVal << 13); //build the data as required by AD5535    NOTE:[i+1] because channel 0 is used for ref
    waveData[i].lowVal =  (i << 27) | (waveData[i].lowVal << 13);
  }
  swapWaveBytes();
}

void swapChannelBytes(uint8_t chan) {
  uint32toBytes dacData;
  dacData.integer = waveData[chan].highVal;
  waveDataHi[chan] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
  waveDataHi[chan + 1] = dacData.byteArray[2];
  waveDataHi[chan + 2] = dacData.byteArray[1];
  dacData.integer = waveData[chan].lowVal;    //load the value inside an uint32_t
  waveDataLo[chan] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
  waveDataLo[chan + 1] = dacData.byteArray[2];
  waveDataLo[chan + 2] = dacData.byteArray[1];
}


void swapWaveBytes() { //TO DEBUG
  uint32toBytes dacData;
  for (int i = 0; i < 32; i++) {
    dacData.integer = waveData[i].highVal;    //load the value inside an uint32_t
    waveDataHi[i] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
    waveDataHi[i + 1] = dacData.byteArray[2];
    waveDataHi[i + 2] = dacData.byteArray[1];
    dacData.integer = waveData[i].lowVal;    //load the value inside an uint32_t
    waveDataLo[i] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
    waveDataLo[i + 1] = dacData.byteArray[2];
    waveDataLo[i + 2] = dacData.byteArray[1];
  }
}

void loadSingleToDAC(byte waveChannelData[]) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));  //open the SPI channel
  digitalWrite(chipSelectPin, LOW);
  for (int i = 0; i < 3; i++)
    SPI.transfer(waveChannelData[i]);
  digitalWrite(chipSelectPin, HIGH);
  SPI.endTransaction();
}


void loadAllToDAC(byte waveArrayData[]) {  //TO DEBUG
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));  //open the SPI channel
  for (int i = 0; i < 32; i++) {
    digitalWrite(chipSelectPin, LOW);
    for (int j = 0; j < 3; j++)
      SPI.transfer(waveArrayData[3 * i + j]);
    digitalWrite(chipSelectPin, HIGH);
  }
  SPI.endTransaction();
}
