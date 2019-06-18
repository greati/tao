#ifndef _TAO_GEOMETRY_
#define _TAO_GEOMETRY_

namespace tao {
namespace geometry {
    /**
     * Convert degress to radians.
     *
     * @param degress
     * @return radians
     * */
    float radians(float degrees) {
        return M_PI * degrees / 180.0;
    }
};
};


#endif
