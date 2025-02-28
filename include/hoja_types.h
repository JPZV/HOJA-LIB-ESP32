#ifndef HOJA_TYPES_H
#define HOJA_TYPES_H

/**
 * Error handling
 */
typedef enum
{
    HOJA_OK = 0,
    HOJA_FAIL,
    HOJA_USB_NODET,         // USB Core not detected on attempt.
    HOJA_I2C_NOTINIT,       // I2C not initialized.
    HOJA_I2C_FAIL,          // I2C communication failed.
    HOJA_BATTERY_NOTSET,    // Battery type needs to be set.
} hoja_err_t;

/** 
 * @brief This data should always be provided as uint16_t to provide
 * as much data as possible. This data will likely need to be
 * scaled down to a different range and we should provide more
 * data to avoid as much stairstepping in values as possible. ONLY 12 BIT VALS.
 * 
 * @param           ls_x  Left Stick X Data
 * @param           ls_y  Left Stick Y Data
 * @param           rs_x  Left Stick X Data
 * @param           rs_y  Left Stick X Data
 * @param           lt_a  Left trigger Analog Data
 * @param           rt_a  Right trigger Analog Data
*/
typedef struct 
{
    uint16_t ls_x;
    uint16_t ls_y;
    uint16_t rs_x;
    uint16_t rs_y;
    uint16_t lt_a;
    uint16_t rt_a;
} __attribute__ ((packed)) hoja_analog_data_s;

/** @brief This is a struct for containing all of the 
 * button input data as bits. This saves space
 * and allows for easier handoff to the various
 * controller cores in the future. 
**/
typedef struct 
{
    union
    {
        struct
        {
            // D-Pad
            uint8_t dpad_up         : 1;
            uint8_t dpad_down       : 1;
            uint8_t dpad_left       : 1;
            uint8_t dpad_right      : 1;
            // Buttons
            uint8_t button_up       : 1;
            uint8_t button_down     : 1;
            uint8_t button_left     : 1;
            uint8_t button_right    : 1;
            // Triggers
            uint8_t trigger_l       : 1;
            uint8_t trigger_zl      : 1;
            uint8_t trigger_r       : 1;
            uint8_t trigger_zr      : 1;

            // Special Functions
            uint8_t button_start    : 1;
            uint8_t button_select   : 1;
            
            // Stick clicks
            uint8_t button_stick_left   : 1;
            uint8_t button_stick_right  : 1;
        };
        uint16_t buttons_all;
    };

    union
    {
        struct
        {
            // Menu buttons (Not remappable by API)
            uint8_t button_capture  : 1;
            uint8_t button_home     : 1;
            uint8_t padding         : 6;
        };
        uint8_t buttons_system;
    };

    // Button for sleeping the controller
    uint8_t button_sleep;

    // Button for pairing the controller
    uint8_t button_pair;

} __attribute__ ((packed)) hoja_button_data_s;

/** @brief This is a struct for containing all of the 
 * rumble incoming data.
**/
typedef struct 
{
    uint8_t left_rumble;
    uint8_t right_rumble;
} __attribute__ ((packed)) hoja_rumble_data_s;

/**
 *  @brief Type to determine what event is being sent
 */
typedef enum
{
    HOJA_EVT_BT,
    HOJA_EVT_SYSTEM,
    HOJA_EVT_USB,
    HOJA_EVT_GC,
    HOJA_EVT_NS,
    HOJA_EVT_INPUT,
    HOJA_EVT_WIRED,
    HOJA_EVT_BOOT,
    HOJA_EVT_BATTERY,
    HOJA_EVT_CHARGER,
} hoja_event_type_t;

/**
 *  @brief Bluetooth events
 */
typedef enum
{
    HEVT_BT_STARTED,
    HEVT_BT_CONNECTING,
    HEVT_BT_PAIRING,
    HEVT_BT_CONNECTED,
    HEVT_BT_DISCONNECTED,
} hoja_bt_event_t;

/**
 *  @brief USB Core(s) events
 */
typedef enum
{
    HEVT_USB_CONNECTED,
    HEVT_USB_DISCONNECTED,
} hoja_usb_event_t;

/**
 *  @brief System events
 */
typedef enum
{
    HEVT_API_INIT_OK,
    HEVT_API_SHUTDOWN,
    HEVT_API_REBOOT,
    HEVT_API_PLAYERNUM,
    HEVT_API_RUMBLE,
} hoja_system_event_t;

/**
 *  @brief Wired utility detect events
 */
typedef enum
{
    HEVT_WIRED_NO_DETECT     = 0,
    HEVT_WIRED_SNES_DETECT   = 1,
    HEVT_WIRED_JOYBUS_DETECT = 2,
} hoja_wired_event_t;

