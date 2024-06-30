#include "GameWorld.hpp"
#include "GameObject.hpp"
GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
  // YOUR CODE HERE
  m_wave = 0;
  m_sun = 50;
  g_time = 0;
  m_hand = HandType::NONE;
  m_objects.push_back(std::make_shared<Background>(shared_from_this()));
  m_objects.push_back(std::make_shared<SunflowerSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<PeashooterSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<WallnutSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<CherryBombSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<RepeaterSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<Shovel>(shared_from_this()));
  for (int x = 0; x < 9; x++)
  {
    for (int y = 0; y < 5; y++)
    {
      m_objects.push_back(std::make_shared<PlantingSpot>(FIRST_COL_CENTER + x * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + y * LAWN_GRID_HEIGHT, shared_from_this()));
    }
  }
}

LevelStatus GameWorld::Update()
{
  // YOUR CODE HERE
  g_time++;
  if (g_time == 180)
  {
    m_objects.push_back(std::make_shared<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT - 1, 1, shared_from_this()));
  }
  else if ((g_time - 180) % 300 == 0)
  {
    m_objects.push_back(std::make_shared<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT - 1, 1, shared_from_this()));
  }
  if (zombie_tick == 0)
  {
    m_wave++;
    if (m_wave)
    {
      int num_zombie = (15 + m_wave) / 10;
      for (int i = 0; i < num_zombie; i++)
      {
        int P1 = 20;
        int P2 = 2 * std::max(m_wave - 8, 0);
        int P3 = 3 * std::max(m_wave - 15, 0);
        int P_total = P1 + P2 + P3;
        int rand = randInt(0, P_total);
        if (rand < P1)
        {
          m_zombies.push_back(std::make_shared<RegularZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT, shared_from_this()));
        }
        else if (rand < P1 + P2)
        {
          //
        }
        else
        {
          //
        }
      }
      zombie_tick = std::max(600 - 20 * m_wave, 150);
    }
  }

  for (auto &object : m_objects)
  {
    object->Update();
  }
  for (auto &object : m_plants)
  {
    object->Update();
  }
  for (auto &object : m_zombies)
  {
    object->Update();
  }

  for (auto &plant : m_plants)
  {
    for (auto &zombie : m_zombies)
    {
      if (checkCollision(plant, zombie))
      {
        printf("Checking\n");
        switch (plant->Collision())
        {
        case 0:
          zombie->SetEat(true);
          zombie->PlayAnimation(ANIMID_EAT_ANIM);
          break;
        case 1:
          zombie->setHp(0);
          break;
        case 2:
          zombie->setHp(zombie->getHp() - 20);
          break;

        default:
          break;
        }
      }
    }
  }

  for (auto it = m_objects.begin(); it != m_objects.end();)
  {
    if ((*it)->getHp() <= 0)
    {
      it = m_objects.erase(it);
    }
    else
    {
      ++it;
    }
  }
  for (auto it = m_plants.begin(); it != m_plants.end();)
  {
    if ((*it)->getHp() <= 0)
    {
      it = m_plants.erase(it);
    }
    else
    {
      ++it;
    }
  }
  for (auto it = m_zombies.begin(); it != m_zombies.end();)
  {
    if ((*it)->getHp() <= 0)
    {
      it = m_zombies.erase(it);
    }
    else
    {
      ++it;
    }
  }

  for (auto &zombie : m_zombies)
  {
    if (zombie->GetX() < 0)
    {
      return LevelStatus::LOSING;
    }
  }

  for (auto &zombie : m_zombies)
  {
    bool collided = false;
    for (auto &plant : m_plants)
    {
      if (checkCollision(zombie, plant))
      {
        collided = true;
        break;
      }
    }
    if (!collided)
    {
      zombie->SetEat(false);
      zombie->PlayAnimation(ANIMID_WALK_ANIM);
    }
  }

  zombie_tick--;
  m_sunText.SetText(std::to_string(m_sun));
  m_flowText.SetText("Flow: " + std::to_string(m_wave));

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
}

void GameWorld::AddObject(std::shared_ptr<GameObject> object)
{
  m_plants.push_back(object);
}

int GameWorld::getFlow()
{
  return m_wave;
}

void GameWorld::setFlow(int flow)
{
  m_wave = flow;
}

int GameWorld::getSun()
{
  return m_sun;
}

void GameWorld::setSun(int sun)
{
  m_sun = sun;
}

HandType GameWorld::getHand()
{
  return m_hand;
}

void GameWorld::setHand(HandType hand)
{
  m_hand = hand;
}

bool GameWorld::checkCollision(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2)
{
  int x_dist = std::abs(obj1->GetX() - obj2->GetX());
  int y_dist = std::abs(obj1->GetY() - obj2->GetY());
  if (x_dist < (obj1->GetWidth() + obj2->GetWidth()) / 2 && y_dist < (obj1->GetHeight() + obj2->GetHeight()) / 2)
  {
    return true;
  }
  return false;
}

bool GameWorld::ZombieOnRight(int x, int y)
{
  for (auto &zombie : m_zombies)
  {
    if (zombie->GetY() == y && zombie->GetX() >= x)
    {
      return true;
    }
  }
  return false;
}