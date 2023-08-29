/* 
 * File:   Nstring.h
 * Author: Nilesh
 *
 * Created on July 10, 2016, 9:33 AM
 */

#ifndef NSTRING_H
#define	NSTRING_H

#ifdef	__cplusplus
extern "C" {
#endif

int str_len(const char *);
void str_cpy(char *,const char *);
void str_ncpy(char *,const char *,int);
int str_cmp(const char *,const char *);
int str_ncmp(const char *,const char *,int);
char * str_chr(const char *,const char);
char * str_rchr(const char *,const char);
char * str_str(const char *,const char *);
void str_rev(char *);
void str_upr(char *);
void str_lwr(char *);
void str_cat(char *,char*);

void int_to_asci(char *,long int);
void float_to_asci(char *,float);

#ifdef	__cplusplus
}
#endif

#endif	/* NSTRING_H */
