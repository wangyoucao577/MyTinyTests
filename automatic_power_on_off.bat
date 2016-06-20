
set /a start_count=0
:loop


serial_power_on_off.py COM4 OFF
timeout 5

serial_power_on_off.py COM4 ON
set /a start_count=%start_count%+1
echo "power on count :" %start_count% 
timeout 200

goto loop