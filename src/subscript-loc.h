#ifndef VCTRS_SUBSCRIPT_LOC_H
#define VCTRS_SUBSCRIPT_LOC_H

#include "utils.h"
#include "subscript.h"


enum subscript_missing {
  SUBSCRIPT_MISSING_PROPAGATE,
  SUBSCRIPT_MISSING_ERROR
};
enum num_loc_negative {
  LOC_NEGATIVE_INVERT,
  LOC_NEGATIVE_ERROR,
  LOC_NEGATIVE_IGNORE
};
enum num_loc_oob {
  LOC_OOB_EXTEND,
  LOC_OOB_ERROR
};
enum num_loc_zero {
  LOC_ZERO_REMOVE,
  LOC_ZERO_ERROR,
  LOC_ZERO_IGNORE
};

struct location_opts {
  const struct subscript_opts* subscript_opts;
  enum num_loc_negative loc_negative;
  enum num_loc_oob loc_oob;
  enum num_loc_zero loc_zero;
  enum subscript_missing missing;
};

extern struct location_opts location_default_opts_obj;
extern struct location_opts location_default_assign_opts_obj;

static const struct location_opts* const location_default_opts = &location_default_opts_obj;
static const struct location_opts* const location_default_assign_opts = &location_default_assign_opts_obj;


SEXP vec_as_location(SEXP i, R_len_t n, SEXP names);
SEXP vec_as_location_opts(SEXP subscript, R_len_t n, SEXP names,
                          const struct location_opts* location_opts);


#endif
