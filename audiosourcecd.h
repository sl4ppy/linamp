#ifndef AUDIOSOURCECD_H
#define AUDIOSOURCECD_H

#define PY_SSIZE_T_CLEAN
#undef slots
#include <Python.h>
#define slots Q_SLOTS

#include <QObject>
#include <QTimer>
#include <QtConcurrent>

#include "audiosourcewspectrumcapture.h"

class AudioSourceCD : public AudioSourceWSpectrumCapture
{
    Q_OBJECT
public:
    explicit AudioSourceCD(QObject *parent = nullptr);
    ~AudioSourceCD();

public slots:
    void activate();
    void deactivate();
    void handlePl();
    void handlePrevious();
    void handlePlay();
    void handlePause();
    void handleStop();
    void handleNext();
    void handleOpen();
    void handleShuffle();
    void handleRepeat();
    void handleSeek(int mseconds);

private:
    bool isActive = false;

    PyObject *cdplayerModule;
    PyObject *cdplayer;

    QTimer *progressRefreshTimer = nullptr;
    QTimer *progressInterpolateTimer = nullptr;
    QElapsedTimer progressInterpolateElapsedTimer;
    quint32 currentProgress = 0;
    void refreshProgress();
    void interpolateProgress();

    // Detect disc insertion thread
    QTimer *detectDiscInsertionTimer = nullptr;
    bool pollInProgress = false;
    void pollDetectDiscInsertion();
    bool doPollDetectDiscInsertion();
    void handlePollResult();
    QFutureWatcher<bool> pollResultWatcher;

    // Load disc thread
    void doLoad();
    void handleLoadEnd();
    QFutureWatcher<void> loadWatcher;

    // Eject thread
    void doEject();
    void handleEjectEnd();
    QFutureWatcher<void> ejectWatcher;

    QString currentStatus; // Status as it comes from python
    bool isShuffleEnabled = false;
    bool isRepeatEnabled = false;

    void refreshStatus(bool shouldRefreshTrackInfo = true);
    void refreshTrackInfo(bool force = false);

    quint32 currentTrackNumber = std::numeric_limits<quint32>::max();
};

#endif // AUDIOSOURCECD_H
