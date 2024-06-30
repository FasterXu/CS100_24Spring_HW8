#include "GameWorld.hpp"
#include "GameObject.hpp"
GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
  // YOUR CODE HERE
  m_flow = 0;
  m_sun = 50;
  g_time = 0;
  m_hand = HandType::NONE;
  bg = std::make_shared<Background>(shared_from_this());
  m_objects.push_back(bg);
  ss = std::make_shared<SunflowerSeed>(shared_from_this());
  m_objects.push_back(ss);
  m_objects.push_back(std::make_shared<PeashooterSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<WallnutSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<CherryBombSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<RepeaterSeed>(shared_from_this()));
  m_objects.push_back(std::make_shared<Shovel>(shared_from_this()));

  for (int x = 0; x < 3; x++)
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
  for (auto &object : m_objects)
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
  m_sunText.SetText(std::to_string(m_sun));
  m_flowText.SetText("Flow: " + std::to_string(m_flow));

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
}

void GameWorld::AddObject(std::shared_ptr<GameObject> object)
{
  m_objects.push_back(object);
}

int GameWorld::getFlow()
{
  return m_flow;
}

void GameWorld::setFlow(int flow)
{
  m_flow = flow;
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
