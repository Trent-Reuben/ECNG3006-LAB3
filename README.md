## Integration Test: Integration of gpio_on and status_msg

Purpose: Test to ensure the functions work sequentially using gpio_on and status_msg such that the status_msg works to display the state given the function call for gpio_on.

Pre-Conditions: 3V to esp8266-01, working LED   

Test Input: Conifgured GPIO2 pin, call gpio_on, call status_msg

Expected: LED light turns on, status message is diplayed 

Test Results: LED light turns on, status message is diplayed

Test Result Evidence: lab3_integrationtest.out