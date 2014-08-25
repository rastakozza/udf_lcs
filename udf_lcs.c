#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong; /* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
#include <m_string.h>
#else
/* when compiled as standalone */
#include <string.h>
#endif /*MYSQL_SERVER*/
#endif /*STANDARD*/
#include <mysql.h>
#include <ctype.h>

#ifdef HAVE_DLOPEN

#include "udf_lcs.h"

int __lcs (const char *first, const char *second, int firstl, int secondl, char *max);

my_bool lcs_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void lcs_deinit(UDF_INIT *initid);
char *lcs(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

int __lcs (const char *first, const char *second, int firstl, int secondl, char *result) {

	const char *sub, *max;
	int i, j, k, subl = 0, maxl = 0;

	for (i=0; i+maxl < firstl; ++i) {
		for (j=0; j+maxl < secondl; ++j) {
			for (k=1; i+k <= firstl && j+k <= secondl; ++k) {
				if (first[i+k-1] != second[j+k-1]) {
					break;
				}
				if (k == 1) sub = first + i;
				subl = k;
			}
			if (subl > maxl) {
				max = sub;
				maxl = subl;
			}
			subl = 0;
		}
	}

	strncpy(result, max, maxl);

	return maxl;
}


my_bool lcs_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {

	if (args->arg_count != 2 || args->arg_type[0] != STRING_RESULT || args->arg_type[1] != STRING_RESULT) {
		strcpy(message, "Function requires 2 arguments, (string, string)");
		return 1;
	}

	initid->max_length = LCS_MAX;
	return 0;
}


void lcs_deinit(UDF_INIT *initid) {
}


char *lcs(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args,
		char *result, unsigned long *length, char *is_null,
		char *error __attribute__((unused))) {

	const char *first = args->args[0];
	const char *second = args->args[1];

	if (!first || !second) {
		*is_null = 1;
		return 0;
	}

	int n = args->lengths[0];
	int m = args->lengths[1];

	*length = __lcs(first, second, n, m, result);

	return result;
}


#endif /*HAVE_DLOPEN*/
