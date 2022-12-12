#include "subsystem.hpp"
#include "block.hpp"
#include "subsystem.hpp"
#include "utils.hpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iterator>
#include <algorithm>
#include <stdint.h>

namespace components
{
	class model
	{
	private:

		uint8_t block_id_ct;
		uint8_t ss_id_ct;
		std::unordered_set<block*> inputs;
		std::unordered_set<block*> blocks;

		std::unordered_map<int, block*> block_id;
		std::unordered_map<int, subsystem*> ss_id;

		std::unordered_map<block*, std::unordered_set<func_unit*>> children;
		std::unordered_map<subsystem*, std::list<block*>> subsystems;

	public:
		model(): block_id_ct(0), ss_id_ct(0)
		{}

		bool execute()
		{
			std::unordered_set<block*> curr_level;
			std::unordered_set<func_unit*> next_level;
			int curr_ct;
			int next_ct = 0;
			int ct;

			for (auto itr = inputs.begin(); itr != inputs.end(); ++itr)
			{
				curr_level.insert(curr_level.begin(), *itr);
				next_ct++;
			}

			while (true)
			{
				curr_ct = next_ct;
				next_ct = 0;
				ct = 0;
				for (auto itr = curr_level.begin(); itr != curr_level.end(); ++itr)
				{
					(*itr)->execute();
					if ((*itr)->get_type() != ::block_type::E_OUTPUT)
					{
						auto child_blocks_ = children[*itr];

						if (child_blocks_.size() > 0)
						{
							merge_sets(next_level, child_blocks_);

							next_ct++;
						}
					}
				}



				if (next_level.size() == 0)
					break;

				curr_level.clear();

				for (auto itr = next_level.begin(); itr != next_level.end(); ++itr)
					curr_level.insert(curr_level.end(), (block*) * itr);

				next_level.clear();
			}

			return true;
		}
		//Add block to model
		void add_block(block& curr_block)
		{
			curr_block.set_id(++block_id_ct);

			if (curr_block.get_type() == ::block_type::E_INPUT)
			{
				inputs.insert(inputs.begin(), &curr_block);

			}

			blocks.insert(blocks.end(), &curr_block);
			block_id[curr_block.get_id()] = &curr_block;
		}

		//Connect ports between blocks
		void connect_ports(block& parent_block_, int parent_port_num,
			block& child_block_, int child_port_num)
		{
			child_block_.set_input_port(parent_port_num, child_port_num, &parent_block_);
			children[&parent_block_].insert(children[&parent_block_].end(), &child_block_);

			parent_block_.set_output_port(&child_block_);
		}

		void add_subsystem(subsystem& ss_)
		{
			ss_.set_id(++ss_id_ct);
			ss_id[ss_.get_id()] = &ss_;
		}

		//Add block to subsystem
		bool add_block_to_ss(subsystem& ss_, block& block_)
		{
			if(!ss_.add_block(block_))
				return false;

			subsystems[&ss_].insert(subsystems[&ss_].begin(), &block_);

			return true;

		}

		//Establish relationships between subsystems
		void sync_ss(subsystem& ss_)
		{
			auto ss_child_blocks_ = subsystems[ss_id[ss_.get_id()]];

			for (auto itr1 = ss_child_blocks_.begin(); itr1 != ss_child_blocks_.end(); ++itr1)
				//Add subsystem parents of suceeding blocks as children of this susbsystem
			{
				auto child_blocks_ = (*itr1)->get_child_blocks();

				for (auto itr = child_blocks_.begin(); itr != child_blocks_.end(); ++itr)
				{
					int child_ssid = (*itr)->get_subsystemID();
					if (child_ssid != -1)
						ss_.add_child(ss_id[child_ssid]);

				}

				//Add subsystem parents of preceding blocks as parents of this susbsystem
				auto parent_blocks_ = (*itr1)->get_parent_blocks();

				for (auto itr = parent_blocks_.begin(); itr != parent_blocks_.end(); ++itr)
				{
					int parent_ssid = (*itr)->get_subsystemID();
					if (parent_ssid != -1)
						ss_.add_parent(ss_id[parent_ssid]);

				}
			}

		}

		//Query A.
		void print_root_blocks()
		{
			std::cout << "Query A" << std::endl;
			for (auto itr = blocks.begin(); itr != blocks.end(); ++itr)
			{
				if ((*itr)->get_subsystemID() == -1)
				{
					std::cout << (*itr)->get_id() << " " << get_block_type_str(*itr) << std::endl;
					
				}
			}
		}

		//Query B.
		void print_parent_subsystem(block& block_)
		{
			std::cout << "Query B" << std::endl;
			int block_ssid = block_.get_subsystemID();
			if (block_ssid != -1)
				std::cout << block_ssid << std::endl;
			
			else
				std::cout << "No subsystem" << std::endl;
		}

		//Query C.
		void print_child_blocks(subsystem& ss_, bool f_skip_into = false)
		{
			if(!f_skip_into)
				std::cout << "Query C" << std::endl;
			auto blocks_ = ss_.get_blocks();

			for (auto itr = blocks_.begin(); itr != blocks_.end(); ++itr)
			{
				std::cout << *itr << " " << get_block_type_str(block_id[*itr]) << std::endl;
			}
		}

		//Query D.
		void print_descendant_blocks(subsystem& ss_)
		{
			std::cout << "Query D" << std::endl;
			auto child_ss = ss_.get_child();

			for (auto itr = child_ss.begin(); itr != child_ss.end(); ++itr)
			{
				print_child_blocks(**itr, true);
			}
		}

		//Query E part 1.
		void filter_blocks(::block_type type_)
		{
			std::cout << "Query E" << std::endl;
			for (auto itr = blocks.begin(); itr != blocks.end(); ++itr)
			{
				if((*itr)->get_type() == type_)
					std::cout << (*itr)->get_id() << " " << get_block_type_str(block_id[(*itr)->get_id()]) << std::endl;
			}
		}

		//Query E part 2.
		void filter_blocks(subsystem& ss_, ::block_type type_)
		{
			std::cout << "Query E" << std::endl;
			auto block_ = ss_.get_blocks();
			for (auto itr = block_.begin(); itr != block_.end(); ++itr)
			{
				if (block_id[(*itr)]->get_type() == type_)
					std::cout << *itr << " " << get_block_type_str(block_id[*itr]) << std::endl;
			}
		}

		//Query F.
		void print_dest_blocks(block& block_)
		{

			std::cout << "Query F" << std::endl;

			auto next_level = children[&block_];
			int ct = 0;
			while (next_level.size() > 0)
			{
				auto curr_level = next_level;

				next_level.clear();
				for (auto itr = curr_level.begin(); itr != curr_level.end(); ++itr)
				{
					std::cout << (* itr)->get_id() << " " << get_block_type_str((block*) * itr) << std::endl;

					merge_sets(next_level, children[(block*)(* itr)]);
				}
			}
		}
	};

}
