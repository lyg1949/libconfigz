#ifndef __CONFIGZ__H_
#define __CONFIGZ__H_

#ifdef __cplusplus
extern "C" {
#endif
//获取配置文件中label的个数
//返回值为-1表示失败
int configz_countLabel(const char * configfile, const char * label);
/**configfile,key均不能为NULL.
		label为配置文件中标签的名称，如[test]，label为test
		num为从配置文件中第几个label处查找，配置文件中允许多个相同标签
		label为NULL则认为文件中没有标签，查找过程中遇到标签则认为文件结束，这时忽略num这个参数。
		num为0则认为配置文件中每个标签只允许出现一次，如果有多个相同的标签，则只查找第一个
		返回值为0表示读取成功，-1表示失败
*/
int configz_readString(const char * configfile, const char * label, const char * key, char * value, int num);
//IPV4
int configz_readIP(const char * configfile, const char * label, const char * key, char * value, int num);
#ifdef __cplusplus
}
#endif
#endif
