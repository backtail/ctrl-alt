/// @file user_program.h
/// @brief User program header file
/// @details This file contains the declarations for the user-defined functions
/// setup, start, and update. These functions are called in the main program
/// to allow the user to define their own setup, start, and update logic.

#ifndef _USER_PROGRAM_H_
#define _USER_PROGRAM_H_

/// @brief User-defined setup function
/// @details This function is called once at the beginning of the program.
/// It is used to initialize any user-defined variables, configure hardware,
/// and set up any necessary state for the program.
/// @warning If this function is not defined in a user program, the project
/// will not compile.
void setup(void);

/// @brief User-defined start function
/// @details This function is called once after the setup function.
/// It is used to start any processes or tasks that need to run after the
/// initial setup is complete. This function is typically used to start
/// timers, interrupts, or other hardware components that need to be
/// initialized before the main program loop begins.
/// @note This function is called after global interrupts have been enabled.
/// @note Kernel hardware will have started before this function is called.
/// @warning If this function is not defined in a user program, the project
/// will not compile.
void start(void);

/// @brief User-defined update function
/// @details This function is called repeatedly in the main program loop.
/// It is used to perform any periodic tasks or updates that need to occur
/// during the execution of the program. This function is typically used
/// to update the state of the program, read input values, or perform
/// calculations based on the current state of the program.
/// @warning If this function is not defined in a user program, the project
/// will not compile.
void update(void);

#endif // _USER_PROGRAM_H_