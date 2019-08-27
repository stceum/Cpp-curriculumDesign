#include "Stu.h"


course_::course_(){
    grade=0;
}

Stu::Stu(){
	
	sex=false;
	num=0;
	cour=((course *)0);
	if(num==0)
		t_grade=0;
	else{
		
		float total=0;
		for(int i=0;i<num;i++){
			total+=cour[i].grade;
		}
		
		t_grade=total/num;
	}
	
}

bool operator==(Stu &a,Stu &b){
	
	bool same=0;
	same=(a.name==b.name)&&(a.id==b.id)&&(a.major==b.major);
	if(same==false)
		return same;
	else{
		same=(a.sex==b.sex)&&(a.num==b.num);
		if(same==false)
			return same;
		else{
			if(a.num==0)
				return  same;
			else{
				for(int i=0;i<a.num;i++){
					if((a.cour[i].cour==a.cour[i].cour)&&(a.cour[i].grade-b.cour[i].grade<0.0001))
						continue;
					else
						return false;
				}
				return same;
			}
		}
	}
}

Stu::Stu(const Stu &tar){
	this->num=tar.num;
	this->name=tar.name;
	this->major=tar.major;
	this->id=tar.id;
	this->sex=tar.sex;
	this->t_grade=tar.t_grade;
	if(tar.num==0)
		this->cour=((course *)0);
	else{
		this->cour=new course[tar.num];
		for(int i=0;i<tar.num;i++){
			this->cour[i].cour=tar.cour[i].cour;
			this->cour[i].grade=tar.cour[i].grade;
		}
	}
}

bool wtFile(string filename,Stu &tar,long long index){
	fstream file(filename.c_str(),ios_base::out|ios_base::app);
	if(index==-1){//write
		fstream ind((filename+".ind").c_str(),ios_base::out|ios_base::app);
		file.seekp(0,ios_base::end);
		long long point = file.tellp();
		ind<<" "<<point;
		ind.close();
		file<<tar.name<<";"<<tar.sex<<";"<<tar.id<<";"<<tar.major<<";"<<tar.num<<";";
        tar.t_grade=0;
        if(tar.num!=0){
            for(int i=0;i<tar.num;i++){
                file<<tar.cour[i].cour<<";"<<tar.cour[i].grade<<";";
                tar.t_grade+=tar.cour[i].grade;
            }
            tar.t_grade/=tar.num;

        }
        file<<tar.t_grade<<";";
		file<<endl;
		file.close();
	}
	else{//find and replace
		fstream indO((filename+".ind").c_str(),ios_base::out|ios_base::in);//old
		fstream indN(("%"+filename+".ind").c_str(),ios_base::out);//new
		indO.seekp(0);
		file.seekp(0,ios_base::end);
		long long point = file.tellp();
		long long curPoint;//current point
		while(!indO.eof()){
			indO>>curPoint;
			if(curPoint!=index){
				indN<<" "<<curPoint;
			}
			else
				indN<<" "<<point;
		}
		indO.close();
		indN.close();
		file<<tar.name<<";"<<tar.sex<<";"
			<<tar.id<<";"<<tar.major<<";"
			<<tar.num<<";";
        tar.t_grade=0;
        if(tar.num!=0){
            for(int i=0;i<tar.num;i++){
                file<<tar.cour[i].cour<<";"<<tar.cour[i].grade<<";";
                tar.t_grade+=tar.cour[i].grade;
            }
            tar.t_grade/=tar.num;

        }
        file<<tar.t_grade<<";";
		file<<endl;
		file.close();
		
		remove((filename+".ind").c_str());
		rename(("%"+filename+".ind").c_str(),(filename+".ind").c_str());
	}
	return true;
}

