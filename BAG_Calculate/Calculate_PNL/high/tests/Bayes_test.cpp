#include<iostream>
#include <time.h>
#include "test_conf.hpp"
//#include "/home/moonsea/OpenPNL-master/trs/include/trsapi.h"
#include <stdlib.h>
#include <string.h>
#include <string>
#include "pnl_dll.hpp"
//#include "/home/moonsea/OpenPNL-master/high/include/pnlHigh.hpp"
//#include <pnlHigh.hpp>
//#include "/home/moonsea/OpenPNL-master/high/include/Tokens.hpp"
//#include "/home/moonsea/OpenPNL-master/high/include/TestPnlHigh.hpp"
//#include "/home/moonsea/OpenPNL-master/high/include/pnlException.hpp"
//#include <pnlException.hpp>
//#include "/home/moonsea/OpenPNL-master/high/include/pnlFakePtr.hpp"
//#include <pnlFakePtr.hpp>
//#include "BNet.hpp"
#include "pnlWProbabilisticNet.hpp"
#include "pnlWGraph.hpp"
//#include "BNet.hpp"


using namespace std;

int main(int arg,char * argv[])
{
    int a=1,b=2;
    int c=a+b;
    cout<<c<<endl;

    //creating bayes net
    //BayesNet net;
    BayesNet net;

    //adding node
    net.AddNode("discrete^Cloudy","true false");
    net.AddNode(discrete^"Sprinkler Rain WetGrass","true false");


    //adding edges
    net.AddArc("Cloudy","Sprinkler Rain");
    net.AddArc("Sprinkler Rain","WetGrass");


    //sopecfify the CPD
    //cloudy
    net.SetPTabular("Cloudy^true","0.6");
    net.SetPTabular("Cloudy^false","0.4");
    //spprinkler
    net.SetPTabular("Sprinkler^true Sprinkler^false","0.1 0.9","Cloudy^true");
    net.SetPTabular("Sprinkler^true Sprinkler^false","0.5 0.5","Cloudy^false");
    //rain
    net.SetPTabular("Rain^true Rain^false","0.8 0.2","Cloudy^true");
    net.SetPTabular("Rain^true Rain^false","0.2 0.8","Cloudy^false");
    //WetGrass
    net.SetPTabular("WetGrass^true WetGrass^false","0.99 0.01","Sprinkler^true Rain^true");
    net.SetPTabular("WetGrass^true WetGrass^false","0.9 0.1","Sprinkler^true Rain^false");
    net.SetPTabular("WetGrass^true WetGrass^false","0.9 0.1","Sprinkler^false Rain^true");
    net.SetPTabular("WetGrass^true WetGrass^false","0.0 1.0","Sprinkler^false Rain^false");


    //get the cpd
    TokArr PCloudy=net.GetPTabular("Cloudy");
    String PCloudyStr=String(PCloudy);
    float PCloudyTrueF=PCloudy[0].FltValue();
    float PCloudyFalseF=PCloudy[1].FltValue();
    cout<<endl<<"Cloudy"<<endl;
     cout<<PCloudyStr<<endl;
    cout<<PCloudyTrueF<<endl;
    cout<<PCloudyFalseF<<endl;

    /*
    //adding evidence
    //net.AddEvidToBuf("Rain^true WetGrass^true");
    net.EditEvidence("Rain^true WetGrass^true");
    net.CurEvidToBuf();
    net.LearnParameters();
    cout<<endl<<"evidence Rain^true WetGrass^true"<<endl;

    //get the jpd
    TokArr WetGrassMarg=net.GetJPD("WetGrass");
    String WetGrassMargStr=String(WetGrassMarg);
    cout<<endl<<"WetGrass JPD"<<endl<<WetGrassMargStr<<endl;

    TokArr WetGrassAndSprinklerMarg=net.GetJPD("WetGrass Sprinkler Rain");
    String WetGrassAndSprinklerMargStr=String(WetGrassAndSprinklerMarg);
    cout<<endl<<"WetGrass and Sprinkler JPD"<<endl<<WetGrassAndSprinklerMargStr<<endl;

    TokArr WetGrassMPE=net.GetMPE("WetGrass");
    String WetGrassMPEStr=String(WetGrassMPE);
    cout<<endl<<"WetGrass MPE"<<endl<<WetGrassMPEStr<<endl;

    TokArr WetGrassAndSprinklerMPE=net.GetMPE("WetGrass Sprinkler Rain");
    String WetGrassAndSprinklerMPEStr=String(WetGrassAndSprinklerMPE);
    cout<<endl<<"WetGrass and Spinkler MPE"<<endl<<WetGrassAndSprinklerMPEStr<<endl;

    //delete evidence
    net.ClearEvid();
    cout<<"ok"<<endl;*/
    //net.AddEvidToBuf("Sprinkler^true WetGrass^true");
    net.EditEvidence("Sprinkler^true WetGrass^true");
    net.CurEvidToBuf();
    net.LearnParameters();
    cout<<endl<<"evidence Sprinkler^true WetGrass^true"<<endl;

    //get jpd
    TokArr WetGrassMarg=net.GetJPD("WetGrass");
    String WetGrassMargStr=String(WetGrassMarg);
    cout<<endl<<"WetGrass JPD"<<endl<<WetGrassMargStr<<endl;

    TokArr WetGrassAndSprinklerMarg=net.GetJPD("WetGrass Sprinkler Rain");
    String WetGrassAndSprinklerMargStr=String(WetGrassAndSprinklerMarg);
    cout<<endl<<"WetGrass and Sprinkler JPD"<<endl<<WetGrassAndSprinklerMargStr<<endl;

    TokArr WetGrassMPE=net.GetMPE("WetGrass");
    String WetGrassMPEStr=String(WetGrassMPE);
    cout<<endl<<"WetGrass MPE"<<endl<<WetGrassMPEStr<<endl;

    TokArr WetGrassAndSprinklerMPE=net.GetMPE("WetGrass Sprinkler Rain Cloudy");
    String WetGrassAndSprinklerMPEStr=String(WetGrassAndSprinklerMPE);
    cout<<endl<<"WetGrass and Spinkler MPE"<<endl<<WetGrassAndSprinklerMPEStr<<endl;


    cout<<endl<<"moonsea"<<endl;
    return 0;

}
