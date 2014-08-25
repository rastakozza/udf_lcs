udf_lcs
=======

MySQL/MariaDB UDF function for Longest Common Substring

* build

```
gcc -I /usr/include/mysql -shared -o udf_lcs.so udf_lcs.c -fpic -O3
gcc -o test_lcs test_lcs.c udf_lcs.so -Wl,-rpath,./ -L./ -O3
```


* test

```
./runtest.sh
```


* install

 * on shell
 ```
 strip udf_lcs.so
 cp udf_lcs.so /usr/lib/mysql/plugin/
 ```

 * on MySQL/MariaDB
 ```
 CREATE FUNCTION lcs RETURNS STRING SONAME 'udf_lcs.so';
 ```

