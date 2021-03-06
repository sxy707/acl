
#ifndef	__ACL_MYSTRING_INCLUDE_H__
#define	__ACL_MYSTRING_INCLUDE_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include "acl_define.h"

#include <string.h>

/**
 * 功能: 安全的字符串拷贝宏函数, 可以保证最后一个字节为  "\0"
 * @param _obj {char*} 目的内存区指针
 * @param _src {const char*} 源字符串指针
 * @param _size {int} 目的内存区的空间大小
 */
#ifndef ACL_SAFE_STRNCPY
#ifdef	WIN32
#define ACL_SAFE_STRNCPY(_obj, _src, _size) do {            \
    size_t _n = strlen(_src);                               \
    _n = _n > (size_t ) _size - 1? (size_t) _size - 1 : _n; \
    memcpy(_obj, _src, _n);                                 \
    _obj[_n] = 0;                                           \
} while (0)
#else
#define ACL_SAFE_STRNCPY(_obj, _src, _size) do {            \
    if (_obj != NULL && _src != NULL && (int)_size >= 0) {  \
        strncpy(_obj, _src, _size);                         \
            if ((int)_size > 0)                             \
                _obj[_size - 1] = 0;                        \
            else                                            \
                _obj[_size] = 0;                            \
	}                                                       \
} while (0)
#endif
#endif

/**
 * 将字符串转换为小写，直接在原内存空间进行操作
 * @param string {char *} 给定的字符串
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_lowercase(char *string);

/**
 * 将给定字符串的前 n 个字节转换为小写
 * @param string {char *} 给定的字符串
 * @param n {int} 最多仅转换的字节数
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_lowercase2(char *string, size_t n);

/**
 * 将给定字符串转换为小写，结果存储于另一个内存区内
 * @param string {const char*} 源字符串
 * @param buf {char*} 存储转换结果的内存指针
 * @param size {size_t} buf 的空间大小
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_lowercase3(const char *string, char *buf, size_t size);

/**
 * 将字符串转换为大写，直接在原内存空间进行操作
 * @param string {char *} 给定的字符串
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_uppercase(char *string);

/**
 * 将字符串转换为大写，直接在原内存空间进行操作, 最大转换长度有限制
 * @param string {char *} 给定的字符串
 * @param n {int} 最多仅转换的字节数
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_uppercase2(char *string, size_t n);

/**
 * 将给定字符串的前 n 个字节转换为大写
 * @param string {char *} 给定的字符串
 * @param buf {char*} 存储转换结果的内存区
 * @param size {size_t} buf 的空间大小(字节)
 * @return {char*} 成功返回字符串地址，否则返回 NULL
 */
ACL_API char *acl_uppercase3(const char *string, char *buf, size_t size);

/**
 * 将给定字符串用另一个分隔符字符串进行分割
 * @param src {char**} 需要被分割的字符串的地址的指针，必须是非空指针，
 *  可以是空字符串，此时该函数返回 NULL
 * @param sep {const char*} 分隔符，非空字符串
 * @return {char*} 当前被分割的字符串的指针位置，src 指向下一个将要进行
 *  分隔的起始位置；
 *  1）当返回 NULL 时，则表示分隔过程结束，此时 src 的指针位置被赋予 '\0'；
 *  2）当返回非 NULL 时，则此时 src 指向的字符串可能是或不是空字符串，
 *     如果指向空字符串，则再次分隔时函数肯定能返回 NULL，否则，当再次分隔时
 *     函数返回非 NULL 指针
 *  举例: 源字符串："abcd=|efg=|hijk", 分隔符 "=|"，则第一次分隔后
 *  src 将指向 "efg"，而返回的地址为 "abcd"
 */
ACL_API char *acl_mystrtok(char **src, const char *sep);

/**
 * 获得一个逻辑行, 如果某行的尾部由连接符 "\\" 连接，则将下一行合并至本行,
 * 同时将一行字符串中的以及转义字符回车换行("\r\n" or "\n")去掉
 * @param src {char**} 源字符串的地址指针
 * @return {char*} 返回一行数据, 如果返回空则表示没有可用的逻辑行
 */
ACL_API char *acl_mystrline(char **src);

/**
 * 去掉给定字符串中的 " ", "\t"
 * @param str {char*} 源字符串
 * @return {char*} 与源字符串相同的地址
 */
