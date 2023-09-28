
#ifndef METALTONE_PRE_H
#define METALTONE_PRE_H

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

namespace metaltone_pre {


class Dsp {
private:
	uint32_t fSampleRate;
	double fConst1;
	double fConst4;
	double fConst6;
	double fConst9;
	double fConst10;
	double fConst11;
	int iVec0[2];
	double fRec3[2];
	double fConst12;
	double fRec2[2];
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fRec1[6];
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst29;
	double fConst31;
	FAUSTFLOAT fVslider0;
	double fRec4[2];
	double fConst33;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec0[6];
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst53;
	double fConst55;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;


public:
	void connect(uint32_t port,float data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	Dsp();
	~Dsp();
};

} // end namespace metaltone_pre

#endif
