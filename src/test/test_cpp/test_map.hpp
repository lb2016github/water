#pragma once
#include <map>
#include <unordered_map>
using namespace std;

struct MapKey
{
	MapKey(int value) : value(value) {}
	bool operator <(const MapKey& key) const
	{
		return value < key.value;
	}
	bool operator == (const MapKey& key) const
	{
		return value == key.value;
	}

	int value{ 0 };
};

template<>
struct hash<MapKey>
{
	size_t operator()(const MapKey& key) const
	{
		return key.value;
	}
};

struct MapKeyHash
{
	size_t operator ()(const MapKey& key) const
	{
		return key.value;
	}
};

void test()
{
	std::map<MapKey, int> map = 
	{
		{3, 3},
	};
	std::unordered_map<MapKey, int> u_map = {
		{3, 3},
	};
}