# riot
All the stuff in the project for university with an Atmel SAM R21 running riot

# Goal
The goal of the project is to create a door lock system with a pin code panel, two Atmel SAM R21 boards and a linux machine.
One of the SAM R21 boards is outside and connected to the pin code panel, the other is inside and connected to the door lock and the linux machine (LM) (with serial connection).
The outside board should now inform the linux machine whenever a password is entered on the pin code panel. The linux machine checks the password and if it is right, it tells the inside board to open the lock.

# Idea
On the outside board runs a coap-server (CS) that can answer to coap-requests and is observable. The inside board got a border router (BR) running on it. The BR creates a network where the LM (over serial) and the CS (over antenna) are connected to. The LM can send single coap-requests to the CS or observe one of its resources over the network of the BR. 

After the network is created LM should observe a resource of the CS (maybe the resource of the OK button on the pin code panel). Once the resource changes, the LM is getting informed via some payload from CS to LM where the inserted password should be in. The LM compares the inserted received password with the defined correct password. If they are equal, it connects to the BR and tells him to activate a special gpio pin to open the lock.

# Realization
## Coap-server
The coap-server is basically the modified riot nanocoap-server example. Here the nanocoap resources are changed to gcoap resources. That step was neccesary, because the nanocoap librariy got no functions for observing resources. But there are gcoap functions to realize an observe of a resource.
With 

## Linux machine

# Problems
## Bringing the linux machine processes together to one
Ah problem is that the process to observe an resource from the CS and the process to open the network with the riot tool ethos, both require an own terminal and therefore an their own processes.
From the understanding, it should be possible to:
- open a terminal to the BR
- create that network with some commands
- close the terminal
- start observing the CS resource
- if a password comes in and it is right -> open a terminal to the BR (again)
- set gpio pins to open the lock
- close terminal to BR
- start observing the CS resource again
and so on...

But the problem starts with closing the terminal to the BR without losing the network.