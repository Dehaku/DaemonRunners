#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "util.h"
#include "Textures.h"
#include "Shapes.h"



class Directions
{
public:
    bool north;
    bool east;
    bool south;
    bool west;

    enum CardinalDirections
    {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    void clear()
    {
        north = false;
        east = false;
        south = false;
        west = false;
    }

    int getRandomValidDirection()
    {
        std::vector<int> dirs;
        if(north)
            dirs.push_back(NORTH);
        if(east)
            dirs.push_back(EAST);
        if(south)
            dirs.push_back(SOUTH);
        if(west)
            dirs.push_back(WEST);

        if(dirs.empty())
            return -2;
        else
            return dirs[random(0,dirs.size()-1)];
    }

    int getDirectionCount()
    {
        int returnCount = 0;
        if(north)
            returnCount++;
        if(east)
            returnCount++;
        if(south)
            returnCount++;
        if(west)
            returnCount++;

        return returnCount;
    }

    Directions()
    {
        north = false;
        east = false;
        south = false;
        west = false;
    }
};

class ChunkTile
{
public:
    int type;
    bool walkable;
    int health;
    int resistence;
    int workTime;
    sf::Vector2f pos;

    enum tileType
    {
        EMPTY,
        WALL,
        FLOOR,
        WEAKFENCE,
        STRONGFENCE,
        CORE,
        ENEMYSPAWNER,
        TURRETLIGHT,
        TURRETHEAVY,
        TURRETRANDOM

    };


    bool affectHealth(float damage)
    {
         health -= std::max(damage-resistence,0.f);
         if(health <= 0)
         {
             health = 0;
             type = FLOOR;
             walkable = true;
             resistence = 0;
             workTime = 0;
             // Destroyed!
             return true;
         }
         return false;
    }

    ChunkTile()
    {
        type = EMPTY;
        walkable = false;
        health = 100;
        resistence = 1000;
        workTime = 0;
    }
};



class WorldChunk
{
public:
    sf::Texture chunkTexture;
    sf::Image chunkImage;
    bool chunkChanged;

    sf::Vector2i pos;
    ChunkTile tiles[32][32];
    Directions paths;
    bool startingPoint;
    bool deadEnd;
    bool bonusChunk;



    void buildChunkImage();

    void generateTiles();

    void genPaths(int baseDir = -1)
    {
        paths.north = false;
        paths.east = false;
        paths.south = false;
        paths.west = false;


        if(baseDir == -1)
        {
            int dir = random(0,3);
            if(dir == 0)
                paths.north = true;
            if(dir == 1)
                paths.east = true;
            if(dir == 2)
                paths.south = true;
            if(dir == 3)
                paths.west = true;
        }
        else
        {
            if(baseDir == 0)
                paths.south = true;
            if(baseDir == 1)
                paths.west = true;
            if(baseDir == 2)
                paths.north = true;
            if(baseDir == 3)
                paths.east = true;

            RandomWeightList RWL;
            RWL.addEntry("0",10);
            RWL.addEntry("1",60);
            RWL.addEntry("2",20);
            RWL.addEntry("3",10);

            int pathAmount;

            std::string RWLResult = RWL.getRandomName();
            if(RWLResult == "0")
                pathAmount = 0;
            if(RWLResult == "1")
                pathAmount = 1;
            if(RWLResult == "2")
                pathAmount = 2;
            if(RWLResult == "3")
                pathAmount = 3;

            for(int i = 0; i != pathAmount; i++)
            {
                int dir = random(0,3);
                if(dir == 0)
                    paths.north = true;
                if(dir == 1)
                    paths.east = true;
                if(dir == 2)
                    paths.south = true;
                if(dir == 3)
                    paths.west = true;
            }

        }

    }


