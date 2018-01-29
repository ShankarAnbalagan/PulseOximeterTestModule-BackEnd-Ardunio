int data[256];
float frequency[6];
unsigned char i = 0, j = 0;
String incomming_data = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  Serial1.begin(4800);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (frequency[0] == 20525 && frequency[1] == 16000 && frequency[2] == 4 && frequency[3] == 28394 && frequency[4] == 25000 && frequency[5] == 3) { //20525,16000,4,28394,25000,3,
    digitalWrite(4, HIGH);
    while (Serial1.available()) {
      data[i++] = Serial1.read();
    }
    while (j != i)
    {
      //Serial.println(data[j++]);

      if (data[j] == 135) {
        Serial.println(((String)data[j]) + "," + ((String)data[j + 1])+ "," + ((String)data[j + 2])+ "," + ((String)data[j + 3])+ "," + ((String)data[j + 4])+ "," + ((String)data[j + 5])+ "," + ((String)data[j + 6])+ "," + ((String)data[j + 7])+ "," + ((String)data[j + 8])+ "," + ((String)data[j + 9])+ "," + ((String)data[j + 10])+ "," + ((String)data[j + 11])+ "," + ((String)data[j + 12]));
      }
      j++;
    }
    digitalWrite(4, LOW);
  }
  digitalWrite(5, LOW);
}

void convIncommingData() {
  String substr;
  char c;
  int first = 0, j = 0;
  for (int i = 0; i < incomming_data.length(); i++) {
    c = incomming_data.charAt(i);
    if ((c == ',') && (incomming_data.charAt(i + 1) == '\0')) {
      substr = incomming_data.substring(first, i);
      frequency[j] = substr.toFloat();
      break;
    }
    else if (c == ',')
    {
      substr = incomming_data.substring(first, i);
      frequency[j] = substr.toFloat();
      first = i + 1;
      j++;
    }
  }
}

void serialEvent() {
  if (Serial.available()) {
    digitalWrite(5, HIGH);
    incomming_data = Serial.readString();
    convIncommingData();
  }
}
