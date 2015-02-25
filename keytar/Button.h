#define DEBOUNCE_TIME 5
#define SHOULD_DEBOUNCE true

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
    bool shouldNotify(btnState oldState, btnState newState);
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
                setState(SHOULD_DEBOUNCE ? DEBOUNCE : ON);
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
    btnState oldState = state;
    state = newState;
    if (newState == DEBOUNCE) {
        debounceStart = millis();
    } else if (shouldNotify(oldState, newState)) {
        changeCallback(*this);
    }
}

bool Button::isPressed()
{
    return state == ON;
}

bool Button::shouldNotify(btnState oldState, btnState newState)
{
    return (newState == OFF && oldState == ON) ||
           (newState == ON && oldState != ON);
}
