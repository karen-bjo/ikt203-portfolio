#ifndef IKT203_COURSE_ASSIGNMENTS_MUSICPLAYERAPP_H
#define IKT203_COURSE_ASSIGNMENTS_MUSICPLAYERAPP_H

#include "TSongLibraryList.h"
#include "TSongQueue.h"
#include "TSongStack.h"
#include <string>

class MusicPlayerApp
{
public:
    MusicPlayerApp();
    ~MusicPlayerApp();

    void run();

private:
    TSongLibraryList library;
    TSongQueue       mainQueue;
    TSongQueue       wishQueue;
    TSongStack       history;

    bool loadLibraryFromFile(const std::string& filePath);

    void handleShowLibrary() const;
    void handleAddSongToQueue();
    void handlePlayNextSong();
    void handleShowHistory() const;
    void handlePlayPreviousSong();

    void handleShowQueues() const;

    void showMainMenu() const;
    int  readInt(const std::string& prompt) const;
};

#endif //IKT203_COURSE_ASSIGNMENTS_MUSICPLAYERAPP_H