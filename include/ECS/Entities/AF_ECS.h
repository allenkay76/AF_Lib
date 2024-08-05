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
    uint32_t entitiesCount;
    uint32_t currentEntity;
    AF_Entity entities[AF_ECS_TOTAL_ENTITIES];
} AF_ECS;

static inline void AF_ECS_Init(AF_ECS* _ecs){
	// Initialise all entities in the entity pool with default values
	for(uint32_t i = 0; i < AF_ECS_TOTAL_ENTITIES; i++){
		AF_Entity* entity = &_ecs->entities[i];
		entity->alive = false;
 		entity->enabled = false;
		entity->id = i;
		entity->transform = AF_CTransform3D_ZERO();
		entity->sprite = AF_CSprite_ZERO();
		entity->camera = AF_CCamera_ZERO();
	}
	_ecs->entitiesCount = AF_ECS_TOTAL_ENTITIES;
}
//void AF_ECS_Update(AF_Entity* _entities);
//void AF_ECS_Shutdown(AF_Entity* _entities);
static inline AF_Entity* AF_ECS_CreateEntity(AF_ECS* _ecs){
    if(_ecs->currentEntity >= _ecs->entitiesCount){
	    AF_Log_Error("ECS: Ran out of entities !!!\n");
	    return NULL;
    }

    // increment the entity count and return the reference to the next available entity
    _ecs->currentEntity++;
    AF_Entity* entity = &_ecs->entities[_ecs->currentEntity];
    entity->alive = true;
    entity->enabled = true;
    return entity;
}

static inline AF_CCamera* AF_ECS_AddCamera_Component(AF_Entity* _entity){
	if(_entity == NULL){
		AF_Log_Error("AF_ECS_AddCameraComponent:: Recieved a null Entity\n");
		return NULL;
	}
	AF_CCamera* component = &_entity->camera;
	component->has = true;
	component->enabled = true;
	return component;
}

static inline AF_CTransform3D* AF_ECS_AddTransform3D_Component(AF_Entity* _entity){
	if(_entity == NULL){
		AF_Log_Error("AF_ECS_AddTransform3DComponent:: Recieved a null Entity\n");
		return NULL;
	}
	AF_CTransform3D* component = &_entity->transform;
	component->has = true;
	component->enabled = true;
	return component;
}

static inline AF_CSprite* AF_ECS_AddSprite_Component(AF_Entity* _entity){
	if(_entity == NULL){
		AF_Log_Error("AF_ECS_AddSprite:: Recieved a null Entity\n");
		return NULL;
	}
	AF_CSprite* component = &_entity->sprite;
	component->has = true;
	component->enabled = true;
	return component;
}


//void AF_RemoveEntity(Entity* _entity);
void AF_ECS_Update(AF_Entity* _entities);


#endif //AF_ECS_H
