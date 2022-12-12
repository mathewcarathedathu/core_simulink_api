#pragma once

#include <stdint.h>
#include <unordered_set>
#include <set>

#include "block.hpp" 

using namespace components;

void merge_sets(std::unordered_set<block*>& target, std::set<block*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); --s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}

void merge_sets(std::unordered_set<block*>& target, std::list<block*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); --s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}


void merge_sets(std::unordered_set<block*>& target, std::unordered_set<block*>& source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); ++s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}