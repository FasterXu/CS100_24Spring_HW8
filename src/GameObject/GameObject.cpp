#include "GameObject.hpp"
#include "GameWorld.hpp"

pGameWorld GameObject::getShared()
{
    return world;
}

void Sun::Update()
{
    if (!ground)
    {
        if (sky)
        {
            MoveTo(GetX(), GetY() - 2);
        }
        else
        {
            MoveTo(GetX() - 1, GetY() + time - 6);
        }
        if (time == 0)
        {
            ground = true;
            time = 300;
        }
    }
    else
    {
        if (time == 0)
        {
            hp = 0;
        }
    }
    time--;
}
void Sun::OnClick()
{
    world->setSun(world->getSun() + 25);
    hp = 0;
}

void PlantingSpot::OnClick()
{
    if (world->getHand() == HandType::SUNFLOWER)
    {
        world->AddObject(std::make_shared<Sunflower>(GetX(), GetY(), world));
        world->AddObject(std::make_shared<CooldownMask>(130, WINDOW_HEIGHT - 44, 240, world));
        world->setSun(world->getSun() - 50);
        world->setHand(HandType::NONE);
    }
    else if (world->getHand() == HandType::PEASHOOTER)
    {
        world->AddObject(std::make_shared<Peashooter>(GetX(), GetY(), world));
        world->AddObject(std::make_shared<CooldownMask>(190, WINDOW_HEIGHT - 44, 240, world));
        world->setSun(world->getSun() - 100);
        world->setHand(HandType::NONE);
    }
    else if (world->getHand() == HandType::WALLNUT)
    {
        world->AddObject(std::make_shared<Wallnut>(GetX(), GetY(), world));
        world->AddObject(std::make_shared<CooldownMask>(250, WINDOW_HEIGHT - 44, 900, world));
        world->setSun(world->getSun() - 50);
        world->setHand(HandType::NONE);
    }
    else if (world->getHand() == HandType::CHERRY_BOMB)
    {
        world->AddObject(std::make_shared<CherryBomb>(GetX(), GetY(), world));
        world->AddObject(std::make_shared<CooldownMask>(310, WINDOW_HEIGHT - 44, 1200, world));
        world->setSun(world->getSun() - 150);
        world->setHand(HandType::NONE);
        return;
    }
    else if (world->getHand() == HandType::REPEATER)
    {
        world->AddObject(std::make_shared<Repeater>(GetX(), GetY(), world));
        world->AddObject(std::make_shared<CooldownMask>(370, WINDOW_HEIGHT - 44, 240, world));
        world->setSun(world->getSun() - 200);
        world->setHand(HandType::NONE);
    }
}

void SunflowerSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 50)
        {
            world->setHand(HandType::SUNFLOWER);
        }
    }
    else
    {
        world->setHand(HandType::NONE);
    }
    return;
}

void Sunflower::Update()
{
    if (hp > 0)
    {
        if (tick == 0)
        {
            world->AddObject(std::make_shared<Sun>(GetX(), GetY(), false, world));
            tick = 600;
        }
        tick -= 1;
    }
}

void Sunflower::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

int Sunflower::Collision()
{
    if (hp > 0)
    {
        hp -= 3;
    }
    return 0;
}

void CooldownMask::Update()
{
    if (tick == 0)
    {
        hp = 0;
    }
    tick--;
}

void PeashooterSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 100)
        {
            world->setHand(HandType::PEASHOOTER);
        }
    }
    else
    {
        world->setHand(HandType::NONE);
    }
    return;
}

void Peashooter::Update()
{
    if (hp > 0)
    {
        if (tick == 0)
        {
            if (world->ZombieOnRight(GetX(), GetY()))
            {
                world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, world));
                tick = 30;
            }
        }
        else
        {
            tick -= 1;
        }
    }
}

void Peashooter::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

int Peashooter::Collision()
{
    if (hp > 0)
    {
        hp -= 3;
    }
    return 0;
}

