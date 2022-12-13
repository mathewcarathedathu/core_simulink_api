#pragma once

#include <stdint.h>
#include <unordered_set>
#include <set>
#include <string>

#include "func_unit.hpp" 
#include "block.hpp"

using namespace base;


std::string get_block_type_str(components::block* block_)
{

	std::string type_str;

	switch (block_->get_type())
	{
	case ::block_type::E_DIFF:
		type_str =  "Differentiate";
		break;

	case ::block_type::E_GAIN:
		type_str =  "Gain";
		break;

	case ::block_type::E_INPUT:
		type_str =  "Input";
		break;

	case ::block_type::E_INTEG:
		type_str =  "Integration";
		break;

	case ::block_type::E_OUTPUT:
		type_str =  "Output";
		break;

	default:
		type_str =  "Unassigned";
		break;
	}

	return type_str;
}

void merge_sets(std::unordered_set<func_unit*>& target, std::set<func_unit*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); ++s_itr)
	{
		target.insert(target.end(), *s_itr);
	}
}

void merge_sets(std::unordered_set<func_unit*>& target, std::list<func_unit*> source)
{
	for (auto s_itr = source.begin(); s_itr != source.end(); ++s_itr)
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