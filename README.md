# Dynamic Item list creator
This application was created from scratch in under a week, with the purpose to train on class inheritance, custom headers and dynamic memory allocation working in unison.


Instructions:

This programme is used to create a dynamic list of elements, namely PCs, which can be one of 3 types: HomePC, GamingPC, WorkstationPC. It can then perform some functions on the created list, said functions will be specified bellow.


1)This programme uses input from the command line

2) The available opcodes are:
    i) new,  creates a new PC of a given type and name (eg. new HomePC myPC)
    ii) upgrade, upgrades the specs of a given PC (eg. upgrade myPC 2 2 8)
    iii) delete, deletes a PC from the list (eg. delete myPC)
    iv) print "PC type", prints every PC of the given type, along with their individual specs (eg. print HomePC)
    v) compare "x_name" "y_name", compares 2 PCs by name, only for the fields where comparison is applicable, such as CPU cores, but not the OS or the model name (eg. compare myPC yourPC)

3) Examples of using each opcode:

> new HomePC myPC
> new GamingPC myGamingPC
> compare myPC myGamingPC

myPC vs myGamingPC
CPU cores: 2 < 6
Total RAM: 4 < 16
Storage: 256 < 1024
Cost: 800 > 1300
