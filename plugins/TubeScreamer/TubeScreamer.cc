

#include "ts9nonlin.h"
#include "TubeScreamer.hpp"

namespace tubescreamer {

Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int32_t i=0; i<2; i++) fRec0[i] = 0;
	for (int32_t i=0; i<2; i++) fVec0[i] = 0;
	for (int32_t i=0; i<2; i++) fRec2[i] = 0;
	for (int32_t i=0; i<2; i++) fVec1[i] = 0;
	for (int32_t i=0; i<2; i++) fRec1[i] = 0;
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = MIN(192000, MAX(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = (0.00044179999999999995 * iConst0);
	fConst3 = (1 + fConst2);
	fConst4 = (0 - ((1 - fConst2) / fConst3));
	fConst5 = (9.4e-08 * iConst0);
	fConst6 = (1.0 / fConst3);
	clear_state_f();
}

void Dsp::connect(uint32_t port, float data)
{
  switch (port)
    {
    case PluginTubeScreamer::LEVEL:
      fslider0 = data;
      break;
    case PluginTubeScreamer::TONE:
      fslider1 = data;
      break;
    case PluginTubeScreamer::DRIVE:
      fslider2 = data;
      break;
    default:
      break;
    }
}

inline void Dsp::compute(uint32_t count, float *input0, float *output0)
{    
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (1.0 / tan((fConst1 * fslider1)));
	double 	fSlow2 = (1 + fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow1) / fSlow2));
	double 	fSlow4 = (fConst5 * ((500000 * fslider2) + 55700));
	double 	fSlow5 = (1 + fSlow4);
	double 	fSlow6 = (1 - fSlow4);
	double 	fSlow7 = (1.0 / fSlow2);
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec2[0] = ((fConst6 * ((fSlow6 * fVec0[1]) + (fSlow5 * fVec0[0]))) + (fConst4 * fRec2[1]));
		double fTemp1 = (fVec0[0] - ts9nonlin((fRec2[0] - fVec0[0])));
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow7 * (fVec1[0] + fVec1[1])) + (fSlow3 * fRec1[1]));
		output0[i] = (float)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}
}

Dsp *plugin() {
	return new Dsp();
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}

}
