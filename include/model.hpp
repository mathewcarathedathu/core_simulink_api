#include "subsystem.hpp"
#include "block.hpp"
#include "subsystem.hpp"

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iterator>
#include <algorithm>

namespace components
{
	class model : public block, public subsystem
	{
	private:
		std::unordered_set<block*> inputs;
		std::unordered_set<block*> outputs;
		std::unordered_set<block*> blocks;

		std::unordered_map<int, block*> block_id;
		std::unordered_map<block*, std::list<block*>> children;

		std::unordered_map<subsystem*, std::list<block*>> subsystems;

	public:
		model()
		{}

		~model()
		{
			for (auto itr = blocks.begin(); itr != blocks.end(); ++itr)
				delete* itr;
		}

		bool execute()
		{
			block* a;
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
						auto child_blocks_ = (*itr)->get_child_blocks();

						if (child_blocks_.size() > 0)
						{
							std::set_union(next_level.begin(), next_level.end(),
								child_blocks_.begin(), child_blocks_.end(),
								next_level.end());

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


		}
		void add_block(block& curr_block)
		{
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

		void connect_ports(block& parent_block, int parent_port_num,
			block& child_block, int child_port_num)
		{
			parent_block.set_input_port(parent_port_num, child_port_num, &child_block);
			children[&parent_block].insert(children[&parent_block].end(), &child_block);
		}
		
	};

}
