#ifndef WATER_TIMELINE_H
#include <set>

namespace water
{
	struct TimelineObserver
	{
		virtual void onTime(float curTime) = 0;
	};

	/* 
	@Desc Timeline
	@Property m_duration, if m_duration < 0, then m_duration is infinate
	@Property m_curTime
	@Property m_speedRate, speed rate of timeline, 
		if m_speedRate < 0, then timeline goes in reverse direction; 
		else if 0 < m_spped_rate < 1£¬timeline moves slow; 
		else m_speedRate > 1£¬timeline moves fast
	@Property m_loop
	@Property m_playing
	the logic of ending timeline when it is not looped
		if m_speedRate < 0:
			return m_curTime <= 0;
		else:
			return m_curTime >= m_duration;
	the logic of updating current time:
		m_curTime += deltaTime * m_speedRate;
	*/
	class Timeline
	{
	protected:
		// duration of timeline
		float m_duration{ -1 };
		// current time of timeline
		float m_curTime{ 0 };
		// speed rate of timeline
		float m_speedRate{ 1.0 };
		// whether timeline is loop
		float m_loop{ false };
		// whether timeline is playing
		float m_playing{ false };
		// observers
		std::set<TimelineObserver*> m_sObserver;
	public:
		Timeline(float duration);
		Timeline(float duration, bool loop);
		Timeline(float duration, bool loop, float speedRate);
		~Timeline();
	protected:
		void virtual onTick();

	public:
		/*
		play timeline from 0
		*/
		void play();
		/*
		replay timeline
		*/
		void replay();
		/*
		pause timeline
		*/
		void pause();
		/*
		tick
		*/
		void tick(float deltaTime);
		/*
		get current time
		*/
		float getCurrentTime();
		/*
		set current time
		*/
		void setCurrentTime(float time);
		/*
		set current time by ratio, the ratio is in range[0, 1];
		*/
		void setCurrentTimeRatio(float timeRatio);
		/*
		set loop
		*/
		void setLoop(bool loop);
		/*
		add observer
		*/
		void addObserver(TimelineObserver* obs);
		/*
		remove observer
		*/
		void removeObserver(TimelineObserver* obs);
		/*
		set speed rate
		*/
		void setSpeedRate(float speedRate);
		/*
		get speed rate
		*/
		float getSpeedRate();
	private:
		void _informTime(float time);
	};
}
#endif // !WATER_TIMELINE_H
