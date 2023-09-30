

#ifndef COLLISIONDRIVE_H
#define COLLISIONDRIVE_H

#include <cmath>
#include <algorithm>
#include <functional>

#include "gx_resampler.h"


namespace CollisionDrive {

class Dsp {
private:
#ifndef _MOD_DEVICE_DUO
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
#endif
	uint32_t fSampleRate;
	float fHslider0;
	float fCheck0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst10;
	double fConst11;
	double fRec9[2];
	float fHslider1;
	int iVec0[2];
	int iConst12;
	int iRec10[2];
	double fConst14;
	double fConst16;
	double fRec7[2];
	double fRec6[2];
	double fRec3[2];
	int iRec4[2];
	double fRec5[2];
	float fVbargraph0;
	double fConst17;
	double fConst18;
	double fRec2[3];
	double fConst19;
	double fVec1[2];
	double fConst20;
	float fHslider2;
	double fConst21;
	float fHslider3;
	double fRec11[2];
	float fVslider0;
	double fRec12[2];
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fRec1[3];
#ifndef _MOD_DEVICE_DUO
	double lowpass_fRec1[3];
	double lowpass_fRec0[3];
#endif
	std::function<void(const uint32_t , float) > setOutputParameterValue;

public:
	void connect(uint32_t port,float data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, float *input0, float *output0);
	void del_instance(Dsp *p);
	Dsp(std::function<void(const uint32_t , float) > setOutputParameterValue_);
	~Dsp();
};

}

#endif
