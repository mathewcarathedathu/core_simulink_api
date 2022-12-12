#pragma once
#pragma once

#include <stdint.h>
#include <iostream>

#include "block.hpp"

namespace f_block
{
	class output_block : public components::block
	{
	private:
		double prev_num;
		int num_ip = 1;
		int num_op = 0;


	public:

		output_block(int subsys_id = -1) :
			num_ip(1), num_op(0),
			block(1, 0, ::block_type::E_OUTPUT, subsys_id),
			prev_num(0)
		{};

		bool execute()
		{
			auto a = inputs[0]->data;
			auto b = inputs[0]->update_num;
			
			std::cout << inputs[0]->data << ", " << inputs[0]->update_num << std::endl;

			return true;
		}
	};
}
