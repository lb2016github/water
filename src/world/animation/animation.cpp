#include "animation.h"
#include "skeleton.h"
#include <algorithm>
#include "common/log.h"


namespace water
{
	namespace world
	{
		void AnimationClipManager::addAnimClipData(SkeletonID skeId, AnimationClipDataPtr animClipData)
		{
			m_skeletonAnimClipData[skeId] = animClipData;
		}
		AnimationClipDataPtr AnimationClipManager::getAnimClipDataPtr(SkeletonID skeId)
		{
			auto rst = m_skeletonAnimClipData.find(skeId);
			if (rst == m_skeletonAnimClipData.end())
			{
				auto ptr = std::make_shared<AnimationClipData>();
				m_skeletonAnimClipData[skeId] = ptr;
				return ptr;
			}
			return rst->second;
		}
		AnimationClipManager* AnimationClipManager::instance()
		{
			static AnimationClipManager instance;
			return &instance;
		}
		AnimationClipData::AnimationClipData()
		{
		}
		AnimationClipPtr AnimationClipData::getAnimClip(const std::string& animName)
		{
			auto rst = m_animClipData.find(animName);
			if (rst == m_animClipData.end())
			{
				return nullptr;
			}
			return rst->second;
		}
		void AnimationClipData::addAnimClip(const std::string& animName, AnimationClipPtr animClip)
		{
			m_animClipData[animName] = animClip;
		}

		// ============================ AnimationFrameData START ========================== //
		JointFrameData::JointFrameData(unsigned int numTrans, unsigned int numRot, unsigned int numScale):
			m_numTrans(numTrans), m_numRot(numRot), m_numScale(numScale)
		{
			if (m_numTrans > 0)
			{
				m_trans = new Vector3KeyFrame[m_numTrans];
			}
			if (m_numRot > 0)
			{
				m_rot = new QuaternionKeyFrame[m_numRot];
			}
			if (m_scale > 0)
			{
				m_scale = new Vector3KeyFrame[m_numScale];
			}
		}
		JointFrameData::JointFrameData(const JointFrameData& animFrameData)
		{
			m_numTrans = animFrameData.m_numTrans;
			m_numRot = animFrameData.m_numRot;
			m_numScale = animFrameData.m_numScale;
			m_trans = new Vector3KeyFrame[m_numTrans];
			m_rot = new QuaternionKeyFrame[m_numRot];
			m_scale = new Vector3KeyFrame[m_numScale];
			for (int i = 0; i < m_numTrans; ++i)
			{
				m_trans[i] = animFrameData.m_trans[i];
			}
			for (int i = 0; i < m_numRot; ++i)
			{
				m_rot[i] = animFrameData.m_rot[i];
			}
			for (int i = 0; i < m_numScale; ++i)
			{
				m_scale[i] = animFrameData.m_scale[i];
			}
		}
		JointFrameData::JointFrameData(JointFrameData&& animFrameData)
		{
			m_numTrans = animFrameData.m_numTrans;
			m_numRot = animFrameData.m_numRot;
			m_numScale = animFrameData.m_numScale;
			m_trans = animFrameData.m_trans;
			animFrameData.m_trans = nullptr;
			m_rot = animFrameData.m_rot;
			animFrameData.m_rot = nullptr;
			m_scale = animFrameData.m_scale;
			animFrameData.m_scale = nullptr;
		}
		JointFrameData& JointFrameData::operator=(const JointFrameData& animFrameData)
		{
			if (this == &animFrameData) return *this;
			SAFE_DELETE_ARRAY(m_trans);
			SAFE_DELETE_ARRAY(m_scale);
			SAFE_DELETE_ARRAY(m_rot);

			m_numTrans = animFrameData.m_numTrans;
			m_numRot = animFrameData.m_numRot;
			m_numScale = animFrameData.m_numScale;
			if (m_numTrans > 0)
			{
				m_trans = new Vector3KeyFrame[m_numTrans];
				for (int i = 0; i < m_numTrans; ++i)
				{
					m_trans[i] = animFrameData.m_trans[i];
				}
			}
			if (m_numRot > 0)
			{
				m_rot = new QuaternionKeyFrame[m_numRot];
				for (int i = 0; i < m_numRot; ++i)
				{
					m_rot[i] = animFrameData.m_rot[i];
				}
			}
			if (m_scale > 0)
			{
				m_scale = new Vector3KeyFrame[m_numScale];
				for (int i = 0; i < m_numScale; ++i)
				{
					m_scale[i] = animFrameData.m_scale[i];
				}
			}
			return *this;
		}
		JointFrameData& JointFrameData::operator=(JointFrameData&& animFrameData)
		{
			if (this == &animFrameData) return *this;
			SAFE_DELETE_ARRAY(m_trans);
			SAFE_DELETE_ARRAY(m_scale);
			SAFE_DELETE_ARRAY(m_rot);
			m_numTrans = animFrameData.m_numTrans;
			m_numRot = animFrameData.m_numRot;
			m_numScale = animFrameData.m_numScale;
			m_trans = animFrameData.m_trans;
			m_rot = animFrameData.m_rot;
			m_scale = animFrameData.m_scale;
			animFrameData.m_scale = nullptr;
			animFrameData.m_trans = nullptr;
			animFrameData.m_rot = nullptr;
			animFrameData.m_numTrans = 0;
			animFrameData.m_numScale = 0;
			animFrameData.m_numRot = 0;
			return *this;
		}
		JointFrameData::~JointFrameData()
		{
			SAFE_DELETE_ARRAY(m_trans);
			SAFE_DELETE_ARRAY(m_rot);
			SAFE_DELETE_ARRAY(m_scale);
		}
		void JointFrameData::sortByTime()
		{
			std::sort(m_trans, m_trans + m_numTrans);
			std::sort(m_rot, m_rot + m_numRot);
			std::sort(m_scale, m_scale + m_numScale);
		}

