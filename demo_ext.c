
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/php_string.h"
#include "ext/standard/info.h"
#include "ext/standard/php_standard.h"
#include "SAPI.h"
#include "php_demo_ext.h"

/* If you declare any globals in php_demo_ext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(demo_ext)
*/

/* True global resources - no need for thread safety here */
static int le_demo_ext;

zend_class_entry *php_greeting_class_entry;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("demo_ext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_demo_ext_globals, demo_ext_globals)
    STD_PHP_INI_ENTRY("demo_ext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_demo_ext_globals, demo_ext_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_demo_ext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_demo_ext_compiled)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "demo_ext", arg);
    RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_demo_ext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_demo_ext_init_globals(zend_demo_ext_globals *demo_ext_globals)
{
    demo_ext_globals->global_value = 0;
    demo_ext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ Greeting::__construct
 * takes an optional string parameter as the greeting prefix
 */
PHP_METHOD(Greeting, __construct)
{
    char *prefix = "Hello";
    int prefix_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &prefix, &prefix_len) == FAILURE) {
        RETURN_NULL();
    }

    char *prefix_property_name;
    int prefix_property_name_len;

    zend_mangle_property_name(&prefix_property_name, &prefix_property_name_len, "Greeting", 8, "prefix", sizeof("prefix")-1, 0);

    // zval *this_ptr = getThis();
    //
    // if (!this_ptr) {
    //     php_error_docref(NULL TSRMLS_CC, E_WARNING, "Constructor called statically");
    //     RETURN_FALSE;
    // }

    // add_property_stringl(this_ptr, "prefix", prefix, prefix_len);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_Greeting__construct, 0, 0, 0)
    ZEND_ARG_INFO(0, prefix)
ZEND_END_ARG_INFO()

// defines a list of methods for the Greeting class
static zend_function_entry php_greeting_class_entry_functions[] = {
    PHP_ME(Greeting, __construct, arginfo_Greeting__construct, ZEND_ACC_PUBLIC)
    { NULL, NULL, NULL }
};

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(demo_ext)
{
    // temporary variable
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Greeting", php_greeting_class_entry_functions);
    php_greeting_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    // php_greeting_class_entry->create_object = ???

    // declare a protected property for the Greeting class who's default value is "Hello"
    zend_declare_property_string(php_greeting_class_entry, "prefix", sizeof("prefix") - 1, "Hello", ZEND_ACC_PROTECTED);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(demo_ext)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(demo_ext)
{
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(demo_ext)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(demo_ext)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "demo_ext support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ demo_ext_greeting
 * Simple function that take one madatory parameter and returns a string. e.g.
 * demo_ext_greeting('World') will return 'Hello World!'
 */
PHP_FUNCTION(greeting)
{
    char *name, *output;
    int name_len, len;

    // get the single parameter, string, that was passed into the function. if
    // there was a failure in getting it, then PHP will automatically output an
    // error message so that we don't have to here. We, though have to return
    // null.
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
        RETURN_NULL();
    }

    len = spprintf(&output, 0, "Hello %s!", name);

    // char *converted = php_strtoupper(output, len);
    RETURN_STRINGL(output, len, 0);
}
/* }}} */


/* {{{
 * This function takes 2 parameters, the first is mandatory, the second is
 * optional.
 *
 * @param string $name who to say hello to
 * @param string $greeting the actual greeting, defaults to 'Hello'
 */
PHP_FUNCTION(greeting_alt)
{
    char *name,
         *greeting = NULL,  // optionals must be initialised to a default value
         *output,
         *prefix = "Hello";
    int name_len, greeting_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &greeting, &greeting_len) == FAILURE) {
        RETURN_NULL();
    }

    if (greeting != NULL) {
        prefix = greeting;
    }

    int len = spprintf(&output, 0, "%s %s!", prefix, name);

    RETURN_STRINGL(output, len, 0);
}

PHP_FUNCTION(greeting_uppercase)
{

}

/* {{{ demo_ext_functions[]
 *
 * Every user visible function must have an entry in demo_ext_functions[].
 */
const zend_function_entry demo_ext_functions[] = {
    PHP_FE(confirm_demo_ext_compiled,    NULL)        /* For testing, remove later. */
    PHP_FE(greeting, NULL)
    PHP_FE(greeting_alt, NULL)
    PHP_FE(greeting_uppercase, NULL)
    PHP_FE_END    /* Must be the last line in demo_ext_functions[] */
};
/* }}} */

/* {{{ demo_ext_module_entry
 */
zend_module_entry demo_ext_module_entry = {
    STANDARD_MODULE_HEADER,
    "demo_ext",
    demo_ext_functions,
    PHP_MINIT(demo_ext),
    PHP_MSHUTDOWN(demo_ext),
    PHP_RINIT(demo_ext),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(demo_ext),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(demo_ext),
    PHP_DEMO_EXT_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DEMO_EXT
ZEND_GET_MODULE(demo_ext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
