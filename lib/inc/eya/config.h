#ifndef EYA_CONFIG_H
#define EYA_CONFIG_H

/**
 * @def EYA_CONFIG_OFF
 * @brief Flag indicating disabled/off state
 *
 * This macro defines the value used to represent a disabled or off configuration state.
 * Default value is 0 if not previously defined.
 */
#ifndef EYA_CONFIG_OFF
#    define EYA_CONFIG_OFF 0
#endif // EYA_CONFIG_OFF

/**
 * @def EYA_CONFIG_ON
 * @brief Flag indicating enabled/on state
 *
 * This macro defines the value used to represent an enabled or on configuration state.
 * Default value is 1 if not previously defined.
 */
#ifndef EYA_CONFIG_ON
#    define EYA_CONFIG_ON 1
#endif // EYA_CONFIG_ON

#endif // EYA_CONFIG_H
