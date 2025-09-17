
/**
 * @brief Applies a first-order low-pass filter
 * 
 * @param current_input   New input sample (x[n])
 * @param previous_output Previous output sample (y[n-1])
 * @param alpha           Filter coefficient (0 < alpha <= 1)
 * 
 * @return Filtered output (y[n])
 */
float low_pass_filter(float current_input, float previous_output, float alpha);