void Pea::Update()
{
    if (hp > 0)
    {
        MoveTo(GetX() + 8, GetY());
        if (GetX() > WINDOW_WIDTH)
        {
            hp = 0;
        }
    }
}

int Pea::Collision()
{
    hp = 0;
    return 2;
}

void WallnutSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 50)
        {
            world->setHand(HandType::WALLNUT);
        }
    }
    else
    {
        world->setHand(HandType::NONE);
    }
    return;
}

void Wallnut::Update()
{
    if (hp > 0)
    {
        if (hp < 4000 / 3)
        {
            ChangeImage(IMGID_WALLNUT_CRACKED);
        }
    }
}

void Wallnut::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

int Wallnut::Collision()
{
    if (hp > 0)
    {
        hp -= 3;
    }
    return 0;
}

void CherryBombSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 150)
        {
            world->setHand(HandType::CHERRY_BOMB);
        }
    }
    else
    {
        world->setHand(HandType::NONE);
    }
    return;
}

void CherryBomb::Update()
{
    if (hp > 0)
    {
        if (tick == 0)
        {
            world->AddObject(std::make_shared<Explosion>(GetX(), GetY(), world));
            hp = 0;
        }
        tick -= 1;
    }
}

void CherryBomb::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

void Explosion::Update()
{
    if (tick == 0)
    {
        hp = 0;
    }
    tick--;
}

int Explosion::Collision()
{
    return 1;
}

void RepeaterSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 200)
        {
            world->setHand(HandType::REPEATER);
        }
    }
    else
    {
        world->setHand(HandType::NONE);
    }
    return;
}

void Repeater::Update()
{
    if (hp > 0)
    {
        if (tick == 0 || tick == 25)
        {
            if (world->ZombieOnRight(GetX(), GetY()))
            {
                world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, world));
            }
            if (tick == 0)
            {
                tick = 30;
            }
            else
            {
                tick -= 1;
            }
        }
        else
        {
            tick -= 1;
        }
    }
}

void Repeater::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

int Repeater::Collision()
{
    if (hp > 0)
    {
        hp -= 3;
    }
    return 0;
}

void Shovel::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        world->setHand(HandType::NONE);
    }
    else if (world->getHand() == HandType::NONE)
    {
        world->setHand(HandType::SHOVEL);
    }
}

void RegularZombie::Update()
{
    if (hp > 0)
    {
        if (!eat)
        {
            MoveTo(GetX() - 1, GetY());
        }
    }
}

void RegularZombie::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

void BucketHeadZombie::Update()
{
    if (hp > 0)
    {
        if (hp <= 200)
        {
            ChangeImage(IMGID_REGULAR_ZOMBIE);
        }
        if (!eat)
        {
            MoveTo(GetX() - 1, GetY());
        }
    }
}

void BucketHeadZombie::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

void PoleVaultingZombie::Update()
{
    if (hp > 0)
    {
        MoveTo(GetX() - 40, GetY());
        for (auto &object : world->getPlants())
        {
            if (world->checkCollision(shared_from_this(), object) && !walk)
            {
                if (tick == 42 & jump == false)
                {
                    PlayAnimation(ANIMID_JUMP_ANIM);
                    jump = true;
                }
                eat = true;
                if (tick == 0 && walk == false)
                {
                    PlayAnimation(ANIMID_WALK_ANIM);
                    walk = true;
                    MoveTo(GetX() - 150, GetY());
                }
                else
                {
                    tick--;
                }
            }
        }
        MoveTo(GetX() + 40, GetY());
        if (!eat)
        {
            if (walk)
            {
                MoveTo(GetX() - 1, GetY());
            }
            else
            {
                MoveTo(GetX() - 2, GetY());
            }
        }
    }
}

void PoleVaultingZombie::OnClick()
{
    if (world->getHand() == HandType::SHOVEL)
    {
        hp = 0;
        world->setHand(HandType::NONE);
    }
}

// Your everything begins from here.