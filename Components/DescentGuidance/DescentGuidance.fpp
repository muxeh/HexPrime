module components {

    module types {
        array vector3 = [3] F64
        struct quaternion {
            scalar: F64
            vector: vector3
        }
        enum ACMode {
            AC_RCS_ONLY   = 0,
            AC_RCS_FOR_ME = 1,
            NUM_MODES     = 2,
            NOT_SET       = 3
        }
    }

    module ports {
        port Invocator()
        port F64Getter() -> F64
        port Vector3Getter() -> types.vector3
        port QuaternionGetter() -> types.quaternion
        port ACModeSetter() -> types.ACMode
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
        sync input port returnBodyAlignVec: ports.Vector3Getter
        sync input port returnInertAlignVec: ports.Vector3Getter
        sync input port returnBodyConstrainVec: ports.Vector3Getter
        sync input port returnInertConstrainVec: ports.Vector3Getter
        output port setACMode: ports.ACModeSetter

        @ Inertial constrain vector options
        output port getNorthVector: ports.Vector3Getter

        @ Get AGL from ephemeris
        output port getAGL: ports.F64Getter

        @ Get position and velocity in Guidance Frame
        output port getPosCBI: ports.Vector3Getter
        output port getVelCBI: ports.Vector3Getter
        output port getLandingSiteCBF: ports.Vector3Getter

        @ Get Guidance frame quaternions
        output port getQCBIToGuid: ports.QuaternionGetter
        output port getQCBIToCBF: ports.QuaternionGetter
        
        @ Set attitude control mode

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
