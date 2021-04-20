/******************************************************
** Program: moments.cpp
** Author: Rachel Villarreal
** Date: 4/20/2021
** Description: this program solves for the maximum moment 
                along a bridge and reports the max moment, 
                for a given k value 
** Input: input a k value that is within bounds of equation
** Output: prints out maximum moment, corresponding x value, 
           support reaction value, and k that was used
******************************************************/

#include <iostream>
#include <fstream>

using namespace std;

//functions that will solve for different subcases

//function that will solve for the deadload
float dead_func(float x, float L){
    float qtot = 0.15;
    float dead_m = -(qtot * (x * x)) / 2 + ((qtot * L * x)) / 2;
    return dead_m;
}

//function solving for case 1, prints out the max moment
void case1(float L, float d1, float k, float p1){

    //creating output file to store moment information, appending it
    ofstream output;
    output.open ("output_case1.txt", ios::out | ios::app);

    if (output.is_open()) {
        //cout << "File successfully opened " << endl;
    }
//case 1 pass in d1, 
    float dead_m = 0.00,
    live_m = 0.00,    
    max = 0.00,
    tot_m = 0.00,
    x = 0.00;

    //calculation of Al
    float Al = 0.00;
    Al = (p1 * (L - k)) / L;
    //Al = 8.935;

    //calculation of dead shear
    float Vd = 0.15 * (L/2);

    //where i is the distance along the bridge
    for (float i = 0.10; i < k; i = i + 0.1){

        //calculation dead load
        dead_m = dead_func(i, L);
        //cout << "Dead moment is equal to for " << i << " : " << dead_m << endl;

        //calculation live load
        //if (i < k){
        live_m = Al * i;
        // }
        // else {
        //     live_m = (Al * i) - (p1 * (i - k));
        // }

        tot_m = dead_m + live_m;

        //check if max moment has been calculated (if it's greater than previous moment)
        if (max == 0.00){
            max = tot_m;
            x = i;
        }
        else if (tot_m > max){
            max = tot_m;
            x = i;
        }
    }

    for (float i = 15.4; i < L; i = i + 0.1){
        dead_m = dead_func(i, L);

        live_m = (Al * i) - (p1 * (i - k));

        tot_m = dead_m + live_m;

        //check if max moment has been calculated (if it's greater than previous moment)
        if (max == 0.00){
            max = tot_m;
            x = i;
        }
        else if (tot_m > max){
            max = tot_m;
            x = i;
        }
    }

    float tot_shear = Al + Vd;

    output << k; 
    output << '\t';
    output << x ;
    output << '\t';
    output << max ;
    output << '\t';
    output << tot_shear;
    output << '\n';
 
    output.close();
}

//case 2 
//function solving for case 1, prints out the max moment
void case2(float L, float d1, float d2, float k, float p1, float p2){

    //creating output file to store moment information, truncating it
    ofstream output;
    output.open ("output_case2.txt", ios::out | ios::app);

    if (output.is_open()) {
        //cout << "File successfully opened " << endl;
    }

    float dead_m = 0.00,
    live_m = 0.00,    
    max = 0.00,
    tot_m = 0.00,
    x = 0.00;

    //calculation of Al
    float Al = 0.00;
    Al = ((p1 * (L - k)) + (p2 * (L - (k - d1))))/ L;
    //Al = 8.935;

    //calculation of dead shear
    float Vd = 0.15 * (L/2);

    //where i is the distance along the bridge
    for (float i = 0.10; i < (k - d1); i = i + 0.1){

        //calculation dead load
        dead_m = dead_func(i, L);

        //calculation live load
        live_m = Al * i;

        tot_m = dead_m + live_m;

        //check if max moment has been calculated (if it's greater than previous moment)
        if (max == 0.00){
            max = tot_m;
            x = i;
        }
        else if (tot_m > max){
            max = tot_m;
            x = i;
        }
    }

    for (float i = (k - d1); i < k; i = i + 0.1){
        dead_m = dead_func(i, L);

        live_m = (Al * i) - (p2 * (i - (k - d1)));

        tot_m = dead_m + live_m;

        //check if max moment has been calculated (if it's greater than previous moment)
        if (max == 0.00){
            max = tot_m;
            x = i;
        }
        else if (tot_m > max){
            max = tot_m;
            x = i;
        }
    }

    for (float i = k; i < L; i = i + 0.1){
        dead_m = dead_func(i, L);

        live_m = (Al * i) - (p2 * (i - (k - d1))) - (p1 * (i - k));

        tot_m = dead_m + live_m;

        //check if max moment has been calculated (if it's greater than previous moment)
        if (max == 0.00){
            max = tot_m;
            x = i;
        }
        else if (tot_m > max){
            max = tot_m;
            x = i;
        }
    }

    float tot_shear = Al + Vd;

    output << k; 
    output << '\t';
    output << x ;
    output << '\t';
    output << max ;
    output << '\t';
    output << tot_shear;
    output << '\n';

    output.close();
}


int main(){

    cout << "hello" << endl;

    //setting parameters of truck, in feet
    float d1 = 15.4;
    float d2 = 20.0;
    float d3 = 51.4;
    float f4 = 56.0;

    //loads on each tire (in kips)
    float p1 = 6.0;
    float p2 = 8.5;
    float p3 = 8.5;
    float p4 = 8.5;
    float p5 = 8.5;

    //length of bridge 
    float L = 40.0;

    //case1
    for (float k = 0.1; k < d1; k = k + 0.1){
        case1(L, d1, k, p1);
    }

    for (float k = d1; k < (d1 + d2); k = k + 0.1){
        case2(L, d1, d2, k, p1, p2);
    }

    return 0;
}
