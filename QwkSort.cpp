#include "QwkSort.h"

for_s * get_data(string filNm,int num){
	fstream ind((filNm+".ind").c_str(),ios_base::in);
	for_s *list=new for_s[num];
	for(int i=0;i<num;i++){
		ind>>list[i].coord;
		Stu temp=rfFile(filNm,list[i].coord);
		list[i].grade=temp.t_grade;
	}
	return list;
}

for_s * QwkSort(for_s *list,int low,int high){
    //quick sort
    if(low>=high)return list;
	int i=low,j=high+1;
    for_s key=list[low];
	while(1){
        while(list[++i].grade<key.grade){
			if(i==high)
			break;
		}
        while(list[--j].grade>key.grade){
			if(j==low)
			break;
		}
		if(i>=j)
            break;
		for_s temp=list[i];
		list[i]=list[j];
		list[i]=temp;
	}
	for_s temp=list[low];
	list[low]=list[j];
	list[j]=temp;
	QwkSort(list,low,j-1);
    QwkSort(list,j+1,high);
	return list;
}

bool wrtFil_sort(for_s *list,int num){
	fstream sort("sort",ios_base::out);
    for(int i=num-1;i>=0;i--){
		sort<<" "<<list[i].coord;
	}
	sort.close();
	return 1;
}
