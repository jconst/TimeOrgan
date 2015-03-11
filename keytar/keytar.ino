// keytar.ino

#include "Button.h"
#include "NewhavenLCDSerial.h"

const int rotaryA = 18;
const int rotaryB = 19;
int stateA=LOW;
int stateB=LOW;

const int pot0 = 0;
const int pot1 = 2; //using 100k pot w/ 100k voltage divider

const int btnCount = 9;
Button buttons[btnCount] = {
    Button(0, 5),
    Button(1, 6),
    Button(2, 7),
    Button(3, 8),
    Button(4, 9),
    Button(5, 10),
    Button(6, 11),
    Button(7, 12),
    Button(8, 13)
};

const int switchCount = 2;
Button switches[switchCount] = {
    Button(0, 2),
    Button(1, 3)
};

bool sendPot[2] = {false, false};

int lastPot1 = -10;

NewhavenLCDSerial lcd(17);
const int lcdRight = 16;
String posMsg;
String sizeMsg;
String reverbMsg;
String buttonMsg;
bool lcdDirty = false;

void didPressButton(Button btn)
{
    if (btn.id >= 8) {
        sendPot[btn.id-8] = btn.isPressed();
    }

    String msg = String("b " + String(btn.id) + " " + String((int)btn.isPressed()));
    Serial.println(msg);
}

void didFlipSwitch(Button swch)
{
    bool pressed = swch.isPressed();
    if (swch.id == 0)
        pressed = !pressed;
    writeSwitch(swch, pressed);
}

void writeSwitch(Button swch, bool pressed)
{
    String msg = String("s " + String(swch.id) + " " + String((int)pressed));
    Serial.println(msg);
}

void setup()
{
    Serial.begin(57600);
    delay(1000);

    pinMode(rotaryA, INPUT_PULLUP); //set encoder pins to inputs with pullups
    pinMode(rotaryB, INPUT_PULLUP); 

    for (int i=0; i<btnCount; ++i) {
        buttons[i].setCallback(&didPressButton);
    }
    for (int i=0; i<switchCount; ++i) {
        switches[i].setCallback(&didFlipSwitch);
        writeSwitch(switches[i], false);
    }

    displayMessage("test", 0, false);
}

void writePot(int num, int value)
{
    if (num == 0 && !sendPot[num]) //handle softpot "trigger"
        return;

    String msg = String("p " + String(num) + " " + String(value));
    Serial.println(msg);
}
 
void writeRotary(int num, bool cw)
{
    int dir = cw ? 1 : -1;
    String msg = String("r " + String(num) + " " + String(dir));
    Serial.println(msg);
}

void encoderStep()
{
    int readingA = digitalRead(rotaryA);
    int readingB = digitalRead(rotaryB);
    if (stateA!=readingA) { //state has changed->tick
        writeRotary(0, readingA==readingB);
    }
    if (stateB!=readingB) { //state has changed->tick
        writeRotary(0, readingA!=readingB);
    }
    stateA = readingA;   //update state to current reading
    stateB = readingB;
}

void displayMessage(String msg, int row, bool rightAligned)
{
    lcd.setCursor(row, rightAligned ? (lcdRight-msg.length()) : 0);
    for (int i=0; i<msg.length(); i++){
        lcd.write(msg[i]);
    }
}

void updateLCD()
{
    if (!lcdDirty)
        return;

    lcd.clear();
    displayMessage(posMsg, 0, true);
    displayMessage(sizeMsg, 1, true);
    displayMessage(reverbMsg, 1, false);
    displayMessage(buttonMsg, 0, false);
    lcdDirty = false;
}

void parseSerial(String msg)
{
    if (msg.length() == 0)
        return;

    if (msg[0] == 'p') {
        posMsg = msg.substring(2) + String("p");
    }
    else if (msg[0] == 's') {
        sizeMsg = msg.substring(2) + String("s");
    }
    else if (msg[0] == 'r') {
        reverbMsg = String("r") + msg.substring(2);
    }
    else if (msg[0] == 'b') {
        buttonMsg = String("b") + msg.substring(2);
    }
}

void lcdStep()
{
    //for loop to avoid staying in this fn for too long
    for (int i=0; i<10 && Serial.available(); ++i) {
        char msg[30] = {0};
        if (!Serial.readBytesUntil('\n', msg, 29)) {
            break;
        }
        lcdDirty = true;
        parseSerial(String(msg));
    }
    updateLCD();
}

void loop()
{
    for (int i=0; i<btnCount; ++i) {
        buttons[i].updateState();
    }
    for (int i=0; i<switchCount; ++i) {
        switches[i].updateState();
    }
    writePot(0, 1023 - analogRead(pot0));

    int newPot1 = analogRead(pot1);
    if (abs(lastPot1 - newPot1) > 2) {
        // int scaled = (newPot1-530.0)*(1023.0/493.0);
        int scaled = newPot1;
        writePot(1, scaled);
        lastPot1 = newPot1;
    }

    encoderStep();
    lcdStep();
}
