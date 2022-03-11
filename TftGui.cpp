#include <Adafruit_GFX.h>
#include <ST7735_t3.h>
#include <SPI.h>
#include "TftGui.h"
#include "EffectFactory.h"


// ---------------------------------- Window ----------------------------------

Window::Window(ST7735_t3 &tft) 
  : tft(tft)
  , patchPanel(tft)
  , controlsPanel(tft)
  , effectSelectPanel(tft)
  , textInputPanel(tft)
{
}

void Window::initDisplay() {
  inputState = PATCH_CONTROL;
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(FONT_SIZE);
}

void Window::createTestData() {
  Patch * patch = new Patch();
  patch->setPatchName("Dark Neutron Star");

//  patch->setEffect(0, "Bypass");
//  patch->setEffect(0, "Chorus");
//  patch->setEffect(0, "Cosmosis");
//  patch->setEffect(0, "Modulator");
  patch->setEffect(0, "Subtractive Synth");

//  patch->setEffect(1, "Chorus");
//  patch->setEffect(1, "Cosmosis");
  patch->setEffect(1, "Lost In Space");
//  patch->setEffect(1, "Modulator");
//  patch->setEffect(1, "Repeater");
//  patch->setEffect(1, "Reverb");
//  patch->setEffect(1, "Rhythmic Delay");
//  patch->setEffect(1, "Standard FX Chain");
//  patch->setEffect(1, "Temporal Collapse");
//   patch->setEffect(1, "Test");

  patchPanel.patch = patch;

  int selectedEffect = 0;
  patchPanel.selectedEffect = selectedEffect;
  controlsPanel.effect = patchPanel.patch->effects[selectedEffect];
}

void Window::render() {
  patchPanel.render(0, 0, 160, 64);
  controlsPanel.render(0, 64, 160, 64);
  if (inputState == EFFECT_SELECT) {
    effectSelectPanel.render(20, 10, 120, 108);
  } else if (inputState == RENAME) {
    textInputPanel.render(20, 10, 120, 35);
  }
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


void Window::scrollDown() {
  switch (inputState) {
    case PATCH_CONTROL:
      patchPanel.incrementSelect();
      if (patchPanel.selection > 0 && patchPanel.selection <= NUM_EFFECTS) {
        patchPanel.selectedEffect = patchPanel.selection - 1;
        controlsPanel.effect = patchPanel.getSelectedEffect();
        controlsPanel.invalidate();
      }
      break;
    case EFFECT_SELECT:
      effectSelectPanel.incrementSelect();
      break;
    case PATCH_SELECT:
      break;
    case RENAME:
      textInputPanel.incrementSelect();
      break;
  }
}


void Window::scrollUp() {
  switch (inputState) {
    case PATCH_CONTROL:
      patchPanel.decrementSelect();
      if (patchPanel.selection > 0 && patchPanel.selection <= NUM_EFFECTS) {
        patchPanel.selectedEffect = patchPanel.selection - 1;
        controlsPanel.effect = patchPanel.getSelectedEffect();
        controlsPanel.invalidate();
      }
      break;
    case EFFECT_SELECT:
      effectSelectPanel.decrementSelect();
      break;
    case PATCH_SELECT:
      break;
    case RENAME:
      textInputPanel.decrementSelect();
      break;
  }
}


void Window::select() {
  switch (inputState) {

    case PATCH_CONTROL:
      if (patchPanel.selection == 0) {
        // Change the patch
        
      } else if (patchPanel.selection <= NUM_EFFECTS) {
        // Change the effect
        patchPanel.selectedEffect = patchPanel.selection - 1; // -1 to account for patch name.
        effectSelectPanel.slot = patchPanel.selectedEffect;
        if (effectSelectPanel.slot == 0) {
          effectSelectPanel.effectVector = EffectFactory::getSlot1EffectList();
        } else {
          effectSelectPanel.effectVector = EffectFactory::getSlot2EffectList();
        }
        effectSelectPanel.selection = 0;
        effectSelectPanel.invalidate();
        inputState = EFFECT_SELECT;

      } else if (patchPanel.selection == NUM_EFFECTS + 1) {
        // New
        
      } else if (patchPanel.selection == NUM_EFFECTS + 2) {
        // Copy
        
      } else if (patchPanel.selection == NUM_EFFECTS + 3) {
        // Rename
        textInputPanel.textSize = MAX_PATCH_NAME_LENGTH;
        if (textInputPanel.textVal) {
          delete textInputPanel.textVal;
        }
        textInputPanel.textVal = (char *)malloc((MAX_PATCH_NAME_LENGTH + 1) * sizeof(char));
        strcpy(textInputPanel.textVal, patchPanel.patch->patchName);
        memset(textInputPanel.textVal + (strlen(patchPanel.patch->patchName) * sizeof(char)), 32, (MAX_PATCH_NAME_LENGTH - strlen(patchPanel.patch->patchName)) * sizeof(char));
        textInputPanel.textVal[MAX_PATCH_NAME_LENGTH] = 0;
        textInputPanel.invalidate();
        inputState = RENAME;

      } else if (patchPanel.selection == NUM_EFFECTS + 4) {
        // Save
      }
      break;

    case EFFECT_SELECT:
      patchPanel.patch->setEffect(effectSelectPanel.slot, effectSelectPanel.effectVector[effectSelectPanel.selection]);
      controlsPanel.effect = patchPanel.patch->effects[effectSelectPanel.slot];
      inputState = PATCH_CONTROL;
      invalidate();
      break;

    case PATCH_SELECT:
      invalidate();
      break;

    case RENAME:
      if (textInputPanel.selection == 0) {
        // Cancel
        inputState = PATCH_CONTROL;
        invalidate();
      } else if (textInputPanel.selection == 1) {
        // Okay
        for (int i = MAX_PATCH_NAME_LENGTH - 1; textInputPanel.textVal[i] == ' ' && i > 0; i--) {
          textInputPanel.textVal[i] = 0;
        }
        strcpy(patchPanel.patch->patchName, textInputPanel.textVal);
        inputState = PATCH_CONTROL;
        invalidate();
      } else {
        // Letter
        textInputPanel.letterSelected = !textInputPanel.letterSelected;
      }
      break;

  }
}


// ---------------------------------- DisplayPanel ----------------------------------

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


// ---------------------------------- PatchPanel ----------------------------------

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


// ---------------------------------- ControlsPanel ----------------------------------

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


// ---------------------------------- EffectSelectPanel ----------------------------------

void EffectSelectPanel::decrementSelect() {
  selection -= 1;
  if (selection < 0) {
    selection += effectVector.size();
  }
  invalidate();
}

void EffectSelectPanel::incrementSelect() {
  selection = (selection + 1) % (effectVector.size());
  invalidate();
}

void EffectSelectPanel::doRender(int xPos, int yPos, int width, int height) {
  // Background and Border
  tft.fillRect(xPos, yPos, width, height, COLOR_BACKGROUND);
  tft.drawRect(xPos, yPos, width, height, COLOR_BORDER);

  // Effect List
  int index = 0;
  for (auto & it : effectVector) {
    tft.setTextColor(COLOR_TEXT);
    if (selection == index) {
      tft.setTextColor(COLOR_TEXT_SELECTED);
    }
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN, yPos + DISPLAY_PANEL_MARGIN + index * LINE_HEIGHT);
    tft.print(it.c_str());
    index++;
  }
}


