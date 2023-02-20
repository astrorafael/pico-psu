# Linenoise

Port from the original `antirez's linenoise library`[https://github.com/antirez/linenoise] for an embedded envirnoment
This port is really mininal:
* No line editing feature. This is really a Dumb mode line entry
* No completion history.

Also, provision has been made for custom allocators in embdeed environments (such as FreeRTOS)
The original license has been preserved.
