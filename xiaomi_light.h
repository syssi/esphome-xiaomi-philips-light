#pragma once

#include "esphome.h"

// https://github.com/Sergey-SRG/ESPHome-Xiaomi-Philips-light
class XiaomiLight : public Component, public LightOutput {
 public:
  XiaomiLight(FloatOutput *cold_white, FloatOutput *brightness) {
    cold_white_ = cold_white;
    brightness_ = brightness;
    color_temperature_cw_ = 175;
    color_temperature_ww_ = 333;
  }
  LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS, light::ColorMode::COLOR_TEMPERATURE});
    traits.set_min_mireds(this->color_temperature_cw_);
    traits.set_max_mireds(this->color_temperature_ww_);
    return traits;
  }

  void write_state(LightState *state) override {
    float brightness;
    const float color_temp =
        clamp(state->current_values.get_color_temperature(), this->color_temperature_cw_, this->color_temperature_ww_);
    const float cw_fraction =
        1.0f - (color_temp - color_temperature_cw_) / (color_temperature_ww_ - color_temperature_cw_);
    state->current_values_as_brightness(&brightness);

    ESP_LOGD("custom", "Brightness: %f", brightness);
    ESP_LOGD("custom", "Cold white fraction: %f", cw_fraction);
    this->cold_white_->set_level(cw_fraction > brightness ? brightness : cw_fraction);
    if (brightness == 0) {
      this->brightness_->set_level(0);
    } else {
      this->brightness_->set_level(this->map(brightness, 0.0f, 100.0f, 0.06f, 100.0f));
    }
  }

  float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
  }

 protected:
  FloatOutput *cold_white_;
  FloatOutput *brightness_;
  float color_temperature_cw_;
  float color_temperature_ww_;
};
