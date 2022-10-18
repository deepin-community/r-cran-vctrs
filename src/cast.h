#ifndef VCTRS_CAST_H
#define VCTRS_CAST_H

#include "ptype2.h"

struct cast_opts {
  SEXP x;
  SEXP to;
  struct vctrs_arg* x_arg;
  struct vctrs_arg* to_arg;
  struct fallback_opts fallback;
};

SEXP df_cast_opts(const struct cast_opts* opts);

// Defined in type-data-frame.c
static inline
SEXP df_cast(SEXP x, SEXP to, struct vctrs_arg* x_arg, struct vctrs_arg* to_arg) {
  const struct cast_opts opts = {
    .x = x,
    .to = to,
    .x_arg = x_arg,
    .to_arg = to_arg
  };
  return df_cast_opts(&opts);
}

SEXP vec_cast_opts(const struct cast_opts* opts);

static inline
SEXP vec_cast_params(SEXP x,
                     SEXP to,
                     struct vctrs_arg* x_arg,
                     struct vctrs_arg* to_arg,
                     enum df_fallback df_fallback,
                     enum s3_fallback s3_fallback) {
  const struct cast_opts opts = {
    .x = x,
    .to = to,
    .x_arg = x_arg,
    .to_arg = to_arg,
    .fallback = {
      .df = df_fallback,
      .s3 = s3_fallback
    }
  };
  return vec_cast_opts(&opts);
}

SEXP vec_cast_common_opts(SEXP xs,
                          SEXP to,
                          const struct fallback_opts* fallback_opts);
SEXP vec_cast_common_params(SEXP xs,
                            SEXP to,
                            enum df_fallback df_fallback,
                            enum s3_fallback s3_fallback);

struct cast_opts new_cast_opts(SEXP x,
                               SEXP y,
                               struct vctrs_arg* x_arg,
                               struct vctrs_arg* y_arg,
                               SEXP opts);

SEXP vec_cast_dispatch_native(const struct cast_opts* opts,
                              enum vctrs_type x_type,
                              enum vctrs_type to_type,
                              bool* lossy);

SEXP vec_cast_e(const struct cast_opts* opts,
                ERR* err);

SEXP vec_cast_default(SEXP x,
                      SEXP y,
                      SEXP x_arg,
                      SEXP to_arg,
                      const struct fallback_opts* opts);

// Defined in cast-bare.c
SEXP int_as_double(SEXP x, bool* lossy);
SEXP lgl_as_double(SEXP x, bool* lossy);
SEXP dbl_as_integer(SEXP x, bool* lossy);
SEXP lgl_as_integer(SEXP x, bool* lossy);
SEXP chr_as_logical(SEXP x, bool* lossy);
SEXP dbl_as_logical(SEXP x, bool* lossy);
SEXP int_as_logical(SEXP x, bool* lossy);


#endif
