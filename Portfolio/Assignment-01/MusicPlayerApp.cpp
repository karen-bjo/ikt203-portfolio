#include "MusicPlayerApp.h"

#include <fstream>
#include <iostream>
#include <sstream>

MusicPlayerApp::MusicPlayerApp() = default;
MusicPlayerApp::~MusicPlayerApp() = default;

void MusicPlayerApp::run()
{
    const std::string songsPath = "../DATA/songs.txt";

    if (!loadLibraryFromFile(songsPath))
    {
        std::cout << "Warning: could not load songs from '" << songsPath
                  << "'. Check the path.\n";
    }

    bool running = true;
    while (running)
    {
        showMainMenu();
        int choice = readInt("Choose an option: ");

        switch (choice)
        {
            case 1: handleShowLibrary();      break;
            case 2: handleAddSongToQueue();   break;
            case 3: handlePlayNextSong();     break;
            case 4: handleShowHistory();      break;
            case 5: handlePlayPreviousSong(); break;
            case 6: handleShowQueues();       break; // extra
            case 0: running = false;          break;
            default:
                std::cout << "Unknown choice.\n";
                break;
        }
    }

    std::cout << "Goodbye!\n";
}

void MusicPlayerApp::showMainMenu() const
{
    std::cout << "\n=== Console Music Player (Option 2 – Advanced) ===\n"
              << "1) Show song library\n"
              << "2) Add song to queue\n"
              << "3) Play next song\n"
              << "4) Show play history\n"
              << "5) Play previous song (from history)\n"
              << "6) Show queues (main & wish) [extra]\n"
              << "0) Exit\n";
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

        if (!std::getline(ss, artist, ';')) continue;
        if (!std::getline(ss, title,  ';')) continue;
        if (!std::getline(ss, yearStr,';')) continue;
        if (!std::getline(ss, genre, ';')) continue;
        if (!std::getline(ss, source,';')) source = "";

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

    std::cout << "Loaded " << library.getCount() << " songs into library.\n";
    return true;
}

void MusicPlayerApp::handleShowLibrary() const
{
    if (library.getCount() == 0)
    {
        std::cout << "Library is empty.\n";
        return;
    }
    library.printAll();
}

void MusicPlayerApp::handleAddSongToQueue()
{
    if (library.getCount() == 0)
    {
        std::cout << "Library is empty, nothing to queue.\n";
        return;
    }

    library.printAll();
    int index = readInt("Enter song index to add: ");

    TSong* song = library.getSongByIndex(index);
    if (!song)
    {
        std::cout << "Invalid index.\n";
        return;
    }

    std::cout << "Add to which queue?\n"
              << "1) Main queue\n"
              << "2) Wish queue\n";
    int choice = readInt("Choice: ");

    if (choice == 1)
    {
        mainQueue.enqueue(song);
        std::cout << "Added to main queue: " << song->toString() << '\n';
    }
    else if (choice == 2)
    {
        wishQueue.enqueue(song);
        std::cout << "Added to wish queue: " << song->toString() << '\n';
    }
    else
    {
        std::cout << "Unknown queue choice.\n";
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
        std::cout << "No songs in either queue.\n";
        return;
    }

    std::cout << "Now playing: " << song->toString() << '\n';
    history.push(song);
}

void MusicPlayerApp::handleShowHistory() const
{
    if (history.isEmpty())
    {
        std::cout << "History is empty.\n";
        return;
    }
    history.print();
}

void MusicPlayerApp::handlePlayPreviousSong()
{
    if (history.isEmpty())
    {
        std::cout << "No previous song in history.\n";
        return;
    }

    TSong* song = history.pop();
    wishQueue.enqueueFront(song);  // should play before anything else
    std::cout << "Previous song moved to front of wish queue: "
              << song->toString() << '\n';
}

void MusicPlayerApp::handleShowQueues() const
{
    std::cout << "\n--- Wish Queue ---\n";
    if (wishQueue.isEmpty())
        std::cout << "(empty)\n";
    else
        wishQueue.print();

    std::cout << "\n--- Main Queue ---\n";
    if (mainQueue.isEmpty())
        std::cout << "(empty)\n";
    else
        mainQueue.print();
}