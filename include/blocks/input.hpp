#pragma once

#include <stdint.h>

#include "block.hpp"

namespace f_block
{
	class input_block : public components::block
	{
	private:
		double prev_num;
		int num_ip;
		int num_op;
	
		
	public:

		input_block(int subsys_id = -1) :
			block(0, 1, ::block_type::E_INPUT, subsys_id),
			prev_num(0)
		{ };

		bool execute()
		{
			if (outputs[0].update_num == 0)
				outputs[0].data = 1;
			else
				outputs[0].data++;

			outputs[0].update_num++;
			

			return true;
		}

	};
}
