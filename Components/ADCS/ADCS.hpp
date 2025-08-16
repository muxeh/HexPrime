// ======================================================================
// \title  ADCS.hpp
// \author maxbinaei
// \brief  hpp file for ADCS component implementation class
// ======================================================================

#ifndef Components_ADCS_HPP
#define Components_ADCS_HPP

#include "Components/ADCS/ADCSComponentAc.hpp"

namespace Components {

using Signal = ADCS_StateMachineStateMachineBase::Signal;
using State = ADCS_StateMachineStateMachineBase::State;
using ModeStatus = ADCSModeStatus;

class ADCS final : public ADCSComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ADCS object
    ADCS(const char* const compName  //!< The component name
    );

    //! Destroy ADCS object
    ~ADCS();

    // ----------------------------------------------------------------------
    // Public helper functions
    // ----------------------------------------------------------------------
    void setReserveMode(Components::ADCSMode reserveMode);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for executeStateMachine
    //!
    //! Receiving calls from rate group
    void executeStateMachine_handler(FwIndexType portNum,  //!< The port number
                                     U32 context           //!< The call order
                                     ) override;

    //! Handler implementation for returnDummySubProcessStatus
    Components::ADCSModeStatus returnDummySubProcessStatus_handler(FwIndexType portNum  //!< The port number
                                                                   ) override;

  private:
    // ----------------------------------------------------------------------
    // Private members
    // ----------------------------------------------------------------------
    // Mode declarations 
    Components::ADCSModeSet m_availableModes;
    Components::ADCSMode m_activeMode;
    // Mode status
    Components::ADCSModeStatus m_subProcessStatus;
    Components::ADCSModeStatus m_dummySubProcessStatus;
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command startNewMode
    //!
    //! Command to start new mode
    void startNewMode_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                 U32 cmdSeq,           //!< The command sequence number
                                 Components::ADCSMode primaryMode,
                                 Components::ADCSMode successMode,
                                 Components::ADCSMode failureMode) override;

    //! Handler implementation for command setDummySubProcessStatus
    void setDummySubProcessStatus_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                             U32 cmdSeq,           //!< The command sequence number
                                             Components::ADCSModeStatus status) override;

    //! Handler implementation for resetDummySubProcess
    void resetDummySubProcess_handler(FwIndexType portNum  //!< The port number
                                      ) override;

  private:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action checkModeStatus of state machine Components_ADCS_StateMachine
    void Components_ADCS_StateMachine_action_checkModeStatus(
        SmId smId,                                   //!< The state machine id
        Components_ADCS_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action useReserveMode of state machine Components_ADCS_StateMachine
    void Components_ADCS_StateMachine_action_useReserveMode(
        SmId smId,                                   //!< The state machine id
        Components_ADCS_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action usePrimaryMode of state machine Components_ADCS_StateMachine
    void Components_ADCS_StateMachine_action_usePrimaryMode(
        SmId smId,                                   //!< The state machine id
        Components_ADCS_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action useSuccessMode of state machine Components_ADCS_StateMachine
    void Components_ADCS_StateMachine_action_useSuccessMode(
        SmId smId,                                   //!< The state machine id
        Components_ADCS_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action useFailureMode of state machine Components_ADCS_StateMachine
    void Components_ADCS_StateMachine_action_useFailureMode(
        SmId smId,                                   //!< The state machine id
        Components_ADCS_StateMachine::Signal signal  //!< The signal
        ) override;

    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------
    void startNewMode(Components::ADCSMode primaryMode,
                      Components::ADCSMode successMode,
                      Components::ADCSMode failureMode);
    void setActiveMode(Components::ADCSMode newActiveMode);
};

}  // namespace Components

#endif
