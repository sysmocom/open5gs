#include "ogs-app.h"
#include "hss-context.h"

#include "metrics.h"

typedef struct hss_metrics_spec_def_s {
    unsigned int type;
    const char *name;
    const char *description;
    int initial_val;
    unsigned int num_labels;
    const char **labels;
} hss_metrics_spec_def_t;

/* Helper generic functions: */
static int hss_metrics_init_inst(ogs_metrics_inst_t **inst, ogs_metrics_spec_t **specs,
        unsigned int len, unsigned int num_labels, const char **labels)
{
    unsigned int i;
    for (i = 0; i < len; i++)
        inst[i] = ogs_metrics_inst_new(specs[i], num_labels, labels);
    return OGS_OK;
}

static int hss_metrics_free_inst(ogs_metrics_inst_t **inst,
        unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++)
        ogs_metrics_inst_free(inst[i]);
    memset(inst, 0, sizeof(inst[0]) * len);
    return OGS_OK;
}

static int hss_metrics_init_spec(ogs_metrics_context_t *ctx,
        ogs_metrics_spec_t **dst, hss_metrics_spec_def_t *src, unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++) {
        dst[i] = ogs_metrics_spec_new(ctx, src[i].type,
                src[i].name, src[i].description,
                src[i].initial_val, src[i].num_labels, src[i].labels,
                NULL);
    }
    return OGS_OK;
}

/* GLOBAL */
ogs_metrics_spec_t *hss_metrics_spec_global[_HSS_METR_GLOB_MAX];
ogs_metrics_inst_t *hss_metrics_inst_global[_HSS_METR_GLOB_MAX];
hss_metrics_spec_def_t hss_metrics_spec_def_global[_HSS_METR_GLOB_MAX] = {
/* Global Gauges: */
[HSS_METR_GLOB_GAUGE_IMSI] = {
    .type = OGS_METRICS_METRIC_TYPE_GAUGE,
    .name = "hss_imsi",
    .description = "Number of IMSIs attached to HSS",
},
[HSS_METR_GLOB_GAUGE_IMPI] = {
    .type = OGS_METRICS_METRIC_TYPE_GAUGE,
    .name = "hss_impi",
    .description = "Number of IMPIs attached to HSS",
},
[HSS_METR_GLOB_GAUGE_IMPU] = {
    .type = OGS_METRICS_METRIC_TYPE_GAUGE,
    .name = "hss_impu",
    .description = "Number of IMPUs attached to HSS",
},
};
int hss_metrics_init_inst_global(void)
{
    return hss_metrics_init_inst(hss_metrics_inst_global, hss_metrics_spec_global,
                _HSS_METR_GLOB_MAX, 0, NULL);
}
int hss_metrics_free_inst_global(void)
{
    return hss_metrics_free_inst(hss_metrics_inst_global, _HSS_METR_GLOB_MAX);
}

void hss_metrics_init(void)
{
    ogs_metrics_context_t *ctx = ogs_metrics_self();
    ogs_metrics_context_init();

    hss_metrics_init_spec(ctx, hss_metrics_spec_global, hss_metrics_spec_def_global,
            _HSS_METR_GLOB_MAX);

    hss_metrics_init_inst_global();
}

void hss_metrics_final(void)
{
    ogs_metrics_context_final();
}