    void drawTiles()
    {
        static sf::Texture &wallTex = texturemanager.getTexture("GenericWall.png");
        static sf::Texture &floorTex = texturemanager.getTexture("GenericFloor.png");
        static sf::Texture &weakfenceTex = texturemanager.getTexture("GenericWeakFence.png");

        sf::Color chunkColor = sf::Color::White;
        if(deadEnd)
            chunkColor = sf::Color(200,0,0);
        if(startingPoint)
            chunkColor = sf::Color(0,0,200);
        if(bonusChunk)
            chunkColor = sf::Color(0,200,0);

        for(int i = 0; i != 32; i++)
            for(int t = 0; t != 32; t++)
        {
            sf::Vector2f drawPos(pos.x+(i*32),pos.y+(t*32));

            if(!onScreen(drawPos))
                continue;

            if(tiles[i][t].type == ChunkTile::WALL)
            {
                shapes.createImageButton(drawPos,wallTex);
                shapes.shapes.back().maincolor = chunkColor;
            }



            if(tiles[i][t].type == ChunkTile::FLOOR)
            {
                shapes.createImageButton(drawPos,floorTex);
                shapes.shapes.back().maincolor = chunkColor;
            }

            if(tiles[i][t].type == ChunkTile::WEAKFENCE)
            {
                shapes.createImageButton(drawPos,weakfenceTex);
                shapes.shapes.back().maincolor = chunkColor;
            }

        }
    }

    WorldChunk()
    {
        chunkChanged = false;

        startingPoint = false;
        deadEnd = false;
        bonusChunk = false;
    }
};

void buildTile(ChunkTile& tile, int tileType);

void buildChallengeChunk(WorldChunk& chunk);

class World
{
public:
    std::list<WorldChunk> chunks;

    class WalkableTile
    {
    public:
        sf::Vector2i pos;
    };

    std::list<WalkableTile> walkableTiles;

    bool isTileWalkableAlt(sf::Vector2i pos)
    {
        if(walkableTiles.empty())
            return false;

        for(auto &walkable : walkableTiles)
        {
            if(aabb(pos,walkable.pos.x-16,walkable.pos.x+16,walkable.pos.y-16,walkable.pos.y+16))
            {
                return true;
            }

        }
        return false;
    }

    ChunkTile& getTile(sf::Vector2i pos)
    {
        for(auto &chunk : chunks)
        {
            sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
            sf::Vector2i checkPos(pos.x/1024,pos.y/1024);
            if(checkPos == chunkPos)
            {

                int tilePosX = (pos.x-(1024*(pos.x/1024)))/32;
                int tilePosY = (pos.y-(1024*(pos.y/1024)))/32;

                return chunk.tiles[tilePosX][tilePosY];

            }
        }
        ChunkTile tiley;
        return tiley;
    }

    WorldChunk& getChunk(sf::Vector2i pos)
    {
        for(auto &chunk : chunks)
        {
            sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
            sf::Vector2i checkPos(pos.x/1024,pos.y/1024);
            if(checkPos == chunkPos)
                return chunk;
        }
        WorldChunk chunky;
        return chunky;
    }

