/*
===============================================================================
AF_ECS_H defninitions
Entity Component System used to process entities and manage them
===============================================================================
*/

#ifndef AF_ECS_H
#define AF_ECS_H
#include "AF_Entity.h"

#define AF_ECS_TOTAL_ENTITIES 1000


typedef struct {
    uint32_t totalEntities;
    AF_Entity entities[AF_ECS_TOTAL_ENTITIES];
} AF_ECS;

static inline void AF_ECS_Init(AF_Entity* _entities){
	// Initialise all entities in the entity pool with default values
	for(uint32_t i = 0; i < AF_ECS_TOTAL_ENTITIES; i++){
 		_entities[i].active = false;
		_entities[i].id = i;
		_entities[i].transform = AF_CTransform3D_ZERO();
		_entities[i].sprite = AF_CSprite_ZERO();
		_entities[i].camera = AF_CCamera_ZERO();
	}
}
void AF_ECS_Update(AF_Entity* _entities);
void AF_ECS_Shutdown(AF_Entity* _entities);
AF_Entity* AF_Entity_System_CreateEntity();
//void AF_RemoveEntity(Entity* _entity);
void AF_ECS_Update(AF_Entity* _entities);


#endif //AF_ECS_H
