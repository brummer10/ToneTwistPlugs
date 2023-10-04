// generated from file '/home/brummer/projecte/guitarix-git/trunk/tools/ampsim/DK/dkbuild/boobtube/boobtube.dsp' by dsp2cc:
// Code generated with Faust 2.60.3 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

using std::signbit;

#include "boobtube_p2_table.h"

namespace boobtube {

Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 4; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 5; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.2132040625887e-21 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst1 + 1.21795304542579e-14) + 1.34267648359548e-12) + 5.00313156108852e-12;
	double fConst3 = 6.14242186019802e-22 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + 2.77370846432488e-15) + 1.63774490055415e-12) + 1.47841055347842e-10;
	double fConst5 = 3.92611085835822e-20 * fConst0;
	fConst6 = mydsp_faustpower3_f(fConst0);
	fConst7 = fConst6 * (8.72469079635164e-14 - fConst5);
	double fConst8 = 4.17671367910449e-18 * fConst0;
	fConst9 = mydsp_faustpower2_f(fConst0);
	fConst10 = fConst9 * (fConst8 + -9.28158595356558e-12);
	fConst11 = fConst0 * (fConst0 * (fConst1 + -1.21795304542579e-14) + 1.34267648359548e-12) + -5.00313156108852e-12;
	fConst12 = fConst0 * (fConst0 * (fConst3 + -2.77370846432488e-15) + 1.63774490055415e-12) + -1.47841055347842e-10;
	double fConst13 = 1.68528162503548e-20 * fConst0;
	fConst14 = fConst9 * (2.43590609085158e-14 - fConst13) + -1.0006263122177e-11;
	double fConst15 = 2.45696874407921e-21 * fConst0;
	fConst16 = fConst9 * (5.54741692864976e-15 - fConst15) + -2.95682110695684e-10;
	fConst17 = 2.52792243755322e-20 * fConst9 + -2.68535296719096e-12;
	fConst18 = 3.68545311611881e-21 * fConst9 + -3.2754898011083e-12;
	fConst19 = fConst9 * (-2.43590609085158e-14 - fConst13) + 1.0006263122177e-11;
	fConst20 = fConst9 * (-5.54741692864976e-15 - fConst15) + 2.95682110695684e-10;
	double fConst21 = 1.53672360615659e-16 * fConst0;
	fConst22 = fConst0 * (fConst0 * (4.24990000313997e-10 - fConst21) + -7.96755869147096e-08) + 3.67739943783547e-06;
	double fConst23 = 4.61017081846978e-16 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst23 + -4.24990000313997e-10) + -7.96755869147096e-08) + 1.10321983135064e-05;
	fConst25 = fConst0 * (fConst0 * (-4.24990000313997e-10 - fConst23) + 7.96755869147096e-08) + 1.10321983135064e-05;
	double fConst26 = fConst0 * (fConst0 * (fConst21 + 4.24990000313997e-10) + 7.96755869147096e-08) + 3.67739943783547e-06;
	fConst27 = 1.0 / fConst26;
	double fConst28 = 1.2419917004877e-15 * fConst0;
	fConst29 = fConst28 + -2.75998155663931e-09;
	double fConst30 = 3.72597510146309e-15 * fConst0;
	fConst31 = 2.75998155663931e-09 - fConst30;
	fConst32 = fConst30 + 2.75998155663931e-09;
	fConst33 = -2.75998155663931e-09 - fConst28;
	fConst34 = 0.333 * (fConst9 / fConst26);
	double fConst35 = 1.57044434334329e-19 * fConst0;
	fConst36 = fConst35 + -1.74493815927033e-13;
	fConst37 = mydsp_faustpower4_f(fConst0);
	fConst38 = 1.85631719071312e-11 * fConst9;
	fConst39 = fConst35 + 1.74493815927033e-13;
	fConst40 = fConst6 * (-8.72469079635164e-14 - fConst5);
	fConst41 = fConst9 * (-9.28158595356558e-12 - fConst8);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst0 * (fConst4 + fConst2 * fRec0[0]) + 5.32248038413672e-10;
		fRec2[0] = double(input0[i0]) - fConst27 * (fConst25 * fRec2[1] + fConst24 * fRec2[2] + fConst22 * fRec2[3]);
		fRec3[0] = fSlow1 + 0.993 * fRec3[1];
		fRec1[0] = fConst34 * fRec3[0] * (fConst33 * fRec2[0] + fConst32 * fRec2[1] + fConst31 * fRec2[2] + fConst29 * fRec2[3]) - (fRec1[1] * (fConst0 * (fConst20 + fConst19 * fRec0[0]) + 2.12899215365469e-09) + fRec1[2] * (fConst9 * (fConst18 + fConst17 * fRec0[0]) + 3.19348823048203e-09) + fRec1[3] * (fConst0 * (fConst16 + fConst14 * fRec0[0]) + 2.12899215365469e-09) + fRec1[4] * (fConst0 * (fConst12 + fConst11 * fRec0[0]) + 5.32248038413672e-10)) / fTemp0;
		output0[i0] = FAUSTFLOAT(boobtube_p2clip((fRec1[0] * (fConst41 + fConst40 * fRec0[0]) + fConst6 * fRec1[1] * (fConst39 * fRec0[0] + 8.35342735820897e-18) + fRec1[2] * (fConst38 + fConst37 * (0.0 - 2.35566651501493e-19 * fRec0[0])) + fConst6 * fRec1[3] * (fConst36 * fRec0[0] + -8.35342735820897e-18) + fRec1[4] * (fConst10 + fConst7 * fRec0[0])) / fTemp0));
		fRec0[1] = fRec0[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		fRec3[1] = fRec3[0];
		for (int j1 = 4; j1 > 0; j1 = j1 - 1) {
			fRec1[j1] = fRec1[j1 - 1];
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
	case PluginBoobTube::GAIN: 
		fVslider1 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginBoobTube::TONE: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginBoobTube::VOLUME: 
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
} // end namespace boobtube
