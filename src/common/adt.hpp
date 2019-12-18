#ifndef WATER_ADT_H
#include <queue>
#include <vector>
#include <algorithm>


namespace water
{
	template <class _Ty, class _Container = std::vector<_Ty>, class _Pr = std::less<typename _Container::value_type>>
	class WaterPriorityQueue : public std::priority_queue<_Ty, _Container, _Pr>
	{
	public:
		void erase(_Ty value)
		{
			for (auto iter = c.begin(); iter != c.end(); ++iter)
			{
				if (*iter == value)
				{
					c.erase(iter);
					break;
				}
			}
			std::make_heap(c.begin(), c.end(), comp);
		}

	};
}

#endif // !WATER_ADT_H
