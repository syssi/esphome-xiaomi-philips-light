#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace xiaomi_light {

class XiaomiLight : public Component, public light::LightOutput {
 public:
  XiaomiLight() {
    color_temperature_cw_ = 175;
    color_temperature_ww_ = 333;
  }

  void set_outputs(output::FloatOutput *cold_white, output::FloatOutput *brightness) {
    cold_white_ = cold_white;
    brightness_ = brightness;
  }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::COLOR_TEMPERATURE});
    traits.set_min_mireds(153.0f);  // <-- for Home Assistant
    traits.set_max_mireds(500.0f);  // <-- for Home Assistant
    return traits;
  }


  void write_state(light::LightState *state) override {
    float brightness;
    const float input_temp = state->current_values.get_color_temperature();
    const float mapped_temp = this->map(input_temp, 153.0f, 500.0f, this->color_temperature_cw_, this->color_temperature_ww_);
    const float color_temp = clamp(mapped_temp, this->color_temperature_cw_, this->color_temperature_ww_);
    const float cw_fraction =
        1.0f - (color_temp - color_temperature_cw_) / (color_temperature_ww_ - color_temperature_cw_);
    state->current_values_as_brightness(&brightness);

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
  output::FloatOutput *cold_white_;
  output::FloatOutput *brightness_;
  float color_temperature_cw_;
  float color_temperature_ww_;
};

}  // namespace xiaomi_light
}  // namespace esphome
