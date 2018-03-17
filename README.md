# riot
All the stuff in the project for university with an Atmel SAM R21 running riot

# Goal
The goal of the project is to create a door lock system with a pin code panel, two Atmel SAM R21 boards and a linux machine.
One of the SAM R21 boards is outside and connected to the pin code panel, the other is inside and connected to the door lock and the linux machine (LM) (with serial connection).
The outside board should now inform the linux machine whenever a password is entered on the pin code panel. The linux machine checks the password and if it is right, it tells the inside board to open the lock.

# Idea
On the outside board runs a coap-server (CS) that can answer to coap-requests and is observable. The inside board got a border router (BR) running on it. The BR creates a network where the LM (over serial) and the CS (over antenna) are connected to. The LM can send single coap-requests to the CS or observe one of its resources over the network of the BR. 

After the network is created LM should observe a resource of the CS (maybe the resource of the OK button on the pin code panel). Once the resource changes, the LM is getting informed via some payload from CS to LM where the inserted password should be in. The LM compares the inserted received password with the defined correct password. If they are equal, it connects to the BR and tells him to activate a special gpio pin to open the lock.

# Used tools
## nanocoap-server

## coap-client
### simple request
coap-client -m get "\<coapAdress\>:\<port\>/\<resource\>"
example:
coap-client -m get "coap://[2001:db8::7b7c:3c3e:f334:64fa]:5683/riot/gcoap/init"
or
coap-client -m get coap://californium.eclipse.org/

### payload
With the option -e \<somePayload\> you can add some payload to the request

### observe
With the option -s \<timeToSubscribe\> you can subscribe to a following resource for the given time.

## ethos
The tool ethos from the riot projects helps to create a network with a connected border router (serial).

# Realization

## Coap-server
### Modify
The coap-server is basically the modified riot nanocoap-server example. Here the nanocoap resources are changed to gcoap resources. That step was neccesary, because the nanocoap librariy got no functions for observing resources. But there are gcoap functions to realize an observe of a resource.
To create and support gcoap resources these steps have to be done:
- initialize a gcoap listener with the function gcoap_register_listener( listener )
- initialize the listener variable with the resources that are also given for the nanocaop server
- handle (normal) resources with coap functions like:
    + gcoap_resp_init()
    + gcoap_finish()

### Handle observe request
First of all the resource that should be observed does not need to be special in any way. It can be a normal resource that uses gcoap_resp_init and gcoap_finish, which are used on a simple gcoap request.
If a resource gets a call with an observe option, the same steps are proceeded that would be on a simple coap request. The difference is, that in the request it is not closed afterwards and the server notes that the resource is obsered which is important for the following steps.
Now that the resource is observed, you can use this resource as a communication to the coap-client from different points in the program with 4 simple steps. For example you could write a interrupt service routine that is executed when a button is pressed. In this ISR you could now initialize these 4 steps to send an update over the observe channel to the coap-client. So the observe is not really fixed on a value that changes and as an action to that an observe answer is sent. Basically these observe answers can be triggered from totally different parts of the program, even another coap request, as long as the observed resource is known.

The example of the ISR was realized to this state of the project. So instead of the goal setup with an pin code panel for now just one button is used. For that example the payload was chosen to be a char that is increased every time a coap answer is created.

## Linux machine
An easy setup to work with is the commandline tool coap-client from Olaf Bergmann.

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

## Observe the resource again after the time ran out
It happens that the canceling of the observation does not really work sometimes. The client stops the process. But if the resource is observed again, it fails. The module has to be reseted, to make the observe work again. It could be that it got a problem with the modified nanocoap server. 
As default a resource can only have one observer, so it could be that the unsubscription of an resource does not work as it is planed. Which would cause a the fail of a new observe request, when the old observ is not active anymore but still listed somehow.