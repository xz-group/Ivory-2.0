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
#include "static_buck.h"
#include "static_switched_capacitor.h"




using namespace std;

// An example to calcuate static efficiency of multiple stage power delivery system
// Here we use a two stage power delivery system as an example
// First stage is a buck voltage regulator, the second stage has three buck voltage regulators

float PDS_efficiency_mid_voltage(float middle_voltage)
{


    int first_stage_vr_num = 1;
    int second_stage_vr_num = 3;

    float total_loss = 0;

    //float middle_voltage = 2.0;

    float first_stage_PDN_loss = 0;
    float second_stage_PDN_loss = 0;
    float first_stage_vr_loss = 0;
    float second_stage_vr_loss[3] = {0,0,0};

    float first_stage_PDN_parasitics = 0.001;
    float second_stage_PDN_parasitics[3] = {0.001, 0.0012, 0.0015};

    float input_voltge = 5.0;

    float load_current[3] = {1.0, 0.8, 0.6};
    float load_voltage[3] = {0.8, 0.9, 1.0};

    float conversion_ratio[3];

    float first_stage_current = 0;
    float second_stage_current[3];


    for(int i=0; i<second_stage_vr_num; i++)
    {
        conversion_ratio[i] = load_voltage[i]/middle_voltage;
    }

    for(int i=0; i<second_stage_vr_num; i++)
    {
        second_stage_current[i] = load_current[i];
    }

    for(int i=0; i<second_stage_vr_num; i++)
    {
        first_stage_current = first_stage_current + load_current[i]*conversion_ratio[i];
    }


    //Calcuate power loss

    //Calcuate first stage power loss
    first_stage_PDN_loss = first_stage_current*first_stage_current*first_stage_PDN_parasitics;

    //Calcuate second stage power loss
    for(int i=0; i<second_stage_vr_num; i++)
    {
        second_stage_PDN_loss = second_stage_PDN_loss + second_stage_current[i]*second_stage_current[i]*second_stage_PDN_parasitics[i];
    }

    //float Static_Buck(int technology, double Vin, double Vout, double P, double Area_buget, double ripple, double Efficiency_buget, int Optimization_Target)
    for(int i=0; i<second_stage_vr_num; i++)
    {
    second_stage_vr_loss[i] = load_current[i] * load_voltage[i] / Static_Buck(1, middle_voltage, load_voltage[i], load_voltage[i]*load_current[i], 50, 0.01, 0.8, 0) - load_current[i] * load_voltage[i];
    cout << "second_stage_vr_loss[i]: " << second_stage_vr_loss[i] << endl;
    }

    //load for first stage voltage regulators
    float first_stage_vr_load = first_stage_PDN_loss + second_stage_PDN_loss;
    for(int i=0; i<second_stage_vr_num; i++)
    {
    first_stage_vr_load = first_stage_vr_load + load_current[i] * load_voltage[i] + second_stage_vr_loss[i];
    }

    first_stage_vr_loss = first_stage_vr_load / Static_Buck(0, input_voltge, middle_voltage, first_stage_vr_load, 200, 0.01, 0.8, 0) - first_stage_vr_load;


    total_loss = total_loss + first_stage_PDN_loss;
    cout << "first_stage_PDN_loss: " << first_stage_PDN_loss << endl;
    for(int i=0; i<second_stage_vr_num; i++)
    {
      cout << "second_stage_vr_loss[i]: " << second_stage_vr_loss[i] << endl;
      total_loss = total_loss + second_stage_vr_loss[i];
    }
    cout << "second_stage_PDN_loss: " << second_stage_PDN_loss << endl;
    total_loss = total_loss + second_stage_PDN_loss;
    cout << "first_stage_vr_loss: " << first_stage_vr_loss << endl;
    total_loss = total_loss + first_stage_vr_loss;

    return total_loss;
}
