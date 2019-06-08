/*
 * 文件名称：error.h
 *
 * 文件说明：system error description 
 * 
 */
 

#ifndef     __ERROE_H
#define     __ERROE_H


#define EOK         0   /* 没有错误 */
#define ERROR       1   /* 通用错误 */
#define ETIMEOUT    2   /* 超时 */
#define EFULL       3   /*  */
#define EEMPTY      4   /*  */
#define ENOMEM      5   /* 内存不足 */
#define EBUSY       6   /* 系统忙 */


typedef signed int  error_t;

#endif                                                            
    

