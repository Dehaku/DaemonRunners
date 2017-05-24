#include "Game.h"

#include <iomanip>

StateTracker::StateTracker()
{
    lastState = mainMenu;
    currentState = mainMenu;
}
StateTracker stateTracker;

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

    enum tileType
    {
        EMPTY,
        WALL,
        FLOOR,
        WEAKFENCE,
        STRONGFENCE,
        CORE

    };


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
    sf::Vector2i pos;
    ChunkTile tiles[32][32];
    Directions paths;
    bool startingPoint;
    bool deadEnd;
    bool bonusChunk;


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
        startingPoint = false;
        deadEnd = false;
        bonusChunk = false;

    }
};

void buildTile(ChunkTile& tile, int tileType)
{
    if(tileType == ChunkTile::WALL)
    {
        tile.type = ChunkTile::WALL;
        tile.walkable = false;
        tile.health = 100;
        tile.resistence = 1000;
        tile.workTime = 0;
    }
    else if(tileType == ChunkTile::FLOOR)
    {
        tile.type = ChunkTile::FLOOR;
        tile.walkable = true;
        tile.health = 0;
        tile.resistence = 0;
        tile.workTime = 0;
    }
    else if(tileType == ChunkTile::WEAKFENCE)
    {
        tile.type = ChunkTile::WEAKFENCE;
        tile.walkable = false;
        tile.health = 100;
        tile.resistence = 10;
        tile.workTime = 0;
    }
}

void buildChallengeChunk(WorldChunk& chunk)
{
    int challengeType = random(1,2);
    if(challengeType == 1)
    {
        for(int i = 4; i != 28; i++)
            for(int t = 4; t != 28; t++)
        {
            buildTile(chunk.tiles[i][t], ChunkTile::FLOOR);
        }

        if(chunk.paths.north && chunk.paths.south)
        {
            for(int i = 4; i != 28; i++)
                for(int t = 15; t != 17; t++)
            {
                buildTile(chunk.tiles[i][t], ChunkTile::WEAKFENCE);
            }
        }

        if(chunk.paths.west && chunk.paths.east)
        {
            for(int i = 15; i != 17; i++)
                for(int t = 4; t != 28; t++)
            {
                buildTile(chunk.tiles[i][t], ChunkTile::WEAKFENCE);
            }
        }
    }
    if(challengeType == 2)
    {
        for(int i = 4; i != 28; i++)
            for(int t = 4; t != 28; t++)
        {
            buildTile(chunk.tiles[i][t], ChunkTile::FLOOR);
        }

        if(chunk.paths.north && chunk.paths.south)
        {
            for(int i = 4; i != 28; i++)
                for(int t = 15; t != 17; t++)
            {
                buildTile(chunk.tiles[i][t], ChunkTile::WALL);
            }

            buildTile(chunk.tiles[15][15], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[15][16], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[16][15], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[16][16], ChunkTile::WEAKFENCE);
        }

        if(chunk.paths.west && chunk.paths.east)
        {
            for(int i = 15; i != 17; i++)
                for(int t = 4; t != 28; t++)
            {
                buildTile(chunk.tiles[i][t], ChunkTile::WALL);
            }

            buildTile(chunk.tiles[15][15], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[15][16], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[16][15], ChunkTile::WEAKFENCE);
            buildTile(chunk.tiles[16][16], ChunkTile::WEAKFENCE);
        }
    }



}

