// Resources needed across all wdist modules.

#ifndef __WDIST_COMMON_H__
#define __WDIST_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

// Uncomment this to build this without CBLAS/CLAPACK.
// #define NOLAPACK

// Uncomment this to prevent all unstable features from being accessible from
// the command line.
// #define STABLE_BUILD

#ifdef STABLE_BUILD
#define UNSTABLE goto main_unstable_disabled
#else
#define UNSTABLE
#endif

#if _WIN32
// needed for MEMORYSTATUSEX
#ifndef _WIN64
#define WINVER 0x0500
#endif
#else // Unix
#include <sys/stat.h>
#endif

#if _WIN32
#define PRId64 "I64d"
#define PRIu64 "I64u"
#define fseeko fseeko64
#define ftello ftello64
#include <windows.h>
#include <process.h>
#define pthread_t HANDLE
#define THREAD_RET_TYPE unsigned __stdcall
#define THREAD_RETURN return 0
#else
#include <pthread.h>
#define THREAD_RET_TYPE void*
#define THREAD_RETURN return NULL
#ifdef __cplusplus
#define PRId64 "lld"
#endif
#endif

#define uint64_t unsigned long long
#define int64_t long long

#ifdef _WIN64
#define __LP64__
#define CTZLU __builtin_ctzll
#else
#define CTZLU __builtin_ctzl
#ifndef __LP64__
#define uintptr_t unsigned long
#define intptr_t long
#endif
#endif

#ifdef __cplusplus
#include <algorithm>
#endif

#ifdef __LP64__

#include <emmintrin.h>
#define FIVEMASK 0x5555555555555555LLU
typedef union {
  __m128i vi;
  __m128d vd;
  uintptr_t u8[2];
  double d8[2];
  uint32_t u4[4];
} __uni16;
#define ZEROLU 0LLU
#define ONELU 1LLU

#if _WIN32 // i.e. Win64

#ifndef PRIuPTR
#define PRIuPTR PRIu64
#endif
#ifndef PRIdPTR
#define PRIdPTR PRId64
#endif

#else // not _WIN32

#ifndef PRIuPTR
#define PRIuPTR "ld"
#endif
#ifndef PRIdPTR
#define PRIdPTR "lu"
#endif

#endif // Win64

#else // not __LP64__

#define FIVEMASK 0x55555555
#define ZEROLU 0LU
#define ONELU 1LU
#ifndef PRIuPTR
#define PRIuPTR "lu"
#endif
#ifndef PRIdPTR
#define PRIdPTR "ld"
#endif

#endif // __LP64__

#include "zlib-1.2.8/zlib.h"
#include "SFMT.h"

#define PI 3.1415926535897932
#define RECIP_2_32 0.00000000023283064365386962890625
// floating point comparison-to-nonzero tolerance, currently 2^{-30}
#define EPSILON 0.000000000931322574615478515625
// less tolerant versions (2^{-35}, 2^{-44}) for some exact calculations
#define SMALLISH_EPSILON 0.00000000002910383045673370361328125
#define SMALL_EPSILON 0.00000000000005684341886080801486968994140625
// at least sqrt(SMALL_EPSILON)
#define BIG_EPSILON 0.000000476837158203125
// 53-bit double precision limit
#define DOUBLE_PREC_LIMIT 0.00000000000000011102230246251565404236316680908203125
#define TWO_63 9223372036854775808.0

// 2^{-83} bias to give exact tests maximum ability to determine tiny p-values.
// (~2^{-53} is necessary to take advantage of denormalized small numbers, then
// allow tail sum to be up to 2^30.)
#define EXACT_TEST_BIAS 0.00000000000000000000000010339757656912845935892608650874535669572651386260986328125

#define RET_SUCCESS 0
#define RET_NOMEM 1
#define RET_OPEN_FAIL 2
#define RET_INVALID_FORMAT 3
#define RET_CALC_NOT_YET_SUPPORTED 4
#define RET_INVALID_CMDLINE 5
#define RET_WRITE_FAIL 6
#define RET_READ_FAIL 7
#define RET_HELP 8
#define RET_THREAD_CREATE_FAIL 9
#define RET_ALLELE_MISMATCH 10
#define RET_NULL_CALC 11
#define LOAD_PHENO_LAST_COL 127

#define MISC_AFFECTION_01 1LLU
#define MISC_PRUNE 2LLU
#define MISC_TAIL_PHENO 4LLU
#define MISC_HWE_ALL 8LLU
#define MISC_NONFOUNDERS 0x10LLU
#define MISC_MAF_SUCC 0x20LLU
#define MISC_FREQ_COUNTS 0x40LLU
#define MISC_FREQX 0x80LLU
#define MISC_KEEP_ALLELE_ORDER 0x100LLU
#define MISC_SET_HH_MISSING 0x200LLU
#define MISC_KEEP_AUTOCONV 0x400LLU
#define MISC_LOAD_CLUSTER_KEEP_NA 0x800LLU
#define MISC_WRITE_CLUSTER_OMIT_UNASSIGNED 0x1000LLU
#define MISC_UNRELATED_HERITABILITY_STRICT 0x2000LLU

#define CALC_RELATIONSHIP 1LLU
#define CALC_IBC 2LLU
#define CALC_DISTANCE 4LLU
#define CALC_PLINK_DISTANCE_MATRIX 8LLU
#define CALC_PLINK_IBS_MATRIX 0x10LLU
#define CALC_GDISTANCE_MASK 0x1cLLU
#define CALC_GROUPDIST 0x20LLU
#define CALC_REGRESS_DISTANCE 0x40LLU
#define CALC_UNRELATED_HERITABILITY 0x80LLU
#define CALC_FREQ 0x100LLU
#define CALC_REL_CUTOFF 0x200LLU
#define CALC_WRITE_SNPLIST 0x400LLU
#define CALC_LIST_23_INDELS 0x800LLU
#define CALC_GENOME 0x1000LLU
#define CALC_REGRESS_REL 0x2000LLU
#define CALC_LD_PRUNE 0x4000LLU
#define CALC_LD_PRUNE_PAIRWISE 0x8000LLU
#define CALC_REGRESS_PCS 0x10000LLU
#define CALC_REGRESS_PCS_DISTANCE 0x20000LLU
#define CALC_MAKE_BED 0x40000LLU
#define CALC_RECODE 0x80000LLU
#define CALC_MERGE 0x100000LLU
#define CALC_WRITE_COVAR 0x200000LLU
#define CALC_WRITE_CLUSTER 0x400000LLU
#define CALC_MODEL 0x800000LLU
#define CALC_HARDY 0x1000000LLU
#define CALC_GXE 0x2000000LLU
#define CALC_IBS_TEST 0x4000000LLU
#define CALC_CLUSTER 0x8000000LLU
#define CALC_HOMOZYG 0x10000000LLU
#define CALC_NEIGHBOR 0x20000000LLU