ACL_API char *acl_mystr_trim(char *str);

/**
 * 从源字符串中去掉给定字符串
 * @param haystack {const char*} 源字符串
 * @param needle {const char*} 需要从源字符串中被整体去掉的字符串
 * @param buf {char*} 存储结果的内存开始位置
 * @param bsize {int} buf 的空间大小
 * @return {int} 拷贝至 buf 中的字符串长度
 */
ACL_API int acl_mystr_strip(const char *haystack, const char *needle, char *buf, int bsize);

/**
 * 从源字符串中找到一行的结束位置并去掉包含回车换行符及其以后的字符串
 * @param str_src {char*} 源字符串
 * @return {int} 0 表示成功，-1表示失败, 也许应该返回最后转换结果的长度!
 */
ACL_API int acl_mystr_truncate_byln(char *str_src);

/**
 * 从后向前比较两个给定字符串，大小写不敏感且限定最大比较范围
 * @param s1 {const char*} 字符串地址
 * @param s2 {const char*} 字符串地址
 * @param n {size_t} 最大比较范围
 * @return {int} 比较结果. 0: 相等, >0: 第一个字符串大于第二个字符串,
 *  < 0: 第一个字符串小第二个字符串
 */
ACL_API int acl_strrncasecmp(const char *s1, const char *s2, size_t n);

/**
 * 从后向前比较两个给定字符串, 大小写敏感且限定最大比较范围
 * @param s1 {const char*} 字符串地址
 * @param s2 {const char*} 字符串地址
 * @param n {size_t} 最大比较范围
 * @return {int} 比较结果. 0: 相等, >0: 第一个字符串大于第二个字符串,
 *  < 0: 第一个字符串小第二个字符串
 */
ACL_API int acl_strrncmp(const char *s1, const char *s2, size_t n);

/**
 * 从后向前扫描查找字符串，大小写敏感
 * @param haystack {char *} 源字符串
 * @param needle {const char *} 匹配查找的字符串
 * @return {char *} != NULL: Ok, NULL: 未发现
 */
ACL_API char *acl_rstrstr(char *haystack, const char *needle);

/**
 * 从前向后扫描查找字符串，大小写不敏感
 * @param haystack {char *} 源字符串
 * @param needle {const char *} 匹配查找的字符串
 * @return {char *} != NULL: Ok, NULL: 未发现
 */
ACL_API char *acl_strcasestr(char *haystack, const char *needle);

/**
 * 从后向前扫描查找字符串，大小写不敏感
 * @param haystack {char *} 源字符串
 * @param needle {const char *} 匹配查找的字符串
 * @return {char *} != NULL: Ok, NULL: 未发现
 */
ACL_API char *acl_rstrcasestr(char *haystack, const char *needle);

/**
 * 计算给定字符串的长度，但限制了最大计算长度，以免产生越界现象，要比 strlen
 * 安全，如，如果给定字符串没有以 "\0" 结尾，则该函数就不会产生越界
 * @param s {const char*} 字符串
 * @param count {size_t} 最大计算长度
 * @return {size_t} 字符串 s 的实际长度
 */
ACL_API size_t acl_strnlen(const char * s, size_t count);

/**
 * 比较两个字符串是否相同，大小写不敏感
 * @param s1 {const char*}
 * @param s2 {cosnt char*}
 * @return {int} 0: 相同; < 0: s1 < s2; > 0: s1 > s2
 */
ACL_API int acl_strcasecmp(const char *s1, const char *s2);

/**
 * 比较两个字符串是否相同，大小写不敏感，同时限定最大比较长度
 * @param s1 {const char*}
 * @param s2 {cosnt char*}
 * @param n {size_t} 限定比较的最大长度
 * @return {int} 0: 相同; < 0: s1 < s2; > 0: s1 > s2
 */
ACL_API int acl_strncasecmp(const char *s1, const char *s2, size_t n);
/**
 * WINDOWS下不支持一些字符串比较函数
 */
#ifdef	WIN32
# ifndef strcasestr
#  define strcasestr	acl_strcasestr
# endif
# ifndef strcasecmp
#  define strcasecmp	acl_strcasecmp
# endif
# ifndef strncasecmp
#  define strncasecmp	acl_strncasecmp
# endif
#endif

