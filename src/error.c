/*! @file
  @brief
  exception classes

  <pre>
  Copyright (C) 2015-2022 Kyushu Institute of Technology.
  Copyright (C) 2015-2022 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.

  </pre>
*/

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/
#include "vm_config.h"
#include <string.h>
#include <stdarg.h>


/***** Local headers ********************************************************/
#include "alloc.h"
#include "value.h"
#include "symbol.h"
#include "error.h"
#include "class.h"
#include "c_string.h"
#include "vm.h"
#include "console.h"


/***** Constat values *******************************************************/
/***** Macros ***************************************************************/
/***** Typedefs *************************************************************/
/***** Function prototypes **************************************************/
/***** Local variables ******************************************************/
/***** Global variables *****************************************************/
/***** Functions ************************************************************/
//================================================================
/*! constructor

  @param  vm		pointer to VM.
  @param  exc_cls	pointer to Exception class.
  @param  message	message.
  @param  len		message length or zero.
  @return		exception object.
*/
mrbc_value mrbc_exception_new(struct VM *vm, struct RClass *exc_cls, const void *message, int len )
{
  // allocate memory.
  mrbc_exception *ex = mrbc_alloc( vm, sizeof(mrbc_exception) );
  if( !ex ) {		// ENOMEM
    return mrbc_nil_value();
  }

  MRBC_INIT_OBJECT_HEADER( ex, "EX" );
  ex->cls = exc_cls;

  if( !message ) {
    ex->message = 0;
    ex->message_size = 0;
    goto RETURN;
  }

  if( *(const char *)message == 0 ) {
    ex->message = (uint8_t *)"";
    ex->message_size = 0;
    goto RETURN;
  }

  if( len == 0 ) {
    ex->message = (uint8_t *)message;
    ex->message_size = 0;
    goto RETURN;
  }

  // else, copy the message.
  ex->message = mrbc_alloc( vm, len+1 );
  if( !ex->message ) {
    ex->message_size = 0;
    goto RETURN;
  }

  memcpy( ex->message, message, len );
  ex->message[len] = '\0';
  ex->message_size = len;

 RETURN:
  return (mrbc_value){.tt = MRBC_TT_EXCEPTION, .exception = ex};
}


//================================================================
/*! constructor with allocated message buffer.

  @param  vm		pointer to VM.
  @param  exc_cls	pointer to Exception class.
  @param  message	message buffer.
  @param  len		message length.
  @return		exception object.
*/
mrbc_value mrbc_exception_new_alloc(struct VM *vm, struct RClass *exc_cls, const void *message, int len )
{
  // allocate memory.
  mrbc_exception *ex = mrbc_alloc( vm, sizeof(mrbc_exception) );
  if( !ex ) {		// ENOMEM
    return mrbc_nil_value();
  }

  MRBC_INIT_OBJECT_HEADER( ex, "EX" );
  ex->cls = exc_cls;
  ex->message = (uint8_t *)message;
  ex->message_size = len;

  return (mrbc_value){.tt = MRBC_TT_EXCEPTION, .exception = ex};
}


//================================================================
/*! destructor

  @param  value		target.
*/
void mrbc_exception_delete(mrbc_value *value)
{
  if( value->exception->message_size ) {
    mrbc_raw_free( value->exception->message );
  }
  mrbc_raw_free( value->exception );
}


//================================================================
/*! raise exception

  @param  vm		pointer to VM.
  @param  exc_cls	pointer to Exception class.
  @param  msg		message.
  @note	(usage) mrbc_raise(vm, MRBC_CLASS(TypeError), "message here.");
*/
void mrbc_raise( struct VM *vm, struct RClass *exc_cls, const char *msg )
{
  vm->exception = mrbc_exception_new( vm,
			exc_cls ? exc_cls : MRBC_CLASS(RuntimeError), msg, 0 );
  vm->flag_preemption = 2;
}


//================================================================
/*! raise exception like printf

  @param  vm		pointer to VM.
  @param  exc_cls	pointer to Exception class.
  @param  fstr		format string.
*/
void mrbc_raisef( struct VM *vm, struct RClass *exc_cls, const char *fstr, ... )
{
  va_list ap;
  va_start( ap, fstr );

  char *buf = mrbc_alloc( vm, 32 );
  if( !buf ) return;	// ENOMEM

  mrbc_vsprintf( buf, 32, fstr, ap );
  va_end( ap );

  vm->exception = mrbc_exception_new_alloc( vm,
			exc_cls ? exc_cls : MRBC_CLASS(RuntimeError),
			buf, strlen(buf) );
  vm->flag_preemption = 2;
}


//----------------------------------------------------------------
// Exception class
//----------------------------------------------------------------
//================================================================
/*! (method) new
 */
static void c_exception_new(struct VM *vm, mrbc_value v[], int argc)
{
  assert( mrbc_type(v[0]) == MRBC_TT_CLASS );

  mrbc_value value;
  if( argc == 1 && mrbc_type(v[1]) == MRBC_TT_STRING ) {
    value = mrbc_exception_new(vm, v[0].cls, mrbc_string_cstr(&v[1]), mrbc_string_size(&v[1]));
  } else {
    value = mrbc_exception_new(vm, v[0].cls, NULL, 0);
  }

  SET_RETURN(value);
}


//================================================================
/*! (method) message
 */
static void c_exception_message(struct VM *vm, mrbc_value v[], int argc)
{
  mrbc_value value;

  if( v[0].exception->message ) {
    value = mrbc_string_new( vm, v[0].exception->message, v[0].exception->message_size );
  } else {
    value = mrbc_string_new_cstr(vm, mrbc_symid_to_str(v->exception->cls->sym_id));
  }

  mrbc_decref( &v[0] );
  v[0] = value;
}


/* mruby/c Exception class hierarchy.

    Exception
      NoMemoryError
      NotImplementedError
      StandardError
        ArgumentError
        IndexError
        NameError
          NoMethodError
        RangeError
        RuntimeError
        TypeError
        ZeroDivisionError
*/

/* MRBC_AUTOGEN_METHOD_TABLE
  FILE("_autogen_class_exception.h")

  CLASS("Exception")
  METHOD("new", c_exception_new )
  METHOD("message", c_exception_message )

  CLASS("NoMemoryError")
  SUPER("Exception")

  CLASS("NotImplementedError")
  SUPER("Exception")

  CLASS("StandardError")
  SUPER("Exception")

  CLASS("ArgumentError")
  SUPER("StandardError")

  CLASS("IndexError")
  SUPER("StandardError")

  CLASS("NameError")
  SUPER("StandardError")

  CLASS("NoMethodError")
  SUPER("NameError")

  CLASS("RangeError")
  SUPER("StandardError")

  CLASS("RuntimeError")
  SUPER("StandardError")

  CLASS("TypeError")
  SUPER("StandardError")

  CLASS("ZeroDivisionError")
  SUPER("StandardError")
*/
#include "_autogen_class_exception.h"
