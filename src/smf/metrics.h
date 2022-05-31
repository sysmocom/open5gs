#ifndef SMF_METRICS_H
#define SMF_METRICS_H

#include "ogs-metrics.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum smf_metric_type_global_s {
    SMF_METR_GLOB_CTR_RX_CREATEPDPCTXREQ = 0,
    SMF_METR_GLOB_GAUGE_PDPCTX_ACTIVE,
    _SMF_METR_GLOB_MAX,
} smf_metric_type_global_t;
extern ogs_metrics_inst_t *smf_metrics_inst_global[_SMF_METR_GLOB_MAX];

static inline void smf_metrics_inst_global_set(smf_metric_type_global_t t, int val)
{
    ogs_metrics_inst_set(smf_metrics_inst_global[t], val);
}
static inline void smf_metrics_inst_global_add(smf_metric_type_global_t t, int val)
{
    ogs_metrics_inst_add(smf_metrics_inst_global[t], val);
}
static inline void smf_metrics_inst_global_inc(smf_metric_type_global_t t)
{
    ogs_metrics_inst_inc(smf_metrics_inst_global[t]);
}
static inline void smf_metrics_inst_global_dec(smf_metric_type_global_t t)
{
    ogs_metrics_inst_dec(smf_metrics_inst_global[t]);
}

int smf_metrics_open(void);
int smf_metrics_close(void);

#ifdef __cplusplus
}
#endif

#endif /* SMF_METRICS_H */
