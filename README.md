# How-to-Migrate-Code-from-STM32F103-Target-to-L1xx

Migrating Code from F103 Target to L1xx     July 8, 2020

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Unanimously, migrating code from one target to another has been less painful. It may 
just be a simple recompile of source code or a bit of modification. Well, that is 
assuming that they are of the same processor architecture and same family. If it is of
a different family, it might require more effort because of differences in peripherals
and enhancements made by silicon vendors. Also, it assumes the programmer didn't use
language intrinsics as well as obfucate code. As long as standardized code is use like
CMSIS, it should be quite easy and portable.

Let's take for example code for STM32F103 family. To move that application codeto L1xx, 
you must change the device header files. The IDE, presumably Keil, automatically changes
the common CMSIS core files like core_cm3.h, arm_math.h, to name a few. You have to make
sure you checked off CMSIS core and Device startup boxes in the manage run-time
environment dialog. If you don't you will have to manually include the required files. As
soon, the project is created, type to change the include from "stm32f10x.h" to 
"stm32l1xx.h" and then click the compile/translate to generate the include files.

Resolve the dependencies until you can compile and build the target. That's it, Good luck!

I included some posts for reference.

https://github.com/noey2020/How-to-Illustrate-Multiple-Exceptions-

https://github.com/noey2020/How-to-Blink-LED-using-Standard-Peripheral-Library

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Have fun and happy coding!
