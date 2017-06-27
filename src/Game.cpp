#include "Game.h"

#include <iomanip>

StateTracker::StateTracker()
{
    lastState = mainMenu;
    currentState = mainMenu;
}
StateTracker stateTracker;


class Weapon
{
public:
    std::string name;
    int weaponID;

    bool melee;
    bool range;

    float attackDamage;
    float attackRange;
    float attackSpeed;
    float attackStun;
    float attackRadius;

    float attackSpeedTimer;

    int magSize;
    int magCurrent;

    float reloadSpeed;
    float reloadSpeedTimer;

    bool beam;

    int arcAmount;
    int bulletAmount;

    enum WeaponsIDs
    {
        Nothing,
        HolyRays,
        Shotgun,
        AssaultRifle,
        SniperRifle,
        LightningArcs,
        Stake,
        Sledgehammer,
        Baton,
        Knife,
        HolyMace,
        DivineArts,
        WeakClaws,
        HeavySmash,
        WeakMachineGun,
        WeakSniperRifle,
        TurretLMG,
        TurretHMG
    };

    Weapon()
    {
        name = "Nothing";
        weaponID = Nothing;
        melee = false;
        range = false;

        attackDamage = 0;
        attackRange = 1;
        attackSpeed = 60;
        attackStun = 10;
        attackRadius = 1; // Bullet Spread/Melee Swing Arc

        attackSpeedTimer = 0;

        magSize = 10;
        magCurrent = magSize;
        reloadSpeed = 600;
        reloadSpeedTimer = 0;


        beam = false;

        arcAmount = 0;
        bulletAmount = 1;
    }

};

class WeaponManager
{
public:
    std::list<Weapon> weapons;

    Weapon getWeapon(int weaponID)
    {
        for(auto &weapon : weapons)
            if(weapon.weaponID == weaponID)
                return weapon;


        return weapons.front();
    }

    WeaponManager()
    {
        Weapon weapon;
        Weapon blankWeapon;

        weapon.name = "Nothing";
        {
            weapon.weaponID = Weapon::Nothing;
            weapon.melee = false;
            weapon.range = false;

            weapon.attackDamage = 0;
            weapon.attackRange = 1;
            weapon.attackSpeed = 60;
            weapon.attackStun = 10;
            weapon.attackRadius = 1; // Bullet Spread/Melee Swing Arc


            weapon.magSize = 0;
            weapon.reloadSpeed = 600;

            weapon.beam = false;

            weapon.arcAmount = 0;
            weapon.bulletAmount = 1;
            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Holy Rays";
        {
            weapon.weaponID = Weapon::HolyRays;
            weapon.range = true;

            weapon.attackDamage = 30;
            weapon.attackRange = 320;
            weapon.attackSpeed = 30;
            weapon.attackStun = 30;

            weapon.attackRadius = 1;


            weapon.magSize = 10;
            weapon.reloadSpeed = 180;

            weapon.beam = true;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Stake";
        {
            weapon.weaponID = Weapon::Stake;
            weapon.melee = true;

            weapon.attackDamage = 30;
            weapon.attackRange = 32;
            weapon.attackSpeed = 15;
            weapon.attackStun = 20;

            weapon.attackRadius = 10;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Shotgun";
        {
            weapon.weaponID = Weapon::Shotgun;
            weapon.range = true;

            weapon.attackDamage = 10;
            weapon.attackRange = 160;
            weapon.attackSpeed = 30;
            weapon.attackStun = 5;

            weapon.attackRadius = 45;

            weapon.magSize = 8;
            weapon.reloadSpeed = 300;

            weapon.bulletAmount = 10;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Sledgehammer";
        {
            weapon.weaponID = Weapon::Sledgehammer;
            weapon.melee = true;

            weapon.attackDamage = 50;
            weapon.attackRange = 32;
            weapon.attackSpeed = 30;
            weapon.attackStun = 30;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Assault Rifle";
        {
            weapon.weaponID = Weapon::AssaultRifle;
            weapon.range = true;

            weapon.attackDamage = 20;
            weapon.attackRange = 720;
            weapon.attackSpeed = 10;
            weapon.attackStun = 5;

            weapon.attackRadius = 15;

            weapon.magSize = 30;
            weapon.reloadSpeed = 160;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Baton";
        {
            weapon.weaponID = Weapon::Baton;
            weapon.melee = true;

            weapon.attackDamage = 10;
            weapon.attackRange = 32;
            weapon.attackSpeed = 15;
            weapon.attackStun = 20;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Sniper Rifle";
        {
            weapon.weaponID = Weapon::SniperRifle;
            weapon.range = true;

            weapon.attackDamage = 100;
            weapon.attackRange = 60000;
            weapon.attackSpeed = 45;
            weapon.attackStun = 60;

            weapon.attackRadius = 0;

            weapon.magSize = 10;
            weapon.reloadSpeed = 300;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Knife";
        {
            weapon.weaponID = Weapon::Knife;
            weapon.melee = true;

            weapon.attackDamage = 50;
            weapon.attackRange = 32;
            weapon.attackSpeed = 20;
            weapon.attackStun = 5;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Lightning Arcs";
        {
            weapon.weaponID = Weapon::LightningArcs;
            weapon.range = true;

            weapon.attackDamage = 75;
            weapon.attackRange = 160;
            weapon.attackSpeed = 30;
            weapon.attackStun = 30;

            weapon.attackRadius = 15;

            weapon.beam = true;
            weapon.arcAmount = 1;

            weapon.magSize = 10;
            weapon.reloadSpeed = 300;

            weapon.bulletAmount = 2;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Holy Mace";
        {
            weapon.weaponID = Weapon::HolyMace;
            weapon.melee = true;

            weapon.attackDamage = 75;
            weapon.attackRange = 32;
            weapon.attackSpeed = 60;
            weapon.attackStun = 60;

            weapon.attackRadius = 90;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Divine Arts";
        {
            weapon.weaponID = Weapon::DivineArts;
            weapon.melee = true;

            weapon.attackDamage = 20;
            weapon.attackRange = 64;
            weapon.attackSpeed = 20;
            weapon.attackStun = 30;

            weapon.attackRadius = 270;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Weak Claws";
        {
            weapon.weaponID = Weapon::WeakClaws;
            weapon.melee = true;

            weapon.attackDamage = 10;
            weapon.attackRange = 24;
            weapon.attackSpeed = 30;
            weapon.attackStun = 5;

            weapon.attackRadius = 10;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Heavy Smash";
        {
            weapon.weaponID = Weapon::HeavySmash;
            weapon.melee = true;

            weapon.attackDamage = 50;
            weapon.attackRange = 32;
            weapon.attackSpeed = 60;
            weapon.attackStun = 15;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Weak Machinegun";
        {
            weapon.weaponID = Weapon::WeakMachineGun;
            weapon.range = true;

            weapon.attackDamage = 10;
            weapon.attackRange = 160;
            weapon.attackSpeed = 10;
            weapon.attackStun = 5;

            weapon.attackRadius = 30;

            weapon.magSize = 30;
            weapon.reloadSpeed = 320;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Weak Sniper Rifle";
        {
            weapon.weaponID = Weapon::WeakSniperRifle;
            weapon.range = true;

            weapon.attackDamage = 75;
            weapon.attackRange = 320;
            weapon.attackSpeed = 120;
            weapon.attackStun = 60;

            weapon.attackRadius = 0;

            weapon.magSize = 1;
            weapon.reloadSpeed = 600;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Turret LMG";
        {
            weapon.weaponID = Weapon::TurretLMG;
            weapon.range = true;

            weapon.attackDamage = 10;
            weapon.attackRange = 640;
            weapon.attackSpeed = 15;
            weapon.attackStun = 5;

            weapon.attackRadius = 45;

            weapon.magSize = 100;
            weapon.reloadSpeed = 600;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

        weapon.name = "Turret HMG";
        {
            weapon.weaponID = Weapon::TurretHMG;
            weapon.range = true;

            weapon.attackDamage = 25;
            weapon.attackRange = 640;
            weapon.attackSpeed = 20;
            weapon.attackStun = 10;

            weapon.attackRadius = 30;

            weapon.magSize = 100;
            weapon.reloadSpeed = 600;

            weapons.push_back(weapon);
        }
        weapon = blankWeapon;

    }

};
WeaponManager weaponManager;

class Trait
{
public:
    std::string name;
    std::string description;
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

class TraitManager
{
public:
    std::list<Trait> baseTraits;

    TraitManager()
    {
        Trait trait;
        trait.name = "Empty";
        trait.description = "Empty Slot";
        trait.traitID = Trait::Empty;
        trait.stackable = 99;
        baseTraits.push_back(trait);

        trait.name = "Sprinter";
        trait.description = "(4) 25% Faster move speed, and 50% faster stamina regen";
        trait.traitID = Trait::Sprinter;
        trait.stackable = 4;
        baseTraits.push_back(trait);

        trait.name = "Quick Renewal";
        trait.description = "(4) Reload and Recharge spells 100% faster";
        trait.traitID = Trait::QuickRenewal;
        trait.stackable = 4;
        baseTraits.push_back(trait);

        trait.name = "Healing Wounds";
        trait.description = "(4) Attacks now heal allies for 20% of the damage";
        trait.traitID = Trait::HealingWounds;
        trait.stackable = 4;
        baseTraits.push_back(trait);

        trait.name = "Armor";
        trait.description = "(4) Take 20% less damage from all sources, Does not apply to energy shield";
        trait.traitID = Trait::Armor;
        trait.stackable = 4;
        baseTraits.push_back(trait);

        trait.name = "Energy Shield";
        trait.description = "(1) Gain a damage sponge that regenerates after not being hit for awhile";
        trait.traitID = Trait::EnergyShield;
        trait.stackable = 1;
        baseTraits.push_back(trait);

        trait.name = "Energy Shield Hardening";
        trait.description = "(1) Allows Armor trait to apply to Energy Shield, Doubles the effect of Armor for the shield (80% Cap)";
        trait.traitID = Trait::EnergyShieldHardening;
        trait.stackable = 1;
        baseTraits.push_back(trait);


        trait.name = "Demolition Expert";
        trait.description = "(4) 100% damage bonus against constructs and buildings, as well as core hearts";
        trait.traitID = Trait::DemolitionsExpert;
        trait.stackable = 4;
        baseTraits.push_back(trait);




    }
};
TraitManager traitManager;

class CharacterClass
{
public:
    std::string name;
    unsigned int id;
    std::string description;
    std::string abilityDescription;
    bool playable; // Determining if NPC only or not.
    float reviveSpeedMultipler; // Priest
    float constructDamageMultipler; // Engineer
    bool unstoppable; // Enforcer
    sf::Clock unstoppableTime; // Enforcer
    bool bulletsPierce; // Sniper
    float evilDamageMultipler; // Angel
    bool focusable; // Monk
    unsigned int focusStacks; // Monk
    int focusDecay;

    Weapon rangeWeapon;
    Weapon meleeWeapon;

    enum CharacterClassIDs
    {
        None,
        Priest,
        Engineer,
        Enforcer,
        Sniper,
        Angel,
        Monk,
        Custom,
        EnemyDummy,
        EnemyLightMelee,
        EnemyHeavyMelee,
        EnemyLightRange,
        EnemyHeavyRange,
        EnemyLightTurret,
        EnemyHeavyTurret
    };


    CharacterClass()
    {
        name = "No One";
        id = None;
        description = "Unknown";
        abilityDescription = "watt.";
        playable = false;
        reviveSpeedMultipler = 1;
        constructDamageMultipler = 1;
        unstoppable = false; // Quite stoppable!
        bulletsPierce = false;
        evilDamageMultipler = 1;
        focusable = false;
        focusStacks = 0;
        focusDecay = 0;

        rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        meleeWeapon = weaponManager.getWeapon(Weapon::Nothing);
    }

};

class CharacterClassManager
{
public:
    std::list<CharacterClass> classes;

    CharacterClass getCharacterClass(unsigned int classID)
    {
        for(auto &characterClass : classes)
        {
            if(characterClass.id == classID)
                return characterClass;
        }


        CharacterClass blankClass;
        return blankClass;
    }

    CharacterClassManager()
    {
        CharacterClass classy;
        classy.playable = true;

        classy.name = "Priest";
        classy.id = classy.Priest;
        classy.description = "Making demons wholly holeyer by his holy self since genesis.";
        classy.abilityDescription = "Revive(4x Revival Speed)";
        classy.reviveSpeedMultipler = 4;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::HolyRays);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Stake);
        classes.push_back(classy);
        classy.reviveSpeedMultipler = 1;

        classy.name = "Engineer";
        classy.id = classy.Engineer;
        classy.description = "Raging against the Demonic Machine.";
        classy.abilityDescription = "Deconstruction(Deals double base damage to constructs and buildings)";
        classy.constructDamageMultipler = 2;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Shotgun);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Sledgehammer);
        classes.push_back(classy);
        classy.constructDamageMultipler = 1;

        classy.name = "Enforcer";
        classy.id = classy.Enforcer;
        classy.description = "Even demons have to follow the holy law.";
        classy.abilityDescription = "Unstoppable(When health reaches 0, You have 10 seconds before you fall. Can be healed during this time.)";
        classy.unstoppable = true;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::AssaultRifle);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Baton);
        classes.push_back(classy);
        classy.unstoppable = false;

        classy.name = "Sniper";
        classy.id = classy.Sniper;
        classy.description = "It's never a long shot when he's around.";
        classy.abilityDescription = "Piercing Rounds!";
        classy.bulletsPierce = true;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::SniperRifle);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Knife);
        classes.push_back(classy);
        classy.bulletsPierce = false;

        classy.name = "Angel";
        classy.id = classy.Angel;
        classy.description = "Good has never been better.";
        classy.abilityDescription = "Holy Smite(Deals +100% damage to the forces of evil. Does not apply to constructs or buildings)";
        classy.evilDamageMultipler = 2;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::LightningArcs);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::HolyMace);
        classes.push_back(classy);
        classy.evilDamageMultipler = 1;

        classy.name = "Monk";
        classy.id = classy.Monk;
        classy.description = "Balance has been achieved.";
        classy.abilityDescription = "Moment of Focus(Every enemy killed grants +5 stacks of Focus)";
        classy.focusable = true;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::DivineArts);
        classes.push_back(classy);
        classy.focusable = false;



        // Enemy classes below this point
        classy.playable = false;

        classy.name = "Enemy Dummy";
        classy.id = classy.EnemyDummy;
        classy.description = "N/A";
        classy.abilityDescription = "Great at being punched";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classes.push_back(classy);


        classy.name = "Enemy Light Melee";
        classy.id = classy.EnemyLightMelee;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::WeakClaws);
        classes.push_back(classy);

        classy.name = "Enemy Heavy Melee";
        classy.id = classy.EnemyHeavyMelee;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::HeavySmash);
        classes.push_back(classy);

        classy.name = "Enemy Light Range";
        classy.id = classy.EnemyLightRange;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::WeakMachineGun);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::WeakClaws);
        classes.push_back(classy);

        classy.name = "Enemy Heavy Range";
        classy.id = classy.EnemyHeavyRange;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.bulletsPierce = true;
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::WeakSniperRifle);
        classes.push_back(classy);
        classy.bulletsPierce = false;

        classy.name = "Enemy Light Turret";
        classy.id = classy.EnemyLightTurret;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::TurretLMG);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classes.push_back(classy);

        classy.name = "Enemy Heavy Turret";
        classy.id = classy.EnemyHeavyTurret;
        classy.description = "N/A";
        classy.abilityDescription = "N/A";
        classy.rangeWeapon = weaponManager.getWeapon(Weapon::TurretHMG);
        classy.meleeWeapon = weaponManager.getWeapon(Weapon::Nothing);
        classes.push_back(classy);


    }
};
CharacterClassManager characterClassManager;

class Player
{
public:

