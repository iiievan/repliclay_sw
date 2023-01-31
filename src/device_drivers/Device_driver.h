#ifndef __DEVICE_DRIVER_H_
#define __DEVICE_DRIVER_H_

typedef struct 
{
      char  name[32];
      char  type[32];
      char  compatible[128];
const void *data;
} DT_device_id_t;

class Device_driver
{
    public:
             Device_driver(const char *name, DT_device_id_t  *match_table)
             : m_Name(name), m_Of_match_table(match_table)
             {}
     
            ~Device_driver() {}

virtual  int  probe (void* dev)     = 0;
virtual  int  init(void)            = 0;
virtual void  sync_state(void* dev) = 0;
virtual  int  remove (void* dev)    = 0;
virtual void  shutdown (void* dev)  = 0;
virtual  int  suspend (void* dev)   = 0;
virtual  int  resume (void* dev)    = 0;
virtual  int  exit(void)            = 0;

    protected:
            const struct dev_pm_ops *pm;
                 const char *m_Name           { nullptr };    // driver name
                       void *m_Owner          { nullptr };    // who uses driver now
       const DT_device_id_t *m_Of_match_table { nullptr };    // device tree load table
};

extern void Device_driver_register(Device_driver& r_Drv);
extern void Device_driver_unregister(Device_driver& r_Drv);
extern void Device_driver_set_client_ops(Device_driver& r_Drv, void * p_options);

#endif  //__DEVICE_DRIVER_H_