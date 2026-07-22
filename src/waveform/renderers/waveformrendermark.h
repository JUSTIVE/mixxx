#pragma once

#include "waveform/renderers/waveformrendermarkbase.h"

class WaveformRenderMark : public WaveformRenderMarkBase {
  public:
    explicit WaveformRenderMark(WaveformWidgetRenderer* waveformWidgetRenderer);

    void draw(QPainter* painter, QPaintEvent* event) override;

  private:
    void updateMarkImage(WaveformMarkPointer pMark) override;
    void drawMemoryCues(QPainter* painter);

    DISALLOW_COPY_AND_ASSIGN(WaveformRenderMark);
};
