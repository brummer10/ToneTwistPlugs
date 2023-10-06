// generated from file './/CollisionDrive.dsp' by dsp2cc:
// Code generated with Faust 2.33.1 (https://faust.grame.fr)

#include "CollisionDrive.hpp"
#include "ts9nonlin.h"

template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}

namespace CollisionDrive {
const static double fmydspSIG0Wave0[6] = {0.46999999999999997,0.22,0.10000000000000001,0.047,0.021999999999999999,0.01};
class mydspSIG0 {
	
  private:
	
	int fmydspSIG0Wave0_idx;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		fmydspSIG0Wave0_idx = 0;
        (void)sample_rate;
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			table[i1] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
			fmydspSIG0Wave0_idx = ((1 + fmydspSIG0Wave0_idx) % 6);
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[6];


Dsp::Dsp(std::function<void(const uint32_t , float) > setOutputParameterValue_) 
  : setOutputParameterValue(setOutputParameterValue_) {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iVec0[l2] = 0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) iRec10[l3] = 0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) iRec4[l7] = 0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec2[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec11[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec12[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec1[l13] = 0.0;
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
	mydspSIG0* sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(fSampleRate);
	sig0->fillmydspSIG0(6, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (4.3304479901401401e-10 * fConst0);
	fConst2 = (1.0 / ((fConst0 * (fConst1 + 4.7159737121383797e-08)) + 1.11568988593319e-06));
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = (0.0 - (8.5004280820074899e-10 * fConst3));
	fConst5 = (1.0 / fConst0);
	double fConst6 = std::max<double>(fConst5, 0.0001);
	double fConst7 = std::max<double>(fConst5, 0.02);
	double fConst8 = std::min<double>(fConst6, fConst7);
	int iConst9 = (std::fabs(fConst8) < 2.2204460492503131e-16);
	fConst10 = (iConst9 ? 0.0 : std::exp((0.0 - (fConst5 / (iConst9 ? 1.0 : fConst8)))));
	fConst11 = (1.0 - fConst10);
	iConst12 = int((fConst0 * std::max<double>(fConst5, 0.20000000000000001)));
	int iConst13 = (std::fabs(fConst6) < 2.2204460492503131e-16);
	fConst14 = (iConst13 ? 0.0 : std::exp((0.0 - (fConst5 / (iConst13 ? 1.0 : fConst6)))));
	int iConst15 = (std::fabs(fConst7) < 2.2204460492503131e-16);
	fConst16 = (iConst15 ? 0.0 : std::exp((0.0 - (fConst5 / (iConst15 ? 1.0 : fConst7)))));
	fConst17 = (2.2313797718663901e-06 - (8.6608959802802803e-10 * fConst3));
	fConst18 = ((fConst0 * (fConst1 + -4.7159737121383797e-08)) + 1.11568988593319e-06);
	fConst19 = (4.2502140410037501e-10 * fConst3);
	fConst20 = (0.002 * fConst0);
	fConst21 = (1.9999999999999999e-06 * fConst0);
	double fConst22 = (5.8939796203307699e-11 * fConst0);
	fConst23 = (fConst22 + -1.3651141432266e-06);
	double fConst24 = (1.3395408228024499e-09 * fConst0);
	fConst25 = (fConst24 + -2.7399746219806602e-06);
	double fConst26 = (1.3395303570560199e-09 * fConst0);
	fConst27 = (3.3488258926400502e-06 - fConst26);
	fConst28 = (fConst22 + 1.3651141432266e-06);
	fConst29 = (fConst24 + 2.7399746219806602e-06);
	fConst30 = (-3.3488258926400502e-06 - fConst26);
	clear_state_f();
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#ifndef _MOD_DEVICE_DUO
	int upcount = smp.max_out_count(count);
	float buf[upcount];
	memset(buf, 0, upcount*sizeof(float));
	int ReCount = smp.up(count, input0, buf);
#else
	if(output0 != input0)
		memcpy(output0, input0, count*sizeof(float));
	float* buf = output0;
	int ReCount = count;
#endif
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fHslider0))));
	double fSlow1 = std::pow(10.0, (0.050000000000000003 * double(fHslider1)));
	double fSlow2 = ftbl0mydspSIG0[int(double(fHslider2))];
	double fSlow3 = (fConst20 * fSlow2);
	double fSlow4 = (1.0 - fSlow3);
	double fSlow5 = ((fConst21 * ((26197.848245627974 * (std::exp((3.0 * double(fHslider3))) + -1.0)) + 11000.0)) * fSlow2);
	double fSlow6 = (fSlow5 + 1.0);
	double fSlow7 = (1.0 - fSlow5);
	double fSlow8 = (fSlow3 + 1.0);
	double fSlow9 = (0.0070000000000000062 * double(fVslider0));
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		int iTemp0 = (iRec4[1] < 4096);
		double fTemp1 = double(buf[i0]);
		fRec9[0] = ((fRec9[1] * fConst10) + (std::fabs(fTemp1) * fConst11));
		double fRec8 = fRec9[0];
		int iTemp2 = (fRec8 > fSlow1);
		iVec0[0] = iTemp2;
		iRec10[0] = std::max<int>(int((iConst12 * (iTemp2 < iVec0[1]))), int((iRec10[1] + -1)));
		double fTemp3 = std::fabs(std::max<double>(double(iTemp2), double((iRec10[0] > 0))));
		double fTemp4 = ((fRec6[1] > fTemp3) ? fConst16 : fConst14);
		fRec7[0] = ((fRec7[1] * fTemp4) + (fTemp3 * (1.0 - fTemp4)));
		fRec6[0] = fRec7[0];
		double fTemp5 = (fTemp1 * fRec6[0]);
		double fTemp6 = std::max<double>(fConst5, std::fabs(fTemp5));
		fRec3[0] = (iTemp0 ? std::max<double>(fRec3[1], fTemp6) : fTemp6);
		iRec4[0] = (iTemp0 ? (iRec4[1] + 1) : 1);
		fRec5[0] = (iTemp0 ? fRec5[1] : fRec3[1]);
		fVbargraph0 = fCheck0 ? 1.0 : float(fRec5[0]);
		fRec2[0] = (fTemp5 - (fConst2 * ((fConst17 * fRec2[1]) + (fConst18 * fRec2[2]))));
		double fTemp7 = (((fConst4 * fRec2[1]) + (fConst19 * fRec2[0])) + (fConst19 * fRec2[2]));
		fVec1[0] = fTemp7;
		double fTemp8 = (fConst2 * fTemp7);
		fRec11[0] = (0.0 - (((fRec11[1] * fSlow4) - (fConst2 * ((fTemp7 * fSlow6) + (fVec1[1] * fSlow7)))) / fSlow8));
		fRec12[0] = (fSlow9 + (0.99299999999999999 * fRec12[1]));
		double fTemp9 = ((fConst0 * (fConst28 + (fRec12[0] * (fConst29 + (fConst30 * fRec12[0]))))) + 0.0015222082526936099);
		fRec1[0] = (fTemp8 - (double(ts9nonlin(double((fRec11[0] - fTemp8)))) + (((fRec1[1] * ((fConst3 * ((fRec12[0] * ((2.6790607141120398e-09 * fRec12[0]) + -2.6790816456048998e-09)) + -1.1787959240661501e-10)) + 0.0030444165053872302)) + (fRec1[2] * ((fConst0 * (fConst23 + (fRec12[0] * (fConst25 + (fConst27 * fRec12[0]))))) + 0.0015222082526936099))) / fTemp9)));
		double fTemp10 = (3.0443566805281699e-06 * fRec12[0]);
		buf[i0] = float(((fRec0[0] * (((fRec1[0] * ((fConst0 * ((fRec12[0] * ((0.0 - fTemp10) + 5.4189548913401304e-06)) + 1.3395169394323901e-07)) + 0.00138379849114917)) + (0.0027675969822983301 * fRec1[1])) + (fRec1[2] * ((fConst0 * ((fRec12[0] * (fTemp10 + -5.4189548913401304e-06)) + -1.3395169394323901e-07)) + 0.00138379849114917)))) / fTemp9));
		fRec0[1] = fRec0[0];
		fRec9[1] = fRec9[0];
		iVec0[1] = iVec0[0];
		iRec10[1] = iRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		iRec4[1] = iRec4[0];
		fRec5[1] = fRec5[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
#ifndef _MOD_DEVICE_DUO
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		lowpass_fRec1[0] = (double(buf[i0]) - ((1.7383024478502873 * lowpass_fRec1[1]) + (0.75793715340193646 * lowpass_fRec1[2])));
		lowpass_fRec0[0] = (((1.7481198006261118 * lowpass_fRec1[1]) + (0.87405990031305592 * (lowpass_fRec1[0] + lowpass_fRec1[2]))) - ((1.8709501296525741 * lowpass_fRec0[1]) + (0.89208313498371072 * lowpass_fRec0[2])));
		buf[i0] = float(((1.8815166323181425 * lowpass_fRec0[1]) + (0.94075831615907124 * (lowpass_fRec0[0] + lowpass_fRec0[2]))));
		lowpass_fRec1[2] = lowpass_fRec1[1];
		lowpass_fRec1[1] = lowpass_fRec1[0];
		lowpass_fRec0[2] = lowpass_fRec0[1];
		lowpass_fRec0[1] = lowpass_fRec0[0];
	}
	smp.down(buf, output0);
#endif
	setOutputParameterValue(PluginCollisionDrive::V1, fVbargraph0 > 0.0001 ? 1.0 : 0.0);
}

