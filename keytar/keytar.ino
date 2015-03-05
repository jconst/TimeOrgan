// buttonstest.ino

#include "Button.h"

const int softPot1 = 2;

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

void didPressButton(Button btn) {
	Serial.print("b ");
	Serial.print(btn.id);
	Serial.print(" ");
	Serial.println((int)btn.isPressed());
}

void setup()
{
	Serial.begin(57600);
	for (int i=0; i<btnCount; ++i) {
	    buttons[i].setCallback(&didPressButton);
	}
}

void writePot(int num, int value)
{
	Serial.print("p ");
	Serial.print(num);
	Serial.print(" ");
	Serial.println(value);
}

void loop()
{
	for (int i=0; i<btnCount; ++i) {
		buttons[i].updateState();
	}
	writePot(0, analogRead(softPot1));
	//REMOVE LATER:
	delay(1);
}
