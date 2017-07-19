#include "debug_functions.h"
#include "acc_driver.h"
#include "diag/Trace.h"

//------------------- dummy data
static const float dumsignal[SIGNAL_SIZE] = {
	-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-1.5178e-13,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-4.2497e-13,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-4.5533e-13,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-8.4994e-13,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-5.3064e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-1.2749e-12,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-5.6099e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-1.6999e-12,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,3.1815e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-1.4858e-11,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-6.217e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-2.5498e-12,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,2.5744e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,-1.5708e-11,-1.3068,-1.8618,1.047,-0.80759,0.59596,-0.40184,2.212,0.8947,-1.1422,-1.1993,-1.287,1.3252,-1.1408,0.69621,0.40727,2.0898,0.12254,-1.9521,-0.62629,-0.78951,1.2209,-1.3301,1.1247,1.0754,1.4197,-0.69912,-2.2325,0.17491,-0.58829,0.90172,-1.1684,1.7071,1.3309,0.34218,-1.239,-1.9979,0.89428,-0.72389,0.63025,-0.6147,2.1517,1.0599,-0.83679,-1.284,-1.4561,1.2879,-1.0486,0.63099,0.17653,2.1814,0.36345,-1.7697,-0.8262,-0.90818,1.2828,-1.3052,0.97583,0.91681,1.6627,-0.47976,-2.2098,-0.059143,-0.60937,1,-1.2566,1.541,1.3105,0.67579,-1.1293,-2.1082,0.71387,-0.65636,0.68777,-0.80728,2.0567,1.1892,-0.51058,-1.3262,-1.625,1.2168,-0.95075,0.59515,-0.058317,2.2267,0.59197,-1.5458,-1.0001,-1.0482,1.3212,-1.2545,0.84589,0.72908,1.8663,-0.24404,-2.1414,-0.29289,-0.65998,1.0959,-1.3108,1.3711,1.2468,0.99259,-0.98146,-2.1866,0.51043,-0.60996,0.76406,-0.97433,1.9326,1.2783,-0.17163,-1.3244,-1.7864,1.1118,-0.85374,0.58863,-0.28971,2.2275,0.80032,-1.2849,-1.142,-1.2046,1.3316,-1.1828,0.73949,0.51872,2.0266,-6.8241e-12,-2.0266,-0.51872,-0.73949,1.1828,-1.3316,1.2046,1.142,1.2849,-0.80032,-2.2275,0.28971,-0.58863,0.85374,-1.1118,1.7864,1.3244,0.17163,-1.2783,-1.9326,0.97433,-0.76406,0.60996,-0.51043,2.1866,0.98146,-0.99259,-1.2468,-1.3711,1.3108,-1.0959,0.65998,0.29289,2.1414,0.24404,-1.8663,-0.72908,-0.84589,1.2545,-1.3212,1.0482,1.0001,1.5458,-0.59197,-2.2267,0.058317,-0.59515,0.95075,-1.2168,1.625,1.3262,0.51058,-1.1892,-2.0567,0.80728,-0.68777,0.65636,-0.71387,2.1082,1.1293,-0.67579,-1.3105,-1.541,1.2566,-1,0.60937,0.059143,2.2098,0.47976,-1.6627,-0.91681,-0.97583,1.3052,-1.2828,0.90818,0.8262,1.7697,-0.36345,-2.1814,-0.17653,-0.63099,1.0486,-1.2879,1.4561,1.284,0.83679,-1.0599,-2.1517,0.6147,-0.63025,0.72389,-0.89428,1.9979,1.239,-0.34218,-1.3309,-1.7071,1.1684,-0.90172,0.58829,-0.17491,2.2325,0.69912,-1.4197,-1.0754,-1.1247,1.3301,-1.2209,0.78951,0.62629,1.9521,-0.12254,-2.0898,-0.40727,-0.69621,1.1408,-1.3252,1.287,1.1993,1.1422,-0.8947,-2.212,0.40184,-0.59596,0.80759,-1.047,1.8618,1.3068,0.0001
};

uint16_t signal_check(float* acc_data){
	uint16_t fault_counter = 0;

	for(uint16_t i=0; i<SIGNAL_SIZE ; i++){
		if(acc_data[i] != dumsignal[i]){
			fault_counter ++;
		}
	}

	return fault_counter;
}

void signal_print(float* acc_data){
	trace_printf("START PRINTING SIGNAL ----\n");
	for(uint16_t i=0; i<SIGNAL_SIZE; i++){
		trace_printf("%0.4f,\n", acc_data[i]);
	}
	trace_printf("PRINTING SIGNAL IS FINISHED----\n");
}

void psd_print(float* psd_data){
	trace_printf("START PRINTING PSD ----\n");
	for(uint16_t i=0; i<NFFT/2; i++){
		trace_printf("%0.4f,\n", psd_data[i]);
	}
	trace_printf("PRINTING PSD IS FINISHED----\n");
}

void fft_print(float* fft_data){
	trace_printf("START PRINTING FFT ----\n");
	for(uint16_t i=0; i<NFFT; i+=2){
		trace_printf("%0.4f + %0.4f ,\n", fft_data[i], fft_data[i+1]);
	}
	trace_printf("PRINTING FFT IS FINISHED----\n");
}
