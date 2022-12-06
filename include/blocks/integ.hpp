#pragma once

#include <stdint.h>

#include "block.hpp"

namespace n_block
{
	class integ_block : public block
	{
	private:
		int num_ip = 1;
		int num_op = 1;

		double prev_val;
		double previous_update_num;
	public:
		integ_block(int subsys_id = -1) :
			block(num_ip, num_op, ::block_type::E_INTEG, subsys_id),
			previous_update_num(0),
			prev_val(0)
		{};

		bool execute()
		{
			if (inputs[0].update_num <= previous_update_num)
				return false;

			outputs[0].data = inputs[0].data * prev_val;
			prev_val = inputs[0].data;
			outputs[0].update_num++;
			previous_update_num = inputs[0].update_num;
		}
	};
}
