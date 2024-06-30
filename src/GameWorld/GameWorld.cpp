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
          m_zombies.push_back(std::make_shared<RegularZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), randInt(0, 5) * LAWN_GRID_HEIGHT + FIRST_ROW_CENTER, shared_from_this()));
        }
        else if (rand < P1 + P2)
        {
          // 生成撑杆跳僵尸
        }
        else
        {
          // 生成铁桶僵尸
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
