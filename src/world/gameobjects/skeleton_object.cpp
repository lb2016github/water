#include "skeleton_object.h"
#include "world/components/animator_component.h"
#include "render/render_const.h"

namespace water
{
	namespace world
	{
		void SkeletonObject::init()
		{
			auto modelPtr = m_parent.lock();
			if (!modelPtr) return;
			auto pMeshComp = GET_COMPONENT(modelPtr, MeshComponent);
			if (!pMeshComp) return;
			auto pMeshPtr = pMeshComp->get_mesh_ptr();
			if (!pMeshPtr) return;
			auto skeletonPtr = SkeletonManager::instance()->getSkeleton(pMeshPtr->skeID);
			if (!skeletonPtr) return;
			auto meshPtr = std::make_shared<render::MeshData>(render::MeshMode::POINTS);
			meshPtr->usage = render::MeshUsage::DYNAMIC_DRAW;
			for (int i = 0; i < skeletonPtr->m_jointCount; ++i)
			{
				auto& joint = skeletonPtr->m_joints[i];
				auto bindPose = joint.m_invBindPose;
				bindPose.inverse();
				meshPtr->position.emplace_back(bindPose.getTranslation());
			}
			meshPtr->updateFormat();
			// set meshPtr to self
			auto meshComp = GET_COMPONENT(this, MeshComponent);
			assert(meshComp);
			meshComp->set_mesh_ptr(meshPtr);
			// init material component
			auto matComp = GET_COMPONENT(this, MaterialComponent);
			assert(matComp);
			auto mat_group = render::Material::loadFromFile("materials/skeleton.mat");
			assert(mat_group.size() > 0);
			matComp->set_material(mat_group[0]);
		}
		void SkeletonObject::tick(float deltaTimeMic)
		{
			SpaceObject::tick(deltaTimeMic);
			auto modelPtr = m_parent.lock();
			if (!modelPtr) return;
			auto animatorComp = GET_COMPONENT(modelPtr, AnimatorComponent);
			if (!animatorComp) return;
			SkeletonPosePtr curPose = animatorComp->getCurPose();
			if (!curPose) return;
			// todo update mesh with curPose
			auto meshComp = GET_COMPONENT(this, MeshComponent);
			auto meshPtr = meshComp->get_mesh_ptr();
			assert(curPose->m_gJointPose.size() == meshPtr->position.size());
			for (int i = 0; i < curPose->m_gJointPose.size(); ++i)
			{
				meshPtr->position[i] = curPose->m_gJointPose[i].getTranslation();
			}
			meshPtr->dirty = true;
		}
	}
}

