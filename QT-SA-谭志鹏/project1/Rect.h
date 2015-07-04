#ifndef __SP_RECT_H__
#define __SP_RECT_H__
//#include <ostream>
#include "Point.h"

namespace RECTPACKING {

struct Rect
{
 public:
    Rect(int w=0,int h=0):width(w),height(h)
    {
        lb.x=lb.y=0;
    }
    void setRect(int w,int h)
    {
        width=w;
        height=h;
    }

    int left() { return lb.x; }
    int right() { return lb.x+width; }
    int bottom() { return lb.y; }
    int top() { return lb.y+height; }
    int width;
    int height;
    Point lb;
};

//std::ostream & operator << (std::ostream &out, Rect &r);

}

#endif	//__SP_RECT_H__
