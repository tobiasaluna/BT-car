#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "AutoESP32";
const char* password = "12345678";

WebServer server(80);

// Pines
int M1A = 26; // tracción
int M1B = 27;

int M2A = 14; // dirección
int M2B = 12;

void setup() {
  Serial.begin(115200);

  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/move", handleMove);

  server.begin();
}

void loop() {
  server.handleClient();
}

void stopAll() {
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}

void handleMove() {
  String dir = server.arg("dir");

  if (dir == "forward") {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
  }

  if (dir == "back") {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
  }

  if (dir == "left") {
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
  }

  if (dir == "right") {
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
  }

  if (dir == "stop") {
    stopAll();
  }

  server.send(200, "text/plain", "OK");
}

void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  body { text-align:center; font-family:Arial; }
  button { width:100px; height:80px; font-size:30px; margin:10px; }
  </style>
  </head>
  <body>
  <h2>Auto ESP32</h2>

  <button ontouchstart="send('forward')" ontouchend="send('stop')">↑</button><br>
  <button ontouchstart="send('left')" ontouchend="send('stop')">←</button>
  <button ontouchstart="send('right')" ontouchend="send('stop')">→</button><br>
  <button ontouchstart="send('back')" ontouchend="send('stop')">↓</button>

  <script>
  function send(dir){
    fetch("/move?dir=" + dir);
  }
  </script>

  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}
