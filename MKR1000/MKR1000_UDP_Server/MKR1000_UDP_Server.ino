/* THIS CODE MAKES THE GENUINO MKR1000 A UDP SERVER
    ABLE TO COMUNICATE WITH "MKR1000 UDP Client.VI"
 ****************************************************
 ******************EDITED BY Frax84*****************
 ************************ENJOY!**********************
*/

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

enum Command {
  UNKNOWN_CMD = 255,
  NONE = 0,
  IS_CONNECTED = 1,
  SET_TIME = 2,
  SET_CHANNELS = 3,
  START_ACQ = 4,
  STOP_ACQ = 5,
};

const int READ_RESOLUTION = 12; // bit depth

int status = WL_IDLE_STATUS;
char ssid[] = "MKR1000Net"; //  your network SSID (name)
char pass[] = "mkr1000lan";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 1;            // your network key Index number (needed only for WEP)
IPAddress ip(192, 168, 1, 5); //Force IP address

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[32] = "ACK";       // a string to send back

Command cmd = NONE; //command sent by the UDP client
int param = 0;   // (optional) parameter of the command

int sample_time = 0; // sample time set by client param in ms
int channel_config = 0; //channel configuration set by client param
bool acquire = 0; // start/stop acquisition of data
float Data[6];


WiFiUDP Udp;

void setup() {
  WiFi.config(ip); 
  do
  {
  } while (WiFi.status()== WL_NO_SHIELD);
  analogReadResolution(READ_RESOLUTION);
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  /*while (!Serial)
  {
    //loop until Serial is not available
  }*/
  Serial.println("DEBUG MODE:");
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to client...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Ricevuto pacchetto di ");
    // read the packet into packetBuffer - 9 BYTES will be read XXYYYYYY/n : 2 bytes for command - 6 bytes for variable - 1 byte for endchar
    int len = Udp.read(packetBuffer, 9);
    if (len > 0) packetBuffer[len] = 0;
    // parse the packet coming from the client
    cmd = readClientCommand(packetBuffer);
    param = readClientParam(packetBuffer);
    // modify the MKR1000 parameters based on the parsed command
    switch (cmd) {
      case NONE:
        break;
      case IS_CONNECTED:
        Serial.println("Richiesta connessione");
        sprintf(ReplyBuffer,"ACK");
        break;
      case SET_TIME:
        sample_time = param;
        Serial.println("Setting di intervallo di acquisizione");
        Serial.print("Impostato timing a: ");
        Serial.println(sample_time);
        sprintf(ReplyBuffer,"ACK");
        break;
      case SET_CHANNELS:
        channel_config = param;
        Serial.println("Setting di canali");
        Serial.print("Impostato riferimento canali a: ");
        Serial.println(channel_config);
        sprintf(ReplyBuffer,"ACK");
        break;
      case START_ACQ:
        Serial.println("Start di acquisizione");
        acquire = 1;
        sprintf(ReplyBuffer,"ACK");
        break;
      case STOP_ACQ:
        Serial.println("Stop di acquisizione");
        acquire = 0;
        sprintf(ReplyBuffer,"ACK");
        break;
      default:
        Serial.println("COMANDO NON RICONOSCIUTO");
        break;
        //end the packet
    }
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    Udp.flush(); //flush the packetbuffer and go to the next packet
    delay(500); //wait to confirm command
  }
  if (acquire) {
    for (int i = 0; i < 6; i++) {
      if (bitRead(channel_config, i))
      { //check which channel has to be acquired
        Data[i] = analogRead(i)*3.3/pow(2, READ_RESOLUTION);
        Serial.println(Data[i]);
      }
      else {
        Data[i] = -1; //write -1 if channel is disabled
      }
    }
    //Serial.println();
    sprintf(ReplyBuffer, "%.3f;%.3f;%.3f;%.3f;%.3f;%.3f" , Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]); //place
    //Serial.println(ReplyBuffer);
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    delay(sample_time);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

Command readClientCommand(char RxBuffer[255]) {
  char CmdBuffer[2];
  for (int i = 0; i < 2; i++) {
    CmdBuffer[i] = RxBuffer[i];
  }
  int client_cmd = atoi(CmdBuffer);
  switch (client_cmd) {
    case 0:
      return NONE;
      break;
    case 1:
      return IS_CONNECTED;
      break;
    case 2:
      return SET_TIME;
      break;
    case 3:
      return SET_CHANNELS;
      break;
    case 4:
      return START_ACQ;
      break;
    case 5:
      return STOP_ACQ;
      break;
    default:
      return UNKNOWN_CMD;
      break;
  }

}

int readClientParam( char RxBuffer[255]) {
  char ParamBuffer[6];
  for (int i = 0; i < 6; i++) {
    ParamBuffer[i] = RxBuffer[2 + i];
  }
  int client_param = atoi(ParamBuffer);
  return client_param;
}
