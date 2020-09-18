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

float total_area = 200;

vector<float> total_loss;
vector<float> ivr_1_area;
vector<float> ivr_2_area;
vector<float> ivr_3_area;

for(float area1 = 20; area1<total_area; area1 = area1 + 20)
{
    for(float area2 = 20; area2<total_area; area2 = area2 + 20)
    {
        float area3 = total_area - area1 - area2;
        if(area3 > 0)
        {
          float area[3] = {area1,area2,area3};
          total_loss.push_back(PDS_efficiency_ivr_area(area));
          ivr_1_area.push_back(area1);
          ivr_2_area.push_back(area2);
          ivr_3_area.push_back(area3);
        }
    }

}


for(int i=0;i<total_loss.size();i++)
{
cout << "IVR areas: " << ivr_1_area[i] << ";" << ivr_2_area[i] << ";" << ivr_3_area[i] << "; total PDS loss: " << total_loss[i] << endl;
}

return 0;
}
