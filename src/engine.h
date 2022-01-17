#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/** enum to distinguish components */
typedef enum { POS, DRAW, PHYSICS, COLLISION } ComponentType;

//////////
// Core //
//////////

/** 2d point */
typedef struct {
  float x, y;
} Vec2;

/** element of a linked list that points to generic data */
typedef struct Node {
  struct Node *next;
  void *data;
} Node;

/** the type of a Component and the data that represents its state */
typedef struct {
  ComponentType type;
  void *data;
} Component;

/** an Entity is merely a linked list of components */
typedef Node Entity;

/** global list of Entities that get iterated over during the game update */
extern Node *globalEntities;

/** adds a generic node to the head of a generic linked list */
void addNode(Node **head, void *data);

/** adds an Entity to the global list */
void addEntity(Entity *entity);

/** find a Component of the given type on an Entity */
void *findComponent(Entity *entity, ComponentType componentType);

////////////////
// Components //
////////////////

/** POS component */
typedef struct {
  Vec2 pos;
} PosComponentData;

Component *makePosComponent(float x, float y);

/** DRAW component requires POS component */
typedef struct {
  int width;
  int height;
  int numFrames;
  int currentFrame;
  int ticksPerFrame;
  bool flipX;
  bool flipY;
  int counter;
  uint8_t *spriteData;
} DrawComponentData;

Component *makeDrawComponent(int width, int height, int numFrames,
                             uint8_t *spriteData);

/** PHYSICS component requires POS component */
typedef struct {
  Vec2 vel;
  Vec2 acc;
  float drag;
} PhysicsComponentData;

Component *makePhysicsComponent(float vx, float vy, float ax, float ay,
                                float drag);

///////////////
// Factories //
///////////////

Entity *makePlayer(float x, float y);

// void makeDrawComponent() {
// }