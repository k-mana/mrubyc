/* Auto generated by make_method_table.rb */
#include "symbol_builtin.h"

static const mrbc_sym method_symbols_Math[] = {
  MRBC_SYM(acos),
  MRBC_SYM(acosh),
  MRBC_SYM(asin),
  MRBC_SYM(asinh),
  MRBC_SYM(atan),
  MRBC_SYM(atan2),
  MRBC_SYM(atanh),
  MRBC_SYM(cbrt),
  MRBC_SYM(cos),
  MRBC_SYM(cosh),
  MRBC_SYM(erf),
  MRBC_SYM(erfc),
  MRBC_SYM(exp),
  MRBC_SYM(hypot),
  MRBC_SYM(ldexp),
  MRBC_SYM(log),
  MRBC_SYM(log10),
  MRBC_SYM(log2),
  MRBC_SYM(sin),
  MRBC_SYM(sinh),
  MRBC_SYM(sqrt),
  MRBC_SYM(tan),
  MRBC_SYM(tanh),
};

static const mrbc_func_t method_functions_Math[] = {
  c_math_acos,
  c_math_acosh,
  c_math_asin,
  c_math_asinh,
  c_math_atan,
  c_math_atan2,
  c_math_atanh,
  c_math_cbrt,
  c_math_cos,
  c_math_cosh,
  c_math_erf,
  c_math_erfc,
  c_math_exp,
  c_math_hypot,
  c_math_ldexp,
  c_math_log,
  c_math_log10,
  c_math_log2,
  c_math_sin,
  c_math_sinh,
  c_math_sqrt,
  c_math_tan,
  c_math_tanh,
};

struct RBuiltinClass mrbc_class_Math = {
  .sym_id = MRBC_SYM(Math),
  .num_builtin_method = sizeof(method_symbols_Math) / sizeof(mrbc_sym),
#if defined(MRBC_DEBUG)
  .names = "Math",
#endif
  .super = MRBC_CLASS(Object),
  .method_link = 0,
  .method_symbols = method_symbols_Math,
  .method_functions = method_functions_Math,
};
