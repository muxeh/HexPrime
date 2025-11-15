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

DescentGuidance ::DescentGuidance(const char* const compName) : DescentGuidanceComponentBase(compName) {}

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
    // Execute common jobs
    // Forward tick signal to state machine
    this->stateMachine_sendSignal_tick();
    // Dispatch queue
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void DescentGuidance ::components_DescentGuidance_StateMachine_action_trackingGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_setDsouzaControllers(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_igniteMainEngine(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_dsouzaGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_shutdownMainEngine(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
}

void DescentGuidance ::components_DescentGuidance_StateMachine_action_terminalAndLandingGuidance(
    SmId smId,
    components_DescentGuidance_StateMachine::Signal signal) {
    // TODO
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

}  // namespace components
