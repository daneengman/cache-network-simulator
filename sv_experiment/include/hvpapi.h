/****************************************************************************
 * SYNOPSYS CONFIDENTIAL - This is an unpublished, proprietary work of
 * Synopsys, Inc., and is fully protected under copyright and trade
 * secret laws. You may not view, use, disclose, copy, or distribute this
 * file or any information contained herein except pursuant to a valid
 * written license from Synopsys.
 ****************************************************************************/

#ifndef _HVPAPI_H
#define _HVPAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "covdb_user.h"
#include "hvpapi_def.h"

unsigned hvp_check_license();

/* load hvp with space sperated hvp filenames */
hvpHandle hvp_load_plan(const char* hvpfile, unsigned option);

hvpStatusT hvp_load_spec(hvpHandle planHdl, unsigned option);

void hvp_unload(hvpHandle hdl);

hvpHandle hvp_apply(hvpHandle planHdl, const char *hvpfile,
                    unsigned option);

/**
 * HVP load vedata function
 * @param plan : HVP plan handle
 * @param dataFileName : filepath, multiple files deliminated by space can be given
 */

hvpStatusT hvp_load_data(hvpHandle planHdl, const char *dataFileName);

/**
 * HVP annotation function
 * Walks an HVP and repeatedly calls hvp_add_ratio_source to annotate HVP
 * with UCAPI coverage data
 *
 * @param plan - the HVP handle
 * @param cmdir - covdb path, multiple paths delimitated by space can be given
 */
hvpStatusT hvp_load_covdb(hvpHandle plan, const char* cmdir);

/**
 * HVP annotation function
 * find the LP plan definition in covdbdir/lp_coverage_metric.hvp
 * replace the dummy LP subplan in plan 
 *
 * @param plan - the HVP handle
 * @param designH - covdb design handle
 */
unsigned hvp_resolve_lpplan(hvpHandle plan, covdbHandle designH);

/**
 * HVP annotation function
 * Walks an HVP and repeatedly calls hvp_add_ratio_source to annotate HVP
 * with UCAPI coverage data
 *
 * @param plan - the HVP handle
 * @param designH - covdb design handle
 * @param testH - covdb test handle
 */
hvpStatusT hvp_load_covdb_handle(hvpHandle plan,
                                 covdbHandle designH,
                                 covdbHandle testH);

/**
 * hier filters are used when given covdb or ve.data are annotated
 * only in part of HVP hierarchy
 */
void hvp_add_hier_filter(hvpHandle plan, const char *filter);

void hvp_clear_hier_filter(hvpHandle plan);

/**
 * HVP editor function
 * Loading vedata files in accumulative way
 * return hvpVE handle
 */
hvpHandle hvp_load_ve(hvpHandle veHdl, const char *vefile, int opt);

hvpHandle hvp_propagate_scores(hvpHandle plan);

hvpStatusT hvp_get_error(const char **message);

hvpHandle hvp_get_handle(hvpHandle hdl, hvp1To1RelationT rel);

int hvp_get(hvpHandle hdl, hvpIntPropertyT prop);

char *hvp_get_str(hvpHandle hdl, hvpStrPropertyT prop,
                  char *buffer, int buflen);

double hvp_get_real(hvpHandle hdl, hvpRealPropertyT prop);

hvpHandle hvp_iterate(hvpHandle hdl, hvp1ToManyRelationT relation);

hvpHandle hvp_scan(hvpHandle iterHdl);

void hvp_release_handle(hvpHandle hdl);

void hvp_configure(hvpConfigItemT item, const char *value);

const char *hvp_get_error_name(hvpStatusT err);

void hvp_set_error_callback(hvpErrorCB fn);

/* DVE HVP editor & viewer functions */
hvpHandle hvp_add_container(hvpHandle parentHdl,
                            hvpTypeT containerType,
                            const char* name,
                            hvpHandle posHdl);

hvpStatusT hvp_rename_container(hvpHandle parentH,
                                hvpHandle objH, const char* name);