    std::string name;
    unsigned int id;
    sf::Vector2f pos;
    sf::Vector2f lastValidPos;

    unsigned int imageID;

    CharacterClass characterClass;



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

    bool alive;
    float health;
    float healthMax;
    bool affectHealth(float amount)
    {
        health -= amount;
        if(health <= 0)
            return true;

        return false;
    }
    float armorReduction;
    float getArmorReduction()
    {
        float baseMulti = 1;
        float Multi = 0;

        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::Armor)
                Multi += 0.2;
        }

        Multi = std::min(Multi,0.8f);

        return baseMulti*Multi;
    }
    float getEnergyShieldMax()
    {
        bool energyShield = false;
        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::EnergyShield)
                energyShield = true;
        }

        return getHealthMax()*energyShield; // Multiplying by a bool, aww ye.
    }

    float energyShieldHealth;

    float getEnergyShieldArmorReduction()
    {
        float baseMulti = 1;
        float Multi = 0;
        bool energyShieldHardening = false;

        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::EnergyShieldHardening)
                energyShieldHardening = true;
            if(trait.traitID == Trait::Armor)
                Multi += 0.4;
        }


        if(!energyShieldHardening)
            Multi = 0;
        else
            Multi = std::min(Multi,0.8f);

        return baseMulti*Multi;
    }




    float getHealthMax()
    {
        return healthMax;
    }
    float moveSpeed;
    float getMoveSpeed()
    {
        float moveSpeedMulti = 1;
        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::Sprinter)
                moveSpeedMulti += 0.25;
        }

        return moveSpeed*moveSpeedMulti;
    }
    float stamina;
    float staminaMax;
    float staminaRegen;
    float getStaminaRegen()
    {
        float staminaMulti = 1;

        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::Sprinter)
                staminaMulti += 0.5;
        }

        return staminaRegen*staminaMulti;
    }
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

    float getConstructDamageMultiplier()
    {
        float baseMulti = characterClass.constructDamageMultipler;
        float Multi = 1;

        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::DemolitionsExpert)
                Multi += 1;
        }

        return baseMulti*Multi;
    }
    float getEvilDamageMultiplier()
    {
        float baseMulti = characterClass.evilDamageMultipler;
        float Multi = 1;

        /*
        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::DemolitionsExpert)
                Multi += 1;
        }
        */

        return baseMulti*Multi;
    }
    float getReviveMultiplier()
    {
        float baseMulti = characterClass.reviveSpeedMultipler;
        float Multi = 1;

        /*
        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::DemolitionsExpert)
                Multi += 1;
        }
        */

        return baseMulti*Multi;
    }

    float getHealBulletMultiplier()
    {
        float baseMulti = 1;
        float Multi = 0;

        for(auto &trait : traits)
        {
            if(trait.traitID == Trait::HealingWounds)
                Multi += 0.2;
        }

        return baseMulti*Multi;
    }





    unsigned int kills;
    unsigned int deaths;
    unsigned int reviveCount;
    unsigned int revivedCount;
    unsigned int missionsComplete;
    unsigned int missionsFailed;

    Player()
    {
        id = worldManager.globalIDs++;
        staminaRegen = 1;

        alive = true;
        healthMax = 100;
        health = healthMax;
        staminaMax = 1000;
        stamina = staminaMax;

        rotation = 0;
        rotationSpeed = 5;


        moveSpeed = 1;

        kills = 0;
        deaths = 0;
        reviveCount = 0;
        revivedCount = 0;
        missionsComplete = 0;
        missionsFailed = 0;
    }

};

class AttackMemory
{
public:
    int lifeTime;
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    float rotation;
    float radius;
    sf::Color color;
    bool melee;
    bool range;

    bool toDelete;

    AttackMemory()
    {
        lifeTime = 3;
        melee = false;
        range = false;
        toDelete = false;
    }
};

class Attack
{
public:
    std::weak_ptr<Player> owner;
    int attackType;

    std::list<AttackMemory> memory;



    enum AttackTypes
    {
        range,
        melee
    };

    bool firstFrame;
    int lifeTime;
    bool toDelete;

    Attack()
    {
        firstFrame = true;
        lifeTime = 0;
        toDelete = false;
    }
};

class AttackManager
{
public:
    std::list<Attack> attacks;

    void manageAttacks();



};
AttackManager attackManager;

class PlayerManager
{
public:
    std::list<std::shared_ptr<Player>> players;

    sf::Vector2f getPlayersAveragePos()
    {
        sf::Vector2f returnPos;

        for(auto &player : players)
        {
            returnPos += player.get()->pos;
        }

        returnPos.x /= players.size();
        returnPos.y /= players.size();

        return returnPos;
    }

