state machine StateMachine {

    # Initial state
    initial enter RESERVE
    
    # Signals
    signal success
    signal failure
    signal tick
    signal startNewMode

    # Actions
    action checkModeStatus
    action useReserveMode
    action usePrimaryMode
    action useSuccessMode
    action useFailureMode
    
    # State entered when initialized or fallen-back to
    state RESERVE {
        # Set ports on entry
        entry do {useReserveMode}

        # Stay in reserve mode until commanded otherwise
        on startNewMode enter PRIMARY
    }
    
    # State entered when new mode is started
    state PRIMARY {
        # Set ports on entry
        entry do {usePrimaryMode}
        
        # Cyclical status check
        on tick do {checkModeStatus}
        on success enter SUCCESS
        on failure enter FAILURE

        # Allow command to start new mode
        on startNewMode enter PRIMARY
    }
   
    # State entered when success is signaled in primary mode
    state SUCCESS {
        # Set ports on entry
        entry do {useSuccessMode}

        # Cyclical status check
        on tick do {checkModeStatus}
        on failure enter RESERVE

        # Allow command to start new mode
        on startNewMode enter PRIMARY
    }
    
    # State entered when failure is signaled in primary mode
    state FAILURE {
        # Set ports on entry
        entry do {useFailureMode}

        # Cyclical status check
        on tick do {checkModeStatus}
        on failure enter RESERVE

        # Allow command to start new mode
        on startNewMode enter PRIMARY
    }
    
}
