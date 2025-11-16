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
                                                                m_velDirAtDsouzaEntry(types::vector3(0)) {}

DescentGuidance ::~DescentGuidance() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void DescentGuidance ::start_handler(FwIndexType portNum) {
    // Forward start signal to state machine
    this->stateMachine_sendSignal_start();
}

void DescentGuidance ::stop_handler(FwIndexType portNum) {
    // Forward stop signal to state machine
    this->stateMachine_sendSignal_stop();
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
    m_velDirAtDsouzaEntry = vec3_normalized(this->getVelCBF_out(0));
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
    // Get spacecraft position and velocity in CBF
    types::vector3 posCBF = this->getPosCBF_out(0);
    types::vector3 velCBF = this->getVelCBF_out(0);
    // Get landing site position in CBF
    types::vector3 landingSiteCBF = this->getLandingSiteCBF_out(0);
    // Get Guidance frame
    types::quaternion q_cbfToGuid = this->getQCBFToGuid_out(0);
    // Rotate CBF state to Guidance frame
    types::vector3 posGuid = quat_leftTransform(q_cbfToGuid, posCBF);
    types::vector3 velGuid = quat_leftTransform(q_cbfToGuid, velCBF);
    types::vector3 landingSiteGuid = quat_leftTransform(q_cbfToGuid, landingSiteCBF);
    // Compute guidance error
    m_guidErrPos = vec3_sub(landingSiteGuid, posGuid);
    m_guidErrPos = vec3_sub(types::vector3(0), velGuid);
    // Write telemetry
    this->tlmWrite_guid_err_pos(m_guidErrPos);
    this->tlmWrite_guid_err_vel(m_guidErrVel);
}


// ----------------------------------------------------------------------
// Vector Math
// ----------------------------------------------------------------------

}  // namespace components
