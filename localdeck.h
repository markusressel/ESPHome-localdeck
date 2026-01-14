#include "esphome.h"

// This array will hold the 24 light partitions
// We use 25 slots so that index 1 matches button 01
light::AddressableLightState* my_keypad_lights[24];

// This function sets up the keypad light array with the provided light states
// Parameters:
// - l01 to l24: Pointers to AddressableLightState objects for each button
void setup_keypad_array(
    esphome::light::AddressableLightState* l01, esphome::light::AddressableLightState* l02,
    esphome::light::AddressableLightState* l03, esphome::light::AddressableLightState* l04,
    esphome::light::AddressableLightState* l05, esphome::light::AddressableLightState* l06,
    esphome::light::AddressableLightState* l07, esphome::light::AddressableLightState* l08,
    esphome::light::AddressableLightState* l09, esphome::light::AddressableLightState* l10,
    esphome::light::AddressableLightState* l11, esphome::light::AddressableLightState* l12,
    esphome::light::AddressableLightState* l13, esphome::light::AddressableLightState* l14,
    esphome::light::AddressableLightState* l15, esphome::light::AddressableLightState* l16,
    esphome::light::AddressableLightState* l17, esphome::light::AddressableLightState* l18,
    esphome::light::AddressableLightState* l19, esphome::light::AddressableLightState* l20,
    esphome::light::AddressableLightState* l21, esphome::light::AddressableLightState* l22,
    esphome::light::AddressableLightState* l23, esphome::light::AddressableLightState* l24
) {
    my_keypad_lights[0] = l01;   my_keypad_lights[1] = l02;   my_keypad_lights[2] = l03;   my_keypad_lights[3] = l04;
    my_keypad_lights[4] = l05;   my_keypad_lights[5] = l06;   my_keypad_lights[6] = l07;   my_keypad_lights[7] = l08;
    my_keypad_lights[8] = l09;   my_keypad_lights[9] = l10;   my_keypad_lights[10] = l11;  my_keypad_lights[11] = l12;
    my_keypad_lights[12] = l13;  my_keypad_lights[13] = l14;  my_keypad_lights[14] = l15;  my_keypad_lights[15] = l16;
    my_keypad_lights[16] = l17;  my_keypad_lights[17] = l18;  my_keypad_lights[18] = l19;  my_keypad_lights[19] = l20;
    my_keypad_lights[20] = l21;  my_keypad_lights[21] = l22;  my_keypad_lights[22] = l23;  my_keypad_lights[23] = l24;
}

// Array to hold the current run IDs for each button (0-23)
int keypad_run_ids[24] = {0};

// Increments the ID for a specific button and returns the new value
// Parameters:
// - index: Button index (0-23)
// Returns:
// - int: The new run ID
int start_new_blip(int index) {
    if (index < 0 || index > 23) return -1;
    return ++keypad_run_ids[index];
}

// Returns the latest run ID for a specific button index
// Parameters:
// - index: Button index (0-23)
// Returns:
// - int: The latest run ID
int get_latest_id(int index) {
    return keypad_run_ids[index];
}

// This function triggers the blip effect for a specific button index
// It calls the blip_light script with the button index and a new run_id
// Parameters:
// - index: Button index (0-23)
void trigger_blip(int index) {
    // We call the script by ID and pass the generated run_id automatically
    id(blip_light).execute(index, start_new_blip(index));
}

// This function calculates the blip color for a given button index and iteration.
// The blip effect is a colored flash that overlays the current color of the button's light.
// The animation targets 25ms per iteration (40fps).
// Parameters:
// - index: Button index (0-23)
// - iteration: Current iteration of the animation (0 to duration/25), or -1 for cleanup
// - duration: Total duration of the blip animation in milliseconds
// - blip_brightness: Maximum brightness of the blip effect (0.0 to 1.0)
// - channel: Color channel to calculate (0=R, 1=G, 2=B)
// Returns:
// - float: The calculated color level for the specified channel (0.0 to 1.0)
float get_blip_color(
  int index,
  int iteration,
  float duration,
  float blip_brightness,
  int channel
) {
    if (index < 0 || index > 23) return 0.0f;

    auto* light_obj = my_keypad_lights[index];

    // 1. Get the current physical color level (Color * Brightness)
    float base_level = 0.0f;
    if (light_obj->remote_values.is_on()) {
        float brightness = light_obj->remote_values.get_brightness();
        if (channel == 0)      base_level = light_obj->remote_values.get_red() * brightness;
        else if (channel == 1) base_level = light_obj->remote_values.get_green() * brightness;
        else if (channel == 2) base_level = light_obj->remote_values.get_blue() * brightness;
    }

    // If iteration is -1, it's a cleanup call - return the calculated base level
    if (iteration < 0) return base_level;

    // 2. Calculate Animation
    float progress = (float)iteration / (duration / 25.0f);
    float intensity = blip_brightness * (1.0f - progress);

    // 3. Add white blip to the physical base level
    return esphome::clamp(base_level + intensity, 0.0f, 1.0f);
}