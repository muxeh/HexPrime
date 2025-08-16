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
    // Exit if sub-process status not connected
    if (!this->isConnected_getSubProcessStatus_OutputPort(m_activeMode)) {
        return;
    }
    switch (m_subProcessStatus) {
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
    // Set reserve as active mode
    setActiveMode(m_availableModes.get_reserve());
}

void ADCS ::Components_ADCS_StateMachine_action_usePrimaryMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set primary as active mode
    setActiveMode(m_availableModes.get_primary());
}

void ADCS ::Components_ADCS_StateMachine_action_useSuccessMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set success as active mode
    setActiveMode(m_availableModes.get_success());
}

void ADCS ::Components_ADCS_StateMachine_action_useFailureMode(SmId smId,
                                                                Components_ADCS_StateMachine::Signal signal) {
    // Set failure as active mode
    setActiveMode(m_availableModes.get_failure());
}

}  // namespace Components
