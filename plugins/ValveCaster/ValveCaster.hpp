


#ifndef VALVECASTER_H
#define VALVECASTER_H

#include <cmath>
#include <algorithm>
#include <functional>

#define FAUSTFLOAT float

namespace valvecaster {

class Dsp {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst17;
	double fConst18;
	double fConst19;
	double fRec3[2];
	double fRec1[4];
	double fConst20;

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
