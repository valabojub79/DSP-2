/*
 * DwWorkerMpi.h
 *
 *  Created on: Nov 18, 2016
 *      Author: kibaekkim
 */

#ifndef SRC_SOLVER_DANTZIGWOLFE_DWWORKERMPI_H_
#define SRC_SOLVER_DANTZIGWOLFE_DWWORKERMPI_H_

#include <Utility/DspMpi.h>
#include <DantzigWolfe/DwWorker.h>

class DwWorkerMpi: public DwWorker {
public:

	/** default constructor */
	DwWorkerMpi(
			DecModel * model,
			DspParams * par,
			DspMessage * message,
			MPI_Comm comm);

	/** default destructor */
	virtual ~DwWorkerMpi();

	/** generate variables */
	DSP_RTN_CODE generateCols(
			int phase,                           /**< [in] phase of the master */
			const double* piA,                   /**< [in] piA */
			std::vector<int>& indices,           /**< [out] subproblem indices */
			std::vector<int>& statuses,          /**< [out] solution status */
			std::vector<double>& cxs,            /**< [out] solution times original objective coefficients */
			std::vector<double>& objs,           /**< [out] subproblem objective values */
			std::vector<CoinPackedVector*>& sols /**< [out] subproblem coupling column solutions */);

	/** set column lower bounds */
	void setColBounds(int j, double lb, double ub);

private:

	enum {
		sig_generateCols = 0,
		sig_setColBounds,
		sig_terminate
	};

	/** In this function, non-root processes receive signals
	 * from the root process and do proper processing. */
	DSP_RTN_CODE coordinator();

private:

	MPI_Comm comm_;
	int comm_rank_;
	int comm_size_;

	int npiA_; /**< size of piA vector */
	double* piA_; /**< local piA vector */

	int nsubprobs_; /**< number of subproblems */
};

#endif /* SRC_SOLVER_DANTZIGWOLFE_DWWORKERMPI_H_ */