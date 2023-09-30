declare id 		"collison";
declare name            "Collision Drive";
declare category        "Distortion";
declare samplerate "96000";

import("stdfaust.lib");

/*******************************************************************************
  * 1-dimensional function table for linear interpolation
*******************************************************************************/
rd = library("reducemaps.lib");

//-- Rdtable from waveform
rtable(table, r) = (table, int(r)):rdtable;

//-- Copy the sign of x to f
ccopysign(f, x) = ma.fabs(f) * sign(x);

//-- Get sign of value x
sign(x) = x<0, 1, -1 : select2;

//-- Check if value x is negative
fsignbit(x) = x<0;

//-- Get fractal part of value n
fractal(n) = n - int(n);

//-- Interpolate value between i and i+1 in table with fractal coefficient f.
interpolation(table, size, f, i) = select2(i<0,select2(i>size-2,
    rtable(table, i)*(1-f) + rtable(table,i+1)*f, rtable(table, size-1)),
    rtable(table, 0)) ;

//-- Linear interpolation for value x in rdtable
circuit_response(table, low, high, step, size, x) =
    interpolation(table, size, fractal(linindex(step, x)),
    int(linindex(step, x))), x : ccopysign;

//-- Calculate linear table index for value x
linindex(step, x) = ma.fabs(x) * step;

//-- table response for the Collison Drive Clipping Amp section
collison_drive_clip = circuit_response(collison_drive_table, low, high, step, size) with {

    low = 0;
    high =0.970874;
    step =101.97;
    size =100;

    collison_drive_table = waveform {
        0.0,-0.0296990148227,-0.0599780676992,-0.0908231643281,-0.122163239629,
        -0.15376009788,-0.184938007182,-0.214177260107,-0.239335434213,-0.259232575019,
        -0.274433909887,-0.286183308354,-0.29553854444,-0.303222323477,-0.309706249977,
        -0.315301338712,-0.320218440785,-0.324604982281,-0.328567120703,-0.332183356975,
        -0.335513124719,-0.33860236542,-0.34148724693,-0.344196707008,-0.346754233717,
        -0.34917913798,-0.351487480543,-0.35369275887,-0.355806424152,-0.357838275995,
        -0.359796767655,-0.361689244919,-0.363522135105,-0.365301098113,-0.367031148289,
        -0.368716753588,-0.370361916943,-0.371970243537,-0.373544996828,-0.375089145544,
        -0.376605403346,-0.378096262548,-0.379564022938,-0.381010816596,-0.382438629377,
        -0.383849319643,-0.385244634694,-0.386626225283,-0.387995658543,-0.389354429565,
        -0.39070397188,-0.392045667012,-0.393380853288,-0.39471083403,-0.396036885269,
        -0.397360263098,-0.398682210753,-0.400003965547,-0.401326765733,-0.402651857394,
        -0.403980501471,-0.405313980999,-0.406653608692,-0.40800073496,-0.409356756504,
        -0.410723125631,-0.412101360439,-0.413493056085,-0.414899897347,-0.416323672745,
        -0.417766290556,-0.419229797097,-0.420716397759,-0.422228481377,-0.423768648654,
        -0.425339745558,-0.426944902828,-0.428587583057,-0.430271637224,-0.432001373102,
        -0.433781638746,-0.435617925286,-0.437516494692,-0.439484540257,-0.441530390423,
        -0.443663770898,-0.445896146322,-0.448241172434,-0.450715304661,-0.453338632988,
        -0.45613605235,-0.45913894467,-0.46238766699,-0.465935359011,-0.469854010456,
        -0.474244617411,-0.479255257451,-0.48511588606,-0.492212726244,-0.501272723631
    };
};


/*
** Noisegate of the Collision Drive
*/

noiseGate = _ <: _*((((abs(_) : si.smoo) < tLinear) : si.smooth(pole)) ) : v1 with{
    threshold = hslider("Gate[name:Gate]", -15, -30, -10, 1);
    tLinear = threshold : ba.db2linear;
    pole = 0.001 : ba.tau2pole; // att
    v1(x) = attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -0, +1));
    envelop = abs : max ~ (1.0/ma.SR) : rd.maxn(4096) ;
};

