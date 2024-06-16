#ifndef AF_INPUT_H
#define AF_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // input buffer que
    int lastKeyCodePressed;

    // Mouse
    int mouseDown;
    float mouseX;
    float mouseY;

} AF_Input;

#ifdef __cplusplus
}
#endif

#endif  // AF_INPUT_H
