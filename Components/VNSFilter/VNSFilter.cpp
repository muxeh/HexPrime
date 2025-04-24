// ======================================================================
// \title  VNSFilter.cpp
// \author maxbinaei
// \brief  cpp file for VNSFilter component implementation class
// ======================================================================

#include "Components/VNSFilter/VNSFilter.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  VNSFilter ::
    VNSFilter(const char* const compName) :
      VNSFilterComponentBase(compName)
  {

  }

  VNSFilter ::
    ~VNSFilter()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void VNSFilter ::
    run_handler(
        FwIndexType portNum,
        U32 context
    )
  {
    // Poll for latest attitude mesaurement
    AttitudeMeasurement quatMeas = this->getAttitudeMeasurement_out(0);
    // Poll for latest position velocity measurement
    PositionMeasurement posVelMeas = this->getPositionMeasurement_out(0);
    // Poll for latest IMU mesaurement
    IMUMeasurement imuMeas = this->getIMUMeasurement_out(0);
    // Poll for latest delta-time computation
    F64 dt = this->getDt_out(0);

    // If filter is uninitalized, and both sets of measurements are available
    if (!m_init &&
	quatMeas.getmeasAvail() &&
	posVelMeas.getmeasAvail()) {
	// Initialize filter
	m_XHat.setattitude(quatMeas.getattitude());
	m_XHat.setposition(posVelMeas.getposition());
	m_XHat.setvelocity(posVelMeas.getvelocity());
	m_P = this->paramGet_INIT_STATE_COV(m_isValid);
	// Set init flag to true
	m_init = true;
    }

    // Execute filter if initialized
    if (m_init) {
	/* Propagate state and covariance */
	computeQ(dt);
	// Proagate attitude with gyro
	propagateAttitude(imuMeas.getGyro(), dt);
	// Proagate position and velocity with accelerometer
	propagatePosVel(imuMeas.getAccel(), dt);
	// Propagate covariance
	propagateCovariance(dt);

	/* Update state and covariance */
	// Check if any measurements available
	if (quatMeas.getmeasAvail() || posVelMeas.getmeasAvail()) {
	    // Compute H
	    computeH();
	    // Check if attitude measurement available
	    if (quatMeas.getmeasAvail()) {
	        // Update attitude estimate
	        updateAttitude(m_XHat, quatMeas);
	        // Reset global attitude estimate with delta-estimate
	        resetAttitude();
	    }
	    // Check if position velocity measurement available
	    if (posVelMeas.getmeasAvail()) {
	        // Update position and velocity estimate
	        updatePosVel(m_XHat, posVelMeas);
	    }
	    // Update covariance
	    updateCovariance(m_P);
	}
    }

    // Write telemetry
    this->tlmWrite_stateEstimate(m_XHat);
    this->tlmWrite_stateCovariance(m_P);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void VNSFilter ::
    TODO_1_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void VNSFilter ::
    TODO_2_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
