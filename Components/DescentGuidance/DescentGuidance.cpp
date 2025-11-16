// ======================================================================
// \title  DescentGuidance.cpp
// \author maxwell.binaei
// \brief  cpp file for DescentGuidance component implementation class
// ======================================================================

#include "Components/DescentGuidance/DescentGuidance.hpp"

namespace components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DescentGuidance ::DescentGuidance(const char* const compName) : DescentGuidanceComponentBase(compName),
                                                                m_guidErrPos(types::vector3(0)),
                                                                m_guidErrVel(types::vector3(0)),
                                                                m_velDirAtDsouzaEntry(types::vector3(0)),
                                                                m_guidAccelCmdDirCBI(types::vector3(0)),
                                                                m_guidAccelCmdMag(types::vector3(0)),
                                                                m_posGuid(types::vector3(0)),
                                                                m_velGuid(types::vector3(0)),
                                                                m_horizVelMag(0) {}

DescentGuidance ::~DescentGuidance() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void DescentGuidance ::start_handler(FwIndexType portNum) {
    // Forward start signal to state machine
    this->stateMachine_sendSignal_start();
}

void DescentGuidance ::tick_handler(FwIndexType portNum, U32 context) {
    // ----------------------------------------------------------------------
    // Execute Common Jobs
    // ----------------------------------------------------------------------
    // Formulate Gidance error
    this->formulateGuidanceError();

    // ----------------------------------------------------------------------
    // Forward tick signal to state machine
    // ----------------------------------------------------------------------
    this->stateMachine_sendSignal_tick();

    // ----------------------------------------------------------------------
    // Dispatch queue
    // ----------------------------------------------------------------------
}

void DescentGuidance ::stop_handler(FwIndexType portNum) {
    // Forward stop signal to state machine
    this->stateMachine_sendSignal_stop();
}

types::vector3 DescentGuidance ::returnBodyAlignVec_handler(FwIndexType portNum) {
    return types::vector3(0);
}

types::vector3 DescentGuidance ::returnBodyConstrainVec_handler(FwIndexType portNum) {
    Fw::ParamValid vld(Fw::ParamValid::INVALID);
    // Return body constrain vector parameter
    return this->paramGet_BODY_CONSTRAIN_VEC(vld);
}

types::vector3 DescentGuidance ::returnInertConstrainVec_handler(FwIndexType portNum) {
    Fw::ParamValid vld(Fw::ParamValid::INVALID);
    // Return configured constrain vector
    switch (this->paramGet_CONSTRAIN_VEC_OPTION(vld)) {
        case ConstrainVecOption::NORTH:
            return this->getNorthVector_out(0);
        default:
            // Default to north
            return this->getNorthVector_out(0);
    };
}

types::vector3 DescentGuidance ::returnInertAlignVec_handler(FwIndexType portNum) {
    return types::vector3(0);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void DescentGuidance ::components_DescentGuidance_StateMachine_action_trackingGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // ----------------------------------------------------------------------
    // Tracking Guidance
    // ----------------------------------------------------------------------
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_setDsouzaControllers(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_getVelDir(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // Get velocity direction
    m_velDirAtDsouzaEntry = vec3_normalized(m_velGuid);
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_igniteMainEngine(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_dsouzaGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    Fw::ParamValid vld(Fw::ParamValid::INVALID);
    // ----------------------------------------------------------------------
    // D'Souza Guidance -- Braking Burn
    // ----------------------------------------------------------------------
    // Check if below horizontal velocity threshold
    if (m_horizVelMag <= this->paramGet_HORIZ_VEL_THRESH(vld)) {
        // Signal transition to state machine
        this->stateMachine_sendSignal_horizVelAchieved();
    }

    // Add target bias to guidance position error
    types::vector3 dsouzaGuidErrPos = vec3_add(m_guidErrPos, this->paramGet_DSOUZA_TARGET_BIAS(vld));
    // Set update inputs
    // Execute DsouzaGuidance
    // Extract ouputs, assign guidance commmand
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_shutdownMainEngine(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_terminalAndLandingGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    Fw::ParamValid vld(Fw::ParamValid::INVALID);
    // ----------------------------------------------------------------------
    // Terminal and Landing Guidance -- Descent Rate Control
    // ----------------------------------------------------------------------
    // Check for transition to Landing Guidance
    if (stateMachine_getState() == DescentGuidance_StateMachineStateMachineBase::State::TERMINAL &&
        this->getAGL_out(0) <= this->paramGet_LANDING_AGL(vld)) {
        // Below or at Landing AGL
        // Transition to Landing Guidance
        this->stateMachine_sendSignal_atLandingAGL();
    }
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_setTerminalControllers(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_buildDescentProfileTable(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_ignoreVNS(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_setLandingControllers(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_ignoreRangeFinder(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_shutdownAllEngines(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

// ----------------------------------------------------------------------
// Helper Functions
// ----------------------------------------------------------------------
void DescentGuidance::formulateGuidanceError() {
    // Get spacecraft position and velocity in CBI
    types::vector3 posCBI = this->getPosCBI_out(0);
    types::vector3 velCBI = this->getVelCBI_out(0);
    // Get landing site position in CBF
    types::vector3 landingSiteCBF = this->getLandingSiteCBF_out(0);
    // Get frame quaternionds
    types::quaternion q_CBIToCBF = this->getQCBIToCBF_out(0);
    types::quaternion q_CBIToGuid = this->getQCBIToGuid_out(0);
    types::quaternion q_CBFToCBI = quat_conjugate(q_CBIToCBF);
    types::quaternion q_CBFToGuid = quat_multiply(q_CBIToGuid, q_CBFToCBI);
    // Rotate states to Guidance frame
    m_posGuid = quat_leftTransform(q_CBIToGuid, posCBI);
    m_velGuid = quat_leftTransform(q_CBIToGuid, velCBI);
    types::vector3 landingSiteGuid = quat_leftTransform(q_CBFToGuid, landingSiteCBF);
    // Compute guidance error
    m_guidErrPos = vec3_sub(landingSiteGuid, m_posGuid);
    m_guidErrPos = vec3_sub(types::vector3(0), m_velGuid);
    // Compute square of horizontal velocity
    m_horizVelMag = sqrt(m_velGuid[0]*m_velGuid[0] + m_velGuid[1]*m_velGuid[1]);
    // Write telemetry
    this->tlmWrite_pos_guid(m_posGuid);
    this->tlmWrite_pos_guid(m_velGuid);
    this->tlmWrite_guid_err_pos(m_guidErrPos);
    this->tlmWrite_guid_err_vel(m_guidErrVel);
    this->tlmWrite_horiz_vel_mag(m_horizVelMag);
}


// ----------------------------------------------------------------------
// Vector Math
// ----------------------------------------------------------------------

}  // namespace components
