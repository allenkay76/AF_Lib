
#include "ECS/Entities/EntityManager.h"
#include "Utils/LogManager.h"

//std::vector<CTransform3D*> m_transformComponents;
//std::vector<CLight*> m_lightComponents;



EntityManager::EntityManager() //:
    //m_totalEntities(0),
    //m_entities(std::vector<std::shared_ptr<Entity>>()),
    //m_entityMap(std::map<std::string, Entity>()),
    //m_entitiesToAdd(std::vector<Entity>())
{
    
}

 void EntityManager::Init(){

    /*
    if (m_entityMemPool.Init(sizeof(Entity), 10)) {
        std::cout << "Memory pool for Entity initialized successfully.\n";

        
        // Set the static memory pool pointer for TestMemory
        Entity::memoryPool = &m_entityMemPool;
    }else {
        std::cerr << "Failed to initialize memory pool for TestMemory.\n";
    }
    */
 }

void EntityManager::Shutdown(){
    LogManager::Log("Deleting: " , m_entities.size() , " Entities" );
    for(size_t i = 0; i < m_entities.size(); i++){
        // Delete all the entities
        delete((m_entities)[i]);
    }
}
    

Entity* EntityManager::MakeEntity(const std::string& _tag)
{
    // if using memory pool, then create entity from pool data
    Entity* entity = new Entity(m_totalEntities++, _tag);// std::make_shared<Entity>(m_totalEntities++, _tag);
    m_entitiesToAdd.push_back(entity);

    // Fix this
    m_entities.push_back(entity);
    return entity;
}

std::vector<Entity*>& EntityManager::GetEntities()
{
    return m_entities;
}

const std::vector<Entity*> &EntityManager::GetIntities(const std::string &_tag)
{
    if(_tag == ""){
        // Do something if checking with an empty tag
    }
    return m_entities;
}

void EntityManager::RemoveDeadEntities(std::vector<Entity*> &_vec)
{
    for(size_t i = 0; i < _vec.size(); i++){
        if(_vec[i]->IsActive() == false){
            //remove this item
        }
    }
}

std::shared_ptr<std::vector<Entity*>> EntityManager::CreateEntities(const glm::vec3 _startingPos, const size_t _arraySize, std::string _tag){
    std::shared_ptr<std::vector<Entity*>> entitiesVector = std::make_shared<std::vector<Entity*>>();
    for(size_t i = 0; i < _arraySize; i++){
        Entity* createdEntity = CreateEntity(_startingPos,  _tag);
        
        //store a local reference pointer
        m_entities.push_back(createdEntity);

        //store a shared vector that will be returned for use by whoever called the function
        entitiesVector->push_back(createdEntity);
    }
    
    return entitiesVector;
}

Entity* EntityManager::CreateEntity(const glm::vec3 _startingPos, std::string _tag){
    // Get sprite info
        // Add entity to new entity system
        Entity* entity = MakeEntity(_tag);

        entity->AddComponent<CTransform3D>(_startingPos, glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0),glm::mat4(1.0f));
        return entity;
}


void EntityManager::UpdateEntities(){
    //CollectTransformComponents();
    //CollectLightComponents();
    for(size_t i = 0; i < m_entities.size(); i++){
        //CTransform2D& entityTransform = m_entities[i]->GetComponent<CTransform2D>();
    }
}

//Singleton pattern to get the instance
std::shared_ptr<EntityManager> EntityManager::GetInstance()
{
    static std::shared_ptr<EntityManager> instance = std::make_shared<EntityManager>();
    return instance;
}

/*
void EntityManager::CollectTransformComponents(){
    //delete the transform vector and update it with this new collection.
    m_transformComponents.clear();
    for(size_t i = 0; i < m_entities.size(); i++){
        if(m_entities[i]->GetComponent<CTransform3D>().has){
            m_transformComponents.push_back(m_entities[i]->GetComponent<CTransform3D>());
        }
    }
}

void EntityManager::CollectLightComponents(){
    //delete the transform vector and update it with this new collection.
    m_transformComponents.clear();
    for(size_t i = 0; i < m_entities.size(); i++){
        if(m_entities[i]->GetComponent<CLight>().has){
            m_transformComponents.push_back(m_entities[i]->GetComponent<CLight>());
        }
    }
}

std::vector<CTransform3D*>& EntityManager::GetTransformComponents(){
    return m_transformComponents;
}

std::vector<CLight*>& EntityManager::GetLightComponents(){
    return m_lightComponents;
}*/