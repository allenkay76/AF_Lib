#ifndef AF_INPUT_H
#define AF_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif
#define AF_INPUT_KEYS_MAPPED 4

typedef struct {
	int code;
	int pressed;
} AF_Key;

typedef struct {
    // input buffer que
    AF_Key keys[AF_INPUT_KEYS_MAPPED];

    // Mouse
    int mouseDown;
    float mouseX;
    float mouseY;

} AF_Input;

#ifdef __cplusplus
}
#endif

#endif  // AF_INPUT_H
