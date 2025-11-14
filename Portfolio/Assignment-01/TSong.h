#ifndef IKT203_COURSE_ASSIGNMENTS_TSONG_H
#define IKT203_COURSE_ASSIGNMENTS_TSONG_H

#include <string>

//simple data class representing one song
class TSong
{
public:
    TSong() = default;

    TSong(const std::string& artist,
          const std::string& title,
          int year,
          const std::string& genre,
          const std::string& source);

    //returns a readable version of the song (used in menus)
    std::string toString() const;

    std::string artist;
    std::string title;
    int year{};
    std::string genre;
    std::string source;
};

#endif //IKT203_COURSE_ASSIGNMENTS_TSONG_H