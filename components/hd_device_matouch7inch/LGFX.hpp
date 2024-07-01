#pragma once

#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

#define SPI_FREQUENCY 15000000
#define TFT_WIDTH 1024
#define TFT_HEIGHT 600
#define TFT_BCKL 39
#define TFT_CS 10
#define TFT_SCLK 12
#define TFT_MOSI 11
#define TFT_DE 40
#define TFT_VSYNC 41
#define TFT_HSYNC 39
#define TFT_PCLK 42
#define TFT_D0 8   //  B0
#define TFT_D1 3   //  B1
#define TFT_D2 46  //  B2
#define TFT_D3 9   //  B3
#define TFT_D4 1   //  B4
#define TFT_D5 5   //  G0
#define TFT_D6 6   //  G1
#define TFT_D7 7   //  G2
#define TFT_D8 15  //  G3
#define TFT_D9 16  //  G4
#define TFT_D10 4  //  G5
#define TFT_D11 45 //  R0
#define TFT_D12 48 //  R1
#define TFT_D13 47 //  R2
#define TFT_D14 21 //  R3
#define TFT_D15 14 //  R4
#define BACKLIGHT_FREQUENCY 1000
#define I2C_TOUCH_FREQUENCY 400000
#define TOUCH_SDA 17
#define TOUCH_SCL 18
#define TOUCH_IRQ 2
#define TOUCH_RST 3

namespace esphome {
namespace hd_device {

class LGFX : public lgfx::LGFX_Device
{
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_GC9503 _panel_instance;
  lgfx::Touch_FT5x06 _touch_instance;
  lgfx::Light_PWM _light_instance;

  LGFX(void)
  {
    {
      auto cfg = _panel_instance.config();

      cfg.memory_width = TFT_WIDTH;
      cfg.memory_height = TFT_HEIGHT;
      cfg.panel_width = TFT_WIDTH;
      cfg.panel_height = TFT_HEIGHT;

      cfg.offset_x = 0;
      cfg.offset_y = 0;

      cfg.pin_rst = TFT_VSYNC;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _panel_instance.config_detail();

      cfg.pin_cs = 10;
      cfg.pin_sclk = 12;
      cfg.pin_mosi = 11;

      _panel_instance.config_detail(cfg);
    }

    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      cfg.pin_d0 = TFT_D0;   // B0
      cfg.pin_d1 = TFT_D1;   // B1
      cfg.pin_d2 = TFT_D2;   // B2
      cfg.pin_d3 = TFT_D3;   // B3
      cfg.pin_d4 = TFT_D4;   // B4
      cfg.pin_d5 = TFT_D5;   // G0
      cfg.pin_d6 = TFT_D6;   // G1
      cfg.pin_d7 = TFT_D7;   // G2
      cfg.pin_d8 = TFT_D8;   // G3
      cfg.pin_d9 = TFT_D9;   // G4
      cfg.pin_d10 = TFT_D10; // G5
      cfg.pin_d11 = TFT_D11; // R0
      cfg.pin_d12 = TFT_D12; // R1
      cfg.pin_d13 = TFT_D13; // R2
      cfg.pin_d14 = TFT_D14; // R3
      cfg.pin_d15 = TFT_D15; // R4

      cfg.pin_henable = TFT_DE;
      cfg.pin_vsync = TFT_VSYNC;
      cfg.pin_hsync = TFT_HSYNC;
      cfg.pin_pclk = TFT_PCLK;
      cfg.freq_write = 16000000;

      cfg.hsync_polarity = 1;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch = 128;
      cfg.vsync_polarity = 1;
      cfg.vsync_front_porch = 13;
      cfg.vsync_pulse_width = 3;
      cfg.vsync_back_porch = 45;
      cfg.pclk_idle_high = 0;
      cfg.de_idle_high = 0;
      cfg.pclk_active_neg = 1;

      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = TFT_WIDTH - 1;
      cfg.y_min = 0;
      cfg.y_max = TFT_HEIGHT - 1;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;

      // cfg.i2c_port = I2C_NUM_1;

      cfg.pin_int = TOUCH_IRQ;
      cfg.pin_sda = TOUCH_SDA;
      cfg.pin_scl = TOUCH_SCL;
      cfg.pin_rst = TOUCH_RST;

      cfg.freq = I2C_TOUCH_FREQUENCY;
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = TFT_BCKL;
      _light_instance.config(cfg);
    }
    _panel_instance.light(&_light_instance);

    setPanel(&_panel_instance);
  }
};

}  // namespace hd_device
}  // namespace esphome