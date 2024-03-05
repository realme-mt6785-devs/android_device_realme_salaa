//
// Copyright (C) 2022-2023 The LineageOS Project
//
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "vendor_init.h"
#include "property_service.h"

#include <fs_mgr_dm_linear.h>

using android::base::ReadFileToString;

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;

    pi = (prop_info *) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void set_ro_build_prop(const std::string& prop, const std::string& value,
                       bool product = true) {
    std::string prop_name;
    std::vector<std::string> prop_types = {
            "",        "bootimage.",  "odm.",    "odm_dlkm.",   "product.",
            "system.", "system_ext.", "vendor.", "vendor_dlkm."};

    for (const auto& source : prop_types) {
        if (product) {
            prop_name = "ro.product." + source + prop;
        } else {
            prop_name = "ro." + source + "build." + prop;
        }

        property_override(prop_name.c_str(), value.c_str(), false);
    }
}

void load_dalvik_properties(void) {
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else if (sys.totalram >= 3ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else {
        return;
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

void set_device_props(void){

    char const *operator_code_file = "/proc/oplusVersion/operatorName";
    std::string operator_code_raw, device, model, market_name, fingerprint;

    if (ReadFileToString(operator_code_file, &operator_code_raw)) {
        int operator_code = stoi(operator_code_raw);
	    switch (operator_code) {
            case 140:
            case 141:
            case 146:
            case 149:
                device="RMX2151";
                model="RMX2151L1";
                fingerprint="realme/RMX2151/RMX2151L1:12/SP1A.210812.016/Q.bf75e7-1:user/release-keys";
                market_name="realme 7";
                break;
            case 142:
                device="RMX2153";
                model="RMX2153L1";
                fingerprint="realme/RMX2156/RMX2156L1:12/SP1A.210812.016/Q.11e8c10-4e353:user/release-keys";
                market_name="realme 7";
                break;
            case 94:
            case 148:
                device="RMX2155";
                model="RMX2155L1";
                fingerprint="realme/RMX2155/RMX2155L1:12/SP1A.210812.016/Q.GDPR.202207131058:user/release-keys";
                market_name="realme 7";
                break;
            case 90:
            case 92:
                device="RMX2156";
                model="RMX2156L1";
                fingerprint="realme/RMX2156/RMX2156L1:12/SP1A.210812.016/Q.11e8c10-4e353:user/release-keys";
                market_name="realme Narzo 30 4G";
                break;
            case 143:
                device="RMX2161";
                model="RMX2161L1";
                fingerprint="realme/RMX2156/RMX2156L1:12/SP1A.210812.016/Q.11e8c10-4e353:user/release-keys";
                market_name="realme Narzo 20 Pro";
                break;
            case 145:
            case 147:
                device="RMX2163";
                model="RMX2163L1";
                fingerprint="realme/RMX2163T2/RMX2163L1:12/SP1A.210812.016/Q.bf75e7-1:user/release-keys";
                market_name="realme Narzo 20 Pro";
                break;
            default:
                LOG(ERROR) << "Unknown operator found: " << operator_code;
                device="";
                model="";
                fingerprint="";
                market_name="";
		}
    }

    set_ro_build_prop("device", device);
    set_ro_build_prop("model", model);
    set_ro_build_prop("name", model);
    set_ro_build_prop("product", model, false);
    property_override("ro.product.device", device.c_str());
    property_override("ro.vendor.device", device.c_str());
    property_override("bluetooth.device.default_name", market_name.c_str());
    property_override("vendor.usb.product_string", market_name.c_str());
    property_override("ro.product.build.fingerprint", fingerprint.c_str());

}

void vendor_load_properties(void) {
#ifndef __ANDROID_RECOVERY__
    set_device_props();
#endif
    load_dalvik_properties();
}
