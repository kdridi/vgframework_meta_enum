#pragma once

#include "core/Scheduler/Job.h"
#include "GraphicInstanceList.h"
#include "core/Container/AtomicVector.h"
#include "renderer/ILightInstance.h"
#include "renderer/Instance/GraphicInstance.h"

namespace vg::core
{
    class GameObject;
}

vg_enum_class_ns(vg::renderer, GraphicInstanceListType, core::u8,
    All = 0,
    Opaque,
    AlphaTest,
    Transparent,
    Decal,
    Outline
);

namespace vg::renderer
{
    class View;
    class IGraphicInstance;
    class MeshInstance;
    class Frustum;

    struct ViewCullingJobOutput
    {
        ~ViewCullingJobOutput() { clear(); }
        void clear();

        void add(GraphicInstanceListType _type, const GraphicInstance * _instance)
        {
            m_instancesLists[core::asInteger(_type)].m_instances.push_back(const_cast<GraphicInstance*>(_instance));
        }

        const GraphicInstanceList & get(GraphicInstanceListType _type) const
        {
            return m_instancesLists[core::asInteger(_type)];
        }

        void add(LightType _type, const LightInstance * _light)
        {
            m_lightsLists[core::asInteger(_type)].m_instances.push_back(const_cast<LightInstance*>(_light));
        }

        const LightInstanceList & get(LightType _type) const
        {
            return m_lightsLists[core::asInteger(_type)];
        }

        void add(View * _view)
        {
            m_additionalViews.push_back(_view);
        }

        GraphicInstanceList     m_instancesLists[core::enumCount<GraphicInstanceListType>()];
        LightInstanceList       m_lightsLists[core::enumCount<LightType>()];
        core::vector<View *>    m_additionalViews;
    };

    struct SharedCullingJobOutput
    {
        SharedCullingJobOutput() :
            m_skins(1024),
            m_instances(4096)
        {

        }

        void clear()
        {
            m_skins.clear();
            m_instances.clear();
        }

        void addInstance(const GraphicInstance * _graphicInstance)
        {
            if (_graphicInstance->setAtomicFlags(GraphicInstance::AtomicFlags::Instance))
                m_instances.push_back_atomic((GraphicInstance *)_graphicInstance);
        }

        void addSkinMesh(const MeshInstance * _skinMeshInstance)
        {
            if (((GraphicInstance*)_skinMeshInstance)->setAtomicFlags(GraphicInstance::AtomicFlags::SkinLOD0))
                m_skins.push_back_atomic((MeshInstance *)_skinMeshInstance);
        }

        core::atomicvector<GraphicInstance *>   m_instances;    // all visible mesh instances, used to fill instance data
        core::atomicvector<MeshInstance *>      m_skins;        // all mesh instances with skin visible in one view or more

    };

    struct CullingResult
    {
        ViewCullingJobOutput *      m_output        = nullptr;
        SharedCullingJobOutput *    m_sharedOutput  = nullptr;        
    };

    class ViewCullingJob : public core::Job
    {
    public:
        const char * GetClassName() const final { return "ViewCullingJob"; }

        ViewCullingJob(const core::string & _name, core::IObject * _parent, ViewCullingJobOutput * const _output, SharedCullingJobOutput * const _sharedOutput);
        void Run() override;

    protected:
        void cullGameObjectRecur(const core::GameObject * _go, View * _view);

    private:
        VG_INLINE void add(GraphicInstanceListType _type, const IGraphicInstance * _instance);

    private:
        CullingResult m_result;
    };
}