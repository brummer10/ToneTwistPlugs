

#ifndef TUBESCREAMER_H
#define TUBESCREAMER_H

#include <cmath>
#include <algorithm>
#include <functional>

namespace tubescreamer {

class Dsp {
private:
	uint32_t fSamplingFreq;
	float 	fslider0;
	double 	fRec0[2];
    float 	fslider1;
	int32_t 	iConst0;
	double 	fConst1;
	double 	fVec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	float 	fslider2;
	double 	fConst5;
	double 	fConst6;
	double 	fRec2[2];
	double 	fVec1[2];
	double 	fRec1[2];
public:
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void del_instance(Dsp *p);
	void compute(uint32_t count, float *input0, float *output0);
    void connect(uint32_t port, float data);
	Dsp();
	~Dsp();
};

}

#endif
