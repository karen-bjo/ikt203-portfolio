#ifndef IKT203_COURSE_ASSIGNMENTS_DATAPATH_H
#define IKT203_COURSE_ASSIGNMENTS_DATAPATH_H

#include <string>

//uses path defined in CMake, IKT203_DATA_DIR
inline std::string GetDataPath(const std::string& filename)
{
    return std::string(IKT203_DATA_DIR) + "/" + filename;
}

#endif //IKT203_COURSE_ASSIGNMENTS_DATAPATH_H