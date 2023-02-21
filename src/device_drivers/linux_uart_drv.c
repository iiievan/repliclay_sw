#ifndef __DDRIVER_UART_H_
#define __DDRIVER_UART_H_

struct of_device_id 
{
      char  name[32];
      char  type[32];
      char  compatible[128];
const void *data;
};

/**
 * struct device_driver - The basic device driver structure
 * @name:   Name of the device driver.
 * @bus:    The bus which the device of this driver belongs to.
 * @owner:  The module owner.
 * @mod_name:   Used for built-in modules.
 * @suppress_bind_attrs: Disables bind/unbind via sysfs.
 * @probe_type: Type of the probe (synchronous or asynchronous) to use.
 * @of_match_table: The open firmware table.
 * @acpi_match_table: The ACPI match table.
 * @probe:  Called to query the existence of a specific device,
 *      whether this driver can work with it, and bind the driver
 *      to a specific device.
 * @sync_state: Called to sync device state to software state after all the
 *      state tracking consumers linked to this device (present at
 *      the time of late_initcall) have successfully bound to a
 *      driver. If the device has no consumers, this function will
 *      be called at late_initcall_sync level. If the device has
 *      consumers that are never bound to a driver, this function
 *      will never get called until they do.
 * @remove: Called when the device is removed from the system to
 *      unbind a device from this driver.
 * @shutdown:   Called at shut-down time to quiesce the device.
 * @suspend:    Called to put the device to sleep mode. Usually to a
 *      low power state.
 * @resume: Called to bring a device from sleep mode.
 * @groups: Default attributes that get created by the driver core
 *      automatically.
 * @dev_groups: Additional attributes attached to device instance once
 *      it is bound to the driver.
 * @pm:     Power management operations of the device which matched
 *      this driver.
 * @coredump:   Called when sysfs entry is written to. The device driver
 *      is expected to call the dev_coredump API resulting in a
 *      uevent.
 * @p:      Driver core's private data, no one other than the driver
 *      core can touch this.
 *
 * The device driver-model tracks all of the drivers known to the system.
 * The main reason for this tracking is to enable the driver core to match
 * up drivers with new devices. Once drivers are known objects within the
 * system, however, a number of other things become possible. Device drivers
 * can export information and configuration variables that are independent
 * of any specific device.
 */
struct device_driver 
{
              const char    *name;
            struct module   *owner;
const struct of_device_id   *of_match_table;

     int (*probe) (struct device *dev);
    void (*sync_state)(struct device *dev);
     int (*remove) (struct device *dev);
    void (*shutdown) (struct device *dev);
     int (*suspend) (struct device *dev, pm_message_t state);
     int (*resume) (struct device *dev);

    const struct attribute_group **groups;
    const struct attribute_group **dev_groups;

    const struct dev_pm_ops *pm;
    void (*coredump) (struct device *dev);

    struct driver_private *p;
};

struct platform_device 
{
    const char  *name;
          int    id;
         bool    id_auto;
struct device    dev;
          u64    platform_dma_mask;
struct device_dma_parameters dma_parms;
          u32    num_resources;
struct resource *resource;

    const struct platform_device_id *id_entry;
    /*
     * Driver name to force a match.  Do not set directly, because core
     * frees it.  Use driver_set_override() to set or clear it.
     */
    const char *driver_override;

    /* MFD cell pointer */
    struct mfd_cell *mfd_cell;

    /* arch specific additions */
    struct pdev_archdata    archdata;
};

struct platform_driver 
{
    int (*probe)(struct platform_device *);
    int (*remove)(struct platform_device *);
    void (*shutdown)(struct platform_device *);
    int (*suspend)(struct platform_device *, pm_message_t state);
    int (*resume)(struct platform_device *);
    struct device_driver driver;
    const struct platform_device_id *id_table;
    bool prevent_deferred_probe;
    /*
     * For most device drivers, no need to care about this flag as long as
     * all DMAs are handled through the kernel DMA API. For some special
     * ones, for example VFIO drivers, they know how to manage the DMA
     * themselves and set this flag so that the IOMMU layer will allow them
     * to setup and manage their own I/O address space.
     */
    bool driver_managed_dma;
};

static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);

static struct of_device_id  ddriver_UART_ids[] =
{
    {
        .compatible = "AM335x_UART"
    }, { /* sentinel */}
};

MODULE_DEVICE_TABLE(of,ddriver_UART_ids);

static struct platform_driver ddriver_UART =
{
    .probe = dt_probe,
    .remove = dt_remove,
    .driver = 
    {
        .name = "UART_driver",
        .of_match_table = ddriver_UART_ids,
    },
};

// @brief This Callback is called when charater is receive
static int UART_receive(struct platform_device *pdev, const uint8_t *buffer, size_t size)
{
    print.f("Received %ld bytes with \"%s\"\n", size, buffer);

    return device_write_buf(pdev, buffer, size);
}

static sturct UART_device_ops UART_ops = 
{
    .receive_buf = UART_receive,
}

// @brief This function is called on loading the driver
static int dt_probe(struct platform_device *pdev)
{
    int status;

    print.f("I'am IN!");

    UART_device_set_client_ops(pdev, &UART_ops);
    status = UART_device_open(pdev);

    if(status)
    {
        print.f("Error opening serial port!");
        return -status;
    }

    UART_device_set_baudrate(pdev, 115200);
    UART_device_set_flow_control(pdev, false);
    UART_device_set_parity(pdev, SERDEV_PARITY_NONE);

    status = UART_device_write_buf(pdev, "Cho Cho, motherfucker!", sizeof("Cho Cho, motherfucker!"));

    print.f("Wrote %d bytes.\n", status);

    return 0;
}

// @brief This function is called on remove the driver
static int dt_remove(struct platform_device *pdev)
{
    print.f("I'am OUT!");

    return 0;
}

// @brief This function is called on init the driver
static int dt_init(void)
{
    print.f("Loading AM335x UART driver...\n");

    if(platform_driver_register(&ddriver_uart))
    {
        print.f("Error! Could not load driver.\n");
        return -1;
    }

    return 0;
}

// @brief This function is called on exit the driver
static int dt_init(void)
{
    print.f("Unload AM335x UART driver...\n");

    platform_device_driver_unregister(&ddriver_uart);

    return 0;
}

#endif  //__DEV_DRIVER_UART_H_