// generated from file '/home/brummer/projecte/guitarix-git/trunk/tools/ampsim/DK/dkbuild/boobtube60v/boobtube60v.dsp' by dsp2cc:
// Code generated with Faust 2.60.3 (https://faust.grame.fr)

using std::signbit;

#include "boobtube60v_p2_table.h"

namespace boobtube60v {

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
	double fConst1 = 3.86223883538146e-21 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst1 + 1.2010857529324e-14) + 1.323404921473e-12) + 4.86147135575005e-12;
	double fConst3 = 5.20661388343281e-22 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + 2.87134677002326e-15) + 1.6288614513149e-12) + 1.4564922895926e-10;
	double fConst5 = 4.85942386030631e-20 * fConst0;
	fConst6 = mydsp_faustpower3_f(fConst0);
	fConst7 = fConst6 * (1.07987196895695e-13 - fConst5);
	double fConst8 = 5.16959985138969e-18 * fConst0;
	fConst9 = mydsp_faustpower2_f(fConst0);
	fConst10 = fConst9 * (fConst8 + -1.14879996697548e-11);
	fConst11 = fConst0 * (fConst0 * (fConst1 + -1.2010857529324e-14) + 1.323404921473e-12) + -4.86147135575005e-12;
	fConst12 = fConst0 * (fConst0 * (fConst3 + -2.87134677002326e-15) + 1.6288614513149e-12) + -1.4564922895926e-10;
	double fConst13 = 1.54489553415258e-20 * fConst0;
	fConst14 = fConst9 * (2.40217150586479e-14 - fConst13) + -9.7229427115001e-12;
	double fConst15 = 2.08264555337313e-21 * fConst0;
	fConst16 = fConst9 * (5.74269354004651e-15 - fConst15) + -2.91298457918521e-10;
	fConst17 = 2.31734330122887e-20 * fConst9 + -2.64680984294599e-12;
	fConst18 = 3.12396833005969e-21 * fConst9 + -3.25772290262979e-12;
	fConst19 = fConst9 * (-2.40217150586479e-14 - fConst13) + 9.7229427115001e-12;
	fConst20 = fConst9 * (-5.74269354004651e-15 - fConst15) + 2.91298457918521e-10;
	double fConst21 = 1.42025099076582e-16 * fConst0;
	fConst22 = fConst0 * (fConst0 * (4.25565240541697e-10 - fConst21) + -7.89011791471091e-08) + 3.58943579169007e-06;
	double fConst23 = 4.26075297229745e-16 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst23 + -4.25565240541697e-10) + -7.89011791471091e-08) + 1.07683073750702e-05;
	fConst25 = fConst0 * (fConst0 * (-4.25565240541697e-10 - fConst23) + 7.89011791471091e-08) + 1.07683073750702e-05;
	double fConst26 = fConst0 * (fConst0 * (fConst21 + 4.25565240541697e-10) + 7.89011791471091e-08) + 3.58943579169007e-06;
	fConst27 = 1.0 / fConst26;
	double fConst28 = 1.67731684132783e-15 * fConst0;
	fConst29 = fConst28 + -3.7273707585063e-09;
	double fConst30 = 5.03195052398348e-15 * fConst0;
	fConst31 = 3.7273707585063e-09 - fConst30;
	fConst32 = fConst30 + 3.7273707585063e-09;
	fConst33 = -3.7273707585063e-09 - fConst28;
	fConst34 = fConst9 / fConst26;
	double fConst35 = 1.94376954412252e-19 * fConst0;
	fConst36 = fConst35 + -2.15974393791391e-13;
	fConst37 = mydsp_faustpower4_f(fConst0);
	fConst38 = 2.29759993395097e-11 * fConst9;
	fConst39 = fConst35 + 2.15974393791391e-13;
	fConst40 = fConst6 * (-1.07987196895695e-13 - fConst5);
	fConst41 = fConst9 * (-1.14879996697548e-11 - fConst8);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst0 * (fConst4 + fConst2 * fRec0[0]) + 5.17177803803197e-10;
		fRec2[0] = double(input0[i0]) - fConst27 * (fConst25 * fRec2[1] + fConst24 * fRec2[2] + fConst22 * fRec2[3]);
		fRec3[0] = fSlow1 + 0.993 * fRec3[1];
		fRec1[0] = (fConst34 * fRec3[0] * (fConst33 * fRec2[0] + fConst32 * fRec2[1] + fConst31 * fRec2[2] + fConst29 * fRec2[3])) - (fRec1[1] * (fConst0 * (fConst20 + fConst19 * fRec0[0]) + 2.06871121521279e-09) + fRec1[2] * (fConst9 * (fConst18 + fConst17 * fRec0[0]) + 3.10306682281918e-09) + fRec1[3] * (fConst0 * (fConst16 + fConst14 * fRec0[0]) + 2.06871121521279e-09) + fRec1[4] * (fConst0 * (fConst12 + fConst11 * fRec0[0]) + 5.17177803803197e-10)) / fTemp0;
		output0[i0] = FAUSTFLOAT(boobtube60v_p2clip((fRec1[0] * (fConst41 + fConst40 * fRec0[0]) + fConst6 * fRec1[1] * (fConst39 * fRec0[0] + 1.03391997027794e-17) + fRec1[2] * (fConst38 + fConst37 * (0.0 - 2.91565431618379e-19 * fRec0[0])) + fConst6 * fRec1[3] * (fConst36 * fRec0[0] + -1.03391997027794e-17) + fRec1[4] * (fConst10 + fConst7 * fRec0[0])) / fTemp0));
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
} // end namespace boobtube60v
