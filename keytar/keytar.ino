// keytar.ino

#include "Button.h"

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

int lastPot1 = -1;

void didPressButton(Button btn)
{
	if (btn.id >= 8) {
		sendPot[btn.id-8] = btn.isPressed();
		return;
	}

	String msg = String("b " + String(btn.id) + " " + String((int)btn.isPressed()));
	Serial.println(msg);
}

void didFlipSwitch(Button swch)
{
	bool pressed = swch.isPressed();
	if (swch.id == 0)
		pressed = !pressed;
	String msg = String("s " + String(swch.id) + " " + String((int)pressed));
	Serial.println(msg);
}

void setup()
{
	Serial.begin(57600);
	delay(1000);
	for (int i=0; i<btnCount; ++i) {
	    buttons[i].setCallback(&didPressButton);
	}
	for (int i=0; i<switchCount; ++i) {
	    switches[i].setCallback(&didFlipSwitch);
	}
}

void writePot(int num, int value)
{
	if (num == 0 && !sendPot[num]) //handle softpot "trigger"
		return;

	String msg = String("p " + String(num) + " " + String(value));
	Serial.println(msg);
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
	if (lastPot1 != newPot1) {
		writePot(1, (int)((newPot1-530.0)*(1023.0/493.0)));
		lastPot1 = newPot1;
	}
}