#define M23_MALE 1
#define M23_FEMALE 2
#define M23_FORCE_MISSING_SEX 4
#define M23_SEX 7
#define M23_CONVERT_XY 8
#define M23_MAKE_XYLIST 0x10

#define MARKER_CMS_OPTIONAL 1
#define MARKER_CMS_FORCED 2

#define UNSORTED_CHROM 1
#define UNSORTED_BP 2
// probably insert unsorted centimorgans later
#define UNSORTED_SPLIT_CHROM 4

#define ALLOW_NO_SEX 1
#define MUST_HAVE_SEX 2

#define LGEN_REFERENCE 1
#define LGEN_ALLELE_COUNT 2

#define PHENO_ALL 1
#define PHENO_MERGE 2

#define FAM_COL_1 1
#define FAM_COL_34 2
#define FAM_COL_5 4
#define FAM_COL_6 8
#define FAM_COL_13456 15

#define FILTER_BINARY_CASES 1
#define FILTER_BINARY_CONTROLS 2
#define FILTER_BINARY_FEMALES 4
#define FILTER_BINARY_MALES 8
#define FILTER_BINARY_FOUNDERS 16
#define FILTER_BINARY_NONFOUNDERS 32

#define COVAR_NAME 1
#define COVAR_NUMBER 2

#define REL_CALC_COV 1
#define REL_CALC_SQ 2
#define REL_CALC_SQ0 4
#define REL_CALC_TRI 6
#define REL_CALC_SHAPEMASK 6
#define REL_CALC_GZ 8
#define REL_CALC_BIN 16
#define REL_CALC_GRM 32

// GCTA 1.10 format
#define REL_CALC_GRM_BIN 64

#define REL_CALC_SINGLE_PREC 128

#define DISTANCE_SQ 1
#define DISTANCE_SQ0 2
#define DISTANCE_TRI 3
#define DISTANCE_SHAPEMASK 3
#define DISTANCE_GZ 4
#define DISTANCE_BIN 8
#define DISTANCE_IBS 0x10
#define DISTANCE_1_MINUS_IBS 0x20
#define DISTANCE_ALCT 0x40
#define DISTANCE_TYPEMASK 0x70
#define DISTANCE_FLAT_MISSING 0x80
#define DISTANCE_3D 0x100

#define RECODE_12 1
#define RECODE_TAB 2
#define RECODE_DELIMX 4
#define RECODE_COMPOUND 8
#define RECODE_23 0x10
#define RECODE_A 0x20
#define RECODE_AD 0x40
#define RECODE_LGEN 0x80
#define RECODE_LGEN_REF 0x100
#define RECODE_LIST 0x200
#define RECODE_RLIST 0x400
#define RECODE_TRANSPOSE 0x800
#define RECODE_VCF 0x1000
#define RECODE_TYPEMASK 0x1ff0
#define RECODE_FID 0x2000
#define RECODE_IID 0x4000

#define GENOME_OUTPUT_GZ 1
#define GENOME_OUTPUT_FULL 2
#define GENOME_IBD_UNBOUNDED 4

#define WRITE_COVAR_PHENO 1
#define WRITE_COVAR_DUMMY 2

#define MERGE_MODE_MASK 7
#define MERGE_EQUAL_POS 8
#define MERGE_BINARY 16
#define MERGE_LIST 32

#define INDIV_SORT_NONE 1
#define INDIV_SORT_NATURAL 2
#define INDIV_SORT_ASCII 4

#define REGRESS_PCS_NORMALIZE_PHENO 1
#define REGRESS_PCS_SEX_SPECIFIC 2
#define REGRESS_PCS_CLIP 4

#define DUMMY_MISSING_GENO 1
#define DUMMY_MISSING_PHENO 2
#define DUMMY_SCALAR_PHENO 4
#define DUMMY_ACGT 8
#define DUMMY_1234 16
#define DUMMY_12 32

#define SIMULATE_QT 1
#define SIMULATE_TAGS 2
#define SIMULATE_HAPS 4
#define SIMULATE_ACGT 8
#define SIMULATE_1234 16
#define SIMULATE_12 32

#define MODEL_ASSOC 1
#define MODEL_FISHER 2
#define MODEL_PERM 4
#define MODEL_MPERM 8
#define MODEL_GENEDROP 16
#define MODEL_PERM_COUNT 32
#define MODEL_ASSOC_COUNTS 64
#define MODEL_ASSOC_P2 128
#define MODEL_ASSOC_FDEPR 256
#define MODEL_DMASK 466
#define MODEL_QT_MEANS 512
#define MODEL_PDOM 1024
#define MODEL_PREC 2048
#define MODEL_PGEN 4096
#define MODEL_PTREND 8192
#define MODEL_TRENDONLY 16384
#define MODEL_PMASK (MODEL_PDOM | MODEL_PREC | MODEL_PGEN | MODEL_PTREND | MODEL_TRENDONLY)
#define MODEL_LIN 32768
#define MODEL_QMASK (MODEL_QT_MEANS | MODEL_LIN)

#define MPERM_DUMP_BEST 1
#define MPERM_DUMP_ALL 2

// (2^31 - 1000001) / 2
#define APERM_MAX 1073241823

#define ADJUST_GC 2
#define ADJUST_LOG10 4
#define ADJUST_QQ 8
#define ADJUST_LAMBDA 16

#define CNV_MAKE_MAP 1
#define CNV_MAKE_MAP_LONG 2
#define CNV_CHECK_NO_OVERLAP 4
#define CNV_DEL 8
#define CNV_DUP 0x10
#define CNV_WRITE_FREQ 0x20
#define CNV_UNIQUE 0x40
#define CNV_DROP_NO_SEGMENT 0x80
#define CNV_INDIV_PERM 0x100
#define CNV_ENRICHMENT_TEST 0x200
#define CNV_TEST 0x400
#define CNV_TEST_FORCE_1SIDED 0x800
#define CNV_TEST_FORCE_2SIDED 0x1000
#define CNV_TEST_REGION 0x2000
#define CNV_TRACK 0x4000
#define CNV_SEGLIST 0x8000
#define CNV_REPORT_REGIONS 0x10000
#define CNV_VERBOSE_REPORT_REGIONS 0x20000
#define CNV_WRITE 0x40000
#define CNV_EXCLUDE_OFF_BY_1 0x80000

#define CNV_INTERSECT 1
#define CNV_EXCLUDE 2
#define CNV_COUNT 4

#define CNV_OVERLAP 1
#define CNV_OVERLAP_REGION 2
#define CNV_OVERLAP_UNION 3
#define CNV_DISRUPT 4

#define CNV_FREQ_EXCLUDE_ABOVE 1
#define CNV_FREQ_EXCLUDE_BELOW 2
#define CNV_FREQ_EXCLUDE_EXACT 4
#define CNV_FREQ_INCLUDE_EXACT 8
#define CNV_FREQ_FILTER 15
#define CNV_FREQ_OVERLAP 16
#define CNV_FREQ_METHOD2 32

