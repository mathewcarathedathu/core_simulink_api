
#pragma once

#include <stdint.h>
#include <memory>
#include <set>
#include <iostream>

#include "data_unit.h"
namespace base
{
	class func_unit
	{
	private:
		int id;
		uint8_t num_inputs;
		uint8_t num_outputs;

		
	protected:
		data_unit** inputs;
		data_unit* outputs;

		
	public:
		func_unit() : id(-1) 
		{ }

		func_unit(uint8_t n_inputs_, uint8_t n_outputs_) : id(-1), num_inputs(n_inputs_), num_outputs(n_outputs_) 
		{
			if (num_inputs > 0)
				inputs = new data_unit*[num_inputs];
			
			if (num_outputs > 0)
				outputs = new data_unit[num_outputs];


		}

		~func_unit()
		{
			if(num_inputs > 0)
				delete[] inputs;

			if (num_outputs > 0)
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

		int get_num_inputs()
		{
			return num_inputs;
		}

		int get_num_outputs()
		{
			return num_outputs;
		}

		void init_outputs()
		{
			for (int i = 0; i < num_outputs; i++)
			{
				outputs[i].update_num = 0;
				outputs[i].data = 0;
			}

		}
	};

}