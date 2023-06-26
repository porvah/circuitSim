# Circuit Sim V1.0
## Preview:
        This Project is made by one and only one student under the directions of prof. Hicham El-Mongui 
        University of Alexandria.
        It was made for learning purposes only.
## Instructions:
        This project is currently in early access and has no GUI.
        To start using this program follow the steps below:
            1. Go to x64 folder -> release directory and open "circuitSim.exe".
            2. To enter the circuit draw the circuit and label each node from 0 to n.
            3. Enter the total number of nodes and compenents to the console window.
            4. Proceed to fill up each component in the following format.
            5. Each component has 4 attributes that you have to fill.
            6. First the type.. place 1 if it is a resistance and 2 if it is a dc voltage source.
                Only dc is currenty supported in this version. Further updates are under development.
            7. Second the value.. place the value of the component in volts (if voltage source) or in kohms (if 
                resistance). You dont need to write the unit.
            8. Third the first terminal node.. in case of resistors T1 and T2 can be switched but in case of voltage 
                sources T1 is connected to the -ve side of the source.
            9. Fourth the second terminal node .. this one is connected to the +ve side of the source if it is a 
                source if case of a resistance it is connected to the other side of the resistance.
            10. After filling all the components choose the ground node (from 0 to n).
        Examples:
            1. To input a resistance of 2kohms that is connected from node 3 to 5
                type :"1 2 3 5"
            2. To input a source of 3 volts with the -ve connected to node 2 and +ve to node 0
                type :"2 3 2 0"
## Notes:
    Source code is located in the root directory of the repository.
##  Credit:
    Name : Abdullah M. El-Sayed.
    University ID: 21010811