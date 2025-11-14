#include "TSong.h"

TSong::TSong(const std::string& artist,
             const std::string& title,
             int year,
             const std::string& genre,
             const std::string& source)
    : artist(artist),
      title(title),
      year(year),
      genre(genre),
      source(source)
{
}

std::string TSong::toString() const
{
    //chose to include the source at the end to show where the song came from
    return artist + " - " + title + " (" + std::to_string(year) + ", " + genre + ", " + source + ")";
}