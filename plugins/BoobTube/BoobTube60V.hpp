
#ifndef BOOBTUBE60V_H
#define BOOBTUBE60V_H

#include <cmath>
#include <algorithm>
#include <functional>

#define FAUSTFLOAT float

namespace boobtube60v {

class Dsp {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst7;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst27;
	double fRec2[4];
	double fConst29;
	double fConst31;
	double fConst32;
	double fConst33;
	FAUSTFLOAT fVslider1;
	double fRec3[2];
	double fConst34;
	double fRec1[5];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];

public:
	void connect(uint32_t port, float data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	Dsp();
	~Dsp();
};

}

#endif