    void runPlayerCharacterLogic()
    {
        if(players.empty())
            return;

        Player& player = *players.back().get();

        Weapon &meleeWeapon = player.characterClass.meleeWeapon;
        Weapon &rangeWeapon = player.characterClass.rangeWeapon;

        if(player.characterClass.focusable)
            meleeWeapon.attackSpeedTimer -= 1+(1*(0.01*player.characterClass.focusStacks));
        else
            meleeWeapon.attackSpeedTimer -= 1;
        rangeWeapon.attackSpeedTimer -= 1;


        if(player.characterClass.focusable)
        {
            player.characterClass.focusDecay--;
            if(player.characterClass.focusDecay <= 0)
            {
                player.characterClass.focusDecay = 60;
                if(player.characterClass.focusStacks > 0)
                    player.characterClass.focusStacks--;
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

    void runPlayerCharacterInput()
    {

        if(players.empty())
            return;

        Player& player = *players.back().get();

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
                yMovement += -player.getMoveSpeed();
            }

            if(inputState.key[Key::A])
            {
                xMovement += -player.getMoveSpeed();
            }

            if(inputState.key[Key::S])
            {
                yMovement += player.getMoveSpeed();
            }

            if(inputState.key[Key::D])
            {
                xMovement += player.getMoveSpeed();
            }



            player.stamina = std::min(player.stamina+player.getStaminaRegen(),player.getStaminaMax());

            if(!player.isTired() && inputState.key[Key::LShift])
            {
                bool isRunning = false;

                if(inputState.key[Key::W])
                {
                    yMovement += -player.getMoveSpeed()*3;
                    isRunning = true;
                }

                if(inputState.key[Key::A])
                {
                    xMovement += -player.getMoveSpeed()*3;
                    isRunning = true;
                }

                if(inputState.key[Key::S])
                {
                    yMovement += player.getMoveSpeed()*3;
                    isRunning = true;
                }

                if(inputState.key[Key::D])
                {
                    xMovement += player.getMoveSpeed()*3;
                    isRunning = true;
                }

                if(isRunning)
                    player.stamina -= 3;

            }


            if(worldManager.currentWorld.isTileWalkable(sf::Vector2i(player.pos.x+xMovement,player.pos.y) ))
            {
                player.pos.x += xMovement;
                player.lastValidPos = player.pos;
            }

            if(worldManager.currentWorld.isTileWalkable(sf::Vector2i(player.pos.x,player.pos.y+yMovement) ))
            {
                player.pos.y += yMovement;
                player.lastValidPos = player.pos;
            }



        }

        { // Attack Code
            Weapon &meleeWeapon = player.characterClass.meleeWeapon;
            Weapon &rangeWeapon = player.characterClass.rangeWeapon;


            if(inputState.key[Key::R].time == 1 && rangeWeapon.reloadSpeedTimer < 0)
                rangeWeapon.reloadSpeedTimer = rangeWeapon.reloadSpeed;

            if(rangeWeapon.reloadSpeedTimer == 0)
            {
                rangeWeapon.magCurrent = rangeWeapon.magSize;
            }
            rangeWeapon.reloadSpeedTimer--;
            for(auto &trait : player.traits)
            {
                if(trait.traitID == Trait::QuickRenewal)
                    rangeWeapon.reloadSpeedTimer--;

            }


            if(rangeWeapon.attackSpeedTimer <= 0 && inputState.lmbTime)
            { // Range
                if(rangeWeapon.magCurrent > 0 && rangeWeapon.reloadSpeedTimer < 0)
                {
                    rangeWeapon.magCurrent--;
                    rangeWeapon.attackSpeedTimer = rangeWeapon.attackSpeed;

                    Attack attack;
                    attack.owner = players.back();
                    attack.attackType = attack.range;
                    attack.lifeTime = 15;
                    attackManager.attacks.push_back(attack);
                }





            }

            if(meleeWeapon.attackSpeedTimer <= 0 && inputState.rmbTime)
            { // Melee
                meleeWeapon.attackSpeedTimer = meleeWeapon.attackSpeed;

                Attack attack;
                attack.owner = players.back();
                attack.attackType = attack.melee;
                attack.lifeTime = 3;
                attackManager.attacks.push_back(attack);

            }

        }




    }

    void makePlayer(sf::Vector2f spawnPos = gvars::mousePos)
    {
        std::shared_ptr<Player> playerPtr(new Player());
        players.push_back(playerPtr);
        Player &player = *playerPtr.get();

        player.pos = spawnPos;
        // player.pos = sf::Vector2f(102400,102400);
        player.healthMax = 100;
        player.health = player.healthMax;
        player.staminaMax = 1000;
        player.stamina = player.staminaMax;

        player.rotation = 0;
        player.rotationSpeed = 5;


        player.moveSpeed = 1;

        player.genBaseTraits();


    }

};
PlayerManager playerManager;

class Enemy : public Player
{
public:
    int pathFinding;
    bool creature;
    bool construct;
    std::weak_ptr<Player> target;
    int targetNumber;
    std::vector<ChunkTile*> storedPath;
    int lastVisionCheck;
    sf::Vector2f lastVisionPos;
    bool followingVision;

    Enemy()
    {
        imageID = 0;
        id = worldManager.globalIDs++;
        creature = true;
        construct = false;
        lastVisionCheck = 0;
        followingVision = false;
    }
};

bool visionCheck(sf::Vector2f startPos, sf::Vector2f endPos)
{

    int accuracy = 5; // The smaller, the more accurate, but the more frames. Basically how many pixels we skip.
    sf::Vector2f tracePos = startPos;
    float transitAngle = math::angleBetweenVectors(tracePos,endPos);

    bool done = false;
    while(!done)
    {
        if(inputState.key[Key::Tab])
            shapes.createCircle(tracePos.x,tracePos.y,3,sf::Color::Green);

        if(math::distance(tracePos,endPos) <= accuracy)
        {

            done = true;
            return true;
        }

        if((!worldManager.currentWorld.isTileWalkable(sf::Vector2i(tracePos) )))
        {
            done = true;
            return false;
        }

        tracePos = math::angleCalc(tracePos,transitAngle,accuracy);
    }

    return false;
}

void runEnemyBrain(Enemy &enemy)
{
    // Acquire a target to do things against
    if(!enemy.target.lock())
    {
        int targets = playerManager.players.size();
        int targetChosen = random(0,targets-1);
        if(targetChosen < 0)
            return;

        int playerCounter = 0;
        for(auto &player : playerManager.players)
        {
            if(playerCounter == targetChosen)
            {
                enemy.target = player;
                enemy.targetNumber = playerCounter;
                break;
            }

            playerCounter++;
        }
    }



    /*
    if(!enemy.target.lock())
        shapes.createText(enemy.pos.x,enemy.pos.y-10,10,sf::Color::Yellow,"Target: NONE FOUND");
    else
        shapes.createText(enemy.pos.x,enemy.pos.y-10,10,sf::Color::Yellow,"Target: Player " + std::to_string(enemy.targetNumber) + " (" + std::to_string(enemy.target.lock().get()->id) + ")" );

        */

    if(!enemy.target.lock())
        return;

    Player& target = *enemy.target.lock().get();



    { // Rotation Code
       enemy.rotationPoint = target.pos;

        int rotationDiff = math::angleDiff(enemy.rotation, math::angleBetweenVectors(enemy.pos,enemy.rotationPoint));
        int rotCheck = rotationDiff;
        if(rotCheck < 0)
            rotCheck = -rotCheck;

        if(rotCheck < enemy.rotationSpeed)
            enemy.rotation = math::angleBetweenVectors(enemy.pos,enemy.rotationPoint);
        else
        {
            if(rotationDiff > 0)
                enemy.rotation += enemy.rotationSpeed;
            if(rotationDiff < 0)
                enemy.rotation -= enemy.rotationSpeed;
        }
    }

    { // Movement Code
        sf::Vector2f desiredPosition;
        bool positionSet = false;

        int longestRange = 600;
        if(longestRange < enemy.characterClass.meleeWeapon.attackRange)
            longestRange = enemy.characterClass.meleeWeapon.attackRange;
        if(longestRange < enemy.characterClass.rangeWeapon.attackRange)
            longestRange = enemy.characterClass.rangeWeapon.attackRange;



        enemy.lastVisionCheck--;
        if(true == false && enemy.followingVision)
        {
            desiredPosition = enemy.lastVisionPos;
            positionSet = true;
            if(enemy.lastVisionCheck <= 0)
            {
                if(enemy.target.lock() && visionCheck(enemy.pos,enemy.target.lock().get()->pos))
                {
                    enemy.lastVisionPos = enemy.target.lock().get()->pos;
                    enemy.followingVision = true;
                    desiredPosition = enemy.target.lock().get()->pos;
                    positionSet = true;
                }
                else
                {
                    enemy.followingVision = false;
                }
                enemy.lastVisionCheck = 60;
            }
        }

        if(enemy.target.lock() && math::distance(enemy.pos,enemy.target.lock().get()->pos) <= longestRange && visionCheck(enemy.pos,enemy.target.lock().get()->pos))
        {

            enemy.lastVisionCheck = 60;
            enemy.lastVisionPos = enemy.target.lock().get()->pos;
            enemy.followingVision = true;
            desiredPosition = enemy.target.lock().get()->pos;
            positionSet = true;
        }
        else if(!enemy.storedPath.empty())
        {
            desiredPosition = enemy.storedPath.front()->pos;
            positionSet = true;
        }


        if(positionSet)
        {
            if(desiredPosition.x > enemy.pos.x)
                enemy.pos.x += enemy.getMoveSpeed();
            if(desiredPosition.x < enemy.pos.x)
                enemy.pos.x -= enemy.getMoveSpeed();
            if(desiredPosition.y > enemy.pos.y)
                enemy.pos.y += enemy.getMoveSpeed();
            if(desiredPosition.y < enemy.pos.y)
                enemy.pos.y -= enemy.getMoveSpeed();
        }






        if(!enemy.storedPath.empty() && math::distance(enemy.pos,desiredPosition) <= 5)
            enemy.storedPath.erase(enemy.storedPath.begin());
    }

}


int getPlayersLowestChunk()
{
    int returnChunk = 99999;
    int chunkCount = 0;
    for(auto &chunk : worldManager.currentWorld.chunks)
    {
        for(auto &player : playerManager.players)
        {
            sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
            sf::Vector2i checkPos(player.get()->pos.x/1024,player.get()->pos.y/1024);
            if(checkPos == chunkPos)
            {
                if(returnChunk > chunkCount)
                    returnChunk = chunkCount;
            }
        }



        chunkCount++;
    }

    if(returnChunk == 99999)
        return 0;

    return returnChunk;

}

int getPlayersHighestChunk()
{
    int returnChunk = 0;

    int chunkCount = 0;
    for(auto &chunk : worldManager.currentWorld.chunks)
    {
        for(auto &player : playerManager.players)
        {
            sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
            sf::Vector2i checkPos(player.get()->pos.x/1024,player.get()->pos.y/1024);
            if(checkPos == chunkPos)
            {
                if(returnChunk < chunkCount)
                    returnChunk = chunkCount;
            }
        }



        chunkCount++;
    }
    return returnChunk;
}

sf::Vector2f getSquadOrRandomPlayerPos()
{
    sf::Vector2f returnPos;
    returnPos = playerManager.getPlayersAveragePos();
    if(worldManager.currentWorld.isTileWalkable(sf::Vector2i(returnPos.x,returnPos.y)))
        return returnPos;

    int randomPlayer = random(0,playerManager.players.size()-1);
    int tracker = 0;
    for(auto &player : playerManager.players)
    {
        if(tracker == randomPlayer)
            returnPos = player.get()->pos;
        tracker++;
    }


    return returnPos;
}

class EnemyManager
{
public:
    std::list<std::shared_ptr<Enemy>> enemies;
    std::list<std::shared_ptr<Enemy>> deadEnemies;
    std::list<Enemy> baseEnemies;

    enum enemyIDs
    {
        enemyDummy,
        meleeLight,
        meleeHeavy,
        rangeLight,
        rangeHeavy,
        turretLight,
        turretHeavy,
    };

    int getLivingEnemyCount()
    {
        int returnValue = 0;
        for(auto &enemy : enemies)
            if(enemy.get()->health > 0)
                returnValue++;
        return returnValue;
    }

    void runEnemyLogic()
    {
        if(enemies.empty())
            return;

        for(auto &enemyPtr : enemies)
        {
            Enemy& enemy = *enemyPtr.get();

            if(enemy.health <= 0)
                continue;


            Weapon &meleeWeapon = enemy.characterClass.meleeWeapon;
            Weapon &rangeWeapon = enemy.characterClass.rangeWeapon;

            meleeWeapon.attackSpeedTimer--;
            rangeWeapon.attackSpeedTimer--;


            runEnemyBrain(enemy);
        }




    }

    void makeEnemy(sf::Vector2f spawnPos, int enemyType = -1)
    {

        std::shared_ptr<Enemy> enemyPtr(new Enemy());
        enemies.push_back(enemyPtr);
        // Enemy &enemy = *enemies.back().get();
        Enemy &enemy = *enemyPtr.get();

        if(enemyType == -1)
            enemyType = random(0,baseEnemies.size()-1);
        int tracker = 0;
        for(auto &baseEnemy : baseEnemies)
        {
            if(tracker == enemyType)
                enemy = baseEnemy;

            tracker++;
        }


        // enemy.name = "Enemy Dummy";
        enemy.pos = spawnPos;
        // enemy.healthMax = 100;
    }

