#ifndef __DEVICE_DRIVER_H_
#define __DEVICE_DRIVER_H_

#include <stdio.h>

typedef struct 
{
      char  name[32];
      char  type[32];
      char  compatible[128];
const void *data;
} DT_device_id_t;

// specify user driver interface options
typedef struct
{
        int  (*write)(void *p_Obj, const char *buffer, size_t len);    
       char  (*read)(void *p_Obj);
       void  (*isr_handler)(void *p_Obj);
} Dev_ops_t;

class Device_driver
{
    public:
             Device_driver(const char *name, const DT_device_id_t *match_table)
             : m_Name(name), m_Of_match_table(match_table)
             {}
     
            ~Device_driver() {}

virtual  int  probe (void)          = 0;
virtual  int  init(void)            = 0;
virtual void  sync_state(void* dev) = 0;
virtual  int  remove (void* dev)    = 0;
virtual void  shutdown (void* dev)  = 0;
virtual  int  suspend (void* dev)   = 0;
virtual  int  resume (void* dev)    = 0;
virtual  int  exit(void)            = 0;

        void  set_Client_ops(Dev_ops_t *p_ops)  { mp_Ops = p_ops; }
        void  set_Owner(void *p_own)            { m_Owner = p_own; }

    protected:
       const DT_device_id_t *m_Of_match_table { nullptr };    // device tree load table
                 const char *m_Name           { nullptr };    // driver name

                  Dev_ops_t *mp_Ops           { nullptr };    // Driver callbacks options struct pointer  
                       void *m_Owner          { nullptr };    // who uses driver now
};


// @brief  device driver manager functions
extern bool  Device_driver_register(Device_driver& r_Drv);
extern void  Device_driver_unregister(Device_driver& r_Drv);

#endif  //__DEVICE_DRIVER_H_