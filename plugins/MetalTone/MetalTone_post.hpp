

#ifndef METALTONE_POST_H
#define METALTONE_POST_H


#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

namespace metaltone_post {


class Dsp {
private:
	gx_resample::SimpleResampler smp;
    int ratio;
	uint32_t fsample_rate;
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst4;
	double fConst7;
	double fConst9;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec4[7];
	double fConst20;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fRec3[2];
	double fConst29;
	FAUSTFLOAT fVslider0;
	double fRec5[2];
	double fConst31;
	double fConst33;
	FAUSTFLOAT fVslider1;
	double fRec6[2];
	double fConst35;
	double fConst37;
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst65;
	double fConst67;
	double fConst69;
	double fConst71;
	double fConst73;
	double fConst75;
	double fConst77;
	double fConst79;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec2[5];
	double fConst92;
	double fConst94;
	double fConst96;
	double fConst98;
	double fConst99;
	double fConst101;
	double fConst102;
	double fConst104;
	double fConst105;
	double fConst107;
	double fConst109;
	double fConst111;
	double fConst113;
	double fConst114;
	double fConst116;
	double fConst117;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst125;
	double fConst126;
	double fConst128;
	double fConst129;
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst152;
	FAUSTFLOAT fVslider2;
	double fRec7[2];
	double fConst154;
	double fConst156;
	double fConst157;
	FAUSTFLOAT fVslider3;
	double fRec8[2];
	double fConst159;
	double fConst161;
	double fConst163;
	double fConst165;
	double fConst167;
	double fConst169;
	double fConst170;
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst192;
	double fConst194;
	double fConst196;
	double fConst198;
	double fConst199;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fRec1[7];
	double fConst211;
	double fConst213;
	double fConst215;
	double fConst217;
	double fConst219;
	double fConst221;
	double fConst223;
	double fConst225;
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	FAUSTFLOAT fVslider4;
	double fRec9[2];
	double fConst239;
	double fConst240;
	double fConst242;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fRec0[3];


public:
	void connect(uint32_t port, float data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	Dsp();
	~Dsp();
};

} // end namespace metaltone_post

#endif
