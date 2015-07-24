// ---------------------------------------------------------------------------

enum {
    MTH_UPDATE=73,
    MTH_CANCEL=80,
    MTH_REFER=83,
    MTH_REGISTER=84,
    MTH_MESSAGE=91,
    MTH_BYE=135,
    MTH_ACK=140,
    MTH_INFO=143,
    MTH_PRACK=145,
    MTH_PUBLISH=146,
    MTH_SUBSCRIBE=149,
    MTH_INVITE=159,
    MTH_NOTIFY=162,
    MTH_OPTION=163
};

int txmap_mthd2Idx(const char* mth) {
    int hash = (mth && *mth && *(mth+1) && *(mth+2))? 
        (toupper(*mth)%toupper(*(mth+1)))+toupper(*(mth+2)):0;
    switch (hash) {
        case MTH_INVITE:    return 0;
        case MTH_BYE:       return 1;
        case MTH_CANCEL:    return 2;
        case MTH_PRACK:     return 3;
        case MTH_REFER:     return 4;
        case MTH_INFO:      return 5;
        case MTH_NOTIFY:    return 6;
        case MTH_UPDATE:    return 7;
        case MTH_ACK:       return 8;
        case MTH_REGISTER:  return 9;
        case MTH_SUBSCRIBE: return 10;
        case MTH_OPTION:    return 11;
        case MTH_PUBLISH:   return 12;
        case MTH_MESSAGE:   return 13;
        default: return -1;
    }
}


const char* txmap_Idx2Mthd(int idx) {
    const char* M[] = {"INVITE","BYE","CANCEL","PRACK","REFER","INFO","NOTIFY","UPDATE"};
    return M[idx];
}
