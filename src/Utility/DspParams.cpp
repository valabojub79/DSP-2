/*
 * DspParams.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: kibaekkim
 */

//#define DSP_DEBUG
#include "Utility/DspMessage.h"
#include "Utility/DspParams.h"

#define MAX_INT_NUM numeric_limits<int>::max()
#define MAX_DBL_NUM numeric_limits<double>::max()

DspParams::DspParams()
{
	initBoolParams();
	initIntParams();
	initDblParams();
	initStrParams();
	initBoolPtrParams();
	initIntPtrParams();
}

DspParams::~DspParams()
{
	BoolPtrParams_.deleteParam("RELAX_INTEGRALITY");
	IntPtrParams_.deleteParam("BD/ARR_AUG_SCENS");
	IntPtrParams_.deleteParam("ARR_PROC_IDX");
}

/** read parameter file */
void DspParams::readParamFile(const char * param_file)
{
	string line;
	ifstream myfile(param_file);
	if (myfile.is_open())
	{
		int pos = 0;
		int col = 0;
		string param_element[3];
		size_t startpos, found;
		while(getline(myfile, line))
		{
			//printf("Read line: %s\n", line.c_str());
			/** comment out? */
			startpos = line.find_first_of("#");
			if(string::npos != startpos) line = line.substr(0, startpos);

			/** empty line? */
			startpos = line.find_first_not_of(" \t");
			if(string::npos == startpos) continue;

			bool is_valid = true;
			for (int i = 0; i < 3; ++i)
			{
				/** ltrim */
				startpos = line.find_first_not_of(" \t");
				if(string::npos != startpos) line = line.substr(startpos);

				/** read element */
				found = line.find_first_of(" \t");
				if(string::npos == found && i < 2)
				{
					printf("Invalid parameter format.\n");
					is_valid = false;
					break;
				}
				param_element[i] = line.substr(0, found);
				if (string::npos != found)
					line = line.substr(found);
			}
			if (!is_valid) break;

			if (param_element[0].compare("bool") == 0)
			{
				if (param_element[2].compare("true") == 0)
					BoolParams_.setParam(param_element[1], true);
				else if (param_element[2].compare("false") == 0)
					BoolParams_.setParam(param_element[1], false);
				else
				{
					printf("Invalid parameter type.\n");
					is_valid = false;
					break;
				}
			}
			else if (param_element[0].compare("double") == 0)
			{
				DblParams_.setParam(param_element[1], atof(param_element[2].c_str()));
			}
			else if (param_element[0].compare("int") == 0)
			{
				IntParams_.setParam(param_element[1], atoi(param_element[2].c_str()));
			}
			else if (param_element[0].compare("string") == 0)
			{
				StrParams_.setParam(param_element[1], param_element[2]);
			}
			else
			{
				printf("Invalid parameter type.\n");
				is_valid = false;
				break;
			}
		}
		myfile.close();
	}
	else
		printf("Unable to open parameter file <%s>.\n", param_file);
}

void DspParams::initBoolParams()
{
	/** enable trust region */
	BoolParams_.createParam("DD/TR", true);

	/** enable decreasing trust region */
	BoolParams_.createParam("DD/TR/DECREASE", true);

	/** enable decreasing trust region */
	BoolParams_.createParam("DD/ALLOW_IDLE_WORKERS", true);

	/** cache recourse models */
	BoolParams_.createParam("DD/CACHE_RECOURSE", true);

	/** log dual variable values */
	BoolParams_.createParam("DD/LOG_DUAL_VARS", false);

	/** log dual variable values */
	BoolParams_.createParam("DD/LOG_LB_TIME", false);

	/** enable asynchronous parallelization */
	BoolParams_.createParam("DD/ASYNC", false);
}

