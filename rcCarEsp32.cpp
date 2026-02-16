#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "AutoESP32";
const char* password = "12345678";

WebServer server(80);

// Pines del L298N
int IN1 = 26;
int IN2 = 27;
int IN3 = 14;
int IN4 = 12;

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println("WiFi iniciado");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/forward", forward);
  server.on("/back", back);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/stop", stopCar);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>button{width:100px;height:60px;font-size:20px;margin:5px;}</style>";
  html += "</head><body style='text-align:center;'>";
  html += "<h2>Auto RC</h2>";
  html += "<a href='/forward'><button>↑</button></a><br>";
  html += "<a href='/left'><button>←</button></a>";
  html += "<a href='/stop'><button>■</button></a>";
  html += "<a href='/right'><button>→</button></a><br>";
  html += "<a href='/back'><button>↓</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  server.send(200, "text/html", "Adelante");
}

void back() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  server.send(200, "text/html", "Atras");
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  server.send(200, "text/html", "Izquierda");
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  server.send(200, "text/html", "Derecha");
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  server.send(200, "text/html", "Stop");
}
