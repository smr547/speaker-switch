/*
  Web Server to control my speaker switch

  The web server listens on port 80 and responds only to GET requests of the form

  GET / HTTP/1.1 -- responds with HTML helps page
  GET /scr HTTP/1.1 -- responds with status of Speaker Control Register (scr) in HEX
  GET /scr&hh HTTP/1.1 -- sets the speaker control value to the hex value hh, responds with scr HEX value

  All other requests will generate a status code of 400 -- Bad Request
  For other hardware doco and other details see https://github.com/smr547/speaker-switch

  Steven Ring
  October 3, 2021
*/

#include <SPI.h>
#include <Ethernet.h>


#define MAX_BUF_LEN 64
char buffer[MAX_BUF_LEN] = "";

/**
   scr -- an 8 bit speaker control register where each bit
   controls one pair of speakers
*/
//
byte scr;

// speaker names for help page
String speakers[8] = {
  "Terrace",
  "Dining",
  "Kitchen",
  "Lounge",
  "Unused",
  "Unused",
  "Unused",
  "Unused"
};

/**
   The following Arduino digital pins are connected to Darlington
   transistors that drive the speaker switching relays
*/
unsigned short spk_pin[] = {2, 3, 4, 5, 6, 7, 8, 9};
/**
   Set the value of the relay driver output pins to match
   the speaker control register (scr)
*/
void configureRelays(byte scr) {
  for (int i = 0; i < 8; i++) {
    pinMode(spk_pin[i], OUTPUT);
    digitalWrite(spk_pin[i], ((byte)1 << i) & scr);
  }
}

