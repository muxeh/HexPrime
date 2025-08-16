module Components {

    enum ADCSMode {
        STANDBY = 0,
        DETUMBLE = 1,
        SUN_ACQ = 2,
        TRACK_Sun = 3,
        TRACK_RSO = 4,
        SLEW_ACS = 5,
        SLEW_RW = 6,
        NUM_ADCS_MODES = 7
    }

    struct ADCSModeSet {
        reserve: ADCSMode,
        primary: ADCSMode,
        success: ADCSMode,
        failure: ADCSMode
    }

    enum ADCSModeStatus {
        RUNNING = 0,
        SUCCESS = 1,
        FAILURE = 2
    }

    port ModeStatusGetter() -> ADCSModeStatus

    port Invocator()

    @ Component for F Prime FSW framework.
    active component ADCS {

        include "StateMachine.fppi"

        # Instantiate state machine
        state machine instance stateMachine: StateMachine
        
        # Telemetry
        telemetry available_modes: ADCSModeSet
        telemetry active_mode: ADCSMode
        telemetry $state: I32
        telemetry subprocess_status: ADCSModeStatus

        # Events
        event REQUESTED_ACTIVE_MODE_MATCHES_CURRENT(mode: ADCSMode) \
            severity activity low \
            format "Requested mode ({}) matches current active mode--proceeding without reset."

        event MODE_TRANSITION(currentMode: ADCSMode, newMode: ADCSMode) \
            severity activity high \
            format "Active mode transitioning from ({}) to ({}). Resetting both state machines."

        
        # Ports
        @ Getting status from sub-processes
        output port getSubProcessStatus: [ADCSMode.NUM_ADCS_MODES] Components.ModeStatusGetter
        @ Receiving calls from rate group
        sync input port executeStateMachine: [ADCSMode.NUM_ADCS_MODES] Svc.Sched
        @ Ticking subprocesses
        output port tickSubProcess: [ADCSMode.NUM_ADCS_MODES] Components.Invocator
        @ Resetting subprocesses
        output port resetSubProcess: [ADCSMode.NUM_ADCS_MODES] Components.Invocator

        # Dummy state machine
        sync input port returnDummySubProcessStatus: Components.ModeStatusGetter
        sync input port resetDummySubProcess: Invocator
        
        @ Command to start new mode
        async command startNewMode(primaryMode: ADCSMode,
                                   successMode: ADCSMode,
                                   failureMode: ADCSMode) opcode 0

        async command setDummySubProcessStatus(status: ADCSModeStatus)

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
