const byte BTN_PIN = 7;
bool btnState;
bool lastBtnState = 0;

const byte LED_PIN = 4;
bool ledState = 0;

const byte TIP120_PIN = 3;
bool motState = 0;

int rm = 0;

//int click = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TIP120_PIN, OUTPUT);
}

void loop() {
  //se premo bottone si accende led, se lascio si spegne -------------------------------------------
  //if(digitalRead(BTN_PIN)) digitalWrite(D2, HIGH);
  //else digitalWrite(D2, LOW);

  //se premo bottono si accnede led, se ripremo si spegne, conto i click ---------------------------
  // btnState = digitalRead(BTN_PIN);
  // if(btnState != lastBtnState){
  //   lastBtnState = btnState;

  //   if(btnState == 1){
  //     click++;
  //     Serial.println(click);

  //     if(click%2 == 0) digitalWrite(LED_PIN, LOW);
  //     else digitalWrite(LED_PIN, HIGH);
  //   }
  // }
  
  //se premo bottono si accnede led, se ripremo si spegne, controllo stato led --------------------
  // btnState = digitalRead(BTN_PIN);
  // if (btnState == 1 && btnState != lastBtnState) ledState = !ledState;
  // lastBtnState = btnState;
  // digitalWrite(LED_PIN, ledState);

  //motor.ino acceso/spento con btn ---------------------------------------------------------------
  // btnState = digitalRead(BTN_PIN);

  // if (btnState == 1 && btnState != lastBtnState){
  //   ledState = !ledState;
  //   motState = !motState;
  //   delay(100);
  // }

  // lastBtnState = btnState;
  // digitalWrite(LED_PIN, ledState);
  // digitalWrite(TIP120_PIN, motState);

  //motor.ino rampe velocità ----------------------------------------------------------------------
  btnState = digitalRead(BTN_PIN);

  if (btnState == 1 && btnState != lastBtnState){

    for(rm = 0; rm <=255; rm++){
      analogWrite(TIP120_PIN, rm);
      analogWrite(LED_PIN, rm);
      delay(10);
    }

    for(rm = 255; rm >=0; rm--){
      analogWrite(TIP120_PIN, rm);
      analogWrite(LED_PIN, rm);
      delay(10);
    }

  }

  lastBtnState = btnState;

  //motor.ino controllo velocità 
}