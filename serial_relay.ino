const int relay_on = 12;

void setup() {
  Serial.begin(9600);
  pinMode(relay_on, OUTPUT);
  digitalWrite(relay_on, 1);

}

void loop() {
  String cmd;

  if (Serial.available()) {
    cmd = Serial.readString();
    Serial.println("got: \"" + cmd + "\"");
    if (cmd == "Arty on"){
      digitalWrite(relay_on, 1);
    }
    else if (cmd == "Arty off"){ 
      digitalWrite(relay_on, 0);
    }
    else {
      Serial.println("meh");
    }
  }
}
