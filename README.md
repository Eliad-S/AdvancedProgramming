# AdvancedProgramming1
# Interpreter-Flight-Simulator-language
Interpreter for a flight simulator coding language, made with CPP. 

## General Description

This program interprets a programming language that was created in order to control "[_FlightGear_]" (https://www.flightgear.org/) flight simulator. 
The program connects to the flight simulator both as client and server.
The client will send the simulator instructions that were coded in the script. That allows us to control our flight vessel with code.
The server will get live data about the flight. 

## Collaborators

This program was developed by Eliad sellem and Shir Goldberger, CS students from Bar-Ilan university, Israel.


## Features

- The program is reading reading from a file given as an argument to the program and placed in the directory of the
cpp of the running program, and start to interpret it line by line and translate it into flight insructions.

- while interpret the file, the program will open a new connection with the simulator, the program as a server and the
simulator as a client in order to get real live data from your flight.

- simultaneously we will open an other connection from the simulator as a server and our program as a client in order to
update the simulator about changed that have been made in the program while interpreting the file.

- The program will support arithmetic expressions (Divide, Multiply, Plus, Minus) using Shunting-Yard algorithm.

- Function definition and usage of functions are supported.

- Nested loops and if statements are supported.

## Setup and execute

1. Insert the file generic_small.xml (can be found inside the repository) into the following path:
    ```bash
    [FlightGear installation path]/‫‪data/protocol
    ```

2. Start with adding the following lines into the additional setting in FlightGear:

    ```bash
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
    --telnet=socket,in,10,127.0.0.1,5402,tcp
    ```
You can choose IP and Port as desired, but you should keep LocalHost IP if you're running both the program and the simulator on the same PC.

3. Complie the program code:

    ```bash
    g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out
    ```

4. Run a.out with the relative path of the code you want to execute as the first argument (Should be in txt file).

5. The program will wait for you to open the FlightGear simulator and start a flight.

6. Look at the simulator and enjoy your flight.

## Comments

1. Please find the file: "fly_with_func" in the repository as an example to a valid script, you can go ahead and execute it.

