#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "PCs.h"

Mamaboard::Mamaboard() {
    ramSlots = 0;
    pcieSlots = 0;
}

void Mamaboard::setMamaboard(int a, int b) {
    ramSlots = a;
    pcieSlots = b;
}

void Mamaboard::printMamaboard() {
    cout << "RAM slots: " << ramSlots << " pcieSlots: " << pcieSlots << endl;
}

Rem::Rem() {
totalRamSlots = 0;
gbPerRam = 0;
totalRam = 0;
}

void Rem::setRem(int a, int b) {
    totalRamSlots = a;
    gbPerRam = b;
    totalRam = a * b;
}

void Rem::printRem() {
    cout << "RAM sticks and GB/stick: " << totalRamSlots << ',' << gbPerRam << endl;
}

PC::PC() {}

void PC::setRam(int a, int b) {
    Ram.setRem(a, b);
}

HomePC::HomePC(string _model){

    model = _model;
    operatingSystem = "MacOS";
    cpu = 2;
    Motherboard.setMamaboard(2, 0);
    Ram.setRem(1, 4);
    ssd = 256;
    cost = 800;

}

void HomePC::print() {
    cout << model << '\n' << operatingSystem << "\nCPU cores: " << cpu << endl;
    Motherboard.printMamaboard();
    Ram.printRem();
    cout << "Storage: " << ssd << "GB\ncost: " << cost << endl;
}

void HomePC::upgrade(int _cpu, int ramstick, int gbram, int placeholder1, int placeholder2) {
    cpu = _cpu;
    Ram.setRem(ramstick, gbram);
}

GamingPC::GamingPC(string _model) {
    model = _model;
    operatingSystem = "Windows";
    cpu = 6;
    Motherboard.setMamaboard(4, 2);
    Ram.setRem(2, 8);
    ssd = 1024;
    cost = 1300;
    GPU = 1;
}

void GamingPC::print() {
    cout << model << '\n' << operatingSystem << "\nCPU cores: " << cpu << endl;
    Motherboard.printMamaboard();
    Ram.printRem();
    cout << "GPUs: " << GPU << "\nStorage: " << ssd << "GB\ncost: " << cost << endl;
}

void GamingPC::upgrade(int _cpu, int ramstick, int gbram, int _GPU, int placeholder) {
    cpu = _cpu;
    Ram.setRem(ramstick, gbram);
    GPU = _GPU;
}

WorkstationPC::WorkstationPC(string _model) {
    model = _model;
    operatingSystem = "Linux";
    cpu = 6;
    Motherboard.setMamaboard(8, 1);
    Ram.setRem(4, 16);
    ssd = 2048;
    cost = 1600;
    GPU = 0;
    Afterburner = 0;
}

void WorkstationPC::print() {
    cout << model << '\n' << operatingSystem << "\nCPU cores: " << cpu << endl;
    Motherboard.printMamaboard();
    Ram.printRem();
    cout << "GPUs: " << GPU << "\nStorage: " << ssd << "GB\nAfterburner: " << Afterburner << "\ncost: " << cost << endl;
}

void WorkstationPC::upgrade(int _cpu, int ramstick, int gbram, int _GPU, int _Afterburner) {
    cpu = _cpu;
    Ram.setRem(ramstick, gbram);
    GPU = _GPU;
    Afterburner = _Afterburner;
}
