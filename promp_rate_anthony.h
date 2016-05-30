float Pe(float Pt, float absEta, int mode){
    if(Pt<30.000000){
        if(absEta<0.800000) return 0.904799  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.868321  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.883462  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.892005  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<40.000000){
        if(absEta<0.800000) return 0.924966  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.880199  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.903364  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.877666  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<50.000000){
        if(absEta<0.800000) return 0.940479  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.900445  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.915915  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.898341  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<60.000000){
        if(absEta<0.800000) return 0.947354  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.920733  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.941403  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.922677  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<80.000000){
        if(absEta<0.800000) return 0.956715  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.918299  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.918403  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.941729  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<100.000000){
        if(absEta<0.800000) return 0.946819  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.908460  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.953202  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.946667  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else if(Pt<150.000000){
        if(absEta<0.800000) return 0.975217  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.896552  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.935294  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.888889  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
    else{
        if(absEta<0.800000) return 0.964758  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<1.444200) return 0.957143  + uPe(Pt, absEta)*peModeBehavior(mode);
        else if(absEta<2.100000) return 0.970000  + uPe(Pt, absEta)*peModeBehavior(mode);
        else return 0.940000  + uPe(Pt, absEta)*peModeBehavior(mode);
    }
}
float uPe(float Pt, float absEta){
    if(Pt<30.000000){
        if(absEta<0.800000) return 0.008926;
        else if(absEta<1.444200) return 0.013539;
        else if(absEta<2.100000) return 0.012900;
        else return 0.064147;
    }
    else if(Pt<40.000000){
        if(absEta<0.800000) return 0.003334;
        else if(absEta<1.444200) return 0.005825;
        else if(absEta<2.100000) return 0.020818;
        else return 0.006960;
    }
    else if(Pt<50.000000){
        if(absEta<0.800000) return 0.002001;
        else if(absEta<1.444200) return 0.002769;
        else if(absEta<2.100000) return 0.003531;
        else return 0.012525;
    }
    else if(Pt<60.000000){
        if(absEta<0.800000) return 0.003884;
        else if(absEta<1.444200) return 0.007230;
        else if(absEta<2.100000) return 0.015422;
        else return 0.014767;
    }
    else if(Pt<80.000000){
        if(absEta<0.800000) return 0.010980;
        else if(absEta<1.444200) return 0.018304;
        else if(absEta<2.100000) return 0.060879;
        else return 0.009564;
    }
    else if(Pt<100.000000){
        if(absEta<0.800000) return 0.042121;
        else if(absEta<1.444200) return 0.049181;
        else if(absEta<2.100000) return 0.009991;
        else return 0.024562;
    }
    else if(Pt<150.000000){
        if(absEta<0.800000) return 0.005337;
        else if(absEta<1.444200) return 0.013091;
        else if(absEta<2.100000) return 0.017647;
        else return 0.053761;
    }
    else{
        if(absEta<0.800000) return 0.011807;
        else if(absEta<1.444200) return 0.023170;
        else if(absEta<2.100000) return 0.03;
        else return 0.06;
    }
}
float Pm(float Pt, float absEta, int mode){
    if(Pt<30.000000){
        if(absEta<0.800000) return 0.958081 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.960073 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.971033 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.954809 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<40.000000){
        if(absEta<0.800000) return 0.970955 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.967389 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.979291 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.962660 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<50.000000){
        if(absEta<0.800000) return 0.976354 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.971111 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.982277 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.960435 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<60.000000){
        if(absEta<0.800000) return 0.974804 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.972770 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.986269 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.965223 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<80.000000){
        if(absEta<0.800000) return 0.982996 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.970852 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.983232 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.971345 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<100.000000){
        if(absEta<0.800000) return 0.979828 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.978470 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.985826 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.974576 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else if(Pt<150.000000){
        if(absEta<0.800000) return 0.980960 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.968444 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.976879 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.978873 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
    else{
        if(absEta<0.800000) return 0.964706 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<1.444200) return 0.961832 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else if(absEta<2.100000) return 0.969325 + uPm(Pt, absEta)*pmModeBehavior(mode);
        else return 0.833333 + uPm(Pt, absEta)*pmModeBehavior(mode);
    }
}
float uPm(float Pt, float absEta){
    if(Pt<30.000000){
        if(absEta<0.800000) return 0.001714;
        else if(absEta<1.444200) return 0.002071;
        else if(absEta<2.100000) return 0.001965;
        else return 0.004038;
    }
    else if(Pt<40.000000){
        if(absEta<0.800000) return 0.001763;
        else if(absEta<1.444200) return 0.002075;
        else if(absEta<2.100000) return 0.002686;
        else return 0.018334;
    }
    else if(Pt<50.000000){
        if(absEta<0.800000) return 0.004519;
        else if(absEta<1.444200) return 0.003354;
        else if(absEta<2.100000) return 0.003218;
        else return 0.005417;
    }
    else if(Pt<60.000000){
        if(absEta<0.800000) return 0.005505;
        else if(absEta<1.444200) return 0.003146;
        else if(absEta<2.100000) return 0.004956;
        else return 0.025827;
    }
    else if(Pt<80.000000){
        if(absEta<0.800000) return 0.003082;
        else if(absEta<1.444200) return 0.005421;
        else if(absEta<2.100000) return 0.011008;
        else return 0.004393;
    }
    else if(Pt<100.000000){
        if(absEta<0.800000) return 0.002662;
        else if(absEta<1.444200) return 0.003380;
        else if(absEta<2.100000) return 0.003102;
        else return 0.008153;
    }
    else if(Pt<150.000000){
        if(absEta<0.800000) return 0.003700;
        else if(absEta<1.444200) return 0.005585;
        else if(absEta<2.100000) return 0.005581;
        else return 0.011813;
    }
    else{
        if(absEta<0.800000) return 0.008635;
        else if(absEta<1.444200) return 0.011385;
        else if(absEta<2.100000) return 0.013092;
        else return 0.063394;
    }
}