// ======================================================================
// \title  DescentGuidance.hpp
// \author maxbinaei
// \brief  hpp file for DescentGuidance component implementation class
// ======================================================================

#ifndef components_DescentGuidance_HPP
#define components_DescentGuidance_HPP

#include "Components/DescentGuidance/DescentGuidanceComponentAc.hpp"

namespace components {

class DescentGuidance final : public DescentGuidanceComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct DescentGuidance object
    DescentGuidance(const char* const compName  //!< The component name
    );

    //! Destroy DescentGuidance object
    ~DescentGuidance();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for start
    void start_handler(FwIndexType portNum  //!< The port number
                       ) override;

    //! Handler implementation for stop
    void stop_handler(FwIndexType portNum  //!< The port number
                      ) override;

    //! Handler implementation for tick
    void tick_handler(FwIndexType portNum,  //!< The port number
                      U32 context           //!< The call order
                      ) override;

    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action trackingGuidance of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_trackingGuidance(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action setDsouzaControllers of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_setDsouzaControllers(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action igniteMainEngine of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_igniteMainEngine(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action dsouzaGuidance of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_dsouzaGuidance(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action shutdownMainEngine of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_shutdownMainEngine(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action terminalAndLandingGuidance of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_terminalAndLandingGuidance(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action setTerminalControllers of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_setTerminalControllers(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action buildDescentProfileTable of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_buildDescentProfileTable(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action ignoreVNS of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_ignoreVNS(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action setLandingControllers of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_setLandingControllers(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action ignoreRangeFinder of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_ignoreRangeFinder(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;

    //! Implementation for action shutdownAllEngines of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_shutdownAllEngines(
        SmId smId,                                              //!< The state machine id
        components_DescentGuidance_StateMachine::Signal signal  //!< The signal
        ) override;
};

}  // namespace components

#endif
