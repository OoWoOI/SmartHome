/*************************************************************************
	> File Name: Utils.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:21:41 PM CST
 ************************************************************************/

#ifndef _UTILS_H
#define _UTILS_H





#ifdef _D
    
#define DBG(fmt, args...) {\
    printf(fmt, ##args);\
}

#else 

#define DBG(fmt, args...) 

#endif 

#endif