void WorldChunk::generateTiles()
{
    for(int i = 0; i != 32; i++)
        for(int t = 0; t != 32; t++)
    {
        int tileType = random(0,1);
        buildTile(tiles[i][t], tileType);
    }



    bool roundAbout = false;
    {
        if(paths.north && paths.east)
            roundAbout = true;
        if(paths.south && paths.east)
            roundAbout = true;
        if(paths.north && paths.west)
            roundAbout = true;
        if(paths.south && paths.west)
            roundAbout = true;
        if(startingPoint || deadEnd || bonusChunk)
            roundAbout = true;
    }

    if(roundAbout)
    {
        for(int i = 0; i != 360; i++)
        {
            for(int t = 0; t != 8; t++)
            {
                sf::Vector2f tilePosF = math::angleCalc(sf::Vector2f(16,16),i,t);
                sf::Vector2i tilePos(tilePosF.x,tilePosF.y);
                buildTile(tiles[tilePos.x][tilePos.y],ChunkTile::FLOOR);
            }

            sf::Vector2f tilePosF = math::angleCalc(sf::Vector2f(16,16),i,8);
            sf::Vector2i tilePos(tilePosF.x,tilePosF.y);
            buildTile(tiles[tilePos.x][tilePos.y],ChunkTile::WALL);
        }
    }



    if(paths.north)
    {
        for(int i = 14; i != 18; i++)
            for(int t = 0; t != 16; t++)
        {
            buildTile(tiles[i][t], ChunkTile::FLOOR);
        }
    }
    if(paths.east)
    {
        for(int i = 15; i != 32; i++)
            for(int t = 14; t != 18; t++)
        {
            buildTile(tiles[i][t], ChunkTile::FLOOR);
        }
    }
    if(paths.south)
    {
        for(int i = 14; i != 18; i++)
            for(int t = 15; t != 32; t++)
        {
            buildTile(tiles[i][t], ChunkTile::FLOOR);
        }
    }
    if(paths.west)
    {
        for(int i = 0; i != 16; i++)
            for(int t = 14; t != 18; t++)
        {
            buildTile(tiles[i][t], ChunkTile::FLOOR);
        }
    }

    if(!roundAbout)
    {
        int challengeChance = random(1,10);

        if(challengeChance <= 3)
            buildChallengeChunk(*this);
    }








}

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

    bool isTileWalkable(sf::Vector2i pos)
    {
        if(walkableTiles.empty())
            return false;

        int tries = 0;

        for(auto &walkable : walkableTiles)
        {
            tries++;
            if(aabb(pos,walkable.pos.x-16,walkable.pos.x+16,walkable.pos.y-16,walkable.pos.y+16))
            {
                return true;
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
    std::list<World> worlds;
    void generateWorld(unsigned int minSize = 3, int maxSize = 10)
    {
        bool properSize = false;
        World world;

        while(properSize == false)
        {


            WorldChunk chunk;

            chunk.genPaths();
            chunk.pos = sf::Vector2i(1024,1024);
            chunk.startingPoint = true;
            world.chunks.push_back(chunk);
            WorldChunk lastChunk = chunk;
            chunk.startingPoint = false;



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

        worlds.push_back(world);

    }

    void drawWalkableTiles()
    {
        if(worlds.empty())
            return;
        World &world = worlds.front();

        for(auto &walkable : world.walkableTiles)
        {
            shapes.createSquare(walkable.pos.x-10,walkable.pos.y-10,walkable.pos.x+10,walkable.pos.y+10,sf::Color::Blue);
        }
    }

    void drawWorld()
    {
        return;

        if(worlds.empty())
            return;
        World &world = worlds.front();

        int chunkCount = 0;
        for(auto &chunk : world.chunks)
        {
            chunkCount++;
            // Chunk Color based on type
            if(chunk.startingPoint)
                shapes.createSquare(chunk.pos.x,chunk.pos.y,chunk.pos.x+1024,chunk.pos.y+1024,sf::Color(0,0,100));
            else if(chunk.bonusChunk)
                shapes.createSquare(chunk.pos.x,chunk.pos.y,chunk.pos.x+1024,chunk.pos.y+1024,sf::Color(0,100,0));
            else if(chunk.deadEnd)
                shapes.createSquare(chunk.pos.x,chunk.pos.y,chunk.pos.x+1024,chunk.pos.y+1024,sf::Color(100,0,0));
            else
                shapes.createSquare(chunk.pos.x,chunk.pos.y,chunk.pos.x+1024,chunk.pos.y+1024,sf::Color(100,100,100));

            shapes.shapes.back().offscreenRender = true;

            chunk.drawTiles();

            // Open Path Waypoints

            if(chunk.paths.north)
                shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512,chunk.pos.y+512-512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
            if(chunk.paths.east)
                shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512+512,chunk.pos.y+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
            if(chunk.paths.south)
                shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512,chunk.pos.y+512+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
            if(chunk.paths.west)
                shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512-512,chunk.pos.y+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;


            shapes.createText(chunk.pos.x+512,chunk.pos.y+512,50,sf::Color::White,std::to_string(chunkCount));
            shapes.shapes.back().offscreenRender = true;

        }





    }
};
WorldManager worldManager;


class Trait
{
public:
    std::string name;
    int traitID;
    int stackable;

    enum traitIDs
    {
        Empty,
        Locked,
        HealingWounds,
        Armor,
        EnergyShield,
        EnergyShieldHardening,
        DemolitionsExpert,
        QuickRenewal,
        Sprinter
    };

};

class Player
{
public:

    std::string name;
    sf::Vector2f pos;
    sf::Vector2f lastValidPos;

    std::string classType;

    std::list<Trait> traits;
    void genBaseTraits()
    {
        Trait trait;
        trait.name = "Empty";
        trait.traitID = Trait::Empty;
        trait.stackable = 99999;
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);

        trait.name = "Locked";
        trait.traitID = Trait::Locked;
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);
        traits.push_back(trait);
    }



    float rotation;
    float rotationSpeed;
    sf::Vector2f rotationPoint;

    float health;
    float healthMax;
    float moveSpeed;
    float stamina;
    float staminaMax;
    float getStaminaMax()
    {
        return staminaMax;
    }
    bool isStillTired;
    bool isTired()
    {
        bool returnStatus = false;

        if(stamina > getStaminaMax()*0.25)
            isStillTired = false;

        if(stamina <= 0)
        {
            isStillTired = true;
            returnStatus = true;
        }

        if(isStillTired)
            returnStatus = true;

        return returnStatus;
    }

    unsigned int kills;
    unsigned int deaths;
    unsigned int reviveCount;
    unsigned int revivedCount;
    unsigned int missionsComplete;
    unsigned int missionsFailed;

    Player()
    {
        kills = 0;
        deaths = 0;
        reviveCount = 0;
        revivedCount = 0;
        missionsComplete = 0;
        missionsFailed = 0;
    }

};

class PlayerManager
{
public:
    std::list<Player> players;

    void runPlayerCharacterLogic()
    {

        if(players.empty())
            return;

        Player& player = players.back();

        { // Camera Lock
            //gvars::currentx = player.pos.x;
            //gvars::currenty = player.pos.y;
            gvars::view1.setCenter(player.pos);
        }

        { // Movement Code

            float xMovement = 0;
            float yMovement = 0;

            if(inputState.key[Key::W])
            {
                yMovement += -player.moveSpeed;
            }

            if(inputState.key[Key::A])
            {
                xMovement += -player.moveSpeed;
            }

            if(inputState.key[Key::S])
            {
                yMovement += player.moveSpeed;
            }

            if(inputState.key[Key::D])
            {
                xMovement += player.moveSpeed;
            }



            player.stamina = std::min(player.stamina+1,player.getStaminaMax());

            if(!player.isTired() && inputState.key[Key::LShift])
            {
                bool isRunning = false;

                if(inputState.key[Key::W])
                {
                    yMovement += -player.moveSpeed*3;
                    isRunning = true;
                }

                if(inputState.key[Key::A])
                {
                    xMovement += -player.moveSpeed*3;
                    isRunning = true;
                }

                if(inputState.key[Key::S])
                {
                    yMovement += player.moveSpeed*3;
                    isRunning = true;
                }

                if(inputState.key[Key::D])
                {
                    xMovement += player.moveSpeed*3;
                    isRunning = true;
                }

                if(isRunning)
                    player.stamina -= 2;

            }


            if(!worldManager.worlds.empty() && worldManager.worlds.back().isTileWalkable(sf::Vector2i(player.pos.x+xMovement,player.pos.y) ))
            {
                player.pos.x += xMovement;
                player.lastValidPos = player.pos;
            }

            if(!worldManager.worlds.empty() && worldManager.worlds.back().isTileWalkable(sf::Vector2i(player.pos.x,player.pos.y+yMovement) ))
            {
                player.pos.y += yMovement;
                player.lastValidPos = player.pos;
            }



        }




        { // Rotation Code
           player.rotationPoint = gvars::mousePos;

            int rotationDiff = math::angleDiff(player.rotation, math::angleBetweenVectors(player.pos,player.rotationPoint));
            int rotCheck = rotationDiff;
            if(rotCheck < 0)
                rotCheck = -rotCheck;

            if(rotCheck < player.rotationSpeed)
                player.rotation = math::angleBetweenVectors(player.pos,player.rotationPoint);
            else
            {
                if(rotationDiff > 0)
                    player.rotation += player.rotationSpeed;
                if(rotationDiff < 0)
                    player.rotation -= player.rotationSpeed;
            }
        }







    }

    void makePlayer()
    {
        Player player;
        player.pos = gvars::mousePos;
        player.healthMax = 100;
        player.health = player.healthMax;
        player.staminaMax = 1000;
        player.stamina = player.staminaMax;

        player.rotation = 0;
        player.rotationSpeed = 5;


        player.moveSpeed = 1;

        player.genBaseTraits();

        players.push_back(player);
    }

};
PlayerManager playerManager;

bool playerCamera()
{
    if(playerManager.players.empty())
        return false;

   gvars::view1.setCenter(playerManager.players.back().pos);

   return true;
}





bool chatCommand(std::string input)
{
    std::vector<std::string> elements;
    bool finished = false;
    sf::Color errorColor(100,100,100);
    sf::Color warmColor(255,150,150);
    sf::Color goodColor = sf::Color::White;
    size_t tStart = 0;
    size_t tEnd = 0;

    while(finished == false)
    {

        tEnd = input.find(" ",tStart);
        std::string injection;
        injection.append(input,tStart,tEnd-tStart);
        elements.push_back(injection);
        tStart = tEnd+1;
        if(tEnd == input.npos)
            finished = true;
    }
    std::cout << "input: " << input << std::endl;
    for(auto &i : elements)
    {
        std::cout << "elements: " << i << std::endl;
    }

    if(elements[0] == "/help" || elements[0] == "/info")
    {
        chatBox.addChat("Commands Available: /me, /setname, /loadCreature, /connect");

        // TODO: Add checks for each command after the /help command, I.E. /help /connect, and print info and what's required for it.
    }

    if(elements[0] == "/me"|| elements[0] == "/emote")
    {
        if(elements.size() < 2)
        {
            chatBox.addChat("Command: /me [action text]", errorColor);
            return false;
        }

        std::string sendText;
        sendText.append("* ");
        sendText.append(myProfile.name);
        sendText.append(" ");

        for(unsigned int i = 1; i != elements.size(); i++)
        {
            sendText.append(elements[i]);
            sendText.append(" ");
        }
        std::cout << "Final String: " << sendText << std::endl;



        sf::Packet sendPacket;
        sendPacket << sf::Uint8(ident::textMessage)
            << sendText;
        serverSocket.send(sendPacket);

    }

    if(elements[0] == "/name" || elements[0] == "/setname" || elements[0] == "/nick")
    {
        chatBox.addChat("Server: " + myProfile.name + " has changed their name to " + elements[1], goodColor);
        myProfile.name = elements[1];
        if(elements[1] == "Lithi" || elements[1] == "Biocava" || elements[1] == "Sneaky" || elements[1] == "SneakySnake")
            chatBox.addChat("Server: Ooo, Ooo, I like you!", warmColor);
        if(elements[1] == "Dehaku")
            chatBox.addChat("Server: Hey, that's my masters name!", warmColor);
        return true;
    }


    if(elements[0] == "/connect")
    {
        std::cout << "Connect chat command detected. \n";

        if(elements.size() == 1)
        {
            AddressContainer addCon;
            addCon = loadConnectAddress();
            if(addCon.address == "")
            {
                chatBox.addChat("The last entered address(if any) wasn't valid. ", errorColor);
                return false;
            }



            bool connectionBool = activateClient(addCon.address, std::stoi(addCon.port));
            if(connectionBool)
            {
                std::cout << "Connected to server " << addCon.address << std::endl;
                network::client = true;
                chatBox.addChat("Server: Connected to " + addCon.address + "(" + addCon.port + ")", goodColor);
                return true;
            }
            else
            {
                std::cout << "Failed to connect to " << addCon.address << std::endl;
                chatBox.addChat("Server: FAILED to connect to " + addCon.address + "(" + addCon.port + ")", goodColor);
                return false;
            }
        }


        if(elements.size() != 3)
        {
            std::cout << "Incorrect argument count, We have " << std::to_string(elements.size()) << " instead. \n";
            chatBox.addChat("Command: /connect [IP Address] [Port], Spaces, No colons.", errorColor);
            return false;
        }
        if(network::connectedServer != "")
        {
            chatBox.addChat("Server: Error, You're already connected to " + network::connectedServer, errorColor);
            return false;
        }
        if(myProfile.name == "Guest")
        {
            chatBox.addChat("Server: Error, please give yourself a name with /setname before attempting to connect.", errorColor);
            return false;
        }
        try
        {
            std::string tryString = elements[2];
            int test = std::stoi(tryString); // This is used, ignore the warning. It's a form of testing the entered string.
        }
        catch (std::exception &e)
        {
            std::cout << "Command: /connect [IP Address] [Port]" << std::endl;
            chatBox.addChat("Command: /connect [IP Address] [Port]", errorColor);
            return false;
        }

        bool connectionBool = activateClient(elements[1], std::stoi(elements[2]));
        if(connectionBool)
        {
            saveConnectAddress(elements[1],elements[2]);

            std::cout << "Connected to server " << elements[1] << std::endl;
            network::client = true;
            chatBox.addChat("Server: Connected to " + elements[1] + "(" + elements[2] + ")", goodColor);
            return true;
        }
        else
        {
            std::cout << "Failed to connect to " << elements[1] << std::endl;
            chatBox.addChat("Server: FAILED to connect to " + elements[1] + "(" + elements[2] + ")", goodColor);
            return false;
        }
    }
    /*


    else if(elements[0] == "/setname")
    {
        chatBox.addChat("Server: " + network::name + " has changed their name to " + elements[1], goodColor);
        network::name = elements[1];
        if(elements[1] == "Lithi" || elements[1] == "Biocava" || elements[1] == "Sneaky" || elements[1] == "SneakySnake")
            chatBox.addChat("Server: Ooo, Ooo, I like you!", warmColor);
        if(elements[1] == "Argwm" || elements[1] == "Dehaku")
            chatBox.addChat("Server: Hey, that's my masters name!", warmColor);
        return true;
    }
    else if(elements[0] == "/repeat")
    {
        try
        {
            int test = std::stoi(elements[1]);
        }
        catch (std::exception &e)
        {
            chatBox.addChat("Invalid argument: " + elements[1] + " in command " + input, errorColor);
            chatBox.addChat("Command: /repeat [numberoftimes] [series of words or numbers]", errorColor);
            return false;
        }
        std::string repeatingLine;
        for(int i = 0; i != elements.size(); i++)
        {
            if(i != 0 && i != 1)
            {
                repeatingLine.append(elements[i] + " ");
            }
        }
        for(int i = 0; i != std::stoi(elements[1]); i++)
        {
            chatBox.addChat("Server: Repeating; " + repeatingLine, goodColor);
        }
        return true;
    }

    chatBox.addChat("Unrecognized command: " + input, errorColor);

    */
    return false;
}


void clientPacketManager::handlePackets()
{
    for(auto &currentPacket : packets)
    {


        sf::Packet &packet = currentPacket.packet;
        byteKeeper.byteInput(packet);


        sf::Uint8 type;
        packet >> type;
        //std::cout << "P: " << int(type) << std::endl;


        if(type == sf::Uint8(ident::textMessage))
        {
            std::string chatLine;
            packet >> chatLine;
            chatBox.addChat(chatLine);
        }

        if(type == sf::Uint8(ident::message))
        {
            std::string in;
            packet >> in;
            std::cout << "Server" << int(type) << ": \"" << in << "\"" << std::endl;
        }

        else if(type == sf::Uint8(ident::initialization))
        {
            std::cout << "Received initialization, ";
            int simCount;
            packet >> simCount;
            std::cout << simCount << " simulations." << std::endl;

            for(int i = 0; i != simCount; i++) // We know all the currently running sims, now we request them all individually.
            {
                sf::Packet sendPacket;
                sendPacket << sf::Uint8(ident::simulationRequest);

                // Take out the ID from the packet, and send it back with the request.
                sf::Uint32 simID;
                packet >> simID;
                sendPacket << simID;
                serverSocket.send(sendPacket);
                std::cout << "Requested Sim " << int(simID) << std::endl;
            }

            // TODO: Send/receive players connected here.

        }


        else if(type == sf::Uint8(ident::clientID) )
        {
            std::cout << "Received our ID: ";
            packet >> myProfile.ID;
            std::cout << int(myProfile.ID) << std::endl;



            std::cout << "Requesting initialization\n";
            sf::Packet requestPacket;
            requestPacket << sf::Uint8(ident::initialization) << myProfile.ID;
            serverSocket.send(requestPacket);
        }
    }
    packets.clear();
}

void serverPacketManager::handlePackets()
{
    for(auto &currentPacket : packets)
    {
        sf::Packet &packet = currentPacket.packet;
        byteKeeper.byteInput(packet);

        sf::Uint8 type;
        packet >> type;


        if(type == sf::Uint8(ident::textMessage))
        {
            std::string chatLine;
            packet >> chatLine;
            chatBox.addChat(chatLine);

            sf::Packet returnPacket;
            returnPacket << sf::Uint8(ident::textMessage)
            << chatLine;
            sendToAllClients(returnPacket);
        }
        else if(type == sf::Uint8(ident::message))
        {
            std::string in;
            packet >> in;
            std::cout << "Client" << int(type) << ": \"" << in << "\"" << std::endl;
        }

        else if(type == sf::Uint8(ident::initialization))
        {
            std::cout << "Initialization 'Request' received from " << int(currentPacket.sender->id) << std::endl;
            sf::Packet sendPacket;

            // Send the same type back.
            /*

            sendPacket << type;
            sendPacket << sf::Uint32(simulationManager.simulations.size());

            for(auto &sim : simulationManager.simulations)
            {
                sendPacket << sf::Uint32(sim.simulationID);
                std::cout << "Sent " << sim.simulationID << std::endl;
            }

            */

            // TODO: Send/receive players connected here.

            currentPacket.sender->socket->send(sendPacket);
        }

        else if(type == sf::Uint8(ident::clientID) )
        {
            std::cout << "ID Request received. \n";
            sf::Uint8 sillyID;
            packet >> sillyID; // Placeholder for login/profile info.

            sf::Packet returnPacket;
            // Send them the ID assigned to them when they joined.

            returnPacket << sf::Uint8(ident::clientID) << currentPacket.sender->id;

            currentPacket.sender->socket->send(returnPacket);
        }
    }
    packets.clear();
}

void gameSetup()
{
    texturemanager.init();


}

void testFunction()
{
    std::cout << "Test! \n";
}

void HUDTabs()
{
    static sf::Texture* hudButton;
    if(hudButton == nullptr)
        hudButton = &texturemanager.getTexture("HUDTab.png");

    int workDudeButt = shapes.createImageButton(sf::Vector2f(-33,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(-33-40,190-8,12,sf::Color::White,"Jobs",&gvars::hudView);
    int evolutionButt = shapes.createImageButton(sf::Vector2f(179,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(179-40,190-8,12,sf::Color::White,"Runners",&gvars::hudView);


    std::string simAddon = "";



    int simulationButt = shapes.createImageButton(sf::Vector2f(391,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(391-40,190-8,12,sf::Color::White,"???"+simAddon,&gvars::hudView);
    int contestButt = shapes.createImageButton(sf::Vector2f(606,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(606-40,190-8,12,sf::Color::White,"???",&gvars::hudView);
    int shopButt = shapes.createImageButton(sf::Vector2f(818,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(818-40,190-8,12,sf::Color::White,"Shops",&gvars::hudView);
    int archiveButt = shapes.createImageButton(sf::Vector2f(1030,190),*hudButton,"",0,&gvars::hudView);
    shapes.createText(1030-40,190-8,12,sf::Color::White,"Archive",&gvars::hudView);


    if(shapes.shapeClicked(workDudeButt))
    {
        std::cout << "Workdude clicked! \n";

        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.quests;

        //sf::sleep(sf::seconds(2));
    }
    if(shapes.shapeClicked(evolutionButt))
    {
        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.evolution;
    }
    if(shapes.shapeClicked(simulationButt))
    {
        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.simulation;

    }

    if(shapes.shapeClicked(contestButt))
    {
        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.contest;
    }
    if(shapes.shapeClicked(shopButt))
    {
        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.shops;
    }
    if(shapes.shapeClicked(archiveButt))
    {
        stateTracker.lastState = stateTracker.currentState;
        stateTracker.currentState = stateTracker.archive;
    }


    if(shapes.shapeHovered(workDudeButt))
    {
        int posX = -33;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(evolutionButt))
    {
        int posX = 179;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(simulationButt))
    {
        int posX = 391;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);


    }
    if(shapes.shapeHovered(contestButt))
    {
        int posX = 606;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(shopButt))
    {
        int posX = 818;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(archiveButt))
    {
        int posX = 1030;
        int posY = 190;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }


}

void drawHUD()
{

    static sf::Texture* mainHud;
    if(mainHud == nullptr)
        mainHud = &texturemanager.getTexture("MainHUD.png");

    // -281, 283
    shapes.createImageButton(sf::Vector2f((1280+(-281))/2,(720+283)/2),*mainHud,"",0,&gvars::hudView);

    HUDTabs();

}

void drawFPSandData()
{
    int yOffset = 21;
    { // FPS/UPS Richtext Display
        sfe::RichText fpsText(gvars::defaultFont);
        fpsText.setPosition(-130,10*yOffset);
        yOffset++;
        fpsText.setCharacterSize(10);
        fpsText << sf::Text::Bold << sf::Color::White << "FPS/UPS:" ;

        if(fpsKeeper.framesPerSecond < 60)
            fpsText << sf::Color::Red << std::to_string(int(fpsKeeper.framesPerSecond));
        else
            fpsText << sf::Color::White << std::to_string(int(fpsKeeper.framesPerSecond));

        fpsText << sf::Color::White << "/";

        if(fpsKeeper.updatesPerSecond > 10000)
            fpsText << sf::Color::Red << std::to_string(int(fpsKeeper.updatesPerSecond));
        else
            fpsText << sf::Color::White << std::to_string(int(fpsKeeper.updatesPerSecond));

        shapes.createRichText(fpsText, &gvars::hudView);
    }

    shapes.createText(-130,10*yOffset,10,sf::Color::White, "Data: "
                      + std::to_string(int(byteKeeper.bytesPerSecond)) + " B/s, "
                      + std::to_string(int(byteKeeper.bytesCollected)) + " B, "
                      + std::to_string(int(byteKeeper.kilobytesCollected)) + " KB, "
                      + std::to_string(int(byteKeeper.megabytesCollected)) + " MB, "
                      + std::to_string(int(byteKeeper.gigabytesCollected)) + " GB"
                      , &gvars::hudView);
    yOffset++;

    shapes.createText(-130,10*yOffset,10,sf::Color::White, "Zoom: "
                      + std::to_string(gvars::cameraZoom)
                      , &gvars::hudView);
    yOffset++;
}

void drawChat()
{

    int xDraw = 200-332;
    int yDraw = 200+637;


    // The Chatbox History
    {
        int yOffset = 0;


        //std::cout << "ChatSize: " << std::max(chatBox.chatStorage.size()-10,0) << std::endl;

        //for(int i = chatBox.chatStorage.size(); (i != 0 && i >= chatBox.chatStorage.size()-10); i--)
        for(unsigned int i = chatBox.chatStorage.size()-1; i >= chatBox.chatStorage.size()-10; i--)
        {

            sfe::RichText chatText(gvars::defaultFont);

            chatText.setPosition(xDraw,(yDraw-15)-(15*yOffset));
            //chatText.setPosition(300,300);
            chatText.setCharacterSize(15);

            chatText << chatBox.chatStorage[i].color
            << sf::Text::Regular << chatBox.chatStorage[i].line;

            shapes.createRichText(chatText, &gvars::hudView);
            yOffset++;

            if(i <= 0)
                break;
        }
    }








    // Our entered text

    sfe::RichText chatText(gvars::defaultFont);

    chatText.setPosition(xDraw,yDraw);
    chatText.setCharacterSize(15);

    chatText << sf::Color::White
    << sf::Text::Bold << myProfile.name << ": "
    << sf::Text::Regular << chatBox.chatString;

    // TODO: Enhance the chat to accept ^89 colors and such, ala Toribash.

    if(network::chatting)
    {
        // int chatGrowth = chatText.getLocalBounds().width;
        shapes.createSquare(xDraw-10,yDraw,xDraw+1200,yDraw+22,sf::Color(0,0,0,100),0,sf::Color::Transparent, &gvars::hudView);

        shapes.createRichText(chatText, &gvars::hudView);
    }
}

void drawMainMenu()
{
    shapes.createImageButton(sf::Vector2f(500,500),texturemanager.getTexture("DaemonRunnersMain.png"),"",0,&gvars::hudView);

    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");


    int startButt = shapes.createImageButton(sf::Vector2f(-33,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(-33-40,843-8,12,sf::Color::White,"Start Game",&gvars::hudView);

    int multiplayerButt = shapes.createImageButton(sf::Vector2f(179,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(179-40,843-8,12,sf::Color::White,"Multiplayer",&gvars::hudView);

    int profileButt = shapes.createImageButton(sf::Vector2f(391,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(391-40,843-8,12,sf::Color::White,"Profile",&gvars::hudView);

    int optionsButt = shapes.createImageButton(sf::Vector2f(606,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(606-40,843-8,12,sf::Color::White,"Options",&gvars::hudView);

    int creditsButt = shapes.createImageButton(sf::Vector2f(818,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(818-40,843-8,12,sf::Color::White,"Credits",&gvars::hudView);

    int exitButt = shapes.createImageButton(sf::Vector2f(1030,843),*hudButton,"",0,&gvars::hudView);
    shapes.createText(1030-40,843-8,12,sf::Color::White,"Quit",&gvars::hudView);


    if(shapes.shapeClicked(startButt))
    {
        stateTracker.currentState = stateTracker.mainLoop;
    }
    if(shapes.shapeClicked(multiplayerButt))
    {
        stateTracker.currentState = stateTracker.multiplayer;
    }
    if(shapes.shapeClicked(profileButt))
    {
        stateTracker.currentState = stateTracker.profile;
    }
    if(shapes.shapeClicked(optionsButt))
    {
        stateTracker.currentState = stateTracker.options;
    }
    if(shapes.shapeClicked(creditsButt))
    {
        stateTracker.currentState = stateTracker.credits;
    }
    if(shapes.shapeClicked(exitButt))
    {
        saveProfile("Sopheroph");
        window.close();
    }



    int posY = 843;
    if(shapes.shapeHovered(startButt))
    {
        int posX = -33;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(multiplayerButt))
    {
        int posX = 179;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(profileButt))
    {
        int posX = 391;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);



    }
    if(shapes.shapeHovered(optionsButt))
    {
        int posX = 606;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(creditsButt))
    {
        int posX = 818;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }
    if(shapes.shapeHovered(exitButt))
    {
        int posX = 1030;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }



}

void simulationMenu()
{
    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");
    sf::Texture* arrowButton = &texturemanager.getTexture("ArrowButton.png");








    sf::Vector2f createPos(-33,270);
    int createButt = shapes.createImageButton(sf::Vector2f(createPos.x,createPos.y),*hudButton,"",0,&gvars::hudView);
    shapes.createText(createPos.x-40,createPos.y-8,12,sf::Color::White,"Create Simulation",&gvars::hudView);
    if(shapes.shapeHovered(createButt))
    {
        if(inputState.lmbTime == 1)
        {
            // Simulation* createdSim = simulationManager.createSimulation();

            if(network::server)
            {
                /*

                sf::Packet returnPacket;
                returnPacket << sf::Uint8(ident::simulationInitialization);
                returnPacket << *createdSim;
                sendToAllClients(returnPacket);

                std::cout << "Sent Simulation to All Clients. \n";

                */
            }
        }
    }


    sf::Vector2f simListPos(191,291);
    // int yOffset = 0;
    // int simCounter = 0;






}

void jobsMenu()
{
    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");
    sf::Texture* arrowButton = &texturemanager.getTexture("ArrowButton.png");
    if(worldManager.worlds.empty())
    {
        worldManager.generateWorld(20,100);
    }

    worldManager.drawWorld();

    if(inputState.key[Key::X].time == 1)
        worldManager.worlds.clear();

    drawChat();
    drawFPSandData();

}

void runnersMenu()
{
    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");
    sf::Texture* arrowButton = &texturemanager.getTexture("ArrowButton.png");

    if(playerManager.players.empty())
        return;

    Player &player = playerManager.players.back();


         static int xMod = 0;
            static int yMod = 0;
            std::cout << "X/Y Mod: " << xMod << "/" << yMod << std::endl;
            if(inputState.key[Key::Up].time == 1 || inputState.key[Key::Up].time >= 15)
                yMod--;
            if(inputState.key[Key::Down].time == 1 || inputState.key[Key::Down].time >= 15)
                yMod++;
            if(inputState.key[Key::Left].time == 1 || inputState.key[Key::Left].time >= 15)
                xMod--;
            if(inputState.key[Key::Right].time == 1 || inputState.key[Key::Right].time >= 15)
                xMod++;


    sf::Vector2f HUDPos(-141, 254);

    shapes.createText(HUDPos.x+15+xMod,HUDPos.y+15+yMod,15,sf::Color::White,"Name: " + player.name, &gvars::hudView);
    shapes.createText(HUDPos.x+15,HUDPos.y+30,15,sf::Color::White,"Class: " + player.classType, &gvars::hudView);


    int traitOffset = 0;
    for(auto &trait : player.traits)
    {
        shapes.createText(HUDPos.x+15,HUDPos.y+45+(15*traitOffset),15,sf::Color::White,"Trait: " + trait.name, &gvars::hudView);
        traitOffset++;
    }

    shapes.createText(HUDPos.x+200,HUDPos.y+15,15,sf::Color::White,"*Stats* ", &gvars::hudView);

    shapes.createText(HUDPos.x+200,HUDPos.y+30,15,sf::Color::White,"* Move Speed: " + std::to_string(player.moveSpeed), &gvars::hudView);
    shapes.createText(HUDPos.x+200,HUDPos.y+45,15,sf::Color::White,"* Max Stamina: " + std::to_string((int) player.getStaminaMax()), &gvars::hudView);
    shapes.createText(HUDPos.x+200,HUDPos.y+60,15,sf::Color::White,"* Max Health: " + std::to_string((int) player.healthMax), &gvars::hudView);


    shapes.createText(HUDPos.x+200,HUDPos.y+90,15,sf::Color::White,"* Melee Damage: ???", &gvars::hudView);
    shapes.createText(HUDPos.x+200,HUDPos.y+105,15,sf::Color::White,"* Range Damage: ???", &gvars::hudView);

    shapes.createText(HUDPos.x+200,HUDPos.y+300,15,sf::Color::White,"* Kills/Deaths: " + std::to_string(player.kills) + "/" + std::to_string(player.deaths), &gvars::hudView);
    shapes.createText(HUDPos.x+200,HUDPos.y+315,15,sf::Color::White,"* Revives(ed): " + std::to_string(player.reviveCount) + "/" + std::to_string(player.revivedCount), &gvars::hudView);
    shapes.createText(HUDPos.x+200,HUDPos.y+330,15,sf::Color::White,"* Missions Win/Lost: " + std::to_string(player.missionsComplete) + "/" + std::to_string(player.missionsFailed), &gvars::hudView);
    //player.




    drawChat();
    drawFPSandData();

}

void drawSubMain()
{

    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");


    int mainButt = shapes.createImageButton(sf::Vector2f(-33,170),*hudButton,"",0,&gvars::hudView);
    shapes.createText(-33-40,170-8,12,sf::Color::White,"Back",&gvars::hudView);
    if(shapes.shapeClicked(mainButt))
    {
        stateTracker.currentState = stateTracker.lastState;
    }
    if(shapes.shapeHovered(mainButt))
    {
        int posX = -33;
        int posY = 170;
        shapes.createSquare(posX-105,posY-15,posX+106,posY+15,sf::Color(255,255,255,150),0,sf::Color::White,&gvars::hudView);
    }


    if(stateTracker.currentState == stateTracker.multiplayer)
    {
        shapes.createText(500,150,20,sf::Color::Cyan,"Multiplayer",&gvars::hudView);
    }
    if(stateTracker.currentState == stateTracker.profile)
    {
        shapes.createText(500,150,20,sf::Color::Cyan,"Profile",&gvars::hudView);

        shapes.createText(300,200,12,sf::Color::Cyan,"Name: " + myProfile.name,&gvars::hudView);
        shapes.createText(300,215,10,sf::Color::Cyan,"You can change your name while playing by pressing Enter, then /setname yourname",&gvars::hudView);
        shapes.createText(300,230,12,sf::Color::Cyan,"Credits: " + std::to_string(myProfile.credits),&gvars::hudView);
        shapes.createText(300,245,12,sf::Color::Cyan,"Pix: " + std::to_string(myProfile.pix),&gvars::hudView);
    }
    if(stateTracker.currentState == stateTracker.options)
    {
        shapes.createText(500,150,20,sf::Color::Cyan,"Options",&gvars::hudView);

        sf::Vector2f textPos(500,200);
        sf::Vector2f buttonPos;


        buttonPos = textPos;
        shapes.createText(textPos,10,sf::Color::White,"Resolution: "
                            + std::to_string(resolution.resolutions[resolution.currentRes].width)
                            +"/"+std::to_string(resolution.resolutions[resolution.currentRes].height)
                            +": "+std::to_string(resolution.resolutions[resolution.currentRes].bitsPerPixel)
                            +"\n \n \nFullscreen: " + str(resolution.fullscreen)
                            ,&gvars::hudView);
        shapes.shapes.back().layer = 15075;

        buttonPos.x += 90;
        buttonPos.y += 20;
        int decreaseResolution = shapes.createImageButton(buttonPos,texturemanager.getTexture("ArrowButton.png"),"",-90,&gvars::hudView);
        shapes.shapes.back().layer = 15050;
        buttonPos.x += 30;
        int increaseResolution = shapes.createImageButton(buttonPos,texturemanager.getTexture("ArrowButton.png"),"",90,&gvars::hudView);
        shapes.shapes.back().layer = 15050;
        buttonPos.x += 30;
        int applyResolution = shapes.createImageButton(buttonPos,texturemanager.getTexture("ArrowButton.png"),"",180,&gvars::hudView);
        shapes.shapes.back().layer = 15050;

        buttonPos.y += 20;
        int toggleFullscreen = shapes.createImageButton(buttonPos,texturemanager.getTexture("ArrowButton.png"),"",180,&gvars::hudView);
        shapes.shapes.back().layer = 15050;




        // Warning, the increase and decrease resolution buttons are backwards, since the videomode put the highest res in first, and the smallest last.
        if(shapes.shapeHovered(increaseResolution) && (inputState.lmbTime == 1))
            if(resolution.currentRes > 0)
                resolution.currentRes--;
        if(shapes.shapeHovered(decreaseResolution) && (inputState.lmbTime == 1))
            if(resolution.currentRes < resolution.resolutions.size()-1)
                resolution.currentRes++;

        if(shapes.shapeHovered(toggleFullscreen))
        {
            shapes.createText(gvars::mousePos,9,sf::Color::White,"  Toggle fullscreen");
            shapes.shapes.back().layer = 15075;
            if((inputState.lmbTime == 1))
                toggle(resolution.fullscreen);
        }


        if(shapes.shapeHovered(applyResolution))
        {
            shapes.createText(gvars::mousePos,9,sf::Color::White,"  Apply the Resolution!",&gvars::hudView);
            shapes.shapes.back().layer = 15075;

            if(inputState.lmbTime == 1)
            {
                if(resolution.fullscreen)
                    window.create(resolution.resolutions[resolution.currentRes], randomWindowName(),sf::Style::Fullscreen);
                else
                    window.create(resolution.resolutions[resolution.currentRes], randomWindowName());
            }

        }



    }
    if(stateTracker.currentState == stateTracker.credits)
    {
        shapes.createText(500,150,20,sf::Color::Cyan,"Credits",&gvars::hudView);
    }

    if(stateTracker.currentState == stateTracker.quests)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Jobs",&gvars::hudView);
        jobsMenu();
    }
    if(stateTracker.currentState == stateTracker.evolution)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Runners",&gvars::hudView);
        runnersMenu();
    }
    if(stateTracker.currentState == stateTracker.simulation)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Simulation",&gvars::hudView);
        simulationMenu();
    }
    if(stateTracker.currentState == stateTracker.contest)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Contests",&gvars::hudView);
    }
    if(stateTracker.currentState == stateTracker.shops)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Shops",&gvars::hudView);
    }
    if(stateTracker.currentState == stateTracker.archive)
    {
        drawHUD();
        shapes.createText(500,210,20,sf::Color::Cyan,"Archives",&gvars::hudView);
    }





}

void chatStuffs()
{
    { // Old Entered Text Cycle for Chatbox.
        if(!network::chatting)
            myProfile.enteredStringAimer = myProfile.enteredStrings.size();
        else
        {
            if(myProfile.enteredStrings.empty())
                return;
            if(!network::chatting)
                return;


            bool arrowPressed = false;
            if(inputState.key[Key::Up].time == 1)
            {
                arrowPressed = true;
                    if(myProfile.enteredStringAimer == myProfile.enteredStrings.size())
                        myProfile.enteredStringAimer--;
                    else if(myProfile.enteredStringAimer != 0)
                    {
                        myProfile.enteredStringAimer--;
                    }
            }

            if(inputState.key[Key::Down].time == 1)
            {
                arrowPressed = true;
                if(chatBox.chatString == "")
                    arrowPressed = false;


                    if(myProfile.enteredStringAimer == myProfile.enteredStrings.size()-1)
                    {
                        chatBox.chatString = "";
                        arrowPressed = false;
                        myProfile.enteredStringAimer = myProfile.enteredStrings.size();
                    }
                    else if(myProfile.enteredStringAimer < myProfile.enteredStrings.size()-1)
                    {
                        myProfile.enteredStringAimer++;
                    }
            }

            if(arrowPressed)
                chatBox.chatString = myProfile.enteredStrings[myProfile.enteredStringAimer];
        }

    }

}


void generalFunctions()
{
    // QTTreeToTree();
    if(inputState.key[Key::PageUp])
        sf::sleep(sf::seconds(1));


    if(inputState.key[Key::Y].time == 1)
        worldManager.worlds.back().printWalkables();




    if(inputState.key[Key::LControl] && inputState.lmbTime == 1)
    {

        playerManager.makePlayer();

    }







}

void generalFunctionsPostRender()
{


    /*
    if(simulationManager.getCurrentSimulation() != nullptr)
    {
        sf::Clock speedClock;
        sf::Time speedTime;
        speedClock.restart();

        Simulation &sim = *simulationManager.getCurrentSimulation();
        for(auto &planty : sim.flora)
        {
            Organism &plant = *planty.get();

            static AABB plantRange;
            plantRange.centre = plant.pos;
            plantRange.halfSize = sf::Vector2f(100,100);

            std::vector<Data<std::shared_ptr<Organism>>> closeOnes = sim.floraQT.queryRange(plantRange);

            for(auto nearCrit : closeOnes)
            {
                std::shared_ptr<Organism>& crit = *nearCrit.load;

                if(math::distance(plant.pos,crit->pos) <= 50)
                {
                    if(inputState.key[Key::Comma])
                    {
                        shapes.createLine(crit->pos.x,crit->pos.y,plant.pos.x,plant.pos.y,1,sf::Color::Cyan);
                    }
                }


            }

        }

        speedTime = speedClock.restart();
        std::cout << "Speed Time: " << speedTime.asMicroseconds() << std::endl;


    }
    */
}

void drawWorld()
{
    if(worldManager.worlds.empty())
        return;

    World &world = worldManager.worlds.back();

    static sf::Texture &wallTex = texturemanager.getTexture("GenericWall.png");
    static sf::Texture &floorTex = texturemanager.getTexture("GenericFloor.png");
    static sf::Texture &weakfenceTex = texturemanager.getTexture("GenericWeakFence.png");

    static sf::Sprite wallSprite;
    static sf::Sprite floorSprite;
    static sf::Sprite weakfenceSprite;

    {
        if(wallSprite.getTexture() == nullptr)
        {
            wallSprite.setTexture(wallTex);
            wallSprite.setOrigin(16,16);
        }
        if(floorSprite.getTexture() == nullptr)
        {
            floorSprite.setTexture(floorTex);
            floorSprite.setOrigin(16,16);
        }
        if(weakfenceSprite.getTexture() == nullptr)
        {
            weakfenceSprite.setTexture(weakfenceTex);
            weakfenceSprite.setOrigin(16,16);
        }

    }


    sf::View oldView = window.getView();
    window.setView(gvars::view1);

    int chunkCount = 0;
    for(auto &chunk : world.chunks)
    {
        chunkCount++;

        sf::Color chunkColor = sf::Color::White;
        if(chunk.deadEnd)
            chunkColor = sf::Color(250,200,200);
        if(chunk.startingPoint)
            chunkColor = sf::Color(200,200,250);
        if(chunk.bonusChunk)
            chunkColor = sf::Color(200,250,200);

        for(int i = 0; i != 32; i++)
            for(int t = 0; t != 32; t++)
        {
            sf::Vector2f drawPos(chunk.pos.x+(i*32),chunk.pos.y+(t*32));

            if(!onScreen(drawPos,20))
                continue;

            if(chunk.tiles[i][t].type == ChunkTile::WALL)
            {
                wallSprite.setPosition(drawPos);
                wallSprite.setColor(chunkColor);
                window.draw(wallSprite);
                //shapes.createImageButton(drawPos,wallTex);
                //shapes.shapes.back().maincolor = chunkColor;
            }



            if(chunk.tiles[i][t].type == ChunkTile::FLOOR)
            {
                floorSprite.setPosition(drawPos);
                floorSprite.setColor(chunkColor);
                window.draw(floorSprite);
            }

            if(chunk.tiles[i][t].type == ChunkTile::WEAKFENCE)
            {
                weakfenceSprite.setPosition(drawPos);
                weakfenceSprite.setColor(chunkColor);
                window.draw(weakfenceSprite);
            }

        }


        if(chunk.paths.north)
        {
            shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512,chunk.pos.y+512-512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
        }


        if(chunk.paths.east)
        {
            shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512+512,chunk.pos.y+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
        }


        if(chunk.paths.south)
        {
            shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512,chunk.pos.y+512+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
        }


        if(chunk.paths.west)
        {
            shapes.createLine(chunk.pos.x+512,chunk.pos.y+512,chunk.pos.x+512-512,chunk.pos.y+512,20,sf::Color::Blue);
            shapes.shapes.back().offscreenRender = true;
        }



        shapes.createText(chunk.pos.x+512,chunk.pos.y+512,50,sf::Color::White,std::to_string(chunkCount));
        shapes.shapes.back().offscreenRender = true;







    }

    window.setView(oldView);

}

void drawPlayers()
{
    static sf::Texture& angelTex = texturemanager.getTexture("Angel.png");
    static sf::Sprite angelSprite;
    if(angelSprite.getTexture() == nullptr)
    {
        angelSprite.setTexture(angelTex);
        angelSprite.setOrigin(angelTex.getSize().x/2,angelTex.getSize().y/2);
    }


    // Setting View
    sf::View oldView = window.getView();
    window.setView(gvars::view1);

    // Render stuffs
    for(auto &player : playerManager.players)
    {
        angelSprite.setPosition(player.pos);
        angelSprite.setRotation(player.rotation+90);
        window.draw(angelSprite);


        std::string staminaString;
        staminaString.append(std::to_string( (int) player.stamina) );
        staminaString.append("/");
        staminaString.append(std::to_string( (int) player.staminaMax));

        if(player.isTired())
            shapes.createText(player.pos.x,player.pos.y+25,10,sf::Color(100,100,100),staminaString);
        else
            shapes.createText(player.pos.x,player.pos.y+25,10,sf::Color::Yellow,staminaString);

    }

    // Fixing View
    window.setView(oldView);
}

void renderGame()
{

    drawWorld();

    if(inputState.key[Key::E])
        worldManager.drawWalkableTiles();

    drawPlayers();

    generalFunctions();

    chatStuffs();



    if(inputState.key[Key::Space].time == 1)
    {
        gvars::currentx = 20;
        gvars::currenty = 20;
    }

    if(stateTracker.currentState == stateTracker.mainMenu)
    {
        drawMainMenu();
    }
    else if(stateTracker.currentState == stateTracker.mainLoop)
    {




        drawHUD();
        drawFPSandData();
        drawChat();
    }
    else
    {
        drawSubMain();
    }





    /*
    if(inputState.key[Key::J])
    {

        shapes.createSquare(gvars::mousePos.x-100,gvars::mousePos.y-100,gvars::mousePos.x+100,gvars::mousePos.y+100,sf::Color::Transparent,1,sf::Color::Cyan);

        AABB getPos = AABB(gvars::mousePos,sf::Vector2f(100,100));
        std::vector<Data<std::shared_ptr<Organism>>> closeOnes = simulationManager.getCurrentSimulation()->organismsQT.queryRange(getPos);

        for(auto nearCrit : closeOnes)
        {
            std::shared_ptr<Organism>& crit = *nearCrit.load;

            shapes.createLine(crit->pos.x,crit->pos.y,gvars::mousePos.x,gvars::mousePos.y,1,sf::Color::Cyan);
        }


    }
    */



    generalFunctionsPostRender();

}

sf::Thread serverListenThread(&serverListen);
sf::Thread clientListenThread(&clientListen);


void runOneSecond()
{

}

void runTenSecond()
{

}

void runOneMinute()
{

}

void runServerStuffs()
{
    if(inputState.key[Key::Home].time == 1)
    {
        network::server = true;
        activateServer();
    }

    if(inputState.key[Key::End].time == 1)
    {
        network::client = true;
        activateClient("127.0.0.1",23636);
    }

    if(network::server && !network::listening)
    {
        network::listening = true;
        serverListenThread.launch();
    }
    if(network::client && !network::listening)
    {
        network::listening = true;
        // clientListen();
        clientListenThread.launch();
        // network::listening = false;
    }

    if(network::client)
    {
        { // Locking and sorting through the packets!
            sf::Lock lock(network::packetManagerHandling);
            cPM.handlePackets();
        }

        if(inputState.key[Key::V].time == 1 && inputState.key[Key::LShift].time == 0)
            clientSendingPing();
        if(inputState.key[Key::V].time == 1 && inputState.key[Key::LShift].time >= 1)
            for(int i = 0; i != 10; i++)
                clientSendingPing();
    }


    if(network::server)
    {
        { // Locking and sorting through the packets!
            sf::Lock lock(network::packetManagerHandling);
            sPM.handlePackets();
        }

        if(inputState.key[Key::V].time == 1 && inputState.key[Key::LShift].time == 0)
            serverPingAll();
        if(inputState.key[Key::V].time == 1 && inputState.key[Key::LShift].time >= 1)
            for(int i = 0; i != 10; i++)
                serverPingAll();

        if(inputState.key[Key::B].time == 1)
            std::cout << "Clients: " << clientCount() << std::endl;

    }


    // The Time Zone, tee hee.
    static bool oneSecondPassed = false;
    static sf::Clock oneSecondTimer;
    if(oneSecondTimer.getElapsedTime().asSeconds() > 1)
    {
        oneSecondTimer.restart();
        oneSecondPassed = true;
    }

    static bool tenSecondPassed = false;
    static sf::Clock tenSecondTimer;
    if(tenSecondTimer.getElapsedTime().asSeconds() > 10)
    {
        tenSecondTimer.restart();
        tenSecondPassed = true;
    }

    static bool oneMinutePassed = false;
    static sf::Clock oneMinuteTimer;
    if(oneMinuteTimer.getElapsedTime().asSeconds() > 60)
    {
        oneMinuteTimer.restart();
        oneMinutePassed = true;
    }


    if(oneSecondPassed)
    {
        runOneSecond();
        oneSecondPassed = false;

        // if(network::server)
        //    sendLifeUpdate();
        //std::cout << "One Second Passed! \n";
    }
    if(tenSecondPassed)
    {
        runTenSecond();
        tenSecondPassed = false;


        //std::cout << "Ten Seconds Passed! \n";
    }
    if(oneMinutePassed)
    {
        runOneMinute();
        oneMinutePassed = false;
        //std::cout << "One Minute Passed! \n";
    }


    if(inputState.key[Key::X].time == 1)
        std::cout << "Breakin console. \n";


}






void runGame()
{
    static int globalCycle = 0;
    globalCycle++;

    playerManager.runPlayerCharacterLogic();




    if((globalCycle % 60) == 0)
    {

    }

}
