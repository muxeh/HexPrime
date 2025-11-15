state machine StateMachine {
        
    # Initial state
    initial enter IDLE
    
    # Signals
    signal atInTrackPDI
    signal horizontalVelocityAchieved
    signal velDirChangeThreshExceeded
    signal minVNSAGLReached
    signal atLandingAGL
    signal groundContact
    signal contingencyShutdown

    # Common signals
    signal start
    signal tick
    signal stop

    # Actions
    action trackingGuidance    
    action setDsouzaControllers
    action igniteMainEngine
    action dsouzaGuidance
    action shutdownMainEngine
    action terminalAndLandingGuidance
    action setTerminalControllers
    action buildDescentProfileTable
    action ignoreVNS
    action setLandingControllers
    action ignoreRangeFinder
    action shutdownAllEngines

    state IDLE {

        on start enter TRACKING

    }
    
    state TRACKING {
    
        on tick do {trackingGuidance}

        on atInTrackPDI enter DSOUZA

    }

    state DSOUZA {

        entry do {setDsouzaControllers, igniteMainEngine}

        on tick do {dsouzaGuidance}
        
        on velDirChangeThreshExceeded enter TERMINAL
        
        on horizontalVelocityAchieved enter TERMINAL

    }
    
    state TERMINAL {

        entry do {shutdownMainEngine, setTerminalControllers, buildDescentProfileTable}

        on tick do {terminalAndLandingGuidance}

        on minVNSAGLReached do {ignoreVNS}
        
        on atLandingAGL enter LANDING

    }
    
    state LANDING {

        entry do {setLandingControllers, ignoreVNS, ignoreRangeFinder}

        on tick do {terminalAndLandingGuidance}

        on groundContact enter SHUTDOWN

        on contingencyShutdown enter SHUTDOWN

    }
    
    state SHUTDOWN {

        entry do {shutdownAllEngines}
        
        on tick enter SURFACE
    
    }
    
    state SURFACE {

    }
    
}
