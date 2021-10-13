#ifndef EVENT_INFO_H
#define EVENT_INFO_H

#include "TTree.h"
#include <regex>
#include <unordered_map>
using namespace std;

/////////////////////////////////////////
// Purpose: To hold general event data //
/////////////////////////////////////////
class event_info {
private:
    std::unordered_map<std::string, int> unc_map;
    
public:
    event_info (std::string);
    virtual ~event_info () {};
    Float_t getRivetUnc(std::vector<double>, std::string);
    
};

// read data from trees into member variables
//event_info::event_info(TTree* input, std::string syst, std::string analyzer, int year) :
event_info::event_info(std::string syst) :
//year_(year),
//isEmbed(false),
unc_map{
{"_THU_ggH_Mu",0},{"_THU_ggH_Res",1},{"_THU_ggH_Mig01",2},{"_THU_ggH_Mig12",3},{"_THU_ggH_VBF2j",4},{"_THU_ggH_VBF3j",5},{"_THU_ggH_PT60",6},{"_THU_ggH_PT120",7},{"_THU_ggH_qmtop",8}
}
{
    }
        
        Float_t event_info::getRivetUnc(std::vector<double> uncs, std::string syst) {
            if (syst.find("_THU_ggH") != std::string::npos) {
                int index = unc_map[syst];
                return uncs.at(index);
//
//                if (syst.find("Up") != std::string::npos) {
//                    return uncs.at(index);
//                } else {
//                    return -1 * uncs.at(index);
//                }
            }
            else {
        return 1;
        }
        }
        
#endif
