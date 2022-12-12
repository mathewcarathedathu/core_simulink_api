#include "subsystem.hpp"
#include "block.hpp"
#include "subsystem.hpp"
#include "utils.hpp"

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iterator>
#include <algorithm>
#include <stdint.h>

namespace components
{
	class model : public block, public subsystem
	{
	private:

		uint8_t block_id_ct;
		std::unordered_set<block*> inputs;
		std::unordered_set<block*> outputs;
		std::unordered_set<block*> blocks;

		std::unordered_map<int, block*> block_id;
		std::unordered_map<block*, std::unordered_set<block*>> children;

		std::unordered_map<subsystem*, std::list<block*>> subsystems;

	public:
		model(): block_id(0)
		{}

		~model()
		{
			for (auto itr = blocks.begin(); itr != blocks.end(); ++itr)
				delete* itr;
		}

		bool execute()
		{
			std::unordered_set<block*> curr_level;
			std::unordered_set<block*> next_level;
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
				curr_level = next_level;
				next_level.clear();
			}

			return true;
		}
		void add_block(block& curr_block)
		{
			curr_block.set_id(++block_id_ct);

			switch (curr_block.get_type())
			{
			case ::block_type::E_INPUT:
				inputs.insert(inputs.begin(), &curr_block);
				break;

			case ::block_type::E_OUTPUT:
				outputs.insert(outputs.begin(), &curr_block);
				break;

			}
			blocks.insert(blocks.end(), &curr_block);
			block_id[curr_block.get_id()] = &curr_block;
		}

		void connect_ports(block& parent_block_, int parent_port_num,
			block& child_block_, int child_port_num)
		{
			child_block_.set_input_port(parent_port_num, child_port_num, &parent_block_);
			children[&parent_block_].insert(children[&parent_block_].end(), &child_block_);

			parent_block_.set_output_port(&child_block_);
		}
		
	};

}
