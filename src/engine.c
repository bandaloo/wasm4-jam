#include "engine.h"
#include "wasm4.h"

#include <stddef.h>

Node *globalEntities;

void addNode(Node **head, void *data) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = (*head);
  (*head) = newNode;
}

void addEntity(Entity *entity) { addNode(&globalEntities, entity); }

void *findComponent(Entity *entity, ComponentType componentType) {
  Node *components = (Node *)entity;
  while (components != NULL) {
    trace("looping");
    Component *component = (Component *)components->data;
    if (component->type == componentType) {
      trace("returning data");
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
  *data = (PosComponentData){.pos = {.x = x, .y = y}};
  return makeComponent(POS, data);
};

Component *makeDrawComponent(int width, int height, int numFrames,
                             uint8_t *spriteData) {
  DrawComponentData *data = malloc(sizeof(DrawComponentData));
  *data = (DrawComponentData){.width = width,
                              .height = height,
                              .numFrames = numFrames,
                              .currentFrame = 0,
                              .ticksPerFrame = 1,
                              .flipX = false,
                              .flipY = false,
                              .counter = 0,
                              .spriteData = spriteData};
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