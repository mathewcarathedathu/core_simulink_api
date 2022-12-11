// Definition of subsystem in simulink model

#pragma once

#include <stdint.h>
#include <string>
#include <set>

#include "func_unit.hpp"
#include "block.hpp"

namespace components
{
	class subsystem : public base::func_unit
	{
	private:
		std::set<int> block_ids;
		
	public:
		void add_block(block& block_)
		{
			block_ids.insert(block_.get_id());
			block_.set_subsystemID(get_id());

		}

		bool remove_block(block& block_)
		{
			auto block_it_ = block_ids.find(block_.get_id());

			if (block_it_ == block_ids.end())
				return false;
			
			block_ids.erase(block_it_);
			block_.set_subsystemID(-1);
			return true;

		}
	};
}