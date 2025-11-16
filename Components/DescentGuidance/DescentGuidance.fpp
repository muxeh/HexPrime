module components {

    module types {
        array vector3 = [3] F64
        struct quaternion {
            scalar: F64
            vector: vector3
        }
    }

    module ports {
        port Invocator()
        port F64Getter() -> F64
        port Vector3Getter() -> types.vector3
        port QuaternionGetter() -> types.quaternion
    }

    enum ConstrainVecOption {
        NORTH = 0,
    }

    @ Component for F Prime FSW framework.
    queued component DescentGuidance {
        include "DescentGuidanceCommands.fppi"
        include "DescentGuidanceParams.fppi"
        include "DescentGuidanceTelemetry.fppi"
        include "StateMachine.fppi"

        state machine instance stateMachine: StateMachine
        
        ###############
        #### Ports ####
        ###############
        @ ADCS ports
        sync input port start: ports.Invocator
        sync input port tick: Svc.Sched
        sync input port stop: ports.Invocator
        sync input port returnBodyConstrainVec: ports.Vector3Getter
        sync input port returnInertConstrainVec: ports.Vector3Getter

        @ Inertial constrain vector options
        output port getNorthVector: ports.Vector3Getter

        @ Get AGL from ephemeris
        output port getAGL: ports.F64Getter

        @ Get position and velocity in Guidance Frame
        output port getPosCBF: ports.Vector3Getter
        output port getVelCBF: ports.Vector3Getter
        output port getLandingSiteCBF: ports.Vector3Getter

        @ Get CBF to Guidance frame quaternion
        output port getQCBFToGuid: ports.QuaternionGetter

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
