const byte BTN_PIN = 13;
bool btnState;
bool lastBtnState = 0;

const byte LED_PIN = 11;
bool ledState = 0;

const byte TIP120_PIN = 10;
int motState = 0;

const byte POT_PIN = A0;
int pwm = 0;

const byte ENCODER_PIN = 7;
bool encoderState;
bool lastEncoderState = 0;
unsigned long startTime = 0;
unsigned long endTime = 0;
int steps = 0;
float lastSteps = 0;
float temp = 0;
float rps = 0;
float rpm = 0;

bool canGo = 0;

//int click = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TIP120_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(ENCODER_PIN, INPUT);
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
  
  //se premo bottono si accende led, se ripremo si spegne, controllo stato led --------------------
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
  // btnState = digitalRead(BTN_PIN);

  // if (btnState == 1 && btnState != lastBtnState){

  //   for(motState = 0; motState <=255; motState++){
  //     analogWrite(TIP120_PIN, motState);
  //     analogWrite(LED_PIN, motState);
  //     delay(10);
  //   }

  //   for(motState = 255; motState >=0; motState--){
  //     analogWrite(TIP120_PIN, motState);
  //     analogWrite(LED_PIN, motState);
  //     delay(10);
  //   }

  // }

  // lastBtnState = btnState;

  //motor.ino controllo velocità con potenziometro e bottone --------------------------------------
  // btnState = digitalRead(BTN_PIN);
  // if (btnState == 1 && btnState != lastBtnState){
  //   posso = !posso;
  // }

  // if (posso == 1){
  //   pwm = analogRead(POT_PIN);
  //   motState = map(pwm, 0, 1023, 0, 255);
  //   analogWrite(TIP120_PIN, motState);
  //   analogWrite(LED_PIN, motState);
  // } else {
  //   analogWrite(TIP120_PIN, 0);
  //   analogWrite(LED_PIN, 0);
  // }

  // lastBtnState = btnState;

  //motor.ino lettura velocità con encoder in un secondo -------------------------------------------
  // btnState = digitalRead(BTN_PIN);
  // if (btnState == 1 && btnState != lastBtnState){
  //   canGo = !canGo;
  // }

  // if (canGo){
  //   pwm = analogRead(POT_PIN);
  //   motState = map(pwm, 0, 1023, 0, 255);
  //   analogWrite(TIP120_PIN, motState);
  //   analogWrite(LED_PIN, motState);
    
  //   startTime = millis();
  //   endTime = startTime + 1000;

  //   while(millis() < endTime){
  //     if (digitalRead(ENCODER_PIN) == 1){
  //       steps++;
  //       while(digitalRead(ENCODER_PIN) == 1);
  //     }
  //   }

  //   temp = steps - lastSteps;
  //   lastSteps = steps;
  //   rps = temp/20;
  //   rpm = rps * 60;

  //   if(rpm != 0 && rps != 0){
  //     Serial.print("rps = ");
  //     Serial.print(rps);
  //     Serial.print(" | rpm = ");
  //     Serial.println(rpm);
  //   } else {
  //     Serial.println("SEI FERMO");
  //   }

  // } else {
  //   for(motState; motState >=0; motState--){
  //     analogWrite(TIP120_PIN, motState);
  //     analogWrite(LED_PIN, motState);
  //     delay(1);
  //   }
  // }

  // lastBtnState = btnState;

  //motor.ino lettura velocità con encoder in un secondo -------------------------------------------
  btnState = digitalRead(BTN_PIN);
  if (btnState == 1 && btnState != lastBtnState){
    canGo = !canGo;
  }

  if (canGo){
    pwm = analogRead(POT_PIN);
    motState = map(pwm, 0, 1023, 0, 255);
    analogWrite(TIP120_PIN, motState);
    analogWrite(LED_PIN, motState);

    steps = 0;
    startTime = millis();
    do {
      encoderState = digitalRead(ENCODER_PIN);
      if (encoderState == 1 && encoderState != lastEncoderState){
        steps++;
      }
      lastEncoderState = encoderState;
    } while (steps<20 && (millis()-startTime) < 2500);
    endTime = millis();

    temp = endTime - startTime;
    rps = 1000/temp;
    rpm = rps*60;

    if(rps<0.5){
      Serial.println("SEI FERMO");
    } else {
      Serial.print("rps: ");
      Serial.print(rps);
      Serial.print(" | rpm: ");
      Serial.println(rpm);
    }

  } else {
    for(motState; motState >=0; motState--){
      analogWrite(TIP120_PIN, motState);
      analogWrite(LED_PIN, motState);
      delay(1);
    }
  }

  lastBtnState = btnState;

}