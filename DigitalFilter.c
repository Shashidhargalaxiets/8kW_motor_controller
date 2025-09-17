#include "DigitalFilter.h"

float low_pass_filter(float current_input, float previous_output, float alpha) {
    return (alpha * current_input) + ((1.0f - alpha) * previous_output);
}