void DspParams::initIntParams()
{
	/** print level */
	IntParams_.createParam("LOG_LEVEL", 1);

	/** branch-and-cut node limit */
	IntParams_.createParam("NODE_LIM", MAX_INT_NUM);

	/** number of cuts to the master per iteration */
	IntParams_.createParam("BD/NUM_CUTS_PER_ITER", 1);

	/** number of cores used in OpenMP library */
	IntParams_.createParam("NUM_CORES", 1);

	/** Benders cut priority (refer CONSHDLR_SEPAPRIORITY of SCIP constraint handler */
	IntParams_.createParam("BD/CUT_PRIORITY", -200000);

	/** Benders lower bound methods:
	 * 0 = solve separate LP relaxation problems;
	 * 1 = solve separate MILP relaxation problems */
	IntParams_.createParam("BD/INIT_LB_ALGO", SEPARATE_LP);

    /** iteration limit of the dual decomposition used in Benders for initial lower bounding */
    IntParams_.createParam("BD/DD/ITER_LIM", 10);

    /** iteration limit */
    IntParams_.createParam("DD/ITER_LIM", MAX_INT_NUM);

	/** algorithm for the master */
	IntParams_.createParam("DD/MASTER_ALGO", IPM_Feasible);

	/** number of cuts to the master per iteration */
	IntParams_.createParam("DD/NUM_CUTS_PER_ITER", 1);

	/** add feasibility cuts */
	IntParams_.createParam("DD/FEAS_CUTS", 1);

	/** add optimality cuts */
	IntParams_.createParam("DD/OPT_CUTS", 1);

	/** evaluate upper bound */
	IntParams_.createParam("DD/EVAL_UB", 1);

	/** maximum number of solutions to evaluate */
	IntParams_.createParam("DD/MAX_EVAL_UB", 100);

	/** maximum queue size for asynchronous one */
	IntParams_.createParam("DD/MAX_QSIZE", 5);

	/** minimum number of processes to wait at the master */
	IntParams_.createParam("DD/MIN_PROCS", 1);

	/** minimum number of processes to wait at the master */
	IntParams_.createParam("SOLVER/MIP", CPLEX);

	/** minimum number of processes to wait at the master */
	IntParams_.createParam("SOLVER/QP", CPLEX);

	/** display frequency */
	IntParams_.createParam("SCIP/DISPLAY_FREQ", 100);
}

void DspParams::initDblParams()
{
	/** wall clock limit */
	DblParams_.createParam("DE/WALL_LIM", MAX_DBL_NUM);

	/** wall clock limit */
	DblParams_.createParam("BD/WALL_LIM", MAX_DBL_NUM);

	/** wall clock limit */
	DblParams_.createParam("DD/WALL_LIM", MAX_DBL_NUM);

	/** initial trust region size */
	DblParams_.createParam("DD/TR/SIZE", 0.1);

	/** stopping tolerance */
	DblParams_.createParam("DD/STOP_TOL", 0.00001);

	/** branch-and-bound gap tolerance */
	DblParams_.createParam("MIP/GAP_TOL", 0.00001);

	/** time limit */
	DblParams_.createParam("MIP/TIME_LIM", 300);

	/** LB-UB worker ratio */
	DblParams_.createParam("DD/WORKER_RATIO", 0.8);

	/** minimum wait time for the master to receive worker processes */
	DblParams_.createParam("DD/ASYNC/MIN_WAIT_TIME", 5.0);
}

void DspParams::initStrParams()
{
	/** prefix for output files */
	StrParams_.createParam("OUTPUT/PREFIX", "dsp");
}

void DspParams::initBoolPtrParams()
{
	/** array of indicating relaxation of integer variables;
	 * each element represents a stage. */
	BoolPtrParams_.createParam("RELAX_INTEGRALITY", 2);
	BoolPtrParams_.setParam("RELAX_INTEGRALITY", 0, false);
	BoolPtrParams_.setParam("RELAX_INTEGRALITY", 1, false);
}

void DspParams::initIntPtrParams()
{
	DSPdebugMessage("creating integer array parameters\n");
	/** array of scenarios for the current process */
	IntPtrParams_.createParam("ARR_PROC_IDX");

	/** array of augmented scenarios */
	IntPtrParams_.createParam("BD/ARR_AUG_SCENS");
}
