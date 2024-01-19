#ifndef _PID_REGULATOR_H
#define _PID_REGULATOR_H

#include <stdbool.h>
#include "stdint.h"

#define PID_OPTIMIZED_I

typedef enum : uint8_t
{
    ON_ERROR = 0,
    ON_RATE
} e_pid_mode;

typedef enum : uint8_t
{
    NORMAL = 0,
    REVERSE
} e_pid_dir;

template<typename T>
class pid_regulator
{
public:
    pid_regulator()
    :m_kp(0.0f), m_ki(0.0f), m_kd(0.0f),m_dt(10),m_dt_s(0.01f) 
    {
        m_mode      = ON_ERROR;
        m_direction = NORMAL;
        m_setpoint  = 0.0f;
        m_input     = 0.0f;
        m_output    = 0.0f;
        m_integral  = 0.0f;
    }

    pid_regulator(float kp, float ki, float kd, uint32_t dt = 10) 
    : m_kp(kp), m_ki(ki), m_kd(kd),m_dt(dt),m_dt_s((float)dt/1000.0f)
    {}

    ~pid_regulator() {}

    void  set_mode(e_pid_mode mode)    { m_mode = mode; }
    void  set_direction(e_pid_dir dir) { m_direction = dir; }
    void  set_limits(T min, T max)     { m_min_out = min; m_max_out = max; }
    void  set_dt(uint32_t dt)          { m_dt_s = (float)dt/1000.0f; m_dt = dt; }

       /**
       * @brief calculate pid regulator in main loop
       */
       T  calculate();

      /**
      * @brief returns a new value not earlier than in dt milliseconds
      */
       T  poll_with_constdt();

       /**
       * @brief calculates the output over the real elapsed time between calls to the function
       */
       T  poll_with_variabledt();

private:
        T m_constrain(T x, T a, T b);  // set value with max and min limits;

        T  m_setpoint;    // value which must be achieved
        T  m_input;       // current input value
        T  m_output;      // output regulation impact
    float  m_kp;          // proportional coefficient
    float  m_ki;          // integral coefficient
    float  m_kd;          // differential coefficient
    float  m_integral;    // integral sum

    uint32_t  m_dt;       // dt in milliseconds
       float  m_dt_s;     // dt in seconds
  e_pid_mode  m_mode;
   e_pid_dir  m_direction;
           T  m_min_out;    // minimal output limit
           T  m_max_out;    // maximum output limit
           T  m_prev_input; 
    uint64_t  m_pid_timer;

};

#endif //_PID_REGULATOR_H