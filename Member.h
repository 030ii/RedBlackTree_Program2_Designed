#ifndef __MEMBER_H__
#define __MEMBER_H__

#define WIDTH "������������������������������������������������������������������������������\n"

void alignCenter(char txt[]);
void roadData(FILE *fp, Tree *RBT, Tree *RBT2);
void menu1_member_view(Tree *tree);
void menu2_member_add(Tree *tree, Tree *tree2);
void menu3_member_modify(Tree *tree, Tree *tree2);
void menu4_member_delete(Tree *tree, Tree *tree2);
void menu6_data_save(Tree *tree);

#endif