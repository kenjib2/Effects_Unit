#include <Adafruit_GFX.h>
#include <ST7735_t3.h>
#include <SPI.h>
#include "TftGui.h"


Window::Window(ST7735_t3 &tft) 
  : tft(tft)
  , patchPanel(tft)
  , controlsPanel(tft)
{
}

void Window::initDisplay() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(FONT_SIZE);
}

void Window::createTestData() {
  Patch * patch = new Patch();
  patch->setPatchName("Dark Neutron Star");

  SubtractiveSynthEffect *effect0 = new SubtractiveSynthEffect();
  patch->setEffect(0, effect0);

  TheFullRackEffect *effect1 = new TheFullRackEffect();
  patch->setEffect(1, effect1);

  patchPanel.patch = patch;

  int selectedEffect = 0;
  patchPanel.selectedEffect = selectedEffect;
  controlsPanel.effect = patchPanel.patch->effects[selectedEffect];
}

void Window::render() {
  patchPanel.render(0, 0, 160, 64);
  controlsPanel.render(0, 64, 160, 64);
}

void Window::invalidate() {
  patchPanel.invalidate();
  controlsPanel.invalidate();
}

Patch * Window::getPatch() {
  return patchPanel.patch;
}

Effect * Window::getEffect(int effectNumber) {
  return patchPanel.patch->effects[effectNumber];
}


DisplayPanel::DisplayPanel(ST7735_t3 &tft)
: tft(tft) {
}

void DisplayPanel::invalidate() {
  needsRefresh = true;
}

void DisplayPanel::render(int xPos, int yPos, int width, int height) {
  if (needsRefresh) {
    doRender(xPos, yPos, width, height);
    needsRefresh = false;
  }
}


Effect * PatchPanel::getSelectedEffect() {
  return patch->effects[selectedEffect];
}

void PatchPanel::decrementSelect() {
  selection -= 1;
  if (selection < 0) {
    selection += NUM_EFFECTS + 5; // +5 To account for patch name, new, rename, save, and delete
  }
  invalidate();
}

void PatchPanel::incrementSelect() {
  selection = (selection + 1) % (NUM_EFFECTS + 5); // +5 to account for patch name, new, rename, save, and delete
  invalidate();
}

// returns true if you need to invalidate all
bool PatchPanel::select() {
  if (selection == 0) {
  } else if (selection <= NUM_EFFECTS) {
    selectedEffect = selection - 1; // -1 to account for patch name.
    invalidate();
    return true;
  } else if (selection == NUM_EFFECTS + 1) {
  } else if (selection == NUM_EFFECTS + 2) {
  } else if (selection == NUM_EFFECTS + 3) {
  } else if (selection == NUM_EFFECTS + 4) {
  }

  return false;
}