    void drawEnemies()
    {

        static sf::Texture& dummyTex = texturemanager.getTexture("Enemy Dummy.png");

        static sf::Texture& meleeLightTex = texturemanager.getTexture("MeleeLight.png");
        static sf::Texture& meleeHeavyTex = texturemanager.getTexture("MeleeHeavy.png");
        static sf::Texture& rangeLightTex = texturemanager.getTexture("RangeLight.png");
        static sf::Texture& rangeHeavyTex = texturemanager.getTexture("RangeHeavy.png");
        static sf::Texture& turretLightTex = texturemanager.getTexture("TurretLight.png");
        static sf::Texture& turretHeavyTex = texturemanager.getTexture("TurretHeavy.png");

        static sf::Sprite dummySprite;
        if(dummySprite.getTexture() == nullptr)
        {
            dummySprite.setTexture(dummyTex);
            dummySprite.setOrigin(dummyTex.getSize().x/2,dummyTex.getSize().y/2);
            dummySprite.scale(sf::Vector2f(0.5,0.5));
        }

        static sf::Sprite meleeLightSprite;
        if(meleeLightSprite.getTexture() == nullptr)
        {
            meleeLightSprite.setTexture(meleeLightTex);
            meleeLightSprite.setOrigin(meleeLightTex.getSize().x/2,meleeLightTex.getSize().y/2);
            meleeLightSprite.scale(sf::Vector2f(0.5,0.5));
        }
        static sf::Sprite meleeHeavySprite;
        if(meleeHeavySprite.getTexture() == nullptr)
        {
            meleeHeavySprite.setTexture(meleeHeavyTex);
            meleeHeavySprite.setOrigin(meleeHeavyTex.getSize().x/2,meleeHeavyTex.getSize().y/2);
            meleeHeavySprite.scale(sf::Vector2f(0.5,0.5));
        }

        static sf::Sprite rangeLightSprite;
        if(rangeLightSprite.getTexture() == nullptr)
        {
            rangeLightSprite.setTexture(rangeLightTex);
            rangeLightSprite.setOrigin(rangeLightTex.getSize().x/2,rangeLightTex.getSize().y/2);
            rangeLightSprite.scale(sf::Vector2f(0.5,0.5));
        }

        static sf::Sprite rangeHeavySprite;
        if(rangeHeavySprite.getTexture() == nullptr)
        {
            rangeHeavySprite.setTexture(rangeHeavyTex);
            rangeHeavySprite.setOrigin(rangeHeavyTex.getSize().x/2,rangeHeavyTex.getSize().y/2);
            rangeHeavySprite.scale(sf::Vector2f(0.5,0.5));
        }

        static sf::Sprite turretLightSprite;
        if(turretLightSprite.getTexture() == nullptr)
        {
            turretLightSprite.setTexture(turretLightTex);
            turretLightSprite.setOrigin(turretLightTex.getSize().x/2,turretLightTex.getSize().y/2);
            turretLightSprite.scale(sf::Vector2f(0.5,0.5));
        }

        static sf::Sprite turretHeavySprite;
        if(turretHeavySprite.getTexture() == nullptr)
        {
            turretHeavySprite.setTexture(turretHeavyTex);
            turretHeavySprite.setOrigin(turretHeavyTex.getSize().x/2,turretHeavyTex.getSize().y/2);
            turretHeavySprite.scale(sf::Vector2f(0.5,0.5));
        }


        // Setting View
        sf::View oldView = window.getView();
        window.setView(gvars::view1);

        // Render stuffs

        // Make the dead darker so they're easier to differentiate;
        {
            meleeLightSprite.setColor(sf::Color(50,50,50));
            meleeHeavySprite.setColor(sf::Color(50,50,50));
            rangeLightSprite.setColor(sf::Color(50,50,50));
            rangeHeavySprite.setColor(sf::Color(50,50,50));
            turretLightSprite.setColor(sf::Color(50,50,50));
            turretHeavySprite.setColor(sf::Color(50,50,50));
        }

        for(auto &enemyPtr : deadEnemies)
        {
            Enemy &enemy = *enemyPtr.get();

            if(!onScreen(enemy.pos))
                continue;




            if(enemy.imageID == meleeLight)
            {
                meleeLightSprite.setPosition(enemy.pos);
                meleeLightSprite.setRotation(enemy.rotation-90);
                window.draw(meleeLightSprite);
            }

            else if(enemy.imageID == meleeHeavy)
            {
                meleeHeavySprite.setPosition(enemy.pos);
                meleeHeavySprite.setRotation(enemy.rotation-90);
                window.draw(meleeHeavySprite);
            }

            else if(enemy.imageID == rangeLight)
            {
                rangeLightSprite.setPosition(enemy.pos);
                rangeLightSprite.setRotation(enemy.rotation-90);
                window.draw(rangeLightSprite);
            }

            else if(enemy.imageID == rangeHeavy)
            {
                rangeHeavySprite.setPosition(enemy.pos);
                rangeHeavySprite.setRotation(enemy.rotation-90);
                window.draw(rangeHeavySprite);
            }

            else if(enemy.imageID == turretLight)
            {
                turretLightSprite.setPosition(enemy.pos);
                turretLightSprite.setRotation(enemy.rotation-90);
                window.draw(turretLightSprite);
            }

            else if(enemy.imageID == turretHeavy)
            {
                turretHeavySprite.setPosition(enemy.pos);
                turretHeavySprite.setRotation(enemy.rotation-90);
                window.draw(turretHeavySprite);
            }

            else if(enemy.imageID == enemyDummy)
            {
                dummySprite.setPosition(enemy.pos);
                dummySprite.setRotation(enemy.rotation-90);
                window.draw(dummySprite);
            }


        }

        // Make 'em bright again.
        {
            meleeLightSprite.setColor(sf::Color::White);
            meleeHeavySprite.setColor(sf::Color::White);
            rangeLightSprite.setColor(sf::Color::White);
            rangeHeavySprite.setColor(sf::Color::White);
            turretLightSprite.setColor(sf::Color::White);
            turretHeavySprite.setColor(sf::Color::White);
        }

        for(auto &enemyPtr : enemies)
        {
            Enemy &enemy = *enemyPtr.get();



            if(enemy.imageID == meleeLight)
            {
                meleeLightSprite.setPosition(enemy.pos);
                meleeLightSprite.setRotation(enemy.rotation-90);
                window.draw(meleeLightSprite);
            }

            else if(enemy.imageID == meleeHeavy)
            {
                meleeHeavySprite.setPosition(enemy.pos);
                meleeHeavySprite.setRotation(enemy.rotation-90);
                window.draw(meleeHeavySprite);
            }

            else if(enemy.imageID == rangeLight)
            {
                rangeLightSprite.setPosition(enemy.pos);
                rangeLightSprite.setRotation(enemy.rotation-90);
                window.draw(rangeLightSprite);
            }

            else if(enemy.imageID == rangeHeavy)
            {
                rangeHeavySprite.setPosition(enemy.pos);
                rangeHeavySprite.setRotation(enemy.rotation-90);
                window.draw(rangeHeavySprite);
            }

            else if(enemy.imageID == turretLight)
            {
                turretLightSprite.setPosition(enemy.pos);
                turretLightSprite.setRotation(enemy.rotation-90);
                window.draw(turretLightSprite);
            }

            else if(enemy.imageID == turretHeavy)
            {
                turretHeavySprite.setPosition(enemy.pos);
                turretHeavySprite.setRotation(enemy.rotation-90);
                window.draw(turretHeavySprite);
            }

            else if(enemy.imageID == enemyDummy)
            {
                dummySprite.setPosition(enemy.pos);
                dummySprite.setRotation(enemy.rotation-90);
                window.draw(dummySprite);
            }


            float healthPercent = enemy.health/enemy.getHealthMax();

            shapes.createSquare(enemy.pos.x-27,enemy.pos.y-17,enemy.pos.x+52,enemy.pos.y-3,sf::Color::Black);
            shapes.createSquare(enemy.pos.x-25,enemy.pos.y-15,enemy.pos.x-25+75*healthPercent,enemy.pos.y-5,sf::Color::Red);


            /*

            std::string staminaString;
            staminaString.append(std::to_string( (int) enemy.health) );
            staminaString.append("/");
            staminaString.append(std::to_string( (int) enemy.getHealthMax()));


            shapes.createText(enemy.pos.x,enemy.pos.y+25,10,sf::Color::Red,staminaString);

            */

        }

        // Fixing View
        window.setView(oldView);

    }

    EnemyManager()
    {
        Enemy blankEnemy;
        Enemy enemy;

        enemy.name = "Dummy";
        {
            enemy.creature = true;
            enemy.construct = true;

            enemy.imageID = enemyDummy;

            enemy.moveSpeed = 0;
            enemy.healthMax = 100000;
            enemy.health = enemy.getHealthMax();
            enemy.rotationSpeed = 1;

            baseEnemies.push_back(enemy);

        }
        enemy = blankEnemy;

        enemy.name = "Light Melee";
        {
            enemy.creature = true;
            enemy.imageID = meleeLight;

            enemy.moveSpeed = 2;
            enemy.healthMax = 50;
            enemy.health = enemy.getHealthMax();
            enemy.rotationSpeed = 2;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyLightMelee);

            baseEnemies.push_back(enemy);

        }
        enemy = blankEnemy;

        enemy.name = "Heavy Melee";
        {
            enemy.creature = true;
            enemy.imageID = meleeHeavy;

            enemy.moveSpeed = 0.5;
            enemy.healthMax = 200;
            enemy.health = enemy.getHealthMax();
            enemy.rotationSpeed = 0.5;
            enemy.armorReduction = 0.2;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyHeavyMelee);

            baseEnemies.push_back(enemy);
        }
        enemy = blankEnemy;

        enemy.name = "Light Range";
        {
            enemy.creature = true;
            enemy.imageID = rangeLight;

            enemy.moveSpeed = 2;
            enemy.healthMax = 100;
            enemy.health = enemy.getHealthMax();
            //enemy.rotationSpeed
            //enemy.armorReduction = 0.2;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyLightRange);

            baseEnemies.push_back(enemy);
        }
        enemy = blankEnemy;

        enemy.name = "Heavy Range";
        {
            enemy.creature = true;
            enemy.imageID = rangeHeavy;

            enemy.moveSpeed = 1;
            enemy.healthMax = 50;
            enemy.health = enemy.getHealthMax();
            //enemy.rotationSpeed
            //enemy.armorReduction = 0.2;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyHeavyRange);

            baseEnemies.push_back(enemy);
        }
        enemy = blankEnemy;

        enemy.name = "Light Turret";
        {
            enemy.creature = false;
            enemy.construct = true;
            enemy.imageID = turretLight;

            enemy.moveSpeed = 0;
            enemy.healthMax = 200;
            enemy.health = enemy.getHealthMax();
            enemy.rotationSpeed = 0.5;
            enemy.armorReduction = 0.4;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyLightTurret);

