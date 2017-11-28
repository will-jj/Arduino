### OpenHAB boiler relay/thermostat control:

#### Required items for basic control:

```
Switch boiler "Boiler [%s]"
Switch boiler_confirm "Boiler Status"
```
#### Required items for temperature control:

```
Number Inside_Temp  "Room Temp [%.2f °C]" 
Number temp_set_point  "Temp Set Point [%.1f °C]"
Switch boiler_therm "Boiler Temp Mode"
```

#### Example rule for temperature control:

```
rule "heating temp set"
    when
		Item Inside_Temp changed or Item boiler_therm changed or Item temp_set_point changed
    then
    var Number setpoint = temp_set_point.state as DecimalType
	var Number cur_temp = Inside_Temp.state as DecimalType
    val  hysteresis = 0.5
        if (boiler_therm.state == ON){
                

		if (cur_temp <= (setpoint - hysteresis)) {
			if (boiler.state == OFF) {
                
                logInfo("(boiler)", "on due to temp")


				sendCommand(boiler, ON)
				}
			}
        
        
		
			
	if (cur_temp >= (setpoint + hysteresis)) {
      
        logInfo("(boiler)", "off due to temp")
			if (boiler.state == ON) {


				sendCommand(boiler, OFF)
				}
			}	
        }
    if (boiler_therm.state == OFF && boiler_boost.state == OFF){
            sendCommand(boiler,OFF)
        }

    end

```

#### Sitemap Example:

```

Text label="Heating" icon="fire"{
			Text item=Inside_Temp icon="temperature"
			Setpoint item=temp_set_point icon=heating step=0.5 minValue=10 maxValue=25 
			Text item=boiler_confirm icon=fire 
			Switch item=boiler_therm 
			}
			
```