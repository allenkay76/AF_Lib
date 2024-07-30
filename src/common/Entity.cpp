#include "ECS/Entities/Entity.h"


//AF_MemoryPool* Entity::memoryPool = nullptr;

Entity::Entity(size_t _id, const std::string &_tag) : 
    //cTransform3D(std::make_shared<CTransform3D>()),
    //cShape(std::make_shared<CShape>()),
    //cCollision(std::make_shared<CCollision3D>()),
    //cInput(std::make_shared<CInput>()),
    //cScore(std::make_shared<CScore>()),
    //cLight(std::make_shared<CLight>()),
    //cSprite(std::make_shared<CSprite2D>()),
    m_active(true),
    m_id(_id),
    m_tag(_tag)
{}

Entity::Entity() :
    //cTransform3D(std::make_shared<CTransform3D>()),
    //cShape(std::make_shared<CShape>()),
    //cCollision(std::make_shared<CCollision3D>()),
    //cInput(std::make_shared<CInput>()),
    //cScore(std::make_shared<CScore>()),
    //cLight(std::make_shared<CLight>()),
    //cSprite(std::make_shared<CSprite2D>()),
    m_active(true),
    m_id(-1),
    m_tag("")
{}

bool Entity::IsActive() const
{
    return m_active;
}

const std::string& Entity::Tag() const
{
    return m_tag;
}



/*
// Overloaded new operator using the memory pool
void* Entity::operator new(size_t size) {
    if (memoryPool == nullptr) {
        std::cerr << "Memory pool not initialized.\n";
        return ::operator new(size);  // Fallback to global new
    }
    return memoryPool->Alloc();
}

// Overloaded delete operator using the memory pool
void Entity::operator delete(void* p) {
    if (memoryPool == nullptr) {
        std::cerr << "Memory pool not initialized.\n";
        ::operator delete(p);  // Fallback to global delete
    } else {
        memoryPool->Free(p);
    }
}
*/
