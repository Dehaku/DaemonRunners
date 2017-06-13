#include "PathingController.h"
#include "util.h"
#include "Shapes.h"

using namespace micropather;

PathingController pathCon;

void PathingController::NodeToXYZ(void *node, int *x, int *y)
{
    ChunkTile *Nodeling = static_cast<ChunkTile *>(node);

    *x = Nodeling->pos.x;
    *y = Nodeling->pos.y;
}

void *PathingController::XYZToNode(int x, int y)
{
    // TODO: Fix this, It is NOT functional.
    return (void *)&(worldManager.currentWorld.chunks.back().tiles[x][y]);
}

int PathingController::Passable(int nx, int ny)
{
    // if (nx >= 0 && nx < GRIDS && ny >= 0 && ny < GRIDS) Range check?

    // TODO: Fix this, It is NOT functional.
    /*

    {

        if (tiles[nx][ny][nz].goesDown && tiles[nx][ny][nz].goesUp)
            return 4;
        if (tiles[nx][ny][nz].goesDown)
            return 3; // return 2;
        if (tiles[nx][ny][nz].goesUp)
            return 2; // return 3;
        if (tiles[nx][ny][nz].walkable)
            return 1;
    }

    */
    return 0;
}

PathingController::PathingController() : pather(0)
{
    pather = new MicroPather(
                this, 20); // Use a very small memory block to stress the pather
}

void PathingController::drawPath()
{
    unsigned int k;
    unsigned int pathSize = microPath.size();
    Vec3 oldPos;
    for (k = 0; k < pathSize; ++k)
    {
        Vec3 pathPos;
        NodeToXYZ(microPath[k], &pathPos.x, &pathPos.y);
        sf::Color pathColor(0, 0, 0);
        if (pathPos.z == 0)
            pathColor.r = 255;
        if (pathPos.z == 1)
            pathColor.g = 255;
        if (pathPos.z == 2)
            pathColor.b = 255;

        if (k != 0)
            shapes.createLine((oldPos.x + 1) * GRID_SIZE - GRID_SIZE/2,
                              (oldPos.y + 1) * GRID_SIZE - GRID_SIZE/2,
                              (pathPos.x + 1) * GRID_SIZE - GRID_SIZE/2,
                              (pathPos.y + 1) * GRID_SIZE - GRID_SIZE/2, 5, pathColor);

        oldPos = pathPos;
    }
}

void PathingController::drawStoredPath()
{
    sf::Vector2f oldPos;
    bool firstRun = true;

    for (auto &i : storedPath)
    {
        sf::Vector2f pathPos;
        pathPos = i->pos;
        sf::Color pathColor(255, 255, 255, 100);

        if (!firstRun)
            shapes.createLine((oldPos.x + 1) * GRID_SIZE - (GRID_SIZE/2),
                              (oldPos.y + 1) * GRID_SIZE - (GRID_SIZE/2),
                              (pathPos.x + 1) * GRID_SIZE - (GRID_SIZE/2),
                              (pathPos.y + 1) * GRID_SIZE - (GRID_SIZE/2), 5, pathColor);

        oldPos = pathPos;
        firstRun = false;
    }

}



void PathingController::storePath(void *node)
{
    ChunkTile *Nodeling = static_cast<ChunkTile *>(node);
    storedPath.push_back(Nodeling);
}

void PathingController::storeRPath(void *node)
{
    ChunkTile *Nodeling = static_cast<ChunkTile *>(node);
    storedRPath.push_back(Nodeling);
}

int PathingController::makePath(sf::Vector2f Ori, sf::Vector2f Tar)
{
    int result = 0;
    if (Passable(Tar.x, Tar.y) == 1)
    {
        float totalCost;

        result = pather->Solve(XYZToNode(Ori.x, Ori.y),
                               XYZToNode(Tar.x, Tar.y), &microPath,
                               &totalCost);

        if (result == MicroPather::SOLVED)
        {
            unsigned int pathSize = microPath.size();
            for (int i = 0; i != pathSize; i++)
            {
                storePath(microPath[i]);
            }
        }
        unsigned int pathSize = microPath.size();
        for (int i = 0; i != pathSize; i++)
        {
            storeRPath(microPath[i]);
        }



    }
    return result;
}

PathingController::~PathingController()
{
    delete pather;
}

float PathingController::LeastCostEstimate(void *nodeStart, void *nodeEnd)
{
    int xStart, yStart, zStart, xEnd, yEnd, zEnd;
    NodeToXYZ(nodeStart, &xStart, &yStart);
    NodeToXYZ(nodeEnd, &xEnd, &yEnd);

    double d = sqrt(pow(xEnd - xStart, 2) + pow(yEnd - yStart, 2) +
                    pow(zEnd - zStart, 2));
    /* Compute the minimum path cost using distance measurement. It is possible
           to compute the exact minimum path using the fact that you can move only
           on a straight line or on a diagonal, and this will yield a better result.
        */
    return d;
}

