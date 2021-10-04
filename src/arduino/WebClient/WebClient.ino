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

//#define DEBUG 1
#undef DEBUG

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
char jsonLine[256];
char * lineBuffer;
int lineBufferLen;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// IPAddress server(3,213,104,19);  // numeric IP for dweet.io
const char server[] = "dweet.io";    // name address for dweet.io

StaticJsonDocument<256> doc;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 1, 1, 177);
// IPAddress myDns(10, 1, 1, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


void setup() {

  // show error status on builtin led via panic() function
  pinMode(LED_BUILTIN, OUTPUT);




  // initalise speaker relays

  for (int i = 0; i < sizeof(spk_status); i++) {
    pinMode(spk_pin[i], OUTPUT);
    digitalWrite(spk_pin[i], spk_status[i]);
  };

  // setup for JSON decoding

  strcpy(buffer, "{\"json_line\":");
  lineBuffer = &buffer[strlen(buffer)];
  lineBufferLen = BUFFLEN - strlen(buffer);

#ifdef DEBUG
  Serial.print("buffer: ");
  Serial.println(buffer);
  Serial.print("lineBuffer: ");
  Serial.println(lineBuffer);
  Serial.print(F("lineBufferLen: "));
  Serial.println(lineBufferLen);
#endif

}

void network_setup(void) {

  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet connection:
#ifdef DEBUG
  Serial.println(F("Initialize Ethernet with DHCP:"));
#endif
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
#ifdef DEBUG
    Serial.println(F("Ethernet shield was not found.  Sorry, can't run without hardware. :("));
#endif
    panic(1);  // flash the led once at 2 second intervals
  }
  if (Ethernet.linkStatus() == LinkOFF) {
#ifdef DEBUG
    Serial.println(F("Ethernet cable is not connected."));
#endif
    panic(2);
  }

#ifdef DEBUG
  Serial.print(F("IP is: "));
  Serial.println(Ethernet.localIP());
#endif

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
  Serial.print(F("connecting to "));
  Serial.print(server);
  Serial.println(F("..."));
#endif

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
#ifdef DEBUG
    Serial.print(F("connected to "));
    Serial.println(client.remoteIP());
#endif
    return true;

  } else {
    // if you didn't get a connection to the server:
#ifdef DEBUG
    Serial.println(F("connection failed"));
#endif
    return false;
  }
}

void loop() {

  network_setup();

  // wait for server connection
  while (!connect_to_server()) {
    panic(4);
  }

  // make HTTP request:
  // Make a HTTP request:
  client.println(F("GET /listen/for/dweets/from/gooreen-speakers HTTP/1.1"));
  client.println(F("Host: dweet.io"));
  client.println(F("Connection: keep-alive"));
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

      Serial.print(F("Bytes: "));
      Serial.println(n, DEC);
#endif

      // prepare to deserialise JSON

      strcat(buffer, "}");
#ifdef DEBUG
      Serial.print(F("deserialising: "));
      Serial.println(buffer);
#endif



      error = deserializeJson(doc, buffer);
      if (error) {
#ifdef DEBUG
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
#endif
      } else {

        strcpy(jsonLine, doc["json_line"]);
#ifdef DEBUG
        Serial.print(F("now deserialising: "));
        Serial.println(jsonLine);
#endif

        error = deserializeJson(doc, jsonLine);
        if (error) {
#ifdef DEBUG
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          delay(1000);
#endif
        } else {
          const char* command = doc["content"]["Speaker Status"];
#ifdef DEBUG
          Serial.print(F("Command: "));
          Serial.println(command);
#endif
          int rc = processCommand(command);
#ifdef DEBUG
          Serial.print(F("processing return code: "));
          Serial.println(rc, DEC);
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

#ifdef DEBUG
  Serial.print(F("processing: "));
  Serial.println(command);
#endif

  // split into <target> <op>

  char * target = command;
  char * op = command;
  char * ptr = command;

  while (*ptr != '\0') {
    if (*ptr == ' ') {
      *ptr = '\0';
      op = ptr + 1;
      break;
    }
    ptr++;
  }

#ifdef DEBUG
  Serial.print(F("target: "));
  Serial.println(target);
  Serial.print(F("op: "));
  Serial.println(op);
#endif

  // check that we could find both a target and op
  if (op == command) {
#ifdef DEBUG
    Serial.println(F("could not parse <target> <op>"));
#endif
    return -1;
  }


  // find target speakers

  int spk_index = findSpeaker(target);

#ifdef DEBUG
  Serial.print(F("spk_index: "));
  Serial.println(spk_index);
#endif

  if (spk_index < 0) {
#ifdef DEBUG
    Serial.println(F("speaker not recognized"));
#endif
    return -2;
  }

  // decode the op as either "on" or "off"
  int opCode = decodeOp(op);
  if (opCode < 0) {
#ifdef DEBUG
    Serial.println(F("op not recognized"));
#endif
    return -3;
  }

  // check for "all" speakers
#ifdef DEBUG
  Serial.print(F("sizeof(spk_name): "));
  Serial.println(sizeof(spk_name));
#endif

  if (spk_index == 4) {
    // is "all"
    if (opCode == 1) {
#ifdef DEBUG
      Serial.println(F("cannot execute 'all on'"));
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

void panic(int err) {
  for (int j = 0; j < 5; j++) {
    for (int i = 1; i <= err; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
    delay(2000);
  }
}