            baseEnemies.push_back(enemy);
        }
        enemy = blankEnemy;

        enemy.name = "Heavy Turret";
        {
            enemy.creature = false;
            enemy.construct = true;
            enemy.imageID = turretHeavy;

            enemy.moveSpeed = 0;
            enemy.healthMax = 500;
            enemy.health = enemy.getHealthMax();
            enemy.rotationSpeed = 0.5;
            enemy.armorReduction = 0.6;

            enemy.characterClass = characterClassManager.getCharacterClass(CharacterClass::EnemyHeavyTurret);

            baseEnemies.push_back(enemy);
        }
        enemy = blankEnemy;
    }

};
EnemyManager enemyManager;

class SpawnController
{
public:
    sf::Vector2f pos;
    bool targetPathed;
    std::vector<ChunkTile*> storedPath;

    SpawnController()
    {
        targetPathed = false;
    }
};

class SpawnControllerManager
{
public:
    std::list<SpawnController> spawnControllers;
    bool allowUpdates;
    int lastUpdated;


    void updateSpawnerPathsIncrementally()
    {
        if(!allowUpdates)
            return;

        static bool oneSecondPassed = false;
        {
            static sf::Clock oneSecondTimer;
            if(oneSecondTimer.getElapsedTime().asSeconds() > 1)
            {
                oneSecondTimer.restart();
                oneSecondPassed = true;
            }
        }


        if(oneSecondPassed)
        {
            oneSecondPassed = false;

            bool doneUpdating = false;

            while(!doneUpdating)
            {
                int subTracker = 0;
                for(auto &spawn : spawnControllers)
                {
                    if(subTracker >= spawnControllers.size()-1) // Start over.
                            lastUpdated = -1;

                    if(subTracker > lastUpdated && spawn.targetPathed)
                    {
                        // std::cout << subTracker << std::endl;
                        lastUpdated = subTracker;



                        sf::Vector2f squadPos = getSquadOrRandomPlayerPos();
                        int results = pathCon.makePath(spawn.pos,squadPos);
                        if(results == 0) // 0 == solved.
                        {
                            spawn.storedPath = pathCon.storedPath;
                            doneUpdating = true;
                            break;
                        }

                    }

                    subTracker++;
                }
            }

        }
    }

    void setupSpawners()
    {
        for(auto &chunk : worldManager.currentWorld.chunks)
        {
            for(int i = 0; i != 32; i++)
                for(int t = 0; t != 32; t++)
            {
                if(chunk.tiles[i][t].type == ChunkTile::ENEMYSPAWNER)
                {
                    SpawnController spawnCon;
                    spawnCon.pos = chunk.tiles[i][t].pos;
                    spawnCon.pos.x += 16;
                    spawnCon.pos.y += 16;

                    spawnControllers.push_back(spawnCon);
                }
            }
        }
    }

    void pathSpawners()
    {
        sf::Vector2f squadPos = getSquadOrRandomPlayerPos();

        int spawnsValid = 0;
        int spawnsInvalid = 0;

        for(auto &spawnCon : spawnControllers)
        {

            int results = pathCon.makePath(spawnCon.pos,squadPos);
            if(results == 0) // 0 == solved.
            {
                spawnCon.targetPathed = true;
                spawnCon.storedPath = pathCon.storedPath;

                allowUpdates = true;
                spawnsValid++;
            }
            else
                spawnsInvalid++;
        }

        std::cout << "Spawns: " << spawnsValid << "/" << spawnsInvalid << std::endl;
    }

    SpawnControllerManager()
    {
        lastUpdated = -1;
        allowUpdates = false;
    }

};
SpawnControllerManager spawnControlManager;

void spawnLogic()
{
    if(enemyManager.enemies.empty())
    {
        for(auto &chunk : worldManager.currentWorld.chunks)
        {

            for(int i = 0; i != 32; i++)
                for(int t = 0; t != 32; t++)
            {
                if(chunk.tiles[i][t].type == ChunkTile::TURRETHEAVY)
                {
                    sf::Vector2f spawnPos = chunk.tiles[i][t].pos;
                    spawnPos += sf::Vector2f(16,16);
                    enemyManager.makeEnemy(spawnPos,EnemyManager::turretHeavy);
                }
                if(chunk.tiles[i][t].type == ChunkTile::TURRETLIGHT)
                {
                    sf::Vector2f spawnPos = chunk.tiles[i][t].pos;
                    spawnPos += sf::Vector2f(16,16);
                    enemyManager.makeEnemy(spawnPos,EnemyManager::turretLight);
                }

                if(chunk.tiles[i][t].type == ChunkTile::TURRETRANDOM)
                {
                    sf::Vector2f spawnPos = chunk.tiles[i][t].pos;
                    spawnPos += sf::Vector2f(16,16);
                    if(random(1,10) <= 3)
                        enemyManager.makeEnemy(spawnPos,EnemyManager::turretHeavy);
                    else
                        enemyManager.makeEnemy(spawnPos,EnemyManager::turretLight);
                }
            }

        }
    }

    sf::Vector2f squadPos = playerManager.getPlayersAveragePos();

    int lowestChunk = getPlayersLowestChunk();
    int highestChunk = getPlayersHighestChunk();

    // std::cout << "Lowest/Highest: " << lowestChunk << "/" << highestChunk << std::endl;

    static bool oneSecondPassed = false;
    { // Tracking Time
        static sf::Clock oneSecondTimer;
        if(oneSecondTimer.getElapsedTime().asSeconds() > 1)
        {
            oneSecondTimer.restart();
            oneSecondPassed = true;
        }
    }


    if(inputState.key[Key::BackSpace].time == 1)
        spawnControlManager.pathSpawners();

    if(oneSecondPassed)
    {
        oneSecondPassed = false;

        if(playerManager.players.size() > 0)
            spawnControlManager.updateSpawnerPathsIncrementally();



        if(enemyManager.getLivingEnemyCount() > 100)
            return;

        std::vector<ChunkTile*> spawnTiles;
        for(auto &chunk : worldManager.currentWorld.chunks)
        {
            for(int i = 0; i != 32; i++)
                for(int t = 0; t != 32; t++)
            {
                if(chunk.tiles[i][t].type == ChunkTile::ENEMYSPAWNER)
                {
                    spawnTiles.push_back(&chunk.tiles[i][t]);
                }
            }
        }

        for(auto &spawnTile : spawnControlManager.spawnControllers)
        {

            if(!spawnTile.targetPathed)
                continue;

            if(random(1,4) != 1) // Don't want it ALWAYS spewing.
                continue;

            int randomEnemy = random(1,8);
            if(randomEnemy > 4)
            { // Melee Light

                sf::Vector2f spawnPos = spawnTile.pos;
                spawnPos += sf::Vector2f(16,16);
                enemyManager.makeEnemy(spawnPos,EnemyManager::meleeLight);

                enemyManager.enemies.back().get()->storedPath = spawnTile.storedPath;
            }
            else if(randomEnemy > 2)
            { // Melee Heavy

                sf::Vector2f spawnPos = spawnTile.pos;
                spawnPos += sf::Vector2f(16,16);
                enemyManager.makeEnemy(spawnPos,EnemyManager::meleeHeavy);

                enemyManager.enemies.back().get()->storedPath = spawnTile.storedPath;

            }
            else if(randomEnemy > 1)
            { // Range Light

                sf::Vector2f spawnPos = spawnTile.pos;
                spawnPos += sf::Vector2f(16,16);
                enemyManager.makeEnemy(spawnPos,EnemyManager::rangeLight);

                enemyManager.enemies.back().get()->storedPath = spawnTile.storedPath;

            }
            else if(randomEnemy == 1)
            { // Range Heavy
                sf::Vector2f spawnPos = spawnTile.pos;
                spawnPos += sf::Vector2f(16,16);
                enemyManager.makeEnemy(spawnPos,EnemyManager::rangeHeavy);

                enemyManager.enemies.back().get()->storedPath = spawnTile.storedPath;
            }
        }
    }


}



sf::Vector2f bulletAttack(Attack &attack, Player &owner, sf::Vector2f attackPos, std::list<std::shared_ptr<Enemy>> &enemies)
{
    std::list<std::weak_ptr<Enemy>> enemiesFound;
    std::vector<int> foundIDs;
    sf::Vector2f returnPos;

    // Optimizations; Accuracy, Filter enemies before using this function via one 180 degree angle check, or two side by side opposite angle checks to mimic a square.
    // Possibly also the isWalkableTile function.

    int accuracy = 3; // The smaller, the more accurate, but the more frames. Basically how many pixels we skip.
    sf::Vector2f tracePos = owner.pos;
    float transitAngle = math::angleBetweenVectors(tracePos,attackPos);

    bool done = false;
    while(!done)
    {
        if(inputState.key[Key::Tab])
            shapes.createCircle(tracePos.x,tracePos.y,3,sf::Color::Green);

        if(math::distance(tracePos,attackPos) <= accuracy)
        {
            done = true;
            returnPos = tracePos;
        }


        // Wall damage will be done with this line.
        if((!worldManager.currentWorld.isTileWalkable(sf::Vector2i(tracePos) )))
        {

            done = true;
            returnPos = tracePos;

            ChunkTile & tile = worldManager.currentWorld.getTile(sf::Vector2i(tracePos));

            if(tile.health > 0)
            {
                float finalDamage = owner.characterClass.rangeWeapon.attackDamage;

                finalDamage *= owner.getConstructDamageMultiplier();

                bool tileDestroyed = tile.affectHealth(finalDamage);

                if(tileDestroyed)
                {
                    WorldChunk & chunk = worldManager.currentWorld.getChunk(sf::Vector2i(tracePos));
                    chunk.updateChunkImage(chunk.convertWorldCordtoChunkTilePos(sf::Vector2i(tracePos)));
                }
            }
        }

        for(auto &enemyPtr : enemies)
        {
            Enemy &enemy = *enemyPtr.get();

            bool alreadyChecked = false;

            for(auto idCheck : foundIDs)
                if(enemy.id == idCheck)
                    alreadyChecked = true;

            if(alreadyChecked)
                continue;

            if(math::distance(tracePos,enemy.pos) <= 32/2)
            {
                foundIDs.push_back(enemy.id);
                enemiesFound.push_back(enemyPtr);


                // Piercing Bullets don't stop this method.
                // Small chance it'll hit two enemies or so, but that's fine.
                if(!owner.characterClass.bulletsPierce)
                {
                    done = true;
                    returnPos = tracePos;
                }
            }
        }

        tracePos = math::angleCalc(tracePos,transitAngle,accuracy);
    }



    if(enemiesFound.size() > 0)
    {

        for(auto &enemyPtr : enemiesFound)
        {
            Enemy &enemy = *enemyPtr.lock().get();



            float finalDamage = owner.characterClass.rangeWeapon.attackDamage;
            if(enemy.creature)
                finalDamage *= owner.getEvilDamageMultiplier();
            if(enemy.construct)
                finalDamage *= owner.getConstructDamageMultiplier();


            bool enemyKilled = enemy.affectHealth(finalDamage);
            if(enemyKilled)
            {
                owner.kills++;

                enemyManager.deadEnemies.push_back(enemyPtr.lock());
                enemyManager.enemies.remove(enemyPtr.lock());
            }


            std::vector<int> arcedIDs;
            arcedIDs.push_back(enemy.id);
            for(int i = 0; i != owner.characterClass.rangeWeapon.arcAmount; i++)
            {
                for(auto &arcEnemyPtr : enemyManager.enemies)
                {
                    Enemy &arcEnemy = *arcEnemyPtr.get();

                    //if(arcEnemy.id == enemy.id)
                      //  continue;

                    if(math::distance(enemy.pos,arcEnemy.pos) <= owner.characterClass.rangeWeapon.attackRange)
                    {



                        bool beenZapped = false;
                        for(auto &zapID : arcedIDs)
                            if(arcEnemy.id == zapID)
                                beenZapped = true;

                        if(beenZapped)
                            continue;







                        arcedIDs.push_back(arcEnemy.id);
                        float finalDamage = owner.characterClass.rangeWeapon.attackDamage;
                        if(arcEnemy.creature)
                            finalDamage *= owner.getEvilDamageMultiplier();
                        if(arcEnemy.construct)
                            finalDamage *= owner.getConstructDamageMultiplier();

                        arcEnemy.health -= finalDamage;


                        AttackMemory atkMem;
                        atkMem.startPos = enemy.pos;
                        atkMem.endPos = arcEnemy.pos;
                        atkMem.lifeTime = 15;
                        atkMem.range = true;
                        atkMem.color = sf::Color::Cyan;

                        attack.memory.push_back(atkMem);

                        // Attack complete
                        break; // TODO: Remove this if we're doing splash damage instead.

                    }
                }



            }


        }
    }

    return returnPos;
}