    bool isTileWalkable(sf::Vector2i pos)
    {
        for(auto &chunk : chunks)
        {
            sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
            sf::Vector2i checkPos(pos.x/1024,pos.y/1024);
            if(checkPos == chunkPos)
            {

                /*
                int xRemoval = pos/1024;
                int xStage2 = pos-(1024*xRemoval);
                int xTile = xStage2/32;
                */

                int tilePosX = (pos.x-(1024*(pos.x/1024)))/32;
                int tilePosY = (pos.y-(1024*(pos.y/1024)))/32;


                if(chunk.tiles[tilePosX][tilePosY].walkable)
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    void printWalkables()
    {
        int tileCount = 0;
        for(auto &walkable : walkableTiles)
        {
            tileCount++;
            if(tileCount > 200)
                break;

            std::cout << tileCount << ": " << walkable.pos.x << "/" << walkable.pos.y << std::endl;


        }
    }

    void cacheWalkableTiles()
    {
        if(chunks.empty())
            return;

        WalkableTile walkable;
        for(auto &chunk : chunks)
        {
            for(int i = 0; i != 32; i++)
                for(int t = 0; t != 32; t++)
            {
                if(chunk.tiles[i][t].walkable)
                {
                    walkable.pos = sf::Vector2i(chunk.pos.x+(i*32),chunk.pos.y+(t*32));
                    walkableTiles.push_back(walkable);
                }
            }
        }

    }

    bool chunkExists(sf::Vector2i chunkPos)
    {
        for(auto &chunk : chunks)
        {
            if(chunk.pos == chunkPos)
                return true;
        }
        return false;
    }

    bool isChunkDeadEnd(WorldChunk& chunky)
    {
        for(auto &chunk : chunks)
        {
            if(chunk.pos == chunky.pos)
            {
                if(chunk.paths.getDirectionCount() == 1 && !chunk.startingPoint)
                {
                    chunk.deadEnd = true;
                    return true;
                }
                else
                {
                    chunk.deadEnd = false;
                    return false;
                }


            }

        }
        return false;
    }

    void furnishChunks()
    {
        for(auto &chunk : chunks)
            chunk.generateTiles();
    }

    World()
    {
        walkableTiles.clear();
    }
};



class WorldManager
{
public:
    // std::list<World> worlds;
    World currentWorld;
    unsigned int globalIDs;
    void generateWorld(unsigned int minSize = 3, int maxSize = 10)
    {
        bool properSize = false;
        World world;

        while(properSize == false)
        {


            WorldChunk chunk;

            chunk.genPaths();
            chunk.pos = sf::Vector2i(102400,102400);
            chunk.startingPoint = true;
            world.chunks.push_back(chunk);
            WorldChunk lastChunk = chunk;
            chunk.startingPoint = false;

            gvars::currentx = 10240;
            gvars::currenty = 10240;



            for(int i = 0; i != maxSize; i++)
            {

                if(world.isChunkDeadEnd(lastChunk))
                    continue;

                std::vector<int> validPaths;
                {
                    bool northAble = false;
                    bool eastAble = false;
                    bool southAble = false;
                    bool westAble = false;
                    if(lastChunk.paths.north)
                        northAble = true;
                    if(lastChunk.paths.east)
                        eastAble = true;
                    if(lastChunk.paths.south)
                        southAble = true;
                    if(lastChunk.paths.west)
                        westAble = true;

                    sf::Vector2i northChunk(lastChunk.pos.x,lastChunk.pos.y-1024);
                    sf::Vector2i eastChunk(lastChunk.pos.x+1024,lastChunk.pos.y);
                    sf::Vector2i southChunk(lastChunk.pos.x,lastChunk.pos.y+1024);
                    sf::Vector2i westChunk(lastChunk.pos.x-1024,lastChunk.pos.y);


                    if(northAble && !world.chunkExists(northChunk))
                        validPaths.push_back(Directions::NORTH);
                    if(eastAble && !world.chunkExists(eastChunk))
                        validPaths.push_back(Directions::EAST);
                    if(southAble && !world.chunkExists(southChunk))
                        validPaths.push_back(Directions::SOUTH);
                    if(westAble && !world.chunkExists(westChunk))
                        validPaths.push_back(Directions::WEST);
                }

                if(validPaths.empty())
                {
                    chunk.deadEnd = true;
                    break;
                }



                int newDir;

                newDir = validPaths[random(0,validPaths.size()-1)];



                {
                    //newDir = lastChunk.paths.getRandomValidDirection();


                    /*
                    std::cout << i << "=== \n Chunks Dirs: " << lastChunk.paths.north << "/"<< lastChunk.paths.east << "/"
                    << lastChunk.paths.south << "/" << lastChunk.paths.west << ";"
                    << "Chosen Dir: " << newDir << std::endl;
                    */


                    if(newDir == Directions::NORTH)
                        chunk.pos += sf::Vector2i(0,-1024);
                    if(newDir == Directions::EAST)
                        chunk.pos += sf::Vector2i(1024,0);
                    if(newDir == Directions::SOUTH)
                        chunk.pos += sf::Vector2i(0,1024);
                    if(newDir == Directions::WEST)
                        chunk.pos += sf::Vector2i(-1024,0);

                }



                chunk.genPaths(newDir);






                // if(i == 9)
                //    chunk.deadEnd = true;

                lastChunk = chunk;
                world.chunks.push_back(chunk);
            }

            world.chunks.back().deadEnd = true;


            for(auto &lastChunkWork : world.chunks)
            {
                bool emptyNorth = false;
                bool emptyEast = false;
                bool emptySouth = false;
                bool emptyWest = false;
                std::vector<int> validPaths;
                {
                    bool northAble = false;
                    bool eastAble = false;
                    bool southAble = false;
                    bool westAble = false;
                    if(lastChunkWork.paths.north)
                        northAble = true;
                    if(lastChunkWork.paths.east)
                        eastAble = true;
                    if(lastChunkWork.paths.south)
                        southAble = true;
                    if(lastChunkWork.paths.west)
                        westAble = true;

                    sf::Vector2i northChunk(lastChunkWork.pos.x,lastChunkWork.pos.y-1024);
                    sf::Vector2i eastChunk(lastChunkWork.pos.x+1024,lastChunkWork.pos.y);
                    sf::Vector2i southChunk(lastChunkWork.pos.x,lastChunkWork.pos.y+1024);
                    sf::Vector2i westChunk(lastChunkWork.pos.x-1024,lastChunkWork.pos.y);


                    if(northAble && !world.chunkExists(northChunk))
                        emptyNorth = true;
                    if(eastAble && !world.chunkExists(eastChunk))
                        emptyEast = true;
                    if(southAble && !world.chunkExists(southChunk))
                        emptySouth = true;
                    if(westAble && !world.chunkExists(westChunk))
                        emptyWest = true;
                }


                if(emptyNorth)
                {
                    //lastChunkWork = chunky;
                    chunk = lastChunkWork;

                    chunk.pos += sf::Vector2i(0,-1024);

                    chunk.paths.clear();
                    chunk.paths.south = true;
                    chunk.bonusChunk = true;
                    world.chunks.push_back(chunk);
                }

                if(emptyEast)
                {
                    chunk = lastChunkWork;

                    chunk.pos += sf::Vector2i(1024,0);

                    chunk.paths.clear();
                    chunk.paths.west = true;
                    chunk.bonusChunk = true;
                    world.chunks.push_back(chunk);
                }

                if(emptySouth)
                {
                    chunk = lastChunkWork;

                    chunk.pos += sf::Vector2i(0,1024);

                    chunk.paths.clear();
                    chunk.paths.north = true;
                    chunk.bonusChunk = true;
                    world.chunks.push_back(chunk);
                }

                if(emptyWest)
                {
                    chunk = lastChunkWork;

                    chunk.pos += sf::Vector2i(-1024,0);

                    chunk.paths.clear();
                    chunk.paths.east = true;
                    chunk.bonusChunk = true;
                    world.chunks.push_back(chunk);
                }



            }


            if(world.chunks.size() > minSize)
                properSize = true;
            else
            {
                std::cout << "World too small, Rejected. (" << world.chunks.size() << ") \n";
                world.chunks.clear();
            }


        }



        world.furnishChunks();

        world.cacheWalkableTiles();
        std::cout << "Found Walkable Tiles: " << world.walkableTiles.size() << std::endl;

        // worlds.push_back(world);
        currentWorld = world;

    }

    void drawWalkableTiles()
    {
        World &world = currentWorld;

        for(auto &walkable : world.walkableTiles)
        {
            shapes.createSquare(walkable.pos.x-10,walkable.pos.y-10,walkable.pos.x+10,walkable.pos.y+10,sf::Color::Blue);
        }
    }


    WorldManager()
    {
        globalIDs = 0;
    }

};
extern WorldManager worldManager;







class WorldTile{
public:

    sf::Color color;
    bool isWater;
    float moveSpeedModifier;
    float temperature;
    WorldTile();


};

extern std::vector<std::vector<WorldTile>> worldTiles;

void resizeWorld(int x, int y, std::vector<std::vector<WorldTile>>& worldlies);



void worldTilesSetup(std::vector<std::vector<WorldTile>>& worldlies);


#endif // TILES_H_INCLUDED
