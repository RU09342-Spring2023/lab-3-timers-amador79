# Deliverables
You will need to upload your code, well documented. You will also need a README for your code (you can replace this README) which will tell the user:
- How does your code work?
              My code uses interrupts from pin 2.3 and 4.1 to reset the timer and read the timer value to set the led to blink at that specific time.
  
- How are the peripherals configured (what modes, what settings)?
               P1.0 is an output, P2.3 is an input with a pullup resistor with interrupts enabled, P4.1 is an input with a pullup resistor with interrupts enabled, TimerB1 is intialized with ACLK divided by 8 with interrupts enabled.
  
- What design considerations did you have to take to account for things like the timer rollover?
                I used the clock in continuous mode rather than up mode so it can count for longer intervals of time allowing the user to hold the button down longer.
  
- How should the user use your code?
             Just press play and the code works on its own, there are no user inputed variables needed.