#ifndef strrncasecmp
# define strrncasecmp	acl_strrncasecmp
#endif
#ifndef strrncmp
# define strrncmp	acl_strrncmp
#endif

/*----------------------------------------------------------------------------
 * 保证结果类似于如下形式:
 * /home/avwall/test.txt
 * @param psrc_file_path {const char*} 源字符串
 * @param pbuf {char*} 存储结果的内存区
 * @param sizeb {int} pbuf 的空间大小
 * @return {int} 0 成功，-1失败
 */
ACL_API int acl_file_path_correct(const char *psrc_file_path, char *pbuf, int sizeb);

/*----------------------------------------------------------------------------
 * 保证路径名经过此函数后都为如下格式:
 * 源:   /home/avwall/, /home//////avwall/, /home/avwall, /////home/avwall///
 *       /home/avwall////, /home///avwall///, ///home///avwall///
 * 结果: /home/avwall/
 * @param psrc_dir {const char*} 源字符串
 * @param pbuf {char*} 存储结果的内存区
 * @param sizeb {int} pbuf 的空间大小
 * @return {int} 0 表示成功，-1表示失败
 */
ACL_API int acl_dir_correct(const char *psrc_dir, char *pbuf, int sizeb);

/*----------------------------------------------------------------------------
 * 从类似: /home/avwall/log.txt 中提取 /home/avwall/ 作为结果返回
 * @param pathname {const char*} 源字符串
 * @param pbuf {char*} 存储结果的内存区
 * @param bsize {int} pbuf 的空间大小
 * @return {int} 0 成功，-1失败
 */
ACL_API int acl_dir_getpath(const char *pathname, char *pbuf, int bsize);

/**
 * 将数据字符串转换为64位无符号长整型
 * @param str {const char*} 字符串指针
 * @return {acl_uint64} 无符号长整型
 */
ACL_API acl_uint64 acl_atoui64(const char *str);

/**
* 将数据字符串转换为64位符号长整型
* @param str {const char*} 字符串指针
* @return {acl_int64} 无符号长整型
*/
ACL_API acl_int64 acl_atoi64(const char *str);

/**
 * 将64位无符号长整型转换为字符串
 * @param value {acl_uint64} 64位无符号长整型
 * @param buf {char*} 用来存取转换结果的内存空间
 * @param size {sizt_t} buf 的空间大小，其中要求其最小为21个字节
 * @return {const char*} 转换的结果，如果转换成功则不为空，否则为空
 */
ACL_API const char *acl_ui64toa(acl_uint64 value, char *buf, size_t size);

/**
 * 将64位符号长整型转换为字符串
 * @param value {acl_int64} 64位符号长整型
 * @param buf {char*} 用来存取转换结果的内存空间
 * @param size {sizt_t} buf 的空间大小，其中要求其最小为21个字节
 * @return {const char*} 转换的结果，如果转换成功则不为空，否则为空
 */
ACL_API const char *acl_i64toa(acl_int64 value, char *buf, size_t size);

/**
 * 将64位符号长整型转换为某进制的字符串
 * @param value {acl_int64} 64位符号长整型
 * @param buf {char*} 用来存取转换结果的内存空间
 * @param size {sizt_t} buf 的空间大小，其中要求其最小为21个字节
 * @param radix {int} 进制, 如: 8 表示八进制, 10 表示十进制, 16 表示十六进制
 * @return {const char*} 转换的结果，如果转换成功则不为空，否则为空
 */
ACL_API const char *acl_i64toa_radix(acl_int64 value, char *buf, size_t size, int radix);

/**
 * 将64位无符号长整型转换为某进制的字符串
 * @param value {acl_int64} 64位符号长整型
 * @param buf {char*} 用来存取转换结果的内存空间
 * @param size {sizt_t} buf 的空间大小，其中要求其最小为21个字节
 * @param radix {int} 进制, 如: 8 表示八进制, 10 表示十进制, 16 表示十六进制
 * @return {const char*} 转换的结果，如果转换成功则不为空，否则为空
 */
ACL_API const char *acl_ui64toa_radix(acl_uint64 value, char *buf, size_t size, int radix);

#ifdef  __cplusplus
}
#endif

#endif
