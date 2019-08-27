#ifndef QWKSORT_H
#define QWKSORT_H
#include"Stu.h"

typedef struct for_sort{
	long long coord;
	float grade; 
}for_s;
 
for_s * get_data(string filNm,int num);
for_s * QwkSort(for_s *list,int low,int high);
bool wrtFil_sort(for_s *list,int num);
#endif
