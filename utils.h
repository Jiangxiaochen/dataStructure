#ifndef jxc_utils_h
#define jxc_utils_h


#define SPLIT_LINE printf("---------------------------------------\n")
#define INFINITY_JXC 9999
#define PRINT_ARR(ARR,LEN){\
	for (int i = 0; i < LEN; i++) {\
		cout << ARR[i] << " ";\
	}\
	cout << endl;\
}
#define RAND_ARR(ARR,LEN){\
	srand(time(NULL));\
	for (int i = 0; i < LEN; i++) {\
		ARR[i] = rand()%1000000;\
	}\
}
#define LEN_ARR(ARR) (int)(sizeof(ARR)/sizeof(ARR[0]))


template < typename T > static inline void swap(T & a, T & b)
{
	T   tmp = a;
	a = b;
	b = tmp;
}

#endif
