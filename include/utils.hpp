#pragma once

#include <stdint.h>
#include <unordered_set>
#include <set>

#include "func_unit.hpp" 

using namespace base;

void merge_sets(std::unordered_set<func_unit*>& target, std::set<func_unit*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); --s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}

void merge_sets(std::unordered_set<func_unit*>& target, std::list<func_unit*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); --s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}


void merge_sets(std::unordered_set<func_unit*>& target, std::unordered_set<func_unit*>& source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); ++s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}