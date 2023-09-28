// generated from file 'metaltone_dist.dsp' by dsp2cc:
// Code generated with Faust 2.37.3 (https://faust.grame.fr)

#include "MetalTone_dist.hpp"

#include "metalzone_p2_table.h"

namespace metaltone_dist {

Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) lowpass_fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) lowpass_fRec0[l1] = 0.0;
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	int upcount = smp.max_out_count(count);
	FAUSTFLOAT buf[upcount];
	memset(buf, 0, upcount*sizeof(float));
	int ReCount = smp.up(count, input0, buf);
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		iVec0[0] = 1;
		fRec0[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec0[1]);
		buf[i0] = FAUSTFLOAT(double(metalzone_p2clip(double((double(buf[i0]) + fRec0[0])))));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
	}
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		lowpass_fRec1[0] = (double(buf[i0]) - ((1.7383024478502873 * lowpass_fRec1[1]) + (0.75793715340193646 * lowpass_fRec1[2])));
		lowpass_fRec0[0] = (((1.7481198006261118 * lowpass_fRec1[1]) + (0.87405990031305592 * (lowpass_fRec1[0] + lowpass_fRec1[2]))) - ((1.8709501296525741 * lowpass_fRec0[1]) + (0.89208313498371072 * lowpass_fRec0[2])));
		buf[i0] = FAUSTFLOAT(((1.8815166323181425 * lowpass_fRec0[1]) + (0.94075831615907124 * (lowpass_fRec0[0] + lowpass_fRec0[2]))));
		lowpass_fRec1[2] = lowpass_fRec1[1];
		lowpass_fRec1[1] = lowpass_fRec1[0];
		lowpass_fRec0[2] = lowpass_fRec0[1];
		lowpass_fRec0[1] = lowpass_fRec0[0];
	}
	smp.down(buf, output0);
}


void Dsp::connect(uint32_t port, float data)
{
	switch (port)
	{
	default:
		break;
	}
    (void) data;
}

Dsp *plugin() {
	return new Dsp();
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}
} // end namespace metaltone_dist
