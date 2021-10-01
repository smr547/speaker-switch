/*
  Web Server to control my speaker switch 

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

Based on the Arduino sample WebServer code
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 this version by Steven Ring, Oct, 2021
 
 */

#include <SPI.h>
#include <Ethernet.h>


// speaker control register
byte scr = 0xff;  

String speakers[] = {
  "Terrace",
  "Dining",
  "KItchen",
  "Lounge",
  "Unused",
  "Unused",
  "Unused",
  "Unused"
};

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 1, 1, 179);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  
  Ethernet.init(10);  // Most Arduino shields

 
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

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


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          // client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><style>");
          client.println("table, th, td {border: 1px solid black; border-radius: 10px;}");
          client.println("</style></head>");
          // output the value of each analog input pin
          client.println("<p>Speakers are controlled by an 8-bit Speaker Control Register (scr) with bit assignment:<br />");
          client.println("<table>");
          client.println("<tr><th>Bit</th><th>Speaker</th><th>Status</th></tr>");
          for (int s = 7; s >= 0; s--) {
            
            client.print("<tr><td>");
            client.print(s);
            client.print("</td><td>");
            client.print(speakers[s]);
            client.print("</td><td>");
            
             
            if (scr & (1<<s)) {
              client.print(" on");
            
            } else {
              client.print(" off");
            }
            client.print("</td></tr>");
          }
          client.println("</table>");
          client.print("<p>scr=");
          client.println(scr,HEX);
          client.println("<p>Full documentation and code can be <a href=\"https://github.com/smr547/speaker-switch\">found on GitHUB</a></p>");
         
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
