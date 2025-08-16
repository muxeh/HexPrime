module Components {

    enum ADCSMode {
        STANDBY = 0,
        DETUMBLE = 1,
        SUN_ACQ = 2,
        TRACK_Sun = 3,
        TRACK_RSO = 4,
        SLEW_ACS = 5,
        SLEW_RW = 6
    }

    enum ADCSModeStatus {
        RUNNING = 0,
        SUCCESS = 1,
        FAILURE = 2
    }

    port ModeStatusGetter() -> ADCSModeStatus

    @ Component for F Prime FSW framework.
    active component ADCS {

        include "StateMachine.fppi"

        # Instantiate state machine
        state machine instance stateMachine: StateMachine
        
        # Telemetry
        telemetry reserve_mode: Components.ADCSMode
        telemetry primary_mode: Components.ADCSMode
        telemetry success_mode: Components.ADCSMode
        telemetry failure_mode: Components.ADCSMode
        telemetry mode_in_use: Components.ADCSMode
        
        # Ports
        @ Getting status from sub-processes
        output port getModeStatus: Components.ModeStatusGetter
        @ Receiving calls from rate group
        sync input port run: Svc.Sched
        
        @ TODO
        async command TODO opcode 0

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
