#include "MusicPlayerApp.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "DataPath.h"

MusicPlayerApp::MusicPlayerApp() = default;
MusicPlayerApp::~MusicPlayerApp() = default;

void MusicPlayerApp::run()
{
    const std::string songsPath = GetDataPath("songs.txt");

    if (!loadLibraryFromFile(songsPath))
    {
        std::cout << "Warning: could not load songs from '" << songsPath << "'. Check the path." << std::endl;
    }

    bool running = true;
    while (running)
    {
        showMainMenu();
        int choice = readInt("Choose an option: ");

        switch (choice)
        {
            case 1: handleShowLibrary();
                break;
            case 2: handleAddSongToQueue();
                break;
            case 3: handlePlayNextSong();
                break;
            case 4: handleShowHistory();
                break;
            case 5: handlePlayPreviousSong();
                break;
            case 6: handleShowQueues();
                break; // extra
            case 0: running = false;
                break;
            default:
                std::cout << "Unknown choice." << std::endl;
                break;
        }
    }

    std::cout << "Goodbye!" << std::endl;
}

void MusicPlayerApp::showMainMenu() const
{
    std::cout << std::endl;
    std::cout << "--- Console Music Player (Option 2 - Advanced) ---" << std::endl
              << "1) Show song library" << std::endl
              << "2) Add song to queue" << std::endl
              << "3) Play next song" << std::endl
              << "4) Show play history" << std::endl
              << "5) Play previous song (from history)" << std::endl
              << "6) Show queues (main & wish) [extra]" << std::endl
              << "0) Exit" << std::endl;
}

int MusicPlayerApp::readInt(const std::string& prompt) const
{
    int value = 0;
    std::cout << prompt;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "Invalid number, try again: ";
    }
    std::cin.ignore(1024, '\n'); // consume rest of line
    return value;
}

bool MusicPlayerApp::loadLibraryFromFile(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in)
    {
        return false;
    }

    std::string line;

    // First line often looks like: [records=50]
    if (!std::getline(in, line))
    {
        return false;
    }
    if (!line.empty() && line[0] != '[')
    {
        // First line is already a song line, rewind.
        in.seekg(0);
    }

    while (std::getline(in, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string artist;
        std::string title;
        std::string yearStr;
        std::string genre;
        std::string source;

        if (!std::getline(ss, artist, ';'))
            continue;
        if (!std::getline(ss, title,  ';'))
            continue;
        if (!std::getline(ss, yearStr,';'))
            continue;
        if (!std::getline(ss, genre, ';'))
            continue;
        if (!std::getline(ss, source,';'))
            source = "";

        int year = 0;
        try
        {
            year = std::stoi(yearStr);
        }
        catch (...)
        {
            year = 0;
        }

        TSong* song = new TSong(artist, title, year, genre, source);
        library.append(song);
    }

    std::cout << "Loaded " << library.getCount() << " songs into library." << std::endl;
    return true;
}

void MusicPlayerApp::handleShowLibrary() const
{
    if (library.getCount() == 0)
    {
        std::cout << "Library is empty." << std::endl;
        return;
    }
    library.printAll();
}

void MusicPlayerApp::handleAddSongToQueue()
{
    if (library.getCount() == 0)
    {
        std::cout << "Library is empty, nothing to queue." << std::endl;
        return;
    }

    library.printAll();
    int index = readInt("Enter song index to add: ");

    TSong* song = library.getSongByIndex(index);
    if (!song)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    std::cout << "Add to which queue?" << std::endl
              << "1) Main queue" << std::endl
              << "2) Wish queue" << std::endl;
    int choice = readInt("Choice: ");

    if (choice == 1)
    {
        mainQueue.enqueue(song);
        std::cout << "Added to main queue: " << song->toString() << std::endl;
    }
    else if (choice == 2)
    {
        wishQueue.enqueue(song);
        std::cout << "Added to wish queue: " << song->toString() << std::endl;
    }
    else
    {
        std::cout << "Unknown queue choice." << std::endl;
    }
}

void MusicPlayerApp::handlePlayNextSong()
{
    TSong* song = nullptr;

    if (!wishQueue.isEmpty())
    {
        song = wishQueue.dequeue();
    }
    else if (!mainQueue.isEmpty())
    {
        song = mainQueue.dequeue();
    }
    else
    {
        std::cout << "No songs in either queue." << std::endl;
        return;
    }

    std::cout << "Now playing: " << song->toString() << std::endl;
    history.push(song);
}

void MusicPlayerApp::handleShowHistory() const
{
    if (history.isEmpty())
    {
        std::cout << "History is empty." << std::endl;
        return;
    }
    history.print();
}

void MusicPlayerApp::handlePlayPreviousSong()
{
    if (history.isEmpty())
    {
        std::cout << "No previous song in history." << std::endl;
        return;
    }

    TSong* song = history.pop();
    wishQueue.enqueueFront(song);  // should play before anything else
    std::cout << "Previous song moved to front of wish queue: "
              << song->toString() << std::endl;
}

void MusicPlayerApp::handleShowQueues() const
{
    std::cout << std::endl;
    std::cout << "--- Wish Queue ---" << std::endl;
    if (wishQueue.isEmpty())
        std::cout << "(empty)" << std::endl;
    else
        wishQueue.print();

    std::cout << std::endl;
    std::cout << "--- Main Queue ---" << std::endl;
    if (mainQueue.isEmpty())
        std::cout << "(empty)" << std::endl;
    else
        mainQueue.print();
}