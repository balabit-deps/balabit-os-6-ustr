#include "tst.h"

static const char *rf = __FILE__;

int tst(void)
{
  Ustr_pool *pool = ustr_pool_ll_make();
  Ustr *tmp = ustr_sc_concat(USTR(""), USTR(""), USTR(""), USTR_NULL);
  Ustrp *ptmp = ustrp_sc_concat(pool, USTRP(""),USTRP(""),USTRP(""),USTRP_NULL);
  
  ASSERT(tmp);
  ASSERT(!ustr_len(tmp));
  ASSERT( ustr_ro(tmp));

  ASSERT(ptmp);
  ASSERT(!ustrp_len(ptmp));
  ASSERT( ustrp_ro(ptmp));

  ASSERT((ptmp = ustrp_sc_concatx(pool, 1,1,1,1, USTRP(""),
                                  USTRP(""), USTRP(""), USTRP_NULL)));
  ASSERT(!ustrp_len(ptmp));
  ASSERT(!ustrp_ro(ptmp));

  tmp = ustr_sc_concat(USTR1(\4, "abcd"),USTR1(\4, "/xyz"),USTR(""), USTR_NULL);
  ASSERT(tmp);
  ASSERT_EQ(tmp, USTR1(\x8, "abcd/xyz"));
  ustr_free(tmp);
  tmp = ustr_sc_concat(USTR1(\4, "abcd"), USTR1(\4, "/xyz"), USTR(""),
                       USTR1(\4, " ---"), USTR(""),USTR1(\4, "- 12"),USTR_NULL);
  ASSERT(tmp);
  ASSERT_EQ(tmp, USTR1(\x10, "abcd/xyz ---- 12"));
  ustr_free(tmp);
  tmp = ustr_sc_concatx(1, 1, 1, 1,
                        USTR1(\4, "abcd"),USTR1(\4, "/xyz"),USTR(""),USTR_NULL);
  ASSERT(tmp);
  ASSERT(ustr_enomem(tmp));
  ASSERT_EQ(tmp, USTR1(\x8, "abcd/xyz"));
  ustr_free(tmp);
  
  ptmp = ustrp_sc_concat(pool, USTRP(""),
                         USTRP1(\4, "abcd"), USTRP1(\4, "/xyz"), USTRP_NULL);
  ASSERT(ptmp);
  ASSERT_PEQ(ptmp, USTRP1(\x8, "abcd/xyz"));
  ptmp = ustrp_sc_concat(pool, USTRP(""),
                         USTRP1(\4, "abcd"), USTRP1(\4, "/xyz"),
                         USTRP1(\4, " ---"), USTRP(""),USTRP1(\4, "- 12"),
                         USTRP_NULL);
  ASSERT_PEQ(ptmp, USTRP1(\x10, "abcd/xyz ---- 12"));
  ptmp = ustrp_sc_concatx(pool, 1, 1, 1, 1, USTRP(""),
                          USTRP1(\4, "abcd"), USTRP1(\4, "/xyz"), USTRP_NULL);
  ASSERT(ptmp);
  ASSERT(ustrp_enomem(ptmp));
  ASSERT_PEQ(ptmp, USTRP1(\x8, "abcd/xyz"));

  ustr_pool_free(pool);
  
  return (EXIT_SUCCESS);
}
