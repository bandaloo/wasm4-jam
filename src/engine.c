#include "engine.h"
#include "sprites.h"
#include "wasm4.h"

Node *globalEntities;

void addNode(Node **head, void *data) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = (*head);
  (*head) = newNode;
}

void addEntity(Entity *entity) { addNode(&globalEntities, entity); }

/** returns pointer data of Component of given type */
void *findComponent(Entity *entity, ComponentType componentType) {
  Node *components = (Node *)entity;
  while (components != NULL) {
    // trace("looping");
    Component *component = (Component *)components->data;
    if (component->type == componentType) {
      // trace("returning data");
      return component->data;
    }
    components = components->next;
  }
  trace("returning null");
  return NULL;
}

static Component *makeComponent(ComponentType type, void *data) {
  Component *component = malloc(sizeof(Component));
  component->type = type;
  component->data = data;
  return component;
}

Component *makePosComponent(float x, float y) {
  PosComponentData *data = malloc(sizeof(PosComponentData));
  *data = (PosComponentData){.x = x, .y = y};
  return makeComponent(POS, data);
};

Component *makeDrawComponent(Sprite sprite, int ticksPerFrame) {
  DrawComponentData *data = malloc(sizeof(DrawComponentData));
  *data = (DrawComponentData){.sprite = sprite,
                              .ticksPerFrame = ticksPerFrame,
                              .currentFrame = 0,
                              .flipX = false,
                              .flipY = false,
                              .counter = 0};
  return makeComponent(DRAW, data);
}

Component *makePhysicsComponent(float vx, float vy, float ax, float ay,
                                float drag) {
  PhysicsComponentData *data = malloc(sizeof(PhysicsComponentData));
  *data = (PhysicsComponentData){
      .vel = {.x = vx, .y = vy}, .acc = {.x = ax, .y = ay}, .drag = drag};
  return makeComponent(PHYSICS, data);
}

Entity *makePlayer(float x, float y) {
  Node *components = NULL;
  addNode(&components, makePosComponent(x, y));
  addNode(&components, makeDrawComponent(FLOWER_SPRITE, 10));
  addNode(&components, makePhysicsComponent(0, 0, 0, 0, 4));

  // PosComponentData *posComponentData = malloc(sizeof(PosComponentData));
  // *posComponentData = initPosComponentData(x, y);
  // addNode(components, posComponentData);

  // PhysicsComponentData *physicsComponentData =
  //     malloc(sizeof(PhysicsComponentData));
  // *physicsComponentData = initPhysicsComponentData(0, 0, 0, 1, 0.01);
  // addNode(components, physicsComponentData);

  return (Entity *)components;
}

// TODO [cole] use function pointer?

void doDrawSystem() {
  Node *node = globalEntities;
  // trace("do draw system");
  while (node != NULL) {
    // trace("draw!");
    Entity *entity = node->data;
    DrawComponentData *drawComponentData =
        (DrawComponentData *)findComponent(entity, DRAW);
    PosComponentData *posComponentData =
        (PosComponentData *)findComponent(entity, POS);

    if (drawComponentData != NULL && posComponentData != NULL) {
      // trace("drawing something");
      blitCenteredSprite(drawComponentData->sprite, posComponentData->x,
                         posComponentData->y, drawComponentData->currentFrame,
                         drawComponentData->sprite.flags);

      // increment the counter
      drawComponentData->counter++;
      drawComponentData->counter %= drawComponentData->ticksPerFrame;

      // advance to next frame and wrap around if counter got reset
      if (drawComponentData->counter == 0) {
        drawComponentData->currentFrame++;
        drawComponentData->currentFrame %= drawComponentData->sprite.frames;
      }
    }
    // TODO X and Y flip
    node = node->next;
  }
}

void blitCenteredSprite(const Sprite sprite, float x, float y, int currentFrame,
                        uint32_t flags) {
  blitSub(sprite.data, x - sprite.width / 2, y - sprite.height / 2,
          sprite.width, sprite.height, currentFrame * sprite.width, 0,
          sprite.width * sprite.frames, sprite.flags | flags);
}