/**
   MAC address and IP address for the Arduino. In this design the
   Arduino is direct connected to the local Ethernet
*/

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 1, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {

  // Turn off all relays

  scr = 0x00;
  configureRelays(scr);

  // initialise the Arduino using the CS pin

  Ethernet.init(10);  // Most Arduino shields


  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (Serial) {
    Serial.println(F("Speaker switch Web Server ver: 0.1"));
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

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

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

/*
   Read characters received from the supplied EthernetClient and return
   whole lines of text to the caller. Lines are deliminted by a CR LF pair
   or simply a LF

   Return a pointer to the buffer containing the received line of text
   Return NULL if the client connection is lost.
   Prevern buffer overflow by returning partial lines of text
*/
char * getRequestLine(EthernetClient * client) {

  unsigned short ptr = 0;   // current text insertion point within the buffer

  while (client->connected()) { // loop continuously, reading character until connection lost
    if (client->available()) {
      char c = client->read();
      buffer[ptr] = '\0'; // make sure the buffer always contains a valid, null terminated, string
      if (ptr == MAX_BUF_LEN - 1) {
        return buffer;    // buffer is full, return the text
      }
      if (c == '\n') {
        if (Serial) {
          Serial.print(F("Returning from getRequestLine() with: "));
          Serial.println(buffer);
        }
        return buffer;    // we've received a LF so return the string
      }
      if (c == '\r') {
        // ignore CR characters, we are not interested
      } else {
        buffer[ptr] = c;    // valid character recieved, append it to the text buffer
        ptr++;
      }
    }
  }
  return NULL;    // client has disconnected
}

void sendError(EthernetClient * client) {
  if (Serial) {
    Serial.println("400 Bad Request");
  }

  client->println(F("HTTP/1.1 400 Bad Request"));
  client->println();
  client->println();
}

void sendOkHeader(EthernetClient * client) {
  if (Serial) {
    Serial.println("200 OK");
  }

  client->println(F("HTTP/1.1 200 OK"));
  client->println(F("Content-Type: text/html"));
  client->println(F("Connection: close"));  // the connection will be closed after completion of the response
  client->println();
}

/* interpret the ascii digits in[0] and in[1] as hex
   notation and convert to an integer 0..255.
*/
int hex8(char *in) {
  uint8_t c, h;

  c = in[0];

  if (c <= '9' && c >= '0') {
    c -= '0';
  } else if (c <= 'f' && c >= 'a') {
    c -= ('a' - 0x0a);
  } else if (c <= 'F' && c >= 'A') {
    c -= ('A' - 0x0a);
  } else return (-1);

  h = c;
  c = in[1];

  if (c <= '9' && c >= '0') {
    c -= '0';
  } else if (c <= 'f' && c >= 'a') {
    c -= ('a' - 0x0a);
  } else if (c <= 'F' && c >= 'A') {
    c -= ('A' - 0x0a);
  } else return (-1);

  return ( h << 4 | c);
}

/**
   Main Arduino loop
*/
void loop() {

  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {

    // we have a connection from a client

    if (Serial) {
      Serial.println("new client");
    }

    // we are only interested the first line of the request (ignore the rest)

    char * line = getRequestLine(&client);

    // if the first line of the request is not NULL, parse it into it's constituent
    // parts according to the HTTP spec

    if (line != NULL) {
      //
      char * method;        // the METHOD text
      char * resource;      // the RESOUCE being accessed
      char * param;         // any parameters
      char * ptr;           // working pointer

      // first the METHOD

      method = line;        // method start at the beginnin
      for (ptr = line; *ptr != ' '; ptr++) {}   // and ends at first space
      *ptr = '\0';

      // now the RESOURCE

      ptr++;
      resource = ptr;       // resouce starts straight after method
      // and ends with first space or the start of parameters (first &)
      while (*ptr != ' ' && *ptr != '&') {
        ptr++;
      }
      if (*ptr == '&') {
        param = ptr + 1;  // there are parameters
      } else {
        param = ptr;
      }
      *ptr = '\0';

      // finally the PARAM

      ptr = param;
      while (*ptr != '\0' && *ptr != ' ') {
        ptr++;
      }
      *ptr = '\0'; // mark the end of parameters

      if (Serial) {
        Serial.print("method=");
        Serial.println(method);
        Serial.print("resource=");
        Serial.println(resource);
        Serial.print("param=");
        Serial.println(param);
      }

      // we only support the GET method

      if (strcmp(method, "GET") != 0) {
        sendError(&client); // illegal method
      } else if (strcmp(resource, "/") == 0) {

        // a request to the root resource yields a human readable webpage

        sendOkHeader(&client);

        client.println(F("<!DOCTYPE HTML>"));
        client.println(F("<html>"));
        client.println(F("<head><style>"));
        client.println(F("table, th, td {border: 1px solid black; border-radius: 10px;}"));
        client.println(F("</style></head><body>"));
        // output the value of each analog input pin
        client.println(F("<p>Speakers are controlled by an 8-bit Speaker Control Register (scr) with bit assignment:<br />"));
        client.println(F("<table>"));
        client.println(F("<tr><th>Bit</th><th>Speaker</th><th>Status</th></tr>"));
        for (int s = 7; s >= 0; s--) {
          client.print(F("<tr><td>"));
          client.print(s);
          client.print(F("</td><td>"));
          client.print(speakers[s]);
          client.print(F("</td><td>"));
          if (scr & (1 << s)) {
            client.print(F(" on"));
          } else {
            client.print(F(" off"));
          }
          client.print(F("</td></tr>"));
        }
        client.println(F("</table>"));
        client.print(F("<p>scr="));
        client.println(scr, HEX);
        client.println(F("<p>Full documentation and code can be <a href=\"https://github.com/smr547/speaker-switch\">found on GitHUB</a></p>"));
        client.println(F("</body></html>"));
      } else if (strcmp(resource, "/scr") == 0 && strlen(param) == 0) {

        // return the HEX representation of the scr

        sendOkHeader(&client);
        client.println(scr, HEX);
      } else if (strcmp(resource, "/scr") == 0 && strlen(param) == 2) {

        // set the scr to the supplied value
        // and reconfigure the relays

        byte new_scr = hex8(param);
        if (new_scr >= 0) {     // check if valid HEX
          scr = new_scr;
          configureRelays(scr);
          sendOkHeader(&client);
          client.println(scr, HEX);
        } else {
          sendError(&client);
        }
      } else {

        // all other cases result in a 400 Bad request error

        sendError(&client);
      }

      // all done for this request

      delay(100);     // give the web browser time to receive the data
      client.stop();  // close the connection
      if (Serial) {
        Serial.println("client disconnected");
      }
    }
  }
}
