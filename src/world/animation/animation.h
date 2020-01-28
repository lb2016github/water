#ifndef WATER_ANIMATION_H
#define WATER_ANIMATION_H
#include "math3d/math3d.hpp"
#include "skeleton.h"
#include <map>
#include "common/common.h"
#include <set>

namespace water
{
	namespace world
	{
		struct Vector3KeyFrame
		{
			float m_timeMic;
			math3d::Vector3 m_data;

			void setData(float timeMic, float x, float y, float z);

			bool operator<(const Vector3KeyFrame& vkf);
			static math3d::Vector3 lerp(const Vector3KeyFrame& a, const Vector3KeyFrame& b, float factor);
		};
		struct QuaternionKeyFrame
		{
			float m_timeMic;
			math3d::Quaternion m_data;

			void setData(float timeMic, float w, float x, float y, float z);
			bool operator<(const QuaternionKeyFrame& vkf);
			static math3d::Quaternion lerp(const QuaternionKeyFrame& a, const QuaternionKeyFrame& b, float factor);
		};
		/*
		key frame data of one joint
		*/
		class JointFrameData
		{
		public:
			JointFrameData(unsigned int numTrans, unsigned int numRot, unsigned int numScale = 1);
			JointFrameData(const JointFrameData& animFrameData);
			JointFrameData(JointFrameData&& animFrameData);
			JointFrameData& operator=(const JointFrameData& animFrameData);
			JointFrameData& operator=(JointFrameData&& animFrameData);
			~JointFrameData();
			/*
			sort by time
			*/
			void sortByTime();
			/*
			get transformation by time in microsecond
			*/
			JointPose getJointPose(float timeMic);

		public:
			unsigned int m_numTrans{ 0 };
			unsigned int m_numRot{ 0 };
			unsigned int m_numScale{ 0 };
			Vector3KeyFrame* m_trans{ nullptr };
			QuaternionKeyFrame* m_rot{ nullptr };
			Vector3KeyFrame* m_scale{ nullptr };
		private:
			// record the pre index
			unsigned int m_preTransIndex{ 0 };
			unsigned int m_preRotIndex{ 0 };
			unsigned int m_preScaleIndex{ 0 };
		};

		/*
		data of one animation clip
		*/
		class AnimationClip: std::enable_shared_from_this<AnimationClip>
		{
		public:
			AnimationClip(SkeletonPtr skPtr, float duration);
			~AnimationClip();
		public:
			void setJointFrameData(unsigned int jointIdx, const JointFrameData& jointFrameData);
			void setJointFrameData(unsigned int jointIdx, JointFrameData&& jointFrameData);
			/*
			get skeleton pose with given time in microsecond
			@param timeMic: time in microsecond
			@return SkeletonPose
			*/
			SkeletonPosePtr getPose(float timeMic);
			/*
			get duration of animation clip
			@return time/microsecond
			*/
			float getDuration();
		public:
			SkeletonPtr m_skeleton;		// id of skeleton
			JointFrameData** m_jointFrameData;	// joint frames
			float m_duration;
		};

		DECL_SHARED_PTR(AnimationClip);

		/*
		animation clip data of one skeleton
		*/
		struct AnimationClipData
		{
			AnimationClipData();

			AnimationClipPtr getAnimClip(const std::string& animName);
			void addAnimClip(const std::string& animName, AnimationClipPtr animClip);
			std::set<std::string> getAnimList();
			bool isEmpty();

			std::map<std::string, AnimationClipPtr> m_animClipData;
			std::string m_defaultClipName{ "" };
		};
		DECL_SHARED_PTR(AnimationClipData);

		/*
		Manager of animation clip
		*/
		class AnimationClipManager
		{
		private:
			std::map<SkeletonID, AnimationClipDataPtr> m_skeletonAnimClipData;
		public:
			void addAnimClipData(SkeletonID skeId, AnimationClipDataPtr animClipData);
			AnimationClipDataPtr getAnimClipDataPtr(SkeletonID skeId, bool force = false);
		public:
			static AnimationClipManager* instance();
		};
	}
}

#endif // !WATER_ANIMATION_H
