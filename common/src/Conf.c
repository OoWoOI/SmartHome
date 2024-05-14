/*************************************************************************
	> File Name: Conf.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 09:20:40 AM CST
 ************************************************************************/

#include "../include/RetVal.h"
#include "../include/Conf.h"

int get_conf_val(const char *filepath, const char *key, char **val) {
    FILE *fp = NULL;

    if ((fp = fopen(filepath, "r+")) == NULL) {
        return FILE_NOT_EXIST;
    }

    size_t len = 0;
    while (getline(val, &len, fp) != -1) {
        if (strstr(*val, key) != NULL) {
            (*val) += strlen(key) + 1;
            (*val)[strlen(*val) - 1] = '\0';
            break;
        }
        memset(*val, 0, len);
    }
    
    if (strlen(*val) == 0) 
        return KEY_NOT_EXIST;//未找到
    
    fclose(fp);
    return SUCCESS;
}