hvpStatusT hvp_move_container(hvpHandle parentH,
                              hvpHandle objH, hvpHandle posHdl);

hvpStatusT hvp_set_specsect_property(hvpHandle sectHdl,
                                     const char* secNum,
                                     const char* secTitle,
                                     int offset,
                                     int length,
                                     const char* bound_startx,
                                     const char* bound_starty,
                                     const char* bound_endx,
                                     const char* bound_endy,
                                     const char* checksum);
    
hvpStatusT hvp_set_metric_property(hvpHandle metricHdl,
                                   hvpTypeT scoreType,
                                   hvpAggRuleT aggRule,
                                   const char *goal);

hvpStatusT hvp_set_attribute_property(hvpHandle attrHdl,
                                      hvpTypeT valueType,
                                      const char* value);

hvpStatusT hvp_set_int_property(hvpHandle hdl,
                                hvpIntPropertyT prop, int val);

hvpStatusT hvp_set_str_property(hvpHandle hdl,
                                hvpStrPropertyT prop, const char* val);

hvpStatusT hvp_verify_expr(const char* strexpr);

hvpStatusT hvp_add_submetric(hvpHandle parentHdl, hvpHandle metricHdl);

hvpStatusT hvp_delete_container(hvpHandle parentHdl, hvpHandle objHdl);

hvpStatusT hvp_delete_submetric(hvpHandle parentHdl, hvpHandle metricHdl);

hvpStatusT hvp_clear_container(hvpHandle parentHdl, hvpTypeT containerType);

hvpStatusT hvp_dump(hvpHandle topPlanHdl, const char* filename);

hvpStatusT hvp_dump_modifier(hvpHandle topPlanHdl, const char* filename);

hvpStatusT hvp_propagate_atts(hvpHandle hdl, hvpHandle prthdl, const char *attName);

hvpStatusT hvp_clear_all(hvpHandle hdl);

hvpStatusT hvp_resolve_subplans(hvpHandle hdl);

hvpHandle hvp_find(hvpHandle hdl, const char* name, hvp1ToManyRelationT relation);

unsigned hvp_goal_value_nature(hvpHandle hdl, hvpHandle scope);

hvpHandle hvp_load_include_file(hvpHandle hdl, const char* name);

/* hvp genxls functions */
hvpStatusT hvp_set_report_config(hvpHandle hdl, hvpReportConfigT item, const char *value);

char *hvp_get_report_config(hvpHandle hdl, hvpReportConfigT item,
                            char *buffer, int buflen);

hvpStatusT hvp_gen_excel_xml_plan(hvpHandle planHdl, const char *xmlFileName);

hvpStatusT hvp_gen_excel_xml_ann_report(hvpHandle planHdl, const char *annFileName);

hvpStatusT hvp_gen_xml_ss_report(hvpHandle planHdl, const char *annFileName);

hvpStatusT hvp_gen_xml_doc_report(hvpHandle planHdl, const char *annFileName);

hvpStatusT hvp_gen_xml_plan(hvpHandle planHdl, const char *annFileName);

int hvp_gen_str_hash(const char* str);

unsigned hvp_xmrcmp(const char* ptrn, const char* str, unsigned icase, unsigned iscope);

/* util functions */
unsigned hvp_is_expected_metric(const char* metName, hvpHandle scope);

hvpHandle hvp_search(covdbHandle designH, covdbHandle testH, const char * source);

/* hvp diff function */
const char* hvp_diff_plans(hvpHandle plan1, hvpHandle plan2);

/* verdi issue tracking issues */
hvpStatusT hvp_bug_init(hvpHandle planHdl);
hvpStatusT hvp_bug_link(hvpHandle planHdl, const char* feat_id, const char* issue, const char* status);
hvpStatusT hvp_clear_bug(hvpHandle planHdl);
hvpStatusT hvp_load_bug(hvpHandle planHdl);

#ifdef __cplusplus
}
#endif

#endif /* _HVPAPI_H */

