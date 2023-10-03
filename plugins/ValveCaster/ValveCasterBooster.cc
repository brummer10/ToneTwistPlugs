// generated from file './/valvecasterbooster.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

namespace valvecasterbooster {

Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(MIN(1.92e+05, MAX(1.0, (double)fSamplingFreq)));
	fConst1 = (4.30050024066113e-10 * fConst0);
	fConst2 = (2.02588854219675e-05 + (fConst0 * (fConst1 - 1.90510118046938e-07)));
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = (4.05177708439351e-05 - (8.60100048132227e-10 * fConst3));
	fConst5 = (2.02588854219675e-05 + (fConst0 * (1.90510118046938e-07 + fConst1)));
	fConst6 = (1.0 / fConst5);
	fConst7 = (fConst3 / fConst5);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(MAX(0.05,fslider0)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fConst6 * ((fConst4 * fRec0[1]) + (fConst2 * fRec0[2]))));
		fRec1[0] = (fSlow0 + (0.993 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fConst7 * ((1.60869706452488e-08 * (fRec0[1] * fRec1[0])) + ((0 - (8.04348532262441e-09 * fRec1[0])) * (fRec0[2] + fRec0[0]))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

void Dsp::connect(uint32_t port, float data)
{
	switch (port)
	{
	case PluginValveCaster::GAIN: 
		fslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
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

/*
typedef enum
{
   GAIN, 
} PortIndex;
*/

} // end namespace valvecasterbooster
