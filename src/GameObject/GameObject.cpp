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
    return;
}

void Peashooter::Update()
{
    if (hp > 0)
    {
        if (tick == 0)
        {
            // whether shoot or not
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

void WallnutSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 50)
        {
            world->setHand(HandType::WALLNUT);
        }
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

void CherryBombSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 150)
        {
            world->setHand(HandType::CHERRY_BOMB);
        }
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

void RepeaterSeed::OnClick()
{
    if (world->getHand() == HandType::NONE)
    {
        if (world->getSun() >= 200)
        {
            world->setHand(HandType::REPEATER);
        }
    }
    return;
}

void Repeater::Update()
{
    if (hp > 0)
    {
        if (tick == 0 || tick == 25)
        {
            // whether shoot or not
            world->AddObject(std::make_shared<Pea>(GetX(), GetY(), world));
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

// Your everything begins from here.