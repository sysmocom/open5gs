#include "ogs-app.h"
#include "context.h"

#include "metrics.h"

typedef struct smf_metrics_spec_def_s {
    unsigned int type;
    const char *name;
    const char *description;
    int initial_val;
    unsigned int num_labels;
    const char **labels;
} smf_metrics_spec_def_t;

ogs_metrics_spec_t *smf_metrics_spec_global[_SMF_METR_GLOB_MAX];
ogs_metrics_inst_t *smf_metrics_inst_global[_SMF_METR_GLOB_MAX];
smf_metrics_spec_def_t smf_metrics_spec_def_global[_SMF_METR_GLOB_MAX] = {
[SMF_METR_GLOB_CTR_RX_CREATEPDPCTXREQ] = {
    .type = OGS_METRICS_METRIC_TYPE_COUNTER,
    .name = "rx_createpdpcontextreq",
    .description = "Received CreatePDPContextRequest messages",
    .initial_val = 0,
    .num_labels = 0,
    .labels = NULL,
    //.num_labels = OGS_ARRAY_SIZE(labels_pdpctx),
    //.labels = labels_pdpctx,
},
[SMF_METR_GLOB_GAUGE_PDPCTX_ACTIVE] = {
    .type = OGS_METRICS_METRIC_TYPE_GAUGE,
    .name = "pdpctx_active",
    .description = "Active PDP Contexts",
    .initial_val = 0,
    .num_labels = 0,
    .labels = NULL,
},
};

const char *labels_pdpctx[] = {
    "apn"
};

static int smf_metrics_init_spec(ogs_metrics_context_t *ctx,
        ogs_metrics_spec_t **dst, smf_metrics_spec_def_t *src, unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++) {
        dst[i] = ogs_metrics_spec_new(ctx, src[i].type,
                src[i].name, src[i].description,
                src[i].initial_val, src[i].num_labels, src[i].labels);
    }
    return OGS_OK;
}


static int smf_metrics_init_inst_global(ogs_metrics_inst_t **inst, ogs_metrics_spec_t **specs, unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++)
        inst[i] = ogs_metrics_inst_new(specs[i], 0, NULL);
    return OGS_OK;
}

int smf_metrics_open(void)
{
    ogs_metrics_context_t *ctx = ogs_metrics_self();
    ogs_metrics_context_open(ctx);

    smf_metrics_init_spec(ctx, smf_metrics_spec_global, smf_metrics_spec_def_global,
            _SMF_METR_GLOB_MAX);

    smf_metrics_init_inst_global(smf_metrics_inst_global, smf_metrics_spec_global,
            _SMF_METR_GLOB_MAX);
    return 0;
}

int smf_metrics_close(void)
{
    ogs_metrics_context_t *ctx = ogs_metrics_self();
    ogs_metrics_context_close(ctx);
    return OGS_OK;
}
