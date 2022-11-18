Verification Test: Verifying the system meets the specified requirements

Requirements/Specifications: 
1. A task turns the GPIO pin on
2. A task turn the GPIO pin off
3. The GPIO pin should be managed using a semaphore/mutex. 
4. The third task will print a status message only for each iteration of change in GPIO.
5. Each task should have it's own priority level in the following order (1.gpio_on; 2. status message 3.gpio_off; 4.status message)

Purpose: To test the system to ensure it meets the requirements

Test Input: Conifgured GPIO2 pin, call gpio_on, call status_msg, call gpio_off

Expected: LED light turns on, status message is diplayed, LED light turns off, status message displayed

Test Results: LED light turns on, status message is diplayed, LED light turns off, status message displayed

Test Result Evidence: lab3_verificationtest.out

