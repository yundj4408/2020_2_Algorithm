/* ID: 2016113832  >> REPLACE WITH YOUR ID
* NAME: DongJun Yun >>> REPLACE WITH YOUR NAME
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include<stdio.h>
#include<string.h>// for strlen and strcpy
#include<stdlib.h>// for malloc

struct student { int id; char name[128], major[128]; };

int main( void ) {

 struct student *myself;
 myself->id = 2016113832;
 strcpy(myself->name,"DongJun Yun");
 strcpy(myself->major,"Electronics Engineering");
 printf("ID: %d\n", myself->id);
 printf("NAME: %s\n", myself->name);
 printf("MAJOR: %s\n", myself->major);
}
