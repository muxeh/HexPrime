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

void ADCS ::run_handler(FwIndexType portNum, U32 context) {
    // Tick state machine
    this->stateMachine_sendSignal_tick();
    // Write telemetry
    this->tlmWrite_reserve_mode(m_reserveMode);
    this->tlmWrite_primary_mode(m_primaryMode);
    this->tlmWrite_success_mode(m_successMode);
    this->tlmWrite_failure_mode(m_failureMode);
    this->tlmWrite_mode_in_use(m_modeInUse);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ADCS ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------
void ADCS::setReserveMode(Components::ADCSMode reserveMode) {
    // Set reserve mode
    m_reserveMode = reserveMode;
}

void ADCS::startNewMode(Components::ADCSMode primaryMode,
                        Components::ADCSMode successMode,
                        Components::ADCSMode failureMode) {
    // Set modes
    m_primaryMode = primaryMode;
    m_successMode = successMode;
    m_failureMode = failureMode;
    // Enter new primary mode in state machine
    this->stateMachine_sendSignal_startNewMode();
}

}  // namespace Components
