void setup() {
Serial.begin(9600);
Serial3.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial3.available()){
    while (Serial3.available()){
      char c=Serial3.read();
      Serial.write(c);
    }
}
  if (Serial.available()){
    delay(1000);
    String command="";
    while (Serial.available()){
      command+=(char)Serial.read();
    }
    Serial3.println(command);
  }
}
