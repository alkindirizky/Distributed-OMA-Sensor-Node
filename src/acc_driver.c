#include "acc_driver.h"
#include "procsetting.h"
#include "testsetting.h"

#define FIFO_SIZE 32
#define MAX_G 4

//------------------- dummy data
#ifdef TESTPEAK5
static const float dumsignal[SIGNAL_SIZE] = { //data with 5 peaks in PSD
        -0.049737,2.3708,3.9373,4.0391,3.0132,1.932,0.98747,0.6794,0.69222,0.40872,-0.43811,-1.2854,-2.2636,-2.2861,-1.8516,-1.3326,-0.74945,-0.82201,-1.063,-0.83472,0.13943,1.6654,2.8003,3.0952,2.2316,0.53163,-1.1643,-1.9396,-1.6631,-0.62389,0.57511,1.1927,0.92477,0.16233,-0.38506,-0.5559,-0.36728,-0.14504,-0.24769,-0.78922,-1.1633,-1.0105,-0.41636,0.68311,1.2252,1.0732,0.12352,-0.62972,-1.025,-0.38465,0.95451,2.2038,2.494,1.6919,0.1455,-1.3749,-2.0898,-1.7822,-1.0373,-0.25795,0.15192,0.10221,-0.012971,0.095839,0.43587,0.7133,0.52151,-0.45661,-1.3023,-1.557,-1.1597,0.10147,1.6155,2.2399,2.0051,0.96393,-0.26281,-0.7549,-0.39287,0.43787,1.0355,1.0106,-0.033716,-1.3481,-2.4702,-2.7534,-2.3945,-1.7623,-1.1226,-0.55269,0.028378,1.179,2.4886,3.8118,4.2758,3.5424,1.8394,-0.17836,-1.7318,-2.2369,-1.7593,-1.1352,-0.99503,-1.5606,-2.4048,-2.9095,-2.3931,-1.1562,0.67207,2.0327,2.8083,2.8538,2.4347,2.0641,1.7759,1.3179,0.43457,-0.92832,-2.2062,-2.9275,-2.6082,-1.3347,0.25638,1.0381,0.97,0.052257,-1.107,-1.3911,-0.86122,0.24986,1.3056,1.7246,1.1517,0.17778,-0.52476,-0.49456,-0.14926,0.23578,0.39219,0.1759,-0.015257,0.069255,0.48354,0.98157,1.1065,0.4242,-1.0572,-2.3978,-2.8957,-2.2625,-0.58608,1.1054,1.8425,1.7406,0.89595,-0.1453,-0.58721,-0.29074,0.28248,0.80613,0.78338,0.21655,-0.13255,-0.25742,0.12245,0.45142,0.41098,-0.20108,-1.0067,-1.3396,-0.97719,-0.01618,1.0229,1.2944,0.43394,-0.9397,-2.2432,-2.4944,-1.7698,-0.026723,1.6246,2.6427,2.9378,2.2375,1.6196,1.0577,0.80948,0.30147,-0.6037,-1.5053,-2.5978,-2.9892,-2.4902,-1.4523,-0.71927,-0.35332,-0.6735,-0.88488,-0.28333,0.88482,2.8994,4.4334,4.6903,3.6653,1.6718,-0.60153,-2.068,-2.6068,-2.5053,-2.0278,-2.0337,-1.9041,-1.7276,-0.99845,0.13116,1.1653,1.5316,1.3994,0.74382,0.29035,0.54976,1.2482,2.0429,1.9371,1.0617,-0.57882,-2.0488,-2.5749,-2.0748,-0.61551,0.67646,1.3084,1.0513,0.29209,-0.54029,-0.75939,-0.63391,-0.52025,-0.38096,-0.73227,-0.84299,-0.32984,0.52423,1.5685,2.1364,1.9279,0.63672,-0.60607,-1.2885,-1.0597,0.011875,0.96932,1.3156,0.58804,-0.66071,-1.832,-2.2246,-1.5925,-0.5189,0.50699,0.83611,0.68824,0.41647,0.41795,0.54197,0.6226,0.49502,-0.28145,-0.95383,-1.218,-0.62537,0.64319,2.0446,2.7258,2.1404,0.53815,-1.0461,-2.0211,-2.0589,-1.2077,-0.61535,-0.36579,-0.7168,-1.3309,-1.6525,-1.0695,-0.12413,0.93876,1.729,1.9573,1.9178,2.0527,2.4847,2.5777,1.9908,0.62461,-1.5471,-3.6707,-4.63,-4.3879,-2.8583,-1.0132,0.38556,0.91081,0.67856,0.46241,0.73258,1.5053,2.4711,2.8774,2.6605,1.6074,0.40593,-0.32747,-0.79029,-1.0568,-1.5355,-2.2877,-2.8937,-2.767,-1.6836,-0.070099,1.7325,2.6335,2.2623,1.0109,-0.4525,-1.2453,-1.0368,-0.11656,0.9941,1.3075,1.0189,0.30947,-0.35118,-0.47946,-0.18392,0.21814,0.13743,-0.23842,-0.75923,-0.75891,-0.32508,0.36611,0.6112,0.071369,-0.86252,-1.9377,-2.0624,-1.119,0.54032,2.2028,2.8242,2.5141,1.0958,-0.28399,-1.0295,-1.2028,-0.51711,-0.0067537,0.099876,-0.08365,-0.38684,-0.27246,0.22961,0.53819,0.39582,-0.33269,-1.2665,-1.6897,-1.3595,-0.30375,0.89106,1.5111,1.0181,-0.079592,-0.97494,-1.1703,-0.14285,1.3184,2.6866,2.868,2.2741,0.92319,-0.49336,-1.3339,-1.8654,-2.1886,-2.4653,-2.8707,-2.8382,-2.0531,-0.55224,1.1765,2.4663,2.9573,2.4859,1.5295,0.91086,1.1807,1.747,2.2629,1.7269,0.12599,-1.8753,-3.4973,-4.211,-3.8233,-2.5004,-1.1382,-0.14274,0.50249,1.2285,1.7667,2.4574,2.7049,2.467,1.2927,-0.11482,-1.1309,-1.1852,-0.46898,0.48521,0.7469,0.15051,-0.91778,-2.065,-2.3257,-1.5111,-0.14807,1.1578,1.6193,1.2718,0.28188,-0.63947,-0.72654,-0.49419,-0.0075632,0.13222,-0.090838,-0.015832,0.2953,1.07,1.8391,2.059,1.3653,-0.054704,-1.5948,-2.4286,-2.1099,-1.0022,0.29789,0.99358,0.67628,-0.17116,-1.1101,-1.2069,-0.5385,0.28706,1.103,1.2017,0.81553,0.4292,0.20835,0.36205,0.60016,0.36065,-0.28176,-0.90741,-1.0875,-0.59241,0.55144,1.5684,2.0993,1.2142,-0.52929,-2.2302,-3.1933,-2.7853,-1.5581,-0.09055,0.73398,1.023,0.86454,0.93898,1.2903,1.9383,2.3486,2.1153,1.4242,0.46715,-0.37316,-0.56602,-0.7315,-1.079,-1.9235,-3.0767,-3.9276,-3.864,-2.4185,0.032325,2.3699,3.8609,4.0333,3.1746,1.9303,0.97566,0.76574,0.62705,0.38524,-0.39903,-1.3712,-2.2097,-2.3093,-1.7595,-1.2288,-0.71992,-0.82601,-0.98239,-0.78439,0.19568,1.5488,2.7264,3.173,2.408,0.59928,-1.1268,-1.947,-1.8338,-0.58953,0.49281,1.0216,0.97309,0.23735,-0.36379,-0.55488,-0.33825,-0.18824,-0.32299,-0.81461,-1.213,-1.0249,-0.2972,0.63922,1.2643,1.1276,0.24053,-0.75766,-1.0127,-0.34485,1.0598,2.1685,2.5374,1.5342,0.056924,-1.3991,-2.0359,-1.8386,-1.0425,-0.1687,0.18368,0.026696,0.0045511,0.11615,0.50442,0.66276,0.44934,-0.33738,-1.2713,-1.5772,-1.114,0.20826,1.5648,2.433,2.0223,0.98116,-0.13363,-0.88494,-0.30482,0.50764,1.0766,1.1189,0.088823,-1.3227,-2.3829,-2.696,-2.4751,-1.7229,-1.1806,-0.46914,0.099211,1.1163,2.5143,3.776,4.3208,3.6279,1.8958,-0.10741,-1.7779,-2.1917,-1.757,-1.2007,-0.92842,-1.534,-2.4541,-2.852,-2.5932,-1.348,0.57605,2.0775,2.7675,2.766,2.5636,2.0288,1.7763,1.2499,0.47154,-0.92777,-2.2293,-2.9344,-2.5373,-1.3048,0.30365,1.1128,1.0083,-0.069657,-1.0148,-1.4795,-0.78018,0.21815,1.2389,1.6013,1.1313,0.29543,-0.39146,-0.47993,-0.21678,0.25524,0.4352,0.2102,-0.072592,0.070492,0.41711,0.95063,1.1544,0.24782,-1.1289,-2.3584,-2.8737,-2.1908,-0.50266,1.0567,2.0276,2.0341,0.80629,-0.10417,-0.53733,-0.34643,0.36889,0.76173,0.76731,0.3056,-0.20827,-0.12384,-0.0020316,0.41871,0.29788,-0.17651,-0.9688,-1.3797,-0.97088,-0.038151,0.91747,1.2735,0.45577,-0.94877,-2.2252,-2.6682,-1.6278,-0.035457,1.6492,2.7552,2.7725,2.2877,1.6284,1.0673,0.87165,0.36993,-0.5521,-1.6343,-2.6888,-2.8394,-2.5128,-1.5972,-0.72446,-0.45841,-0.60909,-0.84052,-0.47336,1.1172,2.9769,4.4311,4.612,3.5712,1.5852,-0.68314,-2.1317,-2.6366,-2.4484,-2.1452,-1.9806,-1.9373,-1.7619,-1.0763,0.097066,1.2035,1.5712,1.399,0.64081,0.35942,0.55482,1.3404,2.0348,2.1019,1.0286,-0.63996,-2.0231,-2.5594,-2.0927,-0.69059,0.64578,1.3204,1.1571,0.19744,-0.4518,-0.77241,-0.65035,-0.42687,-0.46574,-0.69761,-0.86502,-0.46023,0.52388,1.6264,2.2154,1.8866,0.74115,-0.60284,-1.3717,-0.94877,0.010252,0.99789,1.2713,0.59482,-0.6634,-1.7333,-2.0937,-1.5737,-0.50477,0.42927,0.83825,0.67052,0.45509,0.38052,0.57601,0.70063,0.4972,-0.23972,-1.0785,-1.2657,-0.68938,0.68211,2.0897,2.6351,2.0459,0.65189,-1.0517,-2.0064,-1.9506,-1.3089,-0.54907,-0.28582,-0.73609,-1.4112,-1.5302,-1.1546,-0.050407,0.92707,1.7109,1.9938,1.9924,2.2293,2.4394,2.4885,2.1302,0.45595,-1.6202,-3.6571,-4.6899,-4.3827,-2.8069,-0.99697,0.32099,0.86733,0.63278,0.44994,0.71992,1.5293,2.614,2.8963,2.5997,1.6231,0.52623,-0.37893,-0.75605,-1.1549,-1.4481,-2.2132,-2.814,-2.8243,-1.8006,-0.036744,1.5739,2.5867,2.1833,1.0179,-0.38077,-1.2742,-0.95999,-0.0054475,0.91627,1.4074,0.93857,0.10745,-0.32847,-0.43954,-0.10879,0.13114,0.16692,-0.30695,-0.77132,-0.841,-0.31427,0.3836,0.47859,0.16084,-0.88965,-1.8442,-1.9622,-1.0863,0.56808,2.2484,2.8756,2.3773,1.1766,-0.3779,-1.1193,-0.97841,-0.4239,-0.03359,-0.0017921,-0.13016,-0.38414,-0.24851,0.12782,0.58689,0.36357,-0.2525,-1.181,-1.7011,-1.2527,-0.23399,0.96674,1.4782,1.1321,0.033593,-0.98262,-1.1518,-0.20151,1.3009,2.5905,2.8512,2.1851,0.98767,-0.44119,-1.3682,-1.8414,-2.0592,-2.4107,-2.7822,-2.7885,-2.0694,-0.56578,1.171,2.455,3.0101,2.4246,1.4619,0.95625,1.2324,1.7722,2.358,1.7356,0.24528,-1.7702,-3.5218,-4.2713,-3.7637,-2.6307,-1.1082,-0.016181,0.58161,1.0962,1.6569,2.4577,2.7479,2.4929,1.3118,-0.072432,-1.1571,-1.1911,-0.44945,0.36507,0.79835,0.27108,-0.98652,-2.0078,-2.2369,-1.5329,-0.16024,1.0863,1.6714,1.1711,0.27121,-0.49566,-0.68676,-0.56569,-0.081544,0.077846,-0.097301,-0.16751,0.2786,0.9176,1.7962,2.1194,1.3642,-0.066833,-1.5637,-2.4391,-2.1265,-0.96422,0.45151,1.1034,0.65162,-0.24795,-1.0532,-1.2373,-0.49303,0.37641,1.0242,1.1122,0.89287,0.38864,0.2611,0.32885,0.50444,0.41794,-0.26544,-0.92774,-1.2033,-0.52147,0.5804,1.6522,1.9981,1.0553,-0.55022,-2.244,-3.1247,-2.8213,-1.4358,-0.14339,0.70489,0.92633,0.88269,0.86546,1.134,1.8939,2.3755,2.1948,1.4724,0.43073,-0.33201,-0.58379,-0.56802,-0.96722,-1.9345,-3.2225,-4.0401,-3.8057,-2.5153,-0.089311,2.3444,3.9003,4.0722,3.1746,1.9209,0.93369,0.7881,0.67454,0.39786,-0.3415,-1.316,-2.0999,-2.242,-1.9008,-1.2043,-0.75556,-0.92953,-1.0084,-0.77685,0.08956,1.5354,2.7826,3.1458,2.3025,0.73745,-1.0381,-1.9879,-1.7112,-0.52081,0.52351,1.1092,0.89664,0.26384,-0.36261,-0.53491,-0.39457,-0.25179,-0.44197,-0.90835,-1.1372,-0.99354,-0.27733,0.59525,1.2621,1.0087,0.19714,-0.75021,-1.0344,-0.43874,0.93,2.1378,2.4031,1.7077,-0.011426,-1.4857,-1.9919,-1.8063,-1.0573,-0.2369,0.12578,0.08894,-0.019127,0.11395,0.50153,0.66933,0.4359,-0.28646,-1.1983,-1.628,-1.0371,0.20283,1.6103,2.3717,1.9778,1.0238,-0.27756,-0.76351,-0.42348,0.38595,1.0939,1.0697,0.1108,-1.2536,-2.3189,-2.695,-2.4409,-1.7834,-0.98517,-0.60475,-0.0037567,0.99591,2.548,3.852,4.3187,3.5746,1.8056,-0.21123,-1.6516,-2.0916,-1.7183,-1.0787,-0.97182,-1.5095,-2.4346,-2.9403,-2.5252,-1.1166,0.58622,2.1331,2.7635,2.8665,2.5541,2.1817,1.901,1.3959,0.36555,-0.88363,-2.2971,-2.9164,-2.5036,-1.3002,0.28722,1.1549,0.91681,0.045127,-1.0937,-1.5588,-0.91466,0.28417,1.3072,1.6614,1.2429,0.26839,-0.41415,-0.53493,-0.21761,0.27565,0.45349,0.17045,-0.1083,-0.016438,0.52828,1.0319,1.1283,0.31228,-1.078,-2.385,-2.8755,-2.1801,-0.64189,1.1011,1.999,1.7865,0.94634,-0.21365,-0.62479,-0.23692,0.38175,0.80392,0.7404,0.3323,-0.062227,-0.22769,0.1495,0.43223,0.25966,-0.24923,-1.0148,-1.4162,-1.0049,-0.0081357,1.037,1.1964,0.50621,-1.0253,-2.2027,-2.5844,-1.7466,-0.036741,1.8022,2.8054,2.8767,2.2033,1.5808,1.083,0.83853,0.41297,-0.35876,-1.6181,-2.6159,-3.0059,-2.5007,-1.5097,-0.75269,-0.43722,-0.80424,-0.93496,-0.34196,1.0753,2.8162,4.3724,4.5669,3.528,1.6096,-0.5591,-1.9627,-2.5155,-2.5299,-2.207,-1.9912,-1.9831,-1.6989,-0.96624,0.11939,1.1541,1.6172,1.3828,0.65104,0.27338,0.55882,1.3208,2.0446,1.9559,1.0894,-0.59344,-2.0733,-2.6205,-2.0297,-0.70385,0.76702,1.2515,1.0143,0.26804,-0.41852,-0.8402,-0.74573,-0.32371,-0.46854,-0.74925,-0.72341,-0.3206,0.55422,1.6316,2.1975,1.8696,0.6869,-0.59378,-1.3036,-1.0055,0.026351,1.0167,1.2497,0.57751,-0.72102,-1.883,-2.1783,-1.6107,-0.56351,0.50676,0.82067,0.59501,0.46724,0.4076,0.63104,0.77829,0.39055,-0.16357,-1.0416,-1.3972,-0.73005,0.65723,2.1175,2.7424,2.0962,0.61204,-1.1097,-2.0091,-2.1467,-1.2633,-0.43823,-0.36105,-0.71658,-1.3825,-1.5716,-1.1365,-0.15039,1.1076,1.6964,1.8743,2.0062,2.1155,2.4237,2.693,1.9776,0.55653,-1.611,-3.7687,-4.6323,-4.2449,-2.8411,-1.0385,0.41457,0.85119,0.65468,0.5032,0.60842,1.5952,2.558,2.9834,2.6892,1.6258,0.54433,-0.39432,-0.8179,-1.0045,-1.5274,-2.2292,-2.7832,-2.7422,-1.703,-0.08268,1.634,2.41,2.3092,0.94958,-0.48112,-1.3076,-0.98732,0.05778,1.1948,1.3816,1.0138,0.26022,-0.37569,-0.39965,-0.1358,0.22507,0.11086,-0.36615,-0.7689,-0.67516,-0.25782,0.30609,0.52665,0.037028,-0.9058,-1.8388,-2.0367,-1.0538,0.67002,2.2171,2.9392,2.412,0.97239,-0.31869,-1.0753,-1.1303,-0.4862,0.043471,-0.057234,-0.20332,-0.40416,-0.23955,0.26315,0.52837,0.40602,-0.27536,-1.1144,-1.7912,-1.3704,-0.21212,0.9129,1.4775,1.1078,-0.0044134,-1.0944,-1.0072,-0.26713,1.1901,2.5042,2.9334,2.224,0.91098,-0.45529,-1.3837,-1.7902,-2.1322,-2.4177,-2.8405,-2.8189,-2.0446,-0.52178,1.2357,2.5836,2.9094,2.5073,1.5711,0.87898,1.0669,1.6565,2.1518,1.6443,0.17334,-1.7388,-3.549,-4.2337,-3.8318,-2.4654,-1.0497,-0.10124,0.56902,1.0941,1.8023,2.3727,2.7692,2.3822,1.4203,-0.053864,-1.0086,-1.2282,-0.40773,0.37479,0.78435,0.15198,-0.97311,-2.0982,-2.3826,-1.5712,-0.14181,1.2206,1.5575,1.1161,0.23878,-0.52015,-0.72138,-0.50503,0.077317,0.030136,-0.042587,-0.14385,0.26488,1.0087,1.7317,2.0435,1.5108,-0.061043,-1.5557,-2.4171,-2.2184,-0.88665,0.4031,0.94305,0.67169,-0.24793,-1.131,-1.239,-0.57846,0.37734,0.95968,1.1776,0.72807,0.47971,0.17847,0.39741,0.56061,0.42528,-0.1961,-0.98813,-1.1733,-0.59621,0.47101,1.7791,1.9507,1.1583,-0.53295,-2.2858,-3.1349,-2.7188,-1.4871,-0.20503,0.69933,1.1308,0.81493,0.78932,1.2217,1.8776,2.3172,2.0994,1.3597,0.37066,-0.29865,-0.51008,-0.74393,-1.0152,-1.8545,-3.0953,-3.9895,-3.8162,-2.3647,-0.058274,2.3078,3.8516,4.0986,3.0913,1.9025,0.99173,0.6049,0.68127,0.38754,-0.38129,-1.3857,-2.0665,-2.3763,-1.9024,-1.2172,-0.89191,-0.85616,-0.92763,-0.68926,0.18465,1.545,2.808,3.0987,2.4035,0.57603,-1.1448,-1.9505,-1.7003,-0.53176,0.57506,1.2416,0.96728,0.24708,-0.39018,-0.66241,-0.44062,-0.17961,-0.42348,-0.95903,-1.1696,-1.098,-0.27611,0.68158,1.2286,1.0302,0.16305,-0.66488,-1.0156,-0.29341,0.97917,2.2145,2.4811,1.665,0.13469,-1.5459,-2.1051,-1.8534,-1.0863,-0.24423,0.075735,0.13771,-0.061552,0.014228,0.57173,0.70505,0.402,-0.38634,-1.2236,-1.6023,-1.2109,0.13762,1.5761,2.4343,2.0161,0.91861,-0.23894,-0.65418,-0.44735,0.42967,1.1621,1.0576,0.11935,-1.2997,-2.333,-2.7617,-2.3845,-1.7145,-1.1255,-0.50653,0.1218,1.0814,2.573,3.8357,4.222,3.6443,1.7635,-0.21031,-1.7387,-2.1792,-1.7928,-1.1628,-0.91555,-1.5079,-2.3657,-2.8943,-2.4816,-1.2496,0.51464,2.0642,2.8169,2.9098,2.5061,2.147,1.8627,1.332,0.45565,-0.85845,-2.2108,-2.9379,-2.441,-1.3619,0.1952,1.1284,1.0375,0.035962,-1.0936,-1.4171,-0.87723,0.14867,1.2887,1.6591,1.1729,0.18871,-0.39377,-0.55308,-0.2522,0.27513,0.3775,0.16773,-0.032322,0.025725,0.49591,1.0347,0.98422,0.41596,-1.0772,-2.3511,-2.8467,-2.1543,-0.55601,1.0765,2.0947,1.7255,0.86125,-0.097133,-0.56207,-0.20901,0.33572,0.87564,0.68206,0.21835,-0.1213,-0.26192,0.037732,0.37377,0.34942,-0.29263,-0.9816,-1.3618,-0.9858,-0.0024885,0.9445,1.244,0.46581,-1.0325,-2.121,-2.5959,-1.7022,0.044818,1.7608,2.7732,2.8909,2.2581,1.5873,1.0452,0.84837,0.36037,-0.43392,-1.6114,-2.6757,-2.908,-2.4192,-1.525,-0.80228,-0.52189,-0.60384,-0.79882,-0.40612,1.0065,2.8369,4.2913,4.769,3.5942,1.5633,-0.64708,-2.1279,-2.6071,-2.5359,-2.2085,-1.8857,-1.9289,-1.8697,-1.0442,0.18618,1.0846,1.5497,1.3787,0.74643,0.31439,0.50889,1.3064,2.0165,2.042,1.0672,-0.61654,-2.1169,-2.6645,-2.0538,-0.7344,0.70137,1.2593,0.99059,0.22789,-0.40541,-0.74396,-0.66815,-0.41266,-0.42167,-0.71439,-0.7232,-0.40401,0.4698,1.5803,2.1935,1.88,0.68054,-0.62401,-1.3664,-1.0518,0.0044544,1.0053,1.2527,0.63758,-0.54795,-1.8761,-2.212,-1.5923,-0.52839,0.36094,0.84935,0.7794,0.39957,0.35314,0.65181,0.69717,0.46385,-0.23263,-0.94867,-1.2533,-0.76767,0.71068,2.0457,2.6304,2.1731,0.57965,-1.1165,-2.0365,-2.0398,-1.4295,-0.58311,-0.28476,-0.65055,-1.2903,-1.5831,-1.2251,-0.084929,0.96469,1.7536,2.0319,2.0102,2.2647,2.4814,2.6803,2.1176,0.50198,-1.5747,-3.6338,-4.6103,-4.4647,-2.7835,-1.0088,0.39554,0.89391,0.77392,0.53361,0.81816,1.658,2.4812,2.9762,2.5844,1.6602,0.44376,-0.40554,-0.70399,-1.0172,-1.4432,-2.2578,-2.7307,-2.7369,-1.7218,0.068454,1.709,2.588,2.2173,0.97435,-0.36614,-1.2549,-0.92333,0.028813,0.99389,1.3407,0.96998,0.10794,-0.36423,-0.45779,0.0014982,0.18118,0.17566,-0.30515,-0.72471,-0.86234,-0.38885,0.27737,0.52977,0.065067,-0.8879,-1.7894,-2.0299,-1.1391,0.51339,2.1304,2.8919,2.3908,1.0618,-0.33632,-1.1124,-0.99722,-0.49766,-0.00076673,0.047085,-0.19436,-0.42218,-0.35508,0.11318,0.45787,0.40294,-0.26975,-1.1608,-1.7373,-1.2453,-0.23149,0.89816,1.5266,1.0259,-0.050096,-0.95352,-1.0927,-0.2279,1.299,2.5698,2.9419,2.2458,0.85171,-0.54834,-1.375,-1.8646,-2.0731,-2.5184,-2.8187,-2.8413,-2.1533,-0.50528,1.1488,2.5867,2.8848,2.2835,1.4908,1.0848,1.1198,1.8464,2.2223,1.7532,0.2973,-1.8663,-3.603,-4.2341,-3.8061,-2.5356,-1.089,-0.056118,0.66615,1.1095,1.7691,2.4674,2.7643,2.3011,1.3696,-0.075068,-1.0524,-1.2324,-0.55032,0.37825,0.78929,0.24846,-0.98324,-2.0217,-2.3712,-1.5416,-0.14761,1.0799,1.6974,1.2248,0.31282,-0.45129,-0.60793,-0.51371,-0.19253,-0.0017466,-0.12925,-0.16169,0.33535,0.98997,1.8189,2.1966,1.3612,-0.074087,-1.5881,-2.4485,-2.1292,-1.0346,0.32667,1.025,0.7102,-0.1793,-1.0339,-1.2227,-0.65785,0.27482,1.0365,1.0754,0.83927,0.3524,0.30115,0.41055,0.46578,0.32943,-0.20732,-0.93478,-1.2558,-0.64797,0.47673,1.8065,1.9932,1.2242,-0.51492,-2.3513,-3.0812,-2.8084,-1.5575,-0.23734,0.78174,1.0609,0.78981,0.79722,1.2523,1.9077,2.3489,2.169,1.3529,0.3641,-0.28504,-0.67756,-0.67991,-1.0096,-1.9225,-2.988,-4.0133,-3.7987,-2.3922,0.04323,2.3616,3.8988,4.0483,3.1847,1.8775,1.0823,0.55084,0.70802,0.28826,-0.46458,-1.3068,-2.1128,-2.2969,-1.9373,-1.3071,-0.89647,-0.86628,-0.96687,-0.7109,0.23496,1.5604,2.8737,3.2075,2.224,0.56047,-1.1782,-1.9873,-1.7695,-0.5149,0.63407,1.1722,0.84792,0.17822,-0.28214,-0.54122,-0.36686,-0.23509,-0.3971,-0.76217,-1.1239,-1.0381,-0.26231,0.74219,1.2876,0.99571,0.18399,-0.68955
};
#else
static const float dumsignal[SIGNAL_SIZE] = { //data with 4 peaks in PSD
        0.0011358,1.5858,2.8927,3.4272,3.477,2.8788,1.8703,0.76746,-0.11066,-0.53752,-0.90145,-1.0523,-1.2094,-1.3882,-1.6431,-1.8134,-1.817,-1.6319,-0.79686,0.049554,1.0799,1.9568,2.277,2.1252,1.6263,0.65034,-0.29684,-0.97097,-1.1868,-0.85386,-0.4367,0.35646,0.72053,0.9553,0.68292,0.040622,-0.5135,-1.0628,-1.3078,-1.0875,-0.68582,-0.15293,0.36575,0.47921,0.45648,0.15167,-0.25341,-0.17416,-0.12159,0.42055,1.0165,1.3213,1.4599,1.1382,0.37043,-0.43556,-1.294,-1.6674,-1.7345,-1.2508,-0.48145,0.31155,0.85791,0.92922,0.68449,0.12279,-0.51904,-0.89248,-1.1369,-0.76292,-0.088049,0.60043,1.083,1.4049,1.3773,1.1039,0.49943,0.23543,0.036035,0.13427,0.094242,0.079409,-0.085891,-0.67922,-1.4464,-2.1975,-2.6202,-2.7215,-1.9203,-0.82083,0.58071,2.1838,3.2061,3.6267,3.4028,2.5882,1.4978,0.29682,-0.73744,-1.4313,-1.7244,-1.8266,-1.9638,-2.0481,-2.0174,-2.0102,-1.6775,-1.0762,-0.15342,0.96307,2.1608,3.1319,3.3422,3.0349,2.139,0.75629,-0.62847,-1.5756,-2.1611,-2.1805,-1.6241,-0.84924,-0.26466,0.15228,0.19882,0.081808,-0.26043,-0.43491,-0.44667,-0.10102,0.41504,0.80138,1.0349,0.96266,0.55496,0.0090898,-0.37814,-0.61499,-0.5797,-0.051337,0.53434,0.93329,1.227,0.94045,0.25449,-0.58223,-1.5096,-1.9626,-1.9453,-1.3482,-0.67076,0.36817,1.0033,1.4192,1.2596,0.80753,0.30398,-0.24227,-0.28508,-0.20169,0.19736,0.54673,0.76577,0.70743,0.26822,-0.17006,-0.71434,-0.90343,-0.81197,-0.49646,-0.054395,0.31239,0.4169,0.26802,-0.19153,-0.93872,-1.4711,-1.5701,-1.2366,-0.32971,0.77042,1.95,2.6663,2.8814,2.6496,1.6362,0.55582,-0.51727,-1.3896,-1.8644,-2.0216,-2.0779,-1.83,-1.6825,-1.6105,-1.3669,-1.116,-0.38056,0.58218,1.8117,2.8915,3.6005,3.7213,3.0855,1.9542,0.39395,-1.1786,-2.4995,-3.0862,-3.093,-2.5602,-1.7803,-0.79543,-0.15336,0.38983,0.5511,0.57127,0.61521,0.80854,1.0448,1.3902,1.5726,1.4882,1.0654,0.17655,-0.59052,-1.3989,-1.6771,-1.5633,-1.0044,-0.26802,0.50071,0.99316,0.98591,0.57748,-0.19849,-0.84433,-1.318,-1.4255,-0.86384,-0.28478,0.56448,1.2862,1.482,1.3091,0.9399,0.4219,-0.12669,-0.23258,-0.19341,0.078575,0.30852,0.3331,0.043575,-0.28646,-0.85258,-1.3685,-1.4314,-1.1994,-0.54125,0.23561,1.0249,1.2693,1.361,0.8829,0.13568,-0.60612,-0.92464,-1.0244,-0.43164,0.29321,0.95662,1.5788,1.7156,1.3075,0.52639,-0.22584,-0.97001,-1.5366,-1.6124,-1.4346,-1.0239,-0.78722,-0.66403,-0.58622,-0.5289,-0.26447,0.15851,0.87957,1.757,2.6721,3.0579,3.1069,2.5024,1.2314,-0.29975,-1.942,-3.0176,-3.792,-3.5576,-2.8284,-1.7662,-0.59178,0.44889,1.0058,1.319,1.6095,1.6365,1.833,1.9644,2.0769,1.8819,1.448,0.57992,-0.60857,-1.6041,-2.5841,-2.8647,-2.6611,-1.9143,-0.79718,0.30485,1.1928,1.5908,1.4983,1.0774,0.21459,-0.15248,-0.40496,-0.34214,-0.043045,0.54744,0.81584,0.92936,0.57144,0.0944,-0.41346,-0.74986,-0.76321,-0.47699,-0.045667,0.17119,0.41113,0.20407,-0.3578,-0.81382,-1.27,-1.4496,-1.0597,-0.3465,0.59503,1.4025,1.8409,1.9056,1.4125,0.61467,-0.22305,-0.98931,-1.2291,-0.92891,-0.48551,0.073214,0.50415,0.61654,0.45724,-0.1043,-0.62842,-0.95013,-1.0309,-0.79815,-0.40594,0.044076,0.44671,0.51927,0.32593,0.055658,-0.25007,-0.16357,0.23685,1.0037,1.6074,2.1193,2.1488,1.5168,0.47371,-0.85528,-2.099,-3.0923,-3.3683,-3.0458,-2.2283,-1.0093,0.12064,1.1254,1.6121,2.017,2.1002,1.9311,1.9499,1.8902,1.7287,1.4265,0.67226,-0.27648,-1.6061,-2.5797,-3.3517,-3.7386,-3.0443,-2.1398,-0.62105,0.84435,2.0701,2.6039,2.7394,2.2333,1.3337,0.65942,0.083797,-0.22531,-0.34414,-0.073798,-0.0086352,-0.13179,-0.53294,-0.91857,-1.3342,-1.3715,-1.13,-0.43359,0.10709,0.91541,1.1818,1.0248,0.5138,-0.17735,-0.8219,-1.0187,-1.009,-0.1882,0.39978,1.2224,1.7442,1.6803,1.2819,0.52683,-0.3854,-1.0855,-1.4622,-1.2977,-0.89382,-0.39818,0.014595,0.25779,0.12537,-0.15928,-0.30469,-0.53295,-0.40983,0.045845,0.5869,1.0031,1.1924,1.1874,0.59763,0.044438,-0.63733,-0.91766,-0.89011,-0.33364,0.42202,0.85224,1.2171,1.0876,0.3639,-0.53257,-1.6441,-2.1417,-2.3433,-1.8688,-1.1185,-0.11609,0.82051,1.4509,1.752,1.8219,1.7613,1.4172,1.1976,1.0847,0.96139,0.67814,-0.042369,-0.8252,-1.7827,-2.8551,-3.5619,-3.5217,-2.7887,-1.6935,0.01302,1.64,2.9118,3.6055,3.4138,2.7748,1.8696,0.79412,-0.062557,-0.62638,-0.98437,-1.0065,-1.1882,-1.3126,-1.624,-1.9441,-1.854,-1.5371,-0.76089,0.099043,0.99695,1.951,2.2827,2.1239,1.5272,0.59812,-0.33723,-0.99901,-1.296,-0.95253,-0.39952,0.37613,0.8377,0.91072,0.64975,0.049444,-0.67043,-1.1226,-1.2925,-1.0837,-0.63945,-0.058664,0.40789,0.53182,0.36784,0.16629,-0.19193,-0.29676,-0.14224,0.37869,0.97455,1.3853,1.3749,1.1924,0.52882,-0.42256,-1.3018,-1.7614,-1.7391,-1.1595,-0.36441,0.28754,0.93008,0.94375,0.76,0.11924,-0.59693,-1.0566,-1.0727,-0.75722,-0.16781,0.45771,1.1109,1.2666,1.2459,0.99232,0.48581,0.28946,0.064274,0.093538,0.14423,0.28451,-0.088594,-0.67793,-1.4295,-2.1401,-2.5978,-2.7985,-2.0379,-0.79628,0.65421,2.1471,3.1783,3.5462,3.3638,2.5833,1.4354,0.26101,-0.87168,-1.4216,-1.8651,-1.7907,-1.9112,-1.9996,-1.9457,-2.0092,-1.6741,-1.1145,-0.18948,1.0605,2.083,3.1504,3.4207,3.0264,2.1028,0.816,-0.45222,-1.5793,-2.2151,-2.0271,-1.6105,-0.83998,-0.23533,0.11566,0.28499,-0.06777,-0.31716,-0.50427,-0.3509,-0.044254,0.41768,0.77218,1.0109,0.96303,0.59438,0.060897,-0.34669,-0.65198,-0.6034,-0.11773,0.58256,1.0877,1.2173,0.95647,0.18164,-0.56323,-1.4096,-1.9591,-1.8462,-1.3875,-0.5753,0.31697,1.0937,1.3068,1.296,0.79741,0.34358,-0.34896,-0.34575,-0.2284,0.24382,0.49505,0.80742,0.72846,0.37434,-0.20014,-0.61639,-0.94006,-0.93763,-0.42181,-0.058607,0.37689,0.53585,0.29049,-0.29661,-0.94367,-1.5437,-1.6043,-1.225,-0.34807,0.81258,1.8759,2.7938,2.89,2.4923,1.7489,0.42942,-0.47907,-1.2776,-1.9183,-2.0753,-2.011,-1.8104,-1.8187,-1.5176,-1.3215,-0.98559,-0.4134,0.65411,1.6595,2.906,3.5566,3.7273,3.0872,1.8536,0.37722,-1.2108,-2.4802,-3.0604,-3.1885,-2.5193,-1.6994,-0.86416,-0.12318,0.27078,0.63593,0.63427,0.61471,0.83298,1.1404,1.4209,1.6227,1.5476,1.0001,0.32412,-0.52394,-1.176,-1.6692,-1.5855,-0.95231,-0.3113,0.48021,0.85779,0.85079,0.52983,-0.15,-0.80218,-1.3119,-1.265,-0.87067,-0.11975,0.50389,1.2967,1.4007,1.2666,0.9875,0.32635,-0.21268,-0.22112,-0.32306,0.090949,0.33591,0.29563,0.12759,-0.34514,-0.96084,-1.2681,-1.5413,-1.153,-0.54573,0.20898,0.95721,1.4036,1.2916,0.85163,0.14852,-0.63202,-0.95183,-0.94945,-0.53396,0.17697,1.0105,1.601,1.6887,1.2532,0.6228,-0.28549,-0.9793,-1.5672,-1.659,-1.4174,-1.0485,-0.8434,-0.68915,-0.5339,-0.61165,-0.39314,0.2078,0.74983,1.7927,2.5218,3.2059,3.1667,2.4412,1.2033,-0.39294,-1.9517,-3.1593,-3.746,-3.488,-2.8903,-1.6058,-0.55256,0.37474,1.0465,1.3831,1.5669,1.6732,1.8628,1.9375,2.0404,1.8976,1.3834,0.5245,-0.51766,-1.6918,-2.5729,-2.8728,-2.7565,-1.9172,-0.81287,0.35476,1.2637,1.6522,1.4889,0.87922,0.26477,-0.26536,-0.45249,-0.35691,0.017327,0.57439,0.83336,0.86312,0.71167,0.16634,-0.24247,-0.6656,-0.70141,-0.56703,-0.16758,0.23634,0.32939,0.080995,-0.22804,-0.8078,-1.2442,-1.366,-1.107,-0.34652,0.72968,1.3758,2.0177,1.9581,1.3524,0.65714,-0.27107,-0.97274,-1.1308,-0.96911,-0.47703,0.091783,0.48126,0.57788,0.51627,-0.13927,-0.67506,-0.95585,-0.97334,-0.78632,-0.37013,0.036507,0.43138,0.49499,0.32697,0.074232,-0.25494,-0.17238,0.25138,0.94145,1.5202,2.1231,2.011,1.5562,0.50911,-0.73473,-2.1704,-3.0085,-3.3181,-3.1042,-2.142,-0.94245,0.12821,1.082,1.5955,1.9682,2.0038,2.0657,1.918,1.8289,1.8426,1.3868,0.73222,-0.18265,-1.5498,-2.6565,-3.4895,-3.6009,-3.301,-2.1144,-0.62682,0.86692,1.9994,2.6197,2.67,2.1098,1.3767,0.63691,-0.12824,-0.14836,-0.17456,-0.1211,-0.19623,-0.22526,-0.65224,-1.0139,-1.2908,-1.2589,-1.0662,-0.52805,0.18427,0.75947,1.0202,0.9898,0.50236,-0.11638,-0.7458,-1.086,-0.97966,-0.38498,0.47775,1.1644,1.693,1.8006,1.2953,0.51669,-0.35841,-1.2137,-1.5195,-1.3107,-1.0751,-0.37656,0.087825,0.21033,0.13012,-0.18602,-0.37224,-0.55556,-0.29466,0.027603,0.61222,1.1665,1.2795,1.113,0.64525,-0.12947,-0.5711,-0.82713,-0.75515,-0.29356,0.37388,1.0694,1.2929,0.95932,0.39638,-0.52967,-1.5264,-2.044,-2.313,-1.8749,-1.0795,0.019709,0.90181,1.5603,1.8155,1.9326,1.5688,1.3816,1.2674,1.1401,0.96592,0.76152,-0.015664,-0.75432,-1.849,-2.8821,-3.5573,-3.4146,-2.9207,-1.6729,0.006605,1.6051,2.8877,3.5862,3.446,2.7368,1.8433,0.83499,-0.12284,-0.73467,-0.96045,-1.1226,-1.1854,-1.384,-1.5952,-1.821,-1.9513,-1.545,-0.89731,0.16164,1.0866,1.8603,2.2749,2.1404,1.5083,0.45396,-0.31381,-1.0004,-1.1387,-0.93761,-0.37507,0.23642,0.91461,0.98744,0.61615,0.011856,-0.65165,-1.119,-1.4218,-1.0324,-0.68778,0.019056,0.44072,0.4427,0.34451,0.099056,-0.10227,-0.2231,0.036658,0.42409,0.91035,1.3968,1.4648,1.1654,0.39765,-0.50539,-1.3366,-1.6886,-1.678,-1.2466,-0.43447,0.26125,0.75465,0.96525,0.66552,0.15857,-0.44349,-1.0585,-1.0706,-0.87604,-0.16729,0.51965,1.0567,1.3691,1.268,0.95874,0.5309,0.17389,0.080187,0.093778,0.13738,0.16673,-0.074508,-0.68003,-1.3774,-2.2271,-2.7584,-2.6163,-1.9756,-0.85741,0.76834,2.1299,3.1828,3.6811,3.4718,2.6292,1.3924,0.18294,-0.77623,-1.3514,-1.741,-1.8579,-1.9194,-1.9398,-2.0083,-2.0584,-1.7426,-1.1097,-0.15707,1.1992,2.06,3.1109,3.3858,3.0444,2.0987,0.8398,-0.54057,-1.5504,-2.1227,-2.1822,-1.6118,-0.88415,-0.19818,0.06373,0.14995,0.093826,-0.29343,-0.47228,-0.42135,-0.081146,0.36899,0.7539,1.1112,0.9845,0.57457,0.038051,-0.4136,-0.67128,-0.54266,0.024373,0.56823,0.94131,1.277,0.94488,0.27431,-0.6897,-1.3639,-1.9041,-1.9987,-1.3642,-0.51118,0.32731,0.96325,1.3701,1.2133,0.77205,0.28561,-0.20973,-0.38155,-0.16249,0.16009,0.50275,0.80486,0.60644,0.29188,-0.29917,-0.68368,-0.87464,-0.93653,-0.51213,-0.081413,0.40547,0.49274,0.18988,-0.2405,-0.91922,-1.5134,-1.5821,-1.2028,-0.3406,0.79608,1.779,2.6695,2.9797,2.5734,1.7501,0.67217,-0.52762,-1.3891,-1.7825,-1.9997,-1.986,-1.8061,-1.6688,-1.6213,-1.4037,-1.0859,-0.34758,0.67281,1.7907,2.8068,3.6182,3.746,3.0835,1.9692,0.24674,-1.1706,-2.4605,-3.2461,-3.2079,-2.6804,-1.7671,-0.71636,-0.029678,0.43006,0.63569,0.60122,0.67053,0.83601,1.2961,1.4874,1.6083,1.4561,1.0775,0.28335,-0.58324,-1.2265,-1.6585,-1.4705,-1.0402,-0.32931,0.44334,0.9638,1.0588,0.62506,-0.14035,-0.9036,-1.354,-1.2992,-0.994,-0.23573,0.54259,1.1791,1.5101,1.2495,0.81181,0.44899,-0.058727,-0.23902,-0.29196,-0.051434,0.29012,0.32506,0.12949,-0.26453,-0.8851,-1.244,-1.4209,-1.1631,-0.5423,0.18866,1.0373,1.4103,1.3533,0.81455,0.054705,-0.5641,-0.93707,-0.96487,-0.53688,0.32167,1.1704,1.6594,1.6783,1.3772,0.59663,-0.20158,-1.0845,-1.4906,-1.5843,-1.4423,-1.2142,-0.75851,-0.66593,-0.622,-0.54554,-0.38827,0.098643,0.89485,1.8024,2.6603,3.1679,3.1589,2.492,1.3445,-0.27501,-2.0306,-3.1669,-3.7239,-3.5263,-2.8234,-1.787,-0.63986,0.3148,1.0225,1.4914,1.6519,1.6832,1.849,1.9985,1.9699,1.818,1.3178,0.5801,-0.57663,-1.6428,-2.4413,-2.8484,-2.706,-1.9838,-0.73011,0.38587,1.2329,1.6663,1.4877,1.0138,0.33517,-0.30311,-0.55963,-0.42831,0.12024,0.52521,0.89271,0.89163,0.70046,0.19955,-0.32055,-0.65924,-0.78696,-0.46196,-0.1675,0.29389,0.37505,0.16418,-0.2254,-0.83161,-1.2702,-1.2747,-1.0499,-0.27659,0.65468,1.3506,1.8785,2.0028,1.4269,0.60769,-0.27091,-0.88134,-1.2427,-1.0459,-0.3683,0.13177,0.48658,0.59151,0.38887,-0.051602,-0.57856,-0.99296,-1.0686,-0.88296,-0.38231,0.16538,0.3671,0.45285,0.23958,0.040076,-0.1918,-0.082061,0.17069,0.94523,1.5643,2.1225,2.097,1.644,0.52843,-0.76667,-2.1386,-2.9803,-3.37,-3.0337,-2.2792,-1.0608,0.14124,1.0974,1.8273,1.9974,2.0378,1.9383,1.9284,1.971,1.7666,1.4209,0.74701,-0.25055,-1.3527,-2.5702,-3.4165,-3.6425,-3.179,-2.0778,-0.6007,0.86701,1.9811,2.76,2.7202,2.1845,1.3002,0.65082,0.079796,-0.16973,-0.2963,-0.12501,-0.027592,-0.16703,-0.4476,-0.95727,-1.3135,-1.3455,-1.154,-0.47929,0.14301,0.818,1.0468,0.97133,0.55814,-0.12069,-0.72702,-0.99979,-0.94113,-0.38036,0.45357,1.24,1.6714,1.6329,1.2833,0.36068,-0.49507,-1.1707,-1.4192,-1.4644,-1.0346,-0.47687,0.017414,0.28812,0.045669,-0.066058,-0.43382,-0.48943,-0.44739,0.026316,0.61707,1.0523,1.3639,0.96315,0.63831,-0.071909,-0.5964,-0.87938,-0.88365,-0.35022,0.32372,0.97162,1.1537,1.108,0.34997,-0.57121,-1.5172,-2.1793,-2.3402,-1.9671,-1.1453,-0.082016,0.91992,1.4258,1.84,1.8236,1.5626,1.3263,1.213,1.0882,0.94223,0.6812,0.083153,-0.8247,-1.9009,-2.8978,-3.4948,-3.553,-2.9055,-1.6368,-0.053367,1.5749,2.8319,3.5347,3.5507,2.9447,1.8965,0.70942,-0.13662,-0.637,-1.0014,-1.0656,-1.2041,-1.3495,-1.6241,-1.7602,-1.9057,-1.4632,-0.87718,0.17216,1.0345,1.9648,2.2657,2.0979,1.4893,0.55086,-0.37041,-0.96672,-1.2206,-0.89532,-0.28466,0.29484,0.86218,0.84597,0.55991,-0.099305,-0.62898,-1.0387,-1.2429,-1.0845,-0.64037,-0.030797,0.31357,0.47621,0.49036,0.053527,-0.089345,-0.27204,-0.13018,0.48617,1.0291,1.2144,1.5557,1.0729,0.40285,-0.48026,-1.2131,-1.733,-1.7653,-1.2242,-0.46262,0.26486,0.88099,1.074,0.80939,0.072998,-0.48611,-0.99251,-1.1082,-0.74382,-0.17977,0.47133,1.0252,1.2805,1.227,0.92733,0.63842,0.19776,0.054496,0.1121,0.11822,0.15545,-0.080997,-0.50681,-1.4835,-2.1127,-2.6695,-2.7064,-2.0674,-0.82218,0.53517,2.0023,3.1353,3.5286,3.3048,2.6613,1.5174,0.28704,-0.76489,-1.4702,-1.8547,-1.9366,-1.9347,-2.0274,-1.9814,-1.9916,-1.733,-1.1181,-0.11664,1.1348,2.2401,3.1154,3.2647,3.1288,2.1252,0.84403,-0.63458,-1.5172,-2.189,-1.9906,-1.623,-0.85337,-0.30818,0.15426,0.151,-0.073856,-0.21605,-0.40893,-0.43051,-0.13617,0.35162,0.80254,1.0281,0.84481,0.54677,0.074993,-0.45849,-0.71207,-0.55584,-0.049569,0.49879,0.94553,1.2672,0.98622,0.26857,-0.64295,-1.4088,-1.8686,-1.9298,-1.4826,-0.58005,0.41354,0.99729,1.3094,1.1982,0.92809,0.267,-0.24515,-0.35463,-0.11832,0.21209,0.53221,0.80314,0.70603,0.28392,-0.12485,-0.73696,-0.84816,-0.83572,-0.49614,-0.097868,0.34382,0.51533,0.38891,-0.31003,-1.0054,-1.4047,-1.675,-1.3293,-0.31691,0.77228,1.8903,2.72,2.8614,2.3879,1.7496,0.57286,-0.49762,-1.3163,-1.862,-2.0303,-2.0273,-1.8301,-1.7311,-1.6717,-1.377,-0.92555,-0.29452,0.50652,1.8625,2.7996,3.6176,3.6677,3.1909,1.9416,0.3624,-1.2361,-2.5093,-3.1913,-3.1802,-2.5845,-1.8205,-0.84929,-0.062823,0.35955,0.64073,0.55405,0.6177,0.93362,1.2058,1.506,1.5484,1.5029,1.0726,0.33075,-0.60942,-1.299,-1.6505,-1.534,-1.0253,-0.26379,0.5044,0.99793,0.95378,0.56063,-0.093235,-0.91356,-1.3279,-1.3545,-0.97128,-0.2365,0.58445,1.2197,1.4342,1.247,0.89972,0.34592,-0.12551,-0.22786,-0.24573,-0.0030743,0.34789,0.28182,0.086295,-0.2808,-0.84669,-1.2792,-1.4438,-1.0548,-0.60847,0.27868,0.93149,1.3015,1.2761,0.98267,0.12731,-0.49487,-1.0071,-0.91212,-0.46716,0.28392,1.0696,1.522,1.6175,1.3383,0.59027,-0.26268,-0.96672,-1.5433,-1.6526,-1.4051,-1.1747,-0.81266,-0.62204,-0.65772,-0.52452,-0.26321,-0.0066021,0.77934,1.6704,2.5964,3.0886,3.1523,2.5044,1.2185,-0.36073,-2.0036,-3.1145,-3.725,-3.5038,-2.8321,-1.8155,-0.56117,0.42678,1.0435,1.4044,1.5633,1.5631,1.7932,1.9745,1.9945,1.8271,1.3119,0.46536,-0.61985,-1.7203,-2.5231,-2.7967,-2.6042,-1.8165,-0.71145,0.40796,1.2937,1.5845,1.4591,1.0026,0.26348,-0.21842,-0.44375,-0.3644,0.0924,0.47354,0.83081,0.82285,0.66935,0.15434,-0.30233,-0.70601,-0.76633,-0.49016,-0.078086,0.2455,0.30218,0.19496,-0.28951,-0.84204,-1.277,-1.3649,-0.95159,-0.33672,0.56698,1.4604,1.9586,1.8985,1.4164,0.68212,-0.22131,-0.91987,-1.1941,-0.93272,-0.5359,-0.082643,0.53326,0.58374,0.33646,-0.11441,-0.66027,-0.91558,-1.0612,-0.95698,-0.26591,0.072504,0.38097,0.49558,0.32457,0.030393,-0.28281,-0.097048,0.19711,0.92607,1.6553,2.1659,2.1606,1.6509,0.54279,-0.71956,-2.1672,-3.1003,-3.3531,-3.1786,-2.1852,-0.9627,0.10528,1.1043,1.6911,1.9608,2.0719,2.0284,1.9215,1.8896,1.7106,1.3832,0.72581,-0.23984,-1.5836,-2.5137,-3.3428,-3.6122,-3.2222,-2.0719,-0.59794,0.91694,2.0057,2.648,2.7827,2.1994,1.3044,0.66076,0.092773,-0.15458,-0.20266,-0.056464,-0.056796,-0.1435,-0.51911,-0.93708,-1.2695,-1.3883,-0.94552,-0.49376,0.20183,0.76784,1.0891,1.0215,0.54635,-0.17331,-0.72483,-1.1047,-0.93088,-0.33303,0.49373,1.2867,1.8202,1.6702,1.0954,0.51951,-0.39898,-1.0821,-1.4191,-1.3078,-0.97457,-0.43219,0.033048,0.18758,0.14825,-0.050292,-0.39898,-0.47218,-0.35157,0.011469,0.67151,1.056,1.2205,1.0532,0.64464,-0.10325,-0.56388,-0.92201,-0.81317,-0.32236,0.39374,0.888,1.2092,1.0832,0.37072,-0.58443,-1.5143,-2.2286,-2.3244,-1.8887,-1.023,-0.11638,0.8183,1.4963,1.8472,1.8965,1.6556,1.4314,1.1478,1.0931,1.0246,0.62414,0.075929,-0.86906,-1.9367,-2.8501,-3.5002,-3.4361,-2.8566,-1.634,-0.032093,1.6313,2.8879,3.6029,3.569,2.8698,1.9263,0.79045,-0.021609,-0.66585,-1.0428,-1.1378,-1.1697,-1.3474,-1.611,-1.8912,-1.8032,-1.5569,-0.84773,0.045522,1.1302,1.9662,2.3327,2.1838,1.6069,0.58477,-0.40896,-0.98253,-1.1227,-0.87022,-0.23286,0.30192,0.75641,0.94418,0.66395,-0.040188,-0.59477,-1.0753,-1.249,-1.0654,-0.62716,-0.022493,0.32216,0.53504,0.3837,0.10097,-0.1788,-0.29064
};
#endif

//index counter for data
static uint16_t dumindex = 0;

//------------------- main functions

//init accelerometer device
void accelero_init(){
    //currently do nothing
}

//polling data from fifo
void accelero_fifo_poll(float* acc_data){
    memcpy(acc_data, (dumsignal+dumindex), 32*sizeof(float));

    //update the counter
    dumindex += 32;
    if(dumindex >= SIGNAL_SIZE){
        dumindex = 0;
    }
}
