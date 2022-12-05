
#pragma once

#include <stdint.h>
#include <memory>

namespace base
{
	class func_unit
	{
	private:
		int id;
		uint8_t num_inputs;
		uint8_t num_outputs;

	protected:
		func_unit* inputs;
		func_unit* outputs;

	public:
		func_unit() : id(-1) {};

		func_unit(uint8_t n_inputs_, uint8_t n_outputs_) : id(-1), num_inputs(n_inputs_), num_outputs(n_outputs_) 
		{
			inputs = new func_unit[num_inputs];
			outputs = new func_unit[num_outputs];

		}

		~func_unit()
		{
			delete[] inputs;
			delete[] outputs;
		}


		void set_id(int id_)
		{
			id = id_;
		}

		int get_id()
		{
			return id;
		}

	};

}