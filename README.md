## Integration Test: Integration of gpio_on, gpio_off and status_msg

Purpose: Test to ensure the functions work sequentially  

Pre-Conditions: 3V to esp8266-01, working LED   

Test Input: Conifgured GPIO2 pin, call gpio_on, call    status_msg, call gpio_off   

Expected: LED light turns on, status message is diplayed, LED turns off  

Test Results: LED light turns on, status message is diplayed, LED turns off

Test Result Evidence: lab3_integrationtest.out