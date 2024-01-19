#include "pid_regulator.hpp"

#ifdef CMSIS_OS_H_
#    include "FreeRTOS.h"
#    define GET_MS_FROM_BOOT (xTaskGetTickCount() * portTICK_PERIOD_MS)
#else
#    include "stm32f7xx_hal.h"
#    define GET_MS_FROM_BOOT HAL_GetTick()
#endif

template<typename T>
T pid_regulator<T>::calculate()
{
    T error = m_setpoint - m_input;             // regulation error
    T delta_input = m_prev_input - m_input;      
    m_prev_input = m_input;                     
    
    if (m_direction) 
    {   
        error = -error;
        delta_input = -delta_input;
    }

    m_output = m_mode ? 0 : (error * m_kp);         // proportional component
    m_output += (delta_input * m_kd) / m_dt_s;        // differential component
    
    m_integral += error * m_ki * m_dt_s;

#ifdef PID_OPTIMIZED_I
    m_output = m_constrain(m_output, m_min_out, m_max_out);
    if (m_ki != 0) 
        m_integral = m_constrain(m_integral,
                                 (m_min_out - m_output) / m_ki * m_dt_s,
                                 (m_max_out - m_output) / m_ki * m_dt_s);
#endif      
    // proportional speed mode
    if (m_mode) 
        m_integral += delta_input * m_kp;

    m_integral = m_constrain(m_integral, m_min_out, m_max_out);   // limiting integral summ
    m_output += m_integral;                                       // integral component
    m_output = m_constrain(m_output, m_min_out, m_max_out);       // limiting output
    
    return m_output;
}

template<typename T>
T pid_regulator<T>::poll_with_constdt() 
{
    if (((uint32_t)(GET_MS_FROM_BOOT - m_pid_timer)) >= m_dt) 
    {
        m_pid_timer = GET_MS_FROM_BOOT;
        calculate();
    }
    return m_output;
}

template<typename T>
T pid_regulator<T>::poll_with_variabledt() 
{
    set_dt((uint32_t)(GET_MS_FROM_BOOT - m_pid_timer));

    m_pid_timer = GET_MS_FROM_BOOT;

    return calculate();
}

template<typename T>
T pid_regulator<T>::m_constrain(T x, T a, T b)
{
    if(x < a) 
        return a;
    else 
    if(b < x) 
        return b;
    else
        return x;
}

/**
* @brief template specialization
*/
template class pid_regulator<float>;