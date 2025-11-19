state machine StateMachine {
        
    # Initial state
    initial enter IDLE
    
    # Signals
    signal atInTrackPDI
    signal horizVelAchieved
    signal velDirChangeThreshExceeded
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
    action getVelDir
    action igniteMainEngine
    action dsouzaGuidance
    action shutdownMainEngine
    action terminalAndLandingGuidance
    action setTerminalControllers
    action buildDescentProfileTable
    action setLandingControllers
    action shutdownAllEngines

    state IDLE {

        on start enter TRACKING

    }
    
    state TRACKING {
    
        on tick do {trackingGuidance}

        on atInTrackPDI enter DSOUZA

    }

    state DSOUZA {

        entry do {setDsouzaControllers, getVelDir, igniteMainEngine, dsouzaGuidance}

        on tick do {dsouzaGuidance}
        
        on velDirChangeThreshExceeded enter TERMINAL
        
        on horizVelAchieved enter TERMINAL

    }
    
    state TERMINAL {

        entry do {shutdownMainEngine, setTerminalControllers, buildDescentProfileTable, terminalAndLandingGuidance}

        on tick do {terminalAndLandingGuidance}

        on atLandingAGL enter LANDING

    }
    
    state LANDING {

        entry do {setLandingControllers, terminalAndLandingGuidance}

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
