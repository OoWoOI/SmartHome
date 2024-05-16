/*************************************************************************
	> File Name: ClientConf.h
	> Author: 
	> Mail: 
	> Created Time: Wed 15 May 2024 08:46:19 AM CST
 ************************************************************************/

#ifndef _CLIENTCONF_H
#define _CLIENTCONF_H

#include <stdlib.h>
#include "../common/include/Utils.h"
#include "../common/include/RetVal.h"
#include "../common/include/Conf.h"

#define LOGFILE "./conf/client.ini"

char *Get_Server_Ip();

int Get_Server_Port();



#endif
