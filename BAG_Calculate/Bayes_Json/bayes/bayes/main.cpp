/////////////////////////////////源代码inf_learn_bnet.cpp////////////////////////////////////////////
//（代码中含//*<-的行，可视情况更改）
#include "pnl_dll.hpp"
#include <fstream>

PNL_USING
//加载库文件
#pragma comment(lib,"pnl.lib")
#pragma comment(lib,"cxcored.lib")
#pragma comment(lib,"cxcore.lib")
//设置证据节点
CEvidence* CreateEvidenceForBNet( const CBNet* pBnet )
{
    //make one node observed
    int nObsNds = 3;//*<-输入证据节点数
    //the observed node is
    int obsNds[] = { 0, 1, 2};//*<-输入证据节点列表
    //node 0 takes its second value (from two possible values {0, 1})
    valueVector obsVals;
    obsVals.resize(nObsNds);
    obsVals[0].SetInt(1);//*<-输入证据节点的值
       obsVals[1].SetInt(1);//*<-
    obsVals[2].SetInt(1);//*<-
    CEvidence* pEvid = CEvidence::Create( pBnet, nObsNds, obsNds, obsVals );
    return pEvid;
}

//whether the learn process is successful;用于判断学习后的模型与原模型是否相同，如不同则学习成功
int IsTheModelEqual( const CBNet* bnet1, const CBNet * bnet2, float epsilon )
{
    //compare every potential
    int numberOfNodes = bnet1->GetNumberOfNodes();

    int ret = 1;

    for( int i = 0; i < numberOfNodes; i++ )
    {
        if( !(bnet1->GetFactor(i)->IsFactorsDistribFunEqual(
            bnet2->GetFactor(i), epsilon )))
        {
            ret = 0;
        }
    }

    return ret;
}
//构建贝叶斯网络
CBNet* CreateBNet()
{
       // Creation Water-Sprinkler Bayesian network

       const int numOfNds = 4;//*<-声明网络节点数

       // 1 STEP:
       // need to specify the graph structure of the model;
       // there are two way to do it

       CGraph *pGraph;

              // Graph creation using neighbors list
        int C=0,S=1,R=2,W=3;
              int numOfNbrs[numOfNds] = { 2, 2, 2, 2 };//*<-与各节点的邻接点个数（包括父节点与子节点）
              int nbrs0[] = { S, R };//*<-定义网络结构
              int nbrs1[] = { C, W };//*<-
              int nbrs2[] = { C, W };//*<-
              int nbrs3[] = { S, R};//*<-

              // number of neighbors for every node
              int *nbrs[] = { nbrs0, nbrs1, nbrs2, nbrs3 };

              // neighbors can be of either one of the three following types:
              // a parent, a child (for directed arcs) or just a neighbor (for undirected graphs).
              // Accordingly, the types are ntParent, ntChild or ntNeighbor.

              ENeighborType nbrsTypes0[] = { ntChild, ntChild };//*<-定义邻接点的类别
              ENeighborType nbrsTypes1[] = { ntParent, ntChild };//*<-
              ENeighborType nbrsTypes2[] = { ntParent, ntChild };//*<-
              ENeighborType nbrsTypes3[] = { ntParent, ntParent };//*<-

              ENeighborType *nbrsTypes[] = { nbrsTypes0, nbrsTypes1,nbrsTypes2, nbrsTypes3 };

              // this is creation of a directed graph for the BNet model using neighbors list
              pGraph = CGraph::Create( numOfNds, numOfNbrs, nbrs, nbrsTypes );

       // 2 STEP:
       // Creation NodeType objects and specify node types for all nodes of the model.

       nodeTypeVector  nodeTypes;

       // number of node types is 1, because all nodes are of the same type
       // all four are discrete and binary
       CNodeType nt(1,2);//*<-定义各节点变量的类别nt（变量类别数，变量取值数）
       nodeTypes.push_back(nt);

       intVector nodeAssociation;
       // reflects association between node numbers and node types
       // nodeAssociation[k] is a number of node type object in the
       // node types array for the k-th node
       nodeAssociation.assign(numOfNds, 0);

       // 2 STEP:
       // Creation base for BNet using Graph, types of nodes and nodes association

       CBNet* pBNet = CBNet::Create( numOfNds, nodeTypes, nodeAssociation, pGraph );

       // 3 STEP:
       // Allocation space for all factors of the model
       pBNet->AllocFactors();

       // 4 STEP:
       // Creation factors and attach their to model

       //create raw data tables for CPDs
       float table0[] = { 0.5f, 0.5f };//*<-定义初始CPT表
       float table1[] = { 0.5f, 0.5f, 0.9f, 0.1f };
       float table2[] = { 0.8f, 0.2f, 0.2f, 0.8f };
       float table3[] = { 1.0f, 0.0f, 0.1f, 0.9f, 0.1f, 0.9f, 0.01f, 0.99f };

       float* table[] = { table0, table1, table2, table3 };//*<-

       int i;
       for( i = 0; i < numOfNds; ++i )
       {
              pBNet->AllocFactor(i);

              CFactor* pFactor = pBNet->GetFactor(i);

              pFactor->AllocMatrix( table[i], matTable );
       }

       return pBNet;
}
void TestBNet(const CBNet* pBnet)//用于测试网络，输出网络结构和参数
{
       pBnet->GetGraph()->Dump();
  //get information from learned model
       int nFactors = pBnet->GetNumberOfFactors();
       const CFactor *pCPD;
       const CNumericDenseMatrix<float> *pMatForCPD;
       int numOfEl;
       const float *dataCPD;
       int f;
       for( f = 0; f < nFactors; f++ )
       {

              std::cout<<std::endl<<" probability distribution for node "<<f<<std::endl;
              pCPD = pBnet->GetFactor(f);
              //all matrices are dense
              pMatForCPD = static_cast<CNumericDenseMatrix<float> *>
                     (pCPD->GetMatrix(matTable));
              pMatForCPD->GetRawData( &numOfEl, &dataCPD );
              int j;
              for( j = 0; j < numOfEl; j++ )
              {
                     std::cout<<" "<<dataCPD[j];
              }
       }
       std::cout<<std::endl;
       return;
}

