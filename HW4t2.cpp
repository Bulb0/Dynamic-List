#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "PCs.h"

using namespace std;


int main()
{
    int found = 0, error = 0, cores = 0, ramslots = 0, GBperRam = 0, GPUcount = 0, Aftercount = 0, AfterErr = 0;
    string tmpname, opcode, name, type, input = "", FirstComp = "", SecondComp = "", type1, type2;
    vector <PC*> PCList;
    PC* yeet = NULL;
    PC* tmp = NULL;
    int i, FI, SI, tmpInfo;


    while (input != "q") {
        i = 0;
        yeet = NULL;
        type = "";
        name = "";
        error = 0;
        found = 0;
        FirstComp = "";
        SecondComp = "";
        tmpname = "";


        opcode = "";
        getline(cin, input);

        for (i; input[i] != ' ' && i < input.length(); i++) {
            opcode += input[i];
        }
        i++;

        if (opcode == "new") {

            if (i == (input.length() + 1)) {
                cout << "Please enter a PC type\n";
                continue;
            }

            for (i; input[i] != ' ' && i < input.length(); i++) {
                type += input[i];
            }
            i++;

            if (i == (input.length() + 1)) {
                cout << "Please enter a name after you enter the type.\n";
                continue;
            }

            for (i; error == 0 && i < input.length(); i++) {
                if (input[i] == ' ') {
                    cout << "No empty spaces allowed in the names!\n";
                    error = 2;
                }
                name += input[i];
            }

            if (name == "") {
                cout << "Enter a model name for the PC\n";
                continue;
            }


            for (int j = 0; j < PCList.size(); j++) {
                tmpname = PCList[j]->ReturnModel();
                if (tmpname == name) {
                    cout << "This PC model already exists in the list\n";
                    error = 1;
                }
            }

            if (error == 1)
                continue;

            if (type == "HomePC") {
                yeet = new HomePC(name);
            }

            else if (type == "GamingPC") {
                yeet = new GamingPC(name);
            }

            else if (type == "WorkstationPC") {
                yeet = new WorkstationPC(name);
            }

            else {
                cout << "Unknown PC type, please enter a valid one!\n";
                error = 1;
            }

            if (error == 0) {
                cout << "Before\n";
                PCList.push_back(yeet);
                cout << "After\n";
            }

        }

        else if (opcode == "upgrade") {
            cores = 0;
            ramslots = 0;
            GBperRam = 0;
            GPUcount = 0;
            Aftercount = 0;

            if (i == (input.length() + 1)) {
                cout << "Please enter a PC model to upgrade\n";
                continue;
            }

            for (i; input[i] != ' ' && i < input.length(); i++) {
                name += input[i];
            }

            if (name == "") {
                cout << "Please enter a PC model to upgrade\n";
                continue;
            }

            found = -1;

            for (int k = 0; k < PCList.size() && found == -1; k++) {
                tmpname = PCList[k]->ReturnModel();

                if (tmpname == name) {
                    type = PCList[k]->ReturnType();
                    found = k;
                }
            }

            if (found == -1) {
                cout << "The PC model you specified isn't in the list\n";
                continue;
            }

            if (input.length() - i < 6) {
                cout << "Check the input format\n" << input.length() << ' ' << i << endl;
                continue;
            }

            if (input[i] != ' ' || input[i + 2] != ' ' || input[i + 4] != ' ') {
                cout << input[i] << '\n' << input[i + 2] << '\n' << input[i + 4] << '\n';
                cout << "All info must be split with spaces\n";
                continue;
            }

            cores = input[i + 1] - '0';
            ramslots = input[i + 3] - '0';
            i += 5;
            if ((cores % 2 != 0 && cores != 1) || cores < 1 || cores > 8) {
                cout << "Wrong cores\n";
                continue;
            }

            if (ramslots % 2 != 0 && ramslots != 1 || ramslots <= 0 || ramslots > 2 && type == "HomePC" || ramslots > 4 && type == "GamingPC" || ramslots > 8) {
                cout << "Wrong ramslots\n";
                continue;
            }

            for (i; i < input.length() && input[i] != ' '; i++)
                GBperRam = 10 * GBperRam + input[i] - '0';

            if (GBperRam < 2 || GBperRam > 128 || (GBperRam & (GBperRam - 1)) != 0) {
                cout << "GB/RAM need to be a power of 2, between 2 and 128\n";
                continue;
            }


            if (type == "HomePC") {
                if (i < (input.length()))
                    cout << "Unecessary information has been input, only enter CPU cores, RAM sticks, and GB/RAM\n";
                else
                    PCList[found]->upgrade(cores, ramslots, GBperRam, 0, 0);

            }

            else if (type == "GamingPC") {

                i++;
                if (i < input.length()) {
                    GPUcount = input[i] - '0';
                    i++;
                }
                else {
                    cout << "Further input required, specify the GPU number\n";
                    continue;
                }

                if (GPUcount < 0 || GPUcount > 2) {
                    cout << "The possible number of GPUs is between 0 (none) and 2\n";
                }
                else if (i < input.length()) {
                    cout << "Unecessary information has been input, only enter CPU cores, RAM sticks, GB/RAM and GPU number\n";
                }
                else {
                    PCList[found]->upgrade(cores, ramslots, GBperRam, GPUcount, 0);
                    cout << GPUcount << endl;
                }
            }
            else if (type == "WorkstationPC") {
                AfterErr = 0;
                i++;
                if (i < input.length()) {
                    GPUcount = input[i] - '0';
                    i++;
                }
                else {
                    cout << "Further input required, specify the GPU number and Afterburner\n";
                    continue;
                }


                if (GPUcount < 0 || GPUcount > 1) {
                    cout << "The possible number of GPUs is between 0 (none) and 1\n";
                    i++;
                }

                if (i < input.length()) {

                    if (input[i] != ' ')
                        cout << "Please ensure the input is formatted properly\n";

                    else {
                        i++;
                        if (i < input.length()) {
                            if (input[i] - '0' == 0 || input[i] - '0' == 1 && GPUcount == 1) {
                                Aftercount = input[i] - '0';
                                i++;
                            }
                            else {
                                cout << "You can either have 1 Afterburner card (only if you have a GPU), or none. \n";
                                AfterErr = 1;
                            }

                            if (i < input.length() && AfterErr == 0) {
                                if ((input[i] - '0') >= 0 && (input[i] - '0') <= 9 && AfterErr == 0)
                                    cout << "You can either have 1 Afterburner or none\n";
                                else
                                    cout << "Enter either 1 or 0 to specify whether you want an Afterburner or not\n";
                            }

                            if (i == input.length())
                                PCList[found]->upgrade(cores, ramslots, GBperRam, GPUcount, Aftercount);

                            else if (AfterErr == 0)
                                cout << "Unecessary information has been input, only enter CPU cores, RAM sticks, GB/RAM, GPU number and Afterburner\n";

                        }

                        else if (i == input.length())
                            cout << "Specify whether or not you want an Afterburner card (0 for no, 1 for yes)\n";

                    }

                }

                else
                    cout << "Further input is required, specify whether or not you need an Afterburner card\n";

            }

        }

        else if (opcode == "print") {
            if (i == (input.length() + 1)) {
                cout << "Please enter a PC type\n";
                continue;
            }
            for (i; i < input.length(); i++)
                type += input[i];

            if (type != "HomePC" && type != "GamingPC" && type != "WorkstationPC")
                cout << "Invalid type input\n";
            else
            {
                cout << endl;
                found = 0;
                for (int k = 0; k < PCList.size(); k++) {
                    tmpname = PCList[k]->ReturnType();
                    if (tmpname == type) {
                        PCList[k]->print();
                        cout << endl;
                        found = 1;
                    }
                }
                if (found == 0)
                    cout << "There is no model of the type that was specified in the list\n";

            }

        }

        else if (opcode == "delete") {
            if (i == (input.length() + 1)) {
                cout << "Please enter a PC type\n";
                continue;
            }
            for (i; i < input.length(); i++)
                name += input[i];

            found = 0;
            for (int k = 0; k < PCList.size(); k++) {
                tmpname = PCList[k]->ReturnModel();
                if (tmpname == name) {
                    delete PCList[k];
                    PCList.erase(PCList.begin() + k);
                    found = 1;
                    cout << k << " Found: \n";
                }
            }

            if (found == 0)
                cout << "The model you want to delete doesn't exist in the list\n";

        }
        else if (opcode == "compare") {
            FI = 0;
            SI = 0;
            tmpInfo = 0;
            string advantage = "  >  ";

            if (PCList.size() < 2) {
                cout << "There aren't enough PCs in the List for a comparison\n";
                continue;
            }

            if (i >= (input.length())) {
                cout << "Please enter 2 PC models to compare\n";
            }

            else {
                for (i; i < input.length() && input[i] != ' '; i++)
                    FirstComp += input[i];

                cout << FirstComp << endl;

                if (input[i] != ' ') {
                    cout << "Please enter the second name to compare\n";
                    continue;
                }

                else {
                    i++;
                    for (i; i < input.length(); i++)
                        SecondComp += input[i];

                    cout << SecondComp << endl;
                }

                found = 0;
                for (int k = 0; k < PCList.size() && found == 0; k++) {
                    tmpname = PCList[k]->ReturnModel();
                    if (FirstComp == tmpname) {
                        FI = k;
                        found = 1;
                    }
                }

                if (found == 0) {
                    cout << "The first PC name you entered was not in the list\n";
                    continue;
                }

                found = 0;
                for (int k = 0; k < PCList.size() && found == 0; k++) {
                    tmpname = PCList[k]->ReturnModel();
                    if (SecondComp == tmpname) {
                        SI = k;
                        found = 1;
                    }
                }

                if (found == 0) {
                    cout << "The second PC name you entered was not in the list\n";
                    continue;
                }

                cout << PCList[FI]->ReturnModel() << "  vs  " << PCList[SI]->ReturnModel() << endl;

                if (PCList[FI]->GetCpu() < PCList[SI]->GetCpu())
                    advantage = "  <  ";
                else if (PCList[FI]->GetCpu() == PCList[SI]->GetCpu())
                    advantage = "  =  ";

                cout << "CPU cores:  " << PCList[FI]->GetCpu() << advantage << PCList[SI]->GetCpu() << endl;

                advantage = "  >  ";

                if (PCList[FI]->GetTotalRam() < PCList[SI]->GetTotalRam())
                    advantage = "  <  ";
                else if (PCList[FI]->GetTotalRam() == PCList[SI]->GetTotalRam())
                    advantage = "  =  ";

                cout << "Total RAM:  " << PCList[FI]->GetTotalRam() << advantage << PCList[SI]->GetTotalRam() << endl;

                advantage = "  >  ";

                if (PCList[FI]->GetStorage() < PCList[SI]->GetStorage())
                    advantage = "  <  ";
                else if (PCList[FI]->GetStorage() == PCList[SI]->GetStorage())
                    advantage = "  =  ";

                cout << "Storage:  " << PCList[FI]->GetStorage() << advantage << PCList[SI]->GetStorage() << endl;

                advantage = "  >  ";

                type1 = PCList[FI]->ReturnType();
                type2 = PCList[SI]->ReturnType();

                if ((type1 == "GamingPC" || type1 == "WorkstationPC") && (type2 == "GamingPC" || type2 == "WorkstationPC")) {

                    if (PCList[FI]->GetGPU() < PCList[SI]->GetGPU())
                        advantage = "  <  ";
                    else if (PCList[FI]->GetGPU() == PCList[SI]->GetGPU())
                        advantage = "  =  ";

                    cout << "GPUs:  " << PCList[FI]->GetGPU() << advantage << PCList[SI]->GetGPU() << endl;

                    advantage = "  >  ";
                }

                if (type1 == "WorkstationPC" && type2 == "WorkstationPC") {

                    if (PCList[FI]->GetAfterburner() < PCList[SI]->GetAfterburner())
                        advantage = "  <  ";
                    else if (PCList[FI]->GetAfterburner() == PCList[SI]->GetAfterburner())
                        advantage = "  =  ";

                    cout << "Afterburner:  " << PCList[FI]->GetAfterburner() << advantage << PCList[SI]->GetAfterburner() << endl;

                    advantage = "  >  ";
                }

                if (PCList[FI]->GetCost() > PCList[SI]->GetCost())
                    advantage = "  <  ";
                else if (PCList[FI]->GetCost() == PCList[SI]->GetCost())
                    advantage = "  =  ";

                cout << "Cost:  " << PCList[FI]->GetCost() << advantage << PCList[SI]->GetCost() << endl;

            }

        }
        else
        cout << "Please enter a valid command\n";
    }

    for (int k = 0; k < PCList.size(); k++)
        delete PCList[k];

    delete yeet;
    return 0;
}
