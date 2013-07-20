online_railway_reservation
==========================
Write-up on
Railway Reservation System
Name : Saswata Ghosh
Objective :
We have to simulate a railway reservation system for a fixed source to a fixed
destination.
Assignment :
There are three types of seats say ac, sleeper class and chair car with number of
seats for each class given (say m, n and r respectively).
The implementation should have following functionalities.
Book Tickets: takes as input number of seats to be booked and the class to which booking
will be done. It books said number of tickets in that class if available or prints a
message that “seats are not available “.
Check Availability: takes as input the class and prints available seats in that particular
class.
Cancellation: takes class and number of tickets to be cancelled. Cancels said no of tickets
of the said class. (Make sure that no of booked tickets after cancellation does not
go below zero.
The Implementation should ensure that if there is a process that is booking tickets (critical
section since updating shared data), no other process will be allowed to book tickets or view
availability. But, if more than one process wants to book tickets simultaneously of different
classes they will be allowed to do so. On the other hand, if more than one process wishes to
check availability, they will be allowed simultaneously. Note also that if a process is checking
availability and a process that wishes to book ticket makes a request, it must wait until the
reader (the one checking availability) finishes its reading.

Semaphores:
There are in total 10 semaphores used in the solution .
1. Mutex1 : initiallised to 1. Mainly used for making the a.c.processes
mutually exclusive to each other.2. Mutex2 : initiallised to 1. Mainly used for making the chair car
processes mutually exclusive to each other.
3. Mutex3 : initiallised to 1. Mainly used for making the sleeper processes
mutually exclusive to each other.
4. Bookac : initillised to 1. Used to control the processes that enter the
critical region to
book the tickets.
5. Cancelac : initiallised to 1. Used to control the processes the that enter
the critical region to cancl the tickets.
6. Check : initiallised to 1. Used to check the no. of seats in the shared
memory of the ac class.
7. Bookcc : initillised to 1. Used to control the processes that enter the
critical region to
book the tickets in the chair car.
8. Cancelcc : initiallised to 1. Used to control the processes the that
enter the critical region to cancl the tickets in the chair car.
9. Booksl : initillised to 1. Used to control the processes that enter the
critical region to book the tickets in the sleeper.
10. Cancelsl : initiallised to 1. Used to control the processes the that enter
the critical region to cancl the tickets in the sleeper.

for the detailed algorithm contact me at saswata10@gmail.com
