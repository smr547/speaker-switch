/*
   Speaker Control

   Monitor http://dweet.io/latest/dweet/for/goreen-speakers
   for change in "Speaker Status" and respond by setting
   an array of relays

   Steven Ring
   May, 2021

   Based on work
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe, based on work by Adrian McEwen
*/

#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

#define DEBUG 1
//#undef DEBUG

#define BUFFLEN 256

#define SPK_PATIO 0
#define SPK_DINING 1
#define SPK_KITCHEN 2
#define SPK_LOUNGE 3

const int spk_pin[4] = {2, 3, 4, 5};
int spk_status[4] = {LOW, LOW, LOW, LOW};
const char * spk_name[] = {"patio", "dining", "kitchen", "lounge", "all"};


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

  // Open serial communications and wait for port to open:
#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif

  // start the Ethernet connection:
#ifdef DEBUG
  Serial.println("Initialize Ethernet with DHCP:");
#endif
  if (Ethernet.begin(mac) == 0) {
#ifdef DEBUG
    Serial.println("Failed to configure Ethernet using DHCP");
#endif
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
#ifdef DEBUG
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
#endif
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
#ifdef DEBUG
      Serial.println("Ethernet cable is not connected.");
#endif
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
#ifdef DEBUG
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
#endif
  }

  // initalise speaker relays

  for (int i = 0; i < sizeof(spk_status); i++) {
    pinMode(spk_pin[i], OUTPUT);
    digitalWrite(spk_pin[i], spk_status[i]);
  };

  // setup for JSON decoding

  strcpy(buffer, "{\"json_line\":");
  lineBuffer = &buffer[strlen(buffer)];
  lineBufferLen = BUFFLEN - strlen(buffer);

}

/*
   Connect to dweet server

   Return
     true if OK
     false on error
*/
bool connect_to_server(void) {
  // give the Ethernet shield a second to initialize:
  delay(1000);
#ifdef DEBUG
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
#endif

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
#ifdef DEBUG
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
#endif
    return true;

  } else {
    // if you didn't get a connection to the server:
#ifdef DEBUG
    Serial.println("connection failed");
#endif
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


  // if the server remains connected and
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.connected()) {
    int len = client.available();
    if (len > 0) {

      int n = readLine(&client, lineBuffer, lineBufferLen, 100);

#ifdef DEBUG

      Serial.println(lineBuffer);

      Serial.print("Bytes: ");
      Serial.println(n, DEC);
#endif

      // prepare to deserialise JSON

      strcat(buffer, "}");
#ifdef DEBUG
      Serial.print("deserialising: ");
      Serial.println(buffer);
#endif



      error = deserializeJson(doc, buffer);
      if (error) {
#ifdef DEBUG
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
#endif
      } else {
        char jsonLine[256];
        strcpy(jsonLine, doc["json_line"]);
#ifdef DEBUG
        Serial.print("now deserialising: ");
        Serial.print(jsonLine);
#endif

        error = deserializeJson(doc, jsonLine);
        if (error) {
#ifdef DEBUG
          // Serial.print(F("deserializeJson() failed: "));
          // Serial.println(error.f_str());
#endif
        } else {
          const char* command = doc["content"]["Speaker Status"];
          processCommand(command);
#ifdef DEBUG
          Serial.print("Command: ");
          Serial.println(command);
#endif
        }
      }
    }
  }

#ifdef DEBUG
  Serial.println();
  Serial.println("disconnecting.");
#endif
  client.stop();
}

/*
    Process the supplied command -- expecting something like "lounge on" or "all off"
    Return:
      0 if ok
      < 0 on error
*/
int processCommand(char * command) {

  // covert to lower case and split in two
  command = toLower(command);

  // split into <target> <op>

  char * target = command;
  char * op = command;
  char * ptr = command;

  while (*ptr != '\0') {
    if (*ptr == ' ') {
      op = ptr + 1;
      break;
    }
  }

// check that we could find both a target and op
  if (op == command) {
#ifdef DEBUG
    Serial.println("could not parse <target> <op>");
#endif
    return -1;
  }


  // find target speakers

  int spk_index = findSpeaker(target);
  if (spk_index < 0) {
#ifdef DEBUG
    Serial.println("speaker not recognized");
#endif
    return -2;
  }

  // decode the op as either "on" or "off"
  int opCode = decodeOp(op);
  if (opCode < 0) {
#ifdef DEBUG
    Serial.println("op not recognized");
#endif
    return -3;
  }

  // check for "all" speakers

  if (spk_index == (sizeof(spk_name) - 1)) {
    // is "all"
    if (opCode == 1) {
#ifdef DEBUG
      Serial.println("cannot execute 'all on'");
#endif
      return -4;
    }
    // turn all off
    for (int i = 0; i < sizeof(spk_status); i++) {
      spk_status[i] = LOW;
    }
  } else {
    // control selected speaker
    spk_status[spk_index] = opCode;
  }

  // update relay status

  for (int i = 0; i < sizeof(spk_status); i++) {
    digitalWrite(spk_pin[i], spk_status[i]);
  }

  // all done ok
  return 0;
}
/*
   decode the supplied operation
   Return
     0 if "off"
     1 if "on"
     -1 on error
*/
int decodeOp(const char * op) {
  if (strcmp(op, "on") == 0) {
    return 1;
  } else if (strcmp(op, "off") == 0) {
    return 0;
  } else {
    return -1;
  }
}

/*
    Find the named in the string
    Return:
      index of speaker in spk_name array
      -1 if not found
*/

int findSpeaker(const char * speaker) {
  for (int i = 0; i < sizeof(spk_name); i++) {
    if (strcmp(speaker, spk_name[i]) == 0) {
      return i;
    }
  }
  return -1;
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
    Convert supplied string to lower case (in place)
*/
char * toLower(char * buf) {
  char * ptr = buf;
  while (*ptr != '\0') {
    *ptr = tolower(*ptr);
    ptr++;
  }
  return buf;
}
