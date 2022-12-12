#pragma once

#include <stdint.h>

#include "block.hpp"

namespace f_block
{
	class gain_block : public components::block
	{
	private:
		double p_gainFactor;
		int num_ip;
		int num_op;

		double previous_update_num;
	public:
		gain_block(int subsys_id = -1) :
			block(1, 1, ::block_type::E_GAIN, subsys_id),
			p_gainFactor(2),
			previous_update_num(0)
		{};

		gain_block(double gainFactor, int subsys_id = -1) :
			block(1, 1, ::block_type::E_GAIN, subsys_id),
			p_gainFactor(gainFactor),
			previous_update_num(0)
		{};

		bool execute()
		{
			if (inputs[0]->update_num <= previous_update_num)
				return false;

			outputs[0].data = inputs[0]->data* p_gainFactor;
			outputs[0].update_num++;
			previous_update_num = inputs[0]->update_num;

			return true;
		}
	};
}
