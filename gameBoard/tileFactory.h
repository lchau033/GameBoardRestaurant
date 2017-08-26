//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <math.h>
#include"tile.h"


class TileFactory{
private:
    static Tile **tff;
    static int point;
    TileFactory(int _nTiles);
public:
    static TileFactory *get(int _nTiles);

    Tile *next();

};


#endif // TILEFACTORY_H