typedef enum
{
    HEVT_BOOT_PLUGGED,
    HEVT_BOOT_UNPLUGGED,
    HEVT_BOOT_NOBATTERY,
} hoja_boot_event_t;

typedef enum
{
    HEVT_CHARGER_PLUGGED,
    HEVT_CHARGER_UNPLUGGED,
} hoja_charger_event_t;

/**
 *  @brief Battery utility events
 */
typedef enum
{
    HEVT_BATTERY_CHARGING,
    HEVT_BATTERY_CHARGECOMPLETE,
    HEVT_BATTERY_LVLCHANGE,
    HEVT_BATTERY_NOCHARGE,
} hoja_battery_event_t;

/**
 *  @brief Analog axis types
 */
typedef enum
{
    HOJA_ANALOG_LEFT_X      = 0,
    HOJA_ANALOG_LEFT_Y      = 1,
    HOJA_ANALOG_RIGHT_X     = 2,
    HOJA_ANALOG_RIGHT_Y     = 3,
    HOJA_ANALOG_TRIGGER_L   = 4,
    HOJA_ANALOG_TRIGGER_R   = 5,
} hoja_analog_axis_t;

/**
 *  @brief HOJA Core Types
 */
typedef enum
{
    HOJA_CORE_NULL,
    HOJA_CORE_NS,
    HOJA_CORE_SNES,
    HOJA_CORE_N64,
    HOJA_CORE_GC,
    HOJA_CORE_USB,
    HOJA_CORE_BT_DINPUT,
    HOJA_CORE_BT_XINPUT,
    HOJA_CORE_MAX,
} hoja_core_t;

/**
 *  @brief HOJA System Status
 */
typedef enum
{
    HOJA_STATUS_IDLE        = 0, // HOJA not loaded. Needs initialization.
    HOJA_STATUS_INITIALIZED = 1, // API has been initialized
    HOJA_STATUS_RUNNING     = 2, // Core is running
} hoja_status_t;

/**
 *  @brief RGB Struct Type Definition
 */
typedef struct
{
    union
    {
        struct
        {
            uint8_t blue;
            uint8_t green;
            uint8_t red;
            uint8_t dummy;
        };
        uint32_t rgb;
    };
    
} __attribute__ ((packed)) hoja_rgb_s;

typedef enum
{
    HOJA_CONTROLLER_MODE_NS,
    HOJA_CONTROLLER_MODE_RETRO,
    HOJA_CONTROLLER_MODE_XINPUT,
    HOJA_CONTROLLER_MODE_DINPUT,
} hoja_controller_mode_t;

// Map code is used during remap
// operations and configuration
typedef enum
{
    MAPCODE_DUP = 0,
    MAPCODE_DDOWN,
    MAPCODE_DLEFT,
    MAPCODE_DRIGHT,

    MAPCODE_B_UP,
    MAPCODE_B_DOWN,
    MAPCODE_B_LEFT,
    MAPCODE_B_RIGHT,

    MAPCODE_T_L,
    MAPCODE_T_ZL,
    MAPCODE_T_R,
    MAPCODE_T_ZR,

    MAPCODE_B_START,
    MAPCODE_B_SELECT,
    MAPCODE_B_STICKL,
    MAPCODE_B_STICKR,
} hoja_mapcode_t;

typedef struct
{
    union
    {
        struct
        {
            hoja_mapcode_t dpad_up     : 4;
            hoja_mapcode_t dpad_down   : 4;
            hoja_mapcode_t dpad_left   : 4;
            hoja_mapcode_t dpad_right  : 4;

            hoja_mapcode_t button_up       : 4;
            hoja_mapcode_t button_down     : 4;
            hoja_mapcode_t button_left     : 4;
            hoja_mapcode_t button_right    : 4;

            hoja_mapcode_t trigger_l       : 4;
            hoja_mapcode_t trigger_zl      : 4;
            hoja_mapcode_t trigger_r       : 4;
            hoja_mapcode_t trigger_zr      : 4;

            hoja_mapcode_t button_start    : 4;
            hoja_mapcode_t button_select   : 4;
            hoja_mapcode_t button_stick_left : 4;
            hoja_mapcode_t button_stick_right : 4;
        };
        uint64_t val;
    };
} button_remap_s;

typedef enum
{
    // Behaves as dpad only
    DPAD_MODE_STANDARD = 0,
    // Behaves as left analog only
    DPAD_MODE_ANALOGONLY,
    // Behaves as right analog only
    DPAD_MODE_RIGHTANALOGONLY,
    // Behaves as dpad and left analog
    DPAD_MODE_DUAL,
} hoja_dpadmode_t;

#endif