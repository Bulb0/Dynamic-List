#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "PCs.h"

using namespace std;

#ifndef PCS_H
#define PCS_H


class Mamaboard {
protected:
    int ramSlots, pcieSlots;
public:

    Mamaboard();
    void setMamaboard(int a, int b);
    void printMamaboard();
};

class Rem {
protected:
    int totalRamSlots, gbPerRam, totalRam;
public:
    Rem();
    void setRem(int a, int b);
    int GetTotalRam() {
        return totalRam;
    }
    void printRem();
};

class PC {
protected:
    string model = "";
    string operatingSystem = "";
    Mamaboard Motherboard;
    int cpu = 0;
    Rem Ram;
    int ssd = 0;
    int cost = 0;
public:
    PC();
    string ReturnModel() {
        return model;
    }
    void setRam(int a, int b);

    int GetCpu() {
        return cpu;
    }

    int GetTotalRam() {
        return Ram.GetTotalRam();
    }

    int GetStorage() {
        return ssd;
    }

    int GetCost() {
        return cost;
    }

    virtual int GetGPU() = 0;
    virtual int GetAfterburner() = 0;
    virtual string ReturnType() = 0;
    virtual void print() = 0;
    virtual void upgrade(int, int, int, int, int) = 0;
};



class HomePC : public PC {
public:
    HomePC(string _model);
    void print();
    void upgrade(int _cpu, int ramstick, int gbram, int placeholder1, int placeholder2);

    string ReturnType() {
        return "HomePC";
    }

    int GetGPU() { return 0; }

    int GetAfterburner() { return 0; }

};

class GamingPC : public PC {
private:
    int GPU;
public:
    GamingPC(string _model);
    void print();

    void upgrade(int _cpu, int ramstick, int gbram, int _GPU, int placeholder);

    int GetGPU() {
        return GPU;
    }

    string ReturnType() {
        return "GamingPC";
    }

    int GetAfterburner() { return 0; }

};

class WorkstationPC : public PC {
private:
    int GPU, Afterburner;
public:
    WorkstationPC(string _model);
    void print();

    void upgrade(int _cpu, int ramstick, int gbram, int _GPU, int _Afterburner);

    int GetGPU() {
        return GPU;
    }

    int GetAfterburner() {
        return Afterburner;
    }

    string ReturnType() {
        return "WorkstationPC";
    }
};

#endif