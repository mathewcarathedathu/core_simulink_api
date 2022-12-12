#include <gain.hpp>
#include <input.hpp>
#include <integ.hpp>
#include <model.hpp>
#include <output.hpp>

#include <iostream>

int main()
{
	components::model curr_model;

	f_block::input_block ip1;
	
	f_block::gain_block gain1(2, -1);
	f_block::gain_block gain2(3, -1);

	f_block::output_block op1;
	f_block::output_block op2;

	curr_model.add_block(ip1);
	curr_model.add_block(gain1);

	curr_model.connect_ports(ip1, 0, gain1, 0);

	curr_model.add_block(gain2);

	curr_model.connect_ports(ip1, 0, gain2, 0);

	curr_model.add_block(op1);
	curr_model.connect_ports(gain1, 0, op1, 0);

	curr_model.add_block(op2);
	curr_model.connect_ports(gain2, 0, op2, 0);

	int ct = 0;

	while (ct < 10)
	{
		curr_model.execute();
		ct++;
	}

	std::cin.get();
}