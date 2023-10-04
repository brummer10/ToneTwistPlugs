// generated from file '/home/brummer/projecte/guitarix-git/trunk/tools/ampsim/DK/dkbuild/valvecaster/valvecaster.dsp' by dsp2cc:
// Code generated with Faust 2.60.3 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

using std::signbit;

#include "ValveCaster.hpp"
#include "valvecaster_p2_table.h"

namespace valvecaster {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 4; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.3562532820047e-14 * fConst0;
	fConst2 = fConst0 * (fConst1 + 3.13659107980429e-13) + 1.5109930881153e-13;
	double fConst3 = 2.11397893460255e-15 * fConst0;
	fConst4 = fConst0 * (fConst3 + 6.8958713135972e-12) + 1.5834054707833e-10;
	fConst5 = 1.58934810760281e-11 * mydsp_faustpower2_f(fConst0);
	fConst6 = mydsp_faustpower3_f(fConst0);
	fConst7 = 3.17869621520561e-14 * fConst6;
	fConst8 = fConst0 * (3.13659107980429e-13 - fConst1) + -1.5109930881153e-13;
	fConst9 = fConst0 * (6.8958713135972e-12 - fConst3) + -1.5834054707833e-10;
	double fConst10 = 4.06875984601411e-14 * fConst0;
	fConst11 = fConst0 * (fConst10 + -3.13659107980429e-13) + -1.5109930881153e-13;
	double fConst12 = 6.34193680380764e-15 * fConst0;
	fConst13 = fConst0 * (fConst12 + -6.8958713135972e-12) + -1.5834054707833e-10;
	fConst14 = fConst0 * (-3.13659107980429e-13 - fConst10) + 1.5109930881153e-13;
	fConst15 = fConst0 * (-6.8958713135972e-12 - fConst12) + 1.5834054707833e-10;
	double fConst16 = 1.70855815503405e-05 * fConst0;
	fConst17 = -0.000181761505854686 - fConst16;
	fConst18 = 2.93715078148334e-05 * fConst0;
	fConst19 = fConst16 + -0.000181761505854686;
	fConst20 = 9.53608864561684e-14 * fConst6;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst0 * (fConst4 + fConst2 * fRec0[0]) + 7.55496544057651e-11;
		fRec2[0] = fSlow1 + 0.993 * fRec2[1];
		double fTemp1 = fConst18 + fConst17 * fRec2[0] + 0.000312462849093973;
		double fTemp2 = 4.92318574510965e-19 * fRec2[0];
		fRec3[0] = double(input0[i0]) - fRec3[1] * (fConst19 * fRec2[0] + 0.000312462849093973 - fConst18) / fTemp1;
		fRec1[0] = fConst0 * ((fRec3[0] * (fTemp2 + -6.61548352285672e-05) + fRec3[1] * (0.0 - fTemp2 + 6.61548352285672e-05)) / fTemp1) - (fRec1[1] * (fConst0 * (fConst15 + fConst14 * fRec0[0]) + 2.26648963217295e-10) + fRec1[2] * (fConst0 * (fConst13 + fConst11 * fRec0[0]) + 2.26648963217295e-10) + fRec1[3] * (fConst0 * (fConst9 + fConst8 * fRec0[0]) + 7.55496544057651e-11)) / fTemp0;
		output0[i0] = FAUSTFLOAT(valvecaster_p2clip((fRec1[0] * (fConst6 * (0.0 - 3.17869621520561e-14 * fRec0[0]) - fConst5) + fRec1[1] * (fConst5 + fConst20 * fRec0[0]) + fRec1[2] * (fConst5 + fConst6 * (0.0 - 9.53608864561684e-14 * fRec0[0])) + fRec1[3] * (fConst7 * fRec0[0] - fConst5)) / fTemp0));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
	}
	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

}


void Dsp::connect(uint32_t port, float data)
{
	switch (port)
	{
	case PluginValveCaster::GAIN: 
		fVslider1 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginValveCaster::TONE: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginValveCaster::VOLUME: 
		fsliderV0 = data; // , 0.5, 0.0, 1, 0.01 
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
} // end namespace valvecaster
