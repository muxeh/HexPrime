module components {

    port Invocator()

    @ Component for F Prime FSW framework.
    queued component DescentGuidance {
        include "DescentGuidanceCommands.fppi"
        include "StateMachine.fppi"

        state machine instance stateMachine: StateMachine
        
        ###############
        #### Ports ####
        ###############
        sync input port start: Invocator
        sync input port tick: Svc.Sched
        sync input port stop: Invocator

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

        @ Port to set the value of a parameter
        param set port prmSetOut

    }
}
