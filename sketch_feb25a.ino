
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 // blynk auth
char auth[] = "M8Kg0dZFHC2K5wEqEG3TN7HTKYxiZ1gO";
 
//  WiFi credentials.
char ssid[] = "saibaba";
char pass[] = "12345678";
 
int buzzer = D2; //buzzer
int sensor = A0; //sensor
int led = D0; //led

 
// Define threshold value.
int sensor_limit = 300;
 
void setup()
{
pinMode(buzzer, OUTPUT);
pinMode(sensor, INPUT);
pinMode(led, OUTPUT);

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
}
 
void loop()
{
int sensor_value = analogRead(sensor);
Serial.print("Gas Level: ");
Serial.println(sensor_value);
Blynk.virtualWrite(V1, sensor_value);

// Checks if it has reached the threshold value
if (sensor_value > sensor_limit)
{
digitalWrite(buzzer, HIGH);
delay(500);
digitalWrite(buzzer, LOW);
digitalWrite(led, HIGH);
Blynk.notify("Alert: Gas Leakage Detected!!! Take action Immediately");
}
else
{
digitalWrite(buzzer, LOW);
digitalWrite(led, LOW);

}
delay(100);
Blynk.run(); // Initiates Blynk
}
