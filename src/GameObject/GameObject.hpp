#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

enum class HandType
{
  NONE,
  SUNFLOWER,
  PEASHOOTER,
  WALLNUT,
  CHERRY_BOMB,
  REPEATER,
  SHOVEL
};

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this;
  GameObject(int imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld world)
      : ObjectBase(imageID, x, y, layer, width, height, animID), world(world){};
  virtual ~GameObject() = default;
  virtual void Update() = 0;
  virtual void OnClick() = 0;
  pGameWorld getShared();
  int getHp() { return hp; }

protected:
  pGameWorld world;
  int hp = 1;
};

class Background : public GameObject
{
public:
  Background(pGameWorld world)
      : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION, world){};
  ~Background() = default;
  void Update() override {};
  void OnClick() override {};
};

class Sun : public GameObject
{
public:
  Sun(int x, int y, int sky, pGameWorld world)
      : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM, world), sky(sky), ground(false)
  {
    if (sky)
    {
      time = randInt(63, 263);
    }
    else
    {
      time = 12;
    }
  };
  ~Sun() = default;
  void Update() override;
  void OnClick() override;

private:
  bool sky;
  bool ground;
  int time;
};

class PlantingSpot : public GameObject
{
public:
  PlantingSpot(int x, int y, pGameWorld world)
      : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION, world){};
  ~PlantingSpot() = default;
  void Update() override {};
  void OnClick() override;
};

class SunflowerSeed : public GameObject
{
public:
  SunflowerSeed(pGameWorld world)
      : GameObject(IMGID_SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world){};
  ~SunflowerSeed() = default;
  void Update() override {};
  void OnClick() override;
};

class Sunflower : public GameObject
{
public:
  Sunflower(int x, int y, pGameWorld world)
      : GameObject(IMGID_SUNFLOWER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { hp = 300; };
  ~Sunflower() = default;
  void Update() override;
  void OnClick() override;

private:
  int tick = randInt(30, 600);
};

class CooldownMask : public GameObject
{
public:
  CooldownMask(int x, int y, int tick, pGameWorld world)
      : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION, world), tick(tick){};
  ~CooldownMask() = default;
  void Update() override;
  void OnClick() override {};

private:
  int tick;
};

class PeashooterSeed : public GameObject
{
public:
  PeashooterSeed(pGameWorld world)
      : GameObject(IMGID_SEED_PEASHOOTER, 190, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world){};
  ~PeashooterSeed() = default;
  void Update() override {};
  void OnClick() override;
};

class Peashooter : public GameObject
{
public:
  Peashooter(int x, int y, pGameWorld world)
      : GameObject(IMGID_PEASHOOTER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { hp = 300; };
  ~Peashooter() = default;
  void Update() override;
  void OnClick() override;

private:
  int tick = 0;
};

class Pea : public GameObject
{
public:
  Pea(int x, int y, pGameWorld world)
      : GameObject(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION, world) {}
  ~Pea() = default;
  void Update() override;
  void OnClick() override {};
};

class WallnutSeed : public GameObject
{
public:
  WallnutSeed(pGameWorld world)
      : GameObject(IMGID_SEED_WALLNUT, 250, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world){};
  ~WallnutSeed() = default;
  void Update() override {};
  void OnClick() override;
};

class Wallnut : public GameObject
{
public:
  Wallnut(int x, int y, pGameWorld world)
      : GameObject(IMGID_WALLNUT, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { hp = 4000; };
  ~Wallnut() = default;
  void Update() override;
  void OnClick() override;
};

class CherryBombSeed : public GameObject
{
public:
  CherryBombSeed(pGameWorld world)
      : GameObject(IMGID_SEED_CHERRY_BOMB, 310, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world){};
  ~CherryBombSeed() = default;
  void Update() override {};
  void OnClick() override;
};

class CherryBomb : public GameObject
{
public:
  CherryBomb(int x, int y, pGameWorld world)
      : GameObject(IMGID_CHERRY_BOMB, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { hp = 4000; };
  ~CherryBomb() = default;
  void Update() override;
  void OnClick() override;

private:
  int tick = 15;
};

class Explosion : public GameObject
{
public:
  Explosion(int x, int y, pGameWorld world)
      : GameObject(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION, world){};
  ~Explosion() = default;
  void Update() override;
  void OnClick() override {};

private:
  int tick = 3;
};

class RepeaterSeed : public GameObject
{
public:
  RepeaterSeed(pGameWorld world)
      : GameObject(IMGID_SEED_REPEATER, 370, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world){};
  ~RepeaterSeed() = default;
  void Update() override {};
  void OnClick() override;
};

class Repeater : public GameObject
{
public:
  Repeater(int x, int y, pGameWorld world)
      : GameObject(IMGID_REPEATER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { hp = 300; };
  ~Repeater() = default;
  void Update() override;
  void OnClick() override {};

private:
  int tick = 0;
};

class Shovel : public GameObject
{
public:
  Shovel(pGameWorld world)
      : GameObject(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION, world){};
  ~Shovel() = default;
  void Update() override {};
  void OnClick() override;
};

//-----------------Zombie Comes----------------//

#endif // !GAMEOBJECT_HPP__
