#include "PhysicsObjectComponent.h"
#include "physics/Physics_Consts.h"
#include "engine/EngineOptions.h"

#if !VG_ENABLE_INLINE
#include "PhysicsObjectComponent.inl"
#endif

using namespace vg::core;

namespace vg::engine
{
    //--------------------------------------------------------------------------------------
    bool PhysicsObjectComponent::registerProperties(IClassDesc & _desc)
    {
        super::registerProperties(_desc);

        registerPropertyEnum(PhysicsObjectComponent, physics::Category, m_category, "Category");
        setPropertyDescription(PhysicsObjectComponent, m_category, "The physics category this object belongs to");

        registerOptionalPropertyEnumBitfield(PhysicsObjectComponent, m_useCollisionMask, physics::CategoryFlag, m_collisionMask, "Collision Mask");
        setPropertyDescription(PhysicsObjectComponent, m_collisionMask, "Enable/Disable collisions with specifig object categories");

        return true;
    }

    //--------------------------------------------------------------------------------------
    PhysicsObjectComponent::PhysicsObjectComponent(const string & _name, IObject * _parent) :
        super(_name, _parent)
    {
 
    }

    //--------------------------------------------------------------------------------------
    PhysicsObjectComponent::~PhysicsObjectComponent()
    {

    }

    //--------------------------------------------------------------------------------------
    void PhysicsObjectComponent::SetCategory(physics::Category _category) 
    { 
        m_category = _category;
    }

    //--------------------------------------------------------------------------------------
    void PhysicsObjectComponent::EnableCollisionMask(bool _enable)
    {
        m_useCollisionMask = _enable;
    }

    //--------------------------------------------------------------------------------------
    void PhysicsObjectComponent::SetCollisionMask(physics::CategoryFlag _mask)
    {
        m_collisionMask = _mask;
    }
}