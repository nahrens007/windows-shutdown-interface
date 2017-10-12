# windows-shutdown-interface
Interface for shutting down Windows at a specified time. 

# Functionality
- Shut down the computer by specifying the date/time to shut down.
- Shut down the computer by specifying the number of hours, minutes, and seconds to wait for shutdown.

# Goal
The goal of this program is to allow the user to choose a date/time or an amount of time to pass by before shutting down the computer. This becomes valuable when you have a program that is running (perhaps downloading a large file) that you expect to have finished by a certain time, but don't want to manually shut down the computer when it finishes. 

# Tech Specs
The program is written in C++ using the Qt GUI library. 
The computer is shut down the same way that it would be by issuing the command "shutdown.exe /s /f /t 0". This causes
