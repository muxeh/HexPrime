// ======================================================================
// \title  StateMachine.cpp
// \author maxbinaei
// \brief  cpp file for ADCS component state machine
// ======================================================================

#include "Components/ADCS/ADCS.hpp"

namespace Components {

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------
void ADCS ::Components_ADCS_StateMachine_action_checkModeStatus(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Get mode status
    ModeStatus modeStatus = this->getModeStatus_out(m_modeInUse);
    switch (modeStatus) {
        case ModeStatus::SUCCESS:
            this->stateMachine_sendSignal_success();
            break;
        case ModeStatus::FAILURE:
            this->stateMachine_sendSignal_failure();
            break;
        case ModeStatus::RUNNING:
            // Do nothing (same as default)
            break;
        default:
            // Do nothing
            break;
    }
}

void ADCS ::Components_ADCS_StateMachine_action_useReserveMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set port connection 
    m_modeInUse = m_reserveMode;
}

void ADCS ::Components_ADCS_StateMachine_action_usePrimaryMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set port connection 
    m_modeInUse = m_primaryMode;
}

void ADCS ::Components_ADCS_StateMachine_action_useSuccessMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set port connection 
    m_modeInUse = m_successMode;
}

void ADCS ::Components_ADCS_StateMachine_action_useFailureMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set port connection 
    m_modeInUse = m_failureMode;
}

}  // namespace Components
