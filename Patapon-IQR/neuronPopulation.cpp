/****************************************************************************
 ** $Filename: neuronPopulation.cpp
 ** $Header$
 **
 ** $Author: Jesus Sanchez-Palencia
 **
 ** $CreateDate: Tue Mar 11 12:20:53 2011
 ** $Date$
 **
 ** $Keywords:
 ** $Description:
 **
 *****************************************************************************/

#include "neuronPopulation.hpp"

// Interface for dynamic loading is built using a macro.
MAKE_NEURON_DLL_INTERFACE(iqrcommon::ClsNeuronPopulation,
			  "Patapon")

iqrcommon::ClsNeuronPopulation::ClsNeuronPopulation()
    : ClsNeuron(),
      pVmembrane(0),
      pActivity(0)
{
    pExcGain = addDoubleParameter("excGain", "Excitatory gain",
				  1.0, 0.0, 10.0, 4,
				  "Gain of excitatory inputs.\n"
				  "The inputs are summed before\n"
				  "being multiplied by this gain.",
				  "Input");

    pInhGain = addDoubleParameter("inhGain", "Inhibitory gain",
				  1.0, 0.0, 10.0, 4,
				  "Gain of inhibitory inputs.\n"
				  "The inputs are summed before\n"
				  "being multiplied by this gain.",
				  "Input");

    // This neuron type doesn't use modulatory input, so don't include
    // ModGain.

    // Membrane persistence.
/*    pVmPrs = addDoubleParameter("vmPrs", "Membrane persistence",
				0.0, 0.0, 1.0, 4,
				"Proportion of the membrane potential\n"
				"which remains after one time step\n"
				"if no input arrives.",
				"Membrane");

    // Membrane clip parameters
    pClipVm = addBoolParameter("clipVm", "Clip potential",
			       false,
			       "Restrict the range of the membrane potential",
			       "Clip");

    pVmMin = addDoubleParameter("vmMin", "Minimum potential",
				0.0, 0.0, 1.0, 4,
				"Minimum value of the membrane potential.",
				"Clip");

    pVmMax = addDoubleParameter("vmMax", "Maximum potential",
				1.0, 0.0, 1.0, 4,
				"Maximum value of the membrane potential.",
				"Clip");

    pVmMin->setEnabler(pClipVm);
    pVmMax->setEnabler(pClipVm);
    pVmMin->setMaxSetter(pVmMax);
    pVmMax->setMinSetter(pVmMin);
*/
    pProbability = addDoubleParameter("probability", "Probability",
				      1.0, 0.0, 1.0, 4,
				      "Probability of output occuring during a single timestep.",
				      "Membrane");

    pK = addDoubleParameter("k", "K",
				      1.0, 0.0, 10.0, 4,
				      "Constant multiplier K",
				      "Membrane");

    pInitialPopulation = addDoubleParameter("initialPopulation", "Initial Population",
				      1.0, 0.0, 1000.0, 4,
				      "Initial Population Size",
				      "Membrane");

    pThreshold = addDoubleParameter("threshold", "Threshold potential",
				    0.0, 0.0, 1.0, 4,
				    "Membrane potential threshold for output activity.",
				    "Membrane");

    // Add state variables.
    pVmembrane = addStateVariable("vm", "Membrane potential");
    pActivity  = addOutputState("act", "Activity");

    resetPopulation = true;
}

void
iqrcommon::ClsNeuronPopulation::doResetPopulation()
{
    StateArray &vm = pVmembrane->getStateArray();
    double initialPopulation = pInitialPopulation->getValue();

    vm[0] = initialPopulation;
    resetPopulation = false;
}

void
iqrcommon::ClsNeuronPopulation::update()
{
    if (resetPopulation)
        doResetPopulation();

    // Get local references to the state arrays.
    StateArray &excitation = getExcitatoryInput();
    StateArray &inhibition = getInhibitoryInput();
    StateArray &vm         = pVmembrane->getStateArray();
    StateArray &activity   = pActivity->getStateArray();

    // Get parameter values from parameter objects.
    double excGain     = pExcGain->getValue();
    double inhGain     = pInhGain->getValue();
    double probability = pProbability->getValue();
    double threshold   = pThreshold->getValue();

    double k   = pK->getValue();
    double initialPopulation   = pInitialPopulation->getValue();

    excitation[0] *= excGain;
    inhibition[0] *= inhGain;

    // Calculate membrane potential
    vm[0] = vm[0] * exp((excitation[0] - inhibition[0]) * k);

    // Calculate activity = vm for active cells. Probability specifies
    // the number of cells which can successfully output their state.
    activity.fillProbabilityMask(probability);
    activity[0] *= vm[0];
    activity[0][vm[0] <  threshold]  = 0.0;
}
