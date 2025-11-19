@ Body align vector
param BODY_ALIGN_VEC: types.vector3 default [1, 0, 0]

@ Body constraint vector
param BODY_CONSTRAIN_VEC: types.vector3 default [0, 1, 0]

@ Inertial constrain vector option
param CONSTRAIN_VEC_OPTION: ConstrainVecOption default ConstrainVecOption.NORTH

@ Target bias during DSouza phase
param DSOUZA_TARGET_BIAS: types.vector3 default [0, 0, 0]

@ Horizontal velocity threshold to transition to Terminal Guidance
param HORIZ_VEL_THRESH: F64 default 20

@ Terminal descent controller
param TERM_DESC_CTRL: DescentController

@ Landing descent controller
param LAND_DESC_CTRL: DescentController

@ AGL to transition to Landing Guidance
param LANDING_AGL: F64 default 10
