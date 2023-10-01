

#ifndef RUMOR_H
#define RUMOR_H

#include <cmath>
#include <algorithm>
#include <functional>

#include "gx_resampler.h"

#define FAUSTFLOAT float

namespace rumor {

class Dsp {
private:
#ifndef _MOD_DEVICE_DUO
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
#endif
	uint32_t fSampleRate;
	int iVec0[2];
	double fRec7[2];
	double fRec5[2];
	double fRec3[2];
	double fRec1[2];
	double fRec9[2];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec11[2];
	double fConst3;
	double fConst5;
	double fVec1[3];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fRec10[3];
	double fRec0[2];
	FAUSTFLOAT fHslider0;
	double fRec12[2];

#ifndef _MOD_DEVICE_DUO
	double lowpass_fRec1[3];
	double lowpass_fRec0[3];
#endif

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
