//
//
//  1-D Kalman Filter
//
//  Created by Gautam Sharma on 11/10/19.
//  Copyright © 2019 Gautam Sharma. All rights reserved.
//



#include <iostream>
#include <math.h>
#include<vector>
using namespace std;

double new_mean, new_var;


struct kalman{
public:
    double mean1, var1, mean2,var2;
    kalman():mean1(1), var1(1), mean2(2), var2(2){}
    kalman(double a, double b, double c, double d):mean1(a), var1(b), mean2(c), var2(d){}
    friend vector<double> measurement_update(kalman A);
    friend vector<double> state_prediction(kalman A);
    
    
};
vector<double> measurement_update(kalman A){
    vector<double> mu;
    double mean1=A.mean1;
    double mean2=A.mean2;
    double var1= A.var1;
    double var2= A.var2;
    
    new_mean = (var2 * mean1 + var1 * mean2) / (var1 + var2);
    new_var = 1 / (1 / var1 + 1 / var2);
    mu.push_back(new_mean);
    mu.push_back(new_var);
    return mu;
    
}

vector<double> state_prediction(kalman A)
{
    vector<double> sp;
    double mean1=A.mean1;
    double mean2=A.mean2;
    double var1= A.var1;
    double var2= A.var2;
    
    new_mean = mean1 + mean2;
    new_var = var1 + var2;
    sp.push_back(new_mean);
    sp.push_back(new_var);
    
    return sp;
}

int main()
{
    //Measurements and measurement variance
    double measurements[5] = { 5, 6, 7, 9, 10 };
    double measurement_sig = 4;
    vector<double> a;
    vector<double> b;
    
    
    
    //Motions and motion variance
    double motion[5] = { 1, 1, 2, 1, 1 };
    double motion_sig = 2;
    
    //Initial state
    double mu = 0;
    double sig = 1000;
    
    for (int i = 0; i < sizeof(measurements) / sizeof(measurements[0]); i++) {
        a = measurement_update(kalman(mu,sig,measurements[i],4));
        printf("update:  [%f, %f]\n", a[0], a[1]);
        mu=a[0];
        sig=a[1];
        b = state_prediction(kalman(mu,sig,motion[i],2));
        printf("predict:  [%f, %f]\n", b[0], b[1]);
        
        mu=b[0];
        sig=b[1];
    }
    
    return 0;
}