// ---------------------------------- TextInputPanel ----------------------------------

void TextInputPanel::decrementSelect() {
  if (letterSelected) {
    textVal[selection - 2] = prevChar(textVal[selection - 2]);
  } else {
    selection -= 1;
    if (selection < 0) {
      selection += MAX_PATCH_NAME_LENGTH + 2;
    }
  }
  invalidate();
}


void TextInputPanel::incrementSelect() {
  if (letterSelected) {
    textVal[selection - 2] = nextChar(textVal[selection - 2]);
  } else {
    selection = (selection + 1) % (MAX_PATCH_NAME_LENGTH + 2);
  }
  invalidate();
}


void TextInputPanel::doRender(int xPos, int yPos, int width, int height) {
  // Background and Border
  tft.fillRect(xPos, yPos, width, height, COLOR_BACKGROUND);
  tft.drawRect(xPos, yPos, width, height, COLOR_BORDER);

  for (int i = 0; i < MAX_PATCH_NAME_LENGTH; i++) {
    if (selection == i + 2) {
      tft.setTextColor(COLOR_TEXT_SELECTED, COLOR_TEXT_SELECTED_BACKGROUND);
    } else {
      tft.setTextColor(COLOR_TEXT);
    }
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + i * FONT_WIDTH, yPos + DISPLAY_PANEL_MARGIN);
    tft.print(textVal[i]);
  }

    if (selection == 0) {
      tft.setTextColor(COLOR_TEXT_SELECTED);
    } else {
      tft.setTextColor(COLOR_TEXT);
    }
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN, yPos + DISPLAY_PANEL_MARGIN + LINE_HEIGHT * 2);
    tft.print("CANCEL");
    if (selection == 1) {
      tft.setTextColor(COLOR_TEXT_SELECTED);
    } else {
      tft.setTextColor(COLOR_TEXT);
    }
    tft.setCursor(xPos + DISPLAY_PANEL_MARGIN + FONT_WIDTH * 17, yPos + DISPLAY_PANEL_MARGIN + LINE_HEIGHT * 2);
    tft.print("OKAY");
    
}


char TextInputPanel::prevChar(char curChar) {
  switch (curChar) {
    case ' ':
      return 'z';
    case '0':
      return '.';
    default:
      return curChar - 1;
  }
}

    
char TextInputPanel::nextChar(char curChar) {
  switch (curChar) {
    case 'z':
      return ' ';
    case '.':
      return '0';
    default:
      return curChar + 1;
  }
}