void Dsp::connect(uint32_t port, float data)
{
	switch (port)
	{
	case PluginCollisionDrive::dpf_bypass: 
		fCheck0 = data; // , 0, 0.0, 1.0, 0 
		break;
	case PluginCollisionDrive::BRIGHT: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginCollisionDrive::GATE: 
		fHslider1 = data; // , -15.0, -30.0, -10.0, 1.0 
		break;
	case PluginCollisionDrive::ATTACK: 
		fHslider2 = data; // , 3.0, 0.0, 5.0, 1.0 
		break;
	case PluginCollisionDrive::DRIVE: 
		fHslider3 = data; // , 0.10000000000000001, 0.0, 1.0, 0.01 
		break;
	case PluginCollisionDrive::LEVEL: 
		fHslider0 = data; // , -10.0, -20.0, 4.0, 0.10000000000000001 
		break;
	case PluginCollisionDrive::V1: 
		fVbargraph0 = data; // , 0, 0.0, 1.0, 0 
		break;
	default:
		break;
	}
}

Dsp *plugin(std::function<void(const uint32_t , float) > setOutputParameterValue_) {
	return new Dsp(setOutputParameterValue_);
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}

/*
typedef enum
{
   BRIGHT, 
   GATE, 
   ATTACK, 
   DRIVE, 
   LEVEL, 
   V1, 
} PortIndex;
*/

} // end namespace CollisionDrive
