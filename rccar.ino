#include <WiFi.h>
#include <WebServer.h>
// Replace with your network credentials
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
// Motor A
int motorA1 = 25; // IN1 on the motor driver
int motorA2 = 33; // IN2 on the motor driver
int enableA = 2;  // ENA on the motor driver
// Motor B
int motorB1 = 32; // IN3 on the motor driver
int motorB2 = 5; // IN4 on the motor driver
int enableB = 4;  // ENB on the motor driver
// Define the WebServer port
const int serverPort = 80;
WebServer server(serverPort);
void setup() {
  // Set motor pins as outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enableA, OUTPUT);
  
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableB, OUTPUT);
  
  // Initialize all motors to off
  stopCar(); 
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print the IP address
  Serial.println(WiFi.localIP());
  // Define endpoint handlers
  server.on("/forward", HTTP_GET, []() {
    forward();
    server.send(200, "text/plain", "Going forward");
  });
  
  server.on("/reverse", HTTP_GET, []() {
    reverse();
    server.send(200, "text/plain", "Going reverse");
  });
  server.on("/left", HTTP_GET, []() {
    left();
    server.send(200, "text/plain", "Turning left");
  });
  server.on("/right", HTTP_GET, []() {
    right();
    server.send(200, "text/plain", "Turning right");
  });
  server.on("/stop", HTTP_GET, []() {
    stopCar();
    server.send(200, "text/plain", "Stopping");
  });
  // Start server
  server.begin();
}
void loop() {
  server.handleClient();
}
void forward() {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, HIGH);
}
void reverse() {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, HIGH);
}
void left() {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}
void right() {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}
void stopCar() {
  digitalWrite(enableA, LOW);
  digitalWrite(enableB, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
