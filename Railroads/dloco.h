#ifndef DLOCO_H
#define DLOCO_H

#include <dpath.h>

class DLoco
{

 public:
        DLoco();
   double x;
   double y;

   double t;

   double v;

   DPath * path;

   int nextpointindex;


   int d;

};

#endif // DLOCO_H
