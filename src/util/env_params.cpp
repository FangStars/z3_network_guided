/*++
Copyright (c) 2011 Microsoft Corporation

Module Name:

    env_params.cpp

Abstract:

    Goodies for updating environment parameters.

Author:

    Leonardo (leonardo) 2012-12-01

Notes:

--*/
#include "util/env_params.h"
#include "util/params.h"
#include "util/gparams.h"
#include "util/util.h"
#include "util/memory_manager.h"

void env_params::updt_params() {
    params_ref const& p = gparams::get_ref();
    set_verbosity_level(p.get_uint("verbose", get_verbosity_level()));
    enable_warning_messages(p.get_bool("warning", true));
    memory::set_max_size(megabytes_to_bytes(p.get_uint("memory_max_size", 0)));
    memory::set_max_alloc_count(p.get_uint("memory_max_alloc_count", 0));
    memory::set_high_watermark(p.get_uint("memory_high_watermark", 0));
    unsigned mb = p.get_uint("memory_high_watermark_mb", 0);
    if (mb > 0)
        memory::set_high_watermark(megabytes_to_bytes(mb));    
}

void env_params::collect_param_descrs(param_descrs & d) {
    d.insert("verbose", CPK_UINT, "be verbose, where the value is the verbosity level", "0");
    d.insert("warning", CPK_BOOL, "enable/disable warning messages", "true");
    d.insert("memory_max_size", CPK_UINT, "set hard upper limit for memory consumption (in megabytes), if 0 then there is no limit", "0");
    d.insert("memory_max_alloc_count", CPK_UINT, "set hard upper limit for memory allocations, if 0 then there is no limit", "0");
    d.insert("memory_high_watermark", CPK_UINT, "set high watermark for memory consumption (in bytes), if 0 then there is no limit", "0");
    d.insert("memory_high_watermark_mb", CPK_UINT, "set high watermark for memory consumption (in megabytes), if 0 then there is no limit", "0");
    // ADD_BEGIN
    d.insert("topology", CPK_STRING, "set directory of topology", "");  // register global param
    d.insert("guided", CPK_BOOL, "set if guided", "false"); 
    d.insert("dst", CPK_STRING, "prefix origination", "");  
    d.insert("dst_port", CPK_STRING, "prefix origination port", "");
    d.insert("prop_type", CPK_STRING, "property type", "0"); // 0: reachability; 1:isolation; 2:forwarding
    d.insert("network_type", CPK_STRING, "network type", "0"); // 0: internet; 1:fattree
    d.insert("flag_allpair", CPK_STRING, "flag_allpair", "0"); // 0: not all-pair; 1:all-pair
    
    d.insert("ip_file", CPK_STRING, "set directory of ip file", "");  // register global param
    d.insert("dstnode_file", CPK_STRING, "set directory of dstNode file", "");
    d.insert("pdstnode_file", CPK_STRING, "set directory of prior dstNode file", "");

    // ADD_END
}
