double sin (double);//正弦函数
double cos (double);//余弦函数
double tan (double);//正切函数
double sinh (double);//双曲正弦函数
double cosh (double);//双曲余弦函数
double tanh (double);//双曲正切函数
double asin (double);//反正弦函数
double acos (double);//反余弦函数
double atan (double);//反正切函数
double atan2 (double, double);//依然是反正切函数
double exp (double);//以e为底的指数函数
double log (double);//以e为底的对数函数
double log10 (double);//以10为底的对数函数
double pow (double, double);//实数的实数次方
double sqrt (double);//开平方
double ceil (double);//向正无穷方向取整
double floor (double);//向负无穷方向取整
double fabs (double);//绝对值
double ldexp (double, int);//计算前边那个实数乘e的后边那个整数次方的结果，没什么卵用
double frexp (double, int*);//把一个实数分解为x*2^exp次方的形式，貌似也没什么卵用
double modf (double, double*);//得到x的整数部分和小数部分
double fmod (double, double);//求实数除以实数的余数