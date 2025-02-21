import esphome.codegen as cg
from esphome.components import light
import esphome.config_validation as cv

xiaomi_light_ns = cg.esphome_ns.namespace("xiaomi_light")
XiaomiLight = xiaomi_light_ns.class_("XiaomiLight", cg.Component, light.LightOutput)

CONFIG_SCHEMA = cv.Schema({})
