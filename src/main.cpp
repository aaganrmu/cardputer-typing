#include "M5Cardputer.h"
#include "M5GFX.h"

String text = "";
int CHAR_WIDTH = 12;
int CHAR_HEIGHT = 20;

// void draw_function(LovyanGFX* gfx, String text) {
//   int x = rand() % gfx->width();
//   int y = rand() % gfx->height();
//   int colour = rand() % 0xFFFF;
//   gfx->drawString(text, x, y);
// }


M5Canvas canvas(&M5Cardputer.Display);

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg,true);
  int textsize = M5Cardputer.Display.height() / 60;
  if (textsize == 0) {
    textsize = 1;
  }
  M5Cardputer.Display.setTextSize(textsize);
}

void loop() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      bool refresh = false;
      bool draw = false;
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      for (auto c : status.word) {
        text += c;
        draw = true;
      }
      if (status.del) {
        text.remove(text.length() - 1);
        refresh = true;
      }
      if (status.enter) {
        text += "\n";
      }
      
      if (refresh) {
        M5Cardputer.Display.fillScreen(0x000000);
        draw = true;
      }
      if (draw) {
        int x = 0;
        int y = 0;
        for (int i = 0; i < text.length(); i++) {
          char c = text.charAt(i);
          if (c == 0x0a) {
            x = 0;
            y += CHAR_HEIGHT;
          } else {
            M5Cardputer.Display.drawChar(c, x, y);
            x += CHAR_WIDTH;
          }
        }
      }
      // M5Cardputer.Display.drawString(text, 0, 0);
      // draw_function(&M5Cardputer.Display, text);
    }
  }
}