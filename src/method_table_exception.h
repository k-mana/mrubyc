/* Auto generated by make_method_table.rb */
#include "symbol_builtin.h"

static const mrbc_sym method_symbols_Exception[] = {
  MRBC_SYM(message),
  MRBC_SYM(new),
};

static const mrbc_func_t method_functions_Exception[] = {
  c_exception_message,
  c_exception_new,
};

struct RBuiltinClass mrbc_class_Exception = {
  .sym_id = MRBC_SYM(Exception),
  .num_builtin_method = sizeof(method_symbols_Exception) / sizeof(mrbc_sym),
#if defined(MRBC_DEBUG)
  .names = "Exception",
#endif
  .super = MRBC_CLASS(Object),
  .method_link = 0,
  .method_symbols = method_symbols_Exception,
  .method_functions = method_functions_Exception,
};

struct RClass mrbc_class_NoMemoryError = {
  .sym_id = MRBC_SYM(NoMemoryError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "NoMemoryError",
#endif
  .super = MRBC_CLASS(Exception),
  .method_link = 0,
};

struct RClass mrbc_class_StandardError = {
  .sym_id = MRBC_SYM(StandardError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "StandardError",
#endif
  .super = MRBC_CLASS(Exception),
  .method_link = 0,
};

struct RClass mrbc_class_ArgumentError = {
  .sym_id = MRBC_SYM(ArgumentError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "ArgumentError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_IndexError = {
  .sym_id = MRBC_SYM(IndexError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "IndexError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_NameError = {
  .sym_id = MRBC_SYM(NameError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "NameError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_NoMethodError = {
  .sym_id = MRBC_SYM(NoMethodError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "NoMethodError",
#endif
  .super = MRBC_CLASS(NameError),
  .method_link = 0,
};

struct RClass mrbc_class_RangeError = {
  .sym_id = MRBC_SYM(RangeError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "RangeError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_RuntimeError = {
  .sym_id = MRBC_SYM(RuntimeError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "RuntimeError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_TypeError = {
  .sym_id = MRBC_SYM(TypeError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "TypeError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};

struct RClass mrbc_class_ZeroDivisionError = {
  .sym_id = MRBC_SYM(ZeroDivisionError),
  .num_builtin_method = 0,
#if defined(MRBC_DEBUG)
  .names = "ZeroDivisionError",
#endif
  .super = MRBC_CLASS(StandardError),
  .method_link = 0,
};
