/* Definition of general purpose block for a simulink model

*/
#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <set>

#include "func_unit.hpp"
#include "data_unit.h"

static const unsigned MAX_BLOCK_INPUT = 100;
static const unsigned MAX_BLOCK_OUTPUT = 100;

enum class block_type : unsigned char
{
	E_NONE,
	E_INPUT,
	E_OUTPUT,
	E_GAIN,
	E_INTEG,
	E_DIFF	
};
namespace n_block
{
	class block : public base::func_unit
	{

	private:
		
		int subsystem_id;
		block_type type;

		std::set<block*> child_block;
		std::set<block*> parent_block;

		void add_input_block(block* block_)
		{
			parent_block.insert(block_);
		}

		void add_output_block(block* block_)
		{
			child_block.insert(block_);
		}

	public:

		block(): subsystem_id(- 1), type(block_type::E_NONE)
		{
			child_block.clear();
			parent_block.clear();
		}

		block(uint8_t n_inputs, uint8_t n_outputs, block_type b_type_) : subsystem_id(-1), func_unit(n_inputs, n_outputs), type(b_type_)
		{
			child_block.clear();
			parent_block.clear();
		}

		block(uint8_t n_inputs, uint8_t n_outputs, block_type b_type_, int ss_id) : subsystem_id(ss_id), func_unit(n_inputs, n_outputs), type(b_type_)
		{
			child_block.clear();
			parent_block.clear();
		}

		virtual void execute() = 0;

	
		void set_type(block_type b_type)
		{
			type = b_type;
		}
		
	
		block_type get_type()
		{
			return type;
		}

		int get_parent()
		{
			return subsystem_id;
		}

		std::set<block*> get_parent_blocks()
		{
			std::set<block*> parent_block_(parent_block);
			return parent_block_;
		}

		std::set<block*> get_child_blocks()
		{
			std::set<block*> child_block_(child_block);
			return child_block_;
		}

		void set_input_port(int port_num, func_unit* parent_op_port, block* parent_block_)
		{
			inputs[port_num] = *parent_op_port;
			add_input_block(parent_block_);
		}

		void set_output_port(block* child_block_)
		{
			add_output_block(child_block_);
		}
	};
}