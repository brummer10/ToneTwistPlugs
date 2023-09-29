// generated from file 'metaltone_pre.dsp' by dsp2cc:
// Code generated with Faust 2.37.3 (https://faust.grame.fr)

#include "MetalTone_pre.hpp"

namespace metaltone_pre {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec3[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;
	for (int l3 = 0; (l3 < 6); l3 = (l3 + 1)) fRec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec4[l4] = 0.0;
	for (int l5 = 0; (l5 < 6); l5 = (l5 + 1)) fRec0[l5] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (2.4454389978744e-24 * fConst0);
	double fConst3 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst2 + 6.53471849041744e-20)) + 2.5429934560721901e-16)) + 7.8893500689320605e-13)) + 1.26822396718671e-09)) + 3.4370367963274599e-07);
	fConst4 = (fConst0 / fConst3);
	double fConst5 = (2.60149822831355e-21 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (fConst5 + 3.7902141568022202e-16)) + 6.2380028516919599e-12)) + 5.1554905491952698e-10);
	double fConst7 = (2.0828448816504301e-05 * fConst0);
	double fConst8 = (fConst7 + 0.000234456807793764);
	fConst9 = (1.0 / fConst8);
	fConst10 = (2.0461591370717701e-05 * fConst0);
	fConst11 = (0.0 - fConst10);
	fConst12 = ((0.000234456807793764 - fConst7) / fConst8);
	fConst13 = (1.0 / fConst3);
	double fConst14 = (1.2227194989371999e-23 * fConst0);
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-1.9604155471252301e-19 - fConst14)) + -2.5429934560721901e-16)) + 7.8893500689320605e-13)) + 3.8046719015601301e-09)) + 1.71851839816373e-06);
	double fConst16 = (2.4454389978743999e-23 * fConst0);
	fConst17 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst16 + 1.3069436980834899e-19)) + -5.0859869121443703e-16)) + -1.5778700137864101e-12)) + 2.5364479343734201e-09)) + 3.4370367963274599e-06);
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.3069436980834899e-19 - fConst16)) + 5.0859869121443703e-16)) + -1.5778700137864101e-12)) + -2.5364479343734201e-09)) + 3.4370367963274599e-06);
	fConst19 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst14 + -1.9604155471252301e-19)) + 2.5429934560721901e-16)) + 7.8893500689320605e-13)) + -3.8046719015601301e-09)) + 1.71851839816373e-06);
	fConst20 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (6.53471849041744e-20 - fConst2)) + -2.5429934560721901e-16)) + 7.8893500689320605e-13)) + -1.26822396718671e-09)) + 3.4370367963274599e-07);
	double fConst21 = (7.8044946849406405e-21 * fConst0);
	fConst22 = ((fConst0 * ((fConst0 * (-3.7902141568022202e-16 - fConst21)) + 6.2380028516919599e-12)) + 1.54664716475858e-09);
	double fConst23 = (5.2029964566270999e-21 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * (fConst23 + -7.5804283136044503e-16)) + -1.24760057033839e-11)) + 1.03109810983905e-09);
	fConst25 = ((fConst0 * ((fConst0 * (fConst23 + 7.5804283136044503e-16)) + -1.24760057033839e-11)) + -1.03109810983905e-09);
	fConst26 = ((fConst0 * ((fConst0 * (3.7902141568022202e-16 - fConst21)) + 6.2380028516919599e-12)) + -1.54664716475858e-09);
	fConst27 = ((fConst0 * ((fConst0 * (fConst5 + -3.7902141568022202e-16)) + 6.2380028516919599e-12)) + -5.1554905491952698e-10);
	double fConst28 = (8.1829041012475801e-26 * fConst0);
	fConst29 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.4558602855716899e-19 - fConst28)) + -1.6375226020253499e-16)) + 4.1818885656575898e-15)) + 7.81631984574476e-14));
	double fConst30 = (2.0457260253119e-23 * fConst0);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.4726379935447899e-20 - fConst30)) + -3.17729560581312e-19)) + 2.9361901163372201e-18)) + 2.9317775786648898e-22)) + -1.9287541852157898e-37);
	double fConst32 = (1.6365808202495199e-25 * fConst0);
	fConst33 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst32 + 1.6372401903811301e-19)) + -3.27504520405069e-16)) + -8.3637771313151796e-15)) + 5.2108798971631697e-14));
	double fConst34 = (4.09145205062379e-23 * fConst0);
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst34 + 1.6484253290298599e-20)) + -6.3545912116262496e-19)) + -5.8723802326744502e-18)) + 1.9545183857765899e-22)) + -3.8575083704315896e-37);
	fConst36 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.6372401903811301e-19 - fConst32)) + 3.27504520405069e-16)) + -8.3637771313151796e-15)) + -5.2108798971631697e-14));
	fConst37 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.6484253290298599e-20 - fConst34)) + 6.3545912116262496e-19)) + -5.8723802326744502e-18)) + -1.9545183857765899e-22)) + -3.8575083704315896e-37);
	fConst38 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst28 + -2.4558602855716899e-19)) + 1.6375226020253499e-16)) + 4.1818885656575898e-15)) + -7.81631984574476e-14));
	fConst39 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst30 + -2.4726379935447899e-20)) + 3.17729560581312e-19)) + 2.9361901163372201e-18)) + -2.9317775786648898e-22)) + -1.9287541852157898e-37);
	double fConst40 = (1.6365808202495199e-26 * fConst0);
	fConst41 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.1862009519056397e-20 - fConst40)) + -1.6375226020253499e-16)) + 4.1818885656575898e-15)) + -2.6054399485815899e-14));
	double fConst42 = (4.0914520506237897e-24 * fConst0);
	fConst43 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.2421266451492906e-21 - fConst42)) + -3.17729560581312e-19)) + 2.9361901163372201e-18)) + -9.7725919288829695e-23)) + -3.8575083704315898e-38);
	fConst44 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst40 + 8.1862009519056397e-20)) + 1.6375226020253499e-16)) + 4.1818885656575898e-15)) + 2.6054399485815899e-14));
	fConst45 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst42 + 8.2421266451492906e-21)) + 3.17729560581312e-19)) + 2.9361901163372201e-18)) + 9.7725919288829695e-23)) + -3.8575083704315898e-38);
	double fConst46 = (4.5513749074640697e-27 * fConst0);
	fConst47 = ((fConst0 * ((fConst0 * (fConst46 + 2.7631090410295103e-20)) + 1.95978343740697e-16)) + 1.71698163100351e-15);
	double fConst48 = (1.1378437268660201e-24 * fConst0);
	fConst49 = ((fConst0 * ((fConst0 * (fConst48 + 1.21855396824368e-18)) + 8.5849940040990806e-15)) + -6.0912319157991503e-30);
	double fConst50 = (2.2756874537320399e-26 * fConst0);
	fConst51 = ((fConst0 * ((fConst0 * (-8.2893271230885296e-20 - fConst50)) + -1.95978343740697e-16)) + 1.71698163100351e-15);
	double fConst52 = (5.6892186343300897e-24 * fConst0);
	fConst53 = ((fConst0 * ((fConst0 * (-3.6556619047310501e-18 - fConst52)) + -8.5849940040990806e-15)) + -6.0912319157991503e-30);
	double fConst54 = (4.55137490746407e-26 * fConst0);
	fConst55 = ((fConst0 * ((fConst0 * (fConst54 + 5.5262180820590205e-20)) + -3.9195668748139399e-16)) + -3.4339632620070101e-15);
	double fConst56 = (1.13784372686602e-23 * fConst0);
	fConst57 = ((fConst0 * ((fConst0 * (fConst56 + 2.4371079364873701e-18)) + -1.7169988008198199e-14)) + 1.2182463831598301e-29);
	fConst58 = ((fConst0 * ((fConst0 * (5.5262180820590205e-20 - fConst54)) + 3.9195668748139399e-16)) + -3.4339632620070101e-15);
	fConst59 = ((fConst0 * ((fConst0 * (2.4371079364873701e-18 - fConst56)) + 1.7169988008198199e-14)) + 1.2182463831598301e-29);
	fConst60 = ((fConst0 * ((fConst0 * (fConst50 + -8.2893271230885296e-20)) + 1.95978343740697e-16)) + 1.71698163100351e-15);
	fConst61 = ((fConst0 * ((fConst0 * (fConst52 + -3.6556619047310501e-18)) + 8.5849940040990806e-15)) + -6.0912319157991503e-30);
	fConst62 = ((fConst0 * ((fConst0 * (2.7631090410295103e-20 - fConst46)) + -1.95978343740697e-16)) + 1.71698163100351e-15);
	fConst63 = ((fConst0 * ((fConst0 * (1.21855396824368e-18 - fConst48)) + -8.5849940040990806e-15)) + -6.0912319157991503e-30);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider0))) + -1.0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		iVec0[0] = 1;
		fRec3[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec3[1]);
		fRec2[0] = ((double(input0[i0]) + fRec3[0]) - (fConst12 * fRec2[1]));
		fRec1[0] = ((fConst9 * ((fConst11 * fRec2[1]) + (fConst10 * fRec2[0]))) - (fConst13 * (((((fConst15 * fRec1[1]) + (fConst17 * fRec1[2])) + (fConst18 * fRec1[3])) + (fConst19 * fRec1[4])) + (fConst20 * fRec1[5]))));
		fRec4[0] = (fSlow0 + (0.99299999999999999 * fRec4[1]));
		double fTemp0 = (fConst44 + ((fConst45 * fRec4[0]) + 8.67173312581635e-19));
		fRec0[0] = ((fConst4 * ((((((fConst6 * fRec1[0]) + (fConst22 * fRec1[1])) + (fConst24 * fRec1[2])) + (fConst25 * fRec1[3])) + (fConst26 * fRec1[4])) + (fConst27 * fRec1[5]))) - ((((((fRec0[1] * (fConst29 + ((fConst31 * fRec4[0]) + 4.3358665629081701e-18))) + (fRec0[2] * (fConst33 + ((fConst35 * fRec4[0]) + 8.6717331258163494e-18)))) + (fRec0[3] * (fConst36 + ((fConst37 * fRec4[0]) + 8.6717331258163494e-18)))) + (fRec0[4] * (fConst38 + ((fConst39 * fRec4[0]) + 4.3358665629081701e-18)))) + (fRec0[5] * (fConst41 + ((fConst43 * fRec4[0]) + 8.67173312581635e-19)))) / fTemp0));
		output0[i0] = FAUSTFLOAT((fConst1 * (((((((fRec0[0] * (fConst47 + (fConst49 * fRec4[0]))) + (fRec0[1] * (fConst51 + (fConst53 * fRec4[0])))) + (fRec0[2] * (fConst55 + (fConst57 * fRec4[0])))) + (fRec0[3] * (fConst58 + (fConst59 * fRec4[0])))) + (fRec0[4] * (fConst60 + (fConst61 * fRec4[0])))) + (fRec0[5] * (fConst62 + (fConst63 * fRec4[0])))) / fTemp0)) * 0.25);
		iVec0[1] = iVec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
		fRec4[1] = fRec4[0];
		for (int j1 = 5; (j1 > 0); j1 = (j1 - 1)) {
			fRec0[j1] = fRec0[(j1 - 1)];
		}
	}
}


void Dsp::connect(uint32_t port,float data)
{
	switch (port)
	{
	case PluginMetalTone::DIST: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
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
} // end namespace metaltone_pre
