/* Definition of general purpose block for a simulink model

*/
#pragma once

#include <stdint.h>
#include <memory>
#include <string>
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

class block
{
private:
	uint8_t num_inputs;
	uint8_t num_outputs;
	
	std::shared_ptr<data_unit> inputs;
	std::shared_ptr<data_unit> outputs;

	std::string id;
	block_type type;

	block* child;
	block* parent;
public:

	virtual void execute() = 0;

	block_type get_type()
	{
		return type;
	}


};