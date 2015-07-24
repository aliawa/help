// Creating sip trunking rules

void createRules(int devId, vector<Did*>& dids, int pilotOnly )
{

    vector<string> lstFile;
    char buff[200];
    cout << "---- sipdprules -----" << endl;

    if (loadListFile(RULES_CONF, lstFile))
    {
        // Delete all rules with group id equal to SIPTRUNK_RULE_GRP_ID
        vector<string>::iterator it = remove_if(lstFile.begin(), lstFile.end(), listMatch("gid", SIPTRUNK_RULE_GRP_ID));
        lstFile.erase(it, lstFile.end());
    }

    // outgoing rules
    uint id = time(NULL);
    int   n = (pilotOnly)? 1:dids.size();
    if (devId) {
        for (int i=0; i<n; ++i, id++)
        {
            ostringstream s;
            s << id << ' ' <<  devId << ' ';
            s << "io=1 p=1 b=1 r=";
            s << dids[i]->number;
            s << " gid=" << SIPTRUNK_RULE_GRP_ID;
            lstFile.push_back(s.str());
        }
    }

    // Always create outgoing wildcard device rule
    // so that the test UA can work even if the PBX is
    // not configured.
    snprintf(buff, 200, "%d 0 io=1 p=1 s=18 b=1 r=. a=%s gid=%d",
             id,
             dids[0]->number.c_str(),
             SIPTRUNK_RULE_GRP_ID);
    lstFile.push_back(buff);


    // Inbound rules
    if (devId) {
        id++;
        snprintf(buff, 200, "%d %d io=0 p=0 d=1 b=1 gid=%d", id, devId, SIPTRUNK_RULE_GRP_ID);
        lstFile.push_back(buff);
    }
    saveListFile(RULES_CONF, lstFile);
}