void PatchPanel::doRender(int xPos, int yPos, int width, int height) {
  // Background and Border
  tft.fillRect(xPos, yPos, width, height, COLOR_BACKGROUND);
  tft.drawRect(xPos, yPos, width, height, COLOR_BORDER);

  // Patch Name
  tft.setTextColor(COLOR_TEXT);
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN, yPos + DISPLAY_PANEL_MARGIN);
  tft.print("Patch:");
  if (selection == 0) {
    tft.setTextColor(COLOR_TEXT_SELECTED);
  }
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + 7 * FONT_WIDTH + SPACER_SIZE, yPos + DISPLAY_PANEL_MARGIN);
  tft.print(patch->patchName);

  // Effect Names
  char fxLabel[] = "FX 0:  ";
  for (int i = 0; i < NUM_EFFECTS; i++) {
    fxLabel[3] = '1' + i;
    if (selectedEffect == i) {
      fxLabel[6] = '>';
    } else {
      fxLabel[6] = ' ';
    }
    tft.setTextColor(COLOR_TEXT);
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN
        , yPos + DISPLAY_PANEL_MARGIN + SPACER_SIZE + (i + 1) * LINE_HEIGHT
        );
    tft.print(fxLabel);

    if (selection == i + 1) {
      tft.setTextColor(COLOR_TEXT_SELECTED);
    }
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + 7 * FONT_WIDTH + SPACER_SIZE
        , yPos + DISPLAY_PANEL_MARGIN + SPACER_SIZE + (i + 1) * LINE_HEIGHT
        );
    tft.print(patch->effects[i]->effectName);
  }

  // Options
  if (selection == NUM_EFFECTS + 1) {
    tft.setTextColor(COLOR_TEXT_SELECTED);
  } else {
    tft.setTextColor(COLOR_TEXT);
  }
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN
      , yPos + DISPLAY_PANEL_MARGIN + 2 * SPACER_SIZE + 3 * LINE_HEIGHT
      );
  tft.print("NEW");

  if (selection == NUM_EFFECTS + 2) {
    tft.setTextColor(COLOR_TEXT_SELECTED);
  } else {
    tft.setTextColor(COLOR_TEXT);
  }
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + FONT_WIDTH * 7
      , yPos + DISPLAY_PANEL_MARGIN + 2 * SPACER_SIZE + 3 * LINE_HEIGHT
      );
  tft.print("COPY");

  if (selection == NUM_EFFECTS + 3) {
    tft.setTextColor(COLOR_TEXT_SELECTED);
  } else {
    tft.setTextColor(COLOR_TEXT);
  }
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + FONT_WIDTH * 15
      , yPos + DISPLAY_PANEL_MARGIN + 2 * SPACER_SIZE + 3 * LINE_HEIGHT
      );
  tft.print("RENAME");

  if (selection == NUM_EFFECTS + 4) {
    tft.setTextColor(COLOR_TEXT_SELECTED);
  } else {
    tft.setTextColor(COLOR_TEXT);
  }
  tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + FONT_WIDTH * 25
      , yPos + DISPLAY_PANEL_MARGIN + 2 * SPACER_SIZE + 3 * LINE_HEIGHT
      );
  tft.print("SAVE");
}


void ControlsPanel::doRender(int xPos, int yPos, int width, int height) {
  // Background and Border
  tft.fillRect(xPos, yPos, width, height, COLOR_BACKGROUND);
  tft.drawRect(xPos, yPos, width, height, COLOR_BORDER);

  // Buttons labels
  tft.setTextColor(COLOR_TEXT);
  for (int i = 0; i < effect->numButtons; i++) {
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + i * FONT_WIDTH * (CTRL_LABEL_LENGTH + 2),
        yPos + DISPLAY_PANEL_MARGIN
        );
    tft.print(effect->buttonLabels[i]);
  }

  // Knob labels
  for (int i = 0; i < effect->numKnobs; i++) {
    int row = i / CTRL_PER_ROW;
    int column = i % CTRL_PER_ROW;
    
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + column * FONT_WIDTH * (CTRL_LABEL_LENGTH + 2),
        yPos + DISPLAY_PANEL_MARGIN + (row + 1) * LINE_HEIGHT + SPACER_SIZE
        );
    tft.print(effect->knobLabels[i]);
  }

  // Switch labels
  for (int i = 0; i < effect->numSwitches; i++) {
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + CTRL_PER_ROW * FONT_WIDTH * (CTRL_LABEL_LENGTH + 2) + SPACER_SIZE,
        yPos + DISPLAY_PANEL_MARGIN + SPACER_SIZE + i * 3 * LINE_HEIGHT
        );
    tft.print(effect->switchLabels[i]);
  }
}


void Window::scrollDown() {
  patchPanel.incrementSelect();
}

void Window::scrollUp() {
  patchPanel.decrementSelect();
}

void Window::select() {
  if (patchPanel.select()) {
    controlsPanel.effect = patchPanel.getSelectedEffect();
    invalidate();
  }
}
