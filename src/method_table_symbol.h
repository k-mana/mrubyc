/* Auto generated by make_method_table.rb */
#include "symbol_builtin.h"

static const mrbc_sym method_symbols_Symbol[] = {
  MRBC_SYM(all_symbols),
#if MRBC_USE_STRING
  MRBC_SYM(id2name),
#endif
#if MRBC_USE_STRING
  MRBC_SYM(inspect),
#endif
#if MRBC_USE_STRING
  MRBC_SYM(to_s),
#endif
  MRBC_SYM(to_sym),
};

static const mrbc_func_t method_functions_Symbol[] = {
  c_symbol_all_symbols,
#if MRBC_USE_STRING
  c_symbol_to_s,
#endif
#if MRBC_USE_STRING
  c_symbol_inspect,
#endif
#if MRBC_USE_STRING
  c_symbol_to_s,
#endif
  c_ineffect,
};

struct RBuiltinClass mrbc_class_Symbol = {
  .sym_id = MRBC_SYM(Symbol),
  .num_builtin_method = sizeof(method_symbols_Symbol) / sizeof(mrbc_sym),
#if defined(MRBC_DEBUG)
  .names = "Symbol",
#endif
  .super = MRBC_CLASS(Object),
  .method_link = 0,
  .method_symbols = method_symbols_Symbol,
  .method_functions = method_functions_Symbol,
};