#define SEGMENT_GROUP 1

#define WKSPACE_MIN_MB 64
#define WKSPACE_DEFAULT_MB 2048

#define CACHELINE 64 // assumed number of bytes per cache line, for alignment
#define CACHELINE_INT32 (CACHELINE / sizeof(int32_t))
#define CACHELINE_INT64 (CACHELINE / sizeof(int64_t))
#define CACHELINE_DBL (CACHELINE / sizeof(double))

#define CACHEALIGN(val) ((val + (CACHELINE - 1)) & (~(CACHELINE - 1)))
#define CACHEALIGN_DBL(val) ((val + (CACHELINE_DBL - 1)) & (~(CACHELINE_DBL - 1)))
#define MAXV(aa, bb) ((bb) > (aa))? (bb) : (aa)
#define MINV(aa, bb) ((aa) > (bb))? (bb) : (aa)

#define _FILE_OFFSET_BITS 64
#if _WIN32
#define MAX_THREADS 63
#define MAX_THREADS_P1 64
#else
#define MAX_THREADS 127
#define MAX_THREADS_P1 128
#endif

#ifdef __LP64__
#define BITCT 64
#else
#define BITCT 32
#endif

#define BITCT2 (BITCT / 2)

// size of generic text line load buffer.  .ped lines can of course be longer
#define MAXLINELEN 131072

// note that this is NOT foolproof: see e.g.
// http://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html .  (This
// is why I haven't bothered with OS-based #ifdefs here.)  But it should be
// good enough in practice.
#define FNAMESIZE 4096

// allow extensions like .model.trend.fisher.set.score.adjusted
#define MAX_POST_EXT 39

// number of types of jackknife values to precompute (x^2, y^2, x, y, xy)
#define JACKKNIFE_VALS_DIST 5
#define JACKKNIFE_VALS_GROUPDIST 3

#ifdef __LP64__
#define AAAAMASK 0xaaaaaaaaaaaaaaaaLLU
// number of snp-major .bed lines to read at once for distance calc if exponent
// is nonzero.
#define MULTIPLEX_DIST_EXP 64
// number of snp-major .bed lines to read at once for relationship calc
#define MULTIPLEX_REL 60
#else
// N.B. 32-bit version not as carefully tested or optimized, but I'll try to
// make sure it works properly
#define AAAAMASK 0xaaaaaaaaU
#define MULTIPLEX_DIST_EXP 28
#define MULTIPLEX_REL 30
#endif

// used to size a few tables
#define EXPECTED_MISSING_FREQ 0.05

// fit 4 pathologically long IDs plus a bit extra
extern char tbuf[];

extern sfmt_t sfmt;

extern const char errstr_fopen[];
extern const char errstr_append[];
extern const char errstr_thread_create[];
extern const char cmdline_format_str[];
extern const char errstr_phenotype_format[];

extern FILE* logfile;
extern char logbuf[MAXLINELEN];
extern int32_t debug_on;
extern int32_t log_failed;

extern uintptr_t g_indiv_ct;
extern uint32_t g_thread_ct;

typedef struct ll_str_struct {
  struct ll_str_struct* next;
  char ss[];
} Ll_str;

typedef struct two_col_params_struct {
  uint32_t colx;
  uint32_t colid;
  uint32_t skip;
  char skipchar;
  char fname[];
} Two_col_params;

uint32_t push_ll_str(Ll_str** ll_stack_ptr, const char* ss);

void logstr(const char* ss);

void logprint(const char* ss);

void logprintb();

int32_t fopen_checked(FILE** target_ptr, const char* fname, const char* mode);

static inline int32_t fwrite_checkedz(const void* buf, size_t len, FILE* outfile) {
  return ((!len) || fwrite(buf, len, 1, outfile))? 0 : -1;
}


static inline int32_t fwrite_checked(const void* buf, size_t len, FILE* outfile) {
  return fwrite(buf, len, 1, outfile)? 0 : -1;
}

static inline int32_t fputs_checked(const char* ss, FILE* outfile) {
  return (fputs(ss, outfile) == EOF);
}

static inline void fclose_cond(FILE* fptr) {
  if (fptr) {
    fclose(fptr);
  }
}

static inline int32_t fclose_null(FILE** fptr_ptr) {
  int32_t ii;
  ii = fclose(*fptr_ptr);
  *fptr_ptr = NULL;
  return ii;
}

int32_t gzopen_checked(gzFile* target_ptr, const char* fname, const char* mode);

// handle len == 0.  If that's unnecessary, just use !gzwrite instead
static inline int32_t gzwrite_checked(gzFile gz_outfile, const void* buf, size_t len) {
  if ((!len) || gzwrite(gz_outfile, buf, len)) {
    return 0;
  }
  return -1;
}

static inline void gzclose_cond(gzFile gz_outfile) {
  if (gz_outfile) {
    gzclose(gz_outfile);
  }
}

static inline int32_t flexwrite_checked(FILE* outfile, gzFile gz_outfile, char* contents, uintptr_t len) {
  if (outfile) {
    return fwrite_checked(contents, len, outfile);
  } else {
    return gzwrite_checked(gz_outfile, contents, len);
  }
}

static inline int32_t bed_suffix_conflict(uint64_t calculation_type, uint32_t recode_modifier) {
  return (calculation_type & CALC_MAKE_BED) || ((calculation_type & CALC_RECODE) && (recode_modifier & (RECODE_LGEN | RECODE_LGEN_REF | RECODE_RLIST)));
}

// manually managed, very large stack
extern unsigned char* wkspace_base;
extern uintptr_t wkspace_left;

unsigned char* wkspace_alloc(uintptr_t size);

