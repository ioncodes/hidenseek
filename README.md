# hidenseek
Playing hide and seek in kernel mode.

## What is this?
This is a driver. Why? It makes it easier to research and debug.  
Goal of this driver is to show how process/driver hiding can be achieved by manipulating kernel objects directly. Furthermore, the driver should be able to detect a hidden process as well.

## Hiding
Hiding is implemented by directly manipulating the kernel. Some theory first:  
People that are familiar with the `EPROCESS` structure might recognize this easier. There is a member called `ActiveProcessLinks` which is basically a double linked list.  
One such entry contains 2 links: `Blinks` and `Flinks`.  

```
> dt nt!_LIST_ENTRY
+0x000 Flink : Ptr64 _LIST_ENTRY
+0x008 Blink : Ptr64 _LIST_ENTRY
```

A flink points to the next process (forward link) and a blink points to the previous link (backwards link).  
The driver is one such entry. We overwrite the driver's blink with the driver's flink directly and the other way around, this way the driver is "hidden" from the process list.

### How to use this
Build the source (make sure you have the driver kit installed). Load the driver with your preferred method and open up Process Explorer.  
In Process Explorer select the System process (PID 4). Then `View > Show Lower Pane`. Then `View > Lower Pane View > DLLs`. Look for `hidenseek.sys`, can't find it? Good ;)

## Detection
TBD
