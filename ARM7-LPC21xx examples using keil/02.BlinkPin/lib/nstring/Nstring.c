#include "Nstring.h"

int str_len(const char *s)
{
	int i;
	for(i=0;s[i];i++);	

return i;	
}

void str_cpy(char *d,const char *s)
{
	int i;
	for(i=0;s[i];i++)
		d[i]=s[i];

	d[i]='\0';

} 

void str_ncpy(char *d,const char *s,int clen)
{
	int i;
	for(i=0;i<clen;i++)
		d[i]=s[i];

	d[i]='\0';
} 

int str_cmp(const char *s1,const char *s2)
{
	int i;
	for(i=0;s1[i];i++)
		if(s1[i]!=s2[i])
			break;

	if(s1[i]=='\0')
		return 0;
	
	else
		if(s1[i]>s2[i])
			return 1;
		else 
			return -1;
}

int str_ncmp(const char *s1,const char *s2,int clen)
{
	int i;
	for(i=0;i<clen;i++)
		if(s1[i]!=s2[i])
			break;

	if(i==clen)
		return 0;
	else
		if(s1[i]>s2[i])
			return 1;
		else 
			return -1;
}
char * str_chr(const char *s,const char ch)
{
	int i;
	for(i=0;s[i];i++)   
		if(s[i]==ch)
			return (char *)s+i;

	return 0;      
}
char * str_rchr(const char *s,const char ch)
{
	int i;
	for(i=0;s[i];i++);
		for(i=i-1;i>=0;i--)   
			if(s[i]==ch)
				return (char *)s+i;

return 0;      
}
char * str_str(const char *m,const char *s)
{
	int i,j;
	for(i=0;m[i];i++)
	{
		if(s[0]==m[i])
		{
			for(j=1;s[j];j++)
				if(s[j]!=m[i+j])
					break;

			if(s[j]=='\0')
				return (char *)m+i;
		}
	}
	return 0;
}

void str_rev(char *s)
{
	int i,j;
	char temp;
    for(i=0;s[i];i++);
	
    for(i=i-1,j=0;i>j;i--,j++)
	{
        temp=s[j];
        s[j]=s[i];
        s[i]=temp;  	
	}
}

void str_upr(char *s)
{
int i;
	for(i=0;s[i];i++)
		if(s[i]>='a'&&s[i]<='z')
			s[i]=s[i]-32;
}

void str_lwr(char *s)
{
int i;
	for(i=0;s[i];i++)
        if(s[i]>='A'&&s[i]<='Z')
            s[i]=s[i]+32;
}

void str_cat(char * m,char * s)
{
int i,j;
	for(i=0;m[i];i++);
        for(i=i,j=0;s[j];i++,j++)
			m[i]=s[j];
            
			m[i]='\0';
}

void int_to_asci(char *str,long int inte)
{
	int i=10,j=0,k=0,isneg=0;
	char temp[10];
	if(inte<0)
	{
		inte*=-1;
		isneg=1;
	}
	while(inte)
	{
		temp[i]=inte%10+0x30;
		inte=inte/10;
		i--;
	}
	if(isneg)
		str[k++]='-';

	for(j=i+1;j<=10;j++){
		str[k++]=temp[j];
	}
	str[k]='\0';
}

void float_to_asci(char *str,float flot)
{
	int ipart,fpart1,point=0,i=0,k=0,isneg=0;
	char res[10];

	if(flot<0)
	{
		flot*=-1;
		isneg=1;
	}
	ipart = (int)flot;

	fpart1=flot * (float)100;

	int_to_asci(res,(int)fpart1);

	if(ipart==0)
		point=0;
	else if(ipart<10)
		point=1;
	else if(ipart<100)
		point=2;
	else if(ipart<1000)
		point=3;
	else if(ipart<10000)
		point=4;

	for(i=str_len(res)+1;i>=point;i--)
		res[i+1]=res[i];
	
	res[point]='.';

	if(isneg)
		str[k++]='-';

	if(!point){
		str[k++]='0';
	}
	for(i=0;i<str_len(res)+1;i++)
		str[k++]=res[i];
}
