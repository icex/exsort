ExSort
======

PHP Extended Sorting Extension

Author
======

Bogdan Popa (ice.bogdan@gmail.com)

If you think this is useful please consider a donation:
https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=P4BBXXS9U8DA8&lc=US&item_name=Bogdan%20Popa&item_number=exsort&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_LG%2egif%3aNonHosted

How to build
------------
```shell
$ cd exsort
$ phpize
$ ./configure  --enable-exsort
$ make
# make install
```
add the extension line to php.ini
`exsort.so`

How to test
-----------
```shell
$ cd exsort/php_tests/
$ php large_test.php
```

How to use
----------
```php
array exsort ( string $array_string , int $sort_flags  )
```
where `$array_string` is a comma-delimited list of numbers(serves my purposes this way right now)
and `$sort_flags` is the sorting algorithm

Sort flags:
EXSORT_ALGO_TIM_SORT, EXSORT_ALGO_MERGE_SORT_IN_PLACE, EXSORT_ALGO_SHELL_SORT, EXSORT_ALGO_HEAP_SORT, EXSORT_ALGO_MERGE_SORT, EXSORT_ALGO_QUICK_SORT_NATIVE, EXSORT_ALGO_MERGE_SORT_NATIVE, EXSORT_ALGO_QUICK_SORT

Performance
-----------

Check out the output from large_test.php. It benchmarks all algorithms compared to the regular sort() function.
```shell
$ php large_test.php 
----------------------------------------------
array count: 74001
sort time: 0.3533420563
mem used: 19924.5234 KB
----------------------------------------------

✔ algo #0 74001 0.0219919682 sec 16085.5781 KB
✔ algo #1 74001 0.0277831554 sec 16085.5625 KB
✔ algo #2 74001 0.0357818604 sec 16085.6641 KB
✔ algo #3 74001 0.0375499725 sec 16085.7031 KB
✔ algo #5 74001 0.0289521217 sec 16085.9062 KB
✔ algo #6 74001 0.0300860405 sec 16085.4531 KB
✔ algo #7 74001 0.0285148621 sec 16085.5469 KB
----------------------------------------------
```
References
----------
* http://en.wikipedia.org/wiki/Sorting_algorithm
* This extension makes use of sorting routine implementations written by Christopher Swenson available at https://github.com/swenson/sort


License
-------

All code in this repository, unless otherwise specified, is hereby
licensed under the MIT Public License

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.