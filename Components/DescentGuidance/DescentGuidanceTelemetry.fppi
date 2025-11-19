@ Position in guidance frame
telemetry pos_guid: types.vector3

@ Velocity in guidance frame
telemetry vel_guid: types.vector3

@ Guidance error in position
telemetry guid_err_pos: types.vector3

@ Guidance error in velocity
telemetry guid_err_vel: types.vector3

@ Horizontal velocity magnitude
telemetry horiz_vel_mag: F64

# Parameters
telemetry BODY_ALIGN_VEC: types.vector3
telemetry BODY_CONSTRAIN_VEC: types.vector3
telemetry CONSTRAIN_VEC_OPTION: types.vector3
telemetry DSOUZA_TARGET_BIAS: types.vector3
telemetry HORIZ_VEL_THRESH: F64
telemetry TERM_DESC_CTRL: DescentController
telemetry LAND_DESC_CTRL: DescentController
telemetry LANDING_AGL: F64
