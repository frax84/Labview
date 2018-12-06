#include <SPI.h>

//Arduino Uno SPI pinout:
//MOSI    11                            --> PIN DIN
//MISO    12 - Not used in this case
//SCK     13                            --> PIN SCLK
//SS      10                            --> PIN SYNC


/// HOW THIS WORKS //
/* Labview send commands (defined by "labviewCommand" data type) and data.
   Data are:
   - frequency (recorded in "periodDelay" variable)
   - amplitude of 31 channel square waves (31CHSW)
   - BIAS: channel 0 is used as bias to allow biphasic square wave
   Program works cycling the simple sequence: load High values of 31CHSW, wait half period, load Low values of 31CHSW, wait half period.
   To increase speed of the algorithm Hi and Low values of 31CHSW are pre-calculated using the functions "formatSquareWave()" and "swapWaveBytes()" and then transferred already formatted using the function "LoadAllToDAC()"

*/


#define DEBUG 1   //DEBUG 1 is enabled

//CONSTANT DEFINITION

const double VDD = 204.8;
const int SPI_FREQ = 1000000;
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

boolean go = false;   //enable or disable the square wave output
boolean toReset = false;  //when the output is disabled (go=false)allow to reset the output to 0
uint32_t digital_half_vdd = 0;
byte waveDataHi[96];    //stores the values of the HI values of the square wave in digital form properly inverted and ready to be send
byte waveDataLo[96];   //stores the values of the LO values of the square wave in digital form properly inverted and ready to be send
byte waveDataZero[96];    //stores the zero array to reset the output of DAC when squarewave is disabled

void setup() {
  Serial.begin(500000);
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);   //init the Chip Select as OUTPUT...
  digitalWrite(chipSelectPin, HIGH);    //...and put it HIGH so that it will be pulled down when SPI transfer is needed
  digital_half_vdd = uint32_t (VDD / (2.*0.0125));    //calculate only once the digital value of half of VDD
  formatZeroData(); //prepare an array with 0 data on every channel. Needed to reset the DAC output when the squarewave output is disabled
  while (!Serial) {
    //wait for Serial port to connect
  }
}

