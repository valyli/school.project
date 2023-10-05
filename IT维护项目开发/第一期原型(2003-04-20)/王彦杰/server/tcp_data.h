typedef struct tagSMM_c2s        //客户端向服务器传输
{
    SMM_CHAR cIp[19] ;  //ip地址
    SMM_INT  uiPort ;    //端口
    Transfer_C2S_Struct m_Data_Transfer_C2S_Struct ;
    //SMM_INT  iFlag ;   //0:客户端刚连上服务器 1:客户端正常传输 2:客户端关闭
};

typedef struct tagSMM_s2c
{
    SMM_CHAR cIp[19] ;  //ip地址
    SMM_INT  uiPort;     //端口
    Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;
};