bool clnLit(string filNm){

    fstream file(filNm.c_str(),ios_base::in);
    fstream ind((filNm+".ind").c_str(),ios_base::in);

    long long point;
    while(!ind.eof()){
        if(ind>>point){
            file.seekg(point);
            Stu tem;
            stringstream str;
            getline(file,tem.name,';');

            string strr;
            getline(file,strr,';');

            str<<strr;
            str>>tem.sex;
            str.clear();

            getline(file,tem.id,';');
            getline(file,tem.major,';');

            getline(file,strr,';');
            str<<strr;
            str>>tem.num;
            str.clear();

            if(tem.num!=0){
                tem.cour=new course[tem.num];
                for(int i=0;i<tem.num;i++){
                    getline(file,tem.cour[i].cour,';');
                    getline(file,strr,';');
                    str<<strr;
                    str>>tem.cour[i].grade;
                    str.clear();
                }
            }
            getline(file,strr,';');
            str<<strr;
            str>>tem.t_grade;

            wtFile(("%"+filNm),tem);
        }
        else
            break;
    }
    file.close();
    ind.close();

    remove(filNm.c_str());
    rename(("%"+filNm).c_str(),filNm.c_str());
    remove((filNm+".ind").c_str());
    rename(("%"+filNm+".ind").c_str(),(filNm+".ind").c_str());
    return 1;
}

Stu rfFile(string filename,long long index){
	fstream file(filename.c_str(),ios_base::in);
	file.seekg(index);
	Stu tem;
	stringstream str;
	getline(file,tem.name,';');
	
	string strr;
	getline(file,strr,';');
	
	str<<strr;
	str>>tem.sex;
	str.clear();
	
	getline(file,tem.id,';');
	getline(file,tem.major,';');
	
	getline(file,strr,';');
	str<<strr;
	str>>tem.num;
	str.clear();
	
	if(tem.num!=0){
		tem.cour=new course[tem.num];
		for(int i=0;i<tem.num;i++){
			getline(file,tem.cour[i].cour,';');
			getline(file,strr,';');
			str<<strr;
			str>>tem.cour[i].grade;
			str.clear();
		}
	}
    getline(file,strr,';');
    str<<strr;
    str>>tem.t_grade;
    str.clear();
	
	file.close();
	return tem;
}

bool dfFile(string filename,long long index){
    fstream indO((filename+".ind").c_str(),ios_base::out|ios_base::in);//old
    fstream indN(("%"+filename+".ind").c_str(),ios_base::out);//new
    long long curPoint;//current point
    while(!indO.eof()){
        indO>>curPoint;
        if(curPoint!=index){
            indN<<" "<<curPoint;
        }
    }
    indO.close();
    indN.close();

    remove((filename+".ind").c_str());
    rename(("%"+filename+".ind").c_str(),(filename+".ind").c_str());
    return 1;
}

//test
/*
Stu _test(){
	Stu temp;
	cout<<"name"<<endl;
	cin>>temp.name;
	cout<<"sex"<<endl;
	cin>>temp.sex;
	cout<<"id"<<endl;
	cin>>temp.id;
	cout<<"major"<<endl;
	cin>>temp.major;
	cout<<"number"<<endl;
	cin>>temp.num;
	temp.cour=new course[temp.num];
	for(int i=0;i<temp.num;i++){
		cout<<i<<":"<<endl;
		cin>>temp.cour[i].cour;
		cin>>temp.cour[i].grade;
	}
	
	return temp;
}
*/

bool s_jug(string &a,string &b){
    if(a==""||b=="")
        return 1;
    else {
        if(a==b)
            return 1;
        else {
            return 0;
        }
    }
}

bool srch(string filename,Stu &tar){//open the file,open the index,write the result to a new file
    fstream index((filename+".ind").c_str(),ios_base::in);
    fstream srch_res("res",ios_base::out);
    long long point;
    while (!index.eof()) {
        index>>point;
        Stu temp=rfFile(filename,point);
        if(s_jug(tar.name,temp.name)&&s_jug(tar.id,temp.id)&&s_jug(temp.major,tar.major)&&temp.sex==tar.sex)
            srch_res<<" "<<point;
    }
    index.close();
    srch_res.close();
    return 1;
}
