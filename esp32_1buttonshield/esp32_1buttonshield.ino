const int btn = 17; 

const int led = BUILTIN_LED;
 
void setup() {
  pinMode(btn, INPUT); 
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW);
}
 
void loop() {
    digitalWrite(led, digitalRead(btn));  
}
