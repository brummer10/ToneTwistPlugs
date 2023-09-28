// generated from file 'metaltone_post.dsp' by dsp2cc:
// Code generated with Faust 2.37.3 (https://faust.grame.fr)

#include "MetalTone_post.hpp"

using std::signbit;

namespace metaltone_post {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 7); l0 = (l0 + 1)) fRec4[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec3[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 5); l4 = (l4 + 1)) fRec2[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec8[l6] = 0.0;
	for (int l7 = 0; (l7 < 7); l7 = (l7 + 1)) fRec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec9[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec0[l9] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fsample_rate = sample_rate;
    ratio = std::max<int>(1, sample_rate/48000);
    if (ratio > 1) {
        smp.setup( sample_rate, ratio);
        fSampleRate = 48000;
    } else {
        fSampleRate = sample_rate;
    }
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (4.3087720323630099e-07 * fConst0);
	double fConst3 = (fConst2 + 0.97931789424465798);
	fConst4 = (0.0 - (0.97921484773852996 / fConst3));
	double fConst5 = (9.4417836379360192e-31 * fConst0);
	double fConst6 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + 3.0516402141914901e-24)) + 2.5556178881271499e-20)) + 6.7899919390762401e-16)) + 5.3898319044905903e-14)) + 6.6996614046825504e-11)) + 3.3372047119416801e-10);
	fConst7 = (fConst0 / fConst6);
	double fConst8 = (9.4416652478291698e-31 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + 3.4787480770110398e-24)) + 9.4232498304941602e-20)) + 7.2058668901501303e-16)) + 1.5402082244362001e-13)) + 6.6743257337363202e-11);
	fConst10 = (1.0 / fConst6);
	double fConst11 = (5.6650701827616098e-30 * fConst0);
	fConst12 = ((fConst0 * ((fConst0 * ((fConst1 * ((fConst0 * (-1.2206560856766e-23 - fConst11)) + -5.1112357762542902e-20)) + 1.07796638089812e-13)) + 2.6798645618730201e-10)) + 2.0023228271650098e-09);
	double fConst13 = (1.4162675456904e-29 * fConst0);
	fConst14 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst13 + 1.5258201070957399e-23)) + -2.5556178881271499e-20)) + -2.0369975817228701e-15)) + -5.3898319044905903e-14)) + 3.3498307023412798e-10)) + 5.0058070679125201e-09);
	fConst15 = ((fConst1 * ((fConst1 * (1.02224715525086e-19 - (1.8883567275872e-29 * fConst1))) + -2.1559327617962399e-13)) + 6.6744094238833601e-09);
	fConst16 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst13 + -1.5258201070957399e-23)) + -2.5556178881271499e-20)) + 2.0369975817228701e-15)) + -5.3898319044905903e-14)) + -3.3498307023412798e-10)) + 5.0058070679125201e-09);
	fConst17 = ((fConst0 * ((fConst0 * ((fConst1 * ((fConst0 * (1.2206560856766e-23 - fConst11)) + -5.1112357762542902e-20)) + 1.07796638089812e-13)) + -2.6798645618730201e-10)) + 2.0023228271650098e-09);
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + -3.0516402141914901e-24)) + 2.5556178881271499e-20)) + -6.7899919390762401e-16)) + 5.3898319044905903e-14)) + -6.6996614046825504e-11)) + 3.3372047119416801e-10);
	double fConst19 = (5.6649991486975001e-30 * fConst0);
	fConst20 = ((fConst0 * ((fConst1 * ((fConst0 * (-1.39149923080442e-23 - fConst19)) + -1.8846499660988301e-19)) + 3.0804164488724102e-13)) + 2.6697302934945302e-10);
	double fConst21 = (1.4162497871743799e-29 * fConst0);
	fConst22 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst21 + 1.73937403850552e-23)) + -9.4232498304941602e-20)) + -2.1617600670450401e-15)) + -1.5402082244362001e-13)) + 3.3371628668681602e-10);
	fConst23 = (fConst0 * ((fConst1 * (3.7692999321976602e-19 - (1.8883330495658301e-29 * fConst1))) + -6.1608328977448205e-13));
	fConst24 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst21 + -1.73937403850552e-23)) + -9.4232498304941602e-20)) + 2.1617600670450401e-15)) + -1.5402082244362001e-13)) + -3.3371628668681602e-10);
	fConst25 = ((fConst0 * ((fConst1 * ((fConst0 * (1.39149923080442e-23 - fConst19)) + -1.8846499660988301e-19)) + 3.0804164488724102e-13)) + -2.6697302934945302e-10);
	fConst26 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + -3.4787480770110398e-24)) + 9.4232498304941602e-20)) + -7.2058668901501303e-16)) + 1.5402082244362001e-13)) + -6.6743257337363202e-11);
	fConst27 = ((0.97931789424465798 - fConst2) / fConst3);
	double fConst28 = (7.0400571136071893e-21 * fConst0);
	fConst29 = ((fConst1 * (-8.0078455147435801e-15 - fConst28)) + 3.01449593071743e-09);
	double fConst30 = (2.2689898956886401e-20 * fConst0);
	fConst31 = ((fConst1 * (-2.5785659195546901e-14 - fConst30)) + 2.8336690626334099e-09);
	double fConst32 = (2.90899689459521e-20 * fConst0);
	fConst33 = ((fConst1 * (fConst32 + 3.3058822486064198e-14)) + -3.6329408758091402e-09);
	double fConst34 = (3.5509911478994701e-20 * fConst0);
	fConst35 = (fConst34 + 4.0437906149326201e-14);
	double fConst36 = (2.9106484818323203e-20 * fConst0);
	fConst37 = (-3.3145884355804401e-14 - fConst36);
	double fConst38 = (2.9106129719208402e-20 * fConst0);
	fConst39 = (-3.3145511993556e-14 - fConst38);
	double fConst40 = (2.2702767092803499e-20 * fConst0);
	fConst41 = (fConst40 + 2.5853531103439001e-14);
	double fConst42 = (7.1850090332444799e-21 * fConst0);
	fConst43 = ((fConst1 * (-8.1910225583183598e-15 - fConst42)) + 9.75088549859571e-08);
	double fConst44 = (7.0440682036892302e-21 * fConst0);
	fConst45 = ((fConst1 * (fConst44 + 8.0289386899708896e-15)) + -7.9925498511277097e-08);
	fConst46 = ((1.05600856704108e-20 * fConst1) + -1.7563131193709001e-11);
	fConst47 = ((3.4034848435329498e-20 * fConst1) + -3.3309268753080901e-12);
	fConst48 = (4.2704346619705603e-12 - (4.3634953418928202e-20 * fConst1));
	fConst49 = (1.9501505649412399e-10 - (5.3264867218491997e-20 * fConst1));
	fConst50 = ((4.3659727227484801e-20 * fConst1) + -1.59848695208376e-10);
	fConst51 = ((4.36591945788126e-20 * fConst1) + -1.5984689978980099e-10);
	fConst52 = (1.24680735435677e-10 - (3.4054150639205197e-20 * fConst1));
	fConst53 = ((1.07775135498667e-20 * fConst1) + -5.9678280830641404e-11);
	fConst54 = (5.5258291490493902e-11 - (1.05661023055338e-20 * fConst1));
	fConst55 = ((fConst1 * (8.0078455147435801e-15 - fConst28)) + -3.01449593071743e-09);
	fConst56 = ((fConst1 * (2.5785659195546901e-14 - fConst30)) + -2.8336690626334099e-09);
	fConst57 = ((fConst1 * (fConst32 + -3.3058822486064198e-14)) + 3.6329408758091402e-09);
	fConst58 = (fConst34 + -4.0437906149326201e-14);
	fConst59 = (3.3145884355804401e-14 - fConst36);
	fConst60 = (3.3145511993556e-14 - fConst38);
	fConst61 = (fConst40 + -2.5853531103439001e-14);
	fConst62 = ((fConst1 * (8.1910225583183598e-15 - fConst42)) + -9.75088549859571e-08);
	fConst63 = ((fConst1 * (fConst44 + -8.0289386899708896e-15)) + 7.9925498511277097e-08);
	double fConst64 = (1.7600142784018e-21 * fConst0);
	fConst65 = ((fConst0 * ((fConst0 * (fConst64 + -4.0039227573717901e-15)) + 8.7815655968545197e-12)) + -1.5072479653587101e-09);
	double fConst66 = (5.6724747392215897e-21 * fConst0);
	fConst67 = ((fConst0 * ((fConst0 * (fConst66 + -1.28928295977734e-14)) + 1.6654634376540501e-12)) + -1.4168345313167e-09);
	double fConst68 = (7.2724922364880296e-21 * fConst0);
	fConst69 = ((fConst0 * ((fConst0 * (1.6529411243032099e-14 - fConst68)) + -2.1352173309852801e-12)) + 1.8164704379045701e-09);
	double fConst70 = (8.8774778697486707e-21 * fConst0);
	fConst71 = ((fConst0 * (2.0218953074663101e-14 - fConst70)) + -9.7507528247061804e-11);
	double fConst72 = (7.2766212045808007e-21 * fConst0);
	fConst73 = ((fConst0 * (fConst72 + -1.6572942177902201e-14)) + 7.9924347604188206e-11);
	double fConst74 = (7.2765324298021004e-21 * fConst0);
	fConst75 = ((fConst0 * (fConst74 + -1.6572755996778e-14)) + 7.9923449894900598e-11);
	double fConst76 = (5.67569177320088e-21 * fConst0);
	fConst77 = ((fConst0 * (1.2926765551719501e-14 - fConst76)) + -6.2340367717838696e-11);
	double fConst78 = (1.79625225831112e-21 * fConst0);
	fConst79 = ((fConst0 * ((fConst0 * (fConst78 + -4.0955112791591799e-15)) + 2.9839140415320702e-11)) + -4.8754427492978497e-08);
	double fConst80 = (1.7610170509223102e-21 * fConst0);
	fConst81 = ((fConst0 * ((fConst0 * (4.0144693449854503e-15 - fConst80)) + -2.7629145745247e-11)) + 3.9962749255638601e-08);
	fConst82 = ((fConst0 * ((fConst0 * (fConst64 + 4.0039227573717901e-15)) + 8.7815655968545197e-12)) + 1.5072479653587101e-09);
	fConst83 = ((fConst0 * ((fConst0 * (fConst66 + 1.28928295977734e-14)) + 1.6654634376540501e-12)) + 1.4168345313167e-09);
	fConst84 = ((fConst0 * ((fConst0 * (-1.6529411243032099e-14 - fConst68)) + -2.1352173309852801e-12)) + -1.8164704379045701e-09);
	fConst85 = ((fConst0 * (-2.0218953074663101e-14 - fConst70)) + -9.7507528247061804e-11);
	fConst86 = ((fConst0 * (fConst72 + 1.6572942177902201e-14)) + 7.9924347604188206e-11);
	fConst87 = ((fConst0 * (fConst74 + 1.6572755996778e-14)) + 7.9923449894900598e-11);
	fConst88 = ((fConst0 * (-1.2926765551719501e-14 - fConst76)) + -6.2340367717838696e-11);
	fConst89 = ((fConst0 * ((fConst0 * (fConst78 + 4.0955112791591799e-15)) + 2.9839140415320702e-11)) + 4.8754427492978497e-08);
	fConst90 = ((fConst0 * ((fConst0 * (-4.0144693449854503e-15 - fConst80)) + -2.7629145745247e-11)) + -3.9962749255638601e-08);
	double fConst91 = (1.60067201269546e-22 * fConst0);
	fConst92 = ((fConst0 * ((fConst0 * (fConst91 + 4.4756157832158003e-16)) + 1.0517807941630899e-11)) + 9.89915928390436e-09);
	double fConst93 = (7.2723307898573293e-21 * fConst0);
	fConst94 = ((fConst0 * ((fConst0 * (fConst93 + 2.3803403143178002e-14)) + 2.0187473560497501e-11)) + 2.2160438587292599e-09);
	double fConst95 = (7.2724035138924704e-21 * fConst0);
	fConst96 = ((fConst0 * ((fConst0 * (-2.0167403060262301e-14 - fConst95)) + -1.97181527174289e-11)) + -1.8164442812885799e-09);
	double fConst97 = (7.2765484398241294e-21 * fConst0);
	fConst98 = ((fConst0 * (-1.29345022318831e-14 - fConst97)) + -6.2340367733824194e-11);
	fConst99 = ((fConst0 * (fConst97 + 1.65727764517951e-14)) + 7.9923548376697702e-11);
	double fConst100 = (7.2764756743397304e-21 * fConst0);
	fConst101 = ((fConst0 * (fConst100 + 1.6572647106772799e-14)) + 7.9922924973020298e-11);
	fConst102 = ((fConst0 * (-2.02108849439427e-14 - fConst100)) + -9.7505929784087401e-11);
	double fConst103 = (1.6015843200118599e-22 * fConst0);
	fConst104 = ((fConst0 * ((fConst0 * (fConst103 + 2.88365933059091e-16)) + 7.8396168289614906e-12)) + 3.1170495568750797e-08);
	fConst105 = ((fConst0 * ((fConst0 * (-3.6844514905968301e-16 - fConst103)) + -1.0045781804538e-11)) + -3.99621738060907e-08);
	double fConst106 = (6.4026880507818599e-22 * fConst0);
	fConst107 = ((fConst1 * (-8.9512315664316104e-16 - fConst106)) + 1.97983185678087e-08);
	double fConst108 = (2.9089323159429299e-20 * fConst0);
	fConst109 = ((fConst1 * (-4.7606806286355902e-14 - fConst108)) + 4.4320877174585197e-09);
	double fConst110 = (2.90896140555699e-20 * fConst0);
	fConst111 = ((fConst1 * (fConst110 + 4.0334806120524702e-14)) + -3.6328885625771702e-09);
	double fConst112 = (2.9106193759296499e-20 * fConst0);
	fConst113 = (fConst112 + 2.5869004463766101e-14);
	fConst114 = (-3.3145552903590199e-14 - fConst112);
	double fConst115 = (2.9105902697358897e-20 * fConst0);
	fConst116 = (-3.3145294213545598e-14 - fConst115);
	fConst117 = (fConst115 + 4.0421769887885299e-14);
	double fConst118 = (6.4063372800474302e-22 * fConst0);
	fConst119 = ((fConst1 * (-5.7673186611818101e-16 - fConst118)) + 6.2340991137501501e-08);
	fConst120 = ((fConst1 * (fConst118 + 7.3689029811936702e-16)) + -7.9924347612181399e-08);
	fConst121 = ((9.6040320761727809e-22 * fConst1) + -2.1035615883261798e-11);
	fConst122 = ((4.3633984739144e-20 * fConst1) + -4.0374947120995002e-11);
	fConst123 = (3.94363054348578e-11 - (4.3634421083354798e-20 * fConst1));
	double fConst124 = (4.36592906389448e-20 * fConst1);
	fConst125 = (1.24680735467648e-10 - fConst124);
	fConst126 = (fConst124 + -1.5984709675339499e-10);
	double fConst127 = (4.3658854046038397e-20 * fConst1);
	fConst128 = (fConst127 + -1.5984584994604101e-10);
	fConst129 = (1.9501185956817501e-10 - fConst127);
	double fConst130 = (9.6095059200711491e-22 * fConst1);
	fConst131 = (fConst130 + -1.5679233657923001e-11);
	fConst132 = (2.0091563609076e-11 - fConst130);
	fConst133 = ((fConst1 * (8.9512315664316104e-16 - fConst106)) + -1.97983185678087e-08);
	fConst134 = ((fConst1 * (4.7606806286355902e-14 - fConst108)) + -4.4320877174585197e-09);
	fConst135 = ((fConst1 * (fConst110 + -4.0334806120524702e-14)) + 3.6328885625771702e-09);
	fConst136 = (fConst112 + -2.5869004463766101e-14);
	fConst137 = (3.3145552903590199e-14 - fConst112);
	fConst138 = (3.3145294213545598e-14 - fConst115);
	fConst139 = (fConst115 + -4.0421769887885299e-14);
	fConst140 = ((fConst1 * (5.7673186611818101e-16 - fConst118)) + -6.2340991137501501e-08);
	fConst141 = ((fConst1 * (fConst118 + -7.3689029811936702e-16)) + 7.9924347612181399e-08);
	fConst142 = ((fConst0 * ((fConst0 * (fConst91 + -4.4756157832158003e-16)) + 1.0517807941630899e-11)) + -9.89915928390436e-09);
	fConst143 = ((fConst0 * ((fConst0 * (fConst93 + -2.3803403143178002e-14)) + 2.0187473560497501e-11)) + -2.2160438587292599e-09);
	fConst144 = ((fConst0 * ((fConst0 * (2.0167403060262301e-14 - fConst95)) + -1.97181527174289e-11)) + 1.8164442812885799e-09);
	fConst145 = ((fConst0 * (1.29345022318831e-14 - fConst97)) + -6.2340367733824194e-11);
	fConst146 = ((fConst0 * (fConst97 + -1.65727764517951e-14)) + 7.9923548376697702e-11);
	fConst147 = ((fConst0 * (fConst100 + -1.6572647106772799e-14)) + 7.9922924973020298e-11);
	fConst148 = ((fConst0 * (2.02108849439427e-14 - fConst100)) + -9.7505929784087401e-11);
	fConst149 = ((fConst0 * ((fConst0 * (fConst103 + -2.88365933059091e-16)) + 7.8396168289614906e-12)) + -3.1170495568750797e-08);
	fConst150 = ((fConst0 * ((fConst0 * (3.6844514905968301e-16 - fConst103)) + -1.0045781804538e-11)) + 3.99621738060907e-08);
	double fConst151 = (9.2936496343283305e-31 * fConst0);
	fConst152 = ((fConst0 * ((fConst1 * ((fConst0 * (-1.06644965032738e-25 - fConst151)) + -2.2530250529806201e-21)) + 2.88937273789334e-16)) + 3.40910044884256e-15);
	double fConst153 = (4.2234296913936001e-29 * fConst0);
	fConst154 = ((fConst0 * ((fConst1 * ((fConst0 * (-3.9221403182882201e-24 - fConst153)) + -4.9249274848424202e-20)) + 1.98425395320685e-17)) + 7.5857413305164699e-17);
	double fConst155 = (4.7982649833695701e-28 * fConst0);
	fConst156 = (fConst0 * ((fConst1 * ((fConst0 * (-3.4058360249855198e-23 - fConst155)) + -1.5573881049312799e-21)) + 5.9320297842186001e-20));
	fConst157 = mydsp_faustpower3_f(fConst0);
	double fConst158 = (4.19467819701782e-34 * fConst0);
	fConst159 = ((fConst0 * (fConst158 + 1.71187870665812e-26)) + 1.8148178813897101e-21);
	double fConst160 = (9.5333595386768694e-33 * fConst0);
	fConst161 = ((fConst0 * (fConst160 + 3.8888719017657498e-25)) + 4.1227121340066e-20);
	double fConst162 = (2.3234124085820799e-30 * fConst0);
	fConst163 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst162 + 1.33306206290922e-25)) + -1.12651252649031e-21)) + -1.4253701773974901e-17)) + -1.44468636894667e-16)) + 4.2613755610532002e-15);
	double fConst164 = (1.0558574228484e-28 * fConst0);
	fConst165 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst164 + 4.90267539786028e-24)) + -2.4624637424212101e-20)) + -2.3266525652338e-18)) + -9.9212697660342607e-18)) + 9.4821766631455905e-17);
	double fConst166 = (1.19956624584239e-27 * fConst0);
	fConst167 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst166 + 4.2572950312319001e-23)) + -7.78694052465638e-22)) + -4.4355659165854498e-20)) + -2.9660148921093001e-20));
	double fConst168 = (1.04866954925446e-33 * fConst0);
	fConst169 = ((fConst0 * (-2.1398483833226501e-26 - fConst168)) + 9.0740894069485297e-22);
	fConst170 = ((fConst0 * fConst169) + -1.34496199446404e-34);
	double fConst171 = (2.38333988466922e-32 * fConst0);
	fConst172 = ((fConst0 * (-4.8610898772071904e-25 - fConst171)) + 2.0613560670033e-20);
	fConst173 = ((fConst0 * fConst172) + -3.0553430133213101e-33);
	fConst174 = ((fConst1 * (4.5060501059612499e-21 - (3.09788321144278e-30 * fConst1))) + -5.7787454757866899e-16);
	fConst175 = ((fConst1 * (9.8498549696848403e-20 - (1.4078098971312e-28 * fConst1))) + -3.9685079064137e-17);
	fConst176 = ((fConst1 * (3.1147762098625501e-21 - (1.59942166112319e-27 * fConst1))) + -1.18640595684372e-19);
	fConst177 = ((1.3982260656726099e-33 * fConst1) + -3.6296357627794104e-21);
	fConst178 = ((3.1777865128922901e-32 * fConst1) + -8.2454242680132096e-20);
	fConst179 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst162 + -1.33306206290922e-25)) + -1.12651252649031e-21)) + 1.4253701773974901e-17)) + -1.44468636894667e-16)) + -4.2613755610532002e-15);
	fConst180 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst164 + -4.90267539786028e-24)) + -2.4624637424212101e-20)) + 2.3266525652338e-18)) + -9.9212697660342607e-18)) + -9.4821766631455905e-17);
	fConst181 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst166 + -4.2572950312319001e-23)) + -7.78694052465638e-22)) + 4.4355659165854498e-20)) + -2.9660148921093001e-20));
	fConst182 = ((fConst0 * (2.1398483833226501e-26 - fConst168)) + 9.0740894069485297e-22);
	fConst183 = ((fConst0 * fConst182) + 1.34496199446404e-34);
	fConst184 = ((fConst0 * (4.8610898772071904e-25 - fConst171)) + 2.0613560670033e-20);
	fConst185 = ((fConst0 * fConst184) + 3.0553430133213101e-33);
	fConst186 = ((fConst0 * ((fConst1 * ((fConst0 * (1.06644965032738e-25 - fConst151)) + -2.2530250529806201e-21)) + 2.88937273789334e-16)) + -3.40910044884256e-15);
	fConst187 = ((fConst0 * ((fConst1 * ((fConst0 * (3.9221403182882201e-24 - fConst153)) + -4.9249274848424202e-20)) + 1.98425395320685e-17)) + -7.5857413305164699e-17);
	fConst188 = (fConst0 * ((fConst1 * ((fConst0 * (3.4058360249855198e-23 - fConst155)) + -1.5573881049312799e-21)) + 5.9320297842186001e-20));
	fConst189 = ((fConst0 * (fConst158 + -1.71187870665812e-26)) + 1.8148178813897101e-21);
	fConst190 = ((fConst0 * (fConst160 + -3.8888719017657498e-25)) + 4.1227121340066e-20);
	double fConst191 = (1.54894160572139e-31 * fConst0);
	fConst192 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst191 + -2.6661241258184403e-26)) + 1.12651252649031e-21)) + -4.7512339246582902e-18)) + 1.44468636894667e-16)) + -8.52275112210641e-16);
	double fConst193 = (7.0390494856559904e-30 * fConst0);
	fConst194 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst193 + -9.8053507957205596e-25)) + 2.4624637424212101e-20)) + -7.7555085507793196e-19)) + 9.9212697660342607e-18)) + -1.8964353326291199e-17);
	double fConst195 = (7.9971083056159505e-29 * fConst0);
	fConst196 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst195 + -8.5145900624637996e-24)) + 7.78694052465638e-22)) + -1.47852197219515e-20)) + 2.9660148921093001e-20));
	double fConst197 = (6.9911303283630398e-35 * fConst0);
	fConst198 = ((fConst0 * (4.2796967666453101e-27 - fConst197)) + -9.0740894069485297e-22);
	fConst199 = ((fConst0 * fConst198) + -4.4832066482134701e-35);
	double fConst200 = (1.5888932564461401e-33 * fConst0);
	fConst201 = ((fConst0 * (9.7221797544143698e-26 - fConst200)) + -2.0613560670033e-20);
	fConst202 = ((fConst0 * fConst201) + -1.0184476711071e-33);
	fConst203 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst191 + 2.6661241258184403e-26)) + 1.12651252649031e-21)) + 4.7512339246582902e-18)) + 1.44468636894667e-16)) + 8.52275112210641e-16);
	fConst204 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst193 + 9.8053507957205596e-25)) + 2.4624637424212101e-20)) + 7.7555085507793196e-19)) + 9.9212697660342607e-18)) + 1.8964353326291199e-17);
	fConst205 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst195 + 8.5145900624637996e-24)) + 7.78694052465638e-22)) + 1.47852197219515e-20)) + 2.9660148921093001e-20));
	fConst206 = ((fConst0 * (-4.2796967666453101e-27 - fConst197)) + -9.0740894069485297e-22);
	fConst207 = ((fConst0 * fConst206) + 4.4832066482134701e-35);
	fConst208 = ((fConst0 * (-9.7221797544143698e-26 - fConst200)) + -2.0613560670033e-20);
	fConst209 = ((fConst0 * fConst208) + 1.0184476711071e-33);
	double fConst210 = (7.0142010584466404e-35 * fConst0);
	fConst211 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst210 + -1.21840999977658e-26)) + -1.74095101616584e-22)) + -4.7325256235815704e-18)) + -4.7082656768348503e-17)) + -1.1712397241167799e-16);
	double fConst212 = (1.5941366041924201e-33 * fConst0);
	fConst213 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst212 + -6.5128358242887097e-25)) + -3.9879477801707701e-21)) + -3.7833348396828302e-19)) + -1.7826268601057401e-18);
	double fConst214 = (8.5074553512784105e-24 * fConst0);
	fConst215 = (fConst0 * ((fConst0 * (-6.0354236449383803e-22 - fConst214)) + -2.7880190392875799e-21));
	double fConst216 = (4.2085206350679797e-34 * fConst0);
	fConst217 = ((fConst0 * ((fConst1 * ((fConst0 * (4.8736399991063297e-26 - fConst216)) + 3.4819020323316701e-22)) + -9.4165313536697006e-17)) + -4.6849588964671098e-16);
	double fConst218 = (9.5648196251544994e-33 * fConst0);
	fConst219 = ((fConst1 * ((fConst0 * (2.6051343297154901e-24 - fConst218)) + 7.9758955603415402e-21)) + -3.5652537202114702e-18);
	double fConst220 = (3.4029821405113701e-23 * fConst0);
	fConst221 = (fConst1 * (fConst220 + 1.20708472898768e-21));
	double fConst222 = (1.0521301587669999e-33 * fConst0);
	fConst223 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst222 + -6.0920499988829198e-26)) + 1.74095101616584e-22)) + 1.41975768707447e-17)) + 4.7082656768348503e-17)) + -5.8561986205838902e-16);
	double fConst224 = (2.3912049062886301e-32 * fConst0);
	fConst225 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst224 + -3.2564179121443601e-24)) + 3.9879477801707701e-21)) + 1.1350004519048499e-18)) + 1.7826268601057401e-18);
	double fConst226 = (4.2537276756392101e-23 * fConst0);
	fConst227 = (fConst0 * ((fConst0 * (6.0354236449383803e-22 - fConst226)) + 8.3640571178627402e-21));
	fConst228 = ((fConst1 * (-6.9638040646633403e-22 - (1.40284021168933e-33 * fConst1))) + 1.8833062707339401e-16);
	fConst229 = ((fConst1 * (-1.5951791120683101e-20 - (3.1882732083848299e-32 * fConst1))) + 7.1305074404229496e-18);
	fConst230 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst222 + 6.0920499988829198e-26)) + 1.74095101616584e-22)) + -1.41975768707447e-17)) + 4.7082656768348503e-17)) + 5.8561986205838902e-16);
	fConst231 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst224 + 3.2564179121443601e-24)) + 3.9879477801707701e-21)) + -1.1350004519048499e-18)) + 1.7826268601057401e-18);
	fConst232 = (fConst0 * ((fConst0 * (fConst226 + 6.0354236449383803e-22)) + -8.3640571178627402e-21));
	fConst233 = ((fConst0 * ((fConst1 * ((fConst0 * (-4.8736399991063297e-26 - fConst216)) + 3.4819020323316701e-22)) + -9.4165313536697006e-17)) + 4.6849588964671098e-16);
	fConst234 = ((fConst1 * ((fConst0 * (-2.6051343297154901e-24 - fConst218)) + 7.9758955603415402e-21)) + -3.5652537202114702e-18);
	fConst235 = (fConst1 * (1.20708472898768e-21 - fConst220));
	fConst236 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst210 + 1.21840999977658e-26)) + -1.74095101616584e-22)) + 4.7325256235815704e-18)) + -4.7082656768348503e-17)) + 1.1712397241167799e-16);
	fConst237 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst212 + 6.5128358242887097e-25)) + -3.9879477801707701e-21)) + 3.7833348396828302e-19)) + -1.7826268601057401e-18);
	fConst238 = (fConst0 * ((fConst0 * (fConst214 + -6.0354236449383803e-22)) + 2.7880190392875799e-21));
	fConst239 = (3.8841113779793501e-10 * fConst1);
	fConst240 = (7.7093564379726002e-10 * fConst1);
	double fConst241 = (3.8546782189863001e-10 * fConst0);
	fConst242 = (fConst241 + -3.8681053643969802e-10);
	double fConst243 = (1.9420556889896701e-10 * fConst0);
	fConst244 = (fConst243 + -9.6971419202025294e-11);
	fConst245 = (9.6971419202025294e-11 - fConst243);
	fConst246 = (fConst241 + 3.8681053643969802e-10);
	fConst247 = (fConst243 + 9.6971419202025294e-11);
	fConst248 = (-9.6971419202025294e-11 - fConst243);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
    float* buffer = input0;
	int downcount = count/ratio ;
	FAUSTFLOAT buf[downcount];
	memset(buf, 0, downcount*sizeof(float));
    if (ratio > 1) {
        smp.down(downcount, input0, buf);
        buffer = buf;
    } else {
        
        downcount = count;
    }
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	double fSlow2 = (0.00036676987543879196 * (std::exp((3.0 * (1.0 - double(fVslider2)))) + -1.0));
	double fSlow3 = (0.0070000000000000062 * double(fVslider3));
	double fSlow4 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider4))) + -1.0));
	for (int i0 = 0; (i0 < downcount); i0 = (i0 + 1)) {
		fRec4[0] = (double(buffer[i0]) - (fConst10 * ((((((fConst12 * fRec4[1]) + (fConst14 * fRec4[2])) + (fConst15 * fRec4[3])) + (fConst16 * fRec4[4])) + (fConst17 * fRec4[5])) + (fConst18 * fRec4[6]))));
		fRec3[0] = ((fConst7 * (((((((fConst9 * fRec4[0]) + (fConst20 * fRec4[1])) + (fConst22 * fRec4[2])) + (fConst23 * fRec4[3])) + (fConst24 * fRec4[4])) + (fConst25 * fRec4[5])) + (fConst26 * fRec4[6]))) - (fConst27 * fRec3[1]));
		fRec5[0] = (fSlow0 + (0.99299999999999999 * fRec5[1]));
		fRec6[0] = (fSlow1 + (0.99299999999999999 * fRec6[1]));
		double fTemp0 = ((fConst0 * (fConst82 + ((fRec5[0] * (fConst83 + ((fRec5[0] * (fConst84 + (fConst0 * (fRec6[0] * (fConst85 + (fConst86 * fRec6[0])))))) + (fConst0 * (fRec6[0] * (fConst87 + (fConst88 * fRec6[0]))))))) + (fRec6[0] * (fConst89 + (fConst90 * fRec6[0])))))) + 9.0824829748189304e-07);
		fRec2[0] = ((fConst4 * (fRec3[0] + fRec3[1])) - (((((fRec2[1] * ((fConst0 * (fConst29 + ((fRec5[0] * (fConst31 + ((fRec5[0] * (fConst33 + (fConst1 * (fRec6[0] * (fConst35 + (fConst37 * fRec6[0])))))) + (fConst1 * (fRec6[0] * (fConst39 + (fConst41 * fRec6[0]))))))) + (fRec6[0] * (fConst43 + (fConst45 * fRec6[0])))))) + 3.6329931899275701e-06)) + (fRec2[2] * ((fConst1 * (fConst46 + ((fRec5[0] * (fConst47 + ((fRec5[0] * (fConst48 + (fRec6[0] * (fConst49 + (fConst50 * fRec6[0]))))) + (fRec6[0] * (fConst51 + (fConst52 * fRec6[0])))))) + (fRec6[0] * (fConst53 + (fConst54 * fRec6[0])))))) + 5.4494897848913602e-06))) + (fRec2[3] * ((fConst0 * (fConst55 + ((fRec5[0] * (fConst56 + ((fRec5[0] * (fConst57 + (fConst1 * (fRec6[0] * (fConst58 + (fConst59 * fRec6[0])))))) + (fConst1 * (fRec6[0] * (fConst60 + (fConst61 * fRec6[0]))))))) + (fRec6[0] * (fConst62 + (fConst63 * fRec6[0])))))) + 3.6329931899275701e-06))) + (fRec2[4] * ((fConst0 * (fConst65 + ((fRec5[0] * (fConst67 + ((fRec5[0] * (fConst69 + (fConst0 * (fRec6[0] * (fConst71 + (fConst73 * fRec6[0])))))) + (fConst0 * (fRec6[0] * (fConst75 + (fConst77 * fRec6[0]))))))) + (fRec6[0] * (fConst79 + (fConst81 * fRec6[0])))))) + 9.0824829748189304e-07))) / fTemp0));
		fRec7[0] = (fSlow2 + (0.99299999999999999 * fRec7[1]));
		fRec8[0] = (fSlow3 + (0.99299999999999999 * fRec8[1]));
		double fTemp1 = (fRec8[0] * (fConst159 + (fConst161 * fRec7[0])));
		double fTemp2 = (fConst1 * (fRec8[0] * (fConst177 + (fConst178 * fRec7[0]))));
		double fTemp3 = (fRec8[0] * (fConst189 + (fConst190 * fRec7[0])));
		double fTemp4 = ((fConst0 * (fConst203 + ((fRec7[0] * (fConst204 + (fConst205 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst207 + (fConst209 * fRec7[0]))))))) + 1.24601533024252e-15);
		fRec1[0] = (((((((fRec2[0] * ((fConst0 * (fConst92 + ((fRec5[0] * (fConst94 + ((fRec5[0] * (fConst96 + (fConst0 * (fRec6[0] * (fConst98 + (fConst99 * fRec6[0])))))) + (fConst0 * (fRec6[0] * (fConst101 + (fConst102 * fRec6[0]))))))) + (fRec6[0] * (fConst104 + (fConst105 * fRec6[0])))))) + 9.0823122286569797e-07)) + (fRec2[1] * ((fConst0 * (fConst107 + ((fRec5[0] * (fConst109 + ((fRec5[0] * (fConst111 + (fConst1 * (fRec6[0] * (fConst113 + (fConst114 * fRec6[0])))))) + (fConst1 * (fRec6[0] * (fConst116 + (fConst117 * fRec6[0]))))))) + (fRec6[0] * (fConst119 + (fConst120 * fRec6[0])))))) + 3.6329248914627902e-06))) + (fRec2[2] * ((fConst1 * (fConst121 + ((fRec5[0] * (fConst122 + ((fRec5[0] * (fConst123 + (fRec6[0] * (fConst125 + (fConst126 * fRec6[0]))))) + (fRec6[0] * (fConst128 + (fConst129 * fRec6[0])))))) + (fRec6[0] * (fConst131 + (fConst132 * fRec6[0])))))) + 5.4493873371941899e-06))) + (fRec2[3] * ((fConst0 * (fConst133 + ((fRec5[0] * (fConst134 + ((fRec5[0] * (fConst135 + (fConst1 * (fRec6[0] * (fConst136 + (fConst137 * fRec6[0])))))) + (fConst1 * (fRec6[0] * (fConst138 + (fConst139 * fRec6[0]))))))) + (fRec6[0] * (fConst140 + (fConst141 * fRec6[0])))))) + 3.6329248914627902e-06))) + (fRec2[4] * ((fConst0 * (fConst142 + ((fRec5[0] * (fConst143 + ((fRec5[0] * (fConst144 + (fConst0 * (fRec6[0] * (fConst145 + (fConst146 * fRec6[0])))))) + (fConst0 * (fRec6[0] * (fConst147 + (fConst148 * fRec6[0]))))))) + (fRec6[0] * (fConst149 + (fConst150 * fRec6[0])))))) + 9.0823122286569797e-07))) / fTemp0) - (((((((fRec1[1] * ((fConst0 * (fConst152 + ((fRec7[0] * (fConst154 + (fConst156 * fRec7[0]))) + (fConst157 * fTemp1)))) + 7.4760919814551297e-15)) + (fRec1[2] * ((fConst0 * (fConst163 + ((fRec7[0] * (fConst165 + (fConst167 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst170 + (fConst173 * fRec7[0]))))))) + 1.8690229953637799e-14))) + (fRec1[3] * ((fConst1 * (fConst174 + ((fRec7[0] * (fConst175 + (fConst176 * fRec7[0]))) + fTemp2))) + 2.4920306604850401e-14))) + (fRec1[4] * ((fConst0 * (fConst179 + ((fRec7[0] * (fConst180 + (fConst181 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst183 + (fConst185 * fRec7[0]))))))) + 1.8690229953637799e-14))) + (fRec1[5] * ((fConst0 * (fConst186 + ((fRec7[0] * (fConst187 + (fConst188 * fRec7[0]))) + (fConst157 * fTemp3)))) + 7.4760919814551297e-15))) + (fRec1[6] * ((fConst0 * (fConst192 + ((fRec7[0] * (fConst194 + (fConst196 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst199 + (fConst202 * fRec7[0]))))))) + 1.24601533024252e-15))) / fTemp4));
		fRec9[0] = (fSlow4 + (0.99299999999999999 * fRec9[1]));
		double fTemp5 = ((fConst0 * (fConst246 + (fRec9[0] * (fConst247 + (fConst248 * fRec9[0]))))) + 9.6971419202025294e-11);
		fRec0[0] = ((fConst0 * ((((((((fRec1[0] * (fConst211 + (fConst0 * ((fRec7[0] * (fConst213 + (fConst215 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst206 + (fConst208 * fRec7[0])))))))) + (fRec1[1] * (fConst217 + (fConst0 * ((fRec7[0] * (fConst219 + (fConst221 * fRec7[0]))) + (fConst1 * fTemp1)))))) + (fRec1[2] * (fConst223 + (fConst0 * ((fRec7[0] * (fConst225 + (fConst227 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst169 + (fConst172 * fRec7[0]))))))))) + (fConst0 * (fRec1[3] * (fConst228 + (fTemp2 + (fRec7[0] * (fConst229 + (fConst1 * (0.0 - (2.4141694579753499e-21 * fRec7[0])))))))))) + (fRec1[4] * (fConst230 + (fConst0 * ((fRec7[0] * (fConst231 + (fConst232 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst182 + (fConst184 * fRec7[0]))))))))) + (fRec1[5] * (fConst233 + (fConst0 * ((fRec7[0] * (fConst234 + (fConst235 * fRec7[0]))) + (fConst1 * fTemp3)))))) + (fRec1[6] * (fConst236 + (fConst0 * ((fRec7[0] * (fConst237 + (fConst238 * fRec7[0]))) + (fConst1 * (fRec8[0] * (fConst198 + (fConst201 * fRec7[0]))))))))) / fTemp4)) - (((fRec0[1] * (((fRec9[0] * (0.0 - (fConst239 * (1.0 - fRec9[0])))) + 1.93942838404051e-10) - fConst240)) + (fRec0[2] * ((fConst0 * (fConst242 + (fRec9[0] * (fConst244 + (fConst245 * fRec9[0]))))) + 9.6971419202025294e-11))) / fTemp5));
		buffer[i0] = FAUSTFLOAT((fConst1 * ((((fRec0[1] * (0.0 - (7.6526213381953903e-10 * fRec9[0]))) + (3.8263106690976998e-10 * (fRec9[0] * fRec0[0]))) + (3.8263106690976998e-10 * (fRec9[0] * fRec0[2]))) / fTemp5)));
		for (int j0 = 6; (j0 > 0); j0 = (j0 - 1)) {
			fRec4[j0] = fRec4[(j0 - 1)];
		}
		fRec3[1] = fRec3[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		for (int j1 = 4; (j1 > 0); j1 = (j1 - 1)) {
			fRec2[j1] = fRec2[(j1 - 1)];
		}
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		for (int j2 = 6; (j2 > 0); j2 = (j2 - 1)) {
			fRec1[j2] = fRec1[(j2 - 1)];
		}
		fRec9[1] = fRec9[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
    if (ratio > 1) {
        smp.up(downcount, buf, output0);
    }
}


void Dsp::connect(uint32_t port, float data)
{
	switch (port)
	{
	case PluginMetalTone::HIGH: 
		fVslider0 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginMetalTone::LEVEL: 
		fVslider4 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginMetalTone::LOWS: 
		fVslider1 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginMetalTone::MIDFREQ: 
		fVslider2 = data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PluginMetalTone::MIDDLE: 
		fVslider3 = data; // , 0.5, 0.0, 1.0, 0.01 
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
} // end namespace metaltone_post