		template<class T, class Q>
		inline T getFrameValue(float timeMic, Q* dataArray, unsigned int dataLen, unsigned int& preIndex)
		{
			// check start and end
			auto startPtr = &(dataArray[0]);
			if (timeMic <= startPtr->m_timeMic) return startPtr->m_data;
			auto endPtr = &(dataArray[dataLen - 1]);
			if (timeMic >= endPtr->m_timeMic) return endPtr->m_data;

			Q* before{ nullptr };
			Q* after{ nullptr };
			unsigned int index = 0;

			// to speed up search speed, the index starts from preIndex
			Q* curData = &(dataArray[preIndex]);
			if (curData->m_timeMic < timeMic)
			{
				before = curData;
				index = preIndex;
			}

			for (++index; index < dataLen; ++index)
			{
				if (curData->m_timeMic < timeMic)
				{
					before = curData;
					preIndex = index;
				}
				else if (curData->m_timeMic >= timeMic)
				{
					after = curData;
					break;
				}
			}
			assert(before && after);
			float factor = (timeMic - before->m_timeMic) / (after->m_timeMic - before->m_timeMic);
			return Q::lerp(*before, *after, factor);
		}
		
		JointPose JointFrameData::getJointPose(float timeMic)
		{
			math3d::Vector3 trans(0, 0, 0), scale(1, 1, 1);
			math3d::Quaternion rot(1, 0, 0, 0);
			if (m_numTrans > 0)
			{
				trans = getFrameValue<math3d::Vector3, Vector3KeyFrame>(timeMic, m_trans, m_numTrans, m_preTransIndex);
			}
			if (m_numScale > 0)
			{
				scale = getFrameValue<math3d::Vector3, Vector3KeyFrame>(timeMic, m_scale, m_numScale, m_preScaleIndex);
			}
			if (m_numRot > 0)
			{
				rot = getFrameValue<math3d::Quaternion, QuaternionKeyFrame>(timeMic, m_rot, m_numRot, m_preRotIndex);
			}
			return { trans, scale, rot };
		}
		// ============================ AnimationFrameData END ========================== //

		// ============================ AnimationClip START ========================== //
		AnimationClip::AnimationClip(SkeletonPtr skPtr, float duration):
			m_skeleton(skPtr), m_duration(duration)
		{
			m_jointFrameData = new JointFrameData * [m_skeleton->m_jointCount];
			for (int i = 0; i < m_skeleton->m_jointCount; ++i)
			{
				m_jointFrameData[i] = new JointFrameData(0, 0, 0);
			}
		}
		AnimationClip::~AnimationClip()
		{
			delete[] m_jointFrameData;
		}
		void AnimationClip::setJointFrameData(unsigned int jointIdx, const JointFrameData& jointFrameData)
		{
			*(m_jointFrameData[jointIdx]) = jointFrameData;
		}
		void AnimationClip::setJointFrameData(unsigned int jointIdx, JointFrameData&& jointFrameData)
		{
			*(m_jointFrameData[jointIdx]) = jointFrameData;
		}
		SkeletonPosePtr AnimationClip::getPose(float timeMic)
		{
			SkeletonPosePtr posePtr = std::make_shared<SkeletonPose>(m_skeleton);
			for (int i = 0; i < m_skeleton->m_jointCount; ++i)
			{
				posePtr->m_jointPoses[i] = m_jointFrameData[i]->getJointPose(timeMic);
			}
			return posePtr;
		}
		float AnimationClip::getDuration()
		{
			return m_duration;
		}
		void Vector3KeyFrame::setData(float timeMic, float x, float y, float z)
		{
			m_timeMic = timeMic;
			m_data.x = x;
			m_data.y = y;
			m_data.z = z;
		}
		// ============================ AnimationClip END ========================== //
		bool Vector3KeyFrame::operator<(const Vector3KeyFrame& vkf)
		{
			return m_timeMic < vkf.m_timeMic;
		}
		math3d::Vector3 Vector3KeyFrame::lerp(const Vector3KeyFrame& a, const Vector3KeyFrame& b, float factor)
		{
			return math3d::Vector3::lerp(a.m_data, b.m_data, factor);
		}
		void QuaternionKeyFrame::setData(float timeMic, float w, float x, float y, float z)
		{
			m_timeMic = timeMic;
			m_data.w = w;
			m_data.x = x;
			m_data.y = y;
			m_data.z = z;
		}
		bool QuaternionKeyFrame::operator<(const QuaternionKeyFrame& vkf)
		{
			return m_timeMic < vkf.m_timeMic;
		}
		math3d::Quaternion QuaternionKeyFrame::lerp(const QuaternionKeyFrame& a, const QuaternionKeyFrame& b, float factor)
		{
			return math3d::Quaternion::slerp(a.m_data, b.m_data, factor);
		}
}
}
