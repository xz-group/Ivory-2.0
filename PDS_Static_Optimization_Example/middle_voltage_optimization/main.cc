#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <dlfcn.h> /* to load libraries*/
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "static_buck.h"
#include "static_switched_capacitor.h"
#include "PDS_efficiency.h"




using namespace std;

// An example to calcuate static efficiency of multiple stage power delivery system
// Here we use a two stage power delivery system as an example
// First stage is a buck voltage regulator, the second stage has three buck voltage regulators

int main()
{

float mid_voltage_start = 1.1;
float mid_voltage_end = 2.1;

vector<float> total_loss;
vector<float> mid_voltage;

for(float voltage = mid_voltage_start; voltage<=mid_voltage_end; voltage = voltage + 0.1)
{
total_loss.push_back(PDS_efficiency_mid_voltage(voltage));
mid_voltage.push_back(voltage);
}


for(int i=0;i<total_loss.size();i++)
{
cout << "middle voltage: " << mid_voltage[i] << "; total PDS loss: " << total_loss[i] << endl;
}

return 0;
}