void loop() {
  if (Serial.available()) {
    labviewCommand command = labviewCommand(Serial.read());   //the 1st byte is the command
    Serial.readBytes(payloadLenght.byteArray, 2);   //next 2 bytes are the Payload lenght
    switch (command) {
      case START:   //this is used to start to produce the square wave
        go = true;
#if DEBUG
        Serial.println("Cmd: START");
#endif
        break;
      case STOP:    //this is used to stop producing the square wave
        go = false;
        toReset = true;
#if DEBUG
        Serial.println("Cmd: STOP");
#endif
        break;
      case LOAD_ARRAY:    //this is used to load the amplitude of the 31 channel available. Channel 0 is the reference
        Serial.readBytes(periodDelay.byteArray, 2);   //save the period of the square wave in us
        Serial.readBytes(payloadarray.byteArray, 62); //save the digital value of the channels amplitude
        formatWaveData();
#if DEBUG
        Serial.println("Cmd: LOAD ARRAY");
        Serial.print("Period delay: ");
        Serial.println(periodDelay.integer);
        for (int i = 1; i < 32; i++) {
          Serial.print("Ch ");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(payloadarray.integer[i - 1]); //need to map Ch1-31 from Payload Array 0-30
        }
        Serial.println("FUNCTION: FORMATWAVEDATA");
        for (int i = 0; i < 32; i++) {
          Serial.print("Ch ");
          Serial.print(i);
          Serial.print(" Hi: ");
          Serial.println(waveData[i].highVal);
          Serial.print("Ch ");
          Serial.print(i);
          Serial.print(" Lo: ");
          Serial.println(waveData[i].lowVal);
        }
#endif
        break;
      case UPDATE_CHANNEL:    //this is used to update the amplitude of a single channel during runtime
        byte dataBuffer[3];
        Serial.readBytes(dataBuffer, 3);
        uint16toBytes chanWaveAmp;
        uint8_t chanWaveNum;
        chanWaveNum = dataBuffer[0]; //stores the number of the channel to be updated
        chanWaveAmp.integer = dataBuffer[2] << 8 | dataBuffer[1]; //stores the amplitude value of the channel to be updated
        formatChannelData(chanWaveNum, chanWaveAmp);
#if DEBUG
        Serial.println("Cmd: UPDATE CHANNEL");
        Serial.print("Ch ");
        Serial.print(chanWaveNum);
        Serial.print(": ");
        Serial.println(chanWaveAmp.integer);
        Serial.print(" HiVal: ");
        Serial.println(waveData[chanWaveNum].highVal);
        Serial.print(" LoVal: ");
        Serial.println(waveData[chanWaveNum].lowVal);
#endif
        break;
      case UPDATE_FREQUENCY:    //this is used to update the frequency of the produced square wave during runtime
        Serial.readBytes(periodDelay.byteArray, 2);
#if DEBUG
        Serial.println("Cmd: UPDATE FREQUENCY");
        Serial.print("Period delay: ");
        Serial.println(periodDelay.integer);
#endif
        break;
      default:
        Serial.println("No command detected");
        break;
    }
  }
  if (go) {
    loadAllToDAC(waveDataHi);
    delayMicroseconds(periodDelay.integer / 2);
    loadAllToDAC(waveDataLo);
    delayMicroseconds(periodDelay.integer / 2);
    //Serial.println("GO ATTIVO");
  } else {
    if (toReset) {
      loadAllToDAC(waveDataZero);
      //Serial.println("RESETTING OUTPUT");
      toReset = 0;
    }
  }
  //delay(100);
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

void formatZeroData() {   //TODEBUG
  uint32toBytes zeroData[32];
  for (uint32_t i = 0; i < 32; i++) {
    zeroData[i].integer = (i << 27);
    waveDataZero[i] = zeroData[i].byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
    waveDataZero[i + 1] = zeroData[i].byteArray[2];
    waveDataZero[i + 2] = zeroData[i].byteArray[1];
  }
}

void swapChannelBytes(uint8_t chan) {
  uint32toBytes dacData;
  dacData.integer = waveData[chan].highVal;
  waveDataHi[3*chan] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
  waveDataHi[3*chan + 1] = dacData.byteArray[2];
  waveDataHi[3*chan + 2] = dacData.byteArray[1];
  dacData.integer = waveData[chan].lowVal;    //load the value inside an uint32_t
  waveDataLo[3*chan] = dacData.byteArray[3];   //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
  waveDataLo[3*chan + 1] = dacData.byteArray[2];
  waveDataLo[3*chan + 2] = dacData.byteArray[1];
}


void swapWaveBytes() { //TO DEBUG
  uint32toBytes dacData;
  for (int i = 0; i < 32; i++) {
    dacData.integer = waveData[i].highVal;    //load the value inside an uint32_t
    waveDataHi[3 * i] = dacData.byteArray[3]; //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
    waveDataHi[3 * i + 1] = dacData.byteArray[2];
    waveDataHi[3 * i + 2] = dacData.byteArray[1];
    dacData.integer = waveData[i].lowVal;    //load the value inside an uint32_t
    waveDataLo[3 * i] = dacData.byteArray[3]; //use the byte interpretation of uint32_t to swap byte and get the 3 bytes needed
    waveDataLo[3 * i + 1] = dacData.byteArray[2];
    waveDataLo[3 * i + 2] = dacData.byteArray[1];
  }
}

void loadSingleToDAC(byte waveChannelData[]) {
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));  //open the SPI channel
  digitalWrite(chipSelectPin, LOW);
  for (int i = 0; i < 3; i++)
    SPI.transfer(waveChannelData[i]);
  digitalWrite(chipSelectPin, HIGH);
  SPI.endTransaction();
}


void loadAllToDAC(byte waveArrayData[]) {  //TO DEBUG
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));  //open the SPI channel
  for (int i = 0; i < 32; i++) {
    digitalWrite(chipSelectPin, LOW);
    for (int j = 0; j < 3; j++)
      SPI.transfer(waveArrayData[3 * i + j]);
    digitalWrite(chipSelectPin, HIGH);
  }
  SPI.endTransaction();
}
