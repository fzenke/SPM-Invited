/* 
* Copyright 2014-2018 Friedemann Zenke
*
* This file is part of Auryn, a simulation package for plastic
* spiking neural networks.
* 
* Auryn is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Auryn is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Auryn.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "auryn.h"

#define N 4

/*!\file 
 *
 * \brief Example simulation which simulates one Poisson input onto a single postsynaptic neuron and records the membrane potential 
 * */

using namespace auryn;

namespace po = boost::program_options;

int main(int ac, char* av[]) 
{

	int errcode = 0;
	string simname = "out";
	string logfile = simname;
	string tmpstr;
	AurynWeight w = 2.0e-2;

	// BEGIN Global definitions
	auryn_init( ac, av );
	sys->set_simulation_name(simname);
	sys->set_master_seed(52345);
	// END Global definitions

	// define input group
	PoissonGroup * poisson = new PoissonGroup(N,2.0);

	// define receiving group
	IafPscExpGroup * neuron = new IafPscExpGroup(1);
	neuron->set_refractory_period(0);

	// define connection
	SparseConnection * con = new SparseConnection(poisson,neuron,w,1.0,GLUT);
	con->random_data(w*1.0,w*0.3);

	// define monitors
	SpikeMonitor * smon_in = new SpikeMonitor( poisson, sys->fn("input","ras") );
	SpikeMonitor * smon_out = new SpikeMonitor( neuron, sys->fn("output","ras") );
	// StateMonitor * vmon = new StateMonitor( neuron, 0, "mem", sys->fn("mem"), 1e-3 );
	VoltageMonitor * vmon = new VoltageMonitor( neuron, 0, sys->fn("mem") );

	
	// run simulation
	logger->msg("Running ...",PROGRESS);
	double simtime = 0.4;
	sys->run(simtime);
	poisson->set_rate(25.0);
	sys->run(simtime);

	if (errcode)
		auryn_abort(errcode);

	logger->msg("Freeing ...",PROGRESS,true);
	auryn_free();
	return errcode;
}
