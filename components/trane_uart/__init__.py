import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import uart
from esphome.const import CONF_ID

CONF_TX_ENABLE_PIN = "tx_enable_pin"

trane_uart_ns = cg.esphome_ns.namespace("trane_uart")
TraneUARTTestComponent = trane_uart_ns.class_("TraneUARTTestComponent", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(TraneUARTTestComponent),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_TX_ENABLE_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    uart_var = await cg.get_variable(config["uart_id"])
    pin = await cg.gpio_pin_expression(config[CONF_TX_ENABLE_PIN])
    var = cg.new_Pvariable(config[CONF_ID], uart_var, pin)
    await cg.register_component(var, config)
