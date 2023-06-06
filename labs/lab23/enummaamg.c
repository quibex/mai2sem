#include <ctype.h>
#include <string.h>
#include "enummaamg.h"

int get_enum_id(char company[10]) {
    char lower_company[10];
    int i = 0;
    while (company[i]) {
        lower_company[i] = tolower(company[i]);
        i++;
    }
    lower_company[i] = '\0';

    if (strcmp(lower_company, "microsoft") == 0) return MICROSOFT;
    if (strcmp(lower_company, "apple") == 0) return APPLE;
    if (strcmp(lower_company, "amazon") == 0) return AMAZON;
    if (strcmp(lower_company, "meta") == 0) return META;
    if (strcmp(lower_company, "google") == 0) return GOOGLE;
    if (strcmp(lower_company, "yandex") == 0) return YANDEX;
    if (strcmp(lower_company, "samsung") == 0) return SAMSUNG;
    if (strcmp(lower_company, "intel") == 0) return INTEL;
    if (strcmp(lower_company, "nvidia") == 0) return NVIDIA;
    if (strcmp(lower_company, "sony") == 0) return SONY;
    if (strcmp(lower_company, "ibm") == 0) return IBM;
    if (strcmp(lower_company, "adobe") == 0) return ADOBE;
    if (strcmp(lower_company, "tencent") == 0) return TENCENT;
    if (strcmp(lower_company, "tesla") == 0) return TESLA;
    if (strcmp(lower_company, "spacex") == 0) return SPACEX;
    if (strcmp(lower_company, "tsmc") == 0) return TSMC;
    if (strcmp(lower_company, "visa") == 0) return VISA;
    if (strcmp(lower_company, "sber") == 0) return SBER;
    if (strcmp(lower_company, "uber") == 0) return UBER;
    if (strcmp(lower_company, "twitter") == 0) return TWITTER;
    if (strcmp(lower_company, "huawei") == 0) return HUAWEI;
    return -1;
}

char* get_company_name(int id){
    switch(id) {
        case MICROSOFT:
            return "MICROSOFT";
        case APPLE:
            return "APPLE";
        case AMAZON:
            return "AMAZON";
        case META:
            return "META";
        case GOOGLE:
            return "GOOGLE";
        case YANDEX:
            return "YANDEX";
        case SAMSUNG:
            return "SAMSUNG";
        case INTEL:
            return "INTEL";
        case NVIDIA:
            return "NVIDIA";
        case SONY:
            return "SONY";
        case IBM:
            return "IBM";
        case ADOBE:
            return "ADOBE";
        case TENCENT:
            return "TENCENT";
        case TESLA:
            return "TESLA";
        case SPACEX:
            return "SPACEX";
        case TSMC:
            return "TSMC";
        case VISA:
            return "VISA";
        case SBER:
            return "SBER";
        case UBER:
            return "UBER";
        case TWITTER:
            return "TWITTER";
        case HUAWEI:
            return "HUAWEI";
        default:
            return NULL;
    }
}