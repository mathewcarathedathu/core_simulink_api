#pragma once

#include <stdint.h>

#include "block.hpp"

namespace f_block
{
	class input_block : public components::block
	{
	private:
		double prev_num;
		int num_ip = 0;
		int num_op = 1;

		
	public:

		input_block(int subsys_id = -1) :
			block(num_ip, num_op, ::block_type::E_INPUT, subsys_id),
			prev_num(0),
			previous_update_num(0)
		{};

		bool execute()
		{
			outputs[0].data = ++prev_num;
			outputs[0].update_num++;
			

			return true;
		}
	};
}
