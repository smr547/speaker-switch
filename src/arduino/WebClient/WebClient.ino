/*
 * Speaker Control
 * 
 * Monitor http://dweet.io/latest/dweet/for/goreen-speakers
 * for change in "Speaker Status" and respond by setting 
 * an array of relays
 * 
 * Steven Ring
 * May, 2021
 * 
 * Based on work 
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe, based on work by Adrian McEwen
*/

#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

#define BUFFLEN 256

#define SPK_PATIO 0
#define SPK_DINING 1
#define SPK_KITCHEN 2
#define SPK_LOUNGE 3

const int spk_pin[4] = {2, 3, 4, 5};
int spk_status[4] = {LOW, LOW, LOW, LOW};


DeserializationError error;
const char buffer[BUFFLEN];
char * lineBuffer;
int lineBufferLen;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "dweet.io";    // name address for Google (using DNS)

StaticJsonDocument<128> doc;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 1, 1, 177);
IPAddress myDns(10, 1, 1, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  for (int i = 0; i < 4; i++) {
    pinMode(spk_pin[i], OUTPUT);
    digitalWrite(spk_pin[i], spk_status[i]);
  };

  // setup for JSON decoding

  strcpy(buffer, "{\"json_line\":");
  lineBuffer = &buffer[strlen(buffer)];
  lineBufferLen = BUFFLEN - strlen(buffer);

}

bool connect_to_server(void) {
  // give the Ethernet shield a second to initialize:
  delay(1000);
 // Serial.print("connecting to ");
 // Serial.print(server);
 // Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
//    Serial.print("connected to ");
//    Serial.println(client.remoteIP());
    return true;

  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    return false;
  }
}

void loop() {

  // wait for server connection
  while (!connect_to_server()) {}

  // make HTTP request:
  // Make a HTTP request:
  client.println("GET /listen/for/dweets/from/gooreen-speakers HTTP/1.1");
  client.println("Host: dweet.io");
  client.println("Connection: keep-alive");
  client.println();

  // toggle relays
  /*
    for (int i = 0; i < 4 ; i++) {
          if (spk_status[i] == LOW) {
            spk_status[i] = HIGH;
          } else {
            spk_status[i] = LOW;
          }
          Serial.print(spk_pin[i], DEC);
          Serial.print(" ");
          Serial.print(spk_status[i], DEC);
          digitalWrite(spk_pin[i], spk_status[i]);
          Serial.println("");

        };
  */



  // if the server remains connected and
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.connected()) {
    int len = client.available();
    if (len > 0) {

      int n = readLine(&client, lineBuffer, lineBufferLen, 100);

      // Serial.println(lineBuffer);

      // Serial.print("Bytes: ");
      // Serial.println(n, DEC);

      // prepare to deserialise JSON

      strcat(buffer, "}");
      // Serial.print("deserialising: ");
      //Serial.println(buffer);



      error = deserializeJson(doc, buffer);
      if (error) {
      //  Serial.print(F("deserializeJson() failed: "));
      //  Serial.println(error.f_str());
      } else {
        //char * jsonLine = doc["json_line"];
        char jsonLine[256];
        strcpy(jsonLine, doc["json_line"]);
        // Serial.print("now deserialising: ");
        // Serial.print(jsonLine);
        // Serial.println("|");

        error = deserializeJson(doc, jsonLine);
        if (error) {
         // Serial.print(F("deserializeJson() failed: "));
          // Serial.println(error.f_str());
        } else {
          //Serial.println("That's JSON!!");
          const char* command = doc["content"]["Speaker Status"];
          command = toLower(command);
          //Serial.print("Command: ");
          Serial.println(command);
        }
      }
    }
  }

//  Serial.println();
//  Serial.println("disconnecting.");
  client.stop();
}

/*
   Read characters from the client until new line is encoutered or
   timeout or buffer full (timeout not implemented yet)

   Return
   number of characters read
*/
int readLine(EthernetClient * c, char * buf, int max_len, int timeout_millisecs) {

  int ptr = 0;
  buf[ptr] = 0;
  while (client.connected()) {
    while (client.available()) {
      c->read(buf + ptr, 1);
      if (buf[ptr] == '\n') {
        buf[ptr] = 0;
        return ptr;
      }
      ptr++;
      buf[ptr] = 0;
      if (ptr >= max_len) {
        return ptr - 1;
      }
    }
  }
}

/* 
 *  Convert supplied string to lower case
 */
char * toLower(char * buf) {
  char * ptr = buf;
  while (*ptr != '\0') {
    *ptr = tolower(*ptr);
    ptr++;
  }
  return buf;
}