void AttackManager::manageAttacks()
{
    for(auto &attack : attacks)
    {
        if(!attack.owner.lock())
        {
            attack.toDelete = true;
            continue;
        }

        if(attack.lifeTime <= 0)
        {
            attack.toDelete = true;
            continue;
        }
        attack.lifeTime--;

        Player &owner = *attack.owner.lock().get();


        if(attack.attackType == attack.range)
        {
            Weapon weapon = owner.characterClass.rangeWeapon;

            float baseRot = owner.rotation;
            //float radius = weapon.attackRadius/2;

            if(attack.firstFrame)
            { // Attack Code
                attack.firstFrame = false;


                for(int i = 0; i != weapon.bulletAmount; i++)
                {
                    sf::Vector2f bulletHitLocation = math::angleCalc(owner.pos,baseRot+random(-weapon.attackRadius/2,weapon.attackRadius/2),weapon.attackRange);
                    AttackMemory atkMem;
                    atkMem.startPos = owner.pos;
                    atkMem.endPos = bulletHitLocation;
                    atkMem.lifeTime = 15;
                    atkMem.range = true;
                    atkMem.color = sf::Color::White;


                    atkMem.endPos = bulletAttack(attack,owner,atkMem.endPos,enemyManager.enemies);

                    attack.memory.push_back(atkMem);



                }




                /*
                for(auto &enemyPtr : enemyManager.enemies)
                {
                    Enemy &enemy = *enemyPtr.get();

                    float enemyAngle = math::angleBetweenVectors(owner.pos,enemy.pos);
                    float compareAngle = math::angleDiff(owner.rotation,enemyAngle);

                    if(compareAngle < radius && compareAngle > -radius && math::distance(owner.pos,enemy.pos) <= weapon.attackRange)
                    {
                        shapes.createLine(owner.pos.x,owner.pos.y,enemy.pos.x,enemy.pos.y,1,sf::Color::Red);

                        float finalDamage = weapon.attackDamage;
                        if(enemy.creature)
                            finalDamage *= owner.getEvilDamageMultiplier();
                        if(enemy.construct)
                            finalDamage *= owner.getConstructDamageMultiplier();

                        enemy.health -= finalDamage;


                    }


                }

                */




                /*
            weapon.weaponID = Weapon::Sledgehammer;
            weapon.melee = true;

            weapon.attackDamage = 50;
            weapon.attackRange = 32;
            weapon.attackSpeed = 30;
            weapon.attackStun = 30;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            */




            }

            /*

            { // Draw Code



                sf::Vector2f leftEndPos = math::angleCalc(owner.pos,baseRot-radius,weapon.attackRange);
                sf::Vector2f rightEndPos = math::angleCalc(owner.pos,baseRot+radius,weapon.attackRange);

                shapes.createLine(owner.pos.x,owner.pos.y,leftEndPos.x,leftEndPos.y,1,sf::Color::Blue);
                shapes.createLine(owner.pos.x,owner.pos.y,rightEndPos.x,rightEndPos.y,1,sf::Color::Blue);
            }

            */

        }


        if(attack.attackType == attack.melee)
        {


            Weapon weapon = owner.characterClass.meleeWeapon;

            float baseRot = owner.rotation;
            float radius = weapon.attackRadius/2;



            if(attack.firstFrame)
            { // Attack Code
                attack.firstFrame = false;


                for(auto &chunk : worldManager.currentWorld.chunks)
                {
                    sf::Vector2i chunkPos(chunk.pos.x/1024,chunk.pos.y/1024);
                    sf::Vector2i checkPos(owner.pos.x/1024,owner.pos.y/1024);
                    if(checkPos == chunkPos)
                    {

                        for(int x = 0; x != 32; x++)
                            for(int y = 0; y != 32; y++)
                        {
                            ChunkTile &tile = chunk.tiles[x][y];
                            int tilePosX = (chunk.pos.x)+(x*32)+16;
                            int tilePosY = (chunk.pos.y)+(y*32)+16;

                            if(tile.health <= 0)
                                continue;

                            if(math::distance(owner.pos,sf::Vector2f(tilePosX,tilePosY)) > weapon.attackRange)
                                continue;



                            float tileAngle = math::angleBetweenVectors(owner.pos,sf::Vector2f(tilePosX,tilePosY));
                            float compareAngle = math::angleDiff(owner.rotation,tileAngle);


                            if(compareAngle < radius && compareAngle > -radius)
                            {
                                float finalDamage = owner.characterClass.meleeWeapon.attackDamage;

                                finalDamage *= owner.getConstructDamageMultiplier();

                                bool tileDestroyed = tile.affectHealth(finalDamage);

                                if(tileDestroyed)
                                    chunk.updateChunkImage(sf::Vector2i(x*32,y*32));

                            }
                        }
                    }
                }

                for(auto &enemyPtr : enemyManager.enemies)
                {
                    Enemy &enemy = *enemyPtr.get();

                    float enemyAngle = math::angleBetweenVectors(owner.pos,enemy.pos);
                    float compareAngle = math::angleDiff(owner.rotation,enemyAngle);

                    if(compareAngle < radius && compareAngle > -radius && math::distance(owner.pos,enemy.pos) <= weapon.attackRange)
                    {
                        // shapes.createLine(owner.pos.x,owner.pos.y,enemy.pos.x,enemy.pos.y,1,sf::Color::Red);

                        float finalDamage = weapon.attackDamage;
                        if(enemy.creature)
                        {
                            if(owner.characterClass.focusable && owner.characterClass.focusStacks > 0)
                                finalDamage += finalDamage*(0.01*owner.characterClass.focusStacks);

                            finalDamage *= owner.getEvilDamageMultiplier();
                        }

                        if(enemy.construct)
                            finalDamage *= owner.getConstructDamageMultiplier();

                        bool enemyKilled = enemy.affectHealth(finalDamage);
                        if(enemyKilled)
                        {
                            owner.kills++;
                            if(owner.characterClass.focusable)
                                owner.characterClass.focusStacks += 5;

                            enemyManager.deadEnemies.push_back(enemyPtr);
                            enemyManager.enemies.remove(enemyPtr);
                        }
                    }
                }




                /*
            weapon.weaponID = Weapon::Sledgehammer;
            weapon.melee = true;

            weapon.attackDamage = 50;
            weapon.attackRange = 32;
            weapon.attackSpeed = 30;
            weapon.attackStun = 30;

            weapon.attackRadius = 45;

            weapon.magSize = 1;
            weapon.reloadSpeed = 0;

            */




            }

            { // Draw Code



                // sf::Vector2f leftEndPos = math::angleCalc(owner.pos,baseRot-radius,weapon.attackRange);
                // sf::Vector2f rightEndPos = math::angleCalc(owner.pos,baseRot+radius,weapon.attackRange);

                // shapes.createLine(owner.pos.x,owner.pos.y,leftEndPos.x,leftEndPos.y,1,sf::Color::Blue);
                // shapes.createLine(owner.pos.x,owner.pos.y,rightEndPos.x,rightEndPos.y,1,sf::Color::Blue);


                shapes.createCone(owner.pos,baseRot-90,radius*2,weapon.attackRange,sf::Color::Blue);

            }
        }
    }
    AnyDeletes(attacks);
}




