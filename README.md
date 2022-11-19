### Discussion
- The testing carried out in this exercise is based on lab 2.

## Git branching/versioning 

The git branching for this exercise was implemented such that each branch acted as a "folder" for each test case, ie, 3 branches for unit testing, 1 branch for integration testing and 1 for verification testing. This was done as it allowed for easy manipulation of the project files to carry out the tests. The versioning of the branches is based on commits given the one can return to previous commits. 

For larger projects however, branching strategies such as [GitHub flow](https://docs.github.com/en/get-started/quickstart/github-flow) can be implemented. Other branching models can also be implemented as discussed [here](https://nvie.com/posts/a-successful-git-branching-model/). The branching models discussed will allow for larger scope project where multiple collaborators can simultaneously work on one project.  

## Unit Testing
**All information regarding the actual tests carried out are provided in the corresponding branch.**  

For unit testing, the functions were tested using stubs to simulate the environment they would alter. It is important to note that the testing was carried out for the basic operations of the functions, i.e., turn on LED, turn off LED and display a status message of the gpio pin. Any timings were not considered for the unit tests. The unit testing was structured such that the function was called and the output was observed based on the expected outcome. For example, to unit test the "status_msg function", the gpio level was set giving a simulated environment and the function was called. When the function was called, it was expected that the function would display the status of the gpio pin. Hence the unit tests were structured using the following prompts:

Purpose:   
Pre-Conditions:      
Test Input:     
Expected:    
Test Results:   
Test Result Evidence:  

where the expected outcome and test result were compared to determine if the unit test passed or failed. 

For future development, testing frameworks can be implemented which can improved the validity of the testing. Such testing frameworks are [Unity](http://www.throwtheswitch.org).

## Integration Testing   
**All information regarding the actual test carried out are provided in the corresponding branch.**

Integration testing was done similarily to the unit testing, meaning the same format of testing was used,i.e.,  

Purpose: Test to ensure the functions work sequentially using gpio_on and status_msg such that the status_msg works to display the state given the function call for gpio_on.

Pre-Conditions: 3V to esp8266-01, working LED

Test Input: Conifgured GPIO2 pin, call gpio_on, call status_msg

Expected: LED light turns on, status message is diplayed

Test Results: LED light turns on, status message is diplayed

Test Result Evidence: lab3_integrationtest.out 

However, for this exercise, only one integration test was carried out as gpio_on and gpio_off are essentially the reverse of each other. Considering this, once the "status_msg" function worked with either, therefore, complete integration of all the functions would work. Similarily to the unit test, the test was carried out to test the basic operations as above. A [driver/stub](https://www.geeksforgeeks.org/difference-between-stubs-and-drivers/) was not used as the nature of the test did not require it. Due to drivers being used in place of modules not yet developed, it was not needed. In this instance, all modules required were available.  As discussed in unit testing, there are frameworks that can be implemented for larger scope projects.

## Verification Testing

**All information regarding the actual test carried out are provided in the corresponding branch.**

The following requirements were verified:

1. A task turns the GPIO pin on
2. A task turn the GPIO pin off
3. The GPIO pin should be managed using a semaphore/mutex.
4. The third task will print a status message only for each iteration of change in GPIO.
5. Each task should have its own priority level in the following order (1.gpio_on; 2. status message 3.gpio_off; 4.status message)

Because the basic operation of the functions to turn on and turn off the LED on the ESP8266 were verified, no additional equipment was required. The testing was carried out using the format from unit testing as seen in the "VerificationTest" branch.