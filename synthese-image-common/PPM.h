#ifndef IMAGE_SYNTHESIS_PPM_H
#define IMAGE_SYNTHESIS_PPM_H

#include <ostream>
#include "PortableAnymap.h"
#include "vec.h"

class PPM : public PortableAnymap<Vec3<int>> {
public:
    PPM(const int &width, const int &height, const int &maxValue);

    void save(const std::string &path) const override;

    static PPM load(const std::string &path);

    friend std::ostream &operator<<(std::ostream &os, const PPM &pgm);
};

#endif //IMAGE_SYNTHESIS_PPM_H
