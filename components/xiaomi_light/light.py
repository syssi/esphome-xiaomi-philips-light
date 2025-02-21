import esphome.codegen as cg
from esphome.components import light, output
import esphome.config_validation as cv
from esphome.const import CONF_BRIGHTNESS, CONF_COLD_WHITE, CONF_OUTPUT_ID

from . import XiaomiLight

DEPENDENCIES = ["output"]

CONFIG_SCHEMA = light.RGB_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(XiaomiLight),
        cv.Required(CONF_COLD_WHITE): cv.use_id(output.FloatOutput),
        cv.Required(CONF_BRIGHTNESS): cv.use_id(output.FloatOutput),
    }
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    yield cg.register_component(var, config)
    yield light.register_light(var, config)

    cold_white = yield cg.get_variable(config[CONF_COLD_WHITE])
    brightness = yield cg.get_variable(config[CONF_BRIGHTNESS])
    cg.add(var.set_outputs(cold_white, brightness))