/*
** Input buffer based on a circuit diagram of the Collision Drive
*/

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    b0 = 4.25021404100375e-10*pow(fs,2);

    b1 = -8.50042808200749e-10*pow(fs,2);

    b2 = 4.25021404100375e-10*pow(fs,2);

    a0 = fs*(4.33044799014014e-10*fs + 4.71597371213838e-8) + 1.11568988593319e-6;

    a1 = -8.66089598028028e-10*pow(fs,2) + 2.23137977186639e-6;

    a2 = fs*(4.33044799014014e-10*fs - 4.71597371213838e-8) + 1.11568988593319e-6;
};

/*
** Capacitor selector of the Collision Drive
*/

capset = (table, int(p)):rdtable * 1e-6 with {
    table = waveform { 
        0.47, 0.22, 0.1, 0.047, 0.022, 0.01
    };
    p = hslider("attack[name:Attack]", 3, 0, 5, 1); 
};

/*
** Clipping amp based on a circuit diagram of the Collision Drive
*/

p2 = ts9 with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    R1 = 1000;
    R2 = 10000 + 500000 * (hslider("drive[name:Drive]", 0.1, 0, 1, 0.01) : LogPot(3));
    C = capset;
    a1 = (R1 + R2) * C * 2 * ma.SR;
    a2 = R1 * C * 2 * ma.SR;
    B0 = (1 + a1) / (1 + a2);
    B1 = (1 - a1) / (1 + a2);
    A1 = (1 - a2) / (1 + a2);
    X2 = fi.tf1(B0, B1, A1);
    ts9nonlin = ffunction(float ts9nonlin(float), "ts9nonlin.h", "");
    ts9 = _ <: _ - ts9nonlin(X2-_) :> _;
    //ts9 = _ <: _ - collison_drive_clip(X2-_) :> _;
};

/*
** Tone Control section based on a circuit diagram of the Collision Drive
*/

p3 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    Bright = vslider("Bright[name:Bright][style:knob]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);

    b0 = Bright*(-3.04435668052817e-6*Bright*fs + 5.41895489134013e-6*fs) + 1.33951693943239e-7*fs + 0.00138379849114917;

    b1 = 0.00276759698229833;

    b2 = Bright*(3.04435668052817e-6*Bright*fs - 5.41895489134013e-6*fs) - 1.33951693943239e-7*fs + 0.00138379849114917;

    a0 = Bright*(Bright*fs*(-1.33953035705602e-9*fs - 3.34882589264005e-6) + fs*(1.33954082280245e-9*fs + 2.73997462198066e-6)) + fs*(5.89397962033077e-11*fs + 1.3651141432266e-6) + 0.00152220825269361;

    a1 = Bright*(2.67906071411204e-9*Bright*pow(fs,2) - 2.6790816456049e-9*pow(fs,2)) - 1.17879592406615e-10*pow(fs,2) + 0.00304441650538723;

    a2 = Bright*(Bright*fs*(-1.33953035705602e-9*fs + 3.34882589264005e-6) + fs*(1.33954082280245e-9*fs - 2.73997462198066e-6)) + fs*(5.89397962033077e-11*fs - 1.3651141432266e-6) + 0.00152220825269361;
};

/*
** Volume Control section based on a circuit diagram of the Collision Drive
*/

p4 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    Volume = vslider("Level[name:Level][style:knob]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(3) : si.smooth(s);

    b0 = 3.59629027188009e-10*Volume*pow(fs,2);

    b1 = -7.19258054376018e-10*Volume*pow(fs,2);

    b2 = 3.59629027188009e-10*Volume*pow(fs,2);

    a0 = Volume*(Volume*fs*(-9.64298428951757e-11*fs - 4.15286911498117e-7) + fs*(9.64298428951757e-11*fs + 4.15286911498117e-7)) + fs*(3.6890696017522e-10*fs + 1.86049349697801e-6) + 0.000207643455749058;

    a1 = Volume*(1.92859685790351e-10*Volume*pow(fs,2) - 1.92859685790351e-10*pow(fs,2)) - 7.37813920350441e-10*pow(fs,2) + 0.000415286911498117;

    a2 = Volume*(Volume*fs*(-9.64298428951757e-11*fs + 4.15286911498117e-7) + fs*(9.64298428951757e-11*fs - 4.15286911498117e-7)) + fs*(3.6890696017522e-10*fs - 1.86049349697801e-6) + 0.000207643455749058;
};


process = noiseGate : p1 : p2 : p3 : *(gain) with {
    gain = hslider("level[name:Level]", -10, -20, 4, 0.1) : ba.db2linear : si.smooth(0.993);
};
