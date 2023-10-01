// generated from file 'rumor.dsp' by dsp2cc:
// Code generated with Faust 2.37.3 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>


using std::signbit;

#include "Rumor.hpp"

#include "rumor_table.h"

namespace rumor {

Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec7[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec3[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec9[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec11[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec10[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec0[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec12[l10] = 0.0;
#ifndef _MOD_DEVICE_DUO
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) lowpass_fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) lowpass_fRec0[l1] = 0.0;
#endif
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
#ifndef _MOD_DEVICE_DUO
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
#else
	fSampleRate = RsamplingFreq;
#endif
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (2.50211256782905e-10 * fConst0);
	fConst3 = (fConst2 + -1.41841347670627e-07);
	double fConst4 = (3.2334114663882602e-10 * fConst0);
	fConst5 = (fConst4 + -1.8384980771754499e-06);
	fConst6 = (3.68740380275009e-05 * fConst0);
	fConst7 = (0.0 - fConst6);
	fConst8 = (fConst2 + 1.41841347670627e-07);
	fConst9 = (fConst4 + 1.8384980771754499e-06);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#ifndef _MOD_DEVICE_DUO
	int upcount = smp.max_out_count(count);
	FAUSTFLOAT buf[upcount];
	memset(buf, 0, upcount*sizeof(float));
	int ReCount = smp.up(count, input0, buf);
#else
	if(output0 != input0)
		memcpy(output0, input0, count*sizeof(float));
	float* buf = output0;
	int ReCount = count;
#endif
	double fSlow0 = (0.00036676987543879196 * (std::exp((3.0 * (1.0 - double(fVslider0)))) + -1.0));
	double fSlow1 = (0.0070000000000000062 * double(fHslider0));
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		double fTemp0 = double(buf[i0]);
		iVec0[0] = 1;
		double fTemp1 = double(rumorclip(double((0.66600000000000004 * fRec0[1]))));
		double fTemp2 = (0.5 * fRec1[1]);
		double fTemp3 = (0.40000000000000002 * fRec3[1]);
		double fTemp4 = (fTemp2 + ((0.29999999999999999 * fRec5[1]) + fTemp3));
		double fTemp5 = (((0.20000000000000001 * fRec7[1]) + fTemp1) - fTemp4);
		fRec7[0] = fTemp5;
		double fRec8 = (0.0 - (0.20000000000000001 * fTemp5));
		fRec5[0] = (fRec8 + fRec7[1]);
		double fRec6 = (0.29999999999999999 * (fTemp1 - fTemp4));
		fRec3[0] = (fRec6 + fRec5[1]);
		double fRec4 = (0.40000000000000002 * (fTemp1 - (fTemp3 + fTemp2)));
		fRec1[0] = (fRec4 + fRec3[1]);
		double fRec2 = (0.5 * (fTemp1 - fTemp2));
		fRec9[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec9[1]);
		fRec11[0] = (fSlow0 + (0.99299999999999999 * fRec11[1]));
		double fTemp6 = (fTemp0 + fRec9[0]);
		fVec1[0] = fTemp6;
		fRec10[0] = (0.0 - ((((fRec10[1] * ((fConst1 * ((0.0 - (6.4668229327765205e-10 * fRec11[0])) + -5.0042251356581001e-10)) + 0.00018384980771754501)) + (fRec10[2] * ((fConst0 * (fConst3 + (fConst5 * fRec11[0]))) + 9.1924903858772505e-05))) - (((6.8740380275009003e-06 * fVec1[1]) + (fConst6 * fVec1[2])) + (fConst7 * fTemp6))) / ((fConst0 * (fConst8 + (fConst9 * fRec11[0]))) + 9.1924903858772505e-05)));
		fRec0[0] = ((fTemp0 + (fRec1[1] + (fRec2 + (2.0 * fRec9[0])))) - double(rumorclip(double((fRec10[0] - fTemp6)))));
		fRec12[0] = (fSlow1 + (0.99299999999999999 * fRec12[1]));
		buf[i0] = FAUSTFLOAT((fRec0[0] * fRec12[0]));
		iVec0[1] = iVec0[0];
		fRec7[1] = fRec7[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fVec1[2] = fVec1[1];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec0[1] = fRec0[0];
		fRec12[1] = fRec12[0];
	}
#ifndef _MOD_DEVICE_DUO
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
#endif
}


void Dsp::connect(uint32_t port,float data)
{
	switch (port)
	{
	case PluginRumor::INTENSITY: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginRumor::LEVEL: 
		fHslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

Dsp *plugin() {
	return new Dsp();
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}
} // end namespace rumor
