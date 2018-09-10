#ifndef jxc_string_h_
#define jxc_string_h_

//string.h常用函数实现{{{
static inline size_t strlen_jxc(const char *s)
{
	if (s == NULL)
		return 0;
	const char *p = s;
	while (*p++ != '\0');
	return p - s - 1;
}

static inline char *strcpy_jxc(char *dst, const char *src)
{
	if (dst == NULL || src == NULL)
		return NULL;
	char *p = dst;
	while ((*p++ = *src++) != '\0');
	return dst;
}

static inline char *strcat_jxc(char *dst, const char *src)
{
	char *p = dst;
	while (*p != '\0')
		p++;
	while ((*p++ = *src++) != '\0');
	return dst;
}

static inline int strcmp_jxc(const char *s1, const char *s2)
{
	int index = 0;
	while (s1[index] != '\0' || s2[index] != '\0') {
		if (s1[index] > s2[index])
			return 1;
		if (s1[index] < s2[index])
			return -1;
		index++;
	}
	if (s1[index] == '\0' && s2[index] != '\0')
		return -1;
	if (s1[index] != '\0' && s2[index] == '\0')
		return 1;
	return 0;
}

static inline char *strchr_jxc(char *s, char c)
{
	while (*s != '\0') {
		if (*s == c)
			return s;
		s++;
	}
	if (c == '\0')
		return s;
	return NULL;
}

static inline char *strrchr_jxc(char *s, char c)
{
	char *p = NULL;
	while (*s != '\0') {
		if (*s == c)
			p = s;
		s++;
	}
	if (c == '\0')
		return s;
	return p;
}

//}}}
//模式匹配算法(朴素&KMP){{{
static inline int naiveStrMatching(const char *target, const char *pattern)
{								/* 朴素匹配 */
	int t_len = strlen_jxc(target);
	int p_len = strlen_jxc(pattern);
	if (t_len < p_len)
		return -1;
	int t_i = 0, p_i = 0;
	while (t_i < t_len && p_i < p_len) {
		if (target[t_i] == pattern[p_i])
			t_i++, p_i++;
		else
			t_i = t_i - p_i + 1, p_i = 0;
	}
	if (p_i >= p_len)
		return t_i - p_len;
	else
		return -1;
}

static inline int *_findNext(const char *s)
{								/* 字符串特征向量 */
	int i = 0, k = -1, m = strlen_jxc(s);
	assert(m > 0);
	int *next = new int[m];
	assert(next != NULL);
	next[0] = -1;
	while (i < m) {
		while (k >= 0 && s[i] != s[k])
			k = next[k];
		i++, k++;
		if (i == m)
			break;
		if (s[k] == s[i])
			next[i] = next[k];
		else
			next[i] = k;
	}
	return next;
}

static inline int kmpStrMatching(const char *target, const char *pattern)
{								/* kmp 算法 */
	int *next = _findNext(pattern);
	int i = 0, j = 0, t_len = strlen_jxc(target), p_len = strlen_jxc(pattern);
	if (t_len < p_len)
		return -1;
	while (i < p_len && j < t_len) {
		if (i == -1 || target[j] == pattern[i])
			i++, j++;
		else
			i = next[i];
	}
	delete next;
	if (i >= p_len)
		return j - p_len;
	return -1;
}

//}}}

class String_jxc {
  private:
	int _size;
	char *_str;
  public:
	    String_jxc() {

	} String_jxc(const char *s) {
		_size = strlen_jxc(s);
		_str = new char[_size + 1];
		assert(_str);
		strcpy_jxc(_str, s);
	}
	~String_jxc();
	int length();
	int isEmpty();
	void clear();
	int find(const char c, const int start);
	String_jxc append();
	String_jxc concatenate(const char *s);
	String_jxc copy(const char *s);
	String_jxc insert(const char c, const int index);
	String_jxc substr(const int s, const int len);
};
#endif