void PathingController::AdjacentCost(void *node, micropather::MPVector<StateCost> *neighbors)
{
    int x, y, z;
    NodeToXYZ(node, &x, &y);
    //const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    //const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    //const int dx[26] = { -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1};
    //const int dy[26] = { -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1};
    //const int dz[26] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    const int dx[10] = {0, -1, 0, 1, -1, 1, -1, 0, 1, 0};
    const int dy[10] = {0, -1, -1, -1, 0, 0, 1, 1, 1, 0};
    const int dz[10] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 1};

    //const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };
    float One = 1;
    float Two = 1.41f;
    float Three = 1.44f;
    const float cost[10] = {One, Two, One, Two, One,
                            One, Two, One, Two, One};

    ChunkTile *Nodeling = static_cast<ChunkTile *>(node);

    /* Teleporter code
    if (Nodeling->teleporter)
    {
        Vec3 N(Nodeling->telePos);
        StateCost nodeCost = {XYZToNode(N.x, N.y, N.z), 3};
        neighbors->push_back(nodeCost);
    }
    */

    for (int i = 0; i < 10; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];

        int pass = Passable(nx, ny);
        bool notCorner = true;
        if(pass > 0)
        {
            if(i == 1)
            {
                //1 up left, 3 up right, 6 down left, 8 down right
                if(Passable(x+dx[i],y) > 0 && Passable(x,y+dy[i]) > 0){}
                else
                    notCorner = false;

            }
            if(i == 3)
            {
                //1 up left, 3 up right, 6 down left, 8 down right
                if(Passable(x+dx[i],y) > 0 && Passable(x,y+dy[i]) > 0){}
                else
                    notCorner = false;

            }
            if(i == 6)
            {
                //1 up left, 3 up right, 6 down left, 8 down right
                if(Passable(x+dx[i],y) > 0 && Passable(x,y+dy[i]) > 0){}
                else
                    notCorner = false;

            }
            if(i == 8)
            {
                //1 up left, 3 up right, 6 down left, 8 down right
                if(Passable(x+dx[i],y) > 0 && Passable(x,y+dy[i]) > 0){}
                else
                    notCorner = false;

            }
        }

        if(i == 0 || i == 9) // Z-levels are not needed on BT.
            pass = 0;

        if (pass > 0 && notCorner)
        {
            if (pass == 4)
            {
                StateCost nodeCost = {XYZToNode(nx, ny), cost[i]};
                neighbors->push_back(nodeCost);
            }
            else if ( (pass == 1 || pass == 2 || pass == 3) && dz[i] == 0)
            {
                StateCost nodeCost = {XYZToNode(nx, ny), cost[i]};
                neighbors->push_back(nodeCost);
            }
            else if (pass == 3 && dz[i] == -1 && dx[i] == 0 && dy[i] == 0)
            {
                StateCost nodeCost = {XYZToNode(nx, ny), cost[i]};
                neighbors->push_back(nodeCost);
            }
            else if (pass == 2 && dz[i] == 1 && dx[i] == 0 && dy[i] == 0)
            {
                StateCost nodeCost = {XYZToNode(nx, ny), cost[i]};
                neighbors->push_back(nodeCost);
            }
            else
            {
                StateCost nodeCost = {XYZToNode(nx, ny), FLT_MAX};
                neighbors->push_back(nodeCost);
            }
        }
    }
}

void PathingController::AdjacentCostPureFlight(void *node, micropather::MPVector<StateCost> *neighbors)
{
    int x, y, z;
    NodeToXYZ(node, &x, &y);
    //const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    //const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    const int dx[26] = {-1, 0,  1, -1, 0,  1, -1, 0,  1, -1, 0,  1, -1,
                        1,  -1, 0, 1,  -1, 0, 1,  -1, 0, 1,  -1, 0, 1};
    const int dy[26] = {-1, -1, -1, 0, 0,  0,  1,  1, 1, -1, -1, -1, 0,
                        0,  1,  1,  1, -1, -1, -1, 0, 0, 0,  1,  1,  1};
    const int dz[26] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0,
                        0,  0,  0,  0,  1,  1,  1,  1,  1,  1, 1, 1, 1};
    //const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };
    float One = 1;
    float Two = 1.41f;
    float Three = 1.44f;
    const float cost[26] = {Three, Two,   Three, Two,   One,  Two,   Three,
                            Two,   Three, Two,   One,   Two,  One,   One,
                            Two,   One,   Two,   Three, Two,  Three, Two,
                            One,   Two,   Three, Two,   Three};

    for (int i = 0; i < 26; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];

        int pass = Passable(nx, ny);
        if (pass > 0)
        {
            if (pass == 1)
            {
                // Normal floor
                StateCost nodeCost = {XYZToNode(nx, ny), cost[i]};
                neighbors->push_back(nodeCost);
            }
            else
            {
                // Normal floor
                StateCost nodeCost = {XYZToNode(nx, ny), FLT_MAX};
                neighbors->push_back(nodeCost);
            }
        }
    }
}

void PathingController::PrintStateInfo(void *node)
{
    int x, y, z;
    NodeToXYZ(node, &x, &y);
    printf("(%d,%d,%d)", x, y, z);
}

void resetPathingController()
{
    pathCon.pather->Reset();
}
