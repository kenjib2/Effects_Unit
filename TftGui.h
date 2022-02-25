#include <string>
#include <vector>
//#include <SPI.h>
#include <ST7735_t3.h>
#include "Patch.h"
#include "src/patch/EffectSubclasses.h"


const int FONT_SIZE = 1;
const int FONT_WIDTH = 5;
const int FONT_HEIGHT = 8;
const int LINE_HEIGHT = 10;
const int SPACER_SIZE = 8;
const int DISPLAY_PANEL_MARGIN = 4;
const int COLOR_BACKGROUND = 0x0801;
const int COLOR_BORDER = 0x8841;
const int COLOR_TEXT = 0xA51F; // 0x7BFF;
const int SELECTED_TEXT_RED = 255;
const int SELECTED_TEXT_GREEN = 255;
const int SELECTED_TEXT_BLUE = 255;
const int COLOR_TEXT_SELECTED = 0xFFFF;


typedef enum InputState {
  EFFECT_CONTROL
  , EFFECT_SELECT
  , PATCH_SELECT
} InputState;


class DisplayPanel {
  private:
    bool needsRefresh;

  protected:
    ST7735_t3 &tft;

  public:
    DisplayPanel(ST7735_t3 &tft);
    void invalidate();
    void render(int xPos, int yPos, int width, int height);
    virtual void doRender(int xPos, int yPos, int width, int height);
};


class EffectSelectPanel: public DisplayPanel {
  public:
    using DisplayPanel::DisplayPanel;

    int slot = 0;
    int selection = 0;
    std::vector<std::string> effectVector;

    void decrementSelect();
    void incrementSelect();
    void doRender(int xPos, int yPos, int width, int height) override;
};


class PatchPanel: public DisplayPanel {
  public:
    using DisplayPanel::DisplayPanel;

    Patch *patch;
    int selectedEffect = 0;
    int selection = 0;

    Effect *getSelectedEffect();
    void decrementSelect();
    void incrementSelect();
    void doRender(int xPos, int yPos, int width, int height) override;
};


class ControlsPanel: public DisplayPanel {
  public:
    using DisplayPanel::DisplayPanel;
    Effect *effect;

    void doRender(int xPos, int yPos, int width, int height) override;
};


class Window {
  private:
    ST7735_t3 &tft;
    InputState inputState;
    PatchPanel patchPanel;
    ControlsPanel controlsPanel;
    EffectSelectPanel effectSelectPanel;

  public:
    Window(ST7735_t3 &tft);

    void initDisplay();
    void createTestData();
    void render();
    void invalidate();
    void scrollDown();
    void scrollUp();
    void select();
    Patch * getPatch();
    Effect * getEffect(int effectNumber);
    
};
