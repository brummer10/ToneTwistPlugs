


#ifndef VALVECASTERBOOSTER_H
#define VALVECASTERBOOSTER_H

#include <cmath>
#include <algorithm>
#include <functional>

#define FAUSTFLOAT float

namespace valvecasterbooster {

class Dsp {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec0[3];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	double 	fConst7;

public:
	void connect(uint32_t port, float data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	void del_instance(Dsp *p);
	Dsp();
	~Dsp();
};

}

#endif

