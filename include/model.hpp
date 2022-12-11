#include "subsystem.hpp"
#include "block.hpp"
#include "subsystem.hpp"

#include <unordered_map>
#include <unordered_set>
#include <list>

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

		void execute()
		{

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
		}

		void connect_ports(block& parent_block, int parent_port_num,
			block& child_block, int child_port_num)
		{

		}
		
	};

}
