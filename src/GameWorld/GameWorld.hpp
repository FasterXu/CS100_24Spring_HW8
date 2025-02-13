#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"

#include "GameObject.hpp"

#include "TextBase.hpp"
#include "utils.hpp"

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
public:
  // Use shared_from_this() instead of "this" to create a pointer to oneself.
  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void AddObject(std::shared_ptr<GameObject> object);

  int getFlow();

  void setFlow(int flow);

  int getSun();

  void setSun(int sun);

  HandType getHand();

  void setHand(HandType hand);

  bool checkCollision(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>);

  bool ZombieOnRight(int, int);

  std::list<std::shared_ptr<GameObject>> getPlants();

private:
  std::list<std::shared_ptr<GameObject>> m_objects;
  std::list<std::shared_ptr<GameObject>> m_plants;
  std::list<std::shared_ptr<TextBase>> m_texts;
  std::list<std::shared_ptr<GameObject>> m_zombies;
  TextBase m_sunText = TextBase(60, 520, "50");
  TextBase m_flowText = TextBase(700, 560, "Flow: 0");
  int m_wave;
  int m_sun;
  int g_time;
  int zombie_tick;
  HandType m_hand;
};

#endif // !GAMEWORLD_HPP__
