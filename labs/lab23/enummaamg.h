
enum MAAMG {
    MICROSOFT = 0,
    APPLE     = 1,
    AMAZON    = 2,
    META      = 3,
    GOOGLE    = 4,
    YANDEX    = 5,
    SAMSUNG   = 6,
    INTEL     = 7,
    NVIDIA    = 8,
    SONY      = 9,
    IBM       = 10,
    ADOBE     = 11,
    TENCENT   = 12,
    TESLA     = 13,
    SPACEX    = 14,
    TSMC      = 15,
    VISA      = 16,
    SBER      = 17,
    UBER      = 18,
    TWITTER   = 19,
    HUAWEI    = 20
};

int get_enum_id(char company[10]);
char* get_company_name(int id);