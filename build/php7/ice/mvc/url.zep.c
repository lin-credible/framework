
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * This component allows to create URLs.
 *
 * @package     Ice/Mvc
 * @category    Component
 * @author      Ice Team
 * @copyright   (c) 2014-2016 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Mvc_Url) {

	ZEPHIR_REGISTER_CLASS(Ice\\Mvc, Url, ice, mvc_url, ice_mvc_url_method_entry, 0);

	zend_declare_property_string(ice_mvc_url_ce, SL("baseUri"), "/", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(ice_mvc_url_ce, SL("staticUri"), "/", ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Ice_Mvc_Url, getBaseUri) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "baseUri");

}

PHP_METHOD(Ice_Mvc_Url, setBaseUri) {

	zval *baseUri, baseUri_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&baseUri_sub);

	zephir_fetch_params(0, 1, 0, &baseUri);



	zephir_update_property_zval(this_ptr, SL("baseUri"), baseUri);

}

PHP_METHOD(Ice_Mvc_Url, getStaticUri) {

	ZEPHIR_INIT_THIS();


	RETURN_MEMBER(this_ptr, "staticUri");

}

PHP_METHOD(Ice_Mvc_Url, setStaticUri) {

	zval *staticUri, staticUri_sub;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&staticUri_sub);

	zephir_fetch_params(0, 1, 0, &staticUri);



	zephir_update_property_zval(this_ptr, SL("staticUri"), staticUri);

}

/**
 * Generates a URL for a static resource.
 *
 * @param string uri
 * @return string
 */
PHP_METHOD(Ice_Mvc_Url, getStatic) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *uri_param = NULL, _0;
	zval uri;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &uri_param);

	if (!uri_param) {
		ZEPHIR_INIT_VAR(&uri);
		ZVAL_STRING(&uri, "");
	} else {
		zephir_get_strval(&uri, uri_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getstaticuri", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &_0, &uri);
	RETURN_MM();

}

/**
 * Generates a URL.
 *
 * @param string uri
 * @param array|object args Optional arguments to be appended to the query string
 * @param bool local
 * @return string
 */
PHP_METHOD(Ice_Mvc_Url, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool local, _0, _5$$8, _7$$11;
	zval *uri = NULL, uri_sub, *args = NULL, args_sub, *local_param = NULL, _GET, __$null, baseUri, matched, queryString, _1$$3, _2$$3, _3$$4, _4$$4, _6$$10, _8$$12, _9$$12, _10$$13, _11$$14;
	ZEPHIR_INIT_THIS();

	ZVAL_UNDEF(&uri_sub);
	ZVAL_UNDEF(&args_sub);
	ZVAL_UNDEF(&_GET);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&baseUri);
	ZVAL_UNDEF(&matched);
	ZVAL_UNDEF(&queryString);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_8$$12);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$13);
	ZVAL_UNDEF(&_11$$14);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_GET, SL("_GET"));
	zephir_fetch_params(1, 0, 3, &uri, &args, &local_param);

	if (!uri) {
		uri = &uri_sub;
		ZEPHIR_CPY_WRT(uri, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(uri);
	}
	if (!args) {
		args = &args_sub;
		args = &__$null;
	}
	if (!local_param) {
		local = 1;
	} else {
		local = zephir_get_boolval(local_param);
	}


	_0 = !local;
	if (_0) {
		_0 = !(zephir_start_with_str(uri, SL("mailto:")));
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "://");
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strstr", NULL, 73, uri, &_1$$3);
		zephir_check_call_status();
		if (zephir_is_true(&_2$$3)) {
			ZEPHIR_INIT_VAR(&_3$$4);
			ZEPHIR_INIT_VAR(&_4$$4);
			ZVAL_STRING(&_4$$4, "/^[^:\\/?#]++:/");
			ZEPHIR_INIT_VAR(&matched);
			zephir_preg_match(&matched, &_4$$4, uri, &_3$$4, 0, 0 , 0  TSRMLS_CC);
			if (zephir_is_true(&matched)) {
				local = 0;
			} else {
				local = 1;
			}
		} else {
			local = 1;
		}
	}
	ZEPHIR_CALL_METHOD(&baseUri, this_ptr, "getbaseuri", NULL, 0);
	zephir_check_call_status();
	if (local) {
		_5$$8 = ZEPHIR_IS_FALSE_IDENTICAL(uri);
		if (_5$$8) {
			_5$$8 = zephir_array_isset_string(&_GET, SL("_url"));
		}
		if (_5$$8) {
			ZEPHIR_OBS_NVAR(uri);
			zephir_array_fetch_string(uri, &_GET, SL("_url"), PH_NOISY, "ice/mvc/url.zep", 62 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_VAR(&_6$$10);
			ZEPHIR_CONCAT_VV(&_6$$10, &baseUri, uri);
			ZEPHIR_CPY_WRT(uri, &_6$$10);
		}
	}
	if (zephir_is_true(args)) {
		ZEPHIR_CALL_FUNCTION(&queryString, "http_build_query", NULL, 19, args);
		zephir_check_call_status();
		_7$$11 = Z_TYPE_P(&queryString) == IS_STRING;
		if (_7$$11) {
			_7$$11 = (zephir_fast_strlen_ev(&queryString)) ? 1 : 0;
		}
		if (_7$$11) {
			ZEPHIR_INIT_VAR(&_8$$12);
			ZVAL_STRING(&_8$$12, "?");
			ZEPHIR_INIT_VAR(&_9$$12);
			zephir_fast_strpos(&_9$$12, &queryString, &_8$$12, 0 );
			if (!ZEPHIR_IS_FALSE_IDENTICAL(&_9$$12)) {
				ZEPHIR_INIT_VAR(&_10$$13);
				ZEPHIR_CONCAT_SV(&_10$$13, "&", &queryString);
				zephir_concat_self(uri, &_10$$13 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_VAR(&_11$$14);
				ZEPHIR_CONCAT_SV(&_11$$14, "?", &queryString);
				zephir_concat_self(uri, &_11$$14 TSRMLS_CC);
			}
		}
	}
	RETVAL_ZVAL(uri, 1, 0);
	RETURN_MM();

}

