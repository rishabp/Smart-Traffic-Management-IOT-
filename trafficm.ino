#include <SPI.h>
#include <Ethernet.h>
int r1 = 2;
int y1 = 3;
int g1 = 4;
int r2 = 5;
int y2 = 6;
int g2 = 7;
int r3 = 8;
int y3 = 9;
int g3 = 10;
int r4 = 11;
int y4 = 12;
int g4 = 13;
 int f1=2;
 int f2=2;
 int f3=2;
 int f4=2;
const int lane1=A0;
const int lane2=A1;
const int lane3=A2;
const int lane4=A3;
int k=20;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192 ,168 ,137 ,16);//ip address of the arduino



// fill in your Domain Name Server address here:
IPAddress myDns(8, 8, 8, 8);
byte getway[] = {192 ,168 ,137 ,1};////ip address of the port through which ardrino has connected
// initialize the library instance:
EthernetClient client;
int c = 0;
char server[] = "192.168.137.1";//ip address of the port through which ardrino has connected
//char server[] = "128.199.170.225";//ip address of the server (wampp or dogital ocen)
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 2L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers




void setup() {
pinMode (r1, OUTPUT);
pinMode (y1, OUTPUT);
pinMode (g1, OUTPUT);

pinMode (r2, OUTPUT);
pinMode (y2, OUTPUT);
pinMode (g2, OUTPUT);

pinMode (r3, OUTPUT);
pinMode (y3, OUTPUT);
pinMode (g3, OUTPUT);

pinMode (r4, OUTPUT);
pinMode (y4, OUTPUT);
pinMode (g4, OUTPUT);

Serial.begin(9600);
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns, getway);

  ////// captive portal login
  /*client.connect("10.10.10.1",80);
  client.println("GET /cgi-bin/user_session.ggi?user=macrologic&passwd=macrologic123 HTTP/1.1");
  client.println("Host: 10.10.10.1");*/
  //client.println("Accept: */*");
  /*client.println("User-Agent: Mozilla/5.0");
  //client.println("Connection: close");
  client.println()*/
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}


void loop() { 

 if(analogRead(lane1)  <= k)
  { f1=4;}
digitalWrite(g1, HIGH);
digitalWrite(r2, HIGH);
digitalWrite(r3, HIGH);
digitalWrite(r4, HIGH);
delay(f1*5000);
Serial.println(f1);
digitalWrite(g1, LOW);
digitalWrite(r2, LOW);

digitalWrite(y1, HIGH);
digitalWrite(y2, HIGH);
delay(3000);
digitalWrite(y1, LOW);
digitalWrite(y2, LOW);
if(analogRead(lane2)  <= k)
  { f2=4;}
digitalWrite(r1, HIGH);
digitalWrite(g2, HIGH);
delay(f2*5000);
Serial.println(f2);
//Serial.println(analogRead(lane2));
digitalWrite(g2, LOW);
digitalWrite(r3, LOW);


digitalWrite(y2, HIGH);
digitalWrite(y3, HIGH);
delay(3000);

digitalWrite(y2, LOW);
digitalWrite(y3, LOW);
//??? ??????? 

digitalWrite(y3, HIGH);
digitalWrite(y4, HIGH);
delay(3000);


if(analogRead(lane3)  <= k)
  { f3=4;}
  Serial.println(f3);
  //Serial.println(analogRead(lane3));
digitalWrite(r2, HIGH);
digitalWrite(g3, HIGH);
digitalWrite(r4, HIGH);
delay(f3*5000);

digitalWrite(g3, LOW);
digitalWrite(r4, LOW);
digitalWrite(y3, LOW);
digitalWrite(y4, LOW);
if(analogRead(lane4)  <= k)
  { f4=4;}
  Serial.println(f4);
  //Serial.println(analogRead(lane4));
digitalWrite(r3, HIGH);
digitalWrite(g4, HIGH);
delay(f4*5000);

digitalWrite(r3, LOW);
digitalWrite(g4, LOW);
digitalWrite(r1, LOW);
digitalWrite(y1, HIGH);
digitalWrite(y4, HIGH);
delay(3000);

digitalWrite(y1, LOW);
digitalWrite(y4, LOW);


if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
}
}

void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    c++;
    Serial.println(c);

   // DHT.read11(DHT11_PIN);
    client.print("GET /put.php?d1=");
    //client.print("http://192.168.137.1/put.php?d1=");
    client.print(10);
    client.print("&d2=");
    client.print(20);
    client.println(" HTTP/1.1");
    client.println("Host: 128.199.170.225");
    client.println("User-Agent: arduino-ethernet");
    client.println("Accept-Encoding: gzip");
    client.println("Accept-Charset: ISO-8859-1,UTF-8;q=0.7,*;q=0.7");
    client.println("Cache-Control: no-cache");
    client.println("Accept-Language: de,en;q=0.7,en-us;q=0.3");
    client.println("Connection: close");
    client.println();
    Serial.write("request sent\n");
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed\n");
    delay(2000);
  }
}
