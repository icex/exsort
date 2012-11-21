<?php

ArraySort::test(null,1);

ini_set("error_reporting",0);
display_errors(0);
class ArraySort
{
	/* test*/
	public static function test($size=100000,$tests=1)
	{
		$baseMemory = memory_get_usage();
		if($size!==NULL)
		{
			$arr = array();
			for ($i=0; $i<$size; $i++) {
				$arr[] = mt_rand(0, 100000000);
			}
		}
		else
			require_once('data.php');
		
		$b = microtime(1);
		sort($arr, SORT_NUMERIC);
		$b=microtime(1) - $b;
		echo "----------------------------------------------\n";
		printf("array count: %d\n", count($arr));
		printf("sort time: %.10f\n", $b);
		printf("mem used: %.4f KB\n", (memory_get_usage() - $baseMemory)/1024);
		echo "----------------------------------------------\n";
		echo "\n";

		$arr=implode(',',$arr);
		#$sorted=exsort($arr,0);
		#print_r($sorted);
		#die("\n".count($sorted)."\n");
		$algos = array(EXSORT_ALGO_TIM_SORT,
		EXSORT_ALGO_MERGE_SORT_IN_PLACE,
		EXSORT_ALGO_SHELL_SORT,
		EXSORT_ALGO_HEAP_SORT,
		//EXSORT_ALGO_MERGE_SORT, //algo 4 crashes on high memory usage!!!
		EXSORT_ALGO_QUICK_SORT_NATIVE,
		EXSORT_ALGO_MERGE_SORT_NATIVE,
		EXSORT_ALGO_QUICK_SORT); 
		foreach ($algos as $algo) {
				
				$bench = microtime(true);
				for($i=0;$i<$tests;$i++)
				{
					$result = null;
					try {
						$result = exsort($arr,$algo);
					} catch (Exception $e) {
					}
				}
				$bench = (microtime(true) - $bench)/$tests;
				$status = $result ? (self::isSorted($result) ? '✔' : '✖') : '-';
				if($bench<$b and $status==='✔')
				{
					$color="\033[" ."0;32m";
				}
				elseif($status==='x')
				{
					$color="\033[" ."0;31m";
				}

				$end= "\033[0m";
				printf($color."%s algo #%s %-5s %.10f sec %-10.4f KB\n".$end, $status, $algo,count($result), $bench,(memory_get_usage() - $baseMemory)/1024 );

				if ($status=='x') {
					//print_r($result);
					echo "\n\ntotal: ".count($result);
				}

			}
		echo "----------------------------------------------\n";
	}


	/* util */

	public static function isSorted(array $array)
	{
		$tmp = -INF;
		for ($i=0; $i<count($array); $i++) 
		{
			if ($array[$i]<$tmp) {
				return false;
				//echo $array[$i]."<".$tmp."\n";
			}
			$tmp = $array[$i];
		}
		return true;
	}
 
}