

#ifndef METALTONE_DIST_H
#define METALTONE_DIST_H

#include <cmath>
#include <algorithm>

#include "gx_resampler.h"

#define FAUSTFLOAT float

namespace metaltone_dist {


class Dsp {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	int iVec0[2];
	double fRec0[2];

	double lowpass_fRec1[3];
	double lowpass_fRec0[3];

public:
	void connect(uint32_t port, float data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	Dsp();
	~Dsp();
};

} // end namespace metaltone_dist

#endif
