#ifndef __CONFIGZ__H_
#define __CONFIGZ__H_

#ifdef __cplusplus
extern "C" {
#endif
int configz_readKV(const char * configfile, const char * key, char * value);//读取key的value，如果有多个相同的key，只读取第一个
int configz_countLabel(const char * configfile, const char * label);//获取配置文件中label的个数
int configz_readSLKV(const char * configfile, const char * label, const char * key, char * value);//读取label中的key的value;如果有多个相同label的话，只读取第一个label的
int configz_readLKV(const char * configfile, const char * label, const char * key, char * value, int num);//读取第num个label中的key的value;num从1开始
#ifdef __cplusplus
}
#endif
#endif
