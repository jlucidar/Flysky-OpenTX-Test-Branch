/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "opentx.h"

void TextEdit::paint(BitmapBuffer * dc)
{
  bool hasFocus = this->hasFocus();
  LcdFlags textColor = 0;
  LcdFlags lineColor = CURVE_AXIS_COLOR;
  if (hasFocus) {
    textColor = TEXT_INVERTED_BGCOLOR;
    lineColor = TEXT_INVERTED_BGCOLOR;
  }
  if (!hasFocus && zlen(value, length) == 0)
    dc->drawSizedText(3, 3, "---", length, CURVE_AXIS_COLOR);
  else
    dc->drawSizedText(3, 3, value, length, ZCHAR | textColor);
  drawSolidRect(dc, 0, 0, rect.w, rect.h, 1, lineColor);
  if (hasFocus) {
    coord_t cursorPos = keyboard->getCursorPos();
    dc->drawSolidFilledRect(cursorPos + 2, 3, 2, 22, 0); // TEXT_INVERTED_BGCOLOR);
  }
}

bool TextEdit::onTouch(coord_t x, coord_t y)
{
  setFocus();
  if (keyboard->getField() != this) {
    keyboard->setField(this);
  }
  keyboard->setCursorPos(x);
  return true;
}