static inline int32_t wkspace_alloc_c_checked(char** dc_ptr, uintptr_t size) {
  *dc_ptr = (char*)wkspace_alloc(size);
  return (*dc_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_d_checked(double** dp_ptr, uintptr_t size) {
  *dp_ptr = (double*)wkspace_alloc(size);
  return (*dp_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_f_checked(float** fp_ptr, uintptr_t size) {
  *fp_ptr = (float*)wkspace_alloc(size);
  return (*fp_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_i_checked(int32_t** ip_ptr, uintptr_t size) {
  *ip_ptr = (int32_t*)wkspace_alloc(size);
  return (*ip_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_uc_checked(unsigned char** ucp_ptr, uintptr_t size) {
  *ucp_ptr = wkspace_alloc(size);
  return (*ucp_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_ui_checked(uint32_t** uip_ptr, uintptr_t size) {
  *uip_ptr = (uint32_t*)wkspace_alloc(size);
  return (*uip_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_ul_checked(uintptr_t** ulp_ptr, uintptr_t size) {
  *ulp_ptr = (uintptr_t*)wkspace_alloc(size);
  return (*ulp_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_ll_checked(int64_t** llp_ptr, uintptr_t size) {
  *llp_ptr = (int64_t*)wkspace_alloc(size);
  return (*llp_ptr)? 0 : 1;
}

static inline int32_t wkspace_alloc_ull_checked(uint64_t** ullp_ptr, uintptr_t size) {
  *ullp_ptr = (uint64_t*)wkspace_alloc(size);
  return (*ullp_ptr)? 0 : 1;
}

void wkspace_reset(void* new_base);

static inline unsigned char* top_alloc(uintptr_t* topsize_ptr, uint32_t size) {
  uintptr_t ts = *topsize_ptr + ((size + 15) & (~(15 * ONELU)));
  if (ts > wkspace_left) {
    return NULL;
  } else {
    *topsize_ptr = ts;
    return &(wkspace_base[wkspace_left - ts]);
  }
}

static inline Ll_str* top_alloc_llstr(uintptr_t* topsize_ptr, uint32_t size) {
  return (Ll_str*)top_alloc(topsize_ptr, size + sizeof(Ll_str));
}

static inline int32_t is_letter(char cc) {
  return (((((unsigned char)cc) & 192) == 64) && (((((unsigned char)cc) - 1) & 31) < 26));
}

static inline int32_t is_digit(char cc) {
  return (cc <= '9') && (cc >= '0');
}

static inline int32_t is_not_digit(char cc) {
  return (cc > '9') || (cc < '0');
}

static inline int32_t is_not_nzdigit(char cc) {
  return (cc > '9') || (cc <= '0');
}

// may as well treat all chars < 32, except tab, as eoln...
static inline int32_t is_eoln(char cc) {
  return (((unsigned char)cc) < 32) && (cc != '\t');
}

// kns = "known non-space" (where tab counts as a space)
static inline int32_t is_eoln_kns(char cc) {
  return ((unsigned char)cc) < 32;
}

static inline int32_t is_eoln_or_comment(char cc) {
  return (((unsigned char)cc) < 32) || (cc == '#');
}

static inline int32_t no_more_items(char* sptr) {
  return ((!sptr) || is_eoln(*sptr));
}

static inline int32_t no_more_items_kns(char* sptr) {
  return ((!sptr) || is_eoln_kns(*sptr));
}

static inline char* skip_initial_spaces(char* sptr) {
  while ((*sptr == ' ') || (*sptr == '\t')) {
    sptr++;
  }
  return sptr;
}

/*
static inline int32_t is_space_or_eoln(char cc) {
  // ' ', \t, \n, \0, \r
#ifdef __LP64__
  return ((((unsigned char)cc) <= 32) && (0x100002601LLU & (1LLU << cc)));
#else
  return ((((unsigned char)cc) <= 32) && ((cc == ' ') || (0x2601LU & (ONELU << cc))));
#endif
}
*/
static inline int32_t is_space_or_eoln(char cc) {
  return ((unsigned char)cc) <= 32;
}

uint32_t match_upper(char* ss, const char* fixed_str);

uint32_t match_upper_nt(char* ss, const char* fixed_str, uint32_t ct);

int32_t atoiz(char* ss, int32_t* sval);

uint32_t strtoui32(char* ss, uint32_t* valp);

static inline char* memseta(char* target, const unsigned char val, uintptr_t ct) {
  memset(target, val, ct);
  return &(target[ct]);
}

static inline char* memcpya(char* target, const void* source, uintptr_t ct) {
  memcpy(target, source, ct);
  return &(target[ct]);
}

static inline char* memcpyb(char* target, const void* source, uint32_t ct) {
  // Same as memcpya, except the return value is one byte earlier.  Generally
  // used when source is a null-terminated string of known length and we want
  // to copy the null, but sometimes we need to append later.
  memcpy(target, source, ct);
  return &(target[ct - 1]);
}

static inline char* memcpyax(char* target, const void* source, uint32_t ct, const char extra_char) {
  memcpy(target, source, ct);
  target[ct] = extra_char;
  return &(target[ct + 1]);
}

static inline void memcpyx(char* target, const void* source, uint32_t ct, const char extra_char) {
  memcpy(target, source, ct);
  target[ct] = extra_char;
}

static inline void memcpyl3(char* target, const void* source) {
  // when it's safe to clobber the fourth character, this is faster
  *((uint32_t*)target) = *((uint32_t*)source);
}

static inline char* memcpyl3a(char* target, const void* source) {
  memcpyl3(target, source);
  return &(target[3]);
}

static inline char* strcpya(char* target, const void* source) {
  uintptr_t slen = strlen((char*)source);
  memcpy(target, source, slen);
  return &(target[slen]);
}

static inline char* strcpyax(char* target, const void* source, const char extra_char) {
  uintptr_t slen = strlen((char*)source);
  memcpy(target, source, slen);
  target[slen] = extra_char;
  return &(target[slen + 1]);
}

int32_t get_next_noncomment(FILE* fptr, char** lptr_ptr);

int32_t get_next_noncomment_excl(FILE* fptr, char** lptr_ptr, uintptr_t* marker_exclude, uintptr_t* marker_uidx_ptr);

char* item_end(char* sptr);

// does not return NULL if item ends with null char
char* item_endl(char* sptr);

// item_endl without checking if sptr == NULL
// also assumes we are currently in an item
static inline char* item_endnn(char* sptr) {
  while (!is_space_or_eoln(*(++sptr)));
  return sptr;
}

void get_top_two(uint32_t* uint_arr, uintptr_t uia_size, uintptr_t* top_idx_ptr, uintptr_t* second_idx_ptr);

int32_t intlen(int32_t num);

int32_t strlen_se(char* ss);

int32_t strcmp_se(char* s_read, const char* s_const, uint32_t len);

char* next_item(char* sptr);

char* next_item_mult(char* sptr, uint32_t ct);

static inline void copy_nse(char* target, char* source) {
  uint32_t uii;
  if (source) {
    uii = strlen_se(source);
    memcpy(target, source, uii);
    target[uii] = '\0';
  } else {
    *target = '\0';
  }
}

static inline char* write_item_nt(char* read_ptr, FILE* outfile) {
  // assumes read_ptr is at the beginning of an item to write
  uint32_t slen = strlen_se(read_ptr);
  fwrite(read_ptr, 1, slen, outfile);
  return skip_initial_spaces(&(read_ptr[slen + 1]));
}

static inline char* write_item(char* read_ptr, FILE* outfile) {
  uint32_t slen = strlen_se(read_ptr);
  fwrite(read_ptr, 1, slen, outfile);
  putc('\t', outfile);
  return skip_initial_spaces(&(read_ptr[slen + 1]));
}

static inline char* fw_strcpyn(uint32_t min_width, uint32_t source_len, char* source, char* dest) {
  if (source_len < min_width) {
    memcpy(memseta(dest, 32, min_width - source_len), source, source_len);
    return &(dest[min_width]);
  } else {
    return memcpya(dest, source, source_len);
  }
}

static inline char* fw_strcpy(uint32_t min_width, char* source, char* dest) {
  return fw_strcpyn(min_width, strlen(source), source, dest);
}

static inline void intprint2(char* buf, uint32_t num) {
  uint32_t quotient;
  if (num < 10) {
    *buf++ = ' ';
    *buf = '0' + num;
    return;
  }
  quotient = num / 10;
  *buf++ = '0' + quotient;
  *buf = '0' + num - (quotient * 10);
}

char* uint32_write(char* start, uint32_t uii);

char* uint32_writew7(char* start, uint32_t uii);

char* uint32_writew8(char* start, uint32_t uii);

char* uint32_writew10(char* start, uint32_t uii);

char* double_e_write(char* start, double dxx);

char* float_e_write(char* start, float dxx);

char* double_f_writew6(char* start, double dxx);

char* double_f_writew74(char* start, double dxx);

char* double_g_write(char* start, double dxx);

char* float_g_write(char* start, float dxx);

static inline char* width_force(uint32_t min_width, char* startp, char* endp) {
  uintptr_t diff = (endp - startp);
  if (diff >= min_width) {
    return endp;
  } else {
    diff = min_width - diff;
    do {
      --endp;
      endp[diff] = *endp;
    } while (endp > startp);
    memset(startp, 32, diff);
    return &(startp[min_width]);
  }
}

char* double_g_writewx4(char* start, double dxx, uint32_t min_width);

static inline char* uint32_writex(char* start, uint32_t uii, const char extra_char) {
  char* penult = uint32_write(start, uii);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* uint32_writew7x(char* start, uint32_t uii, const char extra_char) {
  char* penult = uint32_writew7(start, uii);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* double_e_writex(char* start, double dxx, const char extra_char) {
  char* penult = double_e_write(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* float_e_writex(char* start, float dxx, const char extra_char) {
  char* penult = float_e_write(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* double_f_writew6x(char* start, double dxx, const char extra_char) {
  char* penult = double_f_writew6(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* double_f_writew74x(char* start, double dxx, const char extra_char) {
  char* penult = double_f_writew74(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* double_g_writex(char* start, double dxx, const char extra_char) {
  char* penult = double_g_write(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* float_g_writex(char* start, float dxx, const char extra_char) {
  char* penult = float_g_write(start, dxx);
  *penult = extra_char;
  return &(penult[1]);
}

static inline char* double_g_writewx4x(char* start, double dxx, uint32_t min_width, const char extra_char) {
  char* penult = double_g_writewx4(start, dxx, min_width);
  *penult = extra_char;
  return &(penult[1]);
}

static inline void read_next_terminate(char* target, char* source) {
  while (!is_space_or_eoln(*source)) {
    *target++ = *source++;
  }
  *target = '\0';
}

void chrom_print_human_terminate(char* buf, uint32_t num);

void magic_num(uint32_t divisor, uint64_t* multp, uint32_t* pre_shiftp, uint32_t* post_shiftp, uint32_t* incrp);

static inline void set_bit_noct(uintptr_t* exclude_arr, uint32_t loc) {
  exclude_arr[loc / BITCT] |= (ONELU << (loc % BITCT));
}

void set_bit(uintptr_t* bit_arr, uint32_t loc, uintptr_t* bit_set_ct_ptr);

void set_bit_sub(uintptr_t* bit_arr, uint32_t loc, uintptr_t* bit_unset_ct_ptr);

static inline void clear_bit_noct(uintptr_t* exclude_arr, uint32_t loc) {
  exclude_arr[loc / BITCT] &= ~(ONELU << (loc % BITCT));
}

void clear_bit(uintptr_t* exclude_arr, uint32_t loc, uintptr_t* include_ct_ptr);

static inline int32_t is_set(uintptr_t* exclude_arr, uint32_t loc) {
  return (exclude_arr[loc / BITCT] >> (loc % BITCT)) & 1;
}

static inline int32_t is_founder(uintptr_t* founder_info, uint32_t loc) {
  return ((!founder_info) || ((founder_info[loc / BITCT]) & (ONELU << (loc % BITCT))));
}

int32_t next_non_set_unsafe(uintptr_t* exclude_arr, uint32_t loc);

int32_t next_non_set(uintptr_t* exclude_arr, uint32_t loc, uint32_t ceil);

int32_t next_set_unsafe(uintptr_t* include_arr, uint32_t loc);

// These functions seem to optimize better than memset(arr, 0, x) under gcc.
static inline void fill_long_zero(intptr_t* larr, size_t size) {
  intptr_t* lptr = &(larr[size]);
  while (larr < lptr) {
    *larr++ = 0;
  }
}

static inline void fill_ulong_zero(uintptr_t* ularr, size_t size) {
  uintptr_t* ulptr = &(ularr[size]);
  while (ularr < ulptr) {
    *ularr++ = 0;
  }
}

static inline void fill_long_one(intptr_t* larr, size_t size) {
  intptr_t* lptr = &(larr[size]);
  while (larr < lptr) {
    *larr++ = -1;
  }
}

static inline void fill_ulong_one(uintptr_t* ularr, size_t size) {
  uintptr_t* ulptr = &(ularr[size]);
  while (ularr < ulptr) {
    *ularr++ = ~ZEROLU;
  }
}

static inline void fill_int_zero(int32_t* iarr, size_t size) {
#ifdef __LP64__
  fill_long_zero((intptr_t*)iarr, size >> 1);
  if (size & 1) {
    iarr[size - 1] = 0;
  }
#else
  fill_long_zero((intptr_t*)iarr, size);
#endif
}

static inline void fill_int_one(int32_t* iarr, size_t size) {
#ifdef __LP64__
  fill_long_one((intptr_t*)iarr, size >> 1);
  if (size & 1) {
    iarr[size - 1] = -1;
  }
#else
  fill_long_one((intptr_t*)iarr, size);
#endif
}

static inline void fill_uint_zero(uint32_t* uiarr, size_t size) {
#ifdef __LP64__
  fill_long_zero((intptr_t*)uiarr, size >> 1);
  if (size & 1) {
    uiarr[size - 1] = 0;
  }
#else
  fill_long_zero((intptr_t*)uiarr, size);
#endif
}

static inline void fill_uint_one(uint32_t* uiarr, size_t size) {
#ifdef __LP64__
  fill_ulong_one((uintptr_t*)uiarr, size >> 1);
  if (size & 1) {
    uiarr[size - 1] = ~0U;
  }
#else
  fill_ulong_one((uintptr_t*)uiarr, size);
#endif
}

static inline void fill_float_zero(float* farr, size_t size) {
  float* fptr = &(farr[size]);
  while (farr < fptr) {
    *farr++ = 0.0;
  }
}

static inline void fill_double_zero(double* darr, size_t size) {
  double* dptr = &(darr[size]);
  while (darr < dptr) {
    *darr++ = 0.0;
  }
}

void fill_idx_to_uidx(uintptr_t* exclude_arr, uint32_t item_ct, uint32_t* idx_to_uidx);

void fill_uidx_to_idx(uintptr_t* exclude_arr, uint32_t item_ct, uint32_t* uidx_to_idx);

void fill_uidx_to_idx_incl(uintptr_t* include_arr, uint32_t item_ct, uint32_t* uidx_to_idx);

void fill_vec_55(uintptr_t* vec, uint32_t ct);

static inline void free_cond(void* memptr) {
  if (memptr) {
    free(memptr);
  }
}

static inline double get_maf(double allele_freq) {
  if (allele_freq < 0.5) {
    return allele_freq;
  } else {
    return (1.0 - allele_freq);
  }
}

static inline char convert_to_1234(char cc) {
  if (cc == 'A') {
    return '1';
  } else if (cc == 'C') {
    return '2';
  } else if (cc == 'G') {
    return '3';
  } else if (cc == 'T') {
    return '4';
  }
  return cc;
}

extern const char acgtarr[];

static inline char convert_to_acgt(char cc) {
  if ((cc > '0') && (cc <= '4')) {
    return acgtarr[cc - '1'];
  }
  return cc;
}

static inline int32_t filename_exists(char* fname, char* fname_end, const char* fname_append) {
#if _WIN32
  DWORD file_attr;
  strcpy(fname_end, fname_append);
  file_attr = GetFileAttributes(fname);
  return (file_attr != 0xffffffffU);
#else
  struct stat st;
  strcpy(fname_end, fname_append);
  return (stat(fname, &st) == 0);
#endif
}

void indiv_delim_convert(uintptr_t unfiltered_indiv_ct, uintptr_t* indiv_exclude, uintptr_t indiv_ct, char* person_ids, uintptr_t max_person_id_len, char oldc, char newc);

// maximum accepted chromosome index is this minus 1.
// currently unsafe to set this above 60 due to using a single uint64_t
// chrom_mask, and reserving the top 4 bits
#define MAX_POSSIBLE_CHROM 42
#define CHROM_X MAX_POSSIBLE_CHROM
#define CHROM_Y (MAX_POSSIBLE_CHROM + 1)
#define CHROM_XY (MAX_POSSIBLE_CHROM + 2)
#define CHROM_MT (MAX_POSSIBLE_CHROM + 3)

typedef struct {
  // no point to dynamic allocation when MAX_POSSIBLE_CHROM is small

  // order of chromosomes in input files
  // currently tolerates out-of-order chromosomes, as long as all markers for
  // any given chromosome are together
  uint32_t chrom_file_order[MAX_POSSIBLE_CHROM];
  uint32_t chrom_ct; // length of chrom_file_order
  uint32_t chrom_file_order_marker_idx[MAX_POSSIBLE_CHROM + 1];

  // markers chrom_start[k] to (chrom_end[k] - 1) are part of chromosome k
  uint32_t chrom_start[MAX_POSSIBLE_CHROM];
  uint32_t chrom_end[MAX_POSSIBLE_CHROM];

  uint32_t species;
  uint64_t chrom_mask;
} Chrom_info;

#define SPECIES_HUMAN 0
#define SPECIES_COW 1
#define SPECIES_DOG 2
#define SPECIES_HORSE 3
#define SPECIES_MOUSE 4
#define SPECIES_RICE 5
#define SPECIES_SHEEP 6

// extern const uint64_t species_def_chrom_mask[];
extern const uint64_t species_autosome_mask[];
extern const uint64_t species_valid_chrom_mask[];
extern const uint64_t species_haploid_mask[];
// extern const char species_regchrom_ct_p1[];
extern const char species_x_code[];
extern const char species_y_code[];
extern const char species_xy_code[];
extern const char species_mt_code[];
extern const char species_max_code[];
extern const uint64_t species_haploid_mask[];
extern char species_singulars[][7];
extern char species_plurals[][8];

extern char* species_singular;
extern char* species_plural;

static inline char* species_str(uintptr_t ct) {
  return (ct == ONELU)? species_singular : species_plural;
}

int32_t marker_code_raw(char* sptr);

int32_t marker_code(uint32_t species, char* sptr);

int32_t marker_code2(uint32_t species, char* sptr, uint32_t slen);

uint32_t get_marker_chrom(Chrom_info* chrom_info_ptr, uintptr_t marker_uidx);

static inline int32_t chrom_exists(Chrom_info* chrom_info_ptr, uint32_t chrom_idx) {
  return (chrom_info_ptr->chrom_mask & (1LLU << chrom_idx));
}

static inline uintptr_t next_autosomal_unsafe(uintptr_t* marker_exclude, uintptr_t marker_uidx, Chrom_info* chrom_info_ptr, uint32_t* chrom_end_ptr, uint32_t* chrom_fo_idx_ptr) {
  marker_uidx = next_non_set_unsafe(marker_exclude, marker_uidx);
  if (marker_uidx >= (*chrom_end_ptr)) {
    while (1) {
      do {
	*chrom_fo_idx_ptr += 1;
	*chrom_end_ptr = chrom_info_ptr->chrom_file_order_marker_idx[(*chrom_fo_idx_ptr) + 1];
      } while (marker_uidx >= (*chrom_end_ptr));
      if (!((species_haploid_mask[chrom_info_ptr->species] >> chrom_info_ptr->chrom_file_order[*chrom_fo_idx_ptr]) & 1LLU)) {
	return marker_uidx;
      }
      marker_uidx = next_non_set_unsafe(marker_exclude, *chrom_end_ptr);
    }
  }
  return marker_uidx;
}

void refresh_chrom_info(Chrom_info* chrom_info_ptr, uintptr_t marker_uidx, uint32_t allow_x_haploid, uint32_t is_all_nonmale, uint32_t* chrom_end_ptr, uint32_t* chrom_fo_idx_ptr, uint32_t* is_x_ptr, uint32_t* is_haploid_ptr);

int32_t strcmp_casted(const void* s1, const void* s2);

int32_t strcmp_natural(const void* s1, const void* s2);

int32_t strcmp_deref(const void* s1, const void* s2);

int32_t strcmp_natural_deref(const void* s1, const void* s2);

char* scan_for_duplicate_ids(char* sorted_ids, uintptr_t id_ct, uintptr_t max_id_len);

int32_t sort_item_ids_noalloc(char* sorted_ids, uint32_t* id_map, uintptr_t unfiltered_ct, uintptr_t* exclude_arr, uintptr_t item_ct, char* item_ids, uintptr_t max_id_len, uint32_t allow_dups, int(* comparator_deref)(const void*, const void*));

int32_t is_missing_pheno(char* bufptr, int32_t missing_pheno, uint32_t missing_pheno_len, uint32_t affection_01);

int32_t eval_affection(char* bufptr, int32_t missing_pheno, uint32_t missing_pheno_len, uint32_t affection_01);

uint32_t triangle_divide(int64_t cur_prod, int32_t modif);

void triangle_fill(uint32_t* target_arr, uint32_t ct, uint32_t pieces, uint32_t parallel_idx, uint32_t parallel_tot, uint32_t start, uint32_t align);

int32_t write_ids(char* outname, uintptr_t unfiltered_indiv_ct, uintptr_t* indiv_exclude, char* person_ids, uintptr_t max_person_id_len);

int32_t distance_d_write_ids(char* outname, char* outname_end, uint32_t dist_calc_type, uintptr_t unfiltered_indiv_ct, uintptr_t* indiv_exclude, char* person_ids, uintptr_t max_person_id_len);

int32_t relationship_req(uint64_t calculation_type);

int32_t distance_req(uint64_t calculation_type, char* readdistname);

int32_t double_cmp(const void* aa, const void* bb);

int32_t double_cmp_deref(const void* aa, const void* bb);

int32_t char_cmp_deref(const void* aa, const void* bb);

#ifndef __cplusplus
int32_t intcmp(const void* aa, const void* bb);

int32_t llcmp(const void* aa, const void* bb);
#endif

void qsort_ext2(char* main_arr, intptr_t arr_length, intptr_t item_length, int(* comparator_deref)(const void*, const void*), char* secondary_arr, intptr_t secondary_item_len, char* proxy_arr, intptr_t proxy_len);

int32_t qsort_ext(char* main_arr, intptr_t arr_length, intptr_t item_length, int(* comparator_deref)(const void*, const void*), char* secondary_arr, intptr_t secondary_item_len);

uintptr_t uint64arr_greater_than(uint64_t* sorted_uint64_arr, uintptr_t arr_length, uint64_t ullii);

uintptr_t doublearr_greater_than(double* sorted_dbl_arr, uintptr_t arr_length, double dxx);

uintptr_t bsearch_str_lb(char* lptr, uintptr_t arr_length, uintptr_t max_id_len, char* id_buf);

int32_t bsearch_str(char* id_buf, char* lptr, uintptr_t max_id_len, intptr_t min_idx, intptr_t max_idx);

int32_t bsearch_str_natural(char* id_buf, char* lptr, uintptr_t max_id_len, intptr_t min_idx, intptr_t max_idx);

void fill_idbuf_fam_indiv(char* id_buf, char* fam_indiv, char fillchar);

int32_t bsearch_fam_indiv(char* id_buf, char* lptr, uintptr_t max_id_len, uint32_t filter_line_ct, char* fam_id, char* indiv_id);

void bsearch_fam(char* id_buf, char* lptr, uintptr_t max_id_len, uint32_t filter_line_ct, char* fam_id, uint32_t* first_idx_ptr, uint32_t* last_idx_ptr);

void bitfield_and(uintptr_t* vv, uintptr_t* include_vec, uintptr_t word_ct);

void bitfield_andnot(uintptr_t* vv, uintptr_t* exclude_vec, uintptr_t word_ct);

void bitfield_andnot_reversed_args(uintptr_t* vv, uintptr_t* include_vec, uintptr_t word_ct);

void bitfield_ornot(uintptr_t* vv, uintptr_t* inverted_or_vec, uintptr_t word_ct);

static inline uint32_t popcount2_long(uintptr_t val) {
#ifdef __LP64__
  val = (val & 0x3333333333333333LLU) + ((val >> 2) & 0x3333333333333333LLU);
  return (((val + (val >> 4)) & 0x0f0f0f0f0f0f0f0fLLU) * 0x0101010101010101LLU) >> 56;
#else
  val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
  return (((val + (val >> 4)) & 0x0f0f0f0f) * 0x01010101) >> 24;
#endif
}

static inline uint32_t popcount_long(uintptr_t val) {
  // the simple version, good enough for all non-time-critical stuff
  return popcount2_long(val - ((val >> 1) & FIVEMASK));
}

uintptr_t popcount_longs(uintptr_t* lptr, uintptr_t start_idx, uintptr_t end_idx);

uintptr_t popcount_chars(uintptr_t* lptr, uintptr_t start_idx, uintptr_t end_idx);

uintptr_t popcount_longs_exclude(uintptr_t* lptr, uintptr_t* exclude_arr, uintptr_t end_idx);

#ifdef __LP64__
void count_2freq_dbl_60v(__m128i* vptr, __m128i* vend, __m128i* mask1vp, __m128i* mask2vp, uint32_t* ct1abp, uint32_t* ct1cp, uint32_t* ct2abp, uint32_t* ct2cp);

void count_3freq_120v(__m128i* vptr, __m128i* vend, __m128i* maskvp, uint32_t* ctap, uint32_t* ctbp, uint32_t* ctcp);
#else
void count_2freq_dbl_6(uintptr_t* lptr, uintptr_t* mask1p, uintptr_t* mask2p, uint32_t* ct1abp, uint32_t* ct1cp, uint32_t* ct2abp, uint32_t* ct2cp);

void count_3freq_12(uintptr_t* lptr, uintptr_t* maskp, uint32_t* ctap, uint32_t* ctbp, uint32_t* ctcp);
#endif

void vec_set_freq(uintptr_t indiv_ctl2, uintptr_t* lptr, uintptr_t* include_vec, uint32_t* set_ctp, uint32_t* missing_ctp);

void vec_set_freq_x(uintptr_t indiv_ctl2, uintptr_t* lptr, uintptr_t* include_vec, uintptr_t* male_vec, uint32_t* set_ctp, uint32_t* missing_ctp);

void vec_set_freq_y(uintptr_t indiv_ctl2, uintptr_t* lptr, uintptr_t* include_vec, uintptr_t* nonmale_vec, uint32_t* set_ctp, uint32_t* missing_ctp);

void vec_3freq(uintptr_t indiv_ctl2, uintptr_t* lptr, uintptr_t* include_vec, uint32_t* missing_ctp, uint32_t* het_ctp, uint32_t* homa2_ctp);

static inline void zero_trailing_bits(uintptr_t* bitfield, uintptr_t unfiltered_ct) {
  uintptr_t trail_ct = unfiltered_ct & (BITCT - 1);
  if (trail_ct) {
    bitfield[unfiltered_ct / BITCT] &= (ONELU << trail_ct) - ONELU;
  }
}

uint32_t count_chrom_markers(Chrom_info* chrom_info_ptr, uint32_t chrom_idx, uintptr_t* marker_exclude);

uint32_t count_non_autosomal_markers(Chrom_info* chrom_info_ptr, uintptr_t* marker_exclude, uint32_t count_x);

void count_genders(uintptr_t* sex_nm, uintptr_t* sex_male, uintptr_t unfiltered_indiv_ct, uintptr_t* indiv_exclude, uint32_t* male_ct_ptr, uint32_t* female_ct_ptr, uint32_t* unk_ct_ptr);

uint32_t block_load_autosomal(FILE* bedfile, int32_t bed_offset, uintptr_t* marker_exclude, uint32_t marker_ct_autosomal, uint32_t block_max_size, uintptr_t unfiltered_indiv_ct4, Chrom_info* chrom_info_ptr, double* set_allele_freqs, uint32_t* marker_weights, unsigned char* readbuf, uint32_t* chrom_fo_idx_ptr, uintptr_t* marker_uidx_ptr, uintptr_t* marker_idx_ptr, uint32_t* block_size_ptr, double* set_allele_freq_buf, float* set_allele_freq_buf_fl, uint32_t* wtbuf);

void exclude_to_vec_include(uintptr_t unfiltered_indiv_ct, uintptr_t* include_arr, uintptr_t* exclude_arr);

void vec_init_invert(uintptr_t vec_entry_ct, uintptr_t* target_arr, uintptr_t* source_arr);

void vec_init_andnot(uintptr_t vec_entry_ct, uintptr_t* target_arr, uintptr_t* source_arr, uintptr_t* exclude_arr);

void vec_include_mask_in(uintptr_t unfiltered_indiv_ct, uintptr_t* include_arr, uintptr_t* mask_arr);

void vec_include_mask_out(uintptr_t unfiltered_indiv_ct, uintptr_t* include_arr, uintptr_t* mask_arr);

void vec_include_mask_out_intersect(uintptr_t unfiltered_indiv_ct, uintptr_t* include_arr, uintptr_t* mask_arr, uintptr_t* mask2_arr);

void hh_reset(unsigned char* loadbuf, uintptr_t* indiv_include2, uintptr_t unfiltered_indiv_ct);

void hh_reset_y(unsigned char* loadbuf, uintptr_t* indiv_include2, uintptr_t* indiv_male_include2, uintptr_t unfiltered_indiv_ct);

void reverse_loadbuf(unsigned char* loadbuf, uintptr_t unfiltered_indiv_ct);

void force_missing(unsigned char* loadbuf, uintptr_t* force_missing_include2, uintptr_t unfiltered_indiv_ct);

static inline char sexchar(uintptr_t* sex_nm, uintptr_t* sex_male, uintptr_t indiv_uidx) {
  return is_set(sex_nm, indiv_uidx)? (is_set(sex_male, indiv_uidx)? '1' : '2') : '0';
}

int32_t open_and_size_string_list(char* fname, FILE** infile_ptr, uintptr_t* list_len_ptr, uintptr_t* max_str_len_ptr);


int32_t load_string_list(FILE** infile_ptr, uintptr_t max_str_len, char* str_list);

int32_t open_and_skip_first_lines(FILE** infile_ptr, char* fname, char* loadbuf, uintptr_t loadbuf_size, uint32_t lines_to_skip);

int32_t scan_max_strlen(char* fname, uint32_t colnum, uint32_t colnum2, uint32_t headerskip, char skipchar, uintptr_t* max_str_len_ptr, uintptr_t* max_str2_len_ptr);

int32_t scan_max_fam_indiv_strlen(char* fname, uint32_t colnum, uintptr_t* max_person_id_len_ptr);

int32_t distance_d_write(FILE** outfile_ptr, FILE** outfile2_ptr, FILE** outfile3_ptr, int32_t dist_calc_type, char* outname, char* outname_end, double* dists, double half_marker_ct_recip, uint32_t indiv_ct, int32_t first_indiv_idx, int32_t end_indiv_idx, int32_t parallel_idx, int32_t parallel_tot, unsigned char* membuf);

void collapse_arr(char* item_arr, int32_t fixed_item_len, uintptr_t* exclude_arr, int32_t exclude_arr_size);

void collapse_copy_bitarr(uint32_t orig_ct, uintptr_t* bitarr, uintptr_t* exclude_arr, uint32_t filtered_ct, uintptr_t* output_arr);

void collapse_copy_bitarr_incl(uint32_t orig_ct, uintptr_t* bitarr, uintptr_t* include_arr, uint32_t filtered_ct, uintptr_t* output_arr);

void collapse_copy_bitarr_to_vec_incl(uint32_t orig_ct, uintptr_t* bitarr, uintptr_t* include_arr, uint32_t filtered_ct, uintptr_t* output_vec);

uint32_t collapse_duplicate_ids(char* sorted_ids, uintptr_t id_ct, uintptr_t max_id_len, uint32_t* id_starts);

static inline double rand_unif(void) {
  return (sfmt_genrand_uint32(&sfmt) + 0.5) * RECIP_2_32;
}

double normdist(double zz);

double rand_normal(double* secondval_ptr);

// void pick_d(unsigned char* cbuf, uint32_t ct, uint32_t dd);

void pick_d_small(unsigned char* tmp_cbuf, uint32_t* uibuf, uint32_t ct, uint32_t dd);

void init_sfmt64_from_sfmt32(sfmt_t* sfmt32, sfmt_t* sfmt64);

void print_pheno_stdev(double* pheno_d, uint32_t indiv_ct);

uint32_t set_default_jackknife_d(uint32_t ct);

void generate_perm1_interleaved(uint32_t tot_ct, uint32_t set_ct, uintptr_t perm_idx, uintptr_t perm_ct, uintptr_t* perm_buf);

void join_threads(pthread_t* threads, uint32_t ctp1);

#if _WIN32
int32_t spawn_threads(pthread_t* threads, unsigned (__stdcall *start_routine)(void*), uintptr_t ct);
#else
int32_t spawn_threads(pthread_t* threads, void* (*start_routine)(void*), uintptr_t ct);
#endif

int32_t regress_distance(uint64_t calculation_type, double* dists_local, double* pheno_d_local, uintptr_t unfiltered_indiv_ct, uintptr_t* indiv_exclude, uint32_t thread_ct, uintptr_t regress_iters, uint32_t regress_d);

typedef struct {
  char* family_ids;
  uintptr_t max_family_id_len; // includes trailing null
  uint32_t* family_sizes;

  uint32_t* family_rel_space_offsets; // offset for rel_space lookup
  uint32_t* family_founder_cts;
  // direct indiv idx -> family idx lookup, to reduce number of bsearches
  uint32_t* family_idxs;

  // truncated triangular arrays of pedigree coefficient of relationship
  double* rel_space;

  // direct indiv idx -> rel_space idx lookup
  uint32_t* family_rel_nf_idxs;

  // following three variables are technically unnecessary for --genome, but we
  // get them for "free" in the process of calculating everything else, and
  // they'll be nice to use if we ever need to iterate by family in the future.
  uint32_t family_id_ct;
  // list of idxs of all individuals in first family, then second family, etc.
  uint32_t* family_info_space;
  uint32_t* family_info_offsets; // offset in family_info_space
} Pedigree_rel_info;

#endif // __WDIST_COMMON_H__
