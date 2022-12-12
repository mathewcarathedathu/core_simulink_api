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

	f_block::integ_block integ1;

	f_block::output_block op1;

	curr_model.add_block(ip1);
	curr_model.add_block(gain1);

	curr_model.connect_ports(ip1, 0, gain1, 0);

	curr_model.add_block(gain2);
	curr_model.connect_ports(gain1, 0, gain2, 0);

	curr_model.add_block(integ1);
	curr_model.connect_ports(gain2, 0, integ1, 0);

	curr_model.add_block(op1);
	curr_model.connect_ports(integ1, 0, op1, 0);

	components::subsystem ss_1;

	components::subsystem ss_2;

	curr_model.add_subsystem(ss_1);
	curr_model.add_subsystem(ss_2);

	curr_model.add_block_to_ss(ss_1, gain1);

	curr_model.add_block_to_ss(ss_2, gain2);

	int ct = 0;

	while (ct < 10)
	{
		curr_model.execute();
		ct++;
	}

	curr_model.sync_ss(ss_1);
	curr_model.sync_ss(ss_2);
	//Query A.
	curr_model.print_root_blocks();

	//Query B.
	curr_model.print_parent_subsystem(gain1);

	//Query C. 
	curr_model.print_child_blocks(ss_2);

	//Query D. 
	curr_model.print_descendant_blocks(ss_1);

	//Query E
	curr_model.filter_blocks(::block_type::E_GAIN);

	curr_model.filter_blocks(ss_1, ::block_type::E_GAIN);

	//Query F.
	curr_model.print_dest_blocks(ip1);

	//std::cin.get();
}