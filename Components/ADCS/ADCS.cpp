// ======================================================================
// \title  ADCS.cpp
// \author maxbinaei
// \brief  cpp file for ADCS component implementation class
// ======================================================================

#include "Components/ADCS/ADCS.hpp"

namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ADCS ::ADCS(const char* const compName) : ADCSComponentBase(compName) {}

ADCS ::~ADCS() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void ADCS ::executeStateMachine_handler(FwIndexType portNum, U32 context) {
    // Tick sub process state machine if connected
    if (this->isConnected_tickSubProcess_OutputPort(m_activeMode)) {
        this->tickSubProcess_out(m_activeMode);
    }
    // Get and telemeter sub-process status if connected
    if (this->isConnected_getSubProcessStatus_OutputPort(m_activeMode)) {
        m_subProcessStatus = this->getSubProcessStatus_out(m_activeMode);
        this->tlmWrite_subprocess_status(m_subProcessStatus);
    }
    // Tick internal state machine
    this->stateMachine_sendSignal_tick();
    // Write telemetry
    this->tlmWrite_available_modes(m_availableModes);
    this->tlmWrite_active_mode(m_activeMode);
    this->tlmWrite_state(static_cast<I32>(this->stateMachine_getState()));
}

Components::ADCSModeStatus ADCS ::returnDummySubProcessStatus_handler(FwIndexType portNum) {
    return m_dummySubProcessStatus;
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ADCS ::startNewMode_cmdHandler(FwOpcodeType opCode, U32 cmdSeq,
                                    Components::ADCSMode primaryMode,
                                    Components::ADCSMode successMode,
                                    Components::ADCSMode failureMode) {
    // Start new mode
    startNewMode(primaryMode, successMode, failureMode);
    // Return command response
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ADCS ::setDummySubProcessStatus_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Components::ADCSModeStatus status) {
    m_dummySubProcessStatus = status;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ADCS ::resetDummySubProcess_handler(FwIndexType portNum) {
    m_dummySubProcessStatus = ADCSModeStatus::RUNNING;
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------
void ADCS::setReserveMode(Components::ADCSMode reserveMode) {
    // Set reserve mode
    m_availableModes.set_reserve(reserveMode);
}

void ADCS::startNewMode(Components::ADCSMode primaryMode,
                        Components::ADCSMode successMode,
                        Components::ADCSMode failureMode) {
    // Set modes
    m_availableModes.set_primary(primaryMode);
    m_availableModes.set_success(successMode);
    m_availableModes.set_failure(failureMode);
    // Enter new primary mode in state machine
    this->stateMachine_sendSignal_startNewMode();
}

void ADCS::setActiveMode(Components::ADCSMode newActiveMode) {
    // Exit if mode not changing
    if (m_activeMode == newActiveMode) {
        // Report mode not changing
        this->log_ACTIVITY_LO_REQUESTED_ACTIVE_MODE_MATCHES_CURRENT(m_activeMode);
        return;
    }
    // Entering new mode
    // Report mode change
    this->log_ACTIVITY_HI_MODE_TRANSITION(m_activeMode, newActiveMode);
    // Reset current and new sub process state machines if connected
    if (this->isConnected_resetSubProcess_OutputPort(m_activeMode)) {
        this->resetSubProcess_out(m_activeMode);
    }
    if (this->isConnected_resetSubProcess_OutputPort(newActiveMode)) {
        this->resetSubProcess_out(newActiveMode);
    }
    // Set new mode
    m_activeMode = newActiveMode;
}

}  // namespace Components
