#include "Tiles.h"

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




    for(int i = 0; i != 32; i++)
        for(int t = 0; t != 32; t++)
    {
        tiles[i][t].pos = sf::Vector2f(pos.x+(i*32),pos.y+(t*32));
    }



}


WorldManager worldManager;

WorldTile::WorldTile()
{

    // 107, 64, 0

    int ran = random(1,10);
    if(ran <= 2)
    { // 20% Water
        isWater = true;
        color = sf::Color(0,0,150);
        moveSpeedModifier = 0.8;
        temperature = random(0,110);

    }
    else if (ran <= 4)
    { // 20% Rocky
        isWater = false;
        color = sf::Color(120,120,120);
        moveSpeedModifier = 0.5;
        temperature = random(0,50);
    }
    else if (ran <= 6)
    { // 20% Desert
        isWater = false;
        color = sf::Color(180,180,60);
        moveSpeedModifier = 1.2;
        temperature = random(90,110);
    }
    else
    { // The rest is dirt.
        isWater = false;
        color = sf::Color(107,64,0);
        moveSpeedModifier = 1;
        temperature = random(40,80);
    }
}

std::vector<std::vector<WorldTile>> worldTiles;

void resizeWorld(int x, int y, std::vector<std::vector<WorldTile>>& worldlies)
{
    worldlies.resize(x);

    for(int i = 0; i != x; i++)
    {
        worldlies.at(i).resize(y);
    }
}

void worldTilesSetup(std::vector<std::vector<WorldTile>>& worldlies)
{
    resizeWorld(10,10,worldlies);

    std::cout << "W: " << worldlies.size();
    std::cout << "0: " << worldlies[0].size()
    << std::endl;
    //std::cout << "1: " << worldlies[0][0].size();

    for(unsigned int i = 0; i != worldlies.size(); i++)
    {
        for(unsigned int t = 0; t != worldlies[i].size(); t++)
        {
            std::cout << "X";
        }
        std::cout << std::endl;
    }

}
