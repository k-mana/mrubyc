/* Auto generated by make_method_table.rb */
#include "symbol_builtin.h"

static const mrbc_sym method_symbols_TrueClass[] = {
#if MRBC_USE_STRING
  MRBC_SYM(inspect),
#endif
#if MRBC_USE_STRING
  MRBC_SYM(to_s),
#endif
};

static const mrbc_func_t method_functions_TrueClass[] = {
#if MRBC_USE_STRING
  c_true_to_s,
#endif
#if MRBC_USE_STRING
  c_true_to_s,
#endif
};

struct RBuiltinClass mrbc_class_TrueClass = {
  .sym_id = MRBC_SYM(TrueClass),
  .num_builtin_method = sizeof(method_symbols_TrueClass) / sizeof(mrbc_sym),
#if defined(MRBC_DEBUG)
  .names = "TrueClass",
#endif
  .super = MRBC_CLASS(Object),
  .method_link = 0,
  .method_symbols = method_symbols_TrueClass,
  .method_functions = method_functions_TrueClass,
};