CBNet* Learn_process(const CBNet* pBnet)//网络参数学习
{
       //start learning for this model
       //create WS BNet with different matrices

       std::cout<<"Learning procedure /n ";
       CGraph *pGraph = CGraph::Copy( pBnet->GetGraph() );
       CModelDomain *pMD = pBnet->GetModelDomain();

       CBNet* pLearnBNet = CBNet::CreateWithRandomMatrices( pGraph, pMD );//定义学习算法

       //loading data from file
       const char * fname = "Data/casesForWS";//用于学习训练的数据

       pEvidencesVector evVec;

       if( ! CEvidence::Load(fname,  &evVec, pMD) )
       {
              printf("can't open file with cases");
              exit(1);
              getchar();
       }
       int numOfSamples = evVec.size();
       std::cout<<"Number of cases for learning = "<<numOfSamples<<std::endl;

       //create learning engine
       CEMLearningEngine *pLearn = CEMLearningEngine::Create( pLearnBNet );

       //set data for learning

       pLearn->SetData( numOfSamples, &evVec.front() );
       pLearn->Learn();

       //compare information from learned model with initial model
       //both BNet have the same topology and node types
       //- we need only to compare CPDs
       //need to set tolerance
       float epsilon = 1e-1f;
       int isEqual = IsTheModelEqual( pBnet, pLearnBNet, epsilon );

       std::cout << " The model was learned. The learning was " << std::endl;

       if( isEqual )
       {
              std::cout << " successful " << std::endl;
       }
       else
       {
              std::cout << " unsuccessful " << std::endl;
       }

       int ev;
       for( ev = 0; ev < evVec.size(); ev++ )
       {
              delete evVec[ev];
       }
       delete pLearn;
       delete pBnet;
       return pLearnBNet;

}
void Infer_Process(const CBNet* pBnet)//推论
{
       //create simple evidence for node 0 from BNet
       CEvidence* pEvidForWS = CreateEvidenceForBNet(pBnet);

       //create Naive inference for BNet
       CNaiveInfEngine* pNaiveInf = CNaiveInfEngine::Create( pBnet );//定义推论引擎

       //enter evidence created before
       pNaiveInf->EnterEvidence( pEvidForWS );

       //set the query node
       int numQueryNds = 1;//*<-定义查询变量的个数
       int queryNds[] = { 3 };//*<-定义查询变量
    //get a marginal for query set of nodes
       pNaiveInf->MarginalNodes( queryNds, numQueryNds );
       const CPotential* pMarg = pNaiveInf->GetQueryJPD();
    //display the evidence node and such velue of BNet
       intVector obsNds;
       pConstValueVector obsVls;
       pEvidForWS->GetObsNodesWithValues(&obsNds, &obsVls);

       int i;
       for( i = 0; i < obsNds.size(); i++ )
       {
              std::cout<<" observed value for node "<<obsNds[i];
              std::cout<<" is "<<obsVls[i]->GetInt()<<std::endl;
       }

       //display the query node and such velue of BNet
       int nnodes;
       const int* domain;
       pMarg->GetDomain( &nnodes, &domain );
       std::cout<<" inference results: /n";

       std::cout<<" probability distribution for nodes [ ";

       for( i = 0; i < nnodes; i++ )
       {
              std::cout<<domain[i]<<" ";
       }

       std::cout<<"]"<<std::endl;

       CMatrix<float>* pMat = pMarg->GetMatrix(matTable);

       // graphical model hase been created using dense matrix
       // so, the marginal is also dense
       EMatrixClass type = pMat->GetMatrixClass();
       if( ! ( type == mcDense || type == mcNumericDense || type == mc2DNumericDense ) )
       {
              assert(0);
       }

       int nEl;
       const float* data;
       static_cast<CNumericDenseMatrix<float>*>(pMat)->GetRawData(&nEl, &data);
       for( i = 0; i < nEl; i++ )
       {
              std::cout<<" "<<data[i];
       }
       std::cout<<std::endl;


       delete pEvidForWS;
       delete pNaiveInf;
}
int main()
{
    //create Water - Sprinkler BNet
    CBNet* pBnet = CreateBNet();

    //Test content of Graph
    TestBNet(pBnet);

       //Inference Process
       Infer_Process(pBnet);

    //Learn Process
       CBNet* pLearnedBnet;
       pLearnedBnet=Learn_process(pBnet);

       //get information from learned model
       TestBNet(pLearnedBnet);

   //Inference Process
       Infer_Process(pLearnedBnet);


    getchar();
    return 0;
}
