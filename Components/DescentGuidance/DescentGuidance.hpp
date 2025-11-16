// ======================================================================
// \title  DescentGuidance.hpp
// \author maxwell.binaei
// \brief  hpp file for DescentGuidance component implementation class
// ======================================================================

#ifndef components_DescentGuidance_HPP
#define components_DescentGuidance_HPP

#include "Components/DescentGuidance/DescentGuidanceComponentAc.hpp"
#include <cmath>

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

    // Topology configure function
    // Set AC mode of each phase
    void configure(types::ACMode dsouzaACMode,
                   types::ACMode terminalACMode,
                   types::ACMode landingACMode);
  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------
    types::vector3 m_guidErrPos;
    types::vector3 m_guidErrVel;
    types::vector3 m_velDirAtDsouzaEntry;
    types::vector3 m_guidAccelCmdCBI;
    types::vector3 m_posGuid;
    types::vector3 m_velGuid;
    types::ACMode m_dsouzaACMode;
    types::ACMode m_terminalACMode;
    types::ACMode m_landingACMode;
    F64 m_horizVelMag;

    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for start
    void start_handler(FwIndexType portNum  //!< The port number
                       ) override;

    //! Handler implementation for tick
    void tick_handler(FwIndexType portNum,  //!< The port number
                      U32 context           //!< The call order
                      ) override;

    //! Handler implementation for stop
    void stop_handler(FwIndexType portNum  //!< The port number
                      ) override;

    //! Handler implementation for returnBodyAlignVec
    components::types::vector3 returnBodyAlignVec_handler(FwIndexType portNum  //!< The port number
                                                          ) override;

    //! Handler implementation for returnBodyConstrainVec
    components::types::vector3 returnBodyConstrainVec_handler(FwIndexType portNum  //!< The port number
                                                              ) override;

    //! Handler implementation for returnInertConstrainVec
    components::types::vector3 returnInertConstrainVec_handler(FwIndexType portNum  //!< The port number
                                                               ) override;

    //! Handler implementation for returnInertialAlignVec
    components::types::vector3 returnInertAlignVec_handler(FwIndexType portNum  //!< The port number
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

    //! Implementation for action getVelDir of state machine components_DescentGuidance_StateMachine
    void components_DescentGuidance_StateMachine_action_getVelDir(
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

    // ----------------------------------------------------------------------
    // Helper Functions
    // ----------------------------------------------------------------------
    void formulateGuidanceError();

    types::vector3 vec3_add(types::vector3 vec1, types::vector3 vec2) {
        return types::vector3({vec1[0] + vec2[0],
                               vec1[1] + vec2[1],
                               vec1[2] + vec2[2]});
    }

    types::vector3 vec3_sub(types::vector3 vec1, types::vector3 vec2) {
        return types::vector3({vec1[0] - vec2[0],
                               vec1[1] - vec2[1],
                               vec1[2] - vec2[2]});
    }

    types::vector3 vec3_scale(const F64 &scalar, const types::vector3 &vec) {
        return types::vector3({scalar * vec[0],
                               scalar * vec[1],
                               scalar * vec[2]});
    }

    F64 vec3_norm(const types::vector3 &vec) {
        return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    }

    types::vector3 vec3_normalized(const types::vector3 &vec) {
        // Check for divide by zero
        if (vec3_norm(vec) < 1e-9) {
            return vec;
        }
        // Return normalized vector
        // Scale by inverse norm
        return vec3_scale(1 / vec3_norm(vec), vec);
    }

    void vec3_normalize(types::vector3 &vec) {
        vec = vec3_normalized(vec);
    }

    types::vector3 quat_leftTransform(const types::quaternion &quat, const types::vector3 &vec) {
        return vec;
    }

    types::quaternion quat_conjugate(const types::quaternion &quat) {
        return types::quaternion(quat.get_scalar(),
                                 vec3_scale(-1, quat.get_vector()));
    }

    types::quaternion quat_multiply(const types::quaternion &quat1, const types::quaternion &quat2) {
        return quat1;
    }

};

}  // namespace components

#endif
