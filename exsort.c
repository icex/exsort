#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "ext/standard/info.h"

#define SORT_NAME ex
#define SORT_TYPE int64_t
#define SORT_CMP(x, y) (x - y)
#include "sort.h"
 
#define PHP_EXSORT_VERSION "0.2"
#define PHP_EXSORT_EXTNAME "exsort"
 
extern zend_module_entry exsort_module_entry;
#define phpext_exsort_ptr &exsort_module_entry
 

PHP_MINIT_FUNCTION(exsort);
PHP_MINFO_FUNCTION(exsort);
PHP_FUNCTION(exsort);

// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
static zend_function_entry my_functions[] = {
    PHP_FE(exsort, NULL)
    {NULL, NULL, NULL}
};
 
// the following code creates an entry for the module and registers it with Zend.
zend_module_entry exsort_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_EXSORT_EXTNAME,
    my_functions,
    PHP_MINIT(exsort), // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    PHP_MINFO(exsort), // name of the MINFO function or NULL if not applicable
#if ZEND_MODULE_API_NO >= 20010901
    PHP_EXSORT_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};



PHP_MINIT_FUNCTION(exsort)
{
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_TIM_SORT",                 0,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_MERGE_SORT_IN_PLACE",      1,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_SHELL_SORT",               2,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_HEAP_SORT",                3,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_MERGE_SORT",               4,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_QUICK_SORT_NATIVE",        5,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_MERGE_SORT_NATIVE",        6,CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("EXSORT_ALGO_QUICK_SORT",               7,CONST_PERSISTENT);
    return SUCCESS;
}


PHP_MINFO_FUNCTION(exsort)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "ExSort support", "enabled");
    php_info_print_table_row(2, "ExSort Extension Version", PHP_EXSORT_VERSION);
    php_info_print_table_row(2, "ExSort algorithms supported:", "EXSORT_ALGO_TIM_SORT,\nEXSORT_ALGO_MERGE_SORT_IN_PLACE,\nEXSORT_ALGO_SHELL_SORT,\nEXSORT_ALGO_HEAP_SORT,\nEXSORT_ALGO_MERGE_SORT,\nEXSORT_ALGO_QUICK_SORT_NATIVE,\nEXSORT_ALGO_MERGE_SORT_NATIVE,\nEXSORT_ALGO_QUICK_SORT");
    php_info_print_table_end();
    php_info_print_box_start(0);
    PUTS("This extension makes use of sorting routine implementations written by Christopher Swenson and available at https://github.com/swenson/sort");
    php_info_print_box_end();
}
 
ZEND_GET_MODULE(exsort)


PHP_FUNCTION(exsort)
{
    char *name;
    int name_len;
    long sort_flag;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len,&sort_flag) == FAILURE) {
        RETURN_NULL();
    }

    int size = 1, i =0;
    const char separator=',';
    char *src,  *end;


    src=name;
    while ((end = strchr(src, separator)) != NULL)
    {
      ++size;
      src = end + 1;
    }

    int64_t arr[size];
    src=name;
    for(i = 0; i < size; ++i)
    {
      arr[i]=strtol(src,&src,10);
      src=src+1;
    }


    switch( sort_flag ) 
    {
        case 0://EXSORT_ALGO_TIM_SORT
            ex_tim_sort(arr, size);
            break;
        case 1://EXSORT_ALGO_MERGE_SORT_IN_PLACE
            ex_merge_sort_in_place(arr, size);
            break;
        case 2://EXSORT_ALGO_SHELL_SORT
            ex_shell_sort(arr, size);
            break;
        case 3://EXSORT_ALGO_HEAP_SORT
            ex_heap_sort(arr, size);
            break;
        case 4://EXSORT_ALGO_MERGE_SORT
            //ex_merge_sort(arr, size);
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Merge Sort algo is buggy! Disabled.");
            RETURN_BOOL(0);
            break;
#ifndef __linux__
        case 5://EXSORT_ALGO_QUICK_SORT_NATIVE
            ex_quick_sort(arr, size);
            break;
        case 6://EXSORT_ALGO_MERGE_SORT_NATIVE
            mergesort(arr, size, sizeof(int64_t), simple_cmp);
            break;
#endif
        case 7://EXSORT_ALGO_QUICK_SORT
            qsort(arr, size, sizeof(int64_t), simple_cmp);
        default :
            ex_tim_sort(arr, size);
    }
    

    //verify 
    for (i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) {
          php_error_docref(NULL TSRMLS_CC, E_WARNING, "Sanity check: Array not properly sorted!");
          RETURN_BOOL(0);
        }
    }

    array_init(return_value);
    for (i = 0; i < size; ++i)
        add_index_long(return_value, i, arr[i]);
}