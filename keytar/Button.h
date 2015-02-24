#define DEBOUNCE_TIME 1

class Button
{
public:
    int id;
    int pin;
    enum btnState {ON, OFF, DEBOUNCE};
    btnState state;

    Button(int i, int p) : id(i), pin(p) {
        pinMode(p, INPUT_PULLUP);
    }
    void setCallback(void (*newCallback)(Button)) {
        changeCallback = newCallback;
    }
    void updateState();
    bool isPressed();
private:
    void setState(btnState newState);
    void (*changeCallback)(Button btn);
    unsigned long debounceStart;
};

void Button::updateState()
{
    int reading = !digitalRead(pin);
    switch (state) {
        case ON:
            if (!reading) {
                setState(OFF);
            }
            break;
        case OFF:
            if (reading) {
                setState(ON);
            }
            break;
        case DEBOUNCE:
            if (!reading) {
                setState(OFF);
            } else if ((millis() - DEBOUNCE_TIME) > debounceStart) {
                setState(ON);
            }
            break;
    }
}

void Button::setState(btnState newState)
{
    state = newState;
    if (newState == DEBOUNCE) {
        debounceStart = millis();
    } else {
        changeCallback(*this);
    }
}

bool Button::isPressed()
{
    return state == ON;
}
