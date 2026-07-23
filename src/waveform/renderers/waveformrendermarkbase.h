#pragma once

#include <QColor>
#include <QObject>

#include <vector>

#include "skin/legacy/skincontext.h"
#include "util/class.h"
#include "waveform/renderers/waveformmarkset.h"
#include "waveform/renderers/waveformrendererabstract.h"

class WaveformRenderMarkBase : public QObject, public WaveformRendererAbstract {
    Q_OBJECT

  public:
    explicit WaveformRenderMarkBase(
            WaveformWidgetRenderer* waveformWidgetRenderer,
            bool updateImagesImmediately);

    void setup(const QDomNode& node, const SkinContext& context) override;

    // Called when a new track is loaded.
    void onSetTrack() override;

    void onResize() override;

  public slots:
    // Called when the loaded track's cues are added, deleted or modified and
    // when a new track is loaded.
    // It updates the marks' names and flags the need for an image update.
    // This method is used for hotcues.
    void slotCuesUpdated();

  private slots:
    // Called when a mark position or visibility changes
    void onMarkChanged(double v);

  protected:
    WaveformMarkSet m_marks;

    // Memory cues (CueType::MemoryCue) are not part of the skin-defined
    // WaveformMarkSet, which instantiates one mark per fixed control name.
    // They are dynamic in count and have no per-cue control, so they are
    // cached here from the track's cue list and painted directly by the
    // concrete renderers. The cache is rebuilt only on cue changes (see
    // updateMarksFromCues), never per frame.
    struct MemoryCueMark {
        double samplePosition;
        QColor color;
    };
    const std::vector<MemoryCueMark>& memoryCueMarks() const {
        return m_memoryCueMarks;
    }

    void updateMarkImages();

  private:
    const bool m_updateImagesImmediately;
    std::vector<MemoryCueMark> m_memoryCueMarks;

    void updateMarksFromCues();
    void updateMarks();

  private:
    virtual void updateMarkImage(WaveformMarkPointer pMark) = 0;

    DISALLOW_COPY_AND_ASSIGN(WaveformRenderMarkBase);
};
