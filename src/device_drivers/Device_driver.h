#ifndef __DEVICE_DRIVER_H_
#define __DEVICE_DRIVER_H_

#include <stdio.h>
#include <string>
#include "INTC.h"

typedef struct 
{
       char  name[32];
       char  type[32];
       char  compatible[128];
 const void *data;
} DT_device_id_t;

// specify user driver interface options
struct Client_ops
{
                int  (*write)(void *p_Obj, const char *buffer, size_t len);    
               char  (*read)(void *p_Obj);
INTC::isr_handler_t  isr;
       
     virtual void operator=(Client_ops &right) = 0;
};

class Device_driver
{
    public:
              Device_driver(const char *name, const DT_device_id_t *match_table)
              : m_Name(name), m_Of_match_table(match_table)
              {}
     
             ~Device_driver() {}

virtual  int  probe (void *p_owner) = 0;
virtual  int  init(void)            = 0;
virtual void  sync_state(void* dev) = 0;
virtual  int  remove (void* dev)    = 0;
virtual void  shutdown (void* dev)  = 0;
virtual  int  suspend (void* dev)   = 0;
virtual  int  resume (void* dev)    = 0;
virtual  int  exit(void)            = 0;

virtual void  set_Client_ops(void *p_owner, Client_ops *p_ops) = 0;
  Client_ops& get_Client_ops() const { return *mp_Ops; }   
                              
    protected:
       const DT_device_id_t *m_Of_match_table { nullptr };    // device tree load table
                 const char *m_Name           { nullptr };    // driver name
                 Client_ops *mp_Ops           { nullptr };    // Driver callbacks options struct pointer  
                       void *m_Owner          { nullptr };    // who uses driver now
};


// @brief  device driver manager functions
extern bool  Device_driver_register(Device_driver& r_Drv);
extern void  Device_driver_unregister(Device_driver& r_Drv);

#endif  //__DEVICE_DRIVER_H_