/* Definition of general purpose block for a simulink model

*/
#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <set>
#include "data_unit.h"

static const unsigned MAX_BLOCK_INPUT = 100;
static const unsigned MAX_BLOCK_OUTPUT = 100;

enum class block_type : unsigned char
{
	E_INPUT,
	E_OUTPUT,
	E_GAIN,
	E_INTEG,
	E_DIFF	
};
namespace n_block
{
	class block
	{
	private:
		uint8_t num_inputs;
		uint8_t num_outputs;

		std::shared_ptr<data_unit> inputs;
		std::shared_ptr<data_unit> outputs;

		std::string id;
		std::string subsystem_id;
		block_type type;

		std::set<block*> child;
		std::set<block*> parent;
	public:

		block()
		{
			subsystem_id.clear();
		}

		virtual void assign_id() = 0;
		virtual void assign_type(block_type b_type) = 0;
		virtual void execute() = 0;

		block_type get_type()
		{
			return type;
		}

		std::string get_id()
		{
			return id;
		}

		std::set<block*> get_parents()
		{
			std::set<block*> parent_(parent);
			return parent_;
		}

		std::set<block*> get_children()
		{
			std::set<block*> child_(child);
			return child_;
		}
	};
}