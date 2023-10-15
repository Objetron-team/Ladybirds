<?php

//test code for /motor/motor.cpp;
/*
    Test the smooth motor algorithm

    The algorithm is based on the following function:
    f(x) = (( (r*x) + a) / sqrt(1 + ( (r*x) + a)²) + 1) / 2


    The speed of the motor will change smoothly from the current speed to the target speed over a given time period.

    The time period is defined by the ramp_timer variable.

    we use an algebraic function to calculate the smooth transition between the current speed and the target speed.

                (speed)%
                    ^
                    |
           (target) -----------------------------==================
                    |                         ---
    (current_speed) |                    --x--
                    |                 ---  |
      (start_speed) ------------------     |
                    |                      |
                    --------|--------------|-----------|-----------> time
                        (start_timer)      |        (end_timer)
                            |       (time_position)    |
                            |                          |
                            |--------------------------|
                                    (ramp_timer)



    The start_timer and end_timer variables are used to calculate the time position of the current speed. (vary between 0 and 1)
    The time between the start_timer and end_timer is defined by the ramp_timer variable.

    Using the time position we can calculate the speed factor using the GetSpeedFactor function. (vary between 0 and 1)
    With the speed factor we can calculate the current speed using the following formula:
        current_speed = start_speed + ((target_speed - start_speed) * speed_factor)



*/

class Motor{

    public function __construct() {
        $this->current_speed = 0;
        $this->target_speed = $this->current_speed;
        $this->start_timer = 0;
        $this->end_timer = 0;
        $this->start_speed = 0;


        $this->ramp_timer = 5000;
        
    }

    function SetSpeed($target){
        if($target != $this->target_speed){

            echo "Target speed changed\n";

            //set the timer to current timestamp
            $this->start_timer = Millis();
            $this->end_timer = $this->start_timer + $this->ramp_timer;
            $this->start_speed = $this->current_speed;
            $this->target_speed = $target;


            echo "Start timer: " . $this->start_timer . "\n";
            echo "End timer: " . $this->end_timer . "\n";
            echo "Delta timer: " . ($this->end_timer - $this->start_timer) . "\n";

            echo "Current speed: " . $this->current_speed . "\n";
            echo "Target speed: " . $target . "\n";
            echo "Start speed: " . $this->start_speed . "\n";
            echo "Speed delta: " . ($target - $this->start_speed) . "\n";
            echo "--------------------------------------------\n";

        }

        if($this->end_timer == $this->start_timer){
            $this->current_speed = $this->target_speed;
            return $this->current_speed;
        }
    
        $time_position = (Millis() - $this->start_timer) / ($this->end_timer - $this->start_timer);
        $speed_factor = $this->GetSpeedFactor($time_position);

        if($time_position >= 1){
            $this->current_speed = $this->target_speed;
            return $this->current_speed;
        }

        //echo "Time position: " . $time_position . "\n";
        //echo "Speed factor: " . $speed_factor . "\n";


        $this->current_speed = $this->start_speed + (($this->target_speed - $this->start_speed) * $speed_factor);
    
        return $this->current_speed;
    }

    function GetSpeedFactor($time_position){

        //return the speed factor for the given time position -> f(x) = (( (r*x) + a) / sqrt(1 + ( (r*x) + a)²) + 1) / 2


        $x = (8 * $time_position) - 4; 

        $algebraic_function =  ( $x ) / sqrt(1 + ( $x*$x ) );
        
        return ($algebraic_function + 1) / 2;
    }

}

function Millis(){
    return floor(microtime(true) * 1000);
}


$motor = new Motor();

echo "Test GetSpeedFactor\n";
echo $motor->GetSpeedFactor(0) . "\n";
echo $motor->GetSpeedFactor(0.5) . "\n";
echo $motor->GetSpeedFactor(1) . "\n";
echo "--------------------------------------------\n";


$start_time = Millis();
$wait_timer = Millis();

$target = 75;
$speeds = [];

while($motor->current_speed != $target){
    
    if(Millis() - $wait_timer > 0){
        $wait_timer = Millis();
        $speeds[] = $motor->SetSpeed($target);
        //echo Millis() . " Current speed: " . $speed . "\n";
        //echo "--------------------------------------------\n";
    }

}

$end_time = Millis();

echo "Time taken: " . ($end_time - $start_time) . " milliseconds\n";
print_r($speeds);

?>