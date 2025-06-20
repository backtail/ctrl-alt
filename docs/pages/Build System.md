
# Build System

[TOC]

### Dependency Management

The build system uses scripts in [`scripts/`](scripts/) to automatically generate STM8S configuration headers and resolve dependencies based on the selected program.

### Do's and Don'ts

> [!IMPORTANT]
> `#include "stm8s.h"` will be ignored in any .c or .h file. 

If you wish to directly talk to the peripherals in the user program, you have to include it like so:

```c
#include "stm8s_adc1.h"
#include "stm8s_tim1.h"
#include "stm8s_tim3.h"
```

> [!WARNING]
> Doing this in the user program might mess with the kernel, so this is not recommended. Please use the provided interfaces from `src/kernel/api/` if possible!
