#ifndef AF_INPUT_H
#define AF_INPUT_H

typedef struct {

    // input buffer que
    int lastKeyCodePressed;

    // Mouse
    int mouseDown;
    float mouseX;
    float mouseY;

} AF_Input;

// poll the platform input and fill the input buffer with registered commands


#endif  // AF_INPUT_H
