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

		std::set<subsystem*> child;
		std::set<subsystem*> parent;
	public:
		bool add_block(block& block_)
		{
			if (block_.get_subsystemID() > 0)
				return false;

			block_ids.insert(block_.get_id());
			block_.set_subsystemID(get_id());

			return true;

		}

		void add_child(subsystem* ss)
		{
			child.insert(child.end(), ss);
		}

		void add_parent(subsystem* ss)
		{
			parent.insert(parent.end(), ss);
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

		std::set<int> get_blocks()
		{
			std::set<int> block_id_(block_ids);

			return block_id_;
		}

		std::set<subsystem*> get_child()
		{
			std::set<subsystem*> child_(child);
			return child_;
		}
	};
}