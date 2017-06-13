#ifndef PATHINGCONTROLLER_H_INCLUDED
#define PATHINGCONTROLLER_H_INCLUDED

#include <string.h> // Apparently required by micropather.h
#include "micropather.h"
#include "Tiles.h"

#include <vector>
#include <SFML/System.hpp>

class ChunkTile;

class PathingController
    : public micropather::Graph
{ // This is the one actually being used.
private:
    PathingController(const PathingController &);
    void operator=(const PathingController &);
public:
    void NodeToXYZ(void *node, int *x, int *y);
    void *XYZToNode(int x, int y);
    int Passable(int nx, int ny);
    micropather::MPVector<void *> microPath;
    micropather::MicroPather *pather;
    std::vector<ChunkTile *> storedPath;
    std::vector<ChunkTile *> storedRPath;
    PathingController();
    void drawPath();
    void drawStoredPath();
    void drawStoredPathRainbow();
    void storePath(void *node);
    void storeRPath(void *node);
    int makePath(sf::Vector2f Ori, sf::Vector2f Tar);
    virtual ~PathingController();
    virtual float LeastCostEstimate(void *nodeStart, void *nodeEnd);
    virtual void AdjacentCost(void *node,
                              micropather::MPVector<micropather::StateCost> *neighbors);
    virtual void
    AdjacentCostPureFlight(void *node,
                           micropather::MPVector<micropather::StateCost> *neighbors);
    virtual void PrintStateInfo(void *node);

};
extern PathingController pathCon;

void resetPathingController();

#endif // PATHINGCONTROLLER_H_INCLUDED
