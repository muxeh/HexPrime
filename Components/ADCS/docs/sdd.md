# Components::ADCS
## Idea
* map with string name to enum
    * for each mode denomination
        * TRACK
        * DETUMBLE
        * HOLD
        * STANDBY
        * SUN_ACQ
* TRACK map example
    * "SUN_POINT" --> TRACK_SUN_POINT
 
def setMode (modeType, mode):
    switch modeType:
        case TRACK:
            setTrackMode(mode)
            break
        ...
 
def setTrackMode (trackMode):
    if trackMode not in trackPortMap.keys()
        warn mode not in map
        return
    portConnection = trackPortMap[trackMode]
    modeType = TRACK

def addTrackMode (trackMode, portConnection):
    if trackMode in trackMap.keys()
        warn mode already in map
        return
    trackPortMap[trackMode] = portConnection

### Example in topology configure phase
adcs.addTrackMode("SUN", ADCS_TRACK_SUN)

### Example in sequence
adcs.setMode(TRACK, "SUN")

### ADCS port calls in sun track
m_attitudeEstimate = this->requestAttitudeEstimate_out(ADCS_TRACK_SUN)
m_attitudeTarget = this->requestAttitudeTarget_out(ADCS_TRACK_SUN)
m_controlTorque = this->requestControlTorque_out(ADCS_TRACK_SUN)

Component for F Prime FSW framework.

## Usage Examples
Add usage examples here

### Diagrams
Add diagrams here

### Typical Usage
And the typical usage of the component here

## Class Diagram
Add a class diagram here

## Port Descriptions
| Name | Description |
|---|---|
|---|---|

## Component States
Add component states in the chart below
| Name | Description |
|---|---|
|---|---|

## Sequence Diagrams
Add sequence diagrams here

## Parameters
| Name | Description |
|---|---|
|---|---|

## Commands
| Name | Description |
|---|---|
|---|---|

## Events
| Name | Description |
|---|---|
|---|---|

## Telemetry
| Name | Description |
|---|---|
|---|---|

## Unit Tests
Add unit test descriptions in the chart below
| Name | Description | Output | Coverage |
|---|---|---|---|
|---|---|---|---|

## Requirements
Add requirements in the chart below
| Name | Description | Validation |
|---|---|---|
|---|---|---|

## Change Log
| Date | Description |
|---|---|
|---| Initial Draft |