bool playerCamera()
{
    if(playerManager.players.empty())
        return false;

   gvars::view1.setCenter(playerManager.players.back().get()->pos);

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

void drawLoadingText(std::string text)
{
    sfe::RichText richText;
    richText.setCharacterSize(20);
    richText.setFont(gvars::defaultFont);
    richText.setPosition(300+RESOLUTION.x/2,300+RESOLUTION.y/2);

    richText << sf::Color::White << text;

    richText.setOrigin(richText.getLocalBounds().width/2,richText.getLocalBounds().height/2);

    window.draw(richText);
    window.display();
    window.clear();
}

void jobsMenu()
{
    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");
    sf::Texture* arrowButton = &texturemanager.getTexture("ArrowButton.png");
    static bool needsWorld = true;
    if(needsWorld)
    {
        needsWorld = false;

        drawLoadingText("Generating World");
        worldManager.generateWorld(20,100);
        drawLoadingText("Generating Spawners");
        spawnControlManager.setupSpawners();

        std::cout << "Building Chunk Images \n";
        drawLoadingText("Generating Chunk Images");
        for(auto &chunk : worldManager.currentWorld.chunks)
            chunk.buildChunkImage();

        playerManager.makePlayer(sf::Vector2f(worldManager.currentWorld.chunks.front().pos.x+(32*16),worldManager.currentWorld.chunks.front().pos.y+(32*16)));

        drawLoadingText("Generating Initial Paths");
        spawnControlManager.pathSpawners();


    }

    if(inputState.key[Key::X].time == 1)
    {
        needsWorld = true;
        enemyManager.enemies.clear();
        spawnControlManager.spawnControllers.clear();
    }


    drawChat();
    drawFPSandData();

}

void runnersMenu()
{
    sf::Texture* hudButton = &texturemanager.getTexture("HUDTab.png");
    sf::Texture* arrowButton = &texturemanager.getTexture("ArrowButton.png");

    if(playerManager.players.empty())
        return;

    Player &player = *playerManager.players.back().get();

    static Trait* selectedTrait = nullptr;
    static bool needsClass = false;
    static int viewWeapon = -1;

    if(selectedTrait != nullptr)
    {
        std::cout << "Selected Trait: " <<  selectedTrait->name << std::endl;
    }


    sf::Vector2f HUDPos(-141, 254);

    shapes.createText(HUDPos.x+60,HUDPos.y+15,15,sf::Color::White,"Name: " + player.name, &gvars::hudView);
    shapes.createText(HUDPos.x+60,HUDPos.y+30,15,sf::Color::White,"Class: " + player.characterClass.name, &gvars::hudView);
    int classButton = shapes.createImageButton(sf::Vector2f(HUDPos.x+60-10,HUDPos.y+30+10),*arrowButton,"",0, &gvars::hudView);
    if(shapes.shapeHovered(classButton))
    {
        shapes.createSquare(gvars::mousePos.x-5,gvars::mousePos.y-10,gvars::mousePos.x+150,gvars::mousePos.y+10,sf::Color::Black);
        shapes.createText(gvars::mousePos.x,gvars::mousePos.y-10,10,sf::Color::Yellow,"    Choose your class!");
        if(inputState.lmbTime == 1)
            needsClass = true;

    }


    shapes.createText(HUDPos.x+60,HUDPos.y+45,15,sf::Color::White,"Range: " + player.characterClass.rangeWeapon.name, &gvars::hudView);
    shapes.createText(HUDPos.x+60,HUDPos.y+60,15,sf::Color::White,"Melee: " + player.characterClass.meleeWeapon.name, &gvars::hudView);


    int traitOffset = 0;
    for(auto &trait : player.traits)
    {
        if(trait.name == "Locked")
            shapes.createText(HUDPos.x+60,HUDPos.y+75+(20*traitOffset),15,sf::Color(100,100,100),"Trait: " + trait.name, &gvars::hudView);
        else
            shapes.createText(HUDPos.x+60,HUDPos.y+75+(20*traitOffset),15,sf::Color::White,"Trait: " + trait.name, &gvars::hudView);

        sf::Vector2f buttPos(HUDPos.x+50,HUDPos.y+85+(20*traitOffset));
        int traitButton = shapes.createImageButton(buttPos,*arrowButton,"",0, &gvars::hudView);

        if(shapes.shapeHovered(traitButton))
        {

            shapes.createSquare(gvars::mousePos.x-5,gvars::mousePos.y-10,gvars::mousePos.x+150,gvars::mousePos.y+10,sf::Color::Black);
            shapes.createText(gvars::mousePos.x,gvars::mousePos.y-10,10,sf::Color::Yellow,"    Choose new trait!");

            if(inputState.lmbTime == 1)
            {
                selectedTrait = &trait;
            }
        }


        traitOffset++;
    }

    if(needsClass)
    {
        traitOffset = 0;
        int xOffset = 345;

        shapes.createText(HUDPos.x+xOffset,HUDPos.y+15+(20*traitOffset),15,sf::Color(100,100,100),"Classes", &gvars::hudView);

        for(auto &classy : characterClassManager.classes)
        {
            if(!classy.playable)
                continue;

            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset),15,sf::Color::White,classy.name, &gvars::hudView);


            sf::Vector2f buttPos(HUDPos.x+xOffset-10,HUDPos.y+40+(20*traitOffset));
            int chooseClassButton = shapes.createImageButton(buttPos,*arrowButton,"",0, &gvars::hudView);

            if(shapes.shapeHovered(chooseClassButton))
            {
                if(inputState.lmbTime == 1)
                {
                    needsClass = false;
                    player.characterClass = classy;
                }
            }

            traitOffset++;
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset++),12,sf::Color(200,200,200),classy.description, &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset++),12,sf::Color(200,200,200),classy.abilityDescription, &gvars::hudView);

            std::string weaponNames = "Weapons: ";
            weaponNames.append(classy.rangeWeapon.name);
            weaponNames.append(" / ");
            weaponNames.append(classy.meleeWeapon.name);

            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset++),12,sf::Color(200,200,200),weaponNames, &gvars::hudView);

        }
    }
    else if(selectedTrait != nullptr)
    {
        traitOffset = 0;
        int xOffset = 345;

        shapes.createText(HUDPos.x+xOffset,HUDPos.y+15+(20*traitOffset),15,sf::Color(200,200,200),"Traits, (Stack Count) ", &gvars::hudView);

        for(auto &trait : traitManager.baseTraits)
        {
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset),15,sf::Color::White,"Trait: " + trait.name, &gvars::hudView);


            sf::Vector2f buttPos(HUDPos.x+xOffset-10,HUDPos.y+40+(20*traitOffset));
            int traitButton = shapes.createImageButton(buttPos,*arrowButton,"",0, &gvars::hudView);

            if(shapes.shapeHovered(traitButton))
            {
                if(inputState.lmbTime == 1)
                {
                    *selectedTrait = trait;
                    selectedTrait = nullptr;
                }
            }

            traitOffset++;
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+30+(20*traitOffset),12,sf::Color(200,200,200),trait.description, &gvars::hudView);



            traitOffset++;
        }
    }
    else
    {
        int xOffset = 345;
        int yOSet = 1;


        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"*Stats* ", &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Move Speed: " + std::to_string(player.getMoveSpeed()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Max Stamina: " + std::to_string((int) player.getStaminaMax()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Stamina Regen: " + std::to_string(player.getStaminaRegen()), &gvars::hudView);
        yOSet++;
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Max Health: " + std::to_string((int) player.getHealthMax()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Armor Reduction: " + std::to_string(player.getArmorReduction()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Cyan,"* Energy Shield Health: " + std::to_string(player.getEnergyShieldMax()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Cyan,"* Energy Shield Reduction: " + std::to_string(player.getEnergyShieldArmorReduction()), &gvars::hudView);
        yOSet += 2;
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Range Damage: " + std::to_string(player.characterClass.rangeWeapon.attackDamage), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Melee Damage: " + std::to_string(player.characterClass.meleeWeapon.attackDamage), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Construct Multiplier: " + std::to_string(player.getConstructDamageMultiplier()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Evil Damage Multiplier: " + std::to_string(player.getEvilDamageMultiplier()), &gvars::hudView);
        yOSet++;
        {
            if(player.characterClass.unstoppable)
            {
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Unstoppable! ", &gvars::hudView);
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color(200,200,200),"* When at 0 health, Continues acting for 10 seconds before falling. Can be healed. ", &gvars::hudView);
            }
            if(player.characterClass.bulletsPierce)
            {
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Piercing Rounds! ", &gvars::hudView);
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color(200,200,200),"* Bullets have unlimited penetrating power. ", &gvars::hudView);
            }
            if(player.characterClass.focusable)
            {
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Moment of Focus! ", &gvars::hudView);
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color(200,200,200),"* Per Focus Stack: +1% Damage, Resistence, and Attack Speed. 1 stack decays per second. ", &gvars::hudView);
            }
        }


        yOSet++;
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Revive Multiplier: " + std::to_string(player.getReviveMultiplier()), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Healing Bullet Multiplier: " + std::to_string(player.getHealBulletMultiplier()), &gvars::hudView);
        yOSet += 3;
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Kills/Deaths: " + std::to_string(player.kills) + "/" + std::to_string(player.deaths), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Revives(ed): " + std::to_string(player.reviveCount) + "/" + std::to_string(player.revivedCount), &gvars::hudView);
        shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Missions Win/Lost: " + std::to_string(player.missionsComplete) + "/" + std::to_string(player.missionsFailed), &gvars::hudView);



        // Weapon Display Time!
        yOSet = 0;
        xOffset += 436;
        Weapon rangeWeapon = player.characterClass.rangeWeapon;
        Weapon meleeWeapon = player.characterClass.meleeWeapon;

        if(rangeWeapon.weaponID != Weapon::Nothing)
        {
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"*Range: " + rangeWeapon.name + "*", &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Damage: " + std::to_string(rangeWeapon.attackDamage), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Range: " + std::to_string(rangeWeapon.attackRange), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Delay: " + std::to_string(rangeWeapon.attackSpeed), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Stun: " + std::to_string(rangeWeapon.attackStun), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Spread: " + std::to_string(rangeWeapon.attackRadius), &gvars::hudView);
            yOSet++;
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Capacity: " + std::to_string(rangeWeapon.magSize), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Restock Delay: " + std::to_string(rangeWeapon.reloadSpeed), &gvars::hudView);
            yOSet++;
            if(rangeWeapon.bulletAmount > 1)
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Projectiles: " + std::to_string(rangeWeapon.bulletAmount), &gvars::hudView);
            if(rangeWeapon.beam)
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Beam!", &gvars::hudView);
            if(rangeWeapon.arcAmount > 0)
                shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::Red,"* Arcs Jumps: " + std::to_string(rangeWeapon.arcAmount), &gvars::hudView);
            yOSet++;
        }

        if(meleeWeapon.weaponID != Weapon::Nothing)
        {
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"*Melee: " + meleeWeapon.name + "*", &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Damage: " + std::to_string(meleeWeapon.attackDamage), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Range: " + std::to_string(meleeWeapon.attackRange), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Delay: " + std::to_string(meleeWeapon.attackSpeed), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Attack Stun: " + std::to_string(meleeWeapon.attackStun), &gvars::hudView);
            shapes.createText(HUDPos.x+xOffset,HUDPos.y+(15*yOSet++),15,sf::Color::White,"* Swing Arc: " + std::to_string(meleeWeapon.attackRadius), &gvars::hudView);
            yOSet++;

        }






    }


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

        buttonPos.y += 20;
        int togglevSync = shapes.createImageButton(buttonPos,texturemanager.getTexture("ArrowButton.png"),"",180,&gvars::hudView);
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

        if(shapes.shapeHovered(togglevSync))
        {
            std::string onOrOff;
            if(gvars::vSync)
                onOrOff = "On";
            else
                onOrOff = "Off";
            shapes.createText(gvars::mousePos,9,sf::Color::White,"  Toggle VSync! Currently: " + onOrOff);
            shapes.shapes.back().layer = 15075;
            if((inputState.lmbTime == 1))
            {
                toggle(gvars::vSync);
                window.setVerticalSyncEnabled(gvars::vSync);
            }


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
        worldManager.currentWorld.printWalkables();




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

void WorldChunk::updateChunkImage(sf::Vector2i updatePos)
{
    static sf::Texture &wallTex = texturemanager.getTexture("GenericWall.png");
    static sf::Texture &floorTex = texturemanager.getTexture("GenericFloor.png");

    static sf::Texture &turretTex = texturemanager.getTexture("GenericTurretPlatform.png");
    static sf::Texture &coreTex = texturemanager.getTexture("GenericCore.png");
    static sf::Texture &spawnTex = texturemanager.getTexture("GenericSpawn.png");

    static sf::Texture &weakfenceTex = texturemanager.getTexture("GenericWeakFence.png");


    for(int i = 0; i != 32; i++)
        for(int t = 0; t != 32; t++)
    {
        sf::Vector2i drawPos((i*32),(t*32));

        if(drawPos != updatePos)
            continue;

        if(tiles[i][t].type == ChunkTile::WALL)
        {
            chunkImage.copy(wallTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::FLOOR)
        {
            chunkImage.copy(floorTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::WEAKFENCE)
        {
            chunkImage.copy(weakfenceTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::CORE)
        {
            chunkImage.copy(coreTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::ENEMYSPAWNER)
        {
            chunkImage.copy(spawnTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::TURRETLIGHT)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }
        if(tiles[i][t].type == ChunkTile::TURRETHEAVY)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::TURRETRANDOM)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }

    }

    chunkTexture.loadFromImage(chunkImage);
}


void WorldChunk::buildChunkImage()
{
    static sf::Texture &wallTex = texturemanager.getTexture("GenericWall.png");
    static sf::Texture &floorTex = texturemanager.getTexture("GenericFloor.png");

    static sf::Texture &turretTex = texturemanager.getTexture("GenericTurretPlatform.png");
    static sf::Texture &coreTex = texturemanager.getTexture("GenericCore.png");
    static sf::Texture &spawnTex = texturemanager.getTexture("GenericSpawn.png");

    static sf::Texture &weakfenceTex = texturemanager.getTexture("GenericWeakFence.png");

    chunkImage.create(32*32,32*32,sf::Color::Transparent);


    for(int i = 0; i != 32; i++)
        for(int t = 0; t != 32; t++)
    {
        sf::Vector2f drawPos((i*32),(t*32));

        if(tiles[i][t].type == ChunkTile::WALL)
        {
            chunkImage.copy(wallTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::FLOOR)
        {
            chunkImage.copy(floorTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::WEAKFENCE)
        {
            chunkImage.copy(weakfenceTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::CORE)
        {
            chunkImage.copy(coreTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::ENEMYSPAWNER)
        {
            chunkImage.copy(spawnTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::TURRETLIGHT)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }
        if(tiles[i][t].type == ChunkTile::TURRETHEAVY)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }

        if(tiles[i][t].type == ChunkTile::TURRETRANDOM)
        {
            chunkImage.copy(turretTex.copyToImage(),drawPos.x,drawPos.y);
        }

    }

    chunkTexture.loadFromImage(chunkImage);
}

void drawWorld()
{
    sf::Clock drawTimer;
    drawTimer.restart();








    World &world = worldManager.currentWorld;

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
            // wallSprite.setOrigin(32,32);
        }
        if(floorSprite.getTexture() == nullptr)
        {
            floorSprite.setTexture(floorTex);
            // floorSprite.setOrigin(32,32);
        }
        if(weakfenceSprite.getTexture() == nullptr)
        {
            weakfenceSprite.setTexture(weakfenceTex);
            // weakfenceSprite.setOrigin(16,16);
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

        if(inputState.key[Key::Comma])
        {



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

            if(chunk.tiles[i][t].type == ChunkTile::CORE)
            {
                wallSprite.setPosition(drawPos);
                wallSprite.setColor(sf::Color::Red);
                window.draw(wallSprite);
            }

            if(chunk.tiles[i][t].type == ChunkTile::ENEMYSPAWNER)
            {
                floorSprite.setPosition(drawPos);
                floorSprite.setColor(sf::Color::Green);
                window.draw(floorSprite);
            }

            if(chunk.tiles[i][t].type == ChunkTile::TURRETLIGHT)
            {
                floorSprite.setPosition(drawPos);
                floorSprite.setColor(sf::Color(255,255,0));
                window.draw(floorSprite);
            }
            if(chunk.tiles[i][t].type == ChunkTile::TURRETHEAVY)
            {
                floorSprite.setPosition(drawPos);
                floorSprite.setColor(sf::Color(100,100,0));
                window.draw(floorSprite);
            }

            if(chunk.tiles[i][t].type == ChunkTile::TURRETRANDOM)
            {
                floorSprite.setPosition(drawPos);
                floorSprite.setColor(sf::Color(150,0,150));
                window.draw(floorSprite);
            }

        }

        }

        else
        {
            sf::Sprite chunkSprite;
            chunkSprite.setTexture(chunk.chunkTexture);
            chunkSprite.setPosition(sf::Vector2f(chunk.pos));

            window.draw(chunkSprite);
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











    int drawTime = drawTimer.getElapsedTime().asMicroseconds();
    if(inputState.key[Key::F1])
        std::cout << "Draw Time: " << drawTime << std::endl;

}

void drawPlayers()
{
    static sf::Texture& angelTex = texturemanager.getTexture("Angel.png");
    static sf::Sprite angelSprite;
    if(angelSprite.getTexture() == nullptr)
    {
        angelSprite.setTexture(angelTex);
         angelSprite.scale(sf::Vector2f(0.5,0.5));
        angelSprite.setOrigin(angelTex.getSize().x/2,angelTex.getSize().y/2);
    }


    // Setting View
    sf::View oldView = window.getView();
    window.setView(gvars::view1);

    // Render stuffs
    for(auto &playerPtr : playerManager.players)
    {
        Player &player = *playerPtr.get();
        angelSprite.setPosition(player.pos);
        angelSprite.setRotation(player.rotation-90);
        window.draw(angelSprite);


        std::string staminaString;
        staminaString.append(std::to_string( (int) player.stamina) );
        staminaString.append("/");
        staminaString.append(std::to_string( (int) player.staminaMax));

        if(player.isTired())
            shapes.createText(player.pos.x,player.pos.y+25,10,sf::Color(100,100,100),staminaString);
        else
            shapes.createText(player.pos.x,player.pos.y+25,10,sf::Color::Yellow,staminaString);


        float healthPercent = player.health/player.getHealthMax();

        shapes.createSquare(player.pos.x-27,player.pos.y-17,player.pos.x+52,player.pos.y-3,sf::Color::Black);
        shapes.createSquare(player.pos.x-25,player.pos.y-15,player.pos.x+50*healthPercent,player.pos.y-5,sf::Color::Red);

    }

    // sf::Vector2f squadPos = playerManager.getPlayersAveragePos();
    // shapes.createCircle(squadPos.x,squadPos.y,10,sf::Color::Cyan);


    // Fixing View
    window.setView(oldView);
}

void drawPlayerAttackCooldowns()
{
    if(playerManager.players.empty())
        return;

    Player &player = *playerManager.players.back().get();

    { // Focus Stacks
        if(player.characterClass.focusable)
        {
            static sf::Texture* focusTex;
            if(focusTex == nullptr)
            {
                focusTex = &texturemanager.getTexture("MomentOfFocus.png");
            }

            shapes.createImageButton(sf::Vector2f(500,720),*focusTex,"",0,&gvars::hudView);
            shapes.createText(sf::Vector2f(500-24+1,720+18+1),10,sf::Color::Black,"x"+std::to_string(player.characterClass.focusStacks),&gvars::hudView);
            shapes.createText(sf::Vector2f(500-24-1,720+18-1),10,sf::Color::Black,"x"+std::to_string(player.characterClass.focusStacks),&gvars::hudView);
            shapes.createText(sf::Vector2f(500-24,720+18),10,sf::Color::White,"x"+std::to_string(player.characterClass.focusStacks),&gvars::hudView);

        }
    }

    Weapon &meleeWeapon = player.characterClass.meleeWeapon;
    Weapon &rangeWeapon = player.characterClass.rangeWeapon;

    float meleeBar = 20*(std::max(meleeWeapon.attackSpeedTimer,0.f)/meleeWeapon.attackSpeed);
    float rangeBar = 20*(std::max(rangeWeapon.attackSpeedTimer,0.f)/rangeWeapon.attackSpeed);
    float ammoBar = 20*(std::max((float)rangeWeapon.magCurrent,0.f)/rangeWeapon.magSize);
    float reloadBar = 20*(std::max(rangeWeapon.reloadSpeedTimer,0.f)/rangeWeapon.reloadSpeed);


    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);


    if(rangeWeapon.weaponID != Weapon::Nothing)
    {
        shapes.createSquare(worldPos.x+10,worldPos.y+10,worldPos.x+10+5,worldPos.y+10-rangeBar,sf::Color::Red,0,sf::Color::Transparent,&gvars::hudView);

        shapes.createSquare(worldPos.x+24,worldPos.y+10,worldPos.x+24+5,worldPos.y+10-ammoBar,sf::Color::White,0,sf::Color::Transparent,&gvars::hudView);
        shapes.createSquare(worldPos.x+31,worldPos.y+10,worldPos.x+31+5,worldPos.y+10-reloadBar,sf::Color::Green,0,sf::Color::Transparent,&gvars::hudView);
    }

    if(meleeWeapon.weaponID != Weapon::Nothing)
        shapes.createSquare(worldPos.x+17,worldPos.y+10,worldPos.x+17+5,worldPos.y+10-meleeBar,sf::Color::Blue,0,sf::Color::Transparent,&gvars::hudView);





}

void drawAttacks()
{
    for(auto &attack : attackManager.attacks)
    {
        for(auto &atkMem : attack.memory)
        {
            shapes.createLine(atkMem.startPos.x,atkMem.startPos.y,atkMem.endPos.x,atkMem.endPos.y,1,atkMem.color);
            //AttackMemory.
            if(atkMem.melee)
                shapes.createCone(atkMem.startPos,atkMem.rotation,atkMem.radius,math::distance(atkMem.startPos,atkMem.endPos),atkMem.color);
        }
    }
}

void drawWallInfo()
{
    ChunkTile & tile = worldManager.currentWorld.getTile(sf::Vector2i(gvars::mousePos));

    std::string outPut;
    outPut.append("Health: " + std::to_string(tile.health) + "\n");
    outPut.append("Resistence: " + std::to_string(tile.resistence) + "\n");
    outPut.append("Pos: " + std::to_string(tile.pos.x) +"/"+std::to_string(tile.pos.y)+ "\n");
    shapes.createText(gvars::mousePos.x+10,gvars::mousePos.y+10,15,sf::Color::White,outPut);



}

void drawEnemyInfo()
{
    for(auto &enemyPtr : enemyManager.enemies)
    {
        Enemy &enemy = *enemyPtr.get();


    }
}

void drawPathFinder()
{

    if(inputState.key[Key::Space].time == 1)
    {
        std::cout << "Attepting to make a Path. \n";
        pathCon.storedPath.clear();
        int result = pathCon.makePath(playerManager.players.back().get()->pos,gvars::mousePos);
        std::cout << "Result: " << result << ", path size: " << pathCon.storedPath.size() << std::endl;

    }


    if(inputState.key[Key::T])
    {
        pathCon.drawStoredPath();

        for(auto &spawn : spawnControlManager.spawnControllers)
        {
            if(spawn.targetPathed)
            {

                // std::cout << "Drawing path! Size: " << spawn.storedPath.size() << std::endl;


                sf::Vector2f oldPos;
                bool firstRun = true;

                for (auto &i : spawn.storedPath)
                {
                    sf::Vector2f pathPos;
                    pathPos = i->pos;
                    sf::Color pathColor(255, 0, 0, 255);

                    if (!firstRun)
                        shapes.createLine((oldPos.x + 32) - (32/2),
                                          (oldPos.y + 32) - (32/2),
                                          (pathPos.x + 32) - (32/2),
                                          (pathPos.y + 32) - (32/2), 5, pathColor);

                    oldPos = pathPos;
                    firstRun = false;
                }






            }
        }
    }

}

void renderGame()
{

    drawWorld();

    if(inputState.key[Key::E])
        worldManager.drawWalkableTiles();

    enemyManager.drawEnemies();

    drawPlayers();

    drawAttacks();

    drawPlayerAttackCooldowns();

    if(inputState.key[Key::Tab])
        drawWallInfo();

    drawPathFinder();

    drawEnemyInfo();

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




void spawning()
{
    if(inputState.key[Key::LShift] && inputState.key[Key::R].time == 1)
    {
        enemyManager.makeEnemy(gvars::mousePos);
    }
}

void runPlayerInputs()
{

    playerManager.runPlayerCharacterInput();


    // std::cout << "CanSee: " << visionCheck(playerManager.players.back().get()->pos,gvars::mousePos) << std::endl;

    spawning();
}

void runGame()
{
    static int globalCycle = 0;
    globalCycle++;


    spawnLogic();
    enemyManager.runEnemyLogic();
    playerManager.runPlayerCharacterLogic();
    attackManager.manageAttacks();




    if((globalCycle % 60) == 0)
    {

    }

}
