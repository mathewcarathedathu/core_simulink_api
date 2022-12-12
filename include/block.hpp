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
namespace components
{
	class block : public base::func_unit
	{

	private:
		
		int subsystem_id;
		block_type type;

		std::set<block*> child;
		std::set<block*> parent;

		void add_input(block* block_)
		{
			parent.insert(block_);
		}

		void add_output(block* block_)
		{
			child.insert(block_);
		}


		
	public:

		block() : 
			subsystem_id(-1), 
			type(block_type::E_NONE)
		{
			child.clear();
			parent.clear();
		}

		block(uint8_t n_inputs, uint8_t n_outputs, block_type b_type_) : 
			subsystem_id(-1), 
			func_unit(n_inputs, n_outputs), 
			type(b_type_) 
		{
			child.clear();
			parent.clear();

			init_outputs();
		};

		block(uint8_t n_inputs, uint8_t n_outputs, block_type b_type_, int ss_id) : 
			subsystem_id(ss_id), 
			func_unit(n_inputs, n_outputs), 
			type(b_type_) 
		{
			child.clear();
			parent.clear();

			init_outputs();
		};

		virtual bool execute() = 0;

		int get_subsystemID()
		{
			return subsystem_id;
		}

		void set_subsystemID(int ssid_)
		{
			subsystem_id = ssid_;
		}
	
		void set_type(block_type b_type)
		{
			type = b_type;
		}
		
	
		block_type get_type()
		{
			return type;
		}

		std::set<block*> get_parent_blocks()
		{
			std::set<block*> parent_block_(parent);
			return parent_block_;
		}

		std::set<block*> get_child_blocks()
		{
			std::set<block*> child_block_(child);
			return child_block_;
		}

		void set_input_port(int input_port_num, int output_port_num, block* parent_block_)
		{
			inputs[input_port_num] = &parent_block_->outputs[output_port_num];
			add_input(parent_block_);
		}

		void set_output_port(block* child_block_)
		{
			
			//outputs[output_port_num] = child_block_->inputs[input_port_num];
			add_output(child_block_);
		}

		/*bool remove_block()
		{
			if (get_num_inputs() != get_num_outputs())
				return false;

			outputs[0] = inputs[0];
			return true;
		}*/
	